// CFlowButton.cpp: 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "CFlowButton.h"


// CFlowButton

IMPLEMENT_DYNAMIC(CFlowButton, CButton)

CFlowButton::CFlowButton()
{
	brushInitialized = FALSE;
	isUpdatedNet = FALSE;
	gridxSize = GRIDXSIZE;
	gridySize = GRIDYSIZE;
	gridxstartpos = 0;
	gridystartpos = 0;
	gridScrollxSpeed = GRIDSCROLLXSPEED;
	gridScrollySpeed = GRIDSCROLLYSPEED;
	netUpdateSpeed = NETUPDATESPEED;
	gridUpdateSpeed = GRIDUPDATESPEED;
	gridGranularity = GRIDGRANULATRITY;

}

CFlowButton::~CFlowButton()
{
}


BEGIN_MESSAGE_MAP(CFlowButton, CButton)
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CFlowButton 消息处理程序




void CFlowButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  添加您的代码以绘制指定项
	ASSERT(lpDrawItemStruct != NULL);

	CDC * pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	int erg = pDC->SelectClipRgn(&ShapeDCRegion);

	CRect rect = lpDrawItemStruct->rcItem;
	UINT state = lpDrawItemStruct->itemState;
	UINT nStyle = GetStyle();

	int nSavedDC = pDC->SaveDC();

	// Create the brush for the color bar
	if (brushInitialized == FALSE)
	{
		CBitmap bmp;
		MemDC *memDC = new MemDC(pDC);

		RECT clipRect;
		memDC->GetClipBox(&clipRect);

		if (clipRect.right - clipRect.left > 1)
		{
			bmp.CreateCompatibleBitmap(memDC, gridGranularity, trafficWinSize.cy);
			CBitmap *pOld = memDC->SelectObject(&bmp);

			CSize bmps = bmp.GetBitmapDimension();

			double factor = 255.0 / (float)trafficWinSize.cy;
			BYTE r, g, b;
			for (int x = 0; x < trafficWinSize.cy; x++)
			{
				g = (BYTE)(255 - factor * x);
				r = (BYTE)(factor*x);
				b = (BYTE)64;
				memDC->SetPixelV(0, x, RGB(r, g, b));
				memDC->SetPixelV(1, x, RGB(r, g, b));
			}
			memDC->SelectObject(pOld);

			colorBrush.CreatePatternBrush(&bmp);
			brushInitialized = TRUE;
		}
	}
	if (initialized == TRUE)
	{
		COLORREF backcolor = GetSysColor(COLOR_BTNFACE);

		CBrush brush;
		MemDC *memDC = new MemDC(pDC);

		RECT clipRect;
		memDC->GetClipBox(&clipRect);
		memDC->FillSolidRect(&clipRect, backcolor);

		CFont *oldFont;
		int xp, yp, xx, yy;
		orgBrushOrigin = memDC->GetBrushOrg();

		oldFont = memDC->SelectObject(&smallFont);

		double scale = (double)trafficWinSize.cy / (double)maxTrafficAmount;

		yp = trafficRect.bottom;
		xp = trafficRect.left;

		RECT fillrect;

		CString tmp;

		// 填充背景
		back = memDC->GetBkColor();
		brush.CreateSolidBrush(darkblue);
		memDC->FillRect(&trafficRect, &brush);

		// 画网格
		int xgridlines, ygridlines;

		xgridlines = trafficWinSize.cx / gridxSize;
		ygridlines = trafficWinSize.cy / gridySize;
		CPen* oldPen = memDC->SelectObject(&gridPen);
		// 创建垂直线
		for (int x = 0; x <= xgridlines; x++)
		{
			memDC->MoveTo(x*gridxSize + gridxstartpos, 0);
			memDC->LineTo(x*gridxSize + gridxstartpos, trafficWinSize.cy);
		}
		// 添加水平线
		for (int y = 0; y <= ygridlines; y++)
		{
			memDC->MoveTo(0, gridystartpos + trafficWinSize.cy - y * gridySize - 2);
			memDC->LineTo(trafficWinSize.cx, gridystartpos + trafficWinSize.cy - y * gridySize - 2);
		}

		gridxstartpos += gridScrollxSpeed;
		gridystartpos += gridScrollySpeed;
		if (gridxstartpos < 0) gridxstartpos = gridxSize;
		if (gridxstartpos > gridxSize) gridxstartpos = 0;
		if (gridystartpos < 0) gridystartpos = gridySize;
		if (gridystartpos > gridySize) gridystartpos = 0;


		memDC->SelectObject(oldPen);

		for (DWORD cnt = 0; cnt < gridNumbers; cnt++)
		{
			xx = xp + cnt * gridGranularity;
			double traffic = (double)trafficDots[cnt].value;
			yy = yp - (int)((double)trafficDots[cnt].value * scale);

			// 网络处在连接状态才绘制
			if (trafficDots[cnt].isConnected == TRUE)
			{
				fillrect.bottom = yp;
				fillrect.top = yy;
				fillrect.left = xx;
				fillrect.right = xx + gridGranularity;
				memDC->SetBrushOrg(xx, yp);
				if (trafficDots[cnt].value > 0.0)
				{
					memDC->FillRect(&fillrect, &colorBrush);
					memDC->SetPixelV(xx, yy, cyan);
				}
			}
		}

		tmp.Format(L"%8.1f", trafficDots[gridNumbers - 1].value);
		COLORREF textcolor = memDC->GetTextColor();
		int bkmode = memDC->GetBkMode();
		memDC->SetBkMode(TRANSPARENT);
		memDC->SetTextColor(darkblue);
		memDC->TextOut(6, 5, showTraffic);
		memDC->SetTextColor(cyan);
		memDC->TextOut(5, 5, showTraffic);
		memDC->SetTextColor(textcolor);
		memDC->SetBkMode(bkmode);
		memDC->SelectObject(oldFont);
		memDC->SetBrushOrg(orgBrushOrigin.x, orgBrushOrigin.y);

		delete memDC;
	}
	pDC->RestoreDC(nSavedDC);

}


void CFlowButton::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	ModifyStyle(0, BS_OWNERDRAW);          //ensure to draw the window by own
//application window size
	this->GetWindowRect(&trafficRect);
	this->GetWindowRect(&trafficUpdateRect);
	ScreenToClient(&trafficRect);
	ScreenToClient(&trafficUpdateRect);
	trafficWinSize.cx = trafficRect.right - trafficRect.left;
	trafficWinSize.cy = trafficRect.bottom - trafficRect.top;

	initialized = FALSE;
	//font
	smallFont.CreateFont(20, 0, 0, 0, 400, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH
		, L"Times New Roman");
	//defined color
	red = RGB(255, 125, 125);
	green = RGB(125, 255, 125);
	cyan = RGB(0, 255, 255);
	darkblue = RGB(0, 0, 75);
	darkgray = RGB(50, 50, 50);
	white = RGB(255, 255, 255);
	black = RGB(0, 0, 0);
	lightgreen = RGB(156, 255, 156);
	darkgreen = RGB(32, 64, 32);
	greenBrush.CreateSolidBrush(green);
	redBrush.CreateSolidBrush(red);
	gridPen.CreatePen(PS_SOLID, 1, darkgreen);
	//set grids and dots
	gridNumbers = trafficWinSize.cx / gridGranularity;
	trafficDots = new TrafficRecords[gridNumbers + 1];
	for (DWORD x = 0; x < gridNumbers; x++)
	{
		trafficDots[x].value = 0;
		trafficDots[x].isConnected = TRUE;
	}
	maxTrafficAmount = 0.0;
	selectedInterface = 0;
	//创建圆角矩形
	CRgn rectRgn, ellRgn;
	rectRgn.CreateRectRgn(0, 0, trafficWinSize.cx, trafficWinSize.cy);
	ShapeWNDRegion.CreateRectRgn(0, 0, trafficWinSize.cx, trafficWinSize.cy);;
	ShapeDCRegion.CreateRectRgn(0, 0, trafficWinSize.cx, trafficWinSize.cy);;

	int x1, x2, y1, y2, xe, ye, xs, ys;
	int xof, yof;
	int r;
	xs = trafficWinSize.cx;
	ys = trafficWinSize.cy;
	x1 = 0;
	y1 = 0;
	x2 = xs;
	y2 = ys;
	xe = 5;//Radius of edge
	ye = 5;//Radius of edge
	xof = (int)((float)xs*0.0);
	yof = (int)((float)ys*0.0);
	r = ellRgn.CreateRoundRectRgn(x1, y1, x2, y2, xe, ye);
	r = ellRgn.OffsetRgn(-xof, -yof);
	r = ShapeWNDRegion.CombineRgn(&rectRgn, &ellRgn, RGN_AND);
	r = ShapeDCRegion.CombineRgn(&rectRgn, &ellRgn, RGN_AND);

	this->SetWindowRgn((HRGN)ShapeWNDRegion, TRUE);
	initialized = TRUE;
	SetTimer(GRIDTIMER, gridUpdateSpeed, 0);
	SetTimer(NETTIMER, netUpdateSpeed, 0);

	CButton::PreSubclassWindow();
}


void CFlowButton::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == NETTIMER)
	{
#ifdef _I_HAVE_PLATFORM_SDK_INSTALLED_
		DWORD flag, reserved;
		BOOL erg;
		flag = 0;                  //offline
		reserved = 0;
		TCHAR connectionName[1024];
		erg = internetGetConnectedStateEx(&flag, (LPTSTR)&connectionName, 1024, 0);
		isOnline = erg;
#else
		isOnline = TRUE;
#endif
		double curTraffic = netTrafficClass.getTraffic(selectedInterface);
		double traffic = curTraffic / 1024.0;
		if (isUpdatedNet == TRUE)
			maxTrafficAmount = 0.0;
		for (DWORD i = 0; i < gridNumbers; i++)
		{
			trafficDots[i].isConnected = trafficDots[i + 1].isConnected;
			trafficDots[i].value = trafficDots[i + 1].value;
			if (trafficDots[i].value > maxTrafficAmount)
				maxTrafficAmount = trafficDots[i].value;
		}
		if (isOnline == TRUE)
		{
			trafficDots[gridNumbers].isConnected = TRUE;
			trafficDots[gridNumbers].value = curTraffic;
			if (trafficDots[gridNumbers].value > maxTrafficAmount)
				maxTrafficAmount = trafficDots[gridNumbers].value;
		}
		else
		{
			trafficDots[gridNumbers].isConnected = FALSE;
			trafficDots[gridNumbers].value = curTraffic;
			if (trafficDots[gridNumbers].value > maxTrafficAmount)
				maxTrafficAmount = trafficDots[gridNumbers].value;
		}
		double trafficMax = maxTrafficAmount / 1024.0;
		showTraffic.Format(L"当前/最大流量: %.1lf / %.1lf KB/s", traffic, trafficMax);
	}
	Invalidate(FALSE);

	CButton::OnTimer(nIDEvent);
}
void CFlowButton::reinit(RECT newSize)
{
	KillTimer(NETTIMER);
	KillTimer(GRIDTIMER);
	delete[]trafficDots;

	trafficWinSize.cx = newSize.right - newSize.left;
	trafficWinSize.cy = newSize.bottom - newSize.top;
	gridNumbers = trafficWinSize.cx / gridGranularity;
	trafficDots = new TrafficRecords[gridNumbers + 1];

	maxTrafficAmount = 0.0;
	selectedInterface = 0;
	for (DWORD x = 0; x < gridNumbers; x++)
	{
		trafficDots[x].isConnected = TRUE;
		trafficDots[x].value = 0.0;
	}
	netTrafficClass.getTraffic(selectedInterface);
	SetTimer(NETTIMER, netUpdateSpeed, 0);
	SetTimer(GRIDTIMER, gridUpdateSpeed, 0);
}
void CFlowButton::reinit(int newInterface)
{
	KillTimer(NETTIMER);
	KillTimer(GRIDTIMER);
	selectedInterface = 0;
	maxTrafficAmount = 0.0;

	for (DWORD x = 0; x < gridNumbers; x++)
	{
		trafficDots[x].isConnected = TRUE;
		trafficDots[x].value = 0.0;
	}
	netTrafficClass.getTraffic(selectedInterface);
	SetTimer(NETTIMER, netUpdateSpeed, 0);
	SetTimer(GRIDTIMER, gridUpdateSpeed, 0);

}
void CFlowButton::setAdaptiveScaling(BOOL adaptive)
{
	isUpdatedNet = adaptive;
}
void CFlowButton::setInterfaceIndex(int index)
{
	selectedInterface = index;
	reinit(selectedInterface);
}
void CFlowButton::selectTrafficType(int trafficType)
{
	switch (trafficType)
	{
	case traffic_total:
		netTrafficClass.setTrafficType(CNetTraffic::allTraffic);
		break;
	case traffic_upload:
		netTrafficClass.setTrafficType(CNetTraffic::uploadTraffic);
		break;
	case traffic_download:
		netTrafficClass.setTrafficType(CNetTraffic::downloadTraffic);
		break;
	default:
		netTrafficClass.setTrafficType(CNetTraffic::allTraffic);
		break;
	}
}

void CFlowButton::setUpdateSpeed(UINT netspeed, UINT gridspeed)
{
	gridUpdateSpeed = gridspeed;
	netUpdateSpeed = netspeed;
	KillTimer(GRIDTIMER);
	KillTimer(NETTIMER);
	SetTimer(GRIDTIMER, gridUpdateSpeed, 0);
	SetTimer(NETTIMER, netUpdateSpeed, 0);
}