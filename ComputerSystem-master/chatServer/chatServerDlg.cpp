
// chatServerDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "chatServer.h"
#include "chatServerDlg.h"
#include "afxdialogex.h"
#include"CLabAdd.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CchatServerDlg 对话框



CchatServerDlg::CchatServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHATSERVER_DIALOG, pParent)
	//, m_ListWords(_T(""))
	, sPort(0)
	, m_sWords(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CchatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, ServerIP);
	//DDX_LBString(pDX, IDC_LIST1, m_ListWords);
	DDX_Text(pDX, IDC_EDIT2, sPort);
	DDX_Control(pDX, IDC_LIST2, m_listWords);
	DDX_Text(pDX, IDC_EDIT1, m_sWords);
	DDX_Control(pDX, IDC_INFOBOX, m_infoList);
}

BEGIN_MESSAGE_MAP(CchatServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LISTEN, &CchatServerDlg::OnBnClickedListen)
	ON_BN_CLICKED(IDC_CLOSE, &CchatServerDlg::OnBnClickedClose)
	ON_BN_CLICKED(IDC_BUTTON1, &CchatServerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_TURNOFF, &CchatServerDlg::OnBnClickedTurnoff)
	ON_BN_CLICKED(IDC_ADDLAB, &CchatServerDlg::OnBnClickedAddlab)
END_MESSAGE_MAP()


// CchatServerDlg 消息处理程序

BOOL CchatServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CchatServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CchatServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CchatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CchatServerDlg::OnBnClickedListen()
{
	// TODO: 在此添加控件通知处理程序代码
	BYTE nFild[4];
	CString sIP, sP;
	UpdateData();
	ServerIP.GetAddress(nFild[0], nFild[1], nFild[2], nFild[3]);
	sIP.Format(L"%d.%d.%d.%d", nFild[0], nFild[1], nFild[2], nFild[3]);
	sP.Format(L"%d", sPort);

	m_listenSocket.Create(sPort, 1, FD_ACCEPT, sIP);
	m_listenSocket.Listen(1);
	m_listWords.AddString(L"监听开始:");
	m_listWords.AddString(L"地址" + sIP + " 端口" + sP);
	m_listWords.AddString(L"等待客户端连接...");
}


void CchatServerDlg::OnBnClickedClose()
{
	// TODO: 在此添加控件通知处理程序代码
	m_listenSocket.Close();
	m_listWords.AddString(L"停止监听");
}


void CchatServerDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_serverSocket.Send(m_sWords,2*m_sWords.GetLength());
	m_infoList.AddString(L"发送: "+ m_sWords);
	m_infoList.SetTopIndex(m_listWords.GetCount() - 1);
	

}




void CchatServerDlg::OnBnClickedTurnoff()
{
	// TODO: 在此添加控件通知处理程序代码
	m_serverSocket.Close();
	m_listWords.AddString(L"断开连接");
}


void CchatServerDlg::OnBnClickedAddlab()
{
	// TODO: 在此添加控件通知处理程序代码
	CLabAdd dlg;
	dlg.DoModal();
}
