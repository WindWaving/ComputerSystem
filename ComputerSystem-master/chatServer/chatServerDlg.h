
// chatServerDlg.h: 头文件
//

#pragma once
#include"CListenSocket.h"
#include"CServerSocket.h"


// CchatServerDlg 对话框
class CchatServerDlg : public CDialogEx
{
// 构造
public:
	CchatServerDlg(CWnd* pParent = nullptr);	// 标准构造函数

	CListenSocket m_listenSocket;
	CServerSocket m_serverSocket;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHATSERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CIPAddressCtrl ServerIP;
	//CString m_ListWords;
	afx_msg void OnBnClickedListen();
	int sPort;
	CListBox m_listWords;
	afx_msg void OnBnClickedClose();
	CString m_sWords;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedTurnoff();
	afx_msg void OnBnClickedAddlab();
	CListBox m_infoList;
};
