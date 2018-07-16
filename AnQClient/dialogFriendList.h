#if !defined(AFX_DIALOGFRIENDLIST_H__A3C18D32_37E2_41B5_9C51_0FA52CAC4AFE__INCLUDED_)
#define AFX_DIALOGFRIENDLIST_H__A3C18D32_37E2_41B5_9C51_0FA52CAC4AFE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dialogFriendList.h : header file
//

#include "afxtempl.h"

/////////////////////////////////////////////////////////////////////////////
// dialogFriendList dialog

class dialogFriendList : public CDialog
{
// Construction
public:
	void AddFriend(CString rsa,CString nick);
	CArray<CString,CString>nickName;
	CArray<CString,CString>rsaName;
	long stringsCount;

	dialogFriendList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(dialogFriendList)
	enum { IDD = IDD_DIALOG_Friend_List };
	CListBox	m_listControl;
	CString	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(dialogFriendList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(dialogFriendList)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGFRIENDLIST_H__A3C18D32_37E2_41B5_9C51_0FA52CAC4AFE__INCLUDED_)
