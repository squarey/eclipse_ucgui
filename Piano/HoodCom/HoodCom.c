/*
 * HoodCom.c
 *
 *  Created on: 2018年9月25日
 *      Author: Administrator
 */


#include "HoodCom.h"

#if COMPILE_ON_C600
#include "SerialPort.h"
#include "SystemTime.h"
#include <linux/fcntl.h>
#include <pthread.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>

#define 		DEFAULT_UART_PORT_NAME		"/dev/ttyS2"
#define 		DEFAULT_RECEIVED_DATA_BUFFER_LEN	32
#define 		DEFAULT_RECEIVED_DATA_LEN			3
#else
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#endif
#define 		DEFAULT_SEND_DATA_LEN				6

#define			DEFAULT_TIME_SEND_INTERVAL			125	//unit ms

#define			DEFAULT_DELAY_OPEN_LIGHT_CNT		3900	// 延迟开灯的时间 unit ms
#define			DEFAULT_DELAY_OPEN_FAN_CNT			2400	// 延迟开风机的时间 unit ms
#define			DEFAULT_WAIT_PLATE_CLOSE_CNT		5000 // 等待面板关闭的时间 unit ms

#define			DELAY_OPEN_LIGHT_FLAG				0x01
#define			DELAY_OPEN_LIGHT_OPEN_FLAG			0x02
#define			DELAY_OPEN_FAN_FLAG					0x10
#define			DELAY_OPEN_FAN_OPEN_FLAG			0x20
#define			LIGHT_FAN_OPEN_STATUS				0x33
#define			DELAY_OPEN_LIGHT_FAN_START			0x80
#define			DELAY_OPEN_LIGHT_NONE				0x00

/*
* 清洗时 错误标记
**/
#define			ERROR_CLEAN_PUMP					0x80		//水泵故障
#define			ERROR_CLEAN_HOT						0x01		//加热故障
#define			ERROR_CLEAN_BOTH					0x81		//水泵、加热故障
#define			PLATE_UP_COMFIRM					0x10		//面板开到位
#define			PLATE_DOWN_COMFIRM					0x08		//面板关到位

#define			BIT_MOTOR							7		//电机状态位
#define			BIT_CLEAN_PUMP						6		//清洗水泵控制位
#define			BIT_CLEAN_HOT						5		//清洗加热控制位
#define			BIT_PLATE							4		//风网控制位
#define			BIT_LIGHT							3		//灯光控制位
#define			BIT_BEEP							0		//

#define			VOICE_TOUCH							0x03		//0b11 按键声
#define			VOICE_OPEN							0x02		//0b01 开机声
#define			VOICE_CLOSE							0x01		//0b10 关机声

	//private final int FLAG_VOICE_NONE					= 0;			//
#define			FLAG_VOICE_TOUCH					1			//按键声音标记
#define			FLAG_VOICE_OPEN						2			//开机声音标记
#define			FLAG_VOICE_CLOSE					3			//关机声音标记

#define			ERROR_NONE							0			//清洗无错误
#define			ERROR_E2							1			//清洗错误E2
#define			ERROR_E3							2			//清洗错误E3
#define			ERROR_ALL							3			//清洗错误E2 E3同时发生

#define			CMD_OPEN							1
#define			CMD_CLOSE							0
//static U8 _DiplayLastSendData[6];
	//private byte[] _DiplayReceivedData = new byte[6];

//当前档位
static U8 _CurTurnSpeed = 0;
//当前灯状态
static U8 _CurLightStatus = 0;
//当前灯的亮度
static U8 _CurLightValue = 0;
//当前清洗状态
static U8 _CleanStatus = 0;
//当前清洗的温度
static U8 _CleanTemperature = 0;
//开始清洗时所设置的温度
static U8 _CleanTemperatureBase = 0;
//清洗的时间
static U32 _CleanTimeCnt = 0;
/* 清洗时温度上升斜率 */
static U8 _CleanTempUpSlope = 0;
/* 清洗时温度下降斜率 */
static U8 _CleanTempDownSlope = 0;
//清洗错误标记
static U8 _CleanErrorFlag = 0;
//清洗时电控板电机相关控制位
static U8 _CleanControlStatus = 0;
//电控板返回的状态
static U8 _PowerAckStatus = 0;
//电控板返回的实时转速
static U32 _RealTimeSpeed = 0;
//强制面板到位状态
static U8 _FocusPlateStatus = 0;
//清洗时的错误状态
static U8 _SaveErrorStatus = 0;
// 延迟开灯开烟机标记
static U8 _FlagDelayOpenLightFan = 0;
// 需要延迟的时间
static U32 _DelayOpenLightFanCnt = 0;
// 烟机翻版关闭到位状态
static U8 _FlagPlateCloseStatus = 0;
// 等待翻版关闭的时间
static U32 _PlateCloseCnt = 0;
//所需发送声音的标记
static U8 _FlagTouch = 0;
//声音改变次数
static U8 _VoiceChangeCnt = 0;
//参考时间
static U32 _SystemRefTime = 0;
//上一次参考时间
static U32 _LastRefTime = 0;
static U32 _LastSendTime = 0;

#if COMPILE_ON_C600
static int _fd = 0;
static U32 _SaveReceivedDataLen = 0;
static U8 _DiplayReceivedData[DEFAULT_RECEIVED_DATA_BUFFER_LEN];
#endif
static U8 _DiplaySendData[DEFAULT_SEND_DATA_LEN];
static U32 _CurReceivedDataLen = 0;
//设置风机档位 范围0-28   0表示风机停止
void HoodCom_SetTurnSpeed(U8 Speed)
{
	_CurTurnSpeed = Speed;
}
//设置灯状态  IsOpen: 0 灯光关闭  1:灯光开启    Value: 灯的亮度值  范围0-100
//只有当IsOpen为1  且 Value不为0时灯才会亮
void HoodCom_SetLightStatus(U8 IsOpen, U8 Value)
{
	_CurLightStatus = IsOpen;
	_CurLightValue = Value;
}
//设置清洗的状态   IsStartClen: 1 开启清洗   0关闭清洗
//每次开启清洗时需传入当前的温度值
void HoodCom_SetCleanStatus(U8 IsStartClen, U8 Temperature)
{
	if(_CleanStatus != IsStartClen){
		I32 TempSlope = 0;
		//计算温度上升与下降的斜率
		TempSlope = (93 - Temperature) << 10;
		_CleanTempUpSlope = TempSlope/60;
		TempSlope = (99 - Temperature) << 10;
		_CleanTempDownSlope = TempSlope/60;
		_CleanStatus = IsStartClen;
		_CleanTemperature = Temperature;
		_CleanTemperatureBase = Temperature;
		//重置清洗时间与参考时间
		_CleanTimeCnt = 600;
		_LastRefTime = _SystemRefTime;
		HoodCom_SetLightStatus(0, 0);
		HoodCom_SetTurnSpeed(0);
	}
}
//设置电控板返回的状态
static void _SetBoardStatus(U8 Status)
{
	_PowerAckStatus = Status;
}
//设置电控板返回来的实时转速
static void _SetBoardSpeed(U32 Speed)
{
	_RealTimeSpeed = Speed;
}
//强制设置面板到位状态  IsUpConfirm: 1 强制开到位   其他值 强制关到位
static void _SetFocusPlateStatus(U8 IsUpConfirm)
{
	if(1 == IsUpConfirm){
		_FocusPlateStatus = 1;
	}else if(0 == IsUpConfirm){
		_FocusPlateStatus = 2;
	}else{
		_FocusPlateStatus = 3;
	}
}
//发送按键声
void HoodCom_SendTouchVoice(void)
{
	_VoiceChangeCnt++;
	_FlagTouch = FLAG_VOICE_TOUCH;
}
//发送开机声
void HoodCom_SendOpenVoice(void)
{
	_VoiceChangeCnt++;
	_FlagTouch = FLAG_VOICE_OPEN;
}
void HoodCom_SendCloseVoice(void)
{
	_VoiceChangeCnt++;
	_FlagTouch = FLAG_VOICE_CLOSE;
}
//获取当前的转速
U8 HoodCom_GetTurnSpeed(void)
{
	return _CurTurnSpeed;
}
//获取当前灯的状态
U8 HoodCom_GetLightStatus(void)
{
	return _CurLightStatus;
}
//获取当前灯的亮度值
U8 HoodCom_GetLightValue(void)
{
	return _CurLightValue;
}
//获取清洗时的清洗温度
U8 HoodCom_GetCleanTemperature(void)
{
	return _CleanTemperature;
}
//获取清洗倒计时的时间   单位:秒
//当返回0值时  表示此次清洗已经结束
U8 HoodCom_GetCleanTimeCnt(void)
{
	return _CleanTimeCnt;
}
//获取电控板返回的实时转速
U32 HoodCom_GetRealTimeSpeed(void)
{
	return _RealTimeSpeed;
}
//获取清洗时发生的错误状态  无错误返回 ERROR_NONE
U8 HoodCom_GetCleanErrorStatus(void)
{
	return _SaveErrorStatus;
}
//错误状态  无错误返回 ERROR_NONE
U8 HoodCom_GetBoardWarnStatus(void)
{
	if(ERROR_CLEAN_BOTH == (_PowerAckStatus & ERROR_CLEAN_BOTH)){
		return ERROR_ALL;
	}else if(ERROR_CLEAN_HOT == (_PowerAckStatus & ERROR_CLEAN_HOT)){
		return ERROR_E2;
	}else if(ERROR_CLEAN_PUMP == (_PowerAckStatus & ERROR_CLEAN_PUMP)){
		return ERROR_E3;
	}else{
		return ERROR_NONE;
	}
}
//获取电控板返回的面板开到位状态 返回1 即表示开到位
U8 HoodCom_GetPlateUpComfirm(void)
{
	return (PLATE_UP_COMFIRM == (_PowerAckStatus & PLATE_UP_COMFIRM)) ? 1 : 0;
}
//获取电控板返回的面板关到位状态  返回1 即表示关到位
U8 HoodCom_GetPlateDownComfirm(void)
{
	return (PLATE_DOWN_COMFIRM == (_PowerAckStatus & PLATE_DOWN_COMFIRM)) ? 1 : 0;
}
//获取强制面板开到位状态 返回1 即表示开到位
U8 HoodCom_GetPlateUpFocusComfirm(void)
{
	return (1 == _FocusPlateStatus) ? 1 : 0;
}
//获取强制面板关到位状态  返回1 即表示关到位
U8 HoodCom_GetPlateDownFocusComfirm(void)
{
	return (2 == _FocusPlateStatus) ? 1 : 0;
}
/*
* 清洗功能处理
*/
static void _CleanFunctionWork(void){
	U32 CurrentCount = 0;
	U32 CurrentTemp = 0;
	if(_SystemRefTime - _LastRefTime < 1000){
		return;
	}
	CurrentCount = 600 - _CleanTimeCnt;
	_LastRefTime = _SystemRefTime;
	CurrentTemp = _CleanTemperature;
	/* 判断清洗状态是否有误 */
	if(ERROR_NONE != HoodCom_GetBoardWarnStatus()){
		if(0 == _CleanErrorFlag){
			_SaveErrorStatus = HoodCom_GetBoardWarnStatus();
			_CleanErrorFlag = 1;
		}
	}
	/* 如果清洗有误则停止加热与水泵 */
	if(1 == _CleanErrorFlag){
		_CleanControlStatus = 0;
		_CleanControlStatus |= 0 << BIT_MOTOR;
		_CleanControlStatus |= 0 << BIT_PLATE;
		_CleanControlStatus |= 0 << BIT_CLEAN_PUMP;
		_CleanControlStatus |= 0 << BIT_CLEAN_HOT;
		HoodCom_SetTurnSpeed(0);
		return;
	}
	_CleanControlStatus = 0;
	/* 清洗300秒一个周期 */
	if(CurrentCount > 300){
		CurrentCount -= 300;
	}
	if(CurrentCount <= 300){
		/* 前240秒内是加热状态 */
		if(CurrentCount < 240){
			HoodCom_SetTurnSpeed(0);
			if((0 == HoodCom_GetPlateDownComfirm()) && (0 == HoodCom_GetPlateDownFocusComfirm())){
				return;
			}
			_CleanTimeCnt--;
			_CleanControlStatus |= 1 << BIT_CLEAN_PUMP;
			_CleanControlStatus |= 1 << BIT_CLEAN_HOT;
			/* 清洗步骤1 60s温度上升至94摄氏度 */
			if(CurrentCount < 60){
				if(CurrentTemp < 94){
					CurrentTemp = _CleanTemperatureBase + ((_CleanTempUpSlope * CurrentCount) >> 10);
				}
				/* 60s温度94 */
			}else if(60 == CurrentCount){
				CurrentTemp = 94;
				/* 90秒内上升到95度 */
			}else if(CurrentCount == 85){
				CurrentTemp = 95;
				/* 120秒内上升到96度 */
			}else if(CurrentCount == 115){
				CurrentTemp = 96;
				/* 150秒内上升到97度 */
			}else if(CurrentCount == 145){
				CurrentTemp = 97;
				/* 180秒内上升到98度 */
			}else if(CurrentCount == 175){
				CurrentTemp = 98;
				/* 210秒内上升到99度 */
			}else if(CurrentCount == 205){
				CurrentTemp = 99;
			}
		}else{
			/* 240秒-300秒打开风机吹风60s */
			_CleanControlStatus |= 0 << BIT_CLEAN_PUMP;
			_CleanControlStatus |= 0 << BIT_CLEAN_HOT;
			//_CleanControlStatus |= 1 << BIT_MOTOR;
			//_CleanControlStatus |= 1 << BIT_PLATE;
			HoodCom_SetTurnSpeed(25);
			/* 当面板开到位的时候才开始倒计时   */
			if((1 == HoodCom_GetPlateUpComfirm()) || (1 == HoodCom_GetPlateUpFocusComfirm())){
				_CleanTimeCnt--;
				if(CurrentTemp > _CleanTemperatureBase){
					/*if(CurrentCount < 260){
						CurrentTemp -= 2;
					}else {
						CurrentTemp -= 1;
					}*/
					CurrentTemp = ((99 << 10) - _CleanTempDownSlope * (CurrentCount - 240)) >> 10;
				}else{
					CurrentTemp = _CleanTemperatureBase;
				}
			}
		}
	}
	//_CleanTimeCnt = CurrentCount;
	_CleanTemperature = CurrentTemp;
	if(0 == _CleanTimeCnt){
		_CleanStatus = 0;
		HoodCom_SetTurnSpeed(0);
	}
}
//定时发送显示板的状态给电控板
static void _TimingControlDataSend(void)
{
	U32 CleanStatus = 0;
	U32 i = 0;
	U32 AdjustValue = 0;
	U32 CurrentSystemTime = 0;
	CurrentSystemTime = _SystemRefTime;

	CleanStatus = _CleanStatus;
	/* 如果是在清洗状态 则发送清洗状态给电控板 */
	if(CMD_OPEN == CleanStatus){
		_CleanFunctionWork();
		_DiplaySendData[1] = _CleanControlStatus;
	}else{
		/* 非清洗状态则清除所有清洗错误位 */
		_LastRefTime = _SystemRefTime;
		_CleanErrorFlag = 0;
		_SaveErrorStatus = ERROR_NONE;
		_DiplaySendData[1] = 0;
		/* 第三个字节为灯的亮度值 */
		_DiplaySendData[2] = HoodCom_GetLightValue();
		_CleanTempUpSlope = 0;
		_CleanTempDownSlope = 0;
	}
	if(CMD_CLOSE == HoodCom_GetLightStatus()){
		_FlagDelayOpenLightFan &= ~(DELAY_OPEN_LIGHT_FLAG | DELAY_OPEN_LIGHT_OPEN_FLAG);
	}else{
		_FlagDelayOpenLightFan |= DELAY_OPEN_LIGHT_FLAG;
		_DiplaySendData[1] |= 1 << BIT_MOTOR;
		_DiplaySendData[1] |= 1 << BIT_PLATE;
	}
	if(0 == HoodCom_GetTurnSpeed()){
		_FlagDelayOpenLightFan &= ~(DELAY_OPEN_FAN_FLAG | DELAY_OPEN_FAN_OPEN_FLAG);
	}else{
		_FlagDelayOpenLightFan |= DELAY_OPEN_FAN_FLAG;
		_DiplaySendData[1] |= 1 << BIT_MOTOR;
		_DiplaySendData[1] |= 1 << BIT_PLATE;
	}
	/* 判断是否灯跟点击都未启动 */
	if(DELAY_OPEN_LIGHT_NONE == (_FlagDelayOpenLightFan & LIGHT_FAN_OPEN_STATUS)){
		_FlagDelayOpenLightFan = DELAY_OPEN_LIGHT_NONE;
		_DiplaySendData[0] = 0;
		if(CMD_CLOSE == CleanStatus){
			_DiplaySendData[1] = 0;
		}else{
			_DiplaySendData[1] = _CleanControlStatus;
		}
		_DelayOpenLightFanCnt = 0;
		if(0 == _FlagPlateCloseStatus){
			_PlateCloseCnt = CurrentSystemTime;
			_FlagPlateCloseStatus = 1;
		}else if(1 == _FlagPlateCloseStatus){
			if((CurrentSystemTime - _PlateCloseCnt) >= DEFAULT_WAIT_PLATE_CLOSE_CNT){
				_FlagPlateCloseStatus = 2;
				/* 强制设置面板关到位 */
				_SetFocusPlateStatus(0);
			}
		}
	}else{
		/* 如果还没有开始延时计时 则记录此时的时间 */
		if(DELAY_OPEN_LIGHT_FAN_START != (DELAY_OPEN_LIGHT_FAN_START & _FlagDelayOpenLightFan)){
			_DelayOpenLightFanCnt = CurrentSystemTime;
			_FlagDelayOpenLightFan |= DELAY_OPEN_LIGHT_FAN_START;
			_SetFocusPlateStatus(2);
		}
		_FlagPlateCloseStatus = 0;
		_PlateCloseCnt = 0;
	}
	/* 判断风机延迟启动时间是否已经到 */
	if((DELAY_OPEN_FAN_FLAG == (_FlagDelayOpenLightFan & DELAY_OPEN_FAN_FLAG)) &&
			((CurrentSystemTime - _DelayOpenLightFanCnt) >= DEFAULT_DELAY_OPEN_FAN_CNT)){
		_FlagDelayOpenLightFan |= DELAY_OPEN_FAN_OPEN_FLAG;
	}
	/* 判断灯的延迟启动时间是否到 */
	if((DELAY_OPEN_LIGHT_FLAG == (_FlagDelayOpenLightFan & DELAY_OPEN_LIGHT_FLAG)) &&
			((CurrentSystemTime - _DelayOpenLightFanCnt) >= DEFAULT_DELAY_OPEN_LIGHT_CNT)){
		_FlagDelayOpenLightFan |= DELAY_OPEN_LIGHT_OPEN_FLAG;
		_SetFocusPlateStatus(1);
	}
	/* 如果电机延时启动时间到 则打开电机 */
	if(DELAY_OPEN_FAN_OPEN_FLAG == (DELAY_OPEN_FAN_OPEN_FLAG & _FlagDelayOpenLightFan)){
		_DiplaySendData[0] = HoodCom_GetTurnSpeed();
		/* 强制设置面板开到位  */
		_SetFocusPlateStatus(1);
	}else{
		_DiplaySendData[0] = 0;
	}
	/* 如果灯延时启动时间到  则打开灯 */
	if(DELAY_OPEN_LIGHT_OPEN_FLAG == (DELAY_OPEN_LIGHT_OPEN_FLAG & _FlagDelayOpenLightFan)){
		if(CMD_OPEN == HoodCom_GetLightStatus()){
			_DiplaySendData[1] |= 1 << BIT_LIGHT;
		}
	}
	/* 发送声音控制位 */
	if(FLAG_VOICE_TOUCH == _FlagTouch){
		_DiplaySendData[1] |= VOICE_TOUCH << BIT_BEEP;
	}else if(FLAG_VOICE_OPEN == _FlagTouch){
		_DiplaySendData[1] |= VOICE_OPEN << BIT_BEEP;
	}else if(FLAG_VOICE_CLOSE == _FlagTouch){
		_DiplaySendData[1] |= VOICE_CLOSE << BIT_BEEP;
	}
	_DiplaySendData[3] = _VoiceChangeCnt & 0x03;

	/* 计算校验值 */
	for(i = 0; i < 4; i++){

		AdjustValue += (_DiplaySendData[i] & 0x0ff);
	}
	_DiplaySendData[4] = AdjustValue & 0xff;
	_DiplaySendData[5] = (AdjustValue & 0x0ff00) >> 8;
	//通过串口将数据发送出去
	if(CurrentSystemTime - _LastSendTime >= DEFAULT_TIME_SEND_INTERVAL){
		_LastSendTime = CurrentSystemTime;
#if COMPILE_ON_C600
		SerialPortWriteData(_fd, _DiplaySendData, DEFAULT_SEND_DATA_LEN);
#endif
	}
}
static U8 _TimingControlDataGet(U8 *pBuffer, U32 Len)
{
	if(Len < 3){
		return 0;
	}
	U32 BufferLen = Len;
	U32 i = 0;
	if(BufferLen >= 3){
		int adjustValue = 0;
		for(i = 0; i <= BufferLen - 3; i++){
			adjustValue = pBuffer[i] + pBuffer[i + 1];
			adjustValue = adjustValue & 0xff;
			if(adjustValue == pBuffer[i + 2]){
				_SetBoardSpeed(pBuffer[i] * 15);
				_SetBoardStatus(pBuffer[i + 1]);
				return 1;
			}
		}
	}
	return 0;
}
#if COMPILE_ON_C600
static void _UseSelectToReadUartData(void)
{
	int Ret = 0;
	fd_set ReadFd;
	struct timeval Timeout;

	Timeout.tv_sec = 0;
	Timeout.tv_usec = 100000;

	FD_ZERO(&ReadFd);
	FD_SET(_fd, &ReadFd);
	Ret = select(_fd + 1,&ReadFd,NULL,NULL,&Timeout);

	if (-1 == Ret){
		GUI_Debug("select fail\n");
	}else if(Ret > 0){
		if(FD_ISSET(_fd, &ReadFd)){
			U32 ReceivedDataLen = 0;
			U8 tBuffer[DEFAULT_RECEIVED_DATA_BUFFER_LEN] = {0};
			/* 发送数据之前先读取串口缓存是否有数据 */
			ReceivedDataLen = SerialPortReadData(_fd, tBuffer, DEFAULT_RECEIVED_DATA_BUFFER_LEN);
			if(ReceivedDataLen > 0){
				if((ReceivedDataLen + _SaveReceivedDataLen) >= DEFAULT_RECEIVED_DATA_BUFFER_LEN){
					_SaveReceivedDataLen = 0;
				}
				memcpy(&_DiplayReceivedData[_SaveReceivedDataLen], tBuffer, ReceivedDataLen);
				_SaveReceivedDataLen += ReceivedDataLen;
				GUI_Debug("_SaveReceivedDataLen:%d\n", _SaveReceivedDataLen);
				if(_TimingControlDataGet(_DiplayReceivedData, _SaveReceivedDataLen)){
					_SaveReceivedDataLen = 0;
				}
			}
		}
	}else{
		//GUI_Debug("select timeout \n");
	}
}
#endif
static void *_HoodComProcess(void *ptr)
{
	while(1){
#if COMPILE_ON_C600
		_UseSelectToReadUartData();
		_SystemRefTime = GetCurrentSystemTime();
#else
		struct timeval tv;
		sleep(1);
		mingw_gettimeofday(&tv, NULL);
		_SystemRefTime = (tv.tv_sec * 1000  + tv.tv_usec/1000);
		//printf("t second %d, usecond %d\n", tv.tv_sec, tv.tv_usec);
		//printf("eclipse cdt pthread cb _SystemRefTime:%d\n", _SystemRefTime);
#endif
		_TimingControlDataSend();
#if COMPILE_ON_C600
		usleep(10000);
#endif
	}
	return 0;
}

static void _HoodComThreadInit(void)
{
	int Err;
	pthread_t ThreadID;
	Err = pthread_create(&ThreadID, NULL, _HoodComProcess, NULL);
	if(0 != Err){
		GUI_Debug("creat thread fail\n");
		return;
	}
	pthread_detach(ThreadID);
	GUI_Debug("Thread create successful\n");
}

//电控板通信初始化
void HoodComInit(void)
{
#if COMPILE_ON_C600
	_fd = open(DEFAULT_UART_PORT_NAME, O_RDWR);
	if(_fd < 0){
		GUI_Debug("open %s fail\n", DEFAULT_UART_PORT_NAME);
		return;
	}
	SetSerialPortParameter(_fd, 9600, 8, 's', 1, DEFAULT_RECEIVED_DATA_LEN);
#endif
	_HoodComThreadInit();
}

//获取串口收到的数据
U32 GetSerialPortReceivedData(char *pBuf, U32 MaxLen)
{
	char TempDataBuffer[13] = {0};
	for(_CurReceivedDataLen = 0; _CurReceivedDataLen < 12; _CurReceivedDataLen++){
		TempDataBuffer[_CurReceivedDataLen] = _CurReceivedDataLen;
	}
	if(_CurReceivedDataLen > 0){
		if(_CurReceivedDataLen < MaxLen){
			memcpy(pBuf, TempDataBuffer, _CurReceivedDataLen);
			return _CurReceivedDataLen;
		}else{
			memcpy(pBuf, TempDataBuffer, MaxLen);
			return MaxLen;
		}
	}
	return 0;
}
