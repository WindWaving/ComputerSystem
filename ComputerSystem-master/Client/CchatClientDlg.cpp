// CchatClientDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "CchatClientDlg.h"
#include "afxdialogex.h"


// CchatClientDlg 对话框

IMPLEMENT_DYNAMIC(CchatClientDlg, CDialogEx)

CchatClientDlg::CchatClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SOCKETCLIENT, pParent)
	, m_Words(_T(""))
	, m_port(0)
	, m_dataSend(_T(""))
{

}

CchatClientDlg::~CchatClientDlg()
{
}

void CchatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Words);
	DDX_Control(pDX, IDC_LIST1, m_listWords);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ip);
	DDX_Text(pDX, IDC_EDIT2, m_port);
	DDX_Text(pDX, IDC_EDIT3, m_dataSend);
	DDX_Control(pDX, IDC_LISTINFO, m_listInfo);
}


BEGIN_MESSAGE_MAP(CchatClientDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CONNECT, &CchatClientDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_CUTCONNECT, &CchatClientDlg::OnBnClickedCutconnect)
	ON_BN_CLICKED(IDCANCEL, &CchatClientDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SEND, &CchatClientDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_SENDFILE, &CchatClientDlg::OnBnClickedSendfile)
END_MESSAGE_MAP()


// CchatClientDlg 消息处理程序


void CchatClientDlg::OnBnClickedConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	BYTE nFild[4];
	CString sIP;
	UpdateData(TRUE);
	m_ip.GetAddress(nFild[0], nFild[1], nFild[2], nFild[3]);
	sIP.Format(L"%d.%d.%d.%d", nFild[0], nFild[1], nFild[2], nFild[3]);


	m_pSocketChat = new CClientSocket(this);
	//m_clientSocket.Create();

	if (m_pSocketChat == NULL)
	{
		MessageBox(_T("初始化失败"));

		delete  m_pSocketChat;
		m_pSocketChat = NULL;
	}

	if (m_pSocketChat->Create()==SOCKET_ERROR)
	{
		MessageBox(_T("创建失败"));

		delete  m_pSocketChat;
		m_pSocketChat = NULL;

	}

	CString sP;
	sP.Format(L"%d", m_port);
	m_listWords.AddString(L"正在连接：地址" + sIP + L"端口:" + sP);

	if (m_pSocketChat->Connect(sIP, m_port) == 0)
	{
		m_listWords.AddString(L"连接服务器成功");
	}
	else
	{
		MessageBox(L"连接服务器失败");
		delete  m_pSocketChat;
		m_pSocketChat = NULL;
	}

}


void CchatClientDlg::OnBnClickedCutconnect()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pSocketChat->Close();
	m_listWords.AddString(L"从服务器断开连接");
}


void CchatClientDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CchatClientDlg::OnBnClickedSend()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	int n = m_Words.GetLength();
	m_pSocketChat->Send(m_Words,2*n);//UNICODE字符为2个字节
	m_listInfo.AddString(L"发送: " + m_Words);
	//m_listWords.SetTopIndex(m_listWords.GetCount() - 1);
}

int CchatClientDlg::RevMsg(void)
{
	
	char temp[1024] = { 0 };
	CString str;
	int iRes = m_pSocketChat->Receive(temp, sizeof(temp));
	//str = temp;
	str.Format(L"%s", temp);
	str = L"接受: " + str;
	m_listInfo.AddString(str);

	return 0;
}


void CchatClientDlg::OnBnClickedSendfile()
{
	// TODO: 在此添加控件通知处理程序代码
	CStdioFile ifile;
	CFileException fileEx;
	if (!ifile.Open(L"data.txt", CFile::modeReadWrite,&fileEx))
	{
		MessageBox(L"文件未能打开");
	}
	CString str;
	ifile.ReadString(str);
	m_dataSend = str;
	int nLen = m_dataSend.GetLength();
	m_pSocketChat->Send(m_dataSend, 2 * nLen);
	m_listWords.AddString(L"发送数据成功");
	ifile.Close();
	

}
