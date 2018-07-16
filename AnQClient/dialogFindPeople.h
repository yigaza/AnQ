#if !defined(AFX_DIALOGFINDPEOPLE_H__AC14207B_67A5_4CAF_B4E8_C4B949D1DC79__INCLUDED_)
#define AFX_DIALOGFINDPEOPLE_H__AC14207B_67A5_4CAF_B4E8_C4B949D1DC79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dialogFindPeople.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// dialogFindPeople dialog

class dialogFindPeople : public CDialog
{
// Construction
public:
	dialogFindPeople(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(dialogFindPeople)
	enum { IDD = IDD_DIALOG_FIND_PEOPLE };
	CString	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(dialogFindPeople)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(dialogFindPeople)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnDblclkLISTPeopleList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGFINDPEOPLE_H__AC14207B_67A5_4CAF_B4E8_C4B949D1DC79__INCLUDED_)
