// CCpuInfo.cpp: 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "CCpuInfo.h"
#include "afxdialogex.h"
#include<Windows.h>

// CCpuInfo 对话框

IMPLEMENT_DYNAMIC(CCpuInfo, CDialogEx)

CCpuInfo::CCpuInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_INFO, pParent)
	, m_userName(_T(""))
	, m_openTime(_T(""))
	, m_cpuName(_T(""))
	, m_sysName(_T(""))
	, m_ipAddress(_T(""))
	, m_cpuInfo(_T(""))
	, m_memInfo(_T(""))
{

}

CCpuInfo::~CCpuInfo()
{
}

void CCpuInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT9, m_userName);
	DDX_Text(pDX, IDC_EDIT8, m_openTime);
	DDX_Text(pDX, IDC_EDIT4, m_cpuName);
	DDX_Text(pDX, IDC_EDIT3, m_sysName);
	DDX_Text(pDX, IDC_EDIT6, m_ipAddress);
	DDX_Text(pDX, IDC_EDIT5, m_cpuInfo);
	DDX_Text(pDX, IDC_EDIT7, m_memInfo);
}


BEGIN_MESSAGE_MAP(CCpuInfo, CDialogEx)
END_MESSAGE_MAP()


CString CCpuInfo::GetCompuName()//获取计算机名称
{
	const int bufSize = MAX_COMPUTERNAME_LENGTH + 1;
	TCHAR buf[bufSize];
	ZeroMemory(buf, bufSize);
	CString str;

	DWORD dwSize = bufSize;
	if (GetComputerName(buf, &dwSize))
	{
		str.Format(_T("%s"), buf);
	}
	else
	{
		MessageBox(L"获取计算机名称出错");
	}
	return str;
}

CString CCpuInfo::GetSysName()
{
	OSVERSIONINFOEX osver;
	CString str=_T("错误");
	osver.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	if (GetVersionEx((LPOSVERSIONINFOW)&osver))
	{

		if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 0)
			str = "Windows 2000";
		else if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 1)
			str = "Windows XP";
		else if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 0)
			str = "Windows 2003";
		else if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 2)
			str = "windows vista";
		else if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 1)
			str = "windows 7";
		else if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 2)
			str = "windows 10";

	}
	else
	{
		MessageBox(L"获取系统信息出错");
	}
	return str;
}


CString CCpuInfo::GetCpuInfo()
{
	SYSTEM_INFO si;
	DWORD dwNum;
	CString chProcessorType;
	memset(&si, 0, sizeof(SYSTEM_INFO));
	GetSystemInfo(&si);
	dwNum = si.dwNumberOfProcessors;

	switch (si.dwProcessorType)
	{
	case PROCESSOR_INTEL_386:
	{
		chProcessorType.Format(_T("Intel 386 processor"));
	}
	break;
	case PROCESSOR_INTEL_486:
	{
		chProcessorType.Format(_T("Intel 486 Processor"));
	}
	break;
	case PROCESSOR_INTEL_PENTIUM:
	{
		chProcessorType.Format(_T("Intel Pentium Processor"));
	}
	break;
	case PROCESSOR_INTEL_IA64:
	{
		chProcessorType.Format(_T("Intel IA64 Processor"));
	}
	break;
	case PROCESSOR_AMD_X8664:
	{
		chProcessorType.Format(_T("AMD X8664 Processor"));
	}
	break;
	default:
		chProcessorType.Format(_T("未知"));
		break;
	}
	return chProcessorType;
}


CString CCpuInfo::GetIPaddress()//获取IP
{
	CString Result;
	WSADATA wsaData;
	char Name[255];
	hostent* hostinfo;
	WORD wVersionRequested = MAKEWORD(2, 2);
	if (WSAStartup(wVersionRequested, &wsaData) == 0) 
	{
		if (gethostname(Name, sizeof(Name)) == 0) 
		{
			hostinfo = gethostbyname(Name);
			if (hostinfo != NULL)
				Result = inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list);
		}
		WSACleanup();
	}
	return Result;

}

CString CCpuInfo::GetMemory()
{
	CString TotalPhys;
	CString TotalVirtual;
	MEMORYSTATUS   Mem;
	//   get   the   memory   status   
	GlobalMemoryStatus(&Mem);
	DWORD dwSize = (DWORD)Mem.dwTotalPhys / (1024 * 1024);
	DWORD dwVirtSize = (DWORD)Mem.dwTotalVirtual / (1024 * 1024);

	TotalPhys.Format(_T("物理内存:%ld MB"), dwSize);
	TotalVirtual.Format(_T("虚拟内存:%ld MB"), dwVirtSize);
	return TotalPhys +" "+ TotalVirtual;

}


CString CCpuInfo::GetCurTime()
{
	SYSTEMTIME st;
	CString str;
	GetLocalTime(&st);
	str.Format(_T("%d-%d-%d  %d:%d:%d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	return str;
}

// CCpuInfo 消息处理程序


BOOL CCpuInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	 //TODO:  在此添加额外的初始化
	m_cpuName = GetCompuName();
	m_sysName = GetSysName();
	m_ipAddress = GetIPaddress();
	m_memInfo = GetMemory();
	m_cpuInfo = GetCpuInfo();
	m_userName = "user";
	m_openTime = GetCurTime();

	UpdateData(FALSE);

	GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				   //异常: OCX 属性页应返回 FALSE
}
