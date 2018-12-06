// NetTrafficButtonDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "NetTrafficButtonDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// 自身的一个指针，这是为回调函数服务的
NetTrafficButtonDlg* me;
// 记录选择的接口号
int SelectedInterface;
// 一个回调函数
void CALLBACK interfaceHasChanged(int interfacenumber);

// NetTrafficButtonDlg 对话框

IMPLEMENT_DYNAMIC(NetTrafficButtonDlg, CDialog)

NetTrafficButtonDlg::NetTrafficButtonDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_NETTRAFFIC, pParent)
{

	//为回调函数服务的
	me = this;

}


void NetTrafficButtonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_BUTTON1, m_cTotalTraffic);
	DDX_Control(pDX, IDC_BUTTON2, m_cIncoming);
	DDX_Control(pDX, IDC_BUTTON3, m_cOutgoing);
}


BEGIN_MESSAGE_MAP(NetTrafficButtonDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &NetTrafficButtonDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// NetTrafficButtonDlg 消息处理程序


BOOL NetTrafficButtonDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	// 使用第一个发现的网络连接
	int SelectedInterface = 0;
	// 每秒钟刷新一次网络状态
	UINT timerresolution = 1000;
	// To fake the Taskmanager....
	UINT gridresolution = 100;

	// 监视的接口
	//m_cTotalTraffic.SetInterfaceNumber(SelectedInterface);
	//// 这个button关注的时总流量
	//m_cTotalTraffic.SelectTrafficType(mftrafficbutton::Traffic_Total);
	//// 设置得到通知的回调函数
	//m_cTotalTraffic.SetInterfaceNumberNotificationFunction(interfaceHasChanged);
	////设置更新速率
	//m_cTotalTraffic.SetUpdateSpeed(timerresolution, gridresolution);

	//m_cOutgoing.SetInterfaceNumber(SelectedInterface);
	//m_cOutgoing.SelectTrafficType(mftrafficbutton::Traffic_Outgoing);
	//m_cOutgoing.SetInterfaceNumberNotificationFunction(interfaceHasChanged);
	//m_cOutgoing.SetUpdateSpeed(timerresolution, gridresolution);

	//m_cIncoming.SetInterfaceNumber(SelectedInterface);
	//m_cIncoming.SelectTrafficType(mftrafficbutton::Traffic_Incoming);
	//m_cIncoming.SetInterfaceNumberNotificationFunction(interfaceHasChanged);
	//m_cIncoming.SetUpdateSpeed(timerresolution, gridresolution);


	return TRUE;
}

void CALLBACK interfaceHasChanged(int interfacenumber)
{
	SelectedInterface = interfacenumber;
	CString text;
	text.Format(L"NetTrafficButton using Interface: %d", SelectedInterface);
	me->SetWindowText(text);
}



void NetTrafficButtonDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}
