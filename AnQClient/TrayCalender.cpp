// TrayCalender.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"

#include "TrayCalender.h"
#include "MainFrm.h"
#include "Splash.h"

#include "time.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Define the Section and Keys to use for registry storage
LPCTSTR szSection       = _T("Settings");
LPCTSTR szAutoShuffle   = _T("Auto shuffle");
LPCTSTR szShuffleDelay  = _T("Shuffle delay");
LPCTSTR szCheckDate     = _T("Check date");


/////////////////////////////////////////////////////////////////////////////
// CTrayCalenderApp

BEGIN_MESSAGE_MAP(CTrayCalenderApp, CWinApp)
	//{{AFX_MSG_MAP(CTrayCalenderApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_Find_Friend, OnFindFriend)
	ON_COMMAND(ID_NEW, OnNew)
	ON_COMMAND(ID_OPEN, OnOpen)
	ON_COMMAND(ID_SendMsg, OnSendMsg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrayCalenderApp construction

CTrayCalenderApp::CTrayCalenderApp()
{
	m_strWindowName		 = _T("AnQ");	// Window/Application name


	time_t t=time(0);
	long tick=GetTickCount();
	RAND_bytes((unsigned char *)(&t),sizeof(time_t));
	RAND_bytes((unsigned char *)(&tick),sizeof(long));

	gs_classTcpIo::TCPIO_Insert();

	
	threadGetMsg.CreateThread();
	

//	friendsCount=0;

	//int RAND_event(UINT, WPARAM, LPARAM);
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTrayCalenderApp object

CTrayCalenderApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTrayCalenderApp initialization

BOOL CTrayCalenderApp::FirstInstance()
{
	// Determine if another window with our class name exists...
	CWnd *PrevCWnd = CWnd::FindWindow(NULL, m_strWindowName);
	return (PrevCWnd == NULL);
}

void CTrayCalenderApp::GetApplicationSettings()
{
//	m_bAutoShuffle		 = GetProfileInt(szSection, szAutoShuffle,   m_bAutoShuffle);
//	m_nShuffleDelay		 = GetProfileInt(szSection, szShuffleDelay,  m_nShuffleDelay);
//	m_bCheckDate		 = GetProfileInt(szSection, szCheckDate,     m_bCheckDate);
}



BOOL CTrayCalenderApp::InitInstance()
{
	//if (!FirstInstance())
	//	return FALSE;

	SetRegistryKey(_T("AnQ"));

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
//	CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);

//	m_StartTime = CTime::GetCurrentTime();

//	m_CurrentDay = m_StartTime.GetDay(); // 1-31

	//m_hIcon = LoadIcon(IDI_ICON1+m_CurrentDay-1);
	m_hIcon = LoadIcon(IDR_MAINFRAME);	
	if (m_hIcon == NULL)
	{
		AfxMessageBox(_T("Unable to get todays icon."));
		return FALSE;
	}

	GetApplicationSettings();

	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// For debugging (or something...)
	//pMainFrame->ActivateFrame();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

#include "HyperLink.h"

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

/*	m_MailButton.SetURL(_T("mailto:chrismaunder@codeguru.com"));

	m_MailButton.SetColours(m_MailButton.GetLinkColour(),m_MailButton.GetLinkColour());
	m_MailButton.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND));
*/
	
	::SetCursor(::LoadCursor(NULL, IDC_ARROW));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// App command to run the dialog
void CTrayCalenderApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CTrayCalenderApp commands

// Called when the application gets its death sentence.
int CTrayCalenderApp::ExitInstance() 
{
	DestroyIcon(m_hIcon);							// ditch the icon
	return CWinApp::ExitInstance();					// get outta here
}



void CTrayCalenderApp::OnFindFriend() 
{
	TiXmlDocument doc;
	TiXmlElement e("Msg");
	e.SetAttribute("GetFriendList","");
	doc.InsertEndChild(e);
	SendXML(&doc);	
	
}

void CTrayCalenderApp::OnNew() 
{
	dialogNew dlg;
	if(IDOK==dlg.DoModal()){		
		RSA *r=odd.GenRSA(dlg.m_len);
		if(r==0){
			AfxMessageBox("产生密钥对不成功");
			return;
		}
		Reset();
		m_rsa=r;
		dlg.m_name=dlg.m_name+".pem";
		m_nickName=dlg.m_name;
		char name[4096],pass[4096];
		strcpy(name,dlg.m_name);
		strcpy(pass,dlg.m_pass);
		odd.SaveRSA(name,pass,r);
		dlg.m_pass="                                                                                                                                                                                                                   ";
		AfxMessageBox("成功生成身份");
		//RSA_blinding_on
	};	
	
}

void CTrayCalenderApp::OnOpen() 
{
	for(;;)
	{	
		dialogOpen dlg;
		if(dlg.DoModal()==IDOK){
			RSA *r=RSA_new();
			CString tmp=dlg.m_list;
			tmp=tmp+".pem";
			char sz[4096],sz1[4096];
			strcpy(sz,tmp);strcpy(sz1,dlg.m_pass);
			if(odd.LoadRSA(sz,sz1,r)){
				RSA_free(r);
				AfxMessageBox("密码错误.");
				continue;
			}else{
				Reset();
				m_nickName=dlg.m_list;
				m_rsa=r;
				m_rsaName=odd.GetNameByRSA(m_rsa);
				_LoadSaveFriendList(0);
			//	ConnectTo("freemap.3322.org",8877);
				ConnectTo("127.0.0.1",8877);
				SendMe();
				break;
			};

/*			RSA *r=odd.GenRSA(dlg.m_len);
			if(r==0){
				AfxMessageBox("产生密钥对不成功");
				return;
			}
			Reset();
			m_rsa=r;
			dlg.m_name=dlg.m_name+".pem";
			m_name=dlg.m_name;
			char name[4096],pass[4096];
			strcpy(name,dlg.m_name);
			strcpy(pass,dlg.m_pass);
			odd.SaveRSA(name,pass,r);
			dlg.m_pass="                                                                                                                                                                                                                   ";
			AfxMessageBox("成功生成身份");
			*/
		}
		else break;
	}
}

void CTrayCalenderApp::OnSendMsg() 
{
	//设计上应该根据RSA,而不是名字来选择
	dialogSendMsg dlg;
	
	dlg.DoModal();
}

BOOL CTrayCalenderApp::PreTranslateMessage(MSG* pMsg) 
{		

	RAND_event(pMsg->message,pMsg->wParam,pMsg->lParam);	
	RAND_bytes((unsigned char *)(&(pMsg->time)),sizeof((pMsg->time)));

	return CWinApp::PreTranslateMessage(pMsg);
}

void CTrayCalenderApp::Reset()
{
	if(m_rsa){
		RSA_free(m_rsa);
		m_rsa=0;
	}
	for(long i=0;i<friendsCount;i++){
		delete friends[i];
	}
}

long CTrayCalenderApp::ConnectTo(char *ip, long port)
{
	gs_classTcpIo::TCPIO_Close(tcps);
	tcps=0;
	tcps=(TCPSOCKET *)gs_classTcpIo::TCPIO_Connect(port,ip);
	threadGetMsg.Lock();
		threadGetMsg.tcps=tcps;
	threadGetMsg.Unlock();
	return 0;
}

long CTrayCalenderApp::SendMe()
{
	TiXmlDocument doc;
	TiXmlElement e("Msg");
	e.SetAttribute("Name",m_rsaName);
	e.SetAttribute("NickName",m_nickName);
	doc.InsertEndChild(e);
	return SendXML(&doc);
	return 0;
}

long CTrayCalenderApp::SendXML(TiXmlDocument *doc)
{
	char sza[100];
	sprintf(sza,"vr2temp%ld.xml",this);
	doc->SaveFile(sza);
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

	
	sz[len]=0;
	CString s;
	s=sz;
	free(sz);
	s.Replace("\r\n","");
	s.Replace("\n","");	
	s=s+"\r\n";
	len=s.GetLength();
	sz=(char *)malloc(1024*1024);
	strcpy(sz,s);
	

	//sz[len]=0;len++;
	long status=0;
	if(tcps==0)
	{
		AfxMessageBox("没有可用连接");
	}
	else
	{
//		char szz[]="sadfal;sdfjlasd";
//		status=gs_classTcpIo::TCPIO_Send(tcps,szz,4);
		status=gs_classTcpIo::TCPIO_Send(tcps,sz,len);
	}
	
	
	BIO_free(out);	
	free(sz);
	if(status<0)return 1;
	return 0;
}

//DEL char * CTrayCalenderApp::WaitAMsg()
//DEL {
//DEL 	char *ch;int len;
//DEL 	for(;;){
//DEL 		long p=gs_classTcpIo::TCPIO_Recv(tcps,(void **)&ch,&len);
//DEL 		if(p<0)break;
//DEL 		if(len&&p==1)
//DEL 		{
//DEL 			return ch;
//DEL 		}
//DEL 		Sleep(200);
//DEL 	}
//DEL }

void CTrayCalenderApp::CheckMsg()
{
	CString s;
	if(threadGetMsg.m_stringsCount){		
		s=threadGetMsg.GetAString();	
	}
	if(s=="")return;

	TiXmlDocument doc;
	long len=s.GetLength();
	char *szTemp=(char *)malloc(len+1);
	strcpy(szTemp,s);
	LoadCharXML(&doc,szTemp,len);
	free(szTemp);
	TiXmlNode *node=doc.FirstChild("Msg");
	if(node==0)return;
	TiXmlElement* e =node->ToElement(); //  .FirstChild( "Msg").Element();
	if(e==0)return;
	TiXmlNode *node1=e->FirstChild("FriendList");
	if(node1)
	{
		ParseFriendList(node1);
		return;
	}
	{		
		TiXmlElement* e1 =node->ToElement();
		char *sz;sz=(char *)e1->Attribute("From");
		if(sz[0]!=0){
			stbFriend *f=0;
			for(long i=0;i<friendsCount;i++)
			{
				if(strcmp(friends[i]->name,sz)==0){
					f=friends[i];
					break;
				}
			}
			node1=e->FirstChild("Msg");
			if(node1)
			{
				ParseMsg(node1,f);
				return;
			}
		}		
	}
	
	
	/*
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
	}*/
		
		
		
	

		/*
		<?xml version="1.0" ?><Msg><FriendList><Friend Name="C87FCEEE4CE7CFFA532C7798EAC
9B9EEB19B565221DB4D35EAAED262A63F64E3014E8F692539A1192E0AC999F00585B2D96997BD1AC
B5E9CB56C37A2A357B364638ED5E74EC4EB7F57F391B8D795F47D7B49484987CB4C33E42BE481714
B7A76724F9E39043048900D82DD5B9038FFE83C0303F2AEA614C2BB18D1695B231EB49D1D4A83E68
E94B83B30CF26D4F476F49926F65706A7426995227581213B2CC2D39A0295C11D9AB0AF4E575F5BB
869B1642C0B898D9FCE6A8DD5A591E618DC7D67CF2446292D3A959C44A7086CD5397B1FD61F3634E
3A15F7A303B8B211C07C8466087E5CED29693F7D67455837EC5AA370AE3ECCFA259F140BE19D8CFD
26DCB-010001" NickName="bb"/></FriendList></Msg>
*/
		//AfxMessageBox(s);
	
}



void CTrayCalenderApp::LoadCharXML(TiXmlDocument *doc, char *ch, long len)
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

void CTrayCalenderApp::ParseFriendList(TiXmlNode *node)
{
	dialogFriendList dlg;
	TiXmlNode *prev=0;
	for(;;){
		TiXmlNode *node1;
		if(prev==0){
			node1=node->FirstChild();			
		}
		else
		{
			node1=node->IterateChildren(prev);
		}
		prev=node1;
		if(node1==0)break;
		TiXmlElement* e1 =node1->ToElement();
		char *sz;
		char *sz1;
		sz=(char *)e1->Attribute("Name");
		if(sz[0]==0)continue;		
		sz1=(char *)e1->Attribute("NickName");
		dlg.AddFriend(sz,sz1);		
		if(prev==0)break;			
	}
	dlg.DoModal();	
	_LoadSaveFriendList(1);
	/*
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
		*/
}

void CTrayCalenderApp::AddFriend(const char *nickName,const char *ne,const char *n,const char *e)
{
	if(friendsCount>=1000)return;
	stbFriend *f=new stbFriend;
	f->rsa=RSA_new();
	long len=strlen(nickName);
	f->nickName=(char *)malloc(len+1);
	memcpy(f->nickName,nickName,len+1);

	len=strlen(ne);
	f->name=(char *)malloc(len+1);
	memcpy(f->name,ne,len+1);

	BN_hex2bn(&(f->rsa->n),n);
	BN_hex2bn(&(f->rsa->e),e);

	for(long i=0;i<friendsCount;i++){
		if(friends[i]->IsEqual(f))
		{
			delete f;
			return;
		}
	}

	friends[friendsCount]=f;
	friendsCount++;

	//c1=BN_bn2hex(rsa->n);
	//c2=BN_bn2hex(rsa->e);
	//stbFriend *friends[1000];
	//long friendsCount;
}

void CTrayCalenderApp::SendMsg(stbFriend *f, const char *msg)
{	
	if(f==0)return;
	
	TiXmlDocument doc;
	TiXmlElement e("Msg");
	e.SetAttribute("From",m_rsaName);
	e.SetAttribute("To",f->name);
	doc.InsertEndChild(e);
	TiXmlElement *root=doc.RootElement();
	TiXmlElement ee("Msg");

	{		
		char *idTemp,id[100],*id1;long idLen;		
		idTemp=GetId(idLen);
		memcpy(id,idTemp,idLen);
		id1=stbSSLTalk::GetIdRand(id,idLen);
		char *idString=stbSSLTalk::GetHexString(id,idLen);
		
		long allLen=strlen(msg)+idLen*2;
		char *msg1=(char *)malloc(allLen);
		memcpy(msg1,id1,idLen*2);
		memcpy(msg1+idLen*2,msg,allLen-idLen*2);

		int lenOut;
		char *out=odd.EncryptByTwoRSA((char *)msg1,allLen,&lenOut,m_rsa,f->rsa);//EncryptByTwoRSA()
		
		if(lenOut==0){
			free(idString);free(msg1);free(id1);
			return;
		}

		char *cc=stbSSLTalk::GetHexString(out,lenOut);
	//	AfxMessageBox(cc);
	//	long l=GetHexStringRevers(cc);
		ee.SetAttribute("Msg",cc);

		ee.SetAttribute("Id",idString);

		free(idString);free(msg1);free(id1);
		free(out);
		free(cc);
	}
	
//	ee.SetAttribute("Msg",msg);
	root->InsertEndChild(ee);

	SendXML(&doc);

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
	long status=gs_classTcpIo::TCPIO_Send(tcps,sz,len);
	
	BIO_free(out);	
	free(sz);
	if(status<0)return;
	*/
	return;
}

void CTrayCalenderApp::ParseMsg(TiXmlNode *node1,stbFriend *f)
{	
	TiXmlElement* e1 =node1->ToElement();
	char *szIdTemp;long lenId;
	szIdTemp=(char *)e1->Attribute("Id");
	if(szIdTemp[0]){
		lenId=strlen(szIdTemp);
		if(lenId>=256)return;if(lenId %2 ==1)return;
		char szId[256],szId1[512];
		long lenId=strlen(szIdTemp);
		memcpy(szId,szIdTemp,lenId+1);
		stbSSLTalk::GetHexStringRevers(szId);
		lenId=lenId/2;
		char *szTemp,*sz;
		szTemp=(char *)e1->Attribute("Msg");
		if(szTemp){
			{				
				long lenszTemp=strlen(szTemp);
				sz=(char *)malloc(lenszTemp+1);
				memcpy(sz,szTemp,lenszTemp+1);
				long l=stbSSLTalk::GetHexStringRevers(sz);
				int lenOut;			
				char *cOut=odd.DecryptByTwoRSA(sz,l,&lenOut,m_rsa,f->rsa);				
				if(lenOut){
					if(lenOut<=lenId)
					{
						free(cOut);free(sz);
						return ;
					}
					memcpy(szId1,cOut,lenId*4);
					stbSSLTalk::GetIdRandReverse(szId1,lenId*2);
					if(memcmp(szId1,szId,lenId)==0)
					{
						cOut[lenOut]=0;					
						CString s;
						s.Format("从%s发来的消息:\r\n%s",f->nickName,cOut+lenId*2);
						AfxMessageBox(s);					
					}
					free(cOut);free(sz);
					/*cOut[lenOut]=0;
					CString s;
					s.Format("从%s发来的消息:\r\n%s",f->nickName,cOut);
					AfxMessageBox(s);
					*/
				}
			}
		}
	}
	else
	{	
		char *sz;
		sz=(char *)e1->Attribute("Msg");
		if(sz){
			{
				long l=stbSSLTalk::GetHexStringRevers(sz);		
				int lenOut;			
				char *cOut=odd.DecryptByTwoRSA(sz,l,&lenOut,m_rsa,f->rsa);
				if(lenOut){
					cOut[lenOut]=0;		
					CString s;
					s.Format("从%s发来的消息:\r\n%s",f->nickName,cOut);
					AfxMessageBox(s);
				}
				free(cOut);
			}
		}
	}
}

void CTrayCalenderApp::_LoadSaveFriendList(long isSave)
{
	CString s;
	s=m_nickName+".friends";
	if(isSave){
	//	CFile file;
	//	file.Open("friendList.xml",CFile::modeCreate|CFile::modeWrite,0);
		
		TiXmlDocument doc;		
		TiXmlElement e("Friends");
		e.SetAttribute("FriendsCount",friendsCount);				
		for(long i=0;i<friendsCount;i++){
			TiXmlElement ee("Friend");
			ee.SetAttribute("Name",friends[i]->name);			
			ee.SetAttribute("NickName",friends[i]->nickName);			
			e.InsertEndChild(ee);						
		}				
		doc.InsertEndChild(e);
		doc.SaveFile(s);		
		//return SendXML(&doc);
	}
	else
	{		
		TiXmlDocument doc;		
		doc.LoadFile(s);			
		TiXmlNode *node=doc.FirstChild("Friends");
		if(node==0)return;
		TiXmlNode *prev=0;
		for(;;){
			TiXmlNode *node1;
			if(prev==0){
				node1=node->FirstChild("Friend");
			}
			else
			{
				node1=node->IterateChildren("Friend",prev);
			}
			prev=node1;
			if(node1==0)break;
			TiXmlElement* e1 =node1->ToElement();
			char *sz;
			char *sz1;
			sz=(char *)e1->Attribute("Name");
			if(sz[0]==0)continue;		
			sz1=(char *)e1->Attribute("NickName");
		
			{	
				CString s,sb,sc;
				s=sz;				
				long i=s.Find("-");
				sb=s.Left(i);
				sc=s.Right(s.GetLength()-i-1);
				this->AddFriend(sz1,sz,sb,sc);
			//	this->Add
			//app->AddFriend((LPCSTR)sa,(LPCSTR)sne,(LPCSTR)sb,(LPCSTR)sc);		

			}
		

			//dlg.AddFriend(sz,sz1);		
			if(prev==0)break;			
		}
	}	
}

char * CTrayCalenderApp::GetId(long &idLen)
{
	static BYTE idchar[100];
	static long idNow=0;
	long t=time(0);
	idNow++;
	idLen=8;	
	memcpy(idchar,&idNow,4);
	memcpy(idchar+4,&t,sizeof(t));	
	return (char *)idchar;
}
