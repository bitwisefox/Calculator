
// CalculatorDlg.h : header file
//

#pragma once
enum ACTION
{
	ACTION_NONE,
	ACTION_PLUS,
	ACTION_MINUS,
	ACTION_MULTIPLY,
	ACTION_DIVIDE,
	ACTION_RESULT
};

// CCalculatorDlg dialog
class CCalculatorDlg : public CDialogEx
{
// Construction
public:
	CCalculatorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNewDigit(UINT iButton);
	afx_msg void OnAction(UINT iButton);
	float m_fNumber;
	CString m_strNumber;
private:
	double m_dLHS;
	int m_iAction;
};
