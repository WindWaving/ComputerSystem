#pragma once
#include"CListMenu.h"

// CProcess 对话框

class CProcess : public CDialogEx
{
	DECLARE_DYNAMIC(CProcess)

public:
	CProcess(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CProcess();

	CString getProcess();               //获取进程
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROCESS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListMenu m_listbox;
	afx_msg void OnMenuEndprocess();
};
