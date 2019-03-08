#pragma once
#include"CFlowButton.h"

// CFlowMonitorDlg 对话框

class CFlowMonitorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFlowMonitorDlg)

public:
	CFlowMonitorDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CFlowMonitorDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRAFFIC };1
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CFlowButton m_totalTraffic;
	CFlowButton m_uploadTraffic;
	CFlowButton m_downTraffic;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCancel();
};
