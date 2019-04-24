#include "stdafx.h"
#include "ComplexNumberCalculator.h"
#include "CCalculatorDlg.h"
#include "afxdialogex.h"


IMPLEMENT_DYNAMIC(CCalculatorDlg, CDialog)

CCalculatorDlg::CCalculatorDlg(CWnd* parent)
	: CDialog(ID_CALCULATOR_DLG, parent)
{

}

CCalculatorDlg::~CCalculatorDlg() = default;

void CCalculatorDlg::DoDataExchange(CDataExchange* data_exchange)
{
	CDialog::DoDataExchange(data_exchange);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialog)
END_MESSAGE_MAP()