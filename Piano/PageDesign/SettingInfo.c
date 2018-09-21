/*
 * SettingInfo.c
 *
 *  Created on: 2018年9月20日
 *      Author: Administrator
 */


#include "SettingInfo.h"


typedef struct
{
	U8 StatusLight;
	U8 StatusWind;
	U8 StatusDelayClose;
}SettingStatus;


static SettingStatus _mSettingStatus;


void Setting_SetLightStatus(U8 Status)
{
	_mSettingStatus.StatusLight = Status;
}

void Setting_SetWindStatus(U8 Status)
{
	_mSettingStatus.StatusWind = Status;
}

void Setting_SetDelayCloseStatus(U8 Status)
{
	_mSettingStatus.StatusDelayClose = Status;
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
