#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "ComplexNumberCalculator.h"
#include "MainFrm.h"

#include "ComplexNumberCalculatorDoc.h"
#include "ComplexNumberCalculatorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CComplexNumberCalculatorApp, CWinApp)
		ON_COMMAND(ID_APP_ABOUT, &CComplexNumberCalculatorApp::OnAppAbout)
		ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
		ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()

CComplexNumberCalculatorApp::CComplexNumberCalculatorApp() noexcept
{
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif
	SetAppID(_T("ComplexNumberCalculator.AppID.NoVersion"));
}

CComplexNumberCalculatorApp app;

BOOL CComplexNumberCalculatorApp::InitInstance()
{
	INITCOMMONCONTROLSEX initial_controls;
	initial_controls.dwSize = sizeof(initial_controls);
	initial_controls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&initial_controls);

	CWinApp::InitInstance();

	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);

	const auto doc_template = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CComplexNumberCalculatorDoc),
		RUNTIME_CLASS(CMainFrame),
		RUNTIME_CLASS(CComplexNumberCalculatorView));
	if (!doc_template)
	{
		return FALSE;
	}
	AddDocTemplate(doc_template);

	CCommandLineInfo cmd_info;
	ParseCommandLine(cmd_info);
	if (!ProcessShellCommand(cmd_info))
	{
		return FALSE;
	}
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

int CComplexNumberCalculatorApp::ExitInstance()
{
	AfxOleTerm(FALSE);
	return CWinApp::ExitInstance();
}

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	void DoDataExchange(CDataExchange* data_exchange) override;
DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* data_exchange)
{
	CDialogEx::DoDataExchange(data_exchange);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

void CComplexNumberCalculatorApp::OnAppAbout()
{
	CAboutDlg about_dlg;
	about_dlg.DoModal();
}
