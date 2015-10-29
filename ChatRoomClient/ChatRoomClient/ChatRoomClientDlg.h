
// ChatRoomClientDlg.h : ͷ�ļ�
//

#pragma once
#include "client.h"
#include "afxwin.h"
#define WM_UPDATE_MESSAGE (WM_USER+20)
// CChatRoomClientDlg �Ի���


class CChatRoomClientDlg : public CDialogEx
{
// ����
public:
	CChatRoomClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CHATROOMCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	

	 static unsigned __stdcall ThreadFunction(LPVOID pThreadData);

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString port;
	afx_msg void OnBnClickedButton1();
	Client client;
	afx_msg void OnBnClickedButton2();
	CString m_Con;
//	CEdit m_con;
	CString m_con;
	void Update(){UpdateData(FALSE);}
	struct CMD_MESSAGE
	{
		CChatRoomClientDlg * dlg;
		Client *client;
	};
	CMD_MESSAGE cmd;
protected:
	afx_msg LRESULT OnUpdateMessage(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnEnChangeEdit3();
//	DWORD wAddress;
	DWORD dAddress;
	CString mIP;
};
