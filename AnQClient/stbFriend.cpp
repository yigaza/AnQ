// stbFriend.cpp: implementation of the stbFriend class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stbFriend.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

stbFriend::stbFriend()
{
	name=0;
	rsa=0;
//	tcps=0;
}

stbFriend::~stbFriend()
{
//	gs_classTcpIo::TCPIO_Close(tcps);tcps=0;
//	gs_classTcpIo::TCPIO_Remove();
	if(name)free(name);
	if(nickName)free(nickName);
	if(rsa){
		RSA_free(rsa);
	}
}

void stbFriend::Reset()
{
	if(rsa)
	{
		RSA_free(rsa);
		rsa=0;
	}
}

//DEL long stbFriend::Load(char *s)
//DEL {
//DEL 	Reset();
//DEL 	rsa=RSA_new();
//DEL 	odd.LoadRSA(s,rsa);
//DEL 	
//DEL 	//rsa->n;
//DEL 	//rsa->e=0;
//DEL //	char *cc=BN_bn2hex(rsa->e);
//DEL 
//DEL 	rsa->d=0;
//DEL 	rsa->p=0;
//DEL 	rsa->q=0;
//DEL 	rsa->dmp1=0;
//DEL 	rsa->iqmp=0;
//DEL 
//DEL 	name=odd.GetNameByRSA(rsa);
//DEL 	
//DEL 	return 0;
//DEL }

long stbFriend::IsEqual(stbFriend *f)
{
	
	if(strcmp(f->name,this->name)==0)return 1;
	return 0;
	
}
