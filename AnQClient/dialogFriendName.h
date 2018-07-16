#if !defined(AFX_DIALOGFRIENDNAME_H__25995378_E8E7_487F_8ED5_5F4EF388FD7A__INCLUDED_)
#define AFX_DIALOGFRIENDNAME_H__25995378_E8E7_487F_8ED5_5F4EF388FD7A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dialogFriendName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// dialogFriendName dialog

class dialogFriendName : public CDialog
{
// Construction
public:
	dialogFriendName(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(dialogFriendName)
	enum { IDD = IDD_DIALOG_firend_name };
	CString	m_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(dialogFriendName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(dialogFriendName)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGFRIENDNAME_H__25995378_E8E7_487F_8ED5_5F4EF388FD7A__INCLUDED_)
