
// ChatRoomServerDlg.h : ͷ�ļ�
//

#pragma once
#include "Server.h"

// CChatRoomServerDlg �Ի���
class CChatRoomServerDlg : public CDialogEx
{
// ����
public:
	CChatRoomServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CHATROOMSERVER_DIALOG };
	Server server;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


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
	afx_msg void OnBnClickedButton1();
	CString m_port;

		static unsigned __stdcall ThreadFunction(LPVOID pThreadData);
};
