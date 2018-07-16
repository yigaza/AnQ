// TrayCalenderOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTrayCalenderOptions dialog

class CTrayCalenderOptions : public CDialog
{
// Construction
public:
	CTrayCalenderOptions(CWnd* pParent = NULL);   // standard constructor

	void SetValues(BOOL bAutoShuffle, UINT nShuffleDelay, BOOL bCheckDate);
	void GetValues(BOOL *bAutoShuffle, UINT *nShuffleDelay, BOOL *bCheckDate);

// Dialog Data
	//{{AFX_DATA(CTrayCalenderOptions)
	enum { IDD = IDD_OPTIONS_DIALOG };
	CSpinButtonCtrl	m_AutoShuffleSpin;
	UINT	m_nShuffleDelay;
	BOOL	m_bNoAutoShuffle;
	BOOL	m_bNoCheckDate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrayCalenderOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTrayCalenderOptions)
	afx_msg void OnAutoShuffle();
	afx_msg void OnCheckDate();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
