// stbFriend.h: interface for the stbFriend class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STBFRIEND_H__039DA88B_6A6B_469F_BDC5_9F0F03FE579F__INCLUDED_)
#define AFX_STBFRIEND_H__039DA88B_6A6B_469F_BDC5_9F0F03FE579F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stbSSLOdd.h"

class stbFriend  
{
public:
	long IsEqual(stbFriend *f);
	void Reset();
	stbFriend();
	virtual ~stbFriend();
	char *name;
	char *nickName;
	RSA *rsa;
//	TCPSOCKET *tcps;
//	stbSSLOdd *odd;
//	char blow[512];
	//char servername;
};

#endif // !defined(AFX_STBFRIEND_H__039DA88B_6A6B_469F_BDC5_9F0F03FE579F__INCLUDED_)
