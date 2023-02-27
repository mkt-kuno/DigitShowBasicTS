#if !defined(AFX_RS232C_H__E874BEF1_5A34_4849_8633_3F1463F32A26__INCLUDED_)
#define AFX_RS232C_H__E874BEF1_5A34_4849_8633_3F1463F32A26__INCLUDED_

#include "DigitShowBasicDoc.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RS232C.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRS232C dialog

class CRS232C : public CDialog
{
// Construction
public:
	CRS232C(CWnd* pParent = NULL);   // standard constructor
	CDigitShowBasicDoc* pDoc;
// Dialog Data
	//{{AFX_DATA(CRS232C)
	enum { IDD = IDD_RS232C };
	CString	m_ReceiveData;
	CString	m_SendData;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRS232C)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRS232C)
	afx_msg void OnBUTTONinitialize();
	afx_msg void OnBUTTONreceive();
	afx_msg void OnBUTTONsend();
	virtual BOOL OnInitDialog();
	afx_msg void OnBUTTONBalanceOn();
	afx_msg void OnBUTTONBalanceOff();
	afx_msg void OnRadioLcdpt();
	afx_msg void OnRADIOBalance();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RS232C_H__E874BEF1_5A34_4849_8633_3F1463F32A26__INCLUDED_)
