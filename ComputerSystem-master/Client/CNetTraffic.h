#pragma once

#include <afxtempl.h>
class CNetTraffic
{
public:
	CNetTraffic();
	virtual ~CNetTraffic();
	enum TrafficType {
		allTraffic = 388,
		uploadTraffic = 264,
		downloadTraffic = 506,
	};                           //不清楚为什么要赋予这几个值？？？？
public:
	void setTrafficType(int trafficType);                    //get traffic type
	BOOL getInterfaceName(CString *interfaceName, int index);//get the name of the indexed interface
	DWORD getInterfaceTraffic(int index);                    //get total traffic of the indexed interface
	int getInterfaceCount();                                 //get number of the interfaces
	double getTraffic(int index);
	DWORD getInterfaceBandwidth(int index);                  //get bandwidth of the indexed interface
private:
	BOOL getInterfaces();                 //list interfaces
	double lastTraffic;                   //traffic before updated
	CStringList interfaces;               //interface(CString type) list
	CList<DWORD, DWORD &>   bandwidths;
	CList<DWORD, DWORD &>   totalTraffics;
	int currentInterface;
	int currentTrafficType;
};
