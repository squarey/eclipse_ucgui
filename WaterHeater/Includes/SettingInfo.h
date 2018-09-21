/*
 * SettingInfo.h
 *
 *  Created on: 2018年5月15日
 *      Author: Administrator
 */

#ifndef __SETTINGINFO_H_
#define __SETTINGINFO_H_

#include <GUI_main.h>

#define MAX_WATER_TEMPERATURE	65
#define MIN_WATER_TEMPERATURE	36

typedef enum
{
	FUNC_KITCHEN = 0x01,
	FUNC_BATHROOM,
	FUNC_BATHTUB,
	FUNC_ENERGY,
}FUNC_SELECT;

#define FUNC_KITCHEN 	0x01
#define FUNC_BATHROOM 	0x02
#define FUNC_BATHTUB 	0x04
#define FUNC_ENERGY 	0x08

#define DEBUG_MODE_NONE					0
#define DEBUG_MODE_NEED_TO_ENTER		1
#define DEBUG_MODE_IS_IN				2
#define DEBUG_MODE_EXIT_NOT_SAVE		3
#define DEBUG_MODE_EXIT_SAVE			4

void WaterHeaterDataInit(void);

void SetTimerTimeValue(U8 Value);
void SetKitchenTempValue(U8 Value);
void SetKitchenWaterValue(U8 Value);
void SetBathroomTempValue(U8 Value);
void SetBathroomWaterValue(U8 Value);
void SetBathtubTempValue(U8 Value);
void SetBathtubWaterValue(U8 Value);
void SetEnergyTempValue(U8 Value);
void SetEnergyWaterValue(U8 Value);
void SetWaterHeaterFuncSelect(U8 Func);
void SetWaterHeaterModel(U8 Model);
void SetWaterHeaterValveMaxValue(U8 Value);
void SetWaterHeaterValveMinValue(U8 Value);
void SetWaterHeaterFireOnValue(U8 Value);

void SetWaterHeaterEnterDebugMode(void);
void SetWaterHeaterSaveExitDebugMode(void);
void SetWaterHeaterExitDebugMode(void);
void SetWaterHeaterIsInDebugMode(void);
void SetWaterHeaterIsExitDebugMode(void);

U8 GetTimerTimeValue(void);
U8 GetKitchenTempValue(void);
U8 GetKitchenWaterValue(void);
U8 GetBathroomTempValue(void);
U8 GetBathroomWaterValue(void);
U8 GetBathtubTempValue(void);
U8 GetBathtubWaterValue(void);
U8 GetEnergyTempValue(void);
U8 GetEnergyWaterValue(void);
U8 GetWaterHeaterFuncSelect(void);
U8 GetWaterHeaterModel(void);
U8 GetWaterHeaterValveMaxValue(void);
U8 GetWaterHeaterValveMinValue(void);
U8 GetWaterHeaterFireOnValue(void);
U8 GetWaterHeaterDebugMode(void);

void SetWaterHeaterPowerFire(U8 Status);
void SetWaterHeaterPowerOutTemperature(U8 Temperature);
void SetWaterHeaterPowerErrorStatus(U8 Status);
void SetWaterHeaterPowerFanRun(U8 Status);
void SetWaterHeaterPowerShowerWater(U8 Status);
void SetWaterHeaterPowerFaultExist(U8 Status);
void SetWaterHeaterPowerBathtubWaterOut(U8 Status);
void SetWaterHeaterPowerWorkMode(U8 Mode);
void SetWaterHeaterPowerDebugMode(U8 Mode);
void SetWaterHeaterPowerMachineMode(U8 Mode);
void SetWaterHeaterPowerWorkTime(U16 Time);
void SetWaterHeaterPowerTimerTimes(U8 Time);
void SetWaterHeaterPowerWaterFlow(U8 Value);
void SetWaterHeaterPowerInTemperatureValue(U8 Value);
void SetWaterHeaterPowerFanSpeed(U8 Speed);
void SetWaterHeaterPowerLoadOutput(U8 Value);
void SetWaterHeaterPowerWaterUsed(U16 Value);
void SetWaterHeaterPowerTurnOnWaterValue(U8 Value);
void SetWaterHeaterPowerWaterValveAdjustValue(U8 Value);
void SetWaterHeaterPowerTemperatureMinValue(U8 Value);
void SetWaterHeaterPowerTemperatureMaxValue(U8 Value);
void SetWaterHeaterPowerCommunicationVersion(U8 Value);
void SetWaterHeaterPowerProgramVersion(U8 Value);
void SetWaterHeaterPowerDebugSerialNumber(U8 Value);
void SetWaterHeaterPowerDisplayMode(U8 Value);
void SetWaterHeaterPowerParameterCodeString(const U8 *pString);
void SetWaterHeaterPowerParameterValue(U8 Value);
void SetWaterHeaterPowerParameterValueString(const U8 *pString);
void SetWaterHeaterPowerCurParameterValueMin(U8 Value);
void SetWaterHeaterPowerCurParameterValueMax(U8 Value);
void SetWaterHeaterPowerDebugSerialNumberMax(U8 Value);

U8 GetWaterHeaterPowerFire(void);
U8 GetWaterHeaterPowerOutTemperature(void);
U8 GetWaterHeaterPowerErrorStatus(void);
U8 GetWaterHeaterPowerFanRun(void);
U8 GetWaterHeaterPowerShowerWater(void);
U8 GetWaterHeaterPowerFaultExist(void);
U8 GetWaterHeaterPowerBathtubWaterOut(void);
U8 GetWaterHeaterPowerWorkMode(void);
U8 GetWaterHeaterPowerDebugMode(void);
U8 GetWaterHeaterPowerMachineMode(void);

U16 GetWaterHeaterPowerWorkTime(void);
U8 GetWaterHeaterPowerTimerTimes(void);
U8 GetWaterHeaterPowerWaterFlow(void);
U8 GetWaterHeaterPowerInTemperatureValue(void);
U8 GetWaterHeaterPowerFanSpeed(void);
U8 GetWaterHeaterPowerLoadOutput(void);
U16 GetWaterHeaterPowerWaterUsed(void);
U8 GetWaterHeaterPowerTurnOnWaterValue(void);
U8 GetWaterHeaterPowerWaterValveAdjustValue(void);
U8 GetWaterHeaterPowerTemperatureMinValue(void);
U8 GetWaterHeaterPowerTemperatureMaxValue(void);
U8 GetWaterHeaterPowerCommunicationVersion(void);
U8 GetWaterHeaterPowerProgramVersion(void);
U8 GetWaterHeaterPowerDebugSerialNumber(void);
U8 GetWaterHeaterPowerDisplayMode(void);
void GetWaterHeaterPowerParameterCodeString(U8 *pString);
U8 GetWaterHeaterPowerParameterValue(void);
void GetWaterHeaterPowerParameterValueString(U8 *pString);
U8 GetWaterHeaterPowerCurParameterValueMin(void);
U8 GetWaterHeaterPowerCurParameterValueMax(void);
U8 GetWaterHeaterPowerDebugSerialNumberMax(void);

void SetWaterHeaterDebugGoToNext(void);
void ClearWaterHeaterDebugGoToNext(void);
void SetWaterHeaterDebugGoToPre(void);
void ClearWaterHeaterDebugGoToPre(void);
void SetWaterHeaterDebugGoToSet(void);
void ClearWaterHeaterDebugGoToSet(void);
void SetWaterHeaterDebugCurValue(U8 Value);
void SetWaterHeaterDebugCurSerialNumber(U8 Number);
U8 GetWaterHeaterDebugGoToNext(void);
U8 GetWaterHeaterDebugGoToPre(void);
U8 GettWaterHeaterDebugGoToSet(void);
U8 GetWaterHeaterDebugCurValue(void);
U8 GetWaterHeaterDebugCurSerialNumber(void);


#endif /* SETTINGINFO_H_ */



