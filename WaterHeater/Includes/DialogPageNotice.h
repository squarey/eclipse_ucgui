/*
 * DialogPageNotice.h
 *
 *  Created on: 2018年6月19日
 *      Author: Administrator
 */

#ifndef DIALOGPAGENOTICE_H_
#define DIALOGPAGENOTICE_H_

#include "GUI.h"

#define ERROR_FIRE						1
#define ERROR_TEMP_CONTROL_OPEN			2
#define ERROR_FIRE_ON					3
#define ERROR_TEMP_CONTROL_SHORT		4
#define ERROR_TIMER_END					5
#define ERROR_PASSWORD					6
#define ERROR_FAN_SWITCH				7
#define ERROR_WATER						8
#define ERROR_COMMUNICATION				9
#define ERROR_FIRE_ACCIDENT				10




void DialgPageNoticeCreate(U8 ViewIndex);
#endif /* DIALOGPAGENOTICE_H_ */
