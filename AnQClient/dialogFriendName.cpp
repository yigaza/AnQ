// dialogFriendName.cpp : implementation file
//

#include "stdafx.h"
#include "TrayCalender.h"
#include "dialogFriendName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// dialogFriendName dialog


dialogFriendName::dialogFriendName(CWnd* pParent /*=NULL*/)
	: CDialog(dialogFriendName::IDD, pParent)
{
	//{{AFX_DATA_INIT(dialogFriendName)
	m_name = _T("");
	//}}AFX_DATA_INIT
}


void dialogFriendName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(dialogFriendName)
	DDX_Text(pDX, IDC_EDIT2, m_name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(dialogFriendName, CDialog)
	//{{AFX_MSG_MAP(dialogFriendName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// dialogFriendName message handlers

void dialogFriendName::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void dialogFriendName::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
