
// ChatRoomClientDlg.h : 头文件
//

#pragma once
#include "client.h"
#include "afxwin.h"

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
};
