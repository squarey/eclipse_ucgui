/*
 * HoodCom.h
 *
 *  Created on: 2018年9月25日
 *      Author: Administrator
 */

#ifndef _HOODCOM_H_
#define _HOODCOM_H_


#include "GUI.h"

//电控板通信初始化
void HoodComInit(void);
//设置风机档位 范围0-28   0表示风机停止
void HoodCom_SetTurnSpeed(U8 Speed);
//设置灯状态  IsOpen: 0 灯光关闭  1:灯光开启    Value: 灯的亮度值  范围0-100
//只有当IsOpen为1  且 Value不为0时灯才会亮
void HoodCom_SetLightStatus(U8 IsOpen, U8 Value);
//设置清洗的状态   IsStartClen: 1 开启清洗   0关闭清洗
//每次开启清洗时需传入当前的温度值
void HoodCom_SetCleanStatus(U8 IsStartClen, U8 Temperature);
//发送按键声
void HoodCom_SendTouchVoice(void);
//发送开机声
void HoodCom_SendOpenVoice(void);
void HoodCom_SendCloseVoice(void);
//获取当前的转速
U8 HoodCom_GetTurnSpeed(void);
//获取当前灯的状态
U8 HoodCom_GetLightStatus(void);
//获取当前灯的亮度值
U8 HoodCom_GetLightValue(void);
//获取清洗时的清洗温度
U8 HoodCom_GetCleanTemperature(void);
//获取清洗倒计时的时间   单位:秒
//当返回0值时  表示此次清洗已经结束
U8 HoodCom_GetCleanTimeCnt(void);
//获取电控板返回的实时转速
U32 HoodCom_GetRealTimeSpeed(void);
//获取清洗时发生的错误状态  无错误返回 ERROR_NONE
U8 HoodCom_GetCleanErrorStatus(void);
//错误状态  无错误返回 ERROR_NONE
U8 HoodCom_GetBoardWarnStatus(void);
//获取电控板返回的面板开到位状态 返回1 即表示开到位
U8 HoodCom_GetPlateUpComfirm(void);
//获取电控板返回的面板关到位状态  返回1 即表示关到位
U8 HoodCom_GetPlateDownComfirm(void);
//获取强制面板开到位状态 返回1 即表示开到位
U8 HoodCom_GetPlateUpFocusComfirm(void);
//获取强制面板关到位状态  返回1 即表示关到位
U8 HoodCom_GetPlateDownFocusComfirm(void);
#endif /* _HOODCOM_H_ */
