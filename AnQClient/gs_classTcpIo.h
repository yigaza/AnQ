// gs_classTcpIo.h: interface for the gs_classTcpIo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GS_CLASSTCPIO_H__F30EF2DB_9525_48D9_AB85_71CA19AAC1A6__INCLUDED_)
#define AFX_GS_CLASSTCPIO_H__F30EF2DB_9525_48D9_AB85_71CA19AAC1A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include<winsock.h>

typedef struct __tcpsocket {
	SOCKET s;
//	SOCKADDR_IN rmt;
//	char svConnectAddr[256];
} TCPSOCKET;

class gs_classTcpIo  
{
public:
	static void * TCPIO_Connect(long port,char *svHost);
	static int TCPIO_Send(void *data, void *pData, int nDataLen);
	static int TCPIO_Remove(void);
	static int TCPIO_Recv(void *data, void **pInData, int *pnInDataLen);
	static void TCPIO_Free(void *data, void *pBuffer);
	static int TCPIO_Close(void *ios);
	static void * TCPIO_Accept(void *data, char *svAddr, int nMaxLen);
	static void * TCPIO_Listen(long port);
	static int TCPIO_Insert();
	gs_classTcpIo();
	virtual ~gs_classTcpIo();

};


DWORD WINAPI RecvFileThread(LPVOID lpArgs);

#endif // !defined(AFX_GS_CLASSTCPIO_H__F30EF2DB_9525_48D9_AB85_71CA19AAC1A6__INCLUDED_)
