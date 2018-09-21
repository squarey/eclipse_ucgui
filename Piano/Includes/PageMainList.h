/*
 * PageMainList.h
 *
 *  Created on: 2018年9月19日
 *      Author: Administrator
 */

#ifndef _PAGEMAINLIST_H_
#define _PAGEMAINLIST_H_

#include "GUI_main.h"

#define PAGE_MAIN		"page main"
#define PAGE_SET		"page set"

WM_HWIN PageListCreate(void);
void PageListShowWinByName(const char *pWinName);

#endif /* _PAGEMAINLIST_H_ */
