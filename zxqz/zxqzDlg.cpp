
// zxqzDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "zxqz.h"
#include "zxqzDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW

#endif



typedef struct
{
	LARGE_INTEGER liKeBootTime;
	LARGE_INTEGER liKeSystemTime;
	LARGE_INTEGER liExpTimeZoneBias;
	ULONG uCurrentTimeZoneId;
	DWORD dwReserved;
} SYSTEM_TIME_INFORMATION;

typedef long(__stdcall * funNtQuerySystemInformation) (UINT SystemInformationClass, PVOID SystemInformation,
	ULONG SystemInformationLength,
	PULONG ReturnLength OPTIONAL
	);
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


// CzxqzDlg 对话框



CzxqzDlg::CzxqzDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ZXQZ_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CzxqzDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT22, m_yds);
	DDX_Control(pDX, IDC_RICHEDIT23, m_xccz);
}

BEGIN_MESSAGE_MAP(CzxqzDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CzxqzDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CzxqzDlg 消息处理程序

BOOL CzxqzDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

void CzxqzDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CzxqzDlg::OnPaint()
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
HCURSOR CzxqzDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CzxqzDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str_systime; //获取系统时间 　　
	CTime tm; tm = CTime::GetCurrentTime();
	str_systime = tm.Format("%Y年%m月%d日 %H:%M:%S");
	GetDlgItem(IDC_STATIC_XTSJ)->SetWindowText(str_systime);



	//获取当前用户
	
	
	char str_curuser[200];
	DWORD size = 200;
	int i = GetUserName((LPSTR)str_curuser, &size);
	
	
	
	
	/*获取当前网络连接的端口*/
	char buffer_port[100];
	GetWindowsDirectory((LPSTR)buffer_port, 100);
	
	WinExec("cmd.exe /c  netstat -n > c:\\port.txt", SW_HIDE);//重定向到c：port.txt中
	
	Sleep(5000);
	CString str_curport = "";
	char sread_port[10000];
	//CFile mfile_port(_T("c:\\port.txt"), CFile::modeRead);
	CFile mfile_port(_T("c:\\port.txt"), CFile::modeRead | CFile::shareDenyNone);
	mfile_port.Read(sread_port, 10000);
	for (int i = 0; i<mfile_port.GetLength(); i++)
	{
		str_curport += sread_port[i];
	}
	mfile_port.Close();
	



	/*获取当前系统信息*/
	char buffer_sysinfo[100];
	GetWindowsDirectory((LPSTR)buffer_sysinfo, 100);
	WinExec("cmd.exe /c  systeminfo> C:\\info.txt", SW_HIDE);//重定向到c：info.txt中
	Sleep(30000);

	CString str_systeminfo = "";
	char sread_sysinfo[21000];
	//CFile mfile_sysinfo(_T("C:\\info.txt"), CFile::modeRead);
	CFile mfile_sysinfo(_T("C:\\info.txt"), CFile::modeRead | CFile::shareDenyNone);
	mfile_sysinfo.Read(sread_sysinfo, 21000);
	for (int i = 0; i<mfile_sysinfo.GetLength(); i++)
	{
		str_systeminfo += sread_sysinfo[i];
	}
	mfile_sysinfo.Close();


	




	

	/*显示richEdit_yds的内容*/
	m_yds.SetWindowText((LPCTSTR)"");//用来清空richedit列表

	//用来显示当前系统时间
	m_yds.SetSel(-1, -1);
	m_yds.ReplaceSel(str_systime);
	m_yds.ReplaceSel("\n");

	//用来显示当前用户名



m_yds.ReplaceSel("当前用户是：");
m_yds.ReplaceSel((LPSTR)str_curuser);
m_yds.ReplaceSel("\n");






	//用来显示当前的网络连接端口
	m_yds.ReplaceSel(str_curport);
	
	
	//用来显示当前系统的信息
	m_yds.ReplaceSel(str_systeminfo);
	m_yds.ReplaceSel("\n");

	


	




	//---------------------------------------------------------------------------//
	/*用来显示现场处置信息*/

	
	

	//CFile::modeRead | CFile::shareDenyNone
	
//用来显示当前系统的路径
char strwindow[50];
char strsystem[50];
::GetWindowsDirectory((LPSTR)strwindow, 50);
::GetSystemDirectory((LPSTR)strsystem, 50);


//用来显示系统已经运行的时间
DWORD time;
CString str_runtime;
time = GetTickCount();
int n, hour, minute, second;
n = time / 1000;
second = n % 60;
n = n / 60;
minute = n % 60;
hour = n / 60;
str_runtime.Format("%d小时%d分%d秒", hour, minute, second);//调整strtime格式


													   //用来显示系统开机时间

HINSTANCE hInstance = LoadLibrary("NTDLL.DLL");
CString str_starttime = "";
funNtQuerySystemInformation NtQuerySystemInformation = (funNtQuerySystemInformation)GetProcAddress(hInstance, "NtQuerySystemInformation");
if (NtQuerySystemInformation)
{
	SYSTEM_TIME_INFORMATION tInfo;
	long ret = NtQuerySystemInformation(3, &tInfo, sizeof(tInfo), 0);

	FILETIME stFile = *(FILETIME*)&tInfo.liKeBootTime;

	SYSTEMTIME stSys;
	FileTimeToLocalFileTime(&stFile, &stFile);
	FileTimeToSystemTime(&stFile, &stSys);

	str_starttime.Format("%02d-%02d-%02d %02d:%02d:%02d", stSys.wYear, stSys.wMonth, stSys.wDay, stSys.wHour, stSys.wMinute, stSys.wSecond);



}

FreeLibrary(hInstance);


	m_xccz.SetWindowText((LPCTSTR)"");//用来清空richedit列表

	m_xccz.ReplaceSel("当前系统路径：");
	m_xccz.ReplaceSel((LPSTR)strsystem);
	m_xccz.ReplaceSel("\n");
	m_xccz.ReplaceSel("当前windows路径：");
	m_xccz.ReplaceSel((LPSTR)strwindow);
	m_xccz.ReplaceSel("\n");

	

	//用来显示系统开机时间
	m_xccz.ReplaceSel("本机开机时间是：");
	m_xccz.ReplaceSel(str_starttime);
	m_xccz.ReplaceSel("\n");

	//用来显示当前系统已经运行的时间
	m_xccz.ReplaceSel("当前系统已经运行的时间是：");
	m_xccz.ReplaceSel(str_runtime);
	m_xccz.ReplaceSel("\n");

	


}
