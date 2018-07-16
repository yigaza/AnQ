// dialogSendMsg.cpp : implementation file
//

#include "stdafx.h"
#include "TrayCalender.h"
#include "dialogSendMsg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// dialogSendMsg dialog


dialogSendMsg::dialogSendMsg(CWnd* pParent /*=NULL*/)
	: CDialog(dialogSendMsg::IDD, pParent)
{
	//{{AFX_DATA_INIT(dialogSendMsg)
	m_history = _T("");
	m_msg = _T("");
	//}}AFX_DATA_INIT
}


void dialogSendMsg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(dialogSendMsg)
	DDX_Control(pDX, IDC_COMBO_listFriend, m_listFriend);
	DDX_Text(pDX, IDC_EDIT_history, m_history);
	DDX_Text(pDX, IDC_EDIT_msg, m_msg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(dialogSendMsg, CDialog)
	//{{AFX_MSG_MAP(dialogSendMsg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// dialogSendMsg message handlers

void dialogSendMsg::OnOK() 
{
	UpdateData();
	CTrayCalenderApp *app=(CTrayCalenderApp *)AfxGetApp();	
	long i=m_listFriend.GetCurSel();
	if(i<0)return;
	if(m_msg=="")return;		
	app->SendMsg(app->friends[i],(LPCSTR)m_msg);
	CDialog::OnOK();
}

void dialogSendMsg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL dialogSendMsg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CTrayCalenderApp *app=(CTrayCalenderApp *)AfxGetApp();	
	for(long i=0;i<app->friendsCount;i++)
	{
		CString s;
		s=app->friends[i]->nickName;
		s=s+"/"+app->friends[i]->name;
		m_listFriend.AddString(s);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
