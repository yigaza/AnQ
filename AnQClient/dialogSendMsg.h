#if !defined(AFX_DIALOGSENDMSG_H__F795F3B9_F5D1_4976_A99A_E07385FE0F1B__INCLUDED_)
#define AFX_DIALOGSENDMSG_H__F795F3B9_F5D1_4976_A99A_E07385FE0F1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dialogSendMsg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// dialogSendMsg dialog

class dialogSendMsg : public CDialog
{
// Construction
public:
	dialogSendMsg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(dialogSendMsg)
	enum { IDD = IDD_DIALOG_SendMsg };
	CComboBox	m_listFriend;
	CString	m_history;
	CString	m_msg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(dialogSendMsg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(dialogSendMsg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGSENDMSG_H__F795F3B9_F5D1_4976_A99A_E07385FE0F1B__INCLUDED_)
