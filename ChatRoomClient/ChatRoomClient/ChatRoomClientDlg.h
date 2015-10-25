
// ChatRoomClientDlg.h : ͷ�ļ�
//

#pragma once
#include "client.h"
#include "afxwin.h"

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
};
