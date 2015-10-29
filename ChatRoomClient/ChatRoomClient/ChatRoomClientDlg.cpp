
// ChatRoomClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatRoomClient.h"
#include "ChatRoomClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CChatRoomClientDlg 对话框



CChatRoomClientDlg::CChatRoomClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChatRoomClientDlg::IDD, pParent)
	, port(_T(""))
	, m_Con(_T(""))
	, m_con(_T(""))
	, dAddress(0)
	, mIP(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatRoomClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, port);
	DDX_Text(pDX, IDC_EDIT2, m_Con);
	//  DDX_Control(pDX, IDC_EDIT1, m_con);
	DDX_Text(pDX, IDC_EDIT1, m_con);
	DDX_Text(pDX, IDC_EDIT_IP, mIP);
}

BEGIN_MESSAGE_MAP(CChatRoomClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CChatRoomClientDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CChatRoomClientDlg::OnBnClickedButton2)
	ON_MESSAGE(WM_UPDATE_MESSAGE, &CChatRoomClientDlg::OnUpdateMessage)
	ON_EN_CHANGE(IDC_EDIT3, &CChatRoomClientDlg::OnEnChangeEdit3)
END_MESSAGE_MAP()


// CChatRoomClientDlg 消息处理程序

BOOL CChatRoomClientDlg::OnInitDialog()
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CChatRoomClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CChatRoomClientDlg::OnPaint()
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
HCURSOR CChatRoomClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChatRoomClientDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	client.init((char *) mIP.GetBuffer(0), _ttoi(port));
	unsigned int m_uThreadID = 0;

	cmd.dlg = this;
	cmd.client = &client;
	//Sleep(1000);
	HANDLE 	m_hThreadHandle=(HANDLE)::_beginthreadex(NULL,0,ThreadFunction, &cmd, 0, &m_uThreadID);
}
unsigned __stdcall CChatRoomClientDlg::ThreadFunction(LPVOID pThreadData)
{
	CMD_MESSAGE * cmd_mesage = (CMD_MESSAGE *) pThreadData;
	Client * tmp = cmd_mesage->client;
	CChatRoomClientDlg *dlg = cmd_mesage->dlg;
	if(tmp->run() == 0)
		return 1;
	SOCKET server = tmp->server;
	char buf[1000];
	int len = 100;
	while(1)
	{	
		int res = recv(server, buf, len, 0);
		if( res == -1)
		{
			closesocket(server);
			break;
		}
		else
		{
			tmp->con.push_back(buf);			
			dlg->m_con = dlg->m_con + "\r\n" + buf;
			dlg->PostMessage(WM_UPDATE_MESSAGE, 0, 0);			
		}
	}
	return 1;

}




void CChatRoomClientDlg::OnBnClickedButton2()
{
	UpdateData(TRUE);
	client.sendData((LPSTR)(LPCTSTR)m_Con, m_Con.GetLength()+1);
	// TODO: 在此添加控件通知处理程序代码
}


afx_msg LRESULT CChatRoomClientDlg::OnUpdateMessage(WPARAM wParam, LPARAM lParam)
{
	UpdateData(FALSE);
	int cnt = ((CEdit *)GetDlgItem(IDC_EDIT1))->GetLineCount();
	 ((CEdit *)GetDlgItem(IDC_EDIT1))->LineScroll(cnt);
	return 0;
}


void CChatRoomClientDlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	// TODO:  在此添加控件通知处理程序代码
}
