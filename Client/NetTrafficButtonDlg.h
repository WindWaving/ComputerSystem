#if !defined(AFX_NETTRAFFICBUTTONDLG_H__F1CE9C31_5EF8_4B96_8897_29C1FAE99A6E__INCLUDED_)
#define AFX_NETTRAFFICBUTTONDLG_H__F1CE9C31_5EF8_4B96_8897_29C1FAE99A6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include"mftrafficbutton.h"

// NetTrafficButtonDlg 对话框

class NetTrafficButtonDlg : public CDialog
{
	DECLARE_DYNAMIC(NetTrafficButtonDlg)

public:
	NetTrafficButtonDlg(CWnd* pParent = nullptr);   // 标准构造函数


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NETTRAFFIC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	mftrafficbutton m_cTotalTraffic;
	mftrafficbutton m_cIncoming;
	mftrafficbutton m_cOutgoing;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
};

#endif;