#pragma once


class CCalculatorDlg : public CDialog
{
	DECLARE_DYNAMIC(CCalculatorDlg)

public:
	CCalculatorDlg(CWnd* parent = nullptr); 
	virtual ~CCalculatorDlg();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CCalculatorDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* data_exchange);

	DECLARE_MESSAGE_MAP()
};
