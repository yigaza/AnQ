#if !defined(AFX_GS_CLASSFILETHREAD_H__E23F1E7B_8660_4F61_BB35_03688D0E6850__INCLUDED_)
#define AFX_GS_CLASSFILETHREAD_H__E23F1E7B_8660_4F61_BB35_03688D0E6850__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// gs_classFileThread.h : header file
//
#include "gs_classTcpIo.h"
#include "gs_classFileTranThread.h"

/////////////////////////////////////////////////////////////////////////////
// gs_classFileThread thread

class gs_classFileThread : public CWinThread
{
	DECLARE_DYNCREATE(gs_classFileThread)
public:
	gs_classFileThread();           // protected constructor used by dynamic creation
private:
// Attributes
public:
	TCPSOCKET *tcps;
	long isRun;
	long m_lMaxClient;
	long m_lClientCount;
	gs_classFileTranThread **m_pThread;
	CString _Msg;
// Operations
public:
	void Step();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(gs_classFileThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
public:
	void Unlock();
	void Lock();
	void _AddReceive(char *ch,long len,char *name);
	long SendMsg(char *to,char *ch,long len);
	long ClientAdd(gs_classFileTranThread *thread);
	void ClientCheckCanCancel();
	virtual ~gs_classFileThread();

	// Generated message map functions
	//{{AFX_MSG(gs_classFileThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GS_CLASSFILETHREAD_H__E23F1E7B_8660_4F61_BB35_03688D0E6850__INCLUDED_)
