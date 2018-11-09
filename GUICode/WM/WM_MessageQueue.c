/*
 * WM_MessageQueue.c
 *
 *  Created on: 2018年9月29日
 *      Author: Administrator
 */

#ifndef _WM_MESSAGEQUEUE_C_
#define _WM_MESSAGEQUEUE_C_



#include "WM.h"
#include "GUI_Protected.h"

typedef struct _MESSAGEQUEUE
{
	I32 QueueId;
	I32 Value;
	WM_HWIN hWin;
	WM_HMEM hData;
	WM_HMEM hNext;
}WM_MESSAGEQUEUE;

static WM_HMEM hFirstMessageQueue = WM_HMEM_NULL;
static U8 _QueueLock = 0;

static void _AddMessageToQueue(WM_MESSAGEQUEUE *pQueue, WM_QUEUE_PARA *pPara)
{
	void *tpData;
	pQueue->Value = pPara->Value;
	pQueue->hWin = pPara->hWin;
	pQueue->QueueId = pPara->QueueId;
	if(pPara->DataLen){
		pQueue->hData = GUI_ALLOC_AllocZero(pPara->DataLen);
		tpData = (void *)GUI_ALLOC_h2p(pQueue->hData);
		GUI_memcpy(tpData, pPara->pData, pPara->DataLen);
	}else{
		pQueue->hData = WM_HMEM_NULL;
	}
	pQueue->hNext = WM_HMEM_NULL;
}
//加入一个消息到消息队列中
void WM_PostMessageToQueue(WM_QUEUE_PARA *pPara)
{
	WM_MESSAGEQUEUE *pQueue, *pNext;
	WM_HMEM hNext, hQueue;
	_QueueLock = 1;
	if(WM_HMEM_NULL == hFirstMessageQueue){
		hQueue = GUI_ALLOC_AllocZero(sizeof(WM_MESSAGEQUEUE));
		if(hQueue){
			pQueue = (WM_MESSAGEQUEUE *)GUI_ALLOC_h2p(hQueue);
		}
		_AddMessageToQueue(pQueue, pPara);
		hFirstMessageQueue = hQueue;
		_QueueLock = 0;
		return;
	}
	pNext = (WM_MESSAGEQUEUE *)GUI_ALLOC_h2p(hFirstMessageQueue);
	hNext = pNext->hNext;
	while(WM_HMEM_NULL != hNext){
		pNext = (WM_MESSAGEQUEUE *)GUI_ALLOC_h2p(pNext->hNext);
		hNext = pNext->hNext;
	}
	hQueue = GUI_ALLOC_AllocZero(sizeof(WM_MESSAGEQUEUE));
	if(hQueue){
		pQueue = (WM_MESSAGEQUEUE *)GUI_ALLOC_h2p(hQueue);
		_AddMessageToQueue(pQueue, pPara);
		pNext->hNext = hQueue;
	}
	_QueueLock = 0;
}
//将消息队列中的消息派发出去
void WM_DistributionMessageFromQueue(void)
{
	if(_QueueLock){
		return;
	}else{
		WM_HMEM hNext;
		WM_MESSAGEQUEUE *pQueue;
		WM_MESSAGE Msg;
		while(hFirstMessageQueue){
			pQueue = (WM_MESSAGEQUEUE *)GUI_ALLOC_h2p(hFirstMessageQueue);
			Msg.MsgId = pQueue->QueueId;
			Msg.hWin = pQueue->hWin;
			Msg.Data.v = pQueue->Value;
			if(pQueue->hData){
				Msg.Data.p = (void *)GUI_ALLOC_h2p(pQueue->hData);
			}else{
				Msg.Data.p = NULL;
			}
			hNext = pQueue->hNext;
			WM_SendMessage(Msg.hWin, &Msg);
			if(pQueue->hData){
				GUI_ALLOC_Free(pQueue->hData);
			}
			GUI_ALLOC_Free(hFirstMessageQueue);
			hFirstMessageQueue = hNext;
		}
	}
}
#endif /* _WM_MESSAGEQUEUE_C_ */
