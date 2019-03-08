// CFlowMonitorDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "CFlowMonitorDlg.h"
#include "afxdialogex.h"


// CFlowMonitorDlg 对话框

IMPLEMENT_DYNAMIC(CFlowMonitorDlg, CDialogEx)

CFlowMonitorDlg::CFlowMonitorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TRAFFIC, pParent)
{

}

CFlowMonitorDlg::~CFlowMonitorDlg()
{
}

void CFlowMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_totalTraffic);
	DDX_Control(pDX, IDC_BUTTON2, m_uploadTraffic);
	DDX_Control(pDX, IDC_BUTTON3, m_downTraffic);
}


BEGIN_MESSAGE_MAP(CFlowMonitorDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CFlowMonitorDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CFlowMonitorDlg 消息处理程序


BOOL CFlowMonitorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	int selectedInterface = 0;
	UINT updateSpeed = 1000;
	UINT gridSpeed = 100;
	m_totalTraffic.setInterfaceIndex(selectedInterface);
	m_totalTraffic.selectTrafficType(CFlowButton::traffic_total);
	m_totalTraffic.setUpdateSpeed(updateSpeed, gridSpeed);

	m_uploadTraffic.setInterfaceIndex(selectedInterface);
	m_uploadTraffic.selectTrafficType(CFlowButton::traffic_upload);
	m_uploadTraffic.setUpdateSpeed(updateSpeed, gridSpeed);

	m_downTraffic.setInterfaceIndex(selectedInterface);
	m_downTraffic.selectTrafficType(CFlowButton::traffic_download);
	m_downTraffic.setUpdateSpeed(updateSpeed, gridSpeed);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CFlowMonitorDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
