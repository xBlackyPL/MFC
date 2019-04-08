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


BEGIN_MESSAGE_MAP(CSDIBallsApp, CWinApp)
		ON_COMMAND(ID_APP_ABOUT, &CSDIBallsApp::OnAppAbout)
		ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
		ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


CSDIBallsApp::CSDIBallsApp() noexcept
{
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	SetAppID(_T("SDIBalls.AppID.NoVersion"));
}

CSDIBallsApp app;

BOOL CSDIBallsApp::InitInstance()
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
		RUNTIME_CLASS(CSDIBallsDoc),
		RUNTIME_CLASS(CMainFrame),
		RUNTIME_CLASS(CSDIBallsView));
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

int CSDIBallsApp::ExitInstance()
{
	AfxOleTerm(FALSE);
	return CWinApp::ExitInstance();
}

class CAboutDlg : public CDialogEx
{
protected:
	void DoDataExchange(CDataExchange* data_exchange) override;
DECLARE_MESSAGE_MAP()

public:
	CAboutDlg() noexcept;
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif
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

void CSDIBallsApp::OnAppAbout()
{
	CAboutDlg about_dlg;
	about_dlg.DoModal();
}
