// gs_classFileTranThread.cpp : implementation file
//

#include "..\zztest\stdafx.h"
#include "gs_classFileTranThread.h"
#include "gs_classFileThread.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// gs_classFileTranThread

IMPLEMENT_DYNCREATE(gs_classFileTranThread, CWinThread)

gs_classFileTranThread::gs_classFileTranThread()
{
	tcps=0;
	m_lStatus=1;
	name=0;
}

gs_classFileTranThread::~gs_classFileTranThread()
{
	
	free(name);
	name=0;
	//((*(CWinThread*)(&*thread))).m_hThread
}

BOOL gs_classFileTranThread::InitInstance()
{
	if(m_lStatus)m_lStatus=2;
	char *ch;int len;
	for(;m_lStatus;)
	{
		long p=gs_classTcpIo::TCPIO_Recv(tcps,(void **)&ch,&len);
		if(p<0)break;
		if(len&&p==1)
		{
			gs_classFileThread *t=(gs_classFileThread *)root;
			t->_AddReceive(ch,len,name);
			CheckMsg(ch,len);
		}
		Sleep(200);
	}
	gs_classTcpIo::TCPIO_Close(tcps);tcps=0;	

	if(m_lStatus)
	{
		m_lStatus++;  //m_lStatus=3;
		for(;m_lStatus!=0;)
		{
			Sleep(1000);
		}
	}

	AfxEndThread(0,1);
	return TRUE;
}

int gs_classFileTranThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(gs_classFileTranThread, CWinThread)
	//{{AFX_MSG_MAP(gs_classFileTranThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// gs_classFileTranThread message handlers















long gs_classFileTranThread::IsStop()
{
	return (m_lStatus==3);
}

void gs_classFileTranThread::Cancel()
{
	m_lStatus=0;
}

long gs_classFileTranThread::CheckMsg(char *ch, long len)
{
	//执行这些函数的时候客户端消失
	TiXmlDocument doc;
	LoadCharXML(&doc,ch,len);	
	
	TiXmlNode *node=doc.FirstChild("Msg");
	if(node==0)return 1;
	TiXmlElement* e =node->ToElement(); //  .FirstChild( "Msg").Element();
	if(e==0)return 1;
	char *sz;
	sz=(char *)e->Attribute("Name");
	if(sz){
		long nameLen=strlen(sz);
		name=(char *)malloc(nameLen+1);
		strcpy(name,sz);
		return 0;
	}		
	sz=(char *)e->Attribute("GetFriendList");
	{
		
		/*long nameLen=strlen(sz);
		name=(char *)malloc(nameLen+1);
		strcpy(name,sz);
		*/
		return 0;
	}
	sz=(char *)e->Attribute("To");
	if(sz)
	{
		gs_classFileThread *t=(gs_classFileThread *)root;
		t->SendMsg(sz,ch,len);
		return 0;
	}
	


	
	
	/*root=doc.Get=	
	e("Msg");
	e.SetAttribute("Name",name);
	doc.InsertEndChild(e);
	char sza[100];
	sprintf(sza,"vr2temp%ld.xml",this);
	doc.SaveFile(sza);

	char *sz;
	sz=(char *)malloc(1024*1024);
	BIO *out;
	out = BIO_new_file(sza, "r");
	long len=0;
	for(;;)
	{
		long w=BIO_read(out,sz+len,1024);
		len+=w;
		if(w<1024)break;
		if(len>=1024*1024-1024)break;
	}

	long status=gs_classTcpIo::TCPIO_Send(tcps,sz,len);
	
	BIO_free(out);	
	free(sz);
	if(status<0)return 1;

  */
	return 0;
}

void gs_classFileTranThread::LoadCharXML(TiXmlDocument *doc, char *ch, long len)
{
	char sza[100];
	sprintf(sza,"vr2temp%ld.xml",this);
	BIO *out;
	out = BIO_new_file(sza, "w");
	if(!out)return ;
	BIO_write(out,ch,len);
	BIO_free(out);		

	doc->LoadFile(sza);
}

long gs_classFileTranThread::SendMsg(char *ch, long len)
{
	//要考虑很多锁定

	gs_classTcpIo::TCPIO_Send(tcps,ch,len);
	return 0;
}

long gs_classFileTranThread::SendFriendList()
{
	TiXmlDocument doc;
	gs_classFileThread *t=(gs_classFileThread *)root;
	
	t->Lock();

	for(long i=0;i<t->m_lClientCount;i++){
		TiXmlElement *e;
		e=new TiXmlElement("Msg");
		e->SetAttribute("Friend","abc");
		doc.InsertEndChild(*e);
		delete e;
	}
	t->Unlock();
	
/*
	char sza[100];
	sprintf(sza,"vr2temp%ld.xml",this);
	doc.SaveFile(sza);

	char *sz;
	sz=(char *)malloc(1024*1024);
	BIO *out;
	out = BIO_new_file(sza, "r");
	long len=0;
	for(;;)
	{
		long w=BIO_read(out,sz+len,1024);
		len+=w;
		if(w<1024)break;
		if(len>=1024*1024-2*1024)break;
	}

	//sz[len]=0;len++;
	long status=gs_classTcpIo::TCPIO_Send(tcps,sz,len);
	
	BIO_free(out);	
	free(sz);
	if(status<0)return 1;

  */

	return 0;
}
