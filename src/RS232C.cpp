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
// RS232C.cpp : implementation file
//

#include "stdafx.h"
#include "DigitShowBasic.h"
#include "RS232C.h"
#include "DigitShowContext.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRS232C dialog

CRS232C::CRS232C(CWnd* pParent /*=NULL*/)
	: CDialog(CRS232C::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRS232C)
	m_ReceiveData = _T("");
	m_SendData = _T("");
	//}}AFX_DATA_INIT
}


void CRS232C::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRS232C)
	DDX_Text(pDX, IDC_EDIT_ReceiveData, m_ReceiveData);
	DDX_Text(pDX, IDC_EDIT_SendData, m_SendData);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRS232C, CDialog)
	//{{AFX_MSG_MAP(CRS232C)
	ON_BN_CLICKED(IDC_BUTTON_initialize, OnBUTTONinitialize)
	ON_BN_CLICKED(IDC_BUTTON_receive, OnBUTTONreceive)
	ON_BN_CLICKED(IDC_BUTTON_send, OnBUTTONsend)
	ON_BN_CLICKED(IDC_BUTTON_BalanceOn, OnBUTTONBalanceOn)
	ON_BN_CLICKED(IDC_BUTTON_BalanceOff, OnBUTTONBalanceOff)
	ON_BN_CLICKED(IDC_RADIO_LCDPT, OnRadioLcdpt)
	ON_BN_CLICKED(IDC_RADIO_Balance, OnRADIOBalance)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRS232C message handlers
BOOL CRS232C::OnInitDialog() 
{	DigitShowContext* ctx = GetContext();
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_initialize);
	CButton* myBTN2=(CButton*)GetDlgItem(IDC_BUTTON_send);
	CButton* myBTN3=(CButton*)GetDlgItem(IDC_BUTTON_receive);
	CButton* myBTN4=(CButton*)GetDlgItem(IDC_BUTTON_BalanceOn);
	CButton* myBTN5=(CButton*)GetDlgItem(IDC_BUTTON_BalanceOff);
	CButton* myBTN6=(CButton*)GetDlgItem(IDOK);
	CButton* radio1=(CButton*)GetDlgItem(IDC_RADIO_LCDPT);
	CButton* radio2=(CButton*)GetDlgItem(IDC_RADIO_Balance);
	if(ctx->flags.SetBalance){
		radio2->SetCheck(1);
		myBTN1->EnableWindow(FALSE);
		myBTN2->EnableWindow(FALSE);
		myBTN3->EnableWindow(FALSE);
		myBTN4->EnableWindow(FALSE);
		myBTN5->EnableWindow(TRUE);
		myBTN6->EnableWindow(TRUE);
	}
	else{
		radio1->SetCheck(1);
		myBTN1->EnableWindow(FALSE);
		myBTN2->EnableWindow(FALSE);
		myBTN3->EnableWindow(FALSE);
		myBTN4->EnableWindow(FALSE);
		myBTN5->EnableWindow(FALSE);
		myBTN6->EnableWindow(TRUE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRS232C::OnRadioLcdpt() 
{	DigitShowContext* ctx = GetContext();
	// TODO: Add your control notification handler code here
	CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_initialize);
	CButton* myBTN2=(CButton*)GetDlgItem(IDC_BUTTON_send);
	CButton* myBTN3=(CButton*)GetDlgItem(IDC_BUTTON_receive);
	CButton* myBTN4=(CButton*)GetDlgItem(IDC_BUTTON_BalanceOn);
	CButton* myBTN5=(CButton*)GetDlgItem(IDC_BUTTON_BalanceOff);
	CButton* myBTN6=(CButton*)GetDlgItem(IDOK);
	myBTN1->EnableWindow(FALSE);
	myBTN2->EnableWindow(FALSE);
	myBTN3->EnableWindow(FALSE);
	myBTN4->EnableWindow(FALSE);
	myBTN5->EnableWindow(FALSE);
	myBTN6->EnableWindow(TRUE);
}

void CRS232C::OnRADIOBalance() 
{	DigitShowContext* ctx = GetContext();
	// TODO: Add your control notification handler code here
	CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_initialize);
	CButton* myBTN2=(CButton*)GetDlgItem(IDC_BUTTON_send);
	CButton* myBTN3=(CButton*)GetDlgItem(IDC_BUTTON_receive);
	CButton* myBTN4=(CButton*)GetDlgItem(IDC_BUTTON_BalanceOn);
	CButton* myBTN5=(CButton*)GetDlgItem(IDC_BUTTON_BalanceOff);
	CButton* myBTN6=(CButton*)GetDlgItem(IDOK);
//
	if(ctx->flags.SetRs232c){
		if(ctx->flags.SetBalance){
			myBTN1->EnableWindow(FALSE);
			myBTN2->EnableWindow(FALSE);
			myBTN3->EnableWindow(FALSE);
			myBTN4->EnableWindow(FALSE);
			myBTN5->EnableWindow(TRUE);
			myBTN6->EnableWindow(TRUE);
		}
		else{
			myBTN1->EnableWindow(FALSE);
			myBTN2->EnableWindow(TRUE);
			myBTN3->EnableWindow(TRUE);
			myBTN4->EnableWindow(TRUE);
			myBTN5->EnableWindow(FALSE);
			myBTN6->EnableWindow(FALSE);
		}
	}
	else{
		myBTN1->EnableWindow(TRUE);
		myBTN2->EnableWindow(FALSE);
		myBTN3->EnableWindow(FALSE);
		myBTN4->EnableWindow(FALSE);
		myBTN5->EnableWindow(FALSE);
		myBTN6->EnableWindow(FALSE);
	}
}

void CRS232C::OnBUTTONinitialize() 
{	DigitShowContext* ctx = GetContext();
	// TODO: Add your control notification handler code here
	CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_initialize);
	CButton* myBTN2=(CButton*)GetDlgItem(IDC_BUTTON_send);
	CButton* myBTN3=(CButton*)GetDlgItem(IDC_BUTTON_receive);
	CButton* myBTN4=(CButton*)GetDlgItem(IDC_BUTTON_BalanceOn);
	CButton* myBTN5=(CButton*)GetDlgItem(IDC_BUTTON_BalanceOff);
	CButton* myBTN6=(CButton*)GetDlgItem(IDOK);
	pDoc->Rs232c_Open();
	if(ctx->flags.SetRs232c){
		myBTN1->EnableWindow(FALSE);
		myBTN2->EnableWindow(TRUE);
		myBTN3->EnableWindow(TRUE);
		myBTN4->EnableWindow(TRUE);
		myBTN5->EnableWindow(FALSE);
		myBTN6->EnableWindow(FALSE);
	}
}

void CRS232C::OnBUTTONreceive() 
{	DigitShowContext* ctx = GetContext();
	// TODO: Add your control notification handler code here
	pDoc->Rs232c_GetData();
	m_ReceiveData=ctx->rs232c.ReadBuffer1;
	UpdateData(FALSE);	
}

void CRS232C::OnBUTTONsend() 
{	DigitShowContext* ctx = GetContext();
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	ctx->rs232c.WriteBuffer1=m_SendData;
	pDoc->Rs232c_SendData();
}

void CRS232C::OnBUTTONBalanceOn() 
{	DigitShowContext* ctx = GetContext();
	// TODO: Add your control notification handler code here
	ctx->rs232c.WriteBuffer1=_T("SIR");
	pDoc->Rs232c_SendData();
	ctx->flags.SetBalance=TRUE;
	CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_initialize);
	CButton* myBTN2=(CButton*)GetDlgItem(IDC_BUTTON_send);
	CButton* myBTN3=(CButton*)GetDlgItem(IDC_BUTTON_receive);
	CButton* myBTN4=(CButton*)GetDlgItem(IDC_BUTTON_BalanceOn);
	CButton* myBTN5=(CButton*)GetDlgItem(IDC_BUTTON_BalanceOff);
	CButton* myBTN6=(CButton*)GetDlgItem(IDOK);
	myBTN1->EnableWindow(FALSE);
	myBTN2->EnableWindow(FALSE);
	myBTN3->EnableWindow(FALSE);
	myBTN4->EnableWindow(FALSE);
	myBTN5->EnableWindow(TRUE);
	myBTN6->EnableWindow(TRUE);
	CButton* radio1=(CButton*)GetDlgItem(IDC_RADIO_LCDPT);
	radio1->EnableWindow(FALSE);
}

void CRS232C::OnBUTTONBalanceOff() 
{	DigitShowContext* ctx = GetContext();
	// TODO: Add your control notification handler code here
	ctx->rs232c.WriteBuffer1=_T("SI");
	pDoc->Rs232c_SendData();
	ctx->flags.SetBalance=FALSE;
	CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_initialize);
	CButton* myBTN2=(CButton*)GetDlgItem(IDC_BUTTON_send);
	CButton* myBTN3=(CButton*)GetDlgItem(IDC_BUTTON_receive);
	CButton* myBTN4=(CButton*)GetDlgItem(IDC_BUTTON_BalanceOn);
	CButton* myBTN5=(CButton*)GetDlgItem(IDC_BUTTON_BalanceOff);
	CButton* myBTN6=(CButton*)GetDlgItem(IDOK);
	myBTN1->EnableWindow(FALSE);
	myBTN2->EnableWindow(TRUE);
	myBTN3->EnableWindow(TRUE);
	myBTN4->EnableWindow(TRUE);
	myBTN5->EnableWindow(FALSE);
	myBTN6->EnableWindow(FALSE);
	CButton* radio1=(CButton*)GetDlgItem(IDC_RADIO_LCDPT);
	radio1->EnableWindow(TRUE);
}

