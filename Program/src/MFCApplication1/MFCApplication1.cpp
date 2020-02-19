
// MFCApplication1.cpp: 定义应用程序的类行为。
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1App

BEGIN_MESSAGE_MAP(CMFCApplication1App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCApplication1App 

CMFCApplication1App::CMFCApplication1App()
{
	// restart manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
}


// Singleton of CMFCApplication1App object

CMFCApplication1App theApp;


// CMFCApplication1App initilization

BOOL CMFCApplication1App::InitInstance()
{

	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// create shell manager
	CShellManager *pShellManager = new CShellManager;

	// active “Windows Native” visual manager in order to start it in MFC
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	SetRegistryKey(_T("Start Local App"));

	CMFCApplication1Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// some handling
	}
	else if (nResponse == IDCANCEL)
	{
		// some handling
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: Failure of start\n");
		TRACE(traceAppMsg, 0, "Warning: if you start MFC controller in chatbox，then #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// delete the shell manager above
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// return false when end
	return FALSE;
}

