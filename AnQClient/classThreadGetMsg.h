#if !defined(AFX_CLASSTHREADGETMSG_H__98270386_08DB_4F25_832D_0DFA5869DD4F__INCLUDED_)
#define AFX_CLASSTHREADGETMSG_H__98270386_08DB_4F25_832D_0DFA5869DD4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// classThreadGetMsg.h : header file
//

#include "gs_classTcpIo.h"
#include "tinyxml.h"
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/x509.h>
#include <openssl/pem.h>

#include "afxtempl.h"


/////////////////////////////////////////////////////////////////////////////
// classThreadGetMsg thread

class classThreadGetMsg : public CWinThread
{
	DECLARE_DYNCREATE(classThreadGetMsg)
public:
	classThreadGetMsg();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	CString GetAString();
	void Unlock();
	void Lock();
	TCPSOCKET *tcps;
	long m_lStatus;
	long m_stringsCount;
	CArray<CString,CString>m_strings;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(classThreadGetMsg)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~classThreadGetMsg();

	// Generated message map functions
	//{{AFX_MSG(classThreadGetMsg)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLASSTHREADGETMSG_H__98270386_08DB_4F25_832D_0DFA5869DD4F__INCLUDED_)
