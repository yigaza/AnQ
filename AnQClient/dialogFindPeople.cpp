// dialogFindPeople.cpp : implementation file
//

#include "stdafx.h"
#include "TrayCalender.h"
#include "dialogFindPeople.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// dialogFindPeople dialog


dialogFindPeople::dialogFindPeople(CWnd* pParent /*=NULL*/)
	: CDialog(dialogFindPeople::IDD, pParent)
{
	//{{AFX_DATA_INIT(dialogFindPeople)
	m_list = _T("");
	//}}AFX_DATA_INIT
}


void dialogFindPeople::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(dialogFindPeople)
	DDX_LBString(pDX, IDC_LIST_PeopleList, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(dialogFindPeople, CDialog)
	//{{AFX_MSG_MAP(dialogFindPeople)
	ON_LBN_DBLCLK(IDC_LIST_PeopleList, OnDblclkLISTPeopleList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// dialogFindPeople message handlers

void dialogFindPeople::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void dialogFindPeople::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void dialogFindPeople::OnDblclkLISTPeopleList() 
{
	UpdateData();
	OnOK();	
}
