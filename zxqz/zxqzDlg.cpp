
// zxqzDlg.cpp : ʵ���ļ�
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
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CzxqzDlg �Ի���



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


// CzxqzDlg ��Ϣ�������

BOOL CzxqzDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CzxqzDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CzxqzDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CzxqzDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str_systime; //��ȡϵͳʱ�� ����
	CTime tm; tm = CTime::GetCurrentTime();
	str_systime = tm.Format("%Y��%m��%d�� %H:%M:%S");
	GetDlgItem(IDC_STATIC_XTSJ)->SetWindowText(str_systime);



	//��ȡ��ǰ�û�
	
	
	char str_curuser[200];
	DWORD size = 200;
	int i = GetUserName((LPSTR)str_curuser, &size);
	
	
	
	
	/*��ȡ��ǰ�������ӵĶ˿�*/
	char buffer_port[100];
	GetWindowsDirectory((LPSTR)buffer_port, 100);
	
	WinExec("cmd.exe /c  netstat -n > c:\\port.txt", SW_HIDE);//�ض���c��port.txt��
	
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
	



	/*��ȡ��ǰϵͳ��Ϣ*/
	char buffer_sysinfo[100];
	GetWindowsDirectory((LPSTR)buffer_sysinfo, 100);
	WinExec("cmd.exe /c  systeminfo> C:\\info.txt", SW_HIDE);//�ض���c��info.txt��
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


	




	

	/*��ʾrichEdit_yds������*/
	m_yds.SetWindowText((LPCTSTR)"");//�������richedit�б�

	//������ʾ��ǰϵͳʱ��
	m_yds.SetSel(-1, -1);
	m_yds.ReplaceSel(str_systime);
	m_yds.ReplaceSel("\n");

	//������ʾ��ǰ�û���



m_yds.ReplaceSel("��ǰ�û��ǣ�");
m_yds.ReplaceSel((LPSTR)str_curuser);
m_yds.ReplaceSel("\n");






	//������ʾ��ǰ���������Ӷ˿�
	m_yds.ReplaceSel(str_curport);
	
	
	//������ʾ��ǰϵͳ����Ϣ
	m_yds.ReplaceSel(str_systeminfo);
	m_yds.ReplaceSel("\n");

	


	




	//---------------------------------------------------------------------------//
	/*������ʾ�ֳ�������Ϣ*/

	
	

	//CFile::modeRead | CFile::shareDenyNone
	
//������ʾ��ǰϵͳ��·��
char strwindow[50];
char strsystem[50];
::GetWindowsDirectory((LPSTR)strwindow, 50);
::GetSystemDirectory((LPSTR)strsystem, 50);


//������ʾϵͳ�Ѿ����е�ʱ��
DWORD time;
CString str_runtime;
time = GetTickCount();
int n, hour, minute, second;
n = time / 1000;
second = n % 60;
n = n / 60;
minute = n % 60;
hour = n / 60;
str_runtime.Format("%dСʱ%d��%d��", hour, minute, second);//����strtime��ʽ


													   //������ʾϵͳ����ʱ��

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


	m_xccz.SetWindowText((LPCTSTR)"");//�������richedit�б�

	m_xccz.ReplaceSel("��ǰϵͳ·����");
	m_xccz.ReplaceSel((LPSTR)strsystem);
	m_xccz.ReplaceSel("\n");
	m_xccz.ReplaceSel("��ǰwindows·����");
	m_xccz.ReplaceSel((LPSTR)strwindow);
	m_xccz.ReplaceSel("\n");

	

	//������ʾϵͳ����ʱ��
	m_xccz.ReplaceSel("��������ʱ���ǣ�");
	m_xccz.ReplaceSel(str_starttime);
	m_xccz.ReplaceSel("\n");

	//������ʾ��ǰϵͳ�Ѿ����е�ʱ��
	m_xccz.ReplaceSel("��ǰϵͳ�Ѿ����е�ʱ���ǣ�");
	m_xccz.ReplaceSel(str_runtime);
	m_xccz.ReplaceSel("\n");

	


}
