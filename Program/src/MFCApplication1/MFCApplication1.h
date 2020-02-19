
// MFCApplication1.h: PROJECT_NAME header file

#pragma once

#ifndef __AFXWIN_H__
	#error "preinclude “stdafx.h” to generate PCH files"
#endif

#include "resource.h"		// main symbol


// CMFCApplication1App:

class CMFCApplication1App : public CWinApp
{
public:
	CMFCApplication1App();

public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication1App theApp;
