#pragma once

// CClientSocket 命令目标

class CClientSocket : public CAsyncSocket
{
public:
	CClientSocket(CWnd *cwnd);
	virtual ~CClientSocket();
	//virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
protected:
	CWnd * m_pParentWnd;

};


