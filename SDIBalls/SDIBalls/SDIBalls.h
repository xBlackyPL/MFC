#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"

class CSDIBallsApp : public CWinApp
{
public:
	CSDIBallsApp() noexcept;
	BOOL InitInstance() override;
	int ExitInstance() override;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSDIBallsApp app;