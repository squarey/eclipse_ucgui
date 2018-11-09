/*
 * SettingInfo.c
 *
 *  Created on: 2018年9月20日
 *      Author: Administrator
 */


#include "SettingInfo.h"
#include "HoodCom.h"


typedef struct
{
	U8 StatusLight;
	U8 StatusWind;
	U8 StatusDelayClose;
	U16 DelayCloseCnt;
	U8 StatusTimingAir;
	U32 TimingAirCnt;
	U8 TimingAirTimeHours;
	U8 TimingAirTimeMinutes;
	U8 StatusCookerTimer;
	U8 StatusCookerTimerLeft;
	U8 StatusCookerTimerRight;
	U16 CookerTimerLeftCnt;
	U16 CookerTimerRightCnt;
}SettingStatus;


static SettingStatus _mSettingStatus;


void Setting_SetLightStatus(U8 Status)
{
	_mSettingStatus.StatusLight = Status;
	HoodCom_SetLightStatus(Status, 100);
}

void Setting_SetWindStatus(U8 Status)
{
	_mSettingStatus.StatusWind = Status;
	if(WIND_NONE == Status){
		HoodCom_SetTurnSpeed(0);
	}else if(WIND_SMALL == Status){
		HoodCom_SetTurnSpeed(8);
	}else if(WIND_MIDDLE == Status){
		HoodCom_SetTurnSpeed(14);
	}else{
		HoodCom_SetTurnSpeed(20);
	}
}

void Setting_SetDelayCloseStatus(U8 Status)
{
	_mSettingStatus.StatusDelayClose = Status;
}
void Setting_SetDelayCloseCnt(U16 Cnt)
{
	_mSettingStatus.DelayCloseCnt = Cnt;
}
void Setting_SetTimingAirStatus(U8 Status)
{
	_mSettingStatus.StatusTimingAir = Status;
}
void Setting_SetTimingAirCnt(U32 Cnt)
{
	_mSettingStatus.TimingAirCnt = Cnt;
}
void Setting_SetTimingAirTime(U8 Hours, U8 Minutes)
{
	_mSettingStatus.TimingAirTimeHours = Hours;
	_mSettingStatus.TimingAirTimeMinutes = Minutes;
}
void Setting_SetCookerTimerStatus(U8 Status)
{
	_mSettingStatus.StatusCookerTimer = Status;
	if(COOKER_TIMER_CLOSE == Status){
		_mSettingStatus.StatusCookerTimerLeft = COOKER_TIMER_CLOSE;
		_mSettingStatus.StatusCookerTimerRight = COOKER_TIMER_CLOSE;
	}
}
void Setting_SetCookerTimerLeftStatus(U8 Status)
{
	_mSettingStatus.StatusCookerTimerLeft = Status;
}
void Setting_SetCookerTimerRightStatus(U8 Status)
{
	_mSettingStatus.StatusCookerTimerRight = Status;
}
void Setting_SetCookerTimerLeftCnt(U16 Cnt)
{
	_mSettingStatus.CookerTimerLeftCnt = Cnt;
}
void Setting_SetCookerTimerRightCnt(U16 Cnt)
{
	_mSettingStatus.CookerTimerRightCnt = Cnt;
}

void Setting_SetCloseAllFunc(void)
{
	_mSettingStatus.StatusLight = LIGHT_CLOSE;
	_mSettingStatus.StatusDelayClose = DELAY_CLOSE;
	_mSettingStatus.StatusCookerTimerLeft = COOKER_TIMER_CLOSE;
	_mSettingStatus.StatusCookerTimerRight = COOKER_TIMER_CLOSE;
	_mSettingStatus.StatusWind = WIND_NONE;
	HoodCom_SetLightStatus(0, 100);
	HoodCom_SetTurnSpeed(0);
}


U8 Setting_GetLightStatus(void)
{
	return _mSettingStatus.StatusLight;
}

U8 Setting_GetWindStatus(void)
{
	return _mSettingStatus.StatusWind;
}

U8 Setting_GetDelayCloseStatus(void)
{
	return _mSettingStatus.StatusDelayClose;
}
U16 Setting_GetDelayCloseCnt(void)
{
	return _mSettingStatus.DelayCloseCnt;
}
U8 Setting_GetTimingAirStatus(void)
{
	return _mSettingStatus.StatusTimingAir;
}
U32 Setting_GetTimingAirCnt(void)
{
	return _mSettingStatus.TimingAirCnt;
}
void Setting_GetTimingAirTime(U8 *pHours, U8 *pMinutes)
{
	*pHours = _mSettingStatus.TimingAirTimeHours;
	*pMinutes = _mSettingStatus.TimingAirTimeMinutes;
}
U8 Setting_GetCookerTimerStatus(void)
{
	return _mSettingStatus.StatusCookerTimer;
}
U8 Setting_GetCookerTimerLeftStatus(void)
{
	return _mSettingStatus.StatusCookerTimerLeft;
}
U8 Setting_GetCookerTimerRightStatus(void)
{
	return _mSettingStatus.StatusCookerTimerRight;
}
U16 Setting_GetCookerTimerLeftCnt(void)
{
	return _mSettingStatus.CookerTimerLeftCnt;
}
U16 Setting_GetCookerTimerRightCnt(void)
{
	return _mSettingStatus.CookerTimerRightCnt;
}
