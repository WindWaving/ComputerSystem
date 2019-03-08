#include "stdafx.h"
#include "CNetTraffic.h"
#include "winperf.h"

CNetTraffic::CNetTraffic()
{
	lastTraffic = 0.0;
	currentInterface = -1;
	currentTrafficType = allTraffic;
	getInterfaces();

}


CNetTraffic::~CNetTraffic()
{
}

//????
PERF_OBJECT_TYPE *FirstObject(PERF_DATA_BLOCK *dataBlock)
{
	return (PERF_OBJECT_TYPE *)((BYTE *)dataBlock + dataBlock->HeaderLength);
}

PERF_OBJECT_TYPE *NextObject(PERF_OBJECT_TYPE *act)
{
	return (PERF_OBJECT_TYPE *)((BYTE *)act + act->TotalByteLength);
}

PERF_COUNTER_DEFINITION *FirstCounter(PERF_OBJECT_TYPE *perfObject)
{
	return (PERF_COUNTER_DEFINITION *)((BYTE *)perfObject + perfObject->HeaderLength);
}

PERF_COUNTER_DEFINITION *NextCounter(PERF_COUNTER_DEFINITION *perfCounter)
{
	return (PERF_COUNTER_DEFINITION *)((BYTE *)perfCounter + perfCounter->ByteLength);
}

PERF_COUNTER_BLOCK *GetCounterBlock(PERF_INSTANCE_DEFINITION *pInstance)
{
	return (PERF_COUNTER_BLOCK *)((BYTE *)pInstance + pInstance->ByteLength);
}

PERF_INSTANCE_DEFINITION *FirstInstance(PERF_OBJECT_TYPE *pObject)
{
	return (PERF_INSTANCE_DEFINITION *)((BYTE *)pObject + pObject->DefinitionLength);
}

PERF_INSTANCE_DEFINITION *NextInstance(PERF_INSTANCE_DEFINITION *pInstance)
{
	PERF_COUNTER_BLOCK  *pCtrBlk = GetCounterBlock(pInstance);

	return (PERF_INSTANCE_DEFINITION *)((BYTE *)pInstance + pInstance->ByteLength + pCtrBlk->ByteLength);
}

char *wideToMulti(wchar_t *source, char *dest, int size)
{
	WideCharToMultiByte(CP_ACP, 0, source, -1, dest, size, 0, 0);
	return dest;
}
double CNetTraffic::getTraffic(int index)
{
	try
	{
		//get interfaceName
		POSITION pos;
		pos = interfaces.FindIndex(index);
		if (pos == NULL)
			return 0.0;
		CString interfaceName = interfaces.GetAt(pos);                //interfaceName choosed

		//get data from certain(510)interface
#define DEFAULT_BUFFER_SIZE 40960L
		unsigned char *data = new unsigned char[DEFAULT_BUFFER_SIZE];//data buffer
		DWORD type;                                                  //data type
		DWORD size = DEFAULT_BUFFER_SIZE;                            //data buffer size
		DWORD ret;                                                   //the return value of RegQueryValueEx

		while (ret = RegQueryValueEx(
			HKEY_PERFORMANCE_DATA, L"510", NULL, &type, data, &size) != ERROR_SUCCESS)
		{
			if (ret == ERROR_MORE_DATA)
			{
				size += DEFAULT_BUFFER_SIZE;
				delete[]data;
				data = new unsigned char[size];
			}
			else
				return 1;
		}


		PERF_DATA_BLOCK *dataBlockPtr = (PERF_DATA_BLOCK *)data;
		PERF_OBJECT_TYPE *objectPtr = FirstObject(dataBlockPtr);
		//overscan the list
		for (int i = 0; i < (int)dataBlockPtr->NumObjectTypes; i++)
		{
			//if the index is 510
			if (objectPtr->ObjectNameTitleIndex == 510)
			{
				//offset value
				DWORD processIdOffset = ULONG_MAX;
				PERF_COUNTER_DEFINITION *counterPtr = FirstCounter(objectPtr);
				// 遍历链表
				for (int b = 0; b < (int)objectPtr->NumCounters; b++)
				{
					if ((int)counterPtr->CounterNameTitleIndex == currentTrafficType)
						processIdOffset = counterPtr->CounterOffset;

					counterPtr = NextCounter(counterPtr);
				}
				if (processIdOffset == ULONG_MAX)
				{
					delete[] data;
					return 1;
				}

				//find the first instance
				PERF_INSTANCE_DEFINITION *instancePtr = FirstInstance(objectPtr);

				DWORD fullTraffic;
				DWORD traffic;
				char nameBuffer[255];  //current interfaceName
				//遍历整个实列,get the current traffic of the current interface
				for (int b = 0; b < objectPtr->NumInstances; b++)
				{
					wchar_t *namePtr = (wchar_t *)((BYTE *)instancePtr + instancePtr->NameOffset);
					PERF_COUNTER_BLOCK *counterBlockPtr = GetCounterBlock(instancePtr);

					// get the interfaceName
					char *pName = wideToMulti(namePtr, nameBuffer, sizeof(nameBuffer));
					CString iName;
					iName.Format(L"%S", pName);
					POSITION pos = totalTraffics.FindIndex(b);
					if (pos != NULL)
					{
						fullTraffic = *((DWORD *)((BYTE *)counterBlockPtr + processIdOffset));
						totalTraffics.SetAt(pos, fullTraffic);
					}

					//if the currentInterface is choosed interface
					if (interfaceName == iName)
					{
						traffic = *((DWORD *)((BYTE *)counterBlockPtr + processIdOffset));
						double curTraffic = (double)traffic;
						double trafficDiff;              //cur-last traffic      
						if (currentInterface != index)   //if the interfaceIndex is new,update it
						{
							lastTraffic = curTraffic;
							trafficDiff = 0.0;
							currentInterface = index;
						}
						else
						{
							trafficDiff = curTraffic - lastTraffic;
							lastTraffic = curTraffic;
						}
						delete[]data;
						return (trafficDiff);
					}
					instancePtr = NextInstance(instancePtr);
				}
			}
			objectPtr = NextObject(objectPtr);
		}
		delete[]data;
		return 0;
	}
	catch (...)
	{
		return 0;
	}
}

BOOL CNetTraffic::getInterfaces()
{
	try
	{
#define DEFAULT_BUFFER_SIZE 40960L

		interfaces.RemoveAll();
		unsigned char *data = (unsigned char*)malloc(DEFAULT_BUFFER_SIZE);
		DWORD type;
		DWORD size = DEFAULT_BUFFER_SIZE;
		DWORD ret;
		while ((ret = RegQueryValueEx(HKEY_PERFORMANCE_DATA, L"510", 0, &type, data, &size)) != ERROR_SUCCESS) {
			while (ret == ERROR_MORE_DATA)
			{
				size += DEFAULT_BUFFER_SIZE;
				data = (unsigned char*)realloc(data, size);
			}
			if (ret != ERROR_SUCCESS)
			{
				return FALSE;
			}
		}
		PERF_DATA_BLOCK	 *dataBlockPtr = (PERF_DATA_BLOCK *)data;
		PERF_OBJECT_TYPE *objectPtr = FirstObject(dataBlockPtr);

		for (int a = 0; a < (int)dataBlockPtr->NumObjectTypes; a++)
		{
			char nameBuffer[255];
			if (objectPtr->ObjectNameTitleIndex == 510)
			{
				DWORD processIdOffset = ULONG_MAX;
				PERF_COUNTER_DEFINITION *counterPtr = FirstCounter(objectPtr);

				for (int b = 0; b < (int)objectPtr->NumCounters; b++)
				{
					if (counterPtr->CounterNameTitleIndex == 520)
						processIdOffset = counterPtr->CounterOffset;

					counterPtr = NextCounter(counterPtr);
				}

				if (processIdOffset == ULONG_MAX) {
					free(data);
					return 1;
				}

				PERF_INSTANCE_DEFINITION *instancePtr = FirstInstance(objectPtr);

				for (int b = 0; b < objectPtr->NumInstances; b++)
				{
					wchar_t *namePtr = (wchar_t *)((BYTE *)instancePtr + instancePtr->NameOffset);
					PERF_COUNTER_BLOCK *counterBlockPtr = GetCounterBlock(instancePtr);
					char *pName = wideToMulti(namePtr, nameBuffer, sizeof(nameBuffer));
					DWORD bandwith = *((DWORD *)((BYTE *)counterBlockPtr + processIdOffset));
					DWORD tottraff = 0;

					interfaces.AddTail(CString(pName));
					bandwidths.AddTail(bandwith);
					totalTraffics.AddTail(tottraff);

					instancePtr = NextInstance(instancePtr);
				}
			}
			objectPtr = NextObject(objectPtr);
		}
		free(data);

		return TRUE;
	}
	catch (...)
	{
		return FALSE;
	}
}

void CNetTraffic::setTrafficType(int trafficType)
{
	currentTrafficType = trafficType;
}

BOOL CNetTraffic::getInterfaceName(CString *interfaceName, int index)
{
	POSITION pos = interfaces.FindIndex(index);
	if (pos == NULL)
		return FALSE;
	interfaceName->Format(L"%s", interfaces.GetAt(pos));
	return TRUE;
}

DWORD CNetTraffic::getInterfaceTraffic(int index)
{
	DWORD totalTraffic = 0.0;
	POSITION pos = interfaces.FindIndex(index);
	if (pos != NULL)
	{
		totalTraffic = totalTraffics.GetAt(pos);
		if (totalTraffic == 0.0)
		{
			getTraffic(index);
			pos = totalTraffics.FindIndex(index);
			if (pos != NULL)
				totalTraffic = totalTraffics.GetAt(pos);
		}
	}
	return totalTraffic;
}

int CNetTraffic::getInterfaceCount()
{
	return interfaces.GetCount() - 1;
}

DWORD CNetTraffic::getInterfaceBandwidth(int index)
{
	POSITION pos = bandwidths.FindIndex(index);
	if (pos == NULL)
		return 0;
	else
		return bandwidths.GetAt(pos) / 8;         //the transformation between bandwidth and nettraffic
}