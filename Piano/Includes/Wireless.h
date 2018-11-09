/*
 * WifiScanTest.h
 *
 *  Created on: 2018年9月28日
 *      Author: Administrator
 */

#ifndef _WIRELESS_H_
#define _WIRELESS_H_

#include "GUI_main.h"

#define ENCRYPTION_WPA		0x01
#define ENCRYPTION_WEP		0x02
#define ENCRYPTION_OPEN		0x04

#define WIFI_FUNC_OPEN		1
#define WIFI_FUNC_CLOSE		2

#define WIFI_DISCONNECTED	1
#define WIFI_CONNECTED		2

typedef struct
{
	char MacAddress[18];	//AP的MAC地址
	char SSID[64];			//AP的SSID
	I32 SignalLevel;		//AP的信号强度
	U8 Encry;				//AP的加密方式
}APInfo;

typedef U8(* APScanResultCallback)(const APInfo *);

int StartScanWifiList(void);
void WirelessInit(void);
void SetWifiScanResultCallback(void *pFunc);
int StartConnectToAp(const char *pSSID, const char *pPassword, int iEncryptionFlag);
const char* GetWifiConnectedSSID(void);
unsigned char GetWifiConnectStatus(void);
void ReverseWifiConnectStatus(void);
void SetWifiFunctionStatus(unsigned char Status);
unsigned char GetWifiFunctionStatus(void);

/***********************************************************/

#define BLUETOOTH_FUNC_OPEN		1
#define BLUETOOTH_FUNC_CLOSE	0

#define BLUETOOTH_CONNECTED		1
#define BLUETOOTH_DISCONNECTED	2
typedef struct
{
	char MacAddress[18];	//Ble的MAC地址
	char Name[64];			//Ble的名称
}BleInfo;

typedef U8(* BleScanResultCallback)(const BleInfo *);

unsigned char GetBluetoothFunctionStatus(void);
void SetBluetoothFunctionStatus(unsigned char Status);
void SetBleScanResultCallback(void *pFunc);
void SetBleStartScan(void);
void BluetoothStartToConnect(const char *pName, const char *pMac);
I32 BluetoothGetConnectInfo(char *pName, char *pMac);
U8 BluetoothGetConnectStauts(void);

#endif /* _WIRELESS_H_ */
