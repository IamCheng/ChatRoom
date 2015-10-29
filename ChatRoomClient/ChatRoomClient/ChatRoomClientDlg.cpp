
// ChatRoomClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatRoomClient.h"
#include "ChatRoomClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CChatRoomClientDlg �Ի���



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


// CChatRoomClientDlg ��Ϣ�������

BOOL CChatRoomClientDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CChatRoomClientDlg::OnPaint()
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
