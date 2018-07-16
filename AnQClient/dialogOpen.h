#if !defined(AFX_DIALOGOPEN_H__DA2D8F31_DD44_4D38_862A_04788C871EA2__INCLUDED_)
#define AFX_DIALOGOPEN_H__DA2D8F31_DD44_4D38_862A_04788C871EA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dialogOpen.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// dialogOpen dialog

class dialogOpen : public CDialog
{
// Construction
public:
	dialogOpen(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(dialogOpen)
	enum { IDD = IDD_DIALOG_OPEN };
	CListBox	m_ctlList;
	CString	m_pass;
	CString	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(dialogOpen)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(dialogOpen)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGOPEN_H__DA2D8F31_DD44_4D38_862A_04788C871EA2__INCLUDED_)
