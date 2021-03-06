// CLabAdd.cpp: 实现文件
//

#include "stdafx.h"
#include "chatServer.h"
#include "CLabAdd.h"
#include "afxdialogex.h"
#include<locale.h>


// CLabAdd 对话框

IMPLEMENT_DYNAMIC(CLabAdd, CDialogEx)

CLabAdd::CLabAdd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LABADD, pParent)
	, m_labName(_T(""))
	, m_password(_T(""))
{

}

CLabAdd::~CLabAdd()
{
}

void CLabAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_labName);
	DDX_Text(pDX, IDC_EDIT1, m_password);
}


BEGIN_MESSAGE_MAP(CLabAdd, CDialogEx)
	ON_BN_CLICKED(IDC_SAVE, &CLabAdd::OnBnClickedSave)
END_MESSAGE_MAP()


// CLabAdd 消息处理程序


void CLabAdd::OnBnClickedSave()
{
	// TODO: 在此添加控件通知处理程序代码
	CStdioFile file;
	CFileException fileEx;
	UpdateData(TRUE);

	if (file.Open(L"lab.txt", CFile::modeReadWrite, &fileEx))
	{
		file.Seek(0, CFile::end);

		char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));//配置字符转换
		setlocale(LC_CTYPE, "zh-Hans");//设定区域为简体中文

		file.WriteString(L"实验室名称：");
		file.WriteString(m_labName);
		file.WriteString(L"\t");

		file.WriteString(L"密码：");
		file.WriteString(m_password);
		file.WriteString(L"\n");

		setlocale(LC_CTYPE, old_locale);
		free(old_locale);
		MessageBox(L"保存成功");

	}

	file.Close();
}
