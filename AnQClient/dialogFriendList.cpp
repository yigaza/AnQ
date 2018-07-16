// dialogFriendList.cpp : implementation file
//

#include "stdafx.h"
#include "TrayCalender.h"
#include "dialogFriendList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// dialogFriendList dialog


dialogFriendList::dialogFriendList(CWnd* pParent /*=NULL*/)
	: CDialog(dialogFriendList::IDD, pParent)
{
	//{{AFX_DATA_INIT(dialogFriendList)
	m_list = _T("");
	//}}AFX_DATA_INIT

	stringsCount=0;
}


void dialogFriendList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(dialogFriendList)
	DDX_Control(pDX, IDC_LIST2, m_listControl);
	DDX_LBString(pDX, IDC_LIST2, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(dialogFriendList, CDialog)
	//{{AFX_MSG_MAP(dialogFriendList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// dialogFriendList message handlers



BOOL dialogFriendList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	for(long i=0;i<stringsCount;i++)
	{
		CString s=nickName[i]+"/"+rsaName[i];
		m_listControl.AddString(s);
	}
	rsaName.RemoveAll();
	nickName.RemoveAll();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void dialogFriendList::AddFriend(CString rsa, CString nick)
{
	if(stringsCount<=rsaName.GetSize()){
		rsaName.SetSize(stringsCount+5);
		nickName.SetSize(stringsCount+5);		
	}
	rsaName[stringsCount]=rsa;
	nickName[stringsCount]=nick;
	stringsCount++;
}

void dialogFriendList::OnOK() 
{
	UpdateData();
	CTrayCalenderApp *app=(CTrayCalenderApp *)AfxGetApp();
	//AfxMessageBox(m_list);
	for(long i=0;i<m_listControl.GetCount();i++)
	{
		if(m_listControl.GetSel(i))
		{
			CString s;
			m_listControl.GetText(i,s);
			if(s=="")continue;
			long i=s.Find("/");
			CString sa,sb,sc,sne;
			sa=s.Left(i);
			sne=s.Right(s.GetLength()-i-1);
			s=sne;
			i=s.Find("-");
			sb=s.Left(i);
			sc=s.Right(s.GetLength()-i-1);
			app->AddFriend((LPCSTR)sa,(LPCSTR)sne,(LPCSTR)sb,(LPCSTR)sc);			
		}
	}
	
	CDialog::OnOK();
}

void dialogFriendList::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
