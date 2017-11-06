
// CalculatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCalculatorDlg dialog



CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
	, m_fNumber(0)
	, m_strNumber(_T(""))
	, m_dLHS(0)
	, m_iAction(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Text(pDX, IDC_EMSG, m_fNumber);
	DDX_Text(pDX, IDC_EMSG, m_strNumber);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_B0, IDC_B9, &CCalculatorDlg::OnNewDigit)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BPLUS, IDC_BAC, &CCalculatorDlg::OnAction)
END_MESSAGE_MAP()


// CCalculatorDlg message handlers

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_fNumber = 0;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCalculatorDlg::OnNewDigit(UINT iButton)
{
	// Clear the previous result
	if (m_iAction == ACTION_RESULT)
	{
		m_strNumber = "";
		m_iAction = ACTION_NONE;
	}

	int iValue = (iButton - IDC_B0);
	m_strNumber.AppendFormat(L"%d", iValue);

//	m_fNumber = (m_fNumber * 10) + iValue;
//	m_strNumber.Format(L"%f", m_fNumber);
	UpdateData(FALSE);
}



void CCalculatorDlg::OnAction(UINT iButton)
{
	double dResult;
	switch (iButton)
	{
	case IDC_BPLUS: 
		m_dLHS = _wtof(m_strNumber);
		m_strNumber = "";
		m_iAction = ACTION_PLUS;
		break;
	case IDC_BMINUS:
		m_dLHS = _wtof(m_strNumber);
		m_strNumber = "";
		m_iAction = ACTION_MINUS;
		break;
	case IDC_BDIV:
		m_dLHS = _wtof(m_strNumber);
		m_strNumber = "";
		m_iAction = ACTION_DIVIDE;
		break;
	case IDC_BMULT:
		m_dLHS = _wtof(m_strNumber);
		m_strNumber = "";
		m_iAction = ACTION_MULTIPLY;
		break;
	case IDC_BEQUAL:
		switch (m_iAction)
		{
		case ACTION_PLUS:
			dResult = m_dLHS + _wtof(m_strNumber);
			break;
		case ACTION_MINUS:
			dResult = m_dLHS - _wtof(m_strNumber);
			break;
		case ACTION_DIVIDE:
			dResult = m_dLHS / _wtof(m_strNumber);
			break;
		case ACTION_MULTIPLY:
			dResult = m_dLHS * _wtof(m_strNumber);
			break;
		}
		m_dLHS = 0;
		m_iAction = ACTION_RESULT;
		m_strNumber.Format(L"%f", dResult);
		break;
	case IDC_BPOINT:
		m_strNumber.Append(L".");
		break;
	case IDC_BAC:
		m_strNumber = "";
		m_dLHS = 0;
		break;
	}
	
	UpdateData(FALSE);
}
