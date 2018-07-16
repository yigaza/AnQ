#if !defined(AFX_DIALOGNEW_H__9D36CAD2_23C4_495C_8FB4_AD788118C11C__INCLUDED_)
#define AFX_DIALOGNEW_H__9D36CAD2_23C4_495C_8FB4_AD788118C11C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dialogNew.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// dialogNew dialog

class dialogNew : public CDialog
{
// Construction
public:
	dialogNew(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(dialogNew)
	enum { IDD = IDD_DIALOG_New };
	CString	m_pass;
	CString	m_pass2;
	long	m_len;
	CString	m_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(dialogNew)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(dialogNew)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGNEW_H__9D36CAD2_23C4_495C_8FB4_AD788118C11C__INCLUDED_)
