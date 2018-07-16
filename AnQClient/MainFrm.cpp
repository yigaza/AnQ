// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "TrayCalender.h"
#include "MainFrm.h"
#include "Splash.h"
#include "TrayCalenderOptions.h"
#include <afxdisp.h>    // COleDateTime

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_ICON_NOTIFY,     OnTrayNotification)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_DateCheckTimerID = 0;			// Timer ID for periodic date check recieved from "SetTimer"
	m_ShuffleTimerID = 0;			// Timer ID for initial reshuffle
 
	m_bInitialShuffleDone = FALSE;
    m_DateCheckTime = COleDateTime::GetCurrentTime();
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs) 
{	
	return CFrameWnd::PreCreateWindow(cs);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	// CG: The following line was added by the Splash Screen component.
//	CSplashWnd::ShowSplashScreen(this);

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CTime theTime = CTime::GetCurrentTime();
	CString strTime = theTime.Format(_T("%#x"));

	if (!m_TrayIcon.Create(this, WM_ICON_NOTIFY, strTime, theApp.m_hIcon, IDR_POPUP_MENU))
		return -1;
	
	TRACE0("Icon created successfully\n");

	SetWindowText(theApp.m_strWindowName);



	SetTimer(0,10,0);
//	SetWindowText("abc");

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

//DEL void CMainFrame::Shuffle()
//DEL {
//DEL 	m_TrayIcon.MoveToRight();
//DEL }

//DEL void CMainFrame::KillShuffleTimer()
//DEL {
//DEL 	if (m_ShuffleTimerID)
//DEL         KillTimer(ID_SHUFFLE_TIMER);
//DEL 	m_ShuffleTimerID = 0;
//DEL }

//DEL void CMainFrame::KillDateCheckTimer()
//DEL {
//DEL 	if (m_DateCheckTimerID) 
//DEL         KillTimer(ID_CHECKDATE_TIMER);
//DEL 	m_DateCheckTimerID = 0;
//DEL }

//DEL void CMainFrame::StartShuffleTimer()
//DEL {
//DEL     // Check it's not already going
//DEL //	if (m_ShuffleTimerID) 
//DEL  //       return;
//DEL 
//DEL //	m_ShuffleTimerID = SetTimer(ID_SHUFFLE_TIMER, theApp.m_nShuffleDelay*1000, 
//DEL //							    (TIMERPROC) NULL);
//DEL //    if (!m_ShuffleTimerID)
//DEL //		MessageBox(_T("Unable to get timer. Will not auto-reshuffle tray icon"));
//DEL }

void CMainFrame::GetDateCheckTime()
{
    // Get the time interval until midnight
    // I just don't trust windows on timers, so I've built in some
    // iterative tolerance.

    COleDateTime time = COleDateTime::GetCurrentTime();
    COleDateTime midnight = COleDateTime(time.GetYear(), time.GetMonth(), time.GetDay(),
                                         0,0,0) + COleDateTimeSpan(1,0,0,0);

    COleDateTimeSpan interval = midnight - time;
    if (interval.GetTotalMinutes() > 15.0)
    {
        TRACE1("Total hours till midnight = %0.0f\n", interval.GetTotalMinutes()/60);
        m_DateCheckTime = midnight - COleDateTimeSpan(0,0,1,0);
    }
    else if (interval.GetTotalMinutes() > 1.0)
    {
        TRACE1("Total minutes till midnight = %0.0f\n", interval.GetTotalMinutes());
        m_DateCheckTime = midnight - COleDateTimeSpan(0,0,0,10);
    }
    else 
        m_DateCheckTime = midnight + COleDateTimeSpan(0,0,0,1);
}

COleDateTimeSpan CMainFrame::GetTimeTillDateCheck()
{
    return m_DateCheckTime - COleDateTime::GetCurrentTime();
}

//DEL void CMainFrame::StartCheckDateTimer()
//DEL {
//DEL 	/*
//DEL     // Check that we should be checking for date change, and that 
//DEL     // it's not already going
//DEL //	if (!theApp.m_bCheckDate || m_DateCheckTimerID) 
//DEL //        return;
//DEL 
//DEL     GetDateCheckTime();
//DEL     COleDateTimeSpan delay = GetTimeTillDateCheck();
//DEL 
//DEL     DWORD dwNumSeconds = (DWORD) delay.GetTotalSeconds();
//DEL     TRACE1("Num seconds till timer tick = %d\n", dwNumSeconds);
//DEL 
//DEL 	m_DateCheckTimerID = SetTimer(ID_CHECKDATE_TIMER, dwNumSeconds*1000, (TIMERPROC) NULL);
//DEL     if (!m_DateCheckTimerID)
//DEL 		MessageBox(_T("Unable to get timer. Will not check date from now on."));
//DEL 		*/
//DEL }

//DEL void CMainFrame::Shutdown()
//DEL {
//DEL 	KillShuffleTimer();
//DEL 	KillDateCheckTimer();
//DEL 
//DEL 	TRACE0("Shutting down...\n");
//DEL 	PostMessage( WM_CLOSE, 0, 0 );
//DEL }

LRESULT CMainFrame::OnTrayNotification(WPARAM wParam, LPARAM lParam)
{
    // Uncomment this if you want to add the time that the date will
    // next be checked to the context menu.

    /*
    // Clicking with right button brings up a context menu
    if (LOWORD(lParam) == WM_RBUTTONUP)
    {    
        // Get "Check Date" menu item
        CMenu menu;
        if (!menu.LoadMenu(IDR_POPUP_MENU))
            return 0;
        
        CMenu* pSubMenu = menu.GetSubMenu(0);
        if (!pSubMenu)
            return 0;

        CString strMenuItem;
        pSubMenu->GetMenuString(ID_CHECK_DATE, strMenuItem, MF_BYCOMMAND);

        // Get time till midnight
        COleDateTime time = COleDateTime::GetCurrentTime();
        COleDateTime midnight = COleDateTime(time.GetYear(), time.GetMonth(), time.GetDay(),
                                         0,0,0) + COleDateTimeSpan(1,0,0,0);

        COleDateTimeSpan interval = midnight - time;

        // Add a time at next check to the ID_CHECK_DATE menu item
        CString strAddition;
        int nHour = m_DateCheckTime.GetHour();
        if (nHour <= 12)
            strAddition.Format(_T(" (%d:%02d AM)"), nHour, m_DateCheckTime.GetMinute(),
                               m_DateCheckTime.GetSecond());
        else
            strAddition.Format(_T(" (%d:%02d PM)"), nHour-12, m_DateCheckTime.GetMinute(),
                               m_DateCheckTime.GetSecond());

        strMenuItem += strAddition;

        ::SetMenuDefaultItem(pSubMenu->m_hMenu, 0, TRUE);
        pSubMenu->ModifyMenu(ID_CHECK_DATE, MF_BYCOMMAND|MF_STRING, ID_CHECK_DATE,
                             strMenuItem);

        // Display and track the popup menu
        CPoint pos;
        GetCursorPos(&pos);

        SetForegroundWindow();  
        ::TrackPopupMenu(pSubMenu->m_hMenu, 0, pos.x, pos.y, 0, GetSafeHwnd(), NULL);

        // BUGFIX: See "PRB: Menus for Notification Icons Don't Work Correctly"
        PostMessage(WM_NULL, 0, 0);

        menu.DestroyMenu();
        return 1;
    } 
    else
        */
    	return m_TrayIcon.OnTrayNotification(wParam, lParam);
}



//DEL void CMainFrame::CheckDate()
//DEL {
//DEL 	TRACE0("Checking date\n");
//DEL 
//DEL 	HICON hIcon = theApp.CheckDate();
//DEL 	if (hIcon) 						    // New icon, which means a new day
//DEL     {
//DEL 		CTime theTime = CTime::GetCurrentTime();
//DEL 		CString strTime = theTime.Format(_T("%#x"));
//DEL 
//DEL 		m_TrayIcon.SetIcon(hIcon);
//DEL 		m_TrayIcon.SetTooltipText(strTime);
//DEL 	}
//DEL }



//DEL void CMainFrame::OnTimeChange() 
//DEL {
//DEL 	CFrameWnd::OnTimeChange();
//DEL 	CheckDate();
//DEL 	KillDateCheckTimer();   // Restart the time with a new delay
//DEL     StartCheckDateTimer();
//DEL }

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	static tickCount=0;
	theApp.CheckMsg();

	
	if(tickCount>=100){
		tickCount=0;
		if(theApp.m_nickName==""){
			m_TrayIcon.SetTooltipText("请选择或新建一个身份");	
		}
		else{
			m_TrayIcon.SetTooltipText(theApp.m_nickName);	
		}
	}
	tickCount=tickCount+1;
	CFrameWnd::OnTimer(nIDEvent);
}
