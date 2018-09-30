/*
 * DialogWifiPassword.h
 *
 *  Created on: 2018年9月28日
 *      Author: Administrator
 */

#ifndef _DIALOGWIFIPASSWORD_H_
#define _DIALOGWIFIPASSWORD_H_

#include "GUI_main.h"

WM_HWIN PageWifiPasswordCreate(WM_HWIN hParent, const char *pSelectSSID, U8 Encry);
WM_HWIN PageWifiPasswordGetHander(void);

#endif /* _DIALOGWIFIPASSWORD_H_ */
