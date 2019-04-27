#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"

class CComplexNumberCalculatorApp : public CWinApp
{
public:
	CComplexNumberCalculatorApp() noexcept;
	BOOL InitInstance() override;
	int ExitInstance() override;

	afx_msg void OnAppAbout();
DECLARE_MESSAGE_MAP()
	afx_msg void OnCalculator();
};

extern CComplexNumberCalculatorApp app;
