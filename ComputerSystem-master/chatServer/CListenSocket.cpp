// CListenSocket.cpp: 实现文件
//

#include "stdafx.h"
#include "chatServer.h"
#include "CListenSocket.h"
#include"chatServerDlg.h"

// CListenSocket

CListenSocket::CListenSocket()
{
}

CListenSocket::~CListenSocket()
{
}


// CListenSocket 成员函数


void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	Accept(((CchatServerDlg *)(AfxGetApp()->m_pMainWnd))->m_serverSocket);
	((CchatServerDlg*)(AfxGetApp()->m_pMainWnd))->m_serverSocket.AsyncSelect(FD_READ | FD_CLOSE);
	((CchatServerDlg*)(AfxGetApp()->m_pMainWnd))->m_listWords.AddString(L"接受了一个请求");
	
	((CchatServerDlg*)(AfxGetApp()->m_pMainWnd))->m_listWords.SetTopIndex(
		((CchatServerDlg*)(AfxGetApp()->m_pMainWnd))->m_listWords.GetCount() - 1);
	CAsyncSocket::OnAccept(nErrorCode);
}
