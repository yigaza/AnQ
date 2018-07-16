// dialogOpen.cpp : implementation file
//

#include "stdafx.h"
#include "TrayCalender.h"
#include "dialogOpen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// dialogOpen dialog


dialogOpen::dialogOpen(CWnd* pParent /*=NULL*/)
	: CDialog(dialogOpen::IDD, pParent)
{
	//{{AFX_DATA_INIT(dialogOpen)
	m_pass = _T("");
	m_list = _T("");
	//}}AFX_DATA_INIT


}


void dialogOpen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(dialogOpen)
	DDX_Control(pDX, IDC_LIST1, m_ctlList);
	DDX_Text(pDX, IDC_EDIT_pass, m_pass);
	DDX_LBString(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP

	
	CFileFind ff;
	long k=ff.FindFile("*.pem");
	if(k)for(;;){
		k=ff.FindNextFile();
		CString sd=ff.GetFileName();
		sd=sd.Left(sd.GetLength()-4);
		m_ctlList.AddString(sd);
		if(k==0)break;
	}
}


BEGIN_MESSAGE_MAP(dialogOpen, CDialog)
	//{{AFX_MSG_MAP(dialogOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// dialogOpen message handlers

void dialogOpen::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void dialogOpen::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
