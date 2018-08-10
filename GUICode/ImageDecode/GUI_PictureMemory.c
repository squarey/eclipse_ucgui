

#include "GUI_PictureMemory.h"

static U8 _InitDone = 0;
static U8 *pPicWorkMemory = NULL;
static U32 PIC_MEMORY_TOTAL_SIZE = 0;


typedef union
{
	struct{
		U32 Used:1;        //1: if the entry is Used
		U32 DataSize:31;     //Size off the data (1 means 4 bytes) ��¼�������ж��ٿ����ڴ�
	}HeaderStatus;
	U32 Header;            //The Header (Used + DataSize)
}PicMemoryHeader_t;

typedef struct
{
	PicMemoryHeader_t Header;
    U8 FirstData;        /*First data byte in the allocated data (Just for easily create a pointer)*/
}PicMemoryEnt_t;


static void *_CheckAllocStatus(PicMemoryEnt_t *pMemory, U32 Size);
static PicMemoryEnt_t *_PicMemoryGetNext(PicMemoryEnt_t * pActMemory);
static void _GoToAlloc(PicMemoryEnt_t *pMemory, U32 Size);


void GUI_PicMemoryInit(void *pBufferStart, U32 Size)
{
	PicMemoryEnt_t *pFull = (PicMemoryEnt_t *)pBufferStart;
    pFull->Header.HeaderStatus.Used = 0;
	pPicWorkMemory = (U8 *)pBufferStart;
	PIC_MEMORY_TOTAL_SIZE = Size;
    /*The total mem size id reduced by the first Header and the close patterns */
    pFull->Header.HeaderStatus.DataSize = PIC_MEMORY_TOTAL_SIZE - sizeof(PicMemoryHeader_t);
	_InitDone = 1;
}
static void GetPicMemoryStatus(void)
{
//	PicMemoryMonitor_t Monitor;
//	GUI_PicMemoryGetMonitor(&Monitor);
//	GUI_Debug("----------------------------------------------\n");
//	GUI_Debug("TotalSize:%d, FreeCount:%d, FreeSize:%d, FreeBiggestSize:%d\n", Monitor.TotalSize, Monitor.FreeCount, Monitor.FreeSize, Monitor.FreeBiggestSize);
//	GUI_Debug("UsedCount:%d, UsedPercent:%d, FragPercent:%d\n", Monitor.UsedCount, Monitor.UsedPercent, Monitor.FragPercent);
//	GUI_Debug("----------------------------------------------\n");
}
void *GUI_PicMemoryAlloc(U32 Size)
{
	void *pAlloc = NULL;
	PicMemoryEnt_t *pMemory = NULL;
	if((0 == Size) || (0 == _InitDone)){
		GUI_Debug("PicMemoryAlloc fail, Size:%d, _InitDone:%d\n", Size, _InitDone);
		return NULL;
	}
	/* ���ֽڶ���   */
	if(Size & 0x3) {
		Size = Size & (~0x3);
		Size += 4;
	}
	do{
		pMemory = _PicMemoryGetNext(pMemory);
		if(pMemory != NULL){
			pAlloc = _CheckAllocStatus(pMemory, Size);
		}
	}while((NULL != pMemory) && (NULL == pAlloc));
	return pAlloc;
}

void GUI_PicMemoryFree(const void * pData)
{
	PicMemoryEnt_t * pNextMemory = NULL;
	PicMemoryEnt_t * pMemory = NULL;
	//U32 FreeMemoryAddress = 0;
    if((pData == NULL) || (0 == _InitDone)){
    	GUI_Debug("PicMemoryFree fail, _InitDone:%d\n", _InitDone);
    	return;
    }
    /*pMemory points to the Header*/
	//FreeMemoryAddress = (unsigned int)pData;
	//printf("FreeMemoryAddress:0x%x\n", FreeMemoryAddress);
	//FreeMemoryAddress = 
    pMemory = (PicMemoryEnt_t *)((U8 *)pData - sizeof(PicMemoryHeader_t));
    pMemory->Header.HeaderStatus.Used = 0;
    /* Make a simple defrag.
     * Join the following free entries after this*/
    pNextMemory = _PicMemoryGetNext(pMemory);
    while(pNextMemory != NULL) {
        if(pNextMemory->Header.HeaderStatus.Used == 0) {
        	/* �����һ������Ҳ��û��ʹ��״̬  �������ڴ��ϲ�   */
        	pMemory->Header.HeaderStatus.DataSize += pNextMemory->Header.HeaderStatus.DataSize + sizeof(PicMemoryHeader_t);
        } else {
            break;
        }
        pNextMemory = _PicMemoryGetNext(pNextMemory);
    }
    GetPicMemoryStatus();
}

void GUI_PicMemoryGetMonitor(PicMemoryMonitor_t * pMonitor)
{
    /*Init the data*/
	PicMemoryEnt_t *pNextMemory;
    GUI_memset(pMonitor, 0, sizeof(PicMemoryMonitor_t));
    pNextMemory = NULL;
    pNextMemory = _PicMemoryGetNext(pNextMemory);
    while(pNextMemory != NULL)  {
        if(pNextMemory->Header.HeaderStatus.Used == 0) {
            pMonitor->FreeCount++;
            pMonitor->FreeSize += pNextMemory->Header.HeaderStatus.DataSize;
            if(pNextMemory->Header.HeaderStatus.DataSize > pMonitor->FreeBiggestSize) {
                pMonitor->FreeBiggestSize = pNextMemory->Header.HeaderStatus.DataSize;
            }
        } else {
            pMonitor->UsedCount++;
        }
        
        pNextMemory = _PicMemoryGetNext(pNextMemory);
    }
    pMonitor->TotalSize = PIC_MEMORY_TOTAL_SIZE;
    pMonitor->UsedPercent = 100 - (100U * pMonitor->FreeSize) / pMonitor->TotalSize;
    pMonitor->FragPercent = (U32)pMonitor->FreeBiggestSize * 100U / pMonitor->FreeSize;
    pMonitor->FragPercent = 100 - pMonitor->FragPercent;
}

/* ��ȡ��һ�����е�memory��ַ   */
static PicMemoryEnt_t *_PicMemoryGetNext(PicMemoryEnt_t * pActMemory)
{
	PicMemoryEnt_t *pNextMemory = NULL;
	/* ����������Ĳ�����NULL��ֱ�ӷ���pic_work_mem���׵�ַ  */
	if(pActMemory == NULL) { /*NULL means: get the first entry*/
		pNextMemory = (PicMemoryEnt_t * )pPicWorkMemory;
	}else {/*�����ȡ��һ�����е�memory��ַ */
		/* ��ȡ��һ���ѷ�����ڴ���׵�ַ    */
        U8 *pData = &pActMemory->FirstData;
        /* ��ת����һ���ڴ���׵�ַ   */
        pNextMemory = (PicMemoryEnt_t * )&pData[pActMemory->Header.HeaderStatus.DataSize];
        /* �����һ���ڴ���׵�ַ�Ƿ��Ѿ������˶�����ڴ��С   */
        if(&pNextMemory->FirstData >= &pPicWorkMemory[PIC_MEMORY_TOTAL_SIZE]){
        	pNextMemory = NULL;
        }
    }
	return pNextMemory;
}

/* �����ڴ��Ƿ�ռ��   */
static void *_CheckAllocStatus(PicMemoryEnt_t *pMemory, U32 Size)
{
    void *pAlloc = NULL;

    /* ����˿��ڴ汻ռ�� ���� ʣ��ռ䲻�� �򲻽��з��� */
    if(pMemory->Header.HeaderStatus.Used == 0 && pMemory->Header.HeaderStatus.DataSize >= Size) {
        /*Truncate the entry to the desired size */
    	_GoToAlloc(pMemory, Size),
        pMemory->Header.HeaderStatus.Used = 1;
        /*Save the allocated data*/
        pAlloc = &pMemory->FirstData;
    }
    return pAlloc;
}

static void _GoToAlloc(PicMemoryEnt_t *pMemory, U32 Size)
{
    /*�����ڴ���4�ֽڶ���*/
    if(Size & 0x3 ) {
        Size = Size & (~0x3);
        Size += 4;
    }

    /*���ʣ��Ŀռ��Ƿ�ոչ��˴��������Ĵ�С*/
    if(pMemory->Header.HeaderStatus.DataSize == Size + sizeof(PicMemoryEnt_t)) {
        Size = pMemory->Header.HeaderStatus.DataSize;
    }

    /* �������ʣ��Ŀռ��򴴽���һ����������ڴ�ı�ͷ */
    if(pMemory->Header.HeaderStatus.DataSize != Size) {
        U8 * pData = &pMemory->FirstData;
        PicMemoryEnt_t * pAfterNewMemory = (PicMemoryEnt_t *)&pData[Size];
        pAfterNewMemory->Header.HeaderStatus.Used = 0;
        /* ����ʣ��Ŀռ�   */
        pAfterNewMemory->Header.HeaderStatus.DataSize = pMemory->Header.HeaderStatus.DataSize - Size - sizeof(PicMemoryHeader_t);
    }
    /* ��ñ����������ڴ�Ĵ�С */
    pMemory->Header.HeaderStatus.DataSize = Size;
}

