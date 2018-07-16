// stbSSLTalk.cpp: implementation of the stbSSLTalk class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stbSSLTalk.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

stbSSLTalk::stbSSLTalk()
{

	/*
	char ds[]="1234567890";
	long lenOut;
	char *cc=GetHexString(ds,strlen(ds));
	long dd=GetHexStringRevers(cc);
	dd=dd;
	*/

	rsa=0;
	tcps=0;
	gs_classTcpIo::TCPIO_Insert();
	m_lFriendsCount=0;
	m_pFriends=(stbFriend **)malloc(1000*4);
	name=0;

}

stbSSLTalk::~stbSSLTalk()
{
	Reset();
	gs_classTcpIo::TCPIO_Close(tcps);tcps=0;
	gs_classTcpIo::TCPIO_Remove();

	for(long i=0;i<m_lFriendsCount;i++)
	{
		delete m_pFriends[i];
	}
	m_lFriendsCount=0;
	free(m_pFriends);

}

void stbSSLTalk::NewRSA()
{	
	Reset();
	rsa=odd.GenRSA(1024);

	name=odd.GetNameByRSA(rsa); 

	return;

}

void stbSSLTalk::Reset()
{
	if(rsa)
	{
		RSA_free(rsa);
		rsa=0;
	}
	if(name){
		free(name);
		name=0;
	}
}

long stbSSLTalk::Save(char *s)
{
	if(rsa==0)return 1;
	odd.SaveRSA(s,rsa);
	return 0;
}

long stbSSLTalk::Load(char *s)
{	
	Reset();
	rsa=RSA_new();
	odd.LoadRSA(s,rsa);
	
	//name=BN_bn2hex(rsa->n); 

	name=odd.GetNameByRSA(rsa);

	return 0;
}

long stbSSLTalk::ConnectTo(char *ip, long port)
{
	gs_classTcpIo::TCPIO_Close(tcps);
	tcps=0;
	tcps=(TCPSOCKET *)gs_classTcpIo::TCPIO_Connect(port,ip);
	return 0;
}

//DEL long stbSSLTalk::AddFriend(char *s)
//DEL {
//DEL 	/*
//DEL 	if(m_lFriendsCount>=1000)return 1;
//DEL 	stbFriend *f=new stbFriend;
//DEL 	if(f==0)return 1;
//DEL 	if(f->Load(s))
//DEL 	{
//DEL 		delete f;return 1;
//DEL 	}
//DEL 	m_pFriends[m_lFriendsCount]=f;
//DEL 	m_lFriendsCount++;	
//DEL 
//DEL 	*/
//DEL 
//DEL 	return 0;
//DEL }

long stbSSLTalk::ExportToPublic(char *s)
{
	if(rsa==0)return 1;
	RSA *r;
	r=RSAPublicKey_dup(rsa);	
	odd.SaveRSA(s,r);
	return 0;
}

long stbSSLTalk::CheckMsg()
{
	char *ch;int len;
	long p=gs_classTcpIo::TCPIO_Recv(tcps,(void **)&ch,&len);
	if(p<0)return 1;
	if(len&&p==1){		
		
	TiXmlDocument doc;
	LoadCharXML(&doc,ch,len);	
	
	TiXmlNode *node=doc.FirstChild("Msg");
	if(node==0)return 1;
	TiXmlElement* e =node->ToElement(); //  .FirstChild( "Msg").Element();
	if(e==0)return 1;
	TiXmlNode *node1=e->FirstChild("Msg");
	TiXmlElement* e1 =node1->ToElement();
	char *sz;
	sz=(char *)e1->Attribute("Msg");
	if(sz){
		{
			long l=GetHexStringRevers(sz);		
			int lenOut;			
			char *cOut=odd.DecryptByTwoRSA(sz,l,&lenOut,rsa,m_pFriends[0]->rsa);
			if(lenOut){
				cOut[lenOut]=0;				
				AfxMessageBox(cOut);
			}
		}
	}
		
		
		
	}
	return 0;
}

long stbSSLTalk::SendMsg(char *msg, char *to)
{
	stbFriend *f=0;	
	if(to==0&&m_lFriendsCount>0)
	{
		f=m_pFriends[0];
	}
	else
	{
		for(long i=0;i<m_lFriendsCount;i++)
		{
			if(strcmp(to,m_pFriends[i]->name)==0)
			{
				f=m_pFriends[i];
			}
		}
	}
	if(f==0)return 1;
	
	TiXmlDocument doc;
	TiXmlElement e("Msg");
	e.SetAttribute("From",name);
	e.SetAttribute("To",f->name);
	doc.InsertEndChild(e);
	TiXmlElement *root=doc.RootElement();
	TiXmlElement ee("Msg");

	{
	
	int lenOut;
	char *out=odd.EncryptByTwoRSA((char *)msg,strlen(msg),&lenOut,rsa,f->rsa);//EncryptByTwoRSA()
	
		if(lenOut==0)return 1;

		char *cc=GetHexString(out,lenOut);
	//	AfxMessageBox(cc);
	//	long l=GetHexStringRevers(cc);
		ee.SetAttribute("Msg",cc);
		free(out);
		free(cc);
	}
	
	//ee.SetAttribute("Msg",msg);
	root->InsertEndChild(ee);
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

//	sz[len]=0;len++;
	long status=gs_classTcpIo::TCPIO_Send(tcps,sz,len);
	
	BIO_free(out);	
	free(sz);
	if(status<0)return 1;

	return 0;
}

long stbSSLTalk::SendMe()
{
	TiXmlDocument doc;
	TiXmlElement e("Msg");
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
		if(len>=1024*1024-2*1024)break;
	}

	//sz[len]=0;len++;
	long status=gs_classTcpIo::TCPIO_Send(tcps,sz,len);
	
	BIO_free(out);	
	free(sz);
	if(status<0)return 1;
	return 0;
}

//DEL long stbSSLTalk::SendByPublic(char *msg, long len, char *to)
//DEL {
//DEL 
//DEL 	/*stbFriend *f=0;	
//DEL 	if(to==0&&m_lFriendsCount>0)
//DEL 	{
//DEL 		f=m_pFriends[0];
//DEL 	}
//DEL 	else
//DEL 	{
//DEL 		for(long i=0;i<m_lFriendsCount;i++)
//DEL 		{
//DEL 			if(strcmp(to,m_pFriends[i]->name)==0)
//DEL 			{
//DEL 				f=m_pFriends[i];
//DEL 			}
//DEL 		}
//DEL 	}
//DEL 	if(f==0)return 1;
//DEL 	
//DEL 	TiXmlDocument doc;
//DEL 	TiXmlElement e("Msg");
//DEL 	e.SetAttribute("From",name);
//DEL 	e.SetAttribute("To",f->name);
//DEL 	doc.InsertEndChild(e);
//DEL 	TiXmlElement *root=doc.RootElement();
//DEL 	TiXmlElement ee("Msg");
//DEL 	ee.SetAttribute("Msg",msg);
//DEL 	root->InsertEndChild(ee);
//DEL 	char sza[100];
//DEL 	sprintf(sza,"vr2temp%ld.xml",this);
//DEL 	doc.SaveFile(sza);
//DEL 
//DEL 	char *sz;
//DEL 	sz=(char *)malloc(1024*1024);
//DEL 	BIO *out;
//DEL 	out = BIO_new_file(sza, "r");
//DEL 	long len=0;
//DEL 	for(;;)
//DEL 	{
//DEL 		long w=BIO_read(out,sz+len,1024);
//DEL 		len+=w;
//DEL 		if(w<1024)break;
//DEL 		if(len>=1024*1024-2*1024)break;
//DEL 	}
//DEL 
//DEL 	sz[len]=0;len++;
//DEL 	long status=gs_classTcpIo::TCPIO_Send(tcps,sz,len);
//DEL 	
//DEL 	BIO_free(out);	
//DEL 	free(sz);
//DEL 	if(status<0)return 1;
//DEL 
//DEL 	*/
//DEL 	return 0;
//DEL }

char * stbSSLTalk::GetHexString(char *c, long len)
{
	char *out=(char *)malloc(len*2+1);
	for(long i=0;i<len;i++){
		unsigned char ch=c[i];
		out[i*2]=(char)('a'+ch/16);
		out[i*2+1]=(char)('a'+ch%16);
	}
	out[len*2]=0;
	return out;
}

long stbSSLTalk::GetHexStringRevers(char *c)
{	
	long a,b,len=0;
	for(long i=0;c[i];i+=2){
		a=c[i]-'a';
		b=c[i+1]-'a';
		c[i/2]=(char )(a*16+b);
		len++;
	}
	return len;
}

void stbSSLTalk::LoadCharXML(TiXmlDocument *doc, char *ch, long len)
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



char * stbSSLTalk::GetIdRand(char *id, long len)
{
	char *c=(char *)malloc(len*2);
	memcpy(c,id,len);
	RAND_bytes((unsigned char *)(c+len),len);
	for(long i=0;i<len;i++)
	{
		c[i]=(char)(((BYTE)id[i])^((BYTE)(c[i+len])));
	}
	return c;
}

void stbSSLTalk::GetIdRandReverse(char *id, long len)
{	
	len /=2;
	long j=len;
	for(long i=0;i<len;i++,j++)
	{		
		id[i]=(char)(((BYTE)id[i])^((BYTE)(id[j])));
	}	
}
