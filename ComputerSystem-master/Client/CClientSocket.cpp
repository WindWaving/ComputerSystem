// CClientSocket.cpp: 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "CClientSocket.h"
#include"CchatClientDlg.h"

// CClientSocket

CClientSocket::CClientSocket(CWnd *cwnd)
{
	m_pParentWnd = cwnd;
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket 成员函数


//void CClientSocket::OnConnect(int nErrorCode)
//{
//	// TODO: 在此添加专用代码和/或调用基类
//	if (nErrorCode)
//	{
//		AfxMessageBox(L"连接失败");
//		return;
//	}
//	((CchatClientDlg *)m_parentWnd)->m_listWords.AddString(L"连接服务器成功");
//	//((CchatClientDlg *)(AfxGetApp()->m_pMainWnd))->m_listWords.AddString(L"连接服务器成功");
//	//((CchatClientDlg *)(AfxGetApp()->m_pMainWnd))->m_listWords.SetTopIndex(
//	//	((CchatClientDlg *)(AfxGetApp()->m_pMainWnd))->m_listWords.GetCount() - 1);
//
//	
//	CAsyncSocket::OnConnect(nErrorCode);
//}



void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	((CchatClientDlg *)m_pParentWnd)->RevMsg();


	CAsyncSocket::OnReceive(nErrorCode);
}


void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	//((CchatClientDlg *)(AfxGetApp()->m_pMainWnd))->m_listWords.AddString(L"已断开");
	//((CchatClientDlg *)(AfxGetApp()->m_pMainWnd))->m_listWords.SetTopIndex(
	//	((CchatClientDlg *)(AfxGetApp()->m_pMainWnd))->m_listWords.GetCount() - 1);
	((CchatClientDlg *)m_pParentWnd)->m_listWords.AddString(L"已断开服务器");

	Close();
	CAsyncSocket::OnClose(nErrorCode);
}
