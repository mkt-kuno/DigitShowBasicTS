// SamplingSettings.cpp : ・ｽC・ｽ・ｽ・ｽv・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽe・ｽ[・ｽV・ｽ・ｽ・ｽ・ｽ ・ｽt・ｽ@・ｽC・ｽ・ｽ
//

#include "stdafx.h"
#include "DigitShowBasic.h"
#include "DigitShowBasicDoc.h"

#include "SamplingSettings.h"
#include "DigitShowContext.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSamplingSettings ・ｽ_・ｽC・ｽA・ｽ・ｽ・ｽO




CSamplingSettings::CSamplingSettings(CWnd* pParent /*=NULL*/)
	: CDialog(CSamplingSettings::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSamplingSettings)
	m_TimeInterval1 = 0;
	m_TimeInterval2 = 0;
	m_TimeInterval3 = 0;
	m_TotalSamplingTimes = 0;
	m_AllocatedMemory = _T("");
	m_AvSmplNum = 0;
	m_Channels = 0;
	m_EventSamplingTimes = 0;
	m_MemoryType = _T("");
	m_SamplingClock = 0.0f;
	m_SavingTime = 0;
	//}}AFX_DATA_INIT
}


void CSamplingSettings::DoDataExchange(CDataExchange* pDX)
{	DigitShowContext* ctx = GetContext();
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSamplingSettings)
	DDX_Text(pDX, IDC_EDIT_TimeInterval1, m_TimeInterval1);
	DDX_Text(pDX, IDC_EDIT_TimeInterval2, m_TimeInterval2);
	DDX_Text(pDX, IDC_EDIT_TimeInterval3, m_TimeInterval3);
	DDX_Text(pDX, IDC_EDIT_TotalSamplingTimes, m_TotalSamplingTimes);
	DDX_Text(pDX, IDC_EDIT_AllocatedMemory, m_AllocatedMemory);
	DDX_Text(pDX, IDC_EDIT_AvSmplNum, m_AvSmplNum);
	DDX_Text(pDX, IDC_EDIT_Channels, m_Channels);
	DDX_Text(pDX, IDC_EDIT_EventSamplingTimes, m_EventSamplingTimes);
	DDX_Text(pDX, IDC_EDIT_MemoryType, m_MemoryType);
	DDX_Text(pDX, IDC_EDIT_SamplingClock, m_SamplingClock);
	DDX_Text(pDX, IDC_EDIT_SavingTime, m_SavingTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSamplingSettings, CDialog)
	//{{AFX_MSG_MAP(CSamplingSettings)
	ON_BN_CLICKED(IDC_BUTTON_Check, OnBUTTONCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSamplingSettings ・ｽ・ｽ・ｽb・ｽZ・ｽ[・ｽW ・ｽn・ｽ・ｽ・ｽh・ｽ・ｽ

BOOL CSamplingSettings::OnInitDialog() 
{	DigitShowContext* ctx = GetContext();
	CDialog::OnInitDialog();
	
	// TODO: ・ｽ・ｽ・ｽﾌ位置・ｽﾉ擾ｿｽ・ｽ・ｽ・ｽ・ｽ・ｽﾌ補足・ｽ・ｽ・ｽ・ｽ・ｽ・ｽﾇ会ｿｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
	m_TimeInterval1 = ctx->timeSettings.Interval1;
	m_TimeInterval2 = ctx->timeSettings.Interval2;
	m_TimeInterval3 = ctx->timeSettings.Interval3;
//
	m_AllocatedMemory.Format("%.1f",ctx->AllocatedMemory);
	m_Channels = ctx->AdMaxCH;
	m_EventSamplingTimes = ctx->ad[0].SamplingTimes;
	m_AvSmplNum = ctx->AvSmplNum;
	if(ctx->ad[0].MemoryType==0) m_MemoryType = _T("FIFO");
	if(ctx->ad[0].MemoryType==1) m_MemoryType = _T("RING");
	m_SamplingClock = ctx->ad[0].SamplingClock/1000.0f;
	m_SavingTime = ctx->SavingTime;
	m_TotalSamplingTimes = ctx->TotalSamplingTimes;
	UpdateData(FALSE);
//
	CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_Check);
	CButton* myBTN2=(CButton*)GetDlgItem(IDOK);
	if(ctx->flags.FIFO==TRUE)	myBTN1->EnableWindow(FALSE);
	myBTN2->EnableWindow(FALSE);

	return TRUE;  // ・ｽR・ｽ・ｽ・ｽg・ｽ・ｽ・ｽ[・ｽ・ｽ・ｽﾉフ・ｽH・ｽ[・ｽJ・ｽX・ｽ・ｽﾝ定し・ｽﾈゑｿｽ・ｽﾆゑｿｽ・ｽA・ｽﾟゑｿｽl・ｽ・ｽ TRUE ・ｽﾆなゑｿｽﾜゑｿｽ
	              // ・ｽ・ｽO: OCX ・ｽv・ｽ・ｽ・ｽp・ｽe・ｽB ・ｽy・ｽ[・ｽW・ｽﾌ戻ゑｿｽl・ｽ・ｽ FALSE ・ｽﾆなゑｿｽﾜゑｿｽ
}

void CSamplingSettings::OnBUTTONCheck() 
{	DigitShowContext* ctx = GetContext();
	// TODO: ・ｽ・ｽ・ｽﾌ位置・ｽﾉコ・ｽ・ｽ・ｽg・ｽ・ｽ・ｽ[・ｽ・ｽ・ｽﾊ知・ｽn・ｽ・ｽ・ｽh・ｽ・ｽ・ｽp・ｽﾌコ・ｽ[・ｽh・ｽ・ｽﾇ会ｿｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
	UpdateData(TRUE);
	m_TotalSamplingTimes=long(m_SavingTime*1000/m_SamplingClock);
	m_AllocatedMemory.Format("%.1f",4*ctx->AdMaxCH*m_TotalSamplingTimes/1024.0f/1024.0f);
	m_EventSamplingTimes=long(ctx->timeSettings.Interval1/m_SamplingClock);
	UpdateData(FALSE);

	CButton* myBTN1=(CButton*)GetDlgItem(IDOK);
	myBTN1->EnableWindow(TRUE);
	
}

void CSamplingSettings::OnOK() 
{	DigitShowContext* ctx = GetContext();
	// TODO: ・ｽ・ｽ・ｽﾌ位置・ｽﾉゑｿｽ・ｽﾌ托ｿｽ・ｽﾌ鯉ｿｽ・ｽﾘ用・ｽﾌコ・ｽ[・ｽh・ｽ・ｽﾇ会ｿｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
	UpdateData(TRUE);
	ctx->ad[0].SamplingClock = m_SamplingClock*1000.0f;
	ctx->ad[0].ScanClock = long(ctx->ad[0].SamplingClock/ctx->ad[0].Channels);	// Newer CONTEC drivers require ScanClock <= SamplingClock/CH (floor to the safe side)
	if(ctx->ad[0].ScanClock<1){ ctx->ad[0].ScanClock=1; }
	ctx->SavingTime = m_SavingTime;
	ctx->ad[0].SamplingTimes = m_EventSamplingTimes;
	ctx->TotalSamplingTimes=long(ctx->SavingTime*1000000/ctx->ad[0].SamplingClock);
	ctx->AllocatedMemory=4*ctx->AdMaxCH*m_TotalSamplingTimes/1024.0f/1024.0f;
	m_AllocatedMemory.Format("%.1f",ctx->AllocatedMemory);
	m_TotalSamplingTimes=ctx->TotalSamplingTimes;
	UpdateData(FALSE);

	if(ctx->NumAD>1){
		ctx->ad[1].SamplingClock=ctx->ad[0].SamplingClock;
		ctx->ad[1].ScanClock=long(ctx->ad[1].SamplingClock/ctx->ad[1].Channels);
		if(ctx->ad[1].ScanClock<1){ ctx->ad[1].ScanClock=1; }
		ctx->ad[1].SamplingTimes=ctx->ad[0].SamplingTimes;
	}
	CDialog::OnOK();
}
