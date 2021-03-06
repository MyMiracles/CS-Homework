// ShowLEX.cpp: 实现文件
//

#include "stdafx.h"
#include "XLexGenerator.h"
#include "ShowLEX.h"
#include "afxdialogex.h"


// ShowLEX 对话框

IMPLEMENT_DYNAMIC(ShowLEX, CDialogEx)

ShowLEX::ShowLEX(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

ShowLEX::~ShowLEX()
{
}

void ShowLEX::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOWPROGRAM, show);
}


BEGIN_MESSAGE_MAP(ShowLEX, CDialogEx)
	ON_BN_CLICKED(IDC_SAVEPROGRAM, &ShowLEX::OnBnClickedSaveProgram)
END_MESSAGE_MAP()

BOOL ShowLEX::OnInitDialog()
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
	show.SetWindowTextW(text);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


// ShowLEX 消息处理程序


void ShowLEX::OnBnClickedSaveProgram()
{
	// TODO: 在此添加控件通知处理程序代码
	//保存到文件中
	CString  path, fileName = L"temp.cpp";
	CFileDialog dlg(FALSE);
	dlg.m_ofn.lpstrTitle = L"我的文件保存对话框";
	dlg.m_ofn.lpstrFilter = L"Text Files(*.cpp)\0*.cpp\0All Files(*.*)\0*.*\0\0";
	dlg.m_ofn.lpstrDefExt = L"cpp";
	if (IDOK == dlg.DoModal())
	{
		path = dlg.GetPathName();
		//创建文件
		CStdioFile file;
		file.Open(path, CFile::modeCreate | CFile::modeWrite);
		file.SeekToEnd();
		file.WriteString(text);
		file.Flush();
		//关闭文件
		file.Close();
		MessageBox(_T("生成成功，请到文件夹查看文件"));
	}
}
