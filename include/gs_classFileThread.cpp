// gs_classFileThread.cpp : implementation file
//

#include "..\zztest\stdafx.h"
#include "gs_classFileThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// gs_classFileThread

IMPLEMENT_DYNCREATE(gs_classFileThread, CWinThread)

gs_classFileThread::gs_classFileThread()
{
	isRun=1;
	tcps=0;		
	if(!gs_classTcpIo::TCPIO_Insert())
	{
		tcps=(TCPSOCKET *)gs_classTcpIo::TCPIO_Listen(58877);
	}
	else
	{
		AfxMessageBox("网络初始化错误，请检查网络，程序退出。");
		exit(1);
	}
	if(tcps==0)
	{
		//_Module.LogEvent("lakdjfakl");
		AfxMessageBox("不能监听端口8877，可能是开了多个本程序");
		exit(2);
	}
	m_lMaxClient=1000;
	m_lClientCount=0;
	m_pThread=(gs_classFileTranThread **)malloc(m_lMaxClient*4);
}

gs_classFileThread::~gs_classFileThread()
{
	gs_classTcpIo::TCPIO_Close(tcps);tcps=0;
}

BOOL gs_classFileThread::InitInstance()
{
	TCPSOCKET *s;
	gs_classFileTranThread *thread;
	long count;
	for(;isRun;count++)
	{		
		s=(TCPSOCKET *)gs_classTcpIo::TCPIO_Accept(tcps,0,0);
		if(s)
		{
			thread=new gs_classFileTranThread;
			thread->tcps=s;
			thread->root=(void *)this;
			if(ClientAdd(thread)){
				thread->CreateThread(1,0);
			}			
		}
		Sleep(30);
		if(count % 3)
		{
			ClientCheckCanCancel();
		}
	}
	gs_classTcpIo::TCPIO_Close(tcps);tcps=0;
	AfxEndThread(0,1);
	return TRUE;
}

int gs_classFileThread::ExitInstance()
{
	/*
InitializeCriticalSection
EnterCriticalSection
LeaveCriticalSection
TryEnterCriticalSection
DeleteCriticalSection
*/
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(gs_classFileThread, CWinThread)
	//{{AFX_MSG_MAP(gs_classFileThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// gs_classFileThread message handlers

void gs_classFileThread::Step()
{	
	
}





void gs_classFileThread::ClientCheckCanCancel()
{
	long found=0;
	for(long i=0;i<m_lClientCount;i++){
		if(m_pThread[i]->IsStop()){
			m_pThread[i]->Cancel();
			m_pThread[i]=0;
			found++;
		}
	}
	if(found==0)return;
	long from;
	from=0;
	for(i=0;i<m_lClientCount;i++){		
		if(m_pThread[i]==0)continue;
		if(from!=i)
		{
			m_pThread[from]=m_pThread[i];
		}
		from++;
	}
	m_lClientCount-=found;
}

long gs_classFileThread::ClientAdd(gs_classFileTranThread *thread)
{
	ClientCheckCanCancel();
	if(m_lClientCount>=m_lMaxClient)
	{
		thread->Cancel();
	}
	else
	{
		m_pThread[m_lClientCount]=thread;
		m_lClientCount++;
	}
	return m_lClientCount;
}





long gs_classFileThread::SendMsg(char *to, char *ch, long len)
{
	for(long i=0;i<m_lClientCount;i++){
		if(m_pThread[i]->name){
			if(!strcmp(m_pThread[i]->name,to))
			{
				m_pThread[i]->SendMsg(ch,len);
			}
		}
	}
	return 0;
}

void gs_classFileThread::_AddReceive(char *ch, long len, char *name)
{
	char sz[11]="";
	if(name)
	{
		memcpy(sz,name,9);
		sz[10]=0;
	}
	CString s=sz;
	s=s+ch;
	s=s+"\r\n";
	_Msg+=s;
}

void gs_classFileThread::Lock()
{

}

void gs_classFileThread::Unlock()
{

}
