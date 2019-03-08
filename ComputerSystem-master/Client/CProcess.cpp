// CProcess.cpp: 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "CProcess.h"
#include "afxdialogex.h"
#include<TlHelp32.h>
#include<Psapi.h>
#include<iostream>
using namespace std;


// CProcess 对话框

IMPLEMENT_DYNAMIC(CProcess, CDialogEx)

CProcess::CProcess(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROCESS, pParent)
{

}

CProcess::~CProcess()
{
}

void CProcess::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listbox);
}


BEGIN_MESSAGE_MAP(CProcess, CDialogEx)
	ON_COMMAND(ID_MENU_ENDPROCESS, &CProcess::OnMenuEndprocess)
END_MESSAGE_MAP()


// CProcess 消息处理程序

CString CProcess::getProcess()
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

	if (ofile.Open(L"data.txt", CFile::modeCreate | CFile::modeReadWrite, &fileEx))
	{
		while (bResult)
		{

			char temp[257];
			WideCharToMultiByte(CP_ACP, 0, pe.szExeFile, -1, temp, sizeof(temp), NULL, NULL);

			//name.Format("%s", temp);
			name = temp;
			name = L"[" + name + L"]";

			int id = pe.th32ProcessID;
			idtmp.Format(L"%d", id);
			idtmp = L"[" + idtmp + L"]";
			str = str + name + L"|";
			ofile.Seek(0, CFile::end);
			ofile.WriteString(str);
			//进程保存到listbox中
			str = L"ProcessID: " + idtmp + L"---ProcessName: " + name;
			m_listbox.AddString(str);
			//进程输出到控制台上
			//AllocConsole();
			//freopen("CONOUT$", "w", stdout);
			//cout << "[" << ++num << "]:" << "process Name:" << temp << " " << "ProcessID:" << id << endl;
			bResult = Process32Next(hProcess, &pe);
			str.Empty();
		}
	}
	else
		MessageBox(L"文件打开错误");
	ofile.Close();
	return str;

}

DWORD FindProcess(TCHAR *strProcessName)
{
	DWORD aProcesses[1024], cbNeeded, cbMNeeded;
	HMODULE hMods[1024];
	HANDLE hProcess;
	TCHAR szProcessName[MAX_PATH];

	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))  return 0;
	for (int i = 0; i < (int)(cbNeeded / sizeof(DWORD)); i++)
	{
		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[i]);
		EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbMNeeded);
		GetModuleFileNameEx(hProcess, hMods[0], szProcessName, sizeof(szProcessName));

		CString strPrcFullName(szProcessName);
		CString strPrcName(strProcessName);
		if (_tcsstr(strPrcFullName, strPrcName) || _tcsstr(strPrcFullName, strPrcName.MakeLower()))
		{
			CString strNameFull;
			strNameFull.Format(_T("Process full name：\n%s;"), szProcessName);
			//AfxMessageBox(strNameFull);
			return(aProcesses[i]);
		}
	}

	return 0;
}

BOOL CProcess::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	getProcess();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void KillProcess(TCHAR *strProcessName)
{
	HANDLE hYourTargetProcess = OpenProcess(PROCESS_QUERY_INFORMATION |   // Required by Alpha
		PROCESS_CREATE_THREAD |   // For CreateRemoteThread
		PROCESS_VM_OPERATION |   // For VirtualAllocEx/VirtualFreeEx
		PROCESS_VM_WRITE |  // For WriteProcessMemory
		PROCESS_TERMINATE,           //Required to terminate a process using TerminateProcess function
		FALSE, FindProcess(strProcessName));

	if (hYourTargetProcess == NULL)
	{
		DWORD ulErrCode = GetLastError();
		CString strError;
		strError.Format(L"OpenProcess failed,error code:%ld", ulErrCode);
		AfxMessageBox(strError);
	}

	BOOL result = TerminateProcess(hYourTargetProcess, 0);
	if (!result)
	{
		DWORD ulErrCode = GetLastError();
		CString strError;
		strError.Format(L"TerminateProcess failed,error code:%ld", ulErrCode);
		AfxMessageBox(strError);
	}
	return;
}
void CProcess::OnMenuEndprocess()
{
	// TODO: 在此添加命令处理程序代码
	int index;
	index = m_listbox.GetCurSel();
	if (index == CB_ERR)
		MessageBox(L"please choose a record.");
	else
		MessageBox(L"Well,this part hasn't finished yet!");
		//m_listbox.DeleteString(index);

}
