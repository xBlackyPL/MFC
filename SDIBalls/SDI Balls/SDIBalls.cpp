#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "SDIBalls.h"
#include "MainFrm.h"
#include "SDIBallsDoc.h"
#include "SDIBallsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(SDIBallsApp, CWinApp)
		ON_COMMAND(ID_APP_ABOUT, &SDIBallsApp::OnAppAbout)
		ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
		ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


SDIBallsApp::SDIBallsApp() noexcept
{
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	SetAppID(_T("SDIBalls.AppID.NoVersion"));
}

SDIBallsApp app;

BOOL SDIBallsApp::InitInstance()
{
	INITCOMMONCONTROLSEX init_ctrl;
	init_ctrl.dwSize = sizeof(init_ctrl);
	init_ctrl.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&init_ctrl);

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
		RUNTIME_CLASS(SDIBallsDoc),
		RUNTIME_CLASS(CMainFrame),
		RUNTIME_CLASS(SDIBallsView));

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

int SDIBallsApp::ExitInstance()
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
	void DoDataExchange(CDataExchange* p_dx) override;
DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* p_dx)
{
	CDialogEx::DoDataExchange(p_dx);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

void SDIBallsApp::OnAppAbout()
{
	CAboutDlg about_dlg;
	about_dlg.DoModal();
}
