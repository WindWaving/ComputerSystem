#pragma once


// CCpuInfo 对话框

class CCpuInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CCpuInfo)

public:
	CCpuInfo(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CCpuInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CString GetCpuInfo();//获取CPU信息
	CString GetIPaddress();
	CString GetSysName();
	CString GetCompuName();
	CString GetMemory();
	CString GetCurTime();

public:
	CString m_userName;
	CString m_openTime;
	CString m_cpuName;//计算机名字
	CString m_sysName;
	CString m_ipAddress;
	CString m_cpuInfo;//CPU信息
	CString m_memInfo;
	virtual BOOL OnInitDialog();
};
