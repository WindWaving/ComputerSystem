#pragma once

// CListenSocket 命令目标

class CListenSocket : public CAsyncSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();
	virtual void OnAccept(int nErrorCode);
};


