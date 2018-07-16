// gs_classTcpIo.cpp: implementation of the gs_classTcpIo class.
//
//////////////////////////////////////////////////////////////////////


#include "gs_classTcpIo.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

gs_classTcpIo::gs_classTcpIo()
{
	TCPIO_Insert();
}

gs_classTcpIo::~gs_classTcpIo()
{
	WSACleanup();
}

int gs_classTcpIo::TCPIO_Insert()
{
	WSADATA wsaData;
	if(WSAStartup(MAKEWORD(1,1), &wsaData)!=0) return -1;
	if(LOBYTE(wsaData.wVersion)!=1 || HIBYTE(wsaData.wVersion)!=1) {
		WSACleanup();
		return -1;
	}
	
	return 0;
}

void * gs_classTcpIo::TCPIO_Listen(long port)
{
	TCPSOCKET *tcps;
	
	struct in_addr bindAddr;
	bindAddr.S_un.S_addr=INADDR_ANY;
	int nPort=port;	
	
	// Create listener socket
	SOCKET s;
	s=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(s==INVALID_SOCKET) return NULL;
	
	BOOL sopt;
	sopt=TRUE;
	setsockopt(s,IPPROTO_TCP,TCP_NODELAY,(char *)&sopt,sizeof(BOOL));
	sopt=TRUE;
	setsockopt(s,SOL_SOCKET,SO_DONTLINGER,(char *)&sopt,sizeof(BOOL));
	
	// Bind socket and listen
	SOCKADDR_IN saddr;
	memset(&saddr,0,sizeof(SOCKADDR_IN));
	saddr.sin_addr=bindAddr;
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons((WORD)nPort);
	
	if(bind(s,(SOCKADDR *) &saddr,sizeof(SOCKADDR_IN))==SOCKET_ERROR) {
		closesocket(s);
		return NULL;
	}
	if(listen(s,SOMAXCONN)!=0) {
		closesocket(s);
		return NULL;
	}
	
	int namelen=sizeof(SOCKADDR_IN);
	getsockname(s,(SOCKADDR *)&saddr,&namelen);

	// Allocate state structure
	tcps=(TCPSOCKET *)malloc(sizeof(TCPSOCKET));
	if(tcps==NULL) {
		closesocket(s);
		return NULL;
	}

	// Fill in state structure
	tcps->s=s;
	//memset(&(tcps->rmt),0,sizeof(SOCKADDR_IN));
	
	// Get connect address
	if(bindAddr.S_un.S_addr==INADDR_ANY) {
		char svHostName[256];
		struct hostent *he;
		struct in_addr *pAddr;
		gethostname(svHostName,256);
		he=gethostbyname(svHostName);
		pAddr=(struct in_addr *)he->h_addr_list[0];
		if(he) {
	//		char cc[20]="%u.%u.%u.%u:%u";
//			wsprintf(tcps->svConnectAddr,cc,pAddr->S_un.S_un_b.s_b1,pAddr->S_un.S_un_b.s_b2,pAddr->S_un.S_un_b.s_b3,pAddr->S_un.S_un_b.s_b4,ntohs(saddr.sin_port));
		} else {
//			strcpy(tcps->svConnectAddr,"No Connect Addr");
		}
	} else {
//		strcpy(tcps->svConnectAddr,"No Connect Addr");
	}
	return tcps;
}

void * gs_classTcpIo::TCPIO_Accept(void *data, char *svAddr, int nMaxLen)
{
	TCPSOCKET *tcps=(TCPSOCKET *)data;	
	// Check for connection
	fd_set rdfds;
	TIMEVAL tm;

	FD_ZERO(&rdfds);
	FD_SET(tcps->s,&rdfds);
	
	tm.tv_sec=0;
	tm.tv_usec=0;

	if(select(0,&rdfds,NULL,NULL,&tm)<=0) {
		return 0;
	}

	// Accept socket
	SOCKADDR_IN saddr;
	int len=sizeof(SOCKADDR_IN);
	SOCKET accs;

	accs=accept(tcps->s,(SOCKADDR *)&saddr,&len);
	if(accs==INVALID_SOCKET) return NULL;

	BOOL sopt;
	sopt=TRUE;
	setsockopt(accs,IPPROTO_TCP,TCP_NODELAY,(char *)&sopt,sizeof(BOOL));
	sopt=TRUE;
	setsockopt(accs,SOL_SOCKET,SO_DONTLINGER,(char *)&sopt,sizeof(BOOL));
	
	TCPSOCKET *acc_ios=(TCPSOCKET *)malloc(sizeof(TCPSOCKET));
	if(acc_ios==NULL) {
		closesocket(accs);
		return NULL;
	}

	acc_ios->s=accs;	
		
	return acc_ios;
}

int gs_classTcpIo::TCPIO_Close(void *ios)
{
	TCPSOCKET *tcps=(TCPSOCKET *)ios;
	if(tcps)
	{
	
		closesocket(tcps->s);

		free(tcps);
	}
	return 0;
}

void gs_classTcpIo::TCPIO_Free(void *data, void *pBuffer)
{
	if(pBuffer==NULL) return;
	free(pBuffer);
}

int gs_classTcpIo::TCPIO_Recv(void *data, void **pInData, int *pnInDataLen)
{
	TCPSOCKET *tcps=(TCPSOCKET *)data;	
	// Check socket for readability 
	TIMEVAL tv;
	int nRet;
	tv.tv_sec=0;
	tv.tv_usec=0;
	fd_set rfds;
	FD_ZERO(&rfds);
	FD_SET(tcps->s,&rfds);
	nRet=select(1,&rfds,NULL,NULL,&tv);
	if(nRet==SOCKET_ERROR) return -1;
	if(nRet==0) return 0;

	DWORD len;
	if(ioctlsocket(tcps->s,FIONREAD,&len)==SOCKET_ERROR) 
		return -1;
	
	BYTE *buf=(BYTE *)malloc(1024*1024+1);
	if(buf==NULL) {
		*pInData=NULL;
		*pnInDataLen=0;
		return -1;
	}

	// Receive data
	char *pbuf=(char *)buf;
	int count=0;
	long lenret;
//	if(count>0)
	//解决CPU消耗过多,但没有找到断线原因
	do {
		lenret=recv(tcps->s,pbuf,1,0);
		if(lenret==SOCKET_ERROR||(lenret<0)) {
			free(buf);
			*pInData=NULL;
			*pnInDataLen=0;
			return -1;
		}
		if(((char *)(pbuf))[0]=='\n'){
			break;
		}
		count+=lenret;
		pbuf+=lenret;
		if(count>1024*1024){
			free(buf);
			*pInData=NULL;
			*pnInDataLen=0;
			return -1;
		}		
		//Sleep(20);
		if(lenret==0){
			Sleep(10);
		}

	}while(1);

	// Pass data back to application
	*pInData=buf;
	*pnInDataLen=count;
	buf[count]=0;
	return 1;


	/*
	TCPSOCKET *tcps=(TCPSOCKET *)data;
	
	// Check socket for readability 
	TIMEVAL tv;
	int nRet;
	tv.tv_sec=0;
	tv.tv_usec=0;
	fd_set rfds;
	FD_ZERO(&rfds);
	FD_SET(tcps->s,&rfds);
	nRet=select(1,&rfds,NULL,NULL,&tv);
	if(nRet==SOCKET_ERROR) return -1;
	if(nRet==0) return 0;

	// Get length of rest of data
	DWORD nPktLen;
	int lenret;
	lenret=recv(tcps->s,(char *)&nPktLen,sizeof(DWORD),MSG_PEEK);
	//if(lenret==0)return -1;
	if(lenret<=0) return -1;
	if(lenret<sizeof(DWORD)) 
		return 0;

	//int sizeSend=9812321-nDataLen;
	nPktLen=9812321-nPktLen;	
	
	// Make sure we have the rest of the packet
	DWORD len;
	if(ioctlsocket(tcps->s,FIONREAD,&len)==SOCKET_ERROR) 
		return -1;

	if(len<(sizeof(DWORD)+nPktLen)) 
		return 0;

	// Clear off the header
	lenret=recv(tcps->s,(char *)&nPktLen,sizeof(DWORD),0);
	if(lenret<sizeof(DWORD)) 
		return -1;

	nPktLen=9812321-nPktLen;
	
	// Allocate buffer for data
	BYTE *buf=(BYTE *)malloc(nPktLen+1);
	buf[nPktLen]=0;
	if(buf==NULL) {
		*pInData=NULL;
		*pnInDataLen=0;
		return -1;
	}

	// Receive data
	char *pbuf=(char *)buf;
	int count=nPktLen;
	if(count>0)
	do {
		lenret=recv(tcps->s,pbuf,count,0);
		if(lenret==SOCKET_ERROR) {
			free(buf);
			*pInData=NULL;
			*pnInDataLen=0;
			return -1;
		}
		count-=lenret;
		pbuf+=lenret;
		if(count>0) Sleep(20);
	} while(count>0);

	// Pass data back to application
	*pInData=buf;
	*pnInDataLen=nPktLen;
	return 1;
	*/
}

int gs_classTcpIo::TCPIO_Remove()
{
	WSACleanup();
	return 0;
}

int gs_classTcpIo::TCPIO_Send(void *tcp, void *pData, int nDataLen)
{
	TCPSOCKET *tcps=(TCPSOCKET *)tcp;
	// Make single packet
	void *pkt=malloc(sizeof(int)+nDataLen);
	if(pkt==NULL) 
		return -1;

	// Send packet
	int ret;
	TIMEVAL tm;
	fd_set wfds;
	FD_ZERO(&wfds);
	FD_SET(tcps->s,&wfds);
	tm.tv_sec=5;
	tm.tv_usec=0;
	if((ret=select(0,NULL,&wfds,NULL,&tm))>0) {
		char *ppkt=(char *)pData;
		int count=nDataLen;
		do {
			ret=send(tcps->s,ppkt,count,0);
			if(ret==SOCKET_ERROR) break;
			count-=ret;
			ppkt+=ret;
			if(count>0) Sleep(20);
		} while(count>0);
		if(ret==SOCKET_ERROR) return -1;
		return 1;
	}
	char rn[]="\r\n";
	if((ret=select(0,NULL,&wfds,NULL,&tm))>0) {
		char *ppkt=(char *)rn;
		int count=2;
		do {
			ret=send(tcps->s,ppkt,count,0);
			if(ret==SOCKET_ERROR) break;

			count-=ret;
			ppkt+=ret;
			if(count>0) Sleep(20);
		} while(count>0);
		if(ret==SOCKET_ERROR) return -1;
		return 1;
	}
	return ret;

	/*
	TCPSOCKET *tcps=(TCPSOCKET *)tcp;
	// Make single packet
	void *pkt=malloc(sizeof(int)+nDataLen);
	if(pkt==NULL) 
		return -1;

	// Send packet length
	int sizeSend=9812321-nDataLen;
	
	memcpy(pkt,&sizeSend,sizeof(int));
	//memcpy(pkt,&nDataLen,sizeof(int));
	memcpy((BYTE *)pkt+sizeof(int),pData,nDataLen);
	
	// Send packet
	int ret;
	TIMEVAL tm;
	fd_set wfds;
	FD_ZERO(&wfds);
	FD_SET(tcps->s,&wfds);
	tm.tv_sec=5;
	tm.tv_usec=0;
	if((ret=select(0,NULL,&wfds,NULL,&tm))>0) {
		char *ppkt=(char *)pkt;
		int count=nDataLen+sizeof(int);
		do {
			ret=send(tcps->s,ppkt,count,0);
			if(ret==SOCKET_ERROR) break;

			count-=ret;
			ppkt+=ret;
			if(count>0) Sleep(20);
		} while(count>0);
		free(pkt);
		if(ret==SOCKET_ERROR) return -1;
		return 1;
	}
	free(pkt);
	return ret;
	*/
}








void * gs_classTcpIo::TCPIO_Connect(long  port,char *svHost)
{
	SOCKET s;
	s=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(s==INVALID_SOCKET) return NULL;

	BOOL sopt;
	sopt=TRUE;
	setsockopt(s,IPPROTO_TCP,TCP_NODELAY,(char *)&sopt,sizeof(BOOL));
	sopt=TRUE;
	setsockopt(s,SOL_SOCKET,SO_DONTLINGER,(char *)&sopt,sizeof(BOOL));
	

	// Get target port
	int nPort=port;	

	DWORD addr;
	if((addr=inet_addr(svHost))==INADDR_NONE) {
		struct hostent *he=gethostbyname(svHost);
		if(he==NULL) {
			closesocket(s);
			return NULL;
		}
		addr=*(DWORD *)(he->h_addr_list[0]);
	}

	// Create socket address
	SOCKADDR_IN saddr;
	memset(&saddr,0,sizeof(SOCKADDR_IN));
	saddr.sin_addr.S_un.S_addr=addr;
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons((WORD)nPort);
	
	// Connect to remote host
	if(connect(s,(SOCKADDR *)&saddr,sizeof(SOCKADDR_IN))!=0) {
		closesocket(s);
		return NULL;
	}
	
	// Allocate internal state structure
	TCPSOCKET *tcps=(TCPSOCKET *)malloc(sizeof(TCPSOCKET));
	if(tcps==NULL) {
		closesocket(s);
		return NULL;
	}
	
	tcps->s=s;
//	tcps->rmt=saddr;
	
	return tcps;
}


