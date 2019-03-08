#pragma once
#include"Globals.h"
#include"CNetTraffic.h"
#include"CMemDC.h"


// CFlowButton

class CFlowButton : public CButton
{
	DECLARE_DYNAMIC(CFlowButton)

public:
	CFlowButton();
	virtual ~CFlowButton();

	enum traffictype {
		traffic_total = 0,
		traffic_upload = 1,
		traffic_download = 2,
	};
	void setAdaptiveScaling(BOOL adaptive);
	void setInterfaceIndex(int index);
	void selectTrafficType(int trafficType);
	void setUpdateSpeed(UINT netspeed, UINT gridspeed);
	void reinit(int newInterface);
	void reinit(RECT newSize);


protected:
	DECLARE_MESSAGE_MAP()


public:
	int gridxSize;		        // 网格大小
	int gridySize;
	int gridScrollxSpeed;		// 网格滚动速度
	int gridScrollySpeed;
	int netUpdateSpeed;			// 网络更新速度
	int gridUpdateSpeed;

protected:
	BOOL initialized;
	//window
	RECT trafficRect;
	RECT trafficUpdateRect;
	CSize trafficWinSize;
	CRgn	ShapeWNDRegion;
	CRgn	ShapeDCRegion;

	//draw
	CFont smallFont;
	COLORREF red, green, back, cyan, darkblue, darkgray, white, black, lightgreen, darkgreen;
	CBrush redBrush;
	CBrush greenBrush;
	CPen gridPen;
	int gridGranularity;     //distance between two grids
	DWORD gridNumbers;       //count of grids(traffic dots)
	BOOL brushInitialized;
	CBrush colorBrush;
	CPoint orgBrushOrigin;
	int gridxstartpos;
	int gridystartpos;
	//traffic
	TrafficRecords *trafficDots;
	double maxTrafficAmount;
	int selectedInterface;
	CString showTraffic;
	//online
	BOOL isOnline;
	CNetTraffic netTrafficClass;
	BOOL isUpdatedNet;

public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	virtual void PreSubclassWindow();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


