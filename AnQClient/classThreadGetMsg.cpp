// classThreadGetMsg.cpp : implementation file
//

#include "stdafx.h"
#include "TrayCalender.h"
#include "classThreadGetMsg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// classThreadGetMsg

IMPLEMENT_DYNCREATE(classThreadGetMsg, CWinThread)

classThreadGetMsg::classThreadGetMsg()
{
	m_lStatus=1;
	tcps=0;
	m_stringsCount=0;
}

classThreadGetMsg::~classThreadGetMsg()
{
}

BOOL classThreadGetMsg::InitInstance()
{
	char *ch;int len;
	for(;m_lStatus;)
	{
		if(tcps==0){Sleep(20);continue;}
		long p=gs_classTcpIo::TCPIO_Recv(tcps,(void **)&ch,&len);
		if(p<0)break;
		if(len&&p==1)
		{
			Lock();
				if(m_strings.GetSize()<=m_stringsCount)
				{
					m_strings.SetSize(m_stringsCount+5);					
				}
				m_strings[m_stringsCount]=ch;
				m_stringsCount++;
			Unlock();
		}
		Sleep(20);
	}	
	return TRUE;
}

int classThreadGetMsg::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(classThreadGetMsg, CWinThread)
	//{{AFX_MSG_MAP(classThreadGetMsg)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// classThreadGetMsg message handlers

void classThreadGetMsg::Lock()
{

}

void classThreadGetMsg::Unlock()
{

}

CString classThreadGetMsg::GetAString()
{
	CString s;
	Lock();
		s=m_strings[0];
		for(long i=0;i<m_stringsCount-1;i++){
			m_strings[i]=m_strings[i+1];
		}
		m_stringsCount--;
	Unlock();
	return s;
}
