/*
 * DigitShowBasicTS - Hollow Torsional Shear Triaxial Test Control Software
 * Copyright (C) 2026 Makoto KUNO
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
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
