; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=dialogSendMsg
LastTemplate=CWinThread
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TrayCalender.h"
LastPage=0

ClassCount=12
Class1=CTrayCalenderApp
Class2=CMainFrame
Class3=CAboutDlg

ResourceCount=11
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CSplashWnd
Resource3=IDD_DIALOG_OPEN
Resource4=IDD_DIALOG_SendMsg
Class5=CTrayCalenderOptions
Class6=dialogSendMsg
Resource5=IDD_DIALOG_Friend_List
Resource6=IDD_DIALOG_FIND_PEOPLE
Resource7=IDR_POPUP_MENU
Resource8=IDD_DIALOG_New
Resource9=IDD_DIALOG_firend_name
Resource10=IDD_OPTIONS_DIALOG
Class7=dialogOpen
Class8=dialogNew
Class9=dialogFriendList
Class10=dialogFriendName
Class11=dialogFindPeople
Class12=classThreadGetMsg
Resource11=IDR_MAINFRAME (English (U.S.))

[CLS:CTrayCalenderApp]
Type=0
HeaderFile=TrayCalender.h
ImplementationFile=TrayCalender.cpp
Filter=N
LastObject=CTrayCalenderApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CFrameWnd
VirtualFilter=fWC



[CLS:CAboutDlg]
Type=0
HeaderFile=TrayCalender.cpp
ImplementationFile=TrayCalender.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_TRICK

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=3
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Command1=ID_APP_EXIT
Command2=ID_APP_ABOUT
CommandCount=2

[CLS:CSplashWnd]
Type=0
HeaderFile=Splash.h
ImplementationFile=Splash.cpp
BaseClass=CWnd

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_APP_ABOUT
CommandCount=2

[CLS:CTrayCalenderOptions]
Type=0
HeaderFile=TrayCalenderOptions.h
ImplementationFile=TrayCalenderOptions.cpp
BaseClass=CDialog
Filter=D
LastObject=CTrayCalenderOptions
VirtualFilter=dWC

[DLG:IDD_OPTIONS_DIALOG]
Type=1
Class=?
ControlCount=8
Control1=IDC_SHUFFLE_DELAY,edit,1350631552
Control2=IDC_AUTOSHUFFLE_SPIN,msctls_updown32,1342177334
Control3=IDC_AUTO_SHUFFLE,button,1342242819
Control4=IDC_CHECK_DATE,button,1342242819
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816
Control7=IDC_AS_STATIC,static,1342308352
Control8=IDC_ASS_STATIC,static,1342308352

[DLG:IDD_DIALOG_FIND_PEOPLE]
Type=1
Class=dialogFindPeople
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST_PeopleList,listbox,1352728835

[DLG:IDD_DIALOG_firend_name]
Type=1
Class=dialogFriendName
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT2,edit,1350631552

[DLG:IDD_DIALOG_Friend_List]
Type=1
Class=dialogFriendList
ControlCount=3
Control1=IDC_LIST2,listbox,1352728843
Control2=IDOK,button,1342242816
Control3=IDCANCEL,button,1342242816

[DLG:IDD_DIALOG_New]
Type=1
Class=dialogNew
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=65535,static,1342308352
Control4=65535,static,1342308352
Control5=IDC_EDIT_pass,edit,1350631584
Control6=65535,static,1342308352
Control7=IDC_EDIT_pass2,edit,1350631584
Control8=65535,static,1342308352
Control9=IDC_EDIT_len,edit,1350639744
Control10=IDC_EDIT1,edit,1350631552

[DLG:IDD_DIALOG_OPEN]
Type=1
Class=dialogOpen
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,listbox,1352728835
Control4=65535,static,1342308352
Control5=IDC_EDIT_pass,edit,1350631584

[DLG:IDD_DIALOG_SendMsg]
Type=1
Class=dialogSendMsg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_history,edit,1350633668
Control4=IDC_EDIT_msg,edit,1350631620
Control5=IDC_COMBO_listFriend,combobox,1344340226

[CLS:dialogSendMsg]
Type=0
HeaderFile=dialogSendMsg.h
ImplementationFile=dialogSendMsg.cpp
BaseClass=CDialog
Filter=D
LastObject=dialogSendMsg
VirtualFilter=dWC

[MNU:IDR_POPUP_MENU]
Type=1
Class=?
Command1=ID_NEW
Command2=ID_OPEN
Command3=ID_Find_Friend
Command4=ID_SendMsg
Command5=ID_APP_ABOUT
Command6=ID_APP_EXIT
CommandCount=6

[CLS:dialogOpen]
Type=0
HeaderFile=dialogOpen.h
ImplementationFile=dialogOpen.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=65535

[CLS:dialogNew]
Type=0
HeaderFile=dialogNew.h
ImplementationFile=dialogNew.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_NEW

[CLS:dialogFriendList]
Type=0
HeaderFile=dialogFriendList.h
ImplementationFile=dialogFriendList.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=dialogFriendList

[CLS:dialogFriendName]
Type=0
HeaderFile=dialogFriendName.h
ImplementationFile=dialogFriendName.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[CLS:dialogFindPeople]
Type=0
HeaderFile=dialogFindPeople.h
ImplementationFile=dialogFindPeople.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_LIST_PeopleList

[CLS:classThreadGetMsg]
Type=0
HeaderFile=classThreadGetMsg.h
ImplementationFile=classThreadGetMsg.cpp
BaseClass=CWinThread
Filter=N

