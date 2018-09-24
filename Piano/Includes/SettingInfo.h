/*
 * SettingInfo.h
 *
 *  Created on: 2018年9月20日
 *      Author: Administrator
 */

#ifndef _SETTINGINFO_H_
#define _SETTINGINFO_H_

#include "GUI.h"


#define 		LIGHT_OPEN		1
#define 		LIGHT_CLOSE		0

#define 		DELAY_START		2
#define 		DELAY_OPEN		1
#define 		DELAY_CLOSE		0
#define 		TIMING_AIR_START	2
#define 		TIMING_AIR_OPEN		1
#define 		TIMING_AIR_CLOSE	0
#define 		COOKER_TIMER_START	2
#define 		COOKER_TIMER_OPEN	1
#define 		COOKER_TIMER_CLOSE	0

#define 		WIND_NONE		0
#define 		WIND_SMALL		1
#define 		WIND_MIDDLE		2
#define 		WIND_LARGE		3


void Setting_SetLightStatus(U8 Status);
void Setting_SetWindStatus(U8 Status);
void Setting_SetDelayCloseStatus(U8 Status);
void Setting_SetDelayCloseCnt(U16 Cnt);
void Setting_SetTimingAirStatus(U8 Status);
void Setting_SetTimingAirCnt(U32 Cnt);
void Setting_SetTimingAirTime(U8 Hours, U8 Minutes);
void Setting_SetCookerTimerStatus(U8 Status);
void Setting_SetCookerTimerLeftStatus(U8 Status);
void Setting_SetCookerTimerRightStatus(U8 Status);
void Setting_SetCookerTimerLeftCnt(U16 Cnt);
void Setting_SetCookerTimerRightCnt(U16 Cnt);

U8 Setting_GetLightStatus(void);
U8 Setting_GetWindStatus(void);
U8 Setting_GetDelayCloseStatus(void);
U16 Setting_GetDelayCloseCnt(void);
U8 Setting_GetTimingAirStatus(void);
U32 Setting_GetTimingAirCnt(void);
void Setting_GetTimingAirTime(U8 *pHours, U8 *pMinutes);
U8 Setting_GetCookerTimerStatus(void);
U8 Setting_GetCookerTimerLeftStatus(void);
U8 Setting_GetCookerTimerRightStatus(void);
U16 Setting_GetCookerTimerLeftCnt(void);
U16 Setting_GetCookerTimerRightCnt(void);

#endif /* _SETTINGINFO_H_ */
