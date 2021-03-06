#pragma once


// CNetSpy 对话框
#include <windows.h>
#include"CProcess.h"
#include"CFlowMonitorDlg.h"
#include"CchatClientDlg.h"
#include <tlhelp32.h>
#include <Psapi.h>
#pragma comment (lib,"Psapi.lib")


class CNetSpy : public CDialogEx
{
	DECLARE_DYNAMIC(CNetSpy)

public:
	CNetSpy(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CNetSpy();
	//BOOL DosPathToNtPath(LPTSTR pszDosPath, LPTSTR pszNtPath);//把dos路径名称传递
	//BOOL GetProcessFullPath(DWORD dwPID);
	//CString ShowProcess();
	
	CString GetProcess();
	CString str;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NETMONITOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedProget();
	afx_msg void OnBnClickedCollect();
	afx_msg void OnBnClickedTraffic();

private:
	CProcess *pDlg;
	CFlowMonitorDlg *pFlowDlg;
	CchatClientDlg *pChatDlg;
public:
	afx_msg void OnBnClickedCancel();
};
