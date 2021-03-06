// CServerSocket.cpp: 实现文件
//

#include "stdafx.h"
#include "chatServer.h"
#include "CServerSocket.h"
#include"chatServerDlg.h"

// CServerSocket

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}


// CServerSocket 成员函数


void CServerSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	char szTemp[1024] = { 0 };
	int n = Receive(szTemp, sizeof(szTemp));
	CString sTemp;
	sTemp.Format(L" %s", szTemp);
	((CchatServerDlg*)(AfxGetApp()->m_pMainWnd))->m_infoList.AddString(L"收到:"+sTemp);
	((CchatServerDlg*)(AfxGetApp()->m_pMainWnd))->m_infoList.SetTopIndex(
		((CchatServerDlg*)(AfxGetApp()->m_pMainWnd))->m_infoList.GetCount() - 1);
	CStdioFile ofile;
	CFileException fileEx;
	if (!ofile.Open(L"data.txt", CFile::modeReadWrite, &fileEx))
	{
		AfxMessageBox(L"保存数据失败");
	}
	else
	{
		ofile.Seek(0, CFile::end);
		ofile.WriteString(sTemp);
		((CchatServerDlg*)(AfxGetApp()->m_pMainWnd))->m_listWords.AddString(L"数据已保存");
	}
	ofile.Close();

	CAsyncSocket::OnReceive(nErrorCode);
}

void CServerSocket::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	((CchatServerDlg*)(AfxGetApp()->m_pMainWnd))->m_listWords.AddString(L"客户端断开连接");
	((CchatServerDlg*)(AfxGetApp()->m_pMainWnd))->m_listWords.SetTopIndex(
		((CchatServerDlg*)(AfxGetApp()->m_pMainWnd))->m_listWords.GetCount() - 1);
	Close();
	CAsyncSocket::OnClose(nErrorCode);
}
