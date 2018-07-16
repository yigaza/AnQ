// stbSSLTalk.h: interface for the stbSSLTalk class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STBSSLTALK_H__4C2B0027_FDE6_4EF1_B584_9AC14A0B06CD__INCLUDED_)
#define AFX_STBSSLTALK_H__4C2B0027_FDE6_4EF1_B584_9AC14A0B06CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stbSSLOdd.h"
#include "stbFriend.h"


class stbSSLTalk  
{
public:
	static void GetIdRandReverse(char *id, long len);
	static char * GetIdRand(char *id,long len);
	void LoadCharXML(TiXmlDocument *doc, char *ch, long len);
	static long GetHexStringRevers(char *c);
	static char * GetHexString(char *c,long len);
	long SendMe();
	long SendMsg(char *msg,char *to);
	long CheckMsg();
	long ExportToPublic(char *s);
	long ConnectTo(char *ip,long port);
	long Load(char *s);
	long Save(char *s);
	void Reset();
	void NewRSA();
	stbSSLTalk();
	virtual ~stbSSLTalk();
	stbSSLOdd odd;
	RSA *rsa;
	TCPSOCKET *tcps;
	stbFriend **m_pFriends;
	long m_lFriendsCount;
	char *name;
};

#endif // !defined(AFX_STBSSLTALK_H__4C2B0027_FDE6_4EF1_B584_9AC14A0B06CD__INCLUDED_)
