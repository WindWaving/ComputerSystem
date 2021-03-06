// CNetSpy.cpp: 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "CNetSpy.h"
#include "afxdialogex.h"
#include"CchatClientDlg.h"
#include"CFlowMonitorDlg.h"
#include"CProcess.h"
#include<iostream>
using namespace std;

// CNetSpy 对话框

IMPLEMENT_DYNAMIC(CNetSpy, CDialogEx)

CNetSpy::CNetSpy(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NETMONITOR, pParent)
{

}

CNetSpy::~CNetSpy()
{
	delete pDlg;
}

void CNetSpy::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNetSpy, CDialogEx)
	ON_BN_CLICKED(IDC_PROGET, &CNetSpy::OnBnClickedProget)
	ON_BN_CLICKED(IDC_COLLECT, &CNetSpy::OnBnClickedCollect)
	ON_BN_CLICKED(IDC_TRAFFIC, &CNetSpy::OnBnClickedTraffic)
	ON_BN_CLICKED(ID_CANCEL, &CNetSpy::OnBnClickedCancel)
END_MESSAGE_MAP()



CString CNetSpy::GetProcess()
{
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(pe);
	HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcess == INVALID_HANDLE_VALUE)
	{
		MessageBox(L"未能获取进程");
	}
	bool bResult = Process32First(hProcess, &pe);
	int num(0);
	CString idtmp;
	CString str;
	CStdioFile ofile;
	CFileException fileEx;
	CString name;

	if (ofile.Open(L"data.txt", CFile::modeCreate|CFile::modeReadWrite, &fileEx))
	{
		while (bResult)
		{
			
			char temp[257];
			WideCharToMultiByte(CP_ACP, 0, pe.szExeFile, -1, temp, sizeof(temp), NULL, NULL);				
				
			//name.Format("%s", temp);
			name = temp;

			int id = pe.th32ProcessID;
			idtmp.Format(L"%d", id);
			str = str + name + L"|";
			ofile.Seek(0, CFile::end);
			ofile.WriteString(str);

			AllocConsole();
			freopen("CONOUT$", "w", stdout);
			cout << "[" << ++num << "]:" << "process Name:" << temp << " " << "ProcessID:" << id << endl;
			
			bResult = Process32Next(hProcess, &pe);
			str.Empty();
		}
	}
	else
		MessageBox(L"文件打开错误");
	ofile.Close();
	return str;

}

void CNetSpy::OnBnClickedProget()
{
	pDlg = new CProcess();
	pDlg->Create(IDD_PROCESS);
	pDlg->ShowWindow(SW_SHOWNORMAL);

}


void CNetSpy::OnBnClickedCollect()
{
	// TODO: 在此添加控件通知处理程序代码
	pChatDlg = new CchatClientDlg();
	pChatDlg->Create(IDD_SOCKETCLIENT);
	pChatDlg->ShowWindow(SW_SHOWNORMAL);
}


void CNetSpy::OnBnClickedTraffic()
{
//	 TODO: 在此添加控件通知处理程序代码
//	CFlowMonitorDlg dlg;
//	dlg.DoModal();
	pFlowDlg = new CFlowMonitorDlg();
	pFlowDlg->Create(IDD_TRAFFIC);
	pFlowDlg->ShowWindow(SW_SHOWNORMAL);
}


void CNetSpy::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	
}
