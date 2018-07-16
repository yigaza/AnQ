#if !defined(AFX_GS_CLASSFILETRANTHREAD_H__609E28D9_8F77_4F06_A367_F9FBDF4A26F8__INCLUDED_)
#define AFX_GS_CLASSFILETRANTHREAD_H__609E28D9_8F77_4F06_A367_F9FBDF4A26F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// gs_classFileTranThread.h : header file
//

#include "gs_classTcpIo.h"
#include "..\zzTest\tinyxml.h"
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/x509.h>
#include <openssl/pem.h>



/////////////////////////////////////////////////////////////////////////////
// gs_classFileTranThread thread

class gs_classFileTranThread : public CWinThread
{
	DECLARE_DYNCREATE(gs_classFileTranThread)
public:
	gs_classFileTranThread();           // protected constructor used by dynamic creation


// Attributes
public:
	void *root;
	long m_lStatus;
	TCPSOCKET *tcps;
	char *name;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(gs_classFileTranThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
public:
	long SendFriendList();
	long SendMsg(char *ch, long len);
	void LoadCharXML(TiXmlDocument *doc,char *ch,long len);
	long CheckMsg(char *ch,long len);
	void Cancel();
	long IsStop();
	virtual ~gs_classFileTranThread();

	// Generated message map functions
	//{{AFX_MSG(gs_classFileTranThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GS_CLASSFILETRANTHREAD_H__609E28D9_8F77_4F06_A367_F9FBDF4A26F8__INCLUDED_)
