#pragma once


// CLabAdd 对话框

class CLabAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CLabAdd)

public:
	CLabAdd(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CLabAdd();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LABADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_labName;
	CString m_password;
	afx_msg void OnBnClickedSave();
};
