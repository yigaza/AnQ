// TrayCalender.h : main header file for the TRAYCALENDER application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "SystemTray.h"
#include "dialogNew.h"
#include "dialogOPen.h"
#include "dialogFriendList.h"
#include "dialogSendMsg.h"

#include "stbSSLTalk.h"

#include "stbFriend.h"
#include "stbSSLOdd.h"
#include "classThreadGetMsg.h"


#define	WM_ICON_NOTIFY			WM_USER+10

/////////////////////////////////////////////////////////////////////////////
// CTrayCalenderApp:
// See TrayCalender.cpp for the implementation of this class
//

class CTrayCalenderApp : public CWinApp
{
// Operations
public:
	CTrayCalenderApp();

// Attributes
public:
	char * GetId(long &idLen);
	
	void _LoadSaveFriendList(long isSave=1);
	void ParseMsg(TiXmlNode *node,stbFriend *f);
	void SendMsg(stbFriend *f,const char *msg);
	void AddFriend(const char *nickName,const char *ne,const char *n,const char *e);
	void ParseFriendList(TiXmlNode *node);
	void LoadCharXML(TiXmlDocument *doc, char *ch, long len);
	void CheckMsg();
	long SendXML(TiXmlDocument *doc);
	long SendMe();
	long ConnectTo(char *ip, long port);
	void Reset();	
	stbSSLOdd odd;
	CString m_nickName;
	CString m_rsaName;
	RSA *m_rsa;

	TCPSOCKET *tcps;
	classThreadGetMsg threadGetMsg;

	stbFriend *friends[1000];
	long friendsCount;	

	CString m_strWindowName;		// Window name for application
	HICON   m_hIcon;				// icon for todays date


// Attributes
protected:
	BOOL FirstInstance();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrayCalenderApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation

	void GetApplicationSettings();

	//{{AFX_MSG(CTrayCalenderApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFindFriend();
	afx_msg void OnNew();
	afx_msg void OnOpen();
	afx_msg void OnSendMsg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CTrayCalenderApp theApp;


/////////////////////////////////////////////////////////////////////////////
