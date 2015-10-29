
// ChatRoomClientDlg.h : 头文件
//

#pragma once
#include "client.h"
#include "afxwin.h"
#define WM_UPDATE_MESSAGE (WM_USER+20)
// CChatRoomClientDlg 对话框


class CChatRoomClientDlg : public CDialogEx
{
// 构造
public:
	CChatRoomClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CHATROOMCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	

	 static unsigned __stdcall ThreadFunction(LPVOID pThreadData);

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
