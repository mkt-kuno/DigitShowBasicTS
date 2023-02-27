// RS232C.cpp : implementation file
//

#include "stdafx.h"
#include "DigitShowBasic.h"
#include "RS232C.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRS232C dialog
extern	bool		Flag_SetRs232c;
extern	bool		Flag_SetBalance;
extern	CString		ReadBuffer1,ReadBuffer2;
extern	CString		WriteBuffer1,WriteBuffer2;

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
{
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
	if(Flag_SetBalance){
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
{
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
{
	// TODO: Add your control notification handler code here
	CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_initialize);
	CButton* myBTN2=(CButton*)GetDlgItem(IDC_BUTTON_send);
	CButton* myBTN3=(CButton*)GetDlgItem(IDC_BUTTON_receive);
	CButton* myBTN4=(CButton*)GetDlgItem(IDC_BUTTON_BalanceOn);
	CButton* myBTN5=(CButton*)GetDlgItem(IDC_BUTTON_BalanceOff);
	CButton* myBTN6=(CButton*)GetDlgItem(IDOK);
//
	if(Flag_SetRs232c){
		if(Flag_SetBalance){
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
{
	// TODO: Add your control notification handler code here
	CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_initialize);
	CButton* myBTN2=(CButton*)GetDlgItem(IDC_BUTTON_send);
	CButton* myBTN3=(CButton*)GetDlgItem(IDC_BUTTON_receive);
	CButton* myBTN4=(CButton*)GetDlgItem(IDC_BUTTON_BalanceOn);
	CButton* myBTN5=(CButton*)GetDlgItem(IDC_BUTTON_BalanceOff);
	CButton* myBTN6=(CButton*)GetDlgItem(IDOK);
	pDoc->Rs232c_Open();
	if(Flag_SetRs232c){
		myBTN1->EnableWindow(FALSE);
		myBTN2->EnableWindow(TRUE);
		myBTN3->EnableWindow(TRUE);
		myBTN4->EnableWindow(TRUE);
		myBTN5->EnableWindow(FALSE);
		myBTN6->EnableWindow(FALSE);
	}
}

void CRS232C::OnBUTTONreceive() 
{
	// TODO: Add your control notification handler code here
	pDoc->Rs232c_GetData();
	m_ReceiveData=ReadBuffer1;
	UpdateData(FALSE);	
}

void CRS232C::OnBUTTONsend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	WriteBuffer1=m_SendData;
	pDoc->Rs232c_SendData();
}

void CRS232C::OnBUTTONBalanceOn() 
{
	// TODO: Add your control notification handler code here
	WriteBuffer1=_T("SIR");
	pDoc->Rs232c_SendData();
	Flag_SetBalance=TRUE;
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
{
	// TODO: Add your control notification handler code here
	WriteBuffer1=_T("SI");
	pDoc->Rs232c_SendData();
	Flag_SetBalance=FALSE;
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

