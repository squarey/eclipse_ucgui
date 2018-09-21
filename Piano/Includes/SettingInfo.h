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

#define 		DELAY_OPEN		1
#define 		DELAY_CLOSE		0

#define 		WIND_NONE		0
#define 		WIND_SMALL		1
#define 		WIND_MIDDLE		2
#define 		WIND_LARGE		3


void Setting_SetLightStatus(U8 Status);
void Setting_SetWindStatus(U8 Status);
void Setting_SetDelayCloseStatus(U8 Status);
U8 Setting_GetLightStatus(void);
U8 Setting_GetWindStatus(void);
U8 Setting_GetDelayCloseStatus(void);

#endif /* _SETTINGINFO_H_ */
