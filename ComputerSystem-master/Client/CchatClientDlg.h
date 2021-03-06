#pragma once
#include"CClientSocket.h"

// CchatClientDlg 对话框

class CchatClientDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CchatClientDlg)

public:
	CchatClientDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CchatClientDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SOCKETCLIENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_Words;
	CListBox m_listWords;
	//CClientSocket *m_clientSocket;
	int RevMsg(void);
	CClientSocket *m_pSocketChat;

	afx_msg void OnBnClickedConnect();
	CIPAddressCtrl m_ip;
	int m_port;
	afx_msg void OnBnClickedCutconnect();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedSend();
	CString m_dataSend;
	afx_msg void OnBnClickedSendfile();
	CListBox m_listInfo;
};
