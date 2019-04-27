#pragma once


class CCalculatorDlg : public CDialog
{
private:
DECLARE_DYNAMIC(CCalculatorDlg)
protected:
	void DoDataExchange(CDataExchange* data_exchange) override;
DECLARE_MESSAGE_MAP()

public:
	CCalculatorDlg(CWnd* parent = nullptr);
	afx_msg void OnBnClickedModulusLeft();
	afx_msg void OnBnClickedConjugateLeft();
	afx_msg void OnBnClickedModulusRight();
	afx_msg void OnBnClickedConjugateRight();
	afx_msg void OnBnClickedPlus();
	afx_msg void OnBnClickedMinus();
	afx_msg void OnBnClickedMultiply();
	afx_msg void OnBnClickedDivide();
	virtual ~CCalculatorDlg();
};
