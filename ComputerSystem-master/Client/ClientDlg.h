
// ClientDlg.h: 头文件
//

#pragma once
#include"CCpuInfo.h"
#include"CNetSpy.h"


// CClientDlg 对话框
class CClientDlg : public CDialogEx
{
// 构造
public:
	CClientDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	CMenu m_clientMenu;
// 实现
protected:
	HICON m_hIcon;
	int m_nCurTab=0;
	CDialog *m_pDlg[2] ;
	CCpuInfo m_tabInfo;
	CNetSpy m_tabNet;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tabClient;
	afx_msg void OnTcnSelchangeClienttab(NMHDR *pNMHDR, LRESULT *pResult);
};
