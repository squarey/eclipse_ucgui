/*
 * SettingInfo.c
 *
 *  Created on: 2018年5月15日
 *      Author: Administrator
 */


#include "SettingInfo.h"


typedef struct
{
	U8 TimerTimeValue;			//定时时间
	U8 KitchenTempValue;		//厨房模式设定温度
	U8 KitchenWaterValue;		//厨房模式设定水量
	U8 BathroomTempValue;		//浴室模式设定温度
	U8 BathroomWaterValue;		//浴室模式设定水量
	U8 BathtubTempValue;		//浴缸模式设定温度
	U8 BathtubWaterValue;		//浴缸模式设定水量
	U8 EnergyTempValue;			//节能模式设定温度
	U8 EnergyWaterValue;		//节能模式设定水量
	U8 FunctionSelect;			//当前模式选择
	U8 Model;					//当前设定机型
	U8 ValveMax;				//当前设定比例阀的最大值
	U8 ValveMin;				//当前设定比例阀的最小值
	U8 FireOnValue;				//当前设定比例阀点火值
	U8 DisplayStatus;			//显示器状态  1: 开  0:关
	U8 DebugFlag;				//1: 需要进入调试模式  2:正在调试模式中  3:退出调试模式,不保存   4:保存并且退出调试模式
}WATER_HEATER_DISP_DATA;

typedef struct
{
	U8 FireStatus;					//火焰状态				1: 有火		0:无火
	U8 FanRun;						//风机运行状态			1: 运行		0:停止
	U8 ShowerWater;					//淋浴有水状态			1: 有水		0:无水
	U8 FaultExist;					//故障状态				1: 有故障	0:无故障
	U8 BathtubWaterOut;				//浴缸放水状态			1: 放水结束 0:在放水
	U8 OutTemperatureValue;			//出水温度
	U8 TimerValue;					//定时时间
	U8 ErrorStatus;					//故障代码
	U8 WorkMode;					//电控板返回的目前正在工作的工作状态
	U8 DebugMode;					//0: 正常工作模式  1: 调试模式
	U8 MachineMode;					//电控板返回的当前机型
	U16 WorkTotalTime;				//正常工作时间  单位: 秒
	U8 SetTimerTimes;				//设置时间
	U8 CurrentWaterFlow;			//当前水流量
	U8 InTemperatureValue;			//进水温度
	U8 FanSpeed;					//风机转速
	U8 LoadOutput;					//当前负荷输出

	//工作模式的相关状态
	U16 WaterUsed;					//已用水量		单位: 升
	U8 TurnOnWaterValue;			//目标放水量  总水量/10  单位: 升
	U8 WaterValveAdjustValue;		//水阀调节目标水量
	U8 TemperatureMinValue;			//能设定的温度下限值
	U8 TemperatureMaxValue;			//能设定的温度上限值
	U8 CommunicationVersion;		//协议版本号
	U8 ProgramVersion;				//程序版本号

	//调试模式的相关状态
	U8 DebugSerialNumber;			//调试的序列号
	U8 DisplayMode;					//在显示器上调试数值显示的方式   bit3->bit0   0: 此参数数值不可调  1:此参数值随意可调  2:此参数状态可调 0值显示of  20-99时显示当前数值
									//bit5->bit4  显示器连续3秒不操作时,需要显示的内容   0:不显示反馈值  1:显示温度值  2:显示转速值
									//bit7->bit6  参数值显示的方式  0:十六进制显示  1:十进制显示  2:字符显示
	U8 ParameterCodeString[3];		//参数代码字符串
	U8 ParameterValue;				//参数数值
	U8 ParameterValueString[3];		//参数数值字符串
	U8 CurParameterValueMin;		//当前参数数值下限值
	U8 CurParameterValueMax;		//当前参数数值上限值
	U8 DebugSerialNumberMax;		//可设置序列号上限值

}WATER_HEATER_POWER_DATA;

typedef struct
{
	U8 GoToNext;					//调试下一项
	U8 GoToPre;						//调试前一项
	U8 GoToSet;						//需发送当前设置值
	U8 CurValue;					//当前值
	U8 CurSerialNumber;				//当前所需调试的序列号
}WATER_HEATER_DEBUG_DATA;

static WATER_HEATER_DISP_DATA _tWaterHeaterDispData;
static WATER_HEATER_POWER_DATA _tWaterHeaterPowerData;
static WATER_HEATER_DEBUG_DATA _tWaterHeaterDebugData;

/* water heater data set */
void SetTimerTimeValue(U8 Value)
{
	_tWaterHeaterDispData.TimerTimeValue = Value;
}
void SetKitchenTempValue(U8 Value)
{
	_tWaterHeaterDispData.KitchenTempValue = Value;
}
void SetKitchenWaterValue(U8 Value)
{
	_tWaterHeaterDispData.KitchenWaterValue = Value;
}
void SetBathroomTempValue(U8 Value)
{
	_tWaterHeaterDispData.BathroomTempValue = Value;
}
void SetBathroomWaterValue(U8 Value)
{
	_tWaterHeaterDispData.BathroomWaterValue = Value;
}
void SetBathtubTempValue(U8 Value)
{
	_tWaterHeaterDispData.BathtubTempValue = Value;
}
void SetBathtubWaterValue(U8 Value)
{
	_tWaterHeaterDispData.BathtubWaterValue = Value;
}
void SetEnergyTempValue(U8 Value)
{
	_tWaterHeaterDispData.EnergyTempValue = Value;
}
void SetEnergyWaterValue(U8 Value)
{
	_tWaterHeaterDispData.EnergyWaterValue = Value;
}
void SetWaterHeaterFuncSelect(U8 Func)
{
	_tWaterHeaterDispData.FunctionSelect = Func;
}
void SetWaterHeaterModel(U8 Model)
{
	_tWaterHeaterDispData.Model = Model;
}
void SetWaterHeaterValveMaxValue(U8 Value)
{
	_tWaterHeaterDispData.ValveMax = Value;
}
void SetWaterHeaterValveMinValue(U8 Value)
{
	_tWaterHeaterDispData.ValveMin = Value;
}
void SetWaterHeaterFireOnValue(U8 Value)
{
	_tWaterHeaterDispData.FireOnValue = Value;
}
void SetWaterHeaterEnterDebugMode(void)
{
	_tWaterHeaterDispData.DebugFlag = DEBUG_MODE_NEED_TO_ENTER;
}
void SetWaterHeaterSaveExitDebugMode(void)
{
	_tWaterHeaterDispData.DebugFlag = DEBUG_MODE_EXIT_SAVE;
}
void SetWaterHeaterNotSaveExitDebugMode(void)
{
	_tWaterHeaterDispData.DebugFlag = DEBUG_MODE_EXIT_NOT_SAVE;
}
void SetWaterHeaterIsInDebugMode(void)
{
	_tWaterHeaterDispData.DebugFlag = DEBUG_MODE_IS_IN;
}
void SetWaterHeaterIsExitDebugMode(void)
{
	_tWaterHeaterDispData.DebugFlag = DEBUG_MODE_NONE;
}

/* water heater data get */
U8 GetTimerTimeValue(void)
{
	return _tWaterHeaterDispData.TimerTimeValue;
}
U8 GetKitchenTempValue(void)
{
	return _tWaterHeaterDispData.KitchenTempValue;
}
U8 GetKitchenWaterValue(void)
{
	return _tWaterHeaterDispData.KitchenWaterValue;
}
U8 GetBathroomTempValue(void)
{
	return _tWaterHeaterDispData.BathroomTempValue;
}
U8 GetBathroomWaterValue(void)
{
	return _tWaterHeaterDispData.BathroomWaterValue;
}
U8 GetBathtubTempValue(void)
{
	return _tWaterHeaterDispData.BathtubTempValue;
}
U8 GetBathtubWaterValue(void)
{
	return _tWaterHeaterDispData.BathtubWaterValue;
}
U8 GetEnergyTempValue(void)
{
	return _tWaterHeaterDispData.EnergyTempValue;
}
U8 GetEnergyWaterValue(void)
{
	return _tWaterHeaterDispData.EnergyWaterValue;
}
U8 GetWaterHeaterFuncSelect(void)
{
	return _tWaterHeaterDispData.FunctionSelect;
}
U8 GetWaterHeaterModel(void)
{
	return _tWaterHeaterDispData.Model;
}
U8 GetWaterHeaterValveMaxValue(void)
{
	return _tWaterHeaterDispData.ValveMax;
}
U8 GetWaterHeaterValveMinValue(void)
{
	return _tWaterHeaterDispData.ValveMin;
}
U8 GetWaterHeaterFireOnValue(void)
{
	return _tWaterHeaterDispData.FireOnValue;
}
U8 GetWaterHeaterDebugMode(void)
{
	return _tWaterHeaterDispData.DebugFlag;
}


/* 电控板返回信息 */
void SetWaterHeaterPowerFire(U8 Status)
{
	_tWaterHeaterPowerData.FireStatus = Status;
}
void SetWaterHeaterPowerOutTemperature(U8 Temperature)
{
	_tWaterHeaterPowerData.OutTemperatureValue = Temperature;
}
void SetWaterHeaterPowerErrorStatus(U8 Status)
{
	_tWaterHeaterPowerData.ErrorStatus = Status;
}
void SetWaterHeaterPowerFanRun(U8 Status)
{
	_tWaterHeaterPowerData.FanRun = Status;
}
void SetWaterHeaterPowerShowerWater(U8 Status)
{
	_tWaterHeaterPowerData.ShowerWater = Status;
}
void SetWaterHeaterPowerFaultExist(U8 Status)
{
	_tWaterHeaterPowerData.FaultExist = Status;
}
void SetWaterHeaterPowerBathtubWaterOut(U8 Status)
{
	_tWaterHeaterPowerData.BathtubWaterOut = Status;
}
void SetWaterHeaterPowerWorkMode(U8 Mode)
{
	_tWaterHeaterPowerData.WorkMode = Mode;
}
void SetWaterHeaterPowerDebugMode(U8 Mode)
{
	_tWaterHeaterPowerData.DebugMode = Mode;
}
void SetWaterHeaterPowerMachineMode(U8 Mode)
{
	_tWaterHeaterPowerData.MachineMode = Mode;
}
void SetWaterHeaterPowerWorkTime(U16 Time)
{
	_tWaterHeaterPowerData.WorkTotalTime = Time;
}
void SetWaterHeaterPowerTimerTimes(U8 Time)
{
	_tWaterHeaterPowerData.SetTimerTimes = Time;
}
void SetWaterHeaterPowerWaterFlow(U8 Value)
{
	_tWaterHeaterPowerData.CurrentWaterFlow = Value;
}
void SetWaterHeaterPowerInTemperatureValue(U8 Value)
{
	_tWaterHeaterPowerData.InTemperatureValue = Value;
}
void SetWaterHeaterPowerFanSpeed(U8 Speed)
{
	_tWaterHeaterPowerData.FanSpeed = Speed;
}
void SetWaterHeaterPowerLoadOutput(U8 Value)
{
	_tWaterHeaterPowerData.LoadOutput = Value;
}
void SetWaterHeaterPowerWaterUsed(U16 Value)
{
	_tWaterHeaterPowerData.WaterUsed = Value;
}
void SetWaterHeaterPowerTurnOnWaterValue(U8 Value)
{
	_tWaterHeaterPowerData.TurnOnWaterValue = Value;
}
void SetWaterHeaterPowerWaterValveAdjustValue(U8 Value)
{
	_tWaterHeaterPowerData.WaterValveAdjustValue = Value;
}
void SetWaterHeaterPowerTemperatureMinValue(U8 Value)
{
	_tWaterHeaterPowerData.TemperatureMinValue = Value;
}
void SetWaterHeaterPowerTemperatureMaxValue(U8 Value)
{
	_tWaterHeaterPowerData.TemperatureMaxValue = Value;
}
void SetWaterHeaterPowerCommunicationVersion(U8 Value)
{
	_tWaterHeaterPowerData.CommunicationVersion = Value;
}
void SetWaterHeaterPowerProgramVersion(U8 Value)
{
	_tWaterHeaterPowerData.ProgramVersion = Value;
}
void SetWaterHeaterPowerDebugSerialNumber(U8 Value)
{
	_tWaterHeaterPowerData.DebugSerialNumber = Value;
}
void SetWaterHeaterPowerDisplayMode(U8 Value)
{
	_tWaterHeaterPowerData.DisplayMode = Value;
}
void SetWaterHeaterPowerParameterCodeString(const U8 *pString)
{
	if(pString){
		GUI_memcpy(_tWaterHeaterPowerData.ParameterCodeString, pString, 3);
	}
}
void SetWaterHeaterPowerParameterValue(U8 Value)
{
	_tWaterHeaterPowerData.ParameterValue = Value;
}
void SetWaterHeaterPowerParameterValueString(const U8 *pString)
{
	if(pString){
		GUI_memcpy(_tWaterHeaterPowerData.ParameterValueString, pString, 3);
	}
}
void SetWaterHeaterPowerCurParameterValueMin(U8 Value)
{
	_tWaterHeaterPowerData.CurParameterValueMin = Value;
}
void SetWaterHeaterPowerCurParameterValueMax(U8 Value)
{
	_tWaterHeaterPowerData.CurParameterValueMax = Value;
}
void SetWaterHeaterPowerDebugSerialNumberMax(U8 Value)
{
	_tWaterHeaterPowerData.DebugSerialNumberMax = Value;
}
U8 GetWaterHeaterPowerFire(void)
{
	return _tWaterHeaterPowerData.FireStatus;
}
U8 GetWaterHeaterPowerOutTemperature(void)
{
	return _tWaterHeaterPowerData.OutTemperatureValue;
}
U8 GetWaterHeaterPowerErrorStatus(void)
{
	return _tWaterHeaterPowerData.ErrorStatus;
}
U8 GetWaterHeaterPowerFanRun(void)
{
	return _tWaterHeaterPowerData.FanRun;
}
U8 GetWaterHeaterPowerShowerWater(void)
{
	return _tWaterHeaterPowerData.ShowerWater;
}
U8 GetWaterHeaterPowerFaultExist(void)
{
	return _tWaterHeaterPowerData.FaultExist;
}
U8 GetWaterHeaterPowerBathtubWaterOut(void)
{
	return _tWaterHeaterPowerData.BathtubWaterOut;
}
U8 GetWaterHeaterPowerWorkMode(void)
{
	return _tWaterHeaterPowerData.WorkMode;
}
U8 GetWaterHeaterPowerDebugMode(void)
{
	return _tWaterHeaterPowerData.DebugMode;
}
U8 GetWaterHeaterPowerMachineMode(void)
{
	return _tWaterHeaterPowerData.MachineMode;
}
U16 GetWaterHeaterPowerWorkTime(void)
{
	return _tWaterHeaterPowerData.WorkTotalTime;
}
U8 GetWaterHeaterPowerTimerTimes(void)
{
	return _tWaterHeaterPowerData.SetTimerTimes;
}
U8 GetWaterHeaterPowerWaterFlow(void)
{
	return _tWaterHeaterPowerData.CurrentWaterFlow;
}
U8 GetWaterHeaterPowerInTemperatureValue(void)
{
	return _tWaterHeaterPowerData.InTemperatureValue;
}
U8 GetWaterHeaterPowerFanSpeed(void)
{
	return _tWaterHeaterPowerData.FanSpeed;
}
U8 GetWaterHeaterPowerLoadOutput(void)
{
	return _tWaterHeaterPowerData.LoadOutput;
}
U16 GetWaterHeaterPowerWaterUsed(void)
{
	return _tWaterHeaterPowerData.WaterUsed;
}
U8 GetWaterHeaterPowerTurnOnWaterValue(void)
{
	return _tWaterHeaterPowerData.TurnOnWaterValue;
}
U8 GetWaterHeaterPowerWaterValveAdjustValue(void)
{
	return _tWaterHeaterPowerData.WaterValveAdjustValue;
}
U8 GetWaterHeaterPowerTemperatureMinValue(void)
{
	return _tWaterHeaterPowerData.TemperatureMinValue;
}
U8 GetWaterHeaterPowerTemperatureMaxValue(void)
{
	return _tWaterHeaterPowerData.TemperatureMaxValue;
}
U8 GetWaterHeaterPowerCommunicationVersion(void)
{
	return _tWaterHeaterPowerData.CommunicationVersion;
}
U8 GetWaterHeaterPowerProgramVersion(void)
{
	return _tWaterHeaterPowerData.ProgramVersion;
}
U8 GetWaterHeaterPowerDebugSerialNumber(void)
{
	return _tWaterHeaterPowerData.DebugSerialNumber;
}
U8 GetWaterHeaterPowerDisplayMode(void)
{
	return _tWaterHeaterPowerData.DisplayMode;
}
void GetWaterHeaterPowerParameterCodeString(U8 *pString)
{
	if(pString){
		GUI_memcpy(pString, _tWaterHeaterPowerData.ParameterCodeString, 3);
	}
}
U8 GetWaterHeaterPowerParameterValue(void)
{
	return _tWaterHeaterPowerData.ParameterValue;
}
void GetWaterHeaterPowerParameterValueString(U8 *pString)
{
	if(pString){
		GUI_memcpy(pString, _tWaterHeaterPowerData.ParameterValueString, 3);
	}
}
U8 GetWaterHeaterPowerCurParameterValueMin(void)
{
	return _tWaterHeaterPowerData.CurParameterValueMin;
}
U8 GetWaterHeaterPowerCurParameterValueMax(void)
{
	return _tWaterHeaterPowerData.CurParameterValueMax;
}
U8 GetWaterHeaterPowerDebugSerialNumberMax(void)
{
	return _tWaterHeaterPowerData.DebugSerialNumberMax;
}

/* 调试项 */
void SetWaterHeaterDebugGoToNext(void)
{
	_tWaterHeaterDebugData.GoToNext = 1;
}
void ClearWaterHeaterDebugGoToNext(void)
{
	_tWaterHeaterDebugData.GoToNext = 0;
}
void SetWaterHeaterDebugGoToPre(void)
{
	_tWaterHeaterDebugData.GoToPre = 1;
}
void ClearWaterHeaterDebugGoToPre(void)
{
	_tWaterHeaterDebugData.GoToPre = 0;
}
void SetWaterHeaterDebugGoToSet(void)
{
	_tWaterHeaterDebugData.GoToSet = 1;
}
void ClearWaterHeaterDebugGoToSet(void)
{
	_tWaterHeaterDebugData.GoToSet = 0;
}
void SetWaterHeaterDebugCurValue(U8 Value)
{
	_tWaterHeaterDebugData.CurValue = Value;
}
void SetWaterHeaterDebugCurSerialNumber(U8 Number)
{
	_tWaterHeaterDebugData.CurSerialNumber = Number;
}
U8 GetWaterHeaterDebugGoToNext(void)
{
	return _tWaterHeaterDebugData.GoToNext;
}
U8 GetWaterHeaterDebugGoToPre(void)
{
	return _tWaterHeaterDebugData.GoToPre;
}
U8 GettWaterHeaterDebugGoToSet(void)
{
	return _tWaterHeaterDebugData.GoToSet;
}
U8 GetWaterHeaterDebugCurValue(void)
{
	return _tWaterHeaterDebugData.CurValue;
}
U8 GetWaterHeaterDebugCurSerialNumber(void)
{
	return _tWaterHeaterDebugData.CurSerialNumber;
}

void WaterHeaterDataInit(void)
{
	_tWaterHeaterDispData.TimerTimeValue = 0;
	_tWaterHeaterDispData.KitchenTempValue = MIN_WATER_TEMPERATURE;
	_tWaterHeaterDispData.KitchenWaterValue = 5;
	_tWaterHeaterDispData.BathroomTempValue = MIN_WATER_TEMPERATURE;
	_tWaterHeaterDispData.BathroomWaterValue = 5;
	_tWaterHeaterDispData.BathtubTempValue = MIN_WATER_TEMPERATURE;
	_tWaterHeaterDispData.BathtubWaterValue = 25;
	_tWaterHeaterDispData.EnergyTempValue = MIN_WATER_TEMPERATURE;
	_tWaterHeaterDispData.EnergyWaterValue = 5;
	_tWaterHeaterDispData.FunctionSelect = FUNC_BATHROOM;
	_tWaterHeaterDispData.Model = 12;
	_tWaterHeaterDispData.ValveMax = 128;
	_tWaterHeaterDispData.ValveMin = 64;
	_tWaterHeaterDispData.FireOnValue = 32;

	_tWaterHeaterPowerData.FireStatus = 0;
	_tWaterHeaterPowerData.OutTemperatureValue = 25;
	_tWaterHeaterPowerData.ErrorStatus = 0;

	GUI_strcpy((char *)_tWaterHeaterPowerData.ParameterCodeString, "123");
	GUI_strcpy((char *)_tWaterHeaterPowerData.ParameterValueString, "30");
}

