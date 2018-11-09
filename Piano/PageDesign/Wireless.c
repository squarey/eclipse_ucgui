/*
 * WifiScanTest.c
 *
 *  Created on: 2018年9月28日
 *      Author: Administrator
 */

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include "Wireless.h"

static char _WifiScanResult[] = "bssid / frequency / signal level / flags / ssid\r\n \
	0e:9b:4b:98:2b:59       2447    -50     [WPA-PSK-CCMP][WPA2-PSK-CCMP][ESS]      ZY-AP30\r\n \
	8c:a6:df:5c:4c:39       2437    -51     [WPA-PSK-CCMP][WPA2-PSK-CCMP][ESS]      secomid\r\n \
	b0:6e:bf:6d:49:98       2417    -66     [WPA2-PSK-CCMP][ESS]    ASUS\r\n \
	b0:6e:bf:6d:49:99       2417    -66     [WPA2-PSK-CCMP][ESS]    ASUS_Guest1\r\n \
	50:bd:5f:31:3d:fa       2437    -73     [WPA-PSK-CCMP][WPA2-PSK-CCMP][ESS]      TP-LINK_3DFA\r\n \
	d8:ae:90:0c:b3:05       2462    -77     [WPA-PSK-TKIP+CCMP][WPA2-PSK-TKIP+CCMP][ESS]    ChinaNet-11f6\r\n" ;
	//d8:ae:90:0c:b3:05       2462    -77     [WPA-PSK-TKIP+CCMP][WPA2-PSK-TKIP+CCMP][ESS]    Test\r\n";

static char _WifiScanResult1[] = "bssid / frequency / signal level / flags / ssid\r\n \
	0e:9b:4b:98:2b:59       2447    -50     [WPA-PSK-CCMP][WPA2-PSK-CCMP][ESS]     secomid\r\n \
	8c:a6:df:5c:4c:39       2437    -51     [WPA-PSK-CCMP][WPA2-PSK-CCMP][ESS]     ZY-AP30\r\n \
	b0:6e:bf:6d:49:98       2417    -66     [WPA2-PSK-CCMP][ESS]    ASUS_Guest1\r\n \
	b0:6e:bf:6d:49:99       2417    -66     [WPA2-PSK-CCMP][ESS]    ASUS\r\n \
	50:bd:5f:31:3d:fa       2437    -73     [WPA-PSK-CCMP][WPA2-PSK-CCMP][ESS]      Test\r\n \
	d8:ae:90:0c:b3:05       2462    -77     [WPA-PSK-TKIP+CCMP][WPA2-PSK-TKIP+CCMP][ESS]    ChinaNet-11f6\r\n \
	d8:ae:90:0c:b3:05       2462    -77     [WPA-PSK-TKIP+CCMP][WPA2-PSK-TKIP+CCMP][ESS]    TP-LINK_3DFA\r\n";

static char _BleScanResult[] = "tMod\r\n12:34:56:78:90:aa\r\ntMod\r\naa:bb:cc:dd:ee:ff\r\n";

static U8 WpaCliStatus = 0;
static U8 Inited = 0;

#define STATUS_NONE					0
#define STATUS_TO_CONNECT_AP		0x01
#define STATUS_TO_SCAN_AP			0x02
#define STATUS_TO_CONNECT_LAST		0x04

static U32 _ScanTimeCnt = 0;
static U8 _ResultFlag = 0;
static U8 _WifiFunctionStatus = WIFI_FUNC_CLOSE;
static U8 _CurConnectStatus = WIFI_DISCONNECTED;
static char _ConnectSSID[64] = "secomid";
/********************************************************/
static U8 _BluetoothStatus = 0;
static U8 _BluetoothScanCnt = 0;
static U8 _BluetoothConnectStatus = 0;
static unsigned char _BluetoothFunctionStatus = BLUETOOTH_FUNC_CLOSE;
static BleScanResultCallback pBleScanResult_cb = NULL;
/*******************************************************/
static APScanResultCallback pScanResult_cb = NULL;
int StartScanWifiList(void)
{
	WpaCliStatus |= STATUS_TO_SCAN_AP;
	_ResultFlag++;
	GUI_Debug("_ResultFlag:%d\n", _ResultFlag);
	return 0;
}
int StartConnectToAp(const char *pSSID, const char *pPassword, int iEncryptionFlag)
{
	GUI_Debug("pSSID:%s\n", pSSID);
	GUI_Debug("pPassword:%s\n", pPassword);
	GUI_Debug("iEncryptionFlag:%x\n", iEncryptionFlag);
	return 0;
}
void SetWifiScanResultCallback(void *pFunc)
{
	pScanResult_cb = (APScanResultCallback)pFunc;
}

const char* GetWifiConnectedSSID(void)
{
	return _ConnectSSID;
}
unsigned char GetWifiConnectStatus(void)
{
	return _CurConnectStatus;
}
void ReverseWifiConnectStatus(void)
{
	if(WIFI_DISCONNECTED == _CurConnectStatus){
		_CurConnectStatus = WIFI_CONNECTED;
	}else{
		_CurConnectStatus = WIFI_DISCONNECTED;
	}
}
void SetWifiFunctionStatus(unsigned char Status)
{
	_WifiFunctionStatus = Status;
}
unsigned char GetWifiFunctionStatus(void)
{
	return _WifiFunctionStatus;
}

static int get_line_from_buf(int index, char *pLine, char *buf)
{
    int i = 0;
    int j;
    int endcnt = -1;
    char *linestart = buf;
    int len;
    char *tpLine = pLine;

    while (1){
        if (buf[i] == '\n' || buf[i] == '\r' || buf[i] == '\0'){
            endcnt++;
            if (index == endcnt){
                len = &buf[i] - linestart;
                strncpy(tpLine, linestart, len);
                tpLine[len] = '\0';
                return 0;
            }else{
                /* 更新linestart */
                for (j = i + 1; buf[j]; ){
                    if (buf[j] == '\n' || buf[j] == '\r'){
                    	j++;
                    }else{
                    	break;
                    }
                }
                if (!buf[j]){
                	return -1;
                }
                linestart = &buf[j];
                i = j;
            }
        }

        if (!buf[i]){
        	return -1;
        }
        i++;
    }
}
void TransChar(const char *pSrcString, char *pDesString)
{
	char pTransBuffer[128] = "";
	char Temp[5] = "";
	U32 pTransLen = 0;
	U32 Len = 0;
	U8 i = 0;
	I32 Value = 0;
	const char *pString_t1 = pSrcString;
	const char *pString_t2;
	if((NULL == pSrcString) || (NULL == pDesString)){
		return;
	}
	//WPA_Debug("pSrcString:%s\n", pSrcString);
	if(strlen(pString_t1) > 128){
		//WPA_Debug("Error: Trans string is too long, max len is 128\n");
		return;
	}
	/* "123\\xe6\\xb5\\x8babc\\xe8\\xaf\\x95qaz" */
	pString_t2 = strstr(pString_t1, "\\x");
	if(pString_t2){
		pTransLen = pString_t2 - pString_t1;
		if((pTransLen) > 0){
			strncpy(pTransBuffer, pString_t1, pTransLen);
		}
	}else{
		strcpy(pDesString, pString_t1);
		return;
	}

	while(pString_t2){
		if(strlen(pString_t2) >= 12){

		}else{
			Len = strlen(pString_t2);
			//WPA_Debug("pString_t2:%s\n", pString_t2);
			strncpy(&pTransBuffer[pTransLen], pString_t2, Len);
			pTransLen += Len;
			break;
		}
		if((pString_t2[0] == '\\') && (pString_t2[4] == '\\') && (pString_t2[8] == '\\')){
			//WPA_Debug("need to trans\n");
			for(i = 0; i < 3; i++){
				strncpy(Temp, &pString_t2[0 + i * 4], 4);
				Temp[0] = '0';
				Temp[4] = '\0';
				//WPA_Debug("Temp:%s\n", Temp);
				sscanf(Temp, "%x", &Value);
				pTransBuffer[pTransLen] = Value;
				pTransLen++;
				//WPA_Debug("Value:%02x\n", Value);
			}
			pString_t2 += 12;
			//WPA_Debug("Buffer:%s\n", Buffer);
		}else{
			pString_t1 = pString_t2;
			pString_t2 = strstr(pString_t1 + 1, "\\x");
			//WPA_Debug("pTransLen:%d\n", pTransLen);
			if(pString_t2){
				Len = pString_t2 - pString_t1;
				strncpy(&pTransBuffer[pTransLen], pString_t1, Len);
				pTransLen += Len;
			}else{
				Len = strlen(pString_t1);
				strncpy(&pTransBuffer[pTransLen], pString_t1, Len);
				pTransLen += Len;
			}
		}
	}
	pTransBuffer[pTransLen] = '\0';
	strcpy(pDesString, pTransBuffer);
}
static void _GetOneInfoFromResult(void)
{
	char Mac[18];
	char Freq[10];
	char Signal[10];
	char Flags[64];
	char SSID[64];
	char tSSID[64];
	char Line[1024];
	unsigned int i = 0;
	char *pResult;
	if(_ResultFlag & 1){
		pResult = _WifiScanResult;
	}else{
		pResult = _WifiScanResult1;
	}
	for (i = 1; !get_line_from_buf(i, Line, pResult); i++){
		APInfo Info = {0};
		memset(SSID, 0, 64);
		sscanf(Line, "%s %s %s %s %s", Mac, Freq, Signal, Flags, SSID);
		if(strlen(SSID) < 4){
			continue;
		}
		TransChar(SSID, tSSID);
		strcpy(&Info.MacAddress[0], Mac);
		strcpy(&Info.SSID[0], tSSID);
		Info.SignalLevel = atoi(Signal);
		if(strstr(Flags, "WPA")){
			Info.Encry |= ENCRYPTION_WPA;
		}else if(strstr(Flags, "WEP")){
			Info.Encry |= ENCRYPTION_WEP;
		}else if(strstr(Flags, "OPEN")){
			Info.Encry |= ENCRYPTION_OPEN;
		}
		if(pScanResult_cb){
			pScanResult_cb(&Info);
		}
	}
}
static void _GetOneBleInfoFromResult(void)
{
	BleInfo Info = {0};
	unsigned int i = 0, j = 0;
	char Line[1024];
	for (i = 0; !get_line_from_buf(i, Line, _BleScanResult); i++){
		j++;
		if(1 == j){
			strcpy(&Info.Name[0], Line);
		}else if(2 == j){
			strcpy(&Info.MacAddress[0], Line);
			j = 0;
			if(pBleScanResult_cb){
				pBleScanResult_cb(&Info);
			}
		}
	}
}
static void *_WifiScanProcess(void *ptr)
{
	while(1){
		sleep(1);
		if(WpaCliStatus & STATUS_TO_SCAN_AP){
			_ScanTimeCnt++;
		}
		if(_ScanTimeCnt >= 1){
			_ScanTimeCnt = 0;
			WpaCliStatus &= ~STATUS_TO_SCAN_AP;
			_GetOneInfoFromResult();
		}
		if(1 == _BluetoothStatus){
			_BluetoothScanCnt++;
		}else if(2 == _BluetoothStatus){
			_BluetoothScanCnt++;
		}
		if(_BluetoothScanCnt >= 2){
			if(1 == _BluetoothStatus){
				_GetOneBleInfoFromResult();
			}else if(2 == _BluetoothStatus){
				_BluetoothConnectStatus = BLUETOOTH_CONNECTED;
			}
			_BluetoothStatus = 0;
			_BluetoothScanCnt = 0;
		}
//		StdinDevInit();
	}
	return 0;
}



void WirelessInit(void)
{
	if(0 == Inited){
		int Err;
		pthread_t ThreadID;
		Err = pthread_create(&ThreadID, NULL, _WifiScanProcess, NULL);
		if(0 != Err){
			GUI_Debug("creat thread fail\n");
			return;
		}
		pthread_detach(ThreadID);
		GUI_Debug("Thread create successful\n");
		Inited = 1;
		GUI_Debug("_WifiScanResult len %d\n", GUI_strlen(_WifiScanResult));
	}

}

/*********************************************/

static char DestBleName[64] = {0};
static char DestBleMac[18] = {0};

unsigned char GetBluetoothFunctionStatus(void)
{
	return _BluetoothFunctionStatus;
}
void SetBluetoothFunctionStatus(unsigned char Status)
{
	_BluetoothFunctionStatus = Status;
}

void SetBleScanResultCallback(void *pFunc)
{
	pBleScanResult_cb = (BleScanResultCallback)pFunc;
}

void SetBleStartScan(void)
{
	_BluetoothStatus = 1;
}

void BluetoothStartToConnect(const char *pName, const char *pMac)
{
	GUI_Debug("pName:%s, pMac:%s\n", pName, pMac);
	strcpy(DestBleName, pName);
	strcpy(DestBleMac, pMac);
	_BluetoothStatus = 2;
}

I32 BluetoothGetConnectInfo(char *pName, char *pMac)
{
	if(BLUETOOTH_CONNECTED == _BluetoothConnectStatus){
		if((NULL != pName) && (NULL != pMac)){
			strcpy(pName, DestBleName);
			strcpy(pMac, DestBleMac);
			return 0;
		}else{
			return -1;
		}
	}else{
		return -1;
	}
}

U8 BluetoothGetConnectStauts(void)
{
	return _BluetoothConnectStatus;
}
