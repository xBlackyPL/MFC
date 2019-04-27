#include "stdafx.h"
#include "ComplexNumberCalculator.h"
#include "CCalculatorDlg.h"
#include "afxdialogex.h"
#include <string>
#include "ComplexNumber.h"

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
		ON_BN_CLICKED(IDC_MODULUS_LEFT, &CCalculatorDlg::OnBnClickedModulusLeft)
		ON_BN_CLICKED(IDC_CONJUGATE_LEFT, &CCalculatorDlg::OnBnClickedConjugateLeft)
		ON_BN_CLICKED(IDC_MODULUS_RIGHT, &CCalculatorDlg::OnBnClickedModulusRight)
		ON_BN_CLICKED(IDC_CONJUGATE_RIGHT, &CCalculatorDlg::OnBnClickedConjugateRight)
		ON_BN_CLICKED(IDC_PLUS, &CCalculatorDlg::OnBnClickedPlus)
		ON_BN_CLICKED(IDC_MINUS, &CCalculatorDlg::OnBnClickedMinus)
		ON_BN_CLICKED(IDC_MULTIPLY, &CCalculatorDlg::OnBnClickedMultiply)
		ON_BN_CLICKED(IDC_DIVIDE, &CCalculatorDlg::OnBnClickedDivide)
END_MESSAGE_MAP()

void CCalculatorDlg::OnBnClickedModulusLeft()
{
	auto real_as_text = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);
	auto imaginary_as_text = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);
	auto result = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);

	GetDlgItemText(IDC_LEFT_RE, real_as_text.get(), MAX_PATH);
	GetDlgItemText(IDC_LEFT_IM, imaginary_as_text.get(), MAX_PATH);
	const auto real = std::wcstod(real_as_text.get(), nullptr);
	const auto imaginary = std::wcstod(imaginary_as_text.get(), nullptr);

	complex_number input_number(real, imaginary);
	const auto modulus = input_number.modulus();
	swprintf_s(result.get(), MAX_PATH, L"%lf", modulus);
	SetDlgItemText(IDC_RESULT_MODULUS, LPCTSTR(result.get()));
}

void CCalculatorDlg::OnBnClickedConjugateLeft()
{
	auto real_as_text = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);
	auto imaginary_as_text = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);
	auto result_re = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);
	auto result_im = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);

	GetDlgItemText(IDC_LEFT_RE, real_as_text.get(), MAX_PATH);
	GetDlgItemText(IDC_LEFT_IM, imaginary_as_text.get(), MAX_PATH);
	const auto real = std::wcstod(real_as_text.get(), nullptr);
	const auto imaginary = std::wcstod(imaginary_as_text.get(), nullptr);

	complex_number input_number(real, imaginary);
	complex_number output_number = input_number.conjugate();

	swprintf_s(result_re.get(), MAX_PATH, L"%lf", output_number.get_real());
	swprintf_s(result_im.get(), MAX_PATH, L"%lf", output_number.get_imaginary());
	SetDlgItemText(IDC_RESULT_RE, LPCTSTR(result_re.get()));
	SetDlgItemText(IDC_RESULT_IM, LPCTSTR(result_im.get()));
}

void CCalculatorDlg::OnBnClickedModulusRight()
{
	auto real_as_text = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);
	auto imaginary_as_text = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);
	auto result = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);

	GetDlgItemText(IDC_RIGHT_RE, real_as_text.get(), MAX_PATH);
	GetDlgItemText(IDC_RIGHT_IM, imaginary_as_text.get(), MAX_PATH);
	const auto real = std::wcstod(real_as_text.get(), nullptr);
	const auto imaginary = std::wcstod(imaginary_as_text.get(), nullptr);

	complex_number input_number(real, imaginary);
	const auto modulus = input_number.modulus();
	swprintf_s(result.get(), MAX_PATH, L"%lf", modulus);
	SetDlgItemText(IDC_RESULT_MODULUS, LPCTSTR(result.get()));
}

void CCalculatorDlg::OnBnClickedConjugateRight()
{
	auto real_as_text = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);
	auto imaginary_as_text = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);
	auto result_re = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);
	auto result_im = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);

	GetDlgItemText(IDC_RIGHT_RE, real_as_text.get(), MAX_PATH);
	GetDlgItemText(IDC_RIGHT_IM, imaginary_as_text.get(), MAX_PATH);
	const auto real = std::wcstod(real_as_text.get(), nullptr);
	const auto imaginary = std::wcstod(imaginary_as_text.get(), nullptr);

	complex_number input_number(real, imaginary);
	complex_number output_number = input_number.conjugate();

	swprintf_s(result_re.get(), MAX_PATH, L"%lf", output_number.get_real());
	swprintf_s(result_im.get(), MAX_PATH, L"%lf", output_number.get_imaginary());
	SetDlgItemText(IDC_RESULT_RE, LPCTSTR(result_re.get()));
	SetDlgItemText(IDC_RESULT_IM, LPCTSTR(result_im.get()));
}

void CCalculatorDlg::OnBnClickedPlus()
{
	auto left_real_text = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);
	auto left_imaginary_text = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);
	auto right_real_text = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);
	auto right_imaginary_text = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);

	auto result_re = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);
	auto result_im = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);

	GetDlgItemText(IDC_LEFT_RE, left_real_text.get(), MAX_PATH);
	GetDlgItemText(IDC_LEFT_IM, left_imaginary_text.get(), MAX_PATH);
	GetDlgItemText(IDC_RIGHT_RE, right_real_text.get(), MAX_PATH);
	GetDlgItemText(IDC_RIGHT_IM, right_imaginary_text.get(), MAX_PATH);

	const auto left_real = std::wcstod(left_real_text.get(), nullptr);
	const auto left_imaginary = std::wcstod(left_imaginary_text.get(), nullptr);
	const auto right_real = std::wcstod(right_real_text.get(), nullptr);
	const auto right_imaginary = std::wcstod(right_imaginary_text.get(), nullptr);

	complex_number input_number_left(left_real, left_imaginary);
	const complex_number input_number_right(right_real, right_imaginary);

	input_number_left += input_number_right;
	swprintf_s(result_re.get(), MAX_PATH, L"%lf", input_number_left.get_real());
	swprintf_s(result_im.get(), MAX_PATH, L"%lf", input_number_left.get_imaginary());
	SetDlgItemText(IDC_RESULT_RE, LPCTSTR(result_re.get()));
	SetDlgItemText(IDC_RESULT_IM, LPCTSTR(result_im.get()));
}

void CCalculatorDlg::OnBnClickedMinus()
{
	auto left_real_text = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);
	auto left_imaginary_text = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);
	auto right_real_text = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);
	auto right_imaginary_text = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);

	auto result_re = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);
	auto result_im = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);

	GetDlgItemText(IDC_LEFT_RE, left_real_text.get(), MAX_PATH);
	GetDlgItemText(IDC_LEFT_IM, left_imaginary_text.get(), MAX_PATH);
	GetDlgItemText(IDC_RIGHT_RE, right_real_text.get(), MAX_PATH);
	GetDlgItemText(IDC_RIGHT_IM, right_imaginary_text.get(), MAX_PATH);

	const auto left_real = std::wcstod(left_real_text.get(), nullptr);
	const auto left_imaginary = std::wcstod(left_imaginary_text.get(), nullptr);
	const auto right_real = std::wcstod(right_real_text.get(), nullptr);
	const auto right_imaginary = std::wcstod(right_imaginary_text.get(), nullptr);

	complex_number input_number_left(left_real, left_imaginary);
	const complex_number input_number_right(right_real, right_imaginary);

	input_number_left -= input_number_right;
	swprintf_s(result_re.get(), MAX_PATH, L"%lf", input_number_left.get_real());
	swprintf_s(result_im.get(), MAX_PATH, L"%lf", input_number_left.get_imaginary());
	SetDlgItemText(IDC_RESULT_RE, LPCTSTR(result_re.get()));
	SetDlgItemText(IDC_RESULT_IM, LPCTSTR(result_im.get()));
}

void CCalculatorDlg::OnBnClickedMultiply()
{
	auto left_real_text = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);
	auto left_imaginary_text = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);
	auto right_real_text = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);
	auto right_imaginary_text = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);

	auto result_re = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);
	auto result_im = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);

	GetDlgItemText(IDC_LEFT_RE, left_real_text.get(), MAX_PATH);
	GetDlgItemText(IDC_LEFT_IM, left_imaginary_text.get(), MAX_PATH);
	GetDlgItemText(IDC_RIGHT_RE, right_real_text.get(), MAX_PATH);
	GetDlgItemText(IDC_RIGHT_IM, right_imaginary_text.get(), MAX_PATH);

	const auto left_real = std::wcstod(left_real_text.get(), nullptr);
	const auto left_imaginary = std::wcstod(left_imaginary_text.get(), nullptr);
	const auto right_real = std::wcstod(right_real_text.get(), nullptr);
	const auto right_imaginary = std::wcstod(right_imaginary_text.get(), nullptr);

	complex_number input_number_left(left_real, left_imaginary);
	const complex_number input_number_right(right_real, right_imaginary);

	input_number_left *= input_number_right;
	swprintf_s(result_re.get(), MAX_PATH, L"%lf", input_number_left.get_real());
	swprintf_s(result_im.get(), MAX_PATH, L"%lf", input_number_left.get_imaginary());
	SetDlgItemText(IDC_RESULT_RE, LPCTSTR(result_re.get()));
	SetDlgItemText(IDC_RESULT_IM, LPCTSTR(result_im.get()));
}

void CCalculatorDlg::OnBnClickedDivide()
{
	auto left_real_text = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);
	auto left_imaginary_text = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);
	auto right_real_text = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);
	auto right_imaginary_text = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);

	auto result_re = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);
	auto result_im = std::unique_ptr<TCHAR>(new TCHAR[MAX_PATH + 1]);

	GetDlgItemText(IDC_LEFT_RE, left_real_text.get(), MAX_PATH);
	GetDlgItemText(IDC_LEFT_IM, left_imaginary_text.get(), MAX_PATH);
	GetDlgItemText(IDC_RIGHT_RE, right_real_text.get(), MAX_PATH);
	GetDlgItemText(IDC_RIGHT_IM, right_imaginary_text.get(), MAX_PATH);

	const auto left_real = std::wcstod(left_real_text.get(), nullptr);
	const auto left_imaginary = std::wcstod(left_imaginary_text.get(), nullptr);
	const auto right_real = std::wcstod(right_real_text.get(), nullptr);
	const auto right_imaginary = std::wcstod(right_imaginary_text.get(), nullptr);

	complex_number input_number_left(left_real, left_imaginary);
	const complex_number input_number_right(right_real, right_imaginary);

	input_number_left /= input_number_right;
	swprintf_s(result_re.get(), MAX_PATH, L"%lf", input_number_left.get_real());
	swprintf_s(result_im.get(), MAX_PATH, L"%lf", input_number_left.get_imaginary());
	SetDlgItemText(IDC_RESULT_RE, LPCTSTR(result_re.get()));
	SetDlgItemText(IDC_RESULT_IM, LPCTSTR(result_im.get()));
}
