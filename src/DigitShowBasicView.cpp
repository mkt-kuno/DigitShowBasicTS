// DigitShowBasicView.cpp : CDigitShowBasicView ・ｽN・ｽ・ｽ・ｽX・ｽﾌ難ｿｽ・ｽ・ｽﾌ抵ｿｽ`・ｽ・ｽ・ｽs・ｽ・ｽ・ｽﾜゑｿｽ・ｽB
//

#include "stdafx.h"
#include "DigitShowBasic.h"

#include "DigitShowBasicDoc.h"
#include "DigitShowBasicView.h"
#include "DigitShowContext.h"

#include "CAIO.H"
#include "SamplingSettings.h"
#include "RS232C.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDigitShowBasicView
// --- A/D ---

		long		tmp,tmp0,tmp1;

//------

//---Flag---
		bool		Flag_Ctrl;

//---Control---

//---Control File---

//---Time---
//---File---
//

IMPLEMENT_DYNCREATE(CDigitShowBasicView, CFormView)

BEGIN_MESSAGE_MAP(CDigitShowBasicView, CFormView)
	//{{AFX_MSG_MAP(CDigitShowBasicView)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_CtrlOff, OnBUTTONCtrlOff)
	ON_BN_CLICKED(IDC_BUTTON_CtrlOn, OnBUTTONCtrlOn)
	ON_BN_CLICKED(IDC_BUTTON_StartSave, OnBUTTONStartSave)
	ON_BN_CLICKED(IDC_BUTTON_StopSave, OnBUTTONStopSave)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_InterceptSave, OnBUTTONInterceptSave)
	ON_BN_CLICKED(IDC_BUTTON_SetCtrlID, OnBUTTONSetCtrlID)
	ON_BN_CLICKED(IDC_BUTTON_SetSamplingTime, OnBUTTONSetSamplingTime)
	ON_BN_CLICKED(IDC_BUTTON_FIFOStart, OnBUTTONFIFOStart)
	ON_BN_CLICKED(IDC_BUTTON_FIFOStop, OnBUTTONFIFOStop)
	ON_BN_CLICKED(IDC_BUTTON_WriteData, OnBUTTONWriteData)
	ON_BN_CLICKED(IDC_BUTTON_DChannel, OnBUTTONDChannel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDigitShowBasicView ・ｽN・ｽ・ｽ・ｽX・ｽﾌ構・ｽz/・ｽ・ｽ・ｽ・ｽ

CDigitShowBasicView::CDigitShowBasicView()
	: CFormView(CDigitShowBasicView::IDD)
{
	DigitShowContext* ctx = GetContext();
	//{{AFX_DATA_INIT(CDigitShowBasicView)
	m_Vout00 = _T("");
	m_Vout01 = _T("");
	m_Vout02 = _T("");
	m_Vout03 = _T("");
	m_Vout04 = _T("");
	m_Vout05 = _T("");
	m_Vout06 = _T("");
	m_Vout07 = _T("");
	m_Vout08 = _T("");
	m_Vout09 = _T("");
	m_Vout10 = _T("");
	m_Vout11 = _T("");
	m_Vout12 = _T("");
	m_Vout13 = _T("");
	m_Vout14 = _T("");
	m_Vout15 = _T("");
	m_Phyout00 = _T("");
	m_Phyout01 = _T("");
	m_Phyout02 = _T("");
	m_Phyout03 = _T("");
	m_Phyout04 = _T("");
	m_Phyout05 = _T("");
	m_Phyout06 = _T("");
	m_Phyout07 = _T("");
	m_Phyout08 = _T("");
	m_Phyout09 = _T("");
	m_Phyout10 = _T("");
	m_Phyout11 = _T("");
	m_Phyout12 = _T("");
	m_Phyout13 = _T("");
	m_Phyout14 = _T("");
	m_Phyout15 = _T("");
	m_Para00 = _T("");
	m_Para01 = _T("");
	m_Para02 = _T("");
	m_Para03 = _T("");
	m_Para04 = _T("");
	m_Para05 = _T("");
	m_Para06 = _T("");
	m_Para07 = _T("");
	m_Para08 = _T("");
	m_Para09 = _T("");
	m_Para10 = _T("");
	m_Para11 = _T("");
	m_Para12 = _T("");
	m_Para13 = _T("");
	m_Para14 = _T("");
	m_Para15 = _T("");
	m_Ctrl_ID = 0;
	m_NowTime = _T("");
	m_SeqTime = 0;
	m_SamplingTime = ctx->timeSettings.Interval3;
	m_FileName = _T("");
	m_Para16 = _T("");
	m_Para17 = _T("");
	m_Para18 = _T("");
	m_Para19 = _T("");
	m_Para20 = _T("");
	m_Para21 = _T("");
	m_Para22 = _T("");
	m_Para23 = _T("");
	m_CFCtrlPattern = 0;
	m_CFCyclicNo = 0;
	m_CFStepNo = 0;
	m_CFStepTime = 0.0;
	m_PHY00 = _T("");
	m_PHY01 = _T("");
	m_PHY02 = _T("");
	m_PHY03 = _T("");
	m_PHY04 = _T("");
	m_PHY05 = _T("");
	m_PHY06 = _T("");
	m_PHY07 = _T("");
	m_PHY08 = _T("");
	m_PHY09 = _T("");
	m_PHY10 = _T("");
	m_PHY11 = _T("");
	m_PHY12 = _T("");
	m_PHY13 = _T("");
	m_PHY14 = _T("");
	m_PHY15 = _T("");
	m_VLT00 = _T("");
	m_VLT01 = _T("");
	m_VLT02 = _T("");
	m_VLT03 = _T("");
	m_VLT04 = _T("");
	m_VLT05 = _T("");
	m_VLT06 = _T("");
	m_VLT07 = _T("");
	m_VLT08 = _T("");
	m_VLT09 = _T("");
	m_VLT10 = _T("");
	m_VLT11 = _T("");
	m_VLT12 = _T("");
	m_VLT13 = _T("");
	m_VLT14 = _T("");
	m_VLT15 = _T("");
	m_DChannel = _T("Ch.00-15");
	//}}AFX_DATA_INIT
	// TODO: ・ｽ・ｽ・ｽﾌ場所・ｽﾉ構・ｽz・ｽp・ｽﾌコ・ｽ[・ｽh・ｽ・ｽﾇ会ｿｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽB
	Flag_Ctrl=FALSE;
	m_pEditBrush= new CBrush(RGB(255,255,255));
	m_pStaticBrush= new CBrush(RGB(0,128,128));	
	m_pDlgBrush= new CBrush(RGB(0,128,128));
}

CDigitShowBasicView::~CDigitShowBasicView()
{
	CDigitShowBasicDoc* pDoc=(CDigitShowBasicDoc *)GetDocument();
	pDoc->CloseBoard();
	pDoc->Rs232c_Close();
}

void CDigitShowBasicView::DoDataExchange(CDataExchange* pDX)
{	DigitShowContext* ctx = GetContext();
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDigitShowBasicView)
	DDX_Text(pDX, IDC_EDIT_Vout00, m_Vout00);
	DDX_Text(pDX, IDC_EDIT_Vout01, m_Vout01);
	DDX_Text(pDX, IDC_EDIT_Vout02, m_Vout02);
	DDX_Text(pDX, IDC_EDIT_Vout03, m_Vout03);
	DDX_Text(pDX, IDC_EDIT_Vout04, m_Vout04);
	DDX_Text(pDX, IDC_EDIT_Vout05, m_Vout05);
	DDX_Text(pDX, IDC_EDIT_Vout06, m_Vout06);
	DDX_Text(pDX, IDC_EDIT_Vout07, m_Vout07);
	DDX_Text(pDX, IDC_EDIT_Vout08, m_Vout08);
	DDX_Text(pDX, IDC_EDIT_Vout09, m_Vout09);
	DDX_Text(pDX, IDC_EDIT_Vout10, m_Vout10);
	DDX_Text(pDX, IDC_EDIT_Vout11, m_Vout11);
	DDX_Text(pDX, IDC_EDIT_Vout12, m_Vout12);
	DDX_Text(pDX, IDC_EDIT_Vout13, m_Vout13);
	DDX_Text(pDX, IDC_EDIT_Vout14, m_Vout14);
	DDX_Text(pDX, IDC_EDIT_Vout15, m_Vout15);
	DDX_Text(pDX, IDC_EDIT_Phyout00, m_Phyout00);
	DDX_Text(pDX, IDC_EDIT_Phyout01, m_Phyout01);
	DDX_Text(pDX, IDC_EDIT_Phyout02, m_Phyout02);
	DDX_Text(pDX, IDC_EDIT_Phyout03, m_Phyout03);
	DDX_Text(pDX, IDC_EDIT_Phyout04, m_Phyout04);
	DDX_Text(pDX, IDC_EDIT_Phyout05, m_Phyout05);
	DDX_Text(pDX, IDC_EDIT_Phyout06, m_Phyout06);
	DDX_Text(pDX, IDC_EDIT_Phyout07, m_Phyout07);
	DDX_Text(pDX, IDC_EDIT_Phyout08, m_Phyout08);
	DDX_Text(pDX, IDC_EDIT_Phyout09, m_Phyout09);
	DDX_Text(pDX, IDC_EDIT_Phyout10, m_Phyout10);
	DDX_Text(pDX, IDC_EDIT_Phyout11, m_Phyout11);
	DDX_Text(pDX, IDC_EDIT_Phyout12, m_Phyout12);
	DDX_Text(pDX, IDC_EDIT_Phyout13, m_Phyout13);
	DDX_Text(pDX, IDC_EDIT_Phyout14, m_Phyout14);
	DDX_Text(pDX, IDC_EDIT_Phyout15, m_Phyout15);
	DDX_Text(pDX, IDC_EDIT_Para00, m_Para00);
	DDX_Text(pDX, IDC_EDIT_Para01, m_Para01);
	DDX_Text(pDX, IDC_EDIT_Para02, m_Para02);
	DDX_Text(pDX, IDC_EDIT_Para03, m_Para03);
	DDX_Text(pDX, IDC_EDIT_Para04, m_Para04);
	DDX_Text(pDX, IDC_EDIT_Para05, m_Para05);
	DDX_Text(pDX, IDC_EDIT_Para06, m_Para06);
	DDX_Text(pDX, IDC_EDIT_Para07, m_Para07);
	DDX_Text(pDX, IDC_EDIT_Para08, m_Para08);
	DDX_Text(pDX, IDC_EDIT_Para09, m_Para09);
	DDX_Text(pDX, IDC_EDIT_Para10, m_Para10);
	DDX_Text(pDX, IDC_EDIT_Para11, m_Para11);
	DDX_Text(pDX, IDC_EDIT_Para12, m_Para12);
	DDX_Text(pDX, IDC_EDIT_Para13, m_Para13);
	DDX_Text(pDX, IDC_EDIT_Para14, m_Para14);
	DDX_Text(pDX, IDC_EDIT_Para15, m_Para15);
	DDX_Text(pDX, IDC_EDIT_Ctrl_ID, m_Ctrl_ID);
	DDX_Text(pDX, IDC_EDIT_NowTime, m_NowTime);
	DDX_Text(pDX, IDC_EDIT_SeqTime, m_SeqTime);
	DDX_Text(pDX, IDC_EDIT_SamplingTime, m_SamplingTime);
	DDX_Text(pDX, IDC_EDIT_FileName, m_FileName);
	DDX_Text(pDX, IDC_EDIT_Para16, m_Para16);
	DDX_Text(pDX, IDC_EDIT_Para17, m_Para17);
	DDX_Text(pDX, IDC_EDIT_Para18, m_Para18);
	DDX_Text(pDX, IDC_EDIT_Para19, m_Para19);
	DDX_Text(pDX, IDC_EDIT_Para20, m_Para20);
	DDX_Text(pDX, IDC_EDIT_Para21, m_Para21);
	DDX_Text(pDX, IDC_EDIT_Para22, m_Para22);
	DDX_Text(pDX, IDC_EDIT_Para23, m_Para23);
	DDX_Text(pDX, IDC_EDIT_CFCtrlPattern, m_CFCtrlPattern);
	DDX_Text(pDX, IDC_EDIT_CFCyclicNo, m_CFCyclicNo);
	DDX_Text(pDX, IDC_EDIT_CFStepNo, m_CFStepNo);
	DDX_Text(pDX, IDC_EDIT_CFStepTime, m_CFStepTime);
	DDX_Text(pDX, IDC_STATIC_PHY00, m_PHY00);
	DDX_Text(pDX, IDC_STATIC_PHY01, m_PHY01);
	DDX_Text(pDX, IDC_STATIC_PHY02, m_PHY02);
	DDX_Text(pDX, IDC_STATIC_PHY03, m_PHY03);
	DDX_Text(pDX, IDC_STATIC_PHY04, m_PHY04);
	DDX_Text(pDX, IDC_STATIC_PHY05, m_PHY05);
	DDX_Text(pDX, IDC_STATIC_PHY06, m_PHY06);
	DDX_Text(pDX, IDC_STATIC_PHY07, m_PHY07);
	DDX_Text(pDX, IDC_STATIC_PHY08, m_PHY08);
	DDX_Text(pDX, IDC_STATIC_PHY09, m_PHY09);
	DDX_Text(pDX, IDC_STATIC_PHY10, m_PHY10);
	DDX_Text(pDX, IDC_STATIC_PHY11, m_PHY11);
	DDX_Text(pDX, IDC_STATIC_PHY12, m_PHY12);
	DDX_Text(pDX, IDC_STATIC_PHY13, m_PHY13);
	DDX_Text(pDX, IDC_STATIC_PHY14, m_PHY14);
	DDX_Text(pDX, IDC_STATIC_PHY15, m_PHY15);
	DDX_Text(pDX, IDC_STATIC_VLT00, m_VLT00);
	DDX_Text(pDX, IDC_STATIC_VLT01, m_VLT01);
	DDX_Text(pDX, IDC_STATIC_VLT02, m_VLT02);
	DDX_Text(pDX, IDC_STATIC_VLT03, m_VLT03);
	DDX_Text(pDX, IDC_STATIC_VLT04, m_VLT04);
	DDX_Text(pDX, IDC_STATIC_VLT05, m_VLT05);
	DDX_Text(pDX, IDC_STATIC_VLT06, m_VLT06);
	DDX_Text(pDX, IDC_STATIC_VLT07, m_VLT07);
	DDX_Text(pDX, IDC_STATIC_VLT08, m_VLT08);
	DDX_Text(pDX, IDC_STATIC_VLT09, m_VLT09);
	DDX_Text(pDX, IDC_STATIC_VLT10, m_VLT10);
	DDX_Text(pDX, IDC_STATIC_VLT11, m_VLT11);
	DDX_Text(pDX, IDC_STATIC_VLT12, m_VLT12);
	DDX_Text(pDX, IDC_STATIC_VLT13, m_VLT13);
	DDX_Text(pDX, IDC_STATIC_VLT14, m_VLT14);
	DDX_Text(pDX, IDC_STATIC_VLT15, m_VLT15);
	DDX_Text(pDX, IDC_EDIT_DChannel, m_DChannel);
	//}}AFX_DATA_MAP
}

BOOL CDigitShowBasicView::PreCreateWindow(CREATESTRUCT& cs)
{	DigitShowContext* ctx = GetContext();
	// TODO: ・ｽ・ｽ・ｽﾌ位置・ｽ・ｽ CREATESTRUCT cs ・ｽ・ｽ・ｽC・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ Window ・ｽN・ｽ・ｽ・ｽX・ｽﾜゑｿｽ・ｽﾍス・ｽ^・ｽC・ｽ・ｽ・ｽ・ｽ
	//  ・ｽC・ｽ・ｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽB
	return CFormView::PreCreateWindow(cs);
}

void CDigitShowBasicView::OnInitialUpdate()
{	DigitShowContext* ctx = GetContext();
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
//
	CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_CtrlOff);
	CButton* myBTN2=(CButton*)GetDlgItem(IDC_BUTTON_StopSave);
	CButton* myBTN3=(CButton*)GetDlgItem(IDC_BUTTON_InterceptSave);
	CButton* myBTN4=(CButton*)GetDlgItem(IDC_BUTTON_FIFOStop);
	CButton* myBTN5=(CButton*)GetDlgItem(IDC_BUTTON_WriteData);
	myBTN1->EnableWindow(FALSE);
	myBTN2->EnableWindow(FALSE);
	myBTN3->EnableWindow(FALSE);
	myBTN4->EnableWindow(FALSE);
	myBTN5->EnableWindow(FALSE);
//
	CString tmp;
	CComboBox* m_Combo1 = (CComboBox*)GetDlgItem(IDC_COMBO_Control_ID);
	m_Combo1->InsertString(-1,"0");	m_Combo1->InsertString(-1,"1");
	m_Combo1->InsertString(-1,"2");	m_Combo1->InsertString(-1,"3");
	m_Combo1->InsertString(-1,"4");	m_Combo1->InsertString(-1,"5");
	m_Combo1->InsertString(-1,"6");	m_Combo1->InsertString(-1,"7");
	m_Combo1->InsertString(-1,"8");	m_Combo1->InsertString(-1,"9");
	m_Combo1->InsertString(-1,"10");	m_Combo1->InsertString(-1,"11");
	m_Combo1->InsertString(-1,"12");	m_Combo1->InsertString(-1,"13");
	m_Combo1->InsertString(-1,"14");	m_Combo1->InsertString(-1,"15");
	m_Combo1->SetWindowText("0");
	CComboBox* m_Combo2 = (CComboBox*)GetDlgItem(IDC_COMBO_SamplingTime);
	m_Combo2->InsertString(-1,"0.1 s");	
	m_Combo2->InsertString(-1,"0.2 s");		m_Combo2->InsertString(-1,"0.5 s");
	m_Combo2->InsertString(-1,"1.0 s");		m_Combo2->InsertString(-1,"2.0 s");
	m_Combo2->InsertString(-1,"3.0 s");		m_Combo2->InsertString(-1,"5.0 s");
	m_Combo2->InsertString(-1,"10.0 s");	m_Combo2->InsertString(-1,"20.0 s");
	m_Combo2->InsertString(-1,"30.0 s");	m_Combo2->InsertString(-1,"1.0 min");
	m_Combo2->InsertString(-1,"2.0 min");	m_Combo2->InsertString(-1,"3.0 min");
	m_Combo2->InsertString(-1,"5.0 min");	m_Combo2->InsertString(-1,"10.0 min");	
	m_Combo2->SetWindowText("1.0 s");
	Reflesh();
//
	CDigitShowBasicDoc* pDoc=(CDigitShowBasicDoc *)GetDocument();
	pDoc->OpenBoard();
	if(ctx->flags.SetBoard){
		if(ctx->NumAD>0)	{
			ctx->ad[0].ScanClock=long(1000/ctx->ad[0].Channels);	// Newer CONTEC drivers require ScanClock <= SamplingClock/CH (floor to the safe side)
			if(ctx->ad[0].ScanClock<1){ ctx->ad[0].ScanClock=1; }
			ctx->Ret = AioSetAiScanClock ( ctx->ad[0].Id , ctx->ad[0].ScanClock );
			ctx->Ret = AioGetAiScanClock ( ctx->ad[0].Id , &ctx->ad[0].ScanClock );
			ctx->Ret = AioSetAiSamplingClock ( ctx->ad[0].Id , 1000 );
			ctx->Ret = AioGetAiSamplingClock ( ctx->ad[0].Id , &ctx->ad[0].SamplingClock );
			ctx->ad[0].SamplingTimes=long(ctx->timeSettings.Interval1*1000/ctx->ad[0].SamplingClock);
			ctx->Ret = AioSetAiEventSamplingTimes ( ctx->ad[0].Id , ctx->ad[0].SamplingTimes );
			ctx->Ret = AioGetAiEventSamplingTimes ( ctx->ad[0].Id , &ctx->ad[0].SamplingTimes );
			ctx->Ret = AioSetAiStopTrigger(ctx->ad[0].Id, 4);
			ctx->Ret = AioResetAiMemory(ctx->ad[0].Id);
		}
		if(ctx->NumAD>1)	{
			ctx->ad[1].ScanClock=long(1000/ctx->ad[1].Channels);	// Newer CONTEC drivers require ScanClock <= SamplingClock/CH (floor to the safe side)
			if(ctx->ad[1].ScanClock<1){ ctx->ad[1].ScanClock=1; }
			ctx->Ret = AioSetAiScanClock ( ctx->ad[1].Id , ctx->ad[1].ScanClock );
			ctx->Ret = AioGetAiScanClock ( ctx->ad[1].Id , &ctx->ad[1].ScanClock );
			ctx->Ret = AioSetAiSamplingClock ( ctx->ad[1].Id , 1000 );
			ctx->Ret = AioGetAiSamplingClock ( ctx->ad[1].Id , &ctx->ad[1].SamplingClock );
			ctx->ad[1].SamplingTimes=long(ctx->timeSettings.Interval1*1000/ctx->ad[1].SamplingClock);
			ctx->Ret = AioSetAiEventSamplingTimes ( ctx->ad[1].Id , ctx->ad[1].SamplingTimes );
			ctx->Ret = AioGetAiEventSamplingTimes ( ctx->ad[1].Id , &ctx->ad[1].SamplingTimes );
			ctx->Ret = AioSetAiStopTrigger(ctx->ad[1].Id, 4);
			ctx->Ret = AioResetAiMemory(ctx->ad[1].Id);
		}
		ctx->AdEvent = AIE_DATA_NUM | AIE_OFERR | AIE_SCERR | AIE_ADERR;
		ctx->Ret = AioSetAiEvent(ctx->ad[ctx->NumAD-1].Id, m_hWnd, ctx->AdEvent);
		ctx->Ret = AioSetAiEventSamplingTimes(ctx->ad[ctx->NumAD-1].Id, ctx->ad[ctx->NumAD-1].SamplingTimes);
		if(ctx->NumAD>0) ctx->Ret = AioStartAi(ctx->ad[0].Id);
		if(ctx->NumAD>1) ctx->Ret = AioStartAi(ctx->ad[1].Id);
	}
	SetTimer(1,ctx->timeSettings.Interval1,NULL);
	CRS232C RS232C;
	RS232C.DoModal();	
}

/////////////////////////////////////////////////////////////////////////////
// CDigitShowBasicView ・ｽN・ｽ・ｽ・ｽX・ｽﾌ診・ｽf

#ifdef _DEBUG
void CDigitShowBasicView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDigitShowBasicView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CDigitShowBasicDoc* CDigitShowBasicView::GetDocument() // ・ｽ・ｽf・ｽo・ｽb・ｽO ・ｽo・ｽ[・ｽW・ｽ・ｽ・ｽ・ｽ・ｽﾍイ・ｽ・ｽ・ｽ・ｽ・ｽC・ｽ・ｽ・ｽﾅゑｿｽ・ｽB
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDigitShowBasicDoc)));
	return (CDigitShowBasicDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDigitShowBasicView ・ｽN・ｽ・ｽ・ｽX・ｽﾌ・ｿｽ・ｽb・ｽZ・ｽ[・ｽW ・ｽn・ｽ・ｽ・ｽh・ｽ・ｽ

HBRUSH CDigitShowBasicView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{	DigitShowContext* ctx = GetContext();
	switch(nCtlColor)
	{
		case CTLCOLOR_EDIT:
			pDC->SetBkColor(RGB(255,255,255));				// white background
			pDC->SetTextColor(RGB(0,0,0));					// black for text color in EDIT
			return (HBRUSH)(m_pEditBrush->GetSafeHandle());	// EDITBOX color
		case CTLCOLOR_STATIC:								// Static label properties  
			pDC->SetBkMode(TRANSPARENT);	
			pDC->SetTextColor(RGB(255,255,255)); 
			return (HBRUSH)(m_pStaticBrush->GetSafeHandle());  
		case CTLCOLOR_DLG:					 				// Setting Dialog Box Color
			pDC->SetTextColor(RGB(0,128,128)); 
			return (HBRUSH)(m_pDlgBrush->GetSafeHandle());
		default:
			return CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	}	
}
void CDigitShowBasicView::OnDestroy() 
{	DigitShowContext* ctx = GetContext();
	CFormView::OnDestroy();
	// TODO: ・ｽ・ｽ・ｽﾌ位置・ｽﾉ・ｿｽ・ｽb・ｽZ・ｽ[・ｽW ・ｽn・ｽ・ｽ・ｽh・ｽ・ｽ・ｽp・ｽﾌコ・ｽ[・ｽh・ｽ・ｽﾇ会ｿｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
	delete	m_pEditBrush;
	delete	m_pStaticBrush;	
	delete	m_pDlgBrush;
}
void CDigitShowBasicView::OnTimer(UINT_PTR nIDEvent)
{	DigitShowContext* ctx = GetContext();
	// TODO: ・ｽ・ｽ・ｽﾌ位置・ｽﾉ・ｿｽ・ｽb・ｽZ・ｽ[・ｽW ・ｽn・ｽ・ｽ・ｽh・ｽ・ｽ・ｽp・ｽﾌコ・ｽ[・ｽh・ｽ・ｽﾇ会ｿｽ・ｽ・ｽ・ｽ驍ｩ・ｽﾜゑｿｽ・ｽﾍデ・ｽt・ｽH・ｽ・ｽ・ｽg・ｽﾌ擾ｿｽ・ｽ・ｽ・ｽ・ｽ・ｽﾄび出・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ

	CDigitShowBasicDoc* pDoc=(CDigitShowBasicDoc *)GetDocument();

	switch (nIDEvent)
	{
	case 1:
		{ 
			ctx->NowTime=ctx->NowTime.GetCurrentTime();
			ctx->SNowTime=ctx->NowTime.Format("%m/%d  %H:%M:%S");
			if(ctx->flags.SaveData){
				ctx->SpanTime=ctx->NowTime-ctx->StartTime;
				ctx->SequentTime1=ctx->SpanTime.GetTotalSeconds();
			}	
			if(ctx->flags.SetBalance)	pDoc -> Rs232c_GetWeight();
			if(ctx->flags.SetBoard)	pDoc -> AD_INPUT();
			pDoc -> Cal_Physical();
			pDoc -> Cal_Param();
			ShowData();
		}
		break;
	case 2:
		{ 
			_ftime(&StepTime1);
			if(Flag_Ctrl==FALSE){
				StepTime0=StepTime1;
				Flag_Ctrl=TRUE;
			}
			ctx->CtrlStepTime=double(StepTime1.time-StepTime0.time)+double( (StepTime1.millitm-StepTime0.millitm)/1000.0 );
			StepTime0=StepTime1;
			if(ctx->flags.SetBoard)	pDoc -> Control_DA(); 
		}
		break;
	case 3:
		{ 
			_ftime(&NowTime2);
			ctx->SequentTime2=double(NowTime2.time-StartTime2.time)+double( (NowTime2.millitm-StartTime2.millitm)/1000.0 );
			if(ctx->flags.SetBoard)	pDoc -> AD_INPUT();
			pDoc -> Cal_Physical();
			pDoc -> Cal_Param();
			pDoc -> SaveToFile();
		}
		break;
	}	
	CFormView::OnTimer(nIDEvent);
}

void CDigitShowBasicView::ShowData()
{	DigitShowContext* ctx = GetContext();
	if(m_DChannel == "Ch.00-15"){
		m_Vout00.Format("%11.4f",ctx->ai.raw[0]);	m_Vout01.Format("%11.4f",ctx->ai.raw[1]);
		m_Vout02.Format("%11.4f",ctx->ai.raw[2]);	m_Vout03.Format("%11.4f",ctx->ai.raw[3]);
		m_Vout04.Format("%11.4f",ctx->ai.raw[4]); 	m_Vout05.Format("%11.4f",ctx->ai.raw[5]);
		m_Vout06.Format("%11.4f",ctx->ai.raw[6]); 	m_Vout07.Format("%11.4f",ctx->ai.raw[7]);
		m_Vout08.Format("%11.4f",ctx->ai.raw[8]);	m_Vout09.Format("%11.4f",ctx->ai.raw[9]);
		m_Vout10.Format("%11.4f",ctx->ai.raw[10]);	m_Vout11.Format("%11.4f",ctx->ai.raw[11]);
		m_Vout12.Format("%11.4f",ctx->ai.raw[12]);	m_Vout13.Format("%11.4f",ctx->ai.raw[13]);
		m_Vout14.Format("%11.4f",ctx->ai.raw[14]);	m_Vout15.Format("%11.4f",ctx->ai.raw[15]);		

		m_Phyout00.Format("%11.4f",ctx->ai.phy[0]);	m_Phyout01.Format("%11.4f",ctx->ai.phy[1]);
		m_Phyout02.Format("%11.4f",ctx->ai.phy[2]);	m_Phyout03.Format("%11.4f",ctx->ai.phy[3]);
		m_Phyout04.Format("%11.4f",ctx->ai.phy[4]);	m_Phyout05.Format("%11.4f",ctx->ai.phy[5]);
		m_Phyout06.Format("%11.4f",ctx->ai.phy[6]);	m_Phyout07.Format("%11.4f",ctx->ai.phy[7]);
		m_Phyout08.Format("%11.4f",ctx->ai.phy[8]);	m_Phyout09.Format("%11.4f",ctx->ai.phy[9]);
		m_Phyout10.Format("%11.4f",ctx->ai.phy[10]);	m_Phyout11.Format("%11.4f",ctx->ai.phy[11]);
		m_Phyout12.Format("%11.4f",ctx->ai.phy[12]);	m_Phyout13.Format("%11.4f",ctx->ai.phy[13]);
		m_Phyout14.Format("%11.4f",ctx->ai.phy[14]);	m_Phyout15.Format("%11.4f",ctx->ai.phy[15]);
	}
	else{
		m_Vout00.Format("%11.4f",ctx->ai.raw[16]);	m_Vout01.Format("%11.4f",ctx->ai.raw[17]);
		m_Vout02.Format("%11.4f",ctx->ai.raw[18]);	m_Vout03.Format("%11.4f",ctx->ai.raw[19]);
		m_Vout04.Format("%11.4f",ctx->ai.raw[20]); m_Vout05.Format("%11.4f",ctx->ai.raw[21]);
		m_Vout06.Format("%11.4f",ctx->ai.raw[22]); m_Vout07.Format("%11.4f",ctx->ai.raw[23]);
		m_Vout08.Format("%11.4f",ctx->ai.raw[24]);	m_Vout09.Format("%11.4f",ctx->ai.raw[25]);
		m_Vout10.Format("%11.4f",ctx->ai.raw[26]);	m_Vout11.Format("%11.4f",ctx->ai.raw[27]);
		m_Vout12.Format("%11.4f",ctx->ai.raw[28]);	m_Vout13.Format("%11.4f",ctx->ai.raw[29]);
		m_Vout14.Format("%11.4f",ctx->ai.raw[30]);	m_Vout15.Format("%11.4f",ctx->ai.raw[31]);		

		m_Phyout00.Format("%11.4f",ctx->ai.phy[16]);	m_Phyout01.Format("%11.4f",ctx->ai.phy[17]);
		m_Phyout02.Format("%11.4f",ctx->ai.phy[18]);	m_Phyout03.Format("%11.4f",ctx->ai.phy[19]);
		m_Phyout04.Format("%11.4f",ctx->ai.phy[20]);	m_Phyout05.Format("%11.4f",ctx->ai.phy[21]);
		m_Phyout06.Format("%11.4f",ctx->ai.phy[22]);	m_Phyout07.Format("%11.4f",ctx->ai.phy[23]);
		m_Phyout08.Format("%11.4f",ctx->ai.phy[24]);	m_Phyout09.Format("%11.4f",ctx->ai.phy[25]);
		m_Phyout10.Format("%11.4f",ctx->ai.phy[26]);	m_Phyout11.Format("%11.4f",ctx->ai.phy[27]);
		m_Phyout12.Format("%11.4f",ctx->ai.phy[28]);	m_Phyout13.Format("%11.4f",ctx->ai.phy[29]);
		m_Phyout14.Format("%11.4f",ctx->ai.phy[30]);	m_Phyout15.Format("%11.4f",ctx->ai.phy[31]);
	}
	m_Para00.Format("%11.5f",ctx->ai.param[0]);	m_Para01.Format("%11.5f",ctx->ai.param[1]);
	m_Para02.Format("%11.5f",ctx->ai.param[2]);	m_Para03.Format("%11.5f",ctx->ai.param[3]);
	m_Para04.Format("%11.5f",ctx->ai.param[4]);	m_Para05.Format("%11.5f",ctx->ai.param[5]);
	m_Para06.Format("%11.5f",ctx->ai.param[6]);	m_Para07.Format("%11.5f",ctx->ai.param[7]);
	m_Para08.Format("%11.5f",ctx->ai.param[8]);	m_Para09.Format("%11.5f",ctx->ai.param[9]);
	m_Para10.Format("%11.5f",ctx->ai.param[10]);	m_Para11.Format("%11.5f",ctx->ai.param[11]);
	m_Para12.Format("%11.5f",ctx->ai.param[12]);	m_Para13.Format("%11.5f",ctx->ai.param[13]);
	m_Para14.Format("%11.5f",ctx->ai.param[14]);	m_Para15.Format("%11.5f",ctx->ai.param[15]);
	m_Para16.Format("%11.5f",ctx->ai.param[16]);	m_Para17.Format("%11.5f",ctx->ai.param[17]);
	m_Para18.Format("%11.5f",ctx->ai.param[18]);	m_Para19.Format("%11.5f",ctx->ai.param[19]);
	m_Para20.Format("%11.5f",ctx->ai.param[20]);	m_Para21.Format("%11.5f",ctx->ai.param[21]);
	m_Para22.Format("%11.5f",ctx->ai.param[22]);	m_Para23.Format("%11.5f",ctx->ai.param[23]);
	
	m_Ctrl_ID=ctx->ControlID;
	m_NowTime=ctx->SNowTime;
	m_SeqTime=ctx->SequentTime1;
	m_SamplingTime=ctx->timeSettings.Interval3;
	if(ctx->flags.FIFO) m_SamplingTime=long(ctx->ad[0].SamplingClock/1000.0f);

	m_CFStepNo = ctx->controlFile.CurrentNum;
	m_CFCtrlPattern = ctx->controlFile.Num[ctx->controlFile.CurrentNum];
	m_CFCyclicNo = ctx->NumCyclic;
	m_CFStepTime = ctx->StepTime;
	UpdateData(FALSE);
}

void CDigitShowBasicView::OnBUTTONCtrlOn() 
{	DigitShowContext* ctx = GetContext();
	// TODO: ・ｽ・ｽ・ｽﾌ位置・ｽﾉコ・ｽ・ｽ・ｽg・ｽ・ｽ・ｽ[・ｽ・ｽ・ｽﾊ知・ｽn・ｽ・ｽ・ｽh・ｽ・ｽ・ｽp・ｽﾌコ・ｽ[・ｽh・ｽ・ｽﾇ会ｿｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
	CDigitShowBasicDoc* pDoc=(CDigitShowBasicDoc *)GetDocument();
	if(ctx->flags.SetBoard){
		SetTimer(2,ctx->timeSettings.Interval2,NULL);
		CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_CtrlOn);
		CButton* myBTN2=(CButton*)GetDlgItem(IDC_BUTTON_CtrlOff);
		myBTN1->EnableWindow(FALSE);	
		myBTN2->EnableWindow(TRUE);
		pDoc->Start_Control();
	}
}

void CDigitShowBasicView::OnBUTTONCtrlOff() 
{	DigitShowContext* ctx = GetContext();
	// TODO: ・ｽ・ｽ・ｽﾌ位置・ｽﾉコ・ｽ・ｽ・ｽg・ｽ・ｽ・ｽ[・ｽ・ｽ・ｽﾊ知・ｽn・ｽ・ｽ・ｽh・ｽ・ｽ・ｽp・ｽﾌコ・ｽ[・ｽh・ｽ・ｽﾇ会ｿｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
	CDigitShowBasicDoc* pDoc=(CDigitShowBasicDoc *)GetDocument();
	KillTimer(2);
	Flag_Ctrl=FALSE;
	CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_CtrlOn);
	CButton* myBTN2=(CButton*)GetDlgItem(IDC_BUTTON_CtrlOff);
	myBTN1->EnableWindow(TRUE);
	myBTN2->EnableWindow(FALSE);
	pDoc->Stop_Control();
}

void CDigitShowBasicView::OnBUTTONStartSave() 
{	DigitShowContext* ctx = GetContext();
	// TODO: ・ｽ・ｽ・ｽﾌ位置・ｽﾉコ・ｽ・ｽ・ｽg・ｽ・ｽ・ｽ[・ｽ・ｽ・ｽﾊ知・ｽn・ｽ・ｽ・ｽh・ｽ・ｽ・ｽp・ｽﾌコ・ｽ[・ｽh・ｽ・ｽﾇ会ｿｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ

	CString	pFileName0, pFileName1, pFileName2, TmpString;
	CDigitShowBasicDoc* pDoc=(CDigitShowBasicDoc *)GetDocument();
	int		i;

	if(ctx->flags.FIFO==FALSE){
		CFileDialog SaveFile_dlg( FALSE, NULL, "*.dat",  OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT,
				"Data Files(*.dat)|*.dat| All Files(*.*)|*.*| |",NULL);
		if(SaveFile_dlg.DoModal()==IDOK){
			// File for saving the physical data 
			pFileName1= SaveFile_dlg.GetPathName();	
			m_FileName=	SaveFile_dlg.GetFileTitle();
			TmpString = SaveFile_dlg.GetFileExt();	
			if(TmpString == "" ){
				TmpString=".dat";
				pFileName1=pFileName1+TmpString;
				m_FileName=m_FileName+TmpString;
			}
			else if(TmpString != "dat"){
				TmpString=_T(".")+TmpString;
				pFileName1.Replace(TmpString,".dat");
				m_FileName=m_FileName+_T(".dat");
			}
			ctx->FileSaveData1 = fopen((LPCSTR)pFileName1 , "w" );
			fprintf(ctx->FileSaveData1,"%s	","Time(s)");
			for(i=0;i<32;i++){
				fprintf(ctx->FileSaveData1,"%s	",ctx->NameP[i]);
			}
			fprintf(ctx->FileSaveData1,"\n");
			// File for saving the voltage data
			pFileName0=pFileName1;
			pFileName0.Replace(".dat",".vlt");
			ctx->FileSaveData0 = fopen((LPCSTR)pFileName0 , "w" );
			fprintf(ctx->FileSaveData0,"%s	","Time(s)");
			for(i=0;i<32;i++){
				fprintf(ctx->FileSaveData0,"%s	",ctx->NameV[i]);
			}
			fprintf(ctx->FileSaveData0,"\n");
			// File for saving the parameter data
			// @ Hashimoto modified 2023.02.28
			pFileName2=pFileName1;
			pFileName2.Replace(".dat",".out");
			ctx->FileSaveData2 = fopen((LPCSTR)pFileName2 , "w" );
			fprintf(ctx->FileSaveData2,"%s	","Time(s)");
			fprintf(ctx->FileSaveData2,"%s	","sigma(z)(kPa)");
			fprintf(ctx->FileSaveData2,"%s	","sigma(r)(kPa)");
			fprintf(ctx->FileSaveData2,"%s	","sigma(q)(kPa)");
			fprintf(ctx->FileSaveData2,"%s	","tau(zq)(kPa)");
			fprintf(ctx->FileSaveData2,"%s	","e_(vol.)");
			fprintf(ctx->FileSaveData2,"%s	","e_(z)");
			fprintf(ctx->FileSaveData2,"%s	","LDT1(mm)");
			fprintf(ctx->FileSaveData2,"%s	","LDT2(mm)");
			fprintf(ctx->FileSaveData2,"%s	","CG1(mm)");
			fprintf(ctx->FileSaveData2,"%s	","CG2(mm)");
			fprintf(ctx->FileSaveData2,"%s	","CG3(mm)");
			fprintf(ctx->FileSaveData2,"%s	","p_(kPa)");
			fprintf(ctx->FileSaveData2,"%s	","q_(kPa)");
			fprintf(ctx->FileSaveData2,"%s	","sigma(1)(kPa)");
			fprintf(ctx->FileSaveData2,"%s	","sigma(2)(kPa)");
			fprintf(ctx->FileSaveData2,"%s	","sigma(3)(kPa)");
			fprintf(ctx->FileSaveData2,"%s	","g1_(zq)");
			fprintf(ctx->FileSaveData2,"%s	","g2_(zq)");
			fprintf(ctx->FileSaveData2,"%s	","InCellPre(kPa)");
			fprintf(ctx->FileSaveData2,"%s	","OutCellPre(kPa)");
			fprintf(ctx->FileSaveData2,"%s	","InnerDia.(mm)");
			fprintf(ctx->FileSaveData2,"%s	","OuterDia.(mm)");
			fprintf(ctx->FileSaveData2,"%s	","Height(mm)");
			fprintf(ctx->FileSaveData2,"%s	","Volume(mm3)");

			
			// 2021.12.07 Edited by M.Kuno
			// customize for Sanjei
			fprintf(ctx->FileSaveData2, "%s	", "ControlStep");
			fprintf(ctx->FileSaveData2, "%s	", "Cyclic");
			fprintf(ctx->FileSaveData2,"\n");

// Timer starts
			SetTimer(3,ctx->timeSettings.Interval3,NULL);
			ctx->NowTime=ctx->NowTime.GetCurrentTime();
			ctx->StartTime=ctx->NowTime;
			ctx->SpanTime=ctx->NowTime-ctx->StartTime;
			ctx->SequentTime1=ctx->SpanTime.GetTotalSeconds();
//
			_ftime(&NowTime2);
			StartTime2=NowTime2;
			ctx->SequentTime2=double(NowTime2.time-StartTime2.time)+double( (NowTime2.millitm-StartTime2.millitm)/1000.0 );
//
			ctx->flags.SaveData=TRUE;
			CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_StartSave);
			CButton* myBTN2=(CButton*)GetDlgItem(IDC_BUTTON_StopSave);
			CButton* myBTN3=(CButton*)GetDlgItem(IDC_BUTTON_InterceptSave);
			CButton* myBTN4=(CButton*)GetDlgItem(IDC_BUTTON_FIFOStart);
			CButton* myBTN5=(CButton*)GetDlgItem(IDC_BUTTON_FIFOStop);
			myBTN1->EnableWindow(FALSE);	
			myBTN2->EnableWindow(TRUE);
			myBTN3->EnableWindow(TRUE);
			myBTN4->EnableWindow(FALSE);
			myBTN5->EnableWindow(FALSE);
//
			if(ctx->flags.SetBoard)	pDoc -> AD_INPUT();
			pDoc -> Cal_Physical();
			pDoc -> Cal_Param();
			pDoc -> SaveToFile();
		}
	}
	if(ctx->flags.SetBoard==TRUE && ctx->flags.FIFO==TRUE){
		ctx->NowTime=ctx->NowTime.GetCurrentTime();
		ctx->StartTime=ctx->NowTime;
		ctx->SpanTime=ctx->NowTime-ctx->StartTime;
		ctx->SequentTime1=ctx->SpanTime.GetTotalSeconds();
	    if(ctx->NumAD>0) ctx->Ret = AioStopAi(ctx->ad[0].Id);
		if(ctx->NumAD>1) ctx->Ret = AioStopAi(ctx->ad[1].Id);
		if(ctx->NumAD>2) ctx->Ret = AioStopAi(ctx->ad[2].Id);
		ctx->flags.SaveData=TRUE;
		ctx->CurrentSamplingTimes=0;
		pDoc->Allocate_Memory();
		CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_StartSave);
		CButton* myBTN2=(CButton*)GetDlgItem(IDC_BUTTON_StopSave);
		CButton* myBTN3=(CButton*)GetDlgItem(IDC_BUTTON_InterceptSave);
		CButton* myBTN4=(CButton*)GetDlgItem(IDC_BUTTON_FIFOStart);
		CButton* myBTN5=(CButton*)GetDlgItem(IDC_BUTTON_FIFOStop);
		CButton* myBTN6=(CButton*)GetDlgItem(IDC_BUTTON_WriteData);
		myBTN1->EnableWindow(FALSE);	
		myBTN2->EnableWindow(TRUE);
		myBTN3->EnableWindow(FALSE);
		myBTN4->EnableWindow(FALSE);
		myBTN5->EnableWindow(FALSE);
		myBTN6->EnableWindow(FALSE);
		if(ctx->NumAD>0) ctx->Ret = AioResetAiMemory(ctx->ad[0].Id);
		if(ctx->NumAD>1) ctx->Ret = AioResetAiMemory(ctx->ad[1].Id);
		if(ctx->NumAD>0) ctx->Ret = AioStartAi(ctx->ad[0].Id);
		if(ctx->NumAD>1) ctx->Ret = AioStartAi(ctx->ad[1].Id);
	}
}

void CDigitShowBasicView::OnBUTTONStopSave() 
{	DigitShowContext* ctx = GetContext();
	// TODO: ・ｽ・ｽ・ｽﾌ位置・ｽﾉコ・ｽ・ｽ・ｽg・ｽ・ｽ・ｽ[・ｽ・ｽ・ｽﾊ知・ｽn・ｽ・ｽ・ｽh・ｽ・ｽ・ｽp・ｽﾌコ・ｽ[・ｽh・ｽ・ｽﾇ会ｿｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ

	CDigitShowBasicDoc* pDoc=(CDigitShowBasicDoc *)GetDocument();

	if(ctx->flags.SaveData==TRUE && ctx->flags.FIFO==FALSE){
		KillTimer(3);
		ctx->NowTime=ctx->NowTime.GetCurrentTime();
		ctx->SpanTime=ctx->NowTime-ctx->StartTime;
		ctx->SequentTime1=ctx->SpanTime.GetTotalSeconds();
		_ftime(&NowTime2);
		ctx->SequentTime2=double(NowTime2.time-StartTime2.time)+double( (NowTime2.millitm-StartTime2.millitm)/1000.0 );
		if(ctx->flags.SetBoard)	pDoc -> AD_INPUT();
		pDoc -> Cal_Physical();
		pDoc -> Cal_Param();
		pDoc -> SaveToFile();
		fclose(ctx->FileSaveData0);
		fclose(ctx->FileSaveData1);
		fclose(ctx->FileSaveData2);
		CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_StartSave);
		CButton* myBTN2=(CButton*)GetDlgItem(IDC_BUTTON_StopSave);	
		CButton* myBTN3=(CButton*)GetDlgItem(IDC_BUTTON_InterceptSave);
		CButton* myBTN4=(CButton*)GetDlgItem(IDC_BUTTON_FIFOStart);
		CButton* myBTN5=(CButton*)GetDlgItem(IDC_BUTTON_FIFOStop);
		myBTN1->EnableWindow(TRUE);	
		myBTN2->EnableWindow(FALSE);
		myBTN3->EnableWindow(FALSE);	
		myBTN4->EnableWindow(TRUE);
		myBTN5->EnableWindow(FALSE);
		ctx->flags.SaveData=FALSE;
	}
	if(ctx->flags.SaveData==TRUE && ctx->flags.FIFO==TRUE){
		ctx->flags.SaveData=FALSE;
	    if(ctx->NumAD>0) ctx->Ret = AioStopAi(ctx->ad[0].Id);
		if(ctx->NumAD>1) ctx->Ret = AioStopAi(ctx->ad[1].Id);
		if(ctx->NumAD>0) ctx->Ret = AioResetAiMemory(ctx->ad[0].Id);
		if(ctx->NumAD>1) ctx->Ret = AioResetAiMemory(ctx->ad[1].Id);
		if(ctx->NumAD>0) ctx->Ret = AioStartAi(ctx->ad[0].Id);
		if(ctx->NumAD>1) ctx->Ret = AioStartAi(ctx->ad[1].Id);
		CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_StartSave);
		CButton* myBTN2=(CButton*)GetDlgItem(IDC_BUTTON_StopSave);	
		CButton* myBTN3=(CButton*)GetDlgItem(IDC_BUTTON_InterceptSave);
		CButton* myBTN4=(CButton*)GetDlgItem(IDC_BUTTON_FIFOStart);
		CButton* myBTN5=(CButton*)GetDlgItem(IDC_BUTTON_FIFOStop);
		CButton* myBTN6=(CButton*)GetDlgItem(IDC_BUTTON_WriteData);
		myBTN1->EnableWindow(TRUE);	
		myBTN2->EnableWindow(FALSE);
		myBTN3->EnableWindow(FALSE);	
		myBTN4->EnableWindow(FALSE);
		myBTN5->EnableWindow(TRUE);
		myBTN6->EnableWindow(TRUE);
	}
}

void CDigitShowBasicView::OnBUTTONInterceptSave() 
{	DigitShowContext* ctx = GetContext();
	// TODO: Add your control notification handler code here
	CDigitShowBasicDoc* pDoc=(CDigitShowBasicDoc *)GetDocument();
	_ftime(&NowTime2);
	ctx->SequentTime2=double(NowTime2.time-StartTime2.time)+double( (NowTime2.millitm-StartTime2.millitm)/1000.0 );	
	if(ctx->flags.SetBoard)	pDoc -> AD_INPUT();
	pDoc -> Cal_Physical();
	pDoc -> Cal_Param();
	pDoc -> SaveToFile();	
}
void CDigitShowBasicView::OnBUTTONFIFOStart() 
{	DigitShowContext* ctx = GetContext();
	// TODO: Add your control notification handler code here
	int	nResult;

	CDigitShowBasicDoc* pDoc=(CDigitShowBasicDoc *)GetDocument();
	CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_FIFOStart);
	CButton* myBTN2=(CButton*)GetDlgItem(IDC_BUTTON_FIFOStop);	

	if(ctx->flags.SetBoard==TRUE){
		if(ctx->NumAD>0) ctx->Ret = AioStopAi(ctx->ad[0].Id);
	    if(ctx->NumAD>1) ctx->Ret = AioStopAi(ctx->ad[1].Id);
		CSamplingSettings SamplingSettings;
		nResult = SamplingSettings.DoModal();
		if(nResult==IDOK){
			if(ctx->NumAD>0)	{
				ctx->Ret = AioSetAiScanClock ( ctx->ad[0].Id , ctx->ad[0].ScanClock );
				ctx->Ret = AioGetAiScanClock ( ctx->ad[0].Id , &ctx->ad[0].ScanClock );	
				ctx->Ret = AioSetAiSamplingClock ( ctx->ad[0].Id , ctx->ad[0].SamplingClock );
				ctx->Ret = AioGetAiSamplingClock ( ctx->ad[0].Id , &ctx->ad[0].SamplingClock );
				ctx->Ret = AioSetAiStopTrigger(ctx->ad[0].Id, 4);
				ctx->Ret = AioSetAiEventSamplingTimes ( ctx->ad[0].Id , ctx->ad[0].SamplingTimes );
				ctx->Ret = AioGetAiEventSamplingTimes ( ctx->ad[0].Id , &ctx->ad[0].SamplingTimes );
				ctx->Ret = AioResetAiMemory(ctx->ad[0].Id);
			}
			if(ctx->NumAD>1)	{
				ctx->Ret = AioSetAiScanClock ( ctx->ad[1].Id , ctx->ad[1].ScanClock );
				ctx->Ret = AioGetAiScanClock ( ctx->ad[1].Id , &ctx->ad[1].ScanClock );
				ctx->Ret = AioSetAiSamplingClock ( ctx->ad[1].Id , ctx->ad[1].SamplingClock );
				ctx->Ret = AioGetAiSamplingClock ( ctx->ad[1].Id , &ctx->ad[1].SamplingClock );
				ctx->Ret = AioSetAiStopTrigger(ctx->ad[1].Id, 4);
				ctx->Ret = AioSetAiEventSamplingTimes ( ctx->ad[1].Id , ctx->ad[1].SamplingTimes );
				ctx->Ret = AioGetAiEventSamplingTimes ( ctx->ad[1].Id , &ctx->ad[1].SamplingTimes );
				ctx->Ret = AioResetAiMemory(ctx->ad[1].Id);
			}
			ctx->Ret = AioSetAiEventSamplingTimes(ctx->ad[ctx->NumAD-1].Id, ctx->ad[ctx->NumAD-1].SamplingTimes);
			ctx->SavingClock=ctx->ad[0].SamplingClock;
			ctx->flags.FIFO=TRUE;
			myBTN1->EnableWindow(FALSE);
			myBTN2->EnableWindow(TRUE);
		}
		if(ctx->NumAD>0) ctx->Ret = AioStartAi(ctx->ad[0].Id);
		if(ctx->NumAD>1) ctx->Ret = AioStartAi(ctx->ad[1].Id);
	}
	else{
		AfxMessageBox("Board Setting has not been accomplished yet.", MB_OK | MB_ICONSTOP, 0);	
	}
}

void CDigitShowBasicView::OnBUTTONFIFOStop() 
{	DigitShowContext* ctx = GetContext();
	// TODO: Add your control notification handler code here
	CDigitShowBasicDoc* pDoc=(CDigitShowBasicDoc *)GetDocument();
	CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_FIFOStart);
	CButton* myBTN2=(CButton*)GetDlgItem(IDC_BUTTON_FIFOStop);	
    if(ctx->NumAD>0) ctx->Ret = AioStopAi(ctx->ad[0].Id);
    if(ctx->NumAD>1) ctx->Ret = AioStopAi(ctx->ad[1].Id);
	ctx->flags.FIFO=FALSE;
	myBTN1->EnableWindow(TRUE);
	myBTN2->EnableWindow(FALSE);
//
	if(ctx->NumAD>0)	{
		ctx->ad[0].ScanClock=long(1000/ctx->ad[0].Channels);	// Newer CONTEC drivers require ScanClock <= SamplingClock/CH (floor to the safe side)
		if(ctx->ad[0].ScanClock<1){ ctx->ad[0].ScanClock=1; }
		ctx->Ret = AioSetAiScanClock ( ctx->ad[0].Id , ctx->ad[0].ScanClock );
		ctx->Ret = AioGetAiScanClock ( ctx->ad[0].Id , &ctx->ad[0].ScanClock );
		ctx->Ret = AioSetAiSamplingClock ( ctx->ad[0].Id , 1000 );
		ctx->Ret = AioGetAiSamplingClock ( ctx->ad[0].Id , &ctx->ad[0].SamplingClock );
		ctx->ad[0].SamplingTimes=long(ctx->timeSettings.Interval1*1000/ctx->ad[0].SamplingClock);
		ctx->Ret = AioSetAiEventSamplingTimes ( ctx->ad[0].Id , ctx->ad[0].SamplingTimes );
		ctx->Ret = AioGetAiEventSamplingTimes ( ctx->ad[0].Id , &ctx->ad[0].SamplingTimes );
		ctx->Ret = AioSetAiStopTrigger(ctx->ad[0].Id, 4);
		ctx->Ret = AioResetAiMemory(ctx->ad[0].Id);
	}
	if(ctx->NumAD>1)	{
		ctx->ad[1].ScanClock=long(1000/ctx->ad[1].Channels);	// Newer CONTEC drivers require ScanClock <= SamplingClock/CH (floor to the safe side)
		if(ctx->ad[1].ScanClock<1){ ctx->ad[1].ScanClock=1; }
		ctx->Ret = AioSetAiScanClock ( ctx->ad[1].Id , ctx->ad[1].ScanClock );
		ctx->Ret = AioGetAiScanClock ( ctx->ad[1].Id , &ctx->ad[1].ScanClock );
		ctx->Ret = AioSetAiSamplingClock ( ctx->ad[1].Id , 1000 );
		ctx->Ret = AioGetAiSamplingClock ( ctx->ad[1].Id , &ctx->ad[1].SamplingClock );
		ctx->ad[1].SamplingTimes=long(ctx->timeSettings.Interval1*1000/ctx->ad[1].SamplingClock);
		ctx->Ret = AioSetAiEventSamplingTimes ( ctx->ad[1].Id , ctx->timeSettings.Interval1 );
		ctx->Ret = AioGetAiEventSamplingTimes ( ctx->ad[1].Id , &ctx->ad[1].SamplingTimes );
		ctx->Ret = AioSetAiStopTrigger(ctx->ad[1].Id, 4);
		ctx->Ret = AioResetAiMemory(ctx->ad[1].Id);
	}
	ctx->Ret = AioSetAiEventSamplingTimes(ctx->ad[ctx->NumAD-1].Id, ctx->ad[ctx->NumAD-1].SamplingTimes);
	if(ctx->NumAD>0) ctx->Ret = AioStartAi(ctx->ad[0].Id);
	if(ctx->NumAD>1) ctx->Ret = AioStartAi(ctx->ad[1].Id);
}
void CDigitShowBasicView::OnBUTTONWriteData() 
{	DigitShowContext* ctx = GetContext();
	// TODO: Add your control notification handler code here
	CString	pFileName0, pFileName1, TmpString;
	CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_WriteData);
	CDigitShowBasicDoc* pDoc=(CDigitShowBasicDoc *)GetDocument();
	int		i;

	if(ctx->flags.FIFO)	OnBUTTONFIFOStop();
    if(ctx->NumAD>0) ctx->Ret = AioStopAi(ctx->ad[0].Id);
    if(ctx->NumAD>1) ctx->Ret = AioStopAi(ctx->ad[1].Id);

	CFileDialog SaveFile_dlg( FALSE, NULL, "*.dat",  OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT,
	"Data Files(*.dat)|*.dat| All Files(*.*)|*.*| |",NULL);
	if (SaveFile_dlg.DoModal()==IDOK){
		// File for saving the physical data 
		pFileName1= SaveFile_dlg.GetPathName();	
		m_FileName=	SaveFile_dlg.GetFileTitle();
		TmpString = SaveFile_dlg.GetFileExt();	
		if(TmpString == "" ){
			TmpString=".dat";
			pFileName1=pFileName1+TmpString;
			m_FileName=m_FileName+TmpString;
		}
		else if(TmpString != "dat"){
			TmpString=_T(".")+TmpString;
			pFileName1.Replace(TmpString,".dat");
			m_FileName=m_FileName+_T(".dat");
		}
		ctx->FileSaveData1 = fopen((LPCSTR)pFileName1 , "w" );
		fprintf(ctx->FileSaveData1,"%s	","Time(s)");
		for(i=0;i<32;i++){
			fprintf(ctx->FileSaveData1,"%s	",ctx->NameP[i]);
		}
		fprintf(ctx->FileSaveData1,"\n");
		// File for saving the voltage data
		pFileName0=pFileName1;
		pFileName0.Replace(".dat",".vlt");
		ctx->FileSaveData0 = fopen((LPCSTR)pFileName0 , "w" );
		fprintf(ctx->FileSaveData0,"%s	","Time(s)");
		for(i=0;i<32;i++){
			fprintf(ctx->FileSaveData0,"%s	",ctx->NameV[i]);
		}
		fprintf(ctx->FileSaveData0,"\n");
		pDoc -> SaveToFile2();
		fclose(ctx->FileSaveData0);
		fclose(ctx->FileSaveData1);
		pDoc -> Allocate_Memory();
		myBTN1->EnableWindow(FALSE);
	}
	if(ctx->NumAD>0)	{
		ctx->ad[0].ScanClock=long(1000/ctx->ad[0].Channels);	// Newer CONTEC drivers require ScanClock <= SamplingClock/CH (floor to the safe side)
		if(ctx->ad[0].ScanClock<1){ ctx->ad[0].ScanClock=1; }
		ctx->Ret = AioSetAiScanClock ( ctx->ad[0].Id , ctx->ad[0].ScanClock );
		ctx->Ret = AioGetAiScanClock ( ctx->ad[0].Id , &ctx->ad[0].ScanClock );
		ctx->Ret = AioSetAiSamplingClock ( ctx->ad[0].Id , 1000 );
		ctx->Ret = AioGetAiSamplingClock ( ctx->ad[0].Id , &ctx->ad[0].SamplingClock );
		ctx->ad[0].SamplingTimes=long(ctx->timeSettings.Interval1*1000/ctx->ad[0].SamplingClock);
		ctx->Ret = AioSetAiEventSamplingTimes ( ctx->ad[0].Id , ctx->ad[0].SamplingTimes );
		ctx->Ret = AioGetAiEventSamplingTimes ( ctx->ad[0].Id , &ctx->ad[0].SamplingTimes );
		ctx->Ret = AioSetAiStopTrigger(ctx->ad[0].Id, 4);
		ctx->Ret = AioResetAiMemory(ctx->ad[0].Id);
	}
	if(ctx->NumAD>1)	{
		ctx->ad[1].ScanClock=long(1000/ctx->ad[1].Channels);	// Newer CONTEC drivers require ScanClock <= SamplingClock/CH (floor to the safe side)
		if(ctx->ad[1].ScanClock<1){ ctx->ad[1].ScanClock=1; }
		ctx->Ret = AioSetAiScanClock ( ctx->ad[1].Id , ctx->ad[1].ScanClock );
		ctx->Ret = AioGetAiScanClock ( ctx->ad[1].Id , &ctx->ad[1].ScanClock );
		ctx->Ret = AioSetAiSamplingClock ( ctx->ad[1].Id , 1000 );
		ctx->Ret = AioGetAiSamplingClock ( ctx->ad[1].Id , &ctx->ad[1].SamplingClock );
		ctx->ad[1].SamplingTimes=long(ctx->timeSettings.Interval1*1000/ctx->ad[1].SamplingClock);
		ctx->Ret = AioSetAiEventSamplingTimes ( ctx->ad[1].Id , ctx->timeSettings.Interval1 );
		ctx->Ret = AioGetAiEventSamplingTimes ( ctx->ad[1].Id , &ctx->ad[1].SamplingTimes );
		ctx->Ret = AioSetAiStopTrigger(ctx->ad[1].Id, 4);
		ctx->Ret = AioResetAiMemory(ctx->ad[1].Id);
	}
	ctx->Ret = AioSetAiEventSamplingTimes(ctx->ad[ctx->NumAD-1].Id, ctx->ad[ctx->NumAD-1].SamplingTimes);
	if(ctx->NumAD>0) ctx->Ret = AioStartAi(ctx->ad[0].Id);
	if(ctx->NumAD>1) ctx->Ret = AioStartAi(ctx->ad[1].Id);
}
void CDigitShowBasicView::OnBUTTONSetCtrlID() 
{	DigitShowContext* ctx = GetContext();
	// TODO: ・ｽ・ｽ・ｽﾌ位置・ｽﾉコ・ｽ・ｽ・ｽg・ｽ・ｽ・ｽ[・ｽ・ｽ・ｽﾊ知・ｽn・ｽ・ｽ・ｽh・ｽ・ｽ・ｽp・ｽﾌコ・ｽ[・ｽh・ｽ・ｽﾇ会ｿｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
	CString		tmp;
	CComboBox* m_Combo1 = (CComboBox*)GetDlgItem(IDC_COMBO_Control_ID);
	m_Combo1->GetWindowText(tmp);
	ctx->ControlID=atoi(tmp);	
}

void CDigitShowBasicView::OnBUTTONSetSamplingTime() 
{	DigitShowContext* ctx = GetContext();
	// TODO: ・ｽ・ｽ・ｽﾌ位置・ｽﾉコ・ｽ・ｽ・ｽg・ｽ・ｽ・ｽ[・ｽ・ｽ・ｽﾊ知・ｽn・ｽ・ｽ・ｽh・ｽ・ｽ・ｽp・ｽﾌコ・ｽ[・ｽh・ｽ・ｽﾇ会ｿｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
	CString		tmp;
	CComboBox* m_Combo1 = (CComboBox*)GetDlgItem(IDC_COMBO_SamplingTime);
	m_Combo1->GetWindowText(tmp);
	if(tmp=="0.1 s")	ctx->timeSettings.Interval3=100;
	if(tmp=="0.2 s")	ctx->timeSettings.Interval3=200;
	if(tmp=="0.5 s")	ctx->timeSettings.Interval3=500;
	if(tmp=="1.0 s")	ctx->timeSettings.Interval3=1000;
	if(tmp=="2.0 s")	ctx->timeSettings.Interval3=2000;
	if(tmp=="3.0 s")	ctx->timeSettings.Interval3=3000;
	if(tmp=="5.0 s")	ctx->timeSettings.Interval3=5000;
	if(tmp=="10.0 s")	ctx->timeSettings.Interval3=10000;
	if(tmp=="20.0 s")	ctx->timeSettings.Interval3=20000;
	if(tmp=="30.0 s")	ctx->timeSettings.Interval3=30000;
	if(tmp=="1.0 min")	ctx->timeSettings.Interval3=60000;
	if(tmp=="2.0 min")	ctx->timeSettings.Interval3=120000;
	if(tmp=="3.0 min")	ctx->timeSettings.Interval3=180000;
	if(tmp=="5.0 min")	ctx->timeSettings.Interval3=300000;
	if(tmp=="10.0 min")	ctx->timeSettings.Interval3=600000;
	if(ctx->flags.SaveData){
		KillTimer(3);
		SetTimer(3,ctx->timeSettings.Interval3,NULL);
	}	
}

void CDigitShowBasicView::OnBUTTONDChannel() 
{	DigitShowContext* ctx = GetContext();
	// TODO: Add your control notification handler code here
	if(m_DChannel == "Ch.00-15")	m_DChannel = "Ch.16-31";
	else							m_DChannel = "Ch.00-15";
	Reflesh();
}

void CDigitShowBasicView::Reflesh()
{	DigitShowContext* ctx = GetContext();
	if(m_DChannel == "Ch.00-15"){
		m_VLT00 = ctx->NameV[0];	m_VLT01 = ctx->NameV[1]; m_VLT02 = ctx->NameV[2]; m_VLT03 = ctx->NameV[3]; 
		m_VLT04 = ctx->NameV[4];	m_VLT05 = ctx->NameV[5]; m_VLT06 = ctx->NameV[6]; m_VLT07 = ctx->NameV[7];	
		m_VLT08 = ctx->NameV[8];	m_VLT09 = ctx->NameV[9]; m_VLT10 = ctx->NameV[10];m_VLT11 = ctx->NameV[11];
	    m_VLT12 = ctx->NameV[12];m_VLT13 = ctx->NameV[13];m_VLT14 = ctx->NameV[14];m_VLT15 = ctx->NameV[15];
		m_PHY00 = ctx->NameP[0];	m_PHY01 = ctx->NameP[1];	m_PHY02 = ctx->NameP[2]; m_PHY03 = ctx->NameP[3];
		m_PHY04 = ctx->NameP[4];	m_PHY05 = ctx->NameP[5];	m_PHY06 = ctx->NameP[6]; m_PHY07 = ctx->NameP[7];
		m_PHY08 = ctx->NameP[8];	m_PHY09 = ctx->NameP[9];	m_PHY10 = ctx->NameP[10];m_PHY11 = ctx->NameP[11];
		m_PHY12 = ctx->NameP[12];m_PHY13 = ctx->NameP[13];m_PHY14 = ctx->NameP[14];m_PHY15 = ctx->NameP[15];
	}
	if(m_DChannel == "Ch.16-31"){
		m_VLT00 = ctx->NameV[16]; m_VLT01 = ctx->NameV[17]; m_VLT02 = ctx->NameV[18]; m_VLT03 = ctx->NameV[19]; 
		m_VLT04 = ctx->NameV[20]; m_VLT05 = ctx->NameV[21]; m_VLT06 = ctx->NameV[22]; m_VLT07 = ctx->NameV[23];	
		m_VLT08 = ctx->NameV[24]; m_VLT09 = ctx->NameV[25]; m_VLT10 = ctx->NameV[26]; m_VLT11 = ctx->NameV[27];
	    m_VLT12 = ctx->NameV[28]; m_VLT13 = ctx->NameV[29]; m_VLT14 = ctx->NameV[30]; m_VLT15 = ctx->NameV[31];
		m_PHY00 = ctx->NameP[16]; m_PHY01 = ctx->NameP[17]; m_PHY02 = ctx->NameP[18]; m_PHY03 = ctx->NameP[19];
		m_PHY04 = ctx->NameP[20]; m_PHY05 = ctx->NameP[21]; m_PHY06 = ctx->NameP[22]; m_PHY07 = ctx->NameP[23];
		m_PHY08 = ctx->NameP[24]; m_PHY09 = ctx->NameP[25]; m_PHY10 = ctx->NameP[26]; m_PHY11 = ctx->NameP[27];
		m_PHY12 = ctx->NameP[28]; m_PHY13 = ctx->NameP[29]; m_PHY14 = ctx->NameP[30]; m_PHY15 = ctx->NameP[31];
	}
	UpdateData(FALSE);
}

LRESULT CDigitShowBasicView::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{	DigitShowContext* ctx = GetContext();
	// TODO: ・ｽ・ｽ・ｽﾌ位置・ｽﾉ固有・ｽﾌ擾ｿｽ・ｽ・ｽ・ｽ・ｽﾇ会ｿｽ・ｽ・ｽ・ｽ驍ｩ・ｽA・ｽﾜゑｿｽ・ｽﾍ奇ｿｽ{・ｽN・ｽ・ｽ・ｽX・ｽ・ｽ・ｽﾄび出・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
	int	i,j;

	switch(message){
	case AIOM_AIE_DATA_NUM:
		if(ctx->NumAD>0)	{
			ctx->Ret = AioGetAiSamplingCount ( ctx->ad[0].Id , &tmp0 );
			tmp=tmp0;
		}
		if(ctx->NumAD>1)	{
			ctx->Ret = AioGetAiSamplingCount ( ctx->ad[1].Id , &tmp1 );
			if(tmp>tmp1) tmp=tmp1;
		}
		if(ctx->NumAD>0){
			ctx->Ret = AioGetAiSamplingData(ctx->ad[0].Id, &tmp, &ctx->AdData0[0]);
		    if(ctx->Ret != 0){
			    ctx->Ret2 = AioGetErrorString(ctx->Ret, ctx->ErrorString);
				ctx->TextString.Format("AioGetAiSamplingData = %d : %s", ctx->Ret, ctx->ErrorString);
				AfxMessageBox(ctx->TextString, MB_ICONSTOP | MB_OK );
			}
		}
		if(ctx->NumAD>1){
			ctx->Ret = AioGetAiSamplingData(ctx->ad[1].Id, &tmp, &ctx->AdData1[0]);
		    if(ctx->Ret != 0){
			    ctx->Ret2 = AioGetErrorString(ctx->Ret, ctx->ErrorString);
				ctx->TextString.Format("AioGetAiSamplingData = %d : %s", ctx->Ret, ctx->ErrorString);
				AfxMessageBox(ctx->TextString, MB_ICONSTOP | MB_OK );
			}
		}
		if(ctx->flags.SaveData==TRUE && ctx->flags.FIFO==TRUE){
			for(i=0;i<tmp;i++){
				if(ctx->CurrentSamplingTimes>=ctx->TotalSamplingTimes) {
					OnBUTTONStopSave();
				}
				else{
					if(ctx->NumAD > 0){
						for(j=0;j<ctx->ad[0].Channels;j++){
							*((PLONG)ctx->pSmplData[0]+ctx->CurrentSamplingTimes*ctx->ad[0].Channels+j)=ctx->AdData0[i*ctx->ad[0].Channels+j];
						}
					}
					if(ctx->NumAD > 1){
						for(j=0;j<ctx->ad[1].Channels;j++){
							*((PLONG)ctx->pSmplData[1]+ctx->CurrentSamplingTimes*ctx->ad[1].Channels+j)=ctx->AdData1[i*ctx->ad[1].Channels+j];
						}
					}
					ctx->CurrentSamplingTimes=ctx->CurrentSamplingTimes+1;
				}
			}
		}
		return TRUE;
	case AIOM_AIE_OFERR:
		if(ctx->flags.FIFO){
			AfxMessageBox("FIFO sttoped by the over flow int the memory of A/D board.", MB_OK | MB_ICONSTOP, 0);	
		}
		else{
			if(ctx->NumAD>0){
				ctx->Ret = AioResetAiMemory(ctx->ad[0].Id);
				ctx->Ret = AioStartAi(ctx->ad[0].Id);
			}
			if(ctx->NumAD>1){
				ctx->Ret = AioResetAiMemory(ctx->ad[1].Id);
				ctx->Ret = AioStartAi(ctx->ad[1].Id);
			}
			AfxMessageBox("FIFO sttoped by the over flow, but restarted automatically.", MB_OK | MB_ICONSTOP, 0);	
		}
		return TRUE;
	case AIOM_AIE_SCERR:
		AfxMessageBox("FIFO sttoped by sampling error.", MB_OK | MB_ICONSTOP, 0);	
		return TRUE;
	case AIOM_AIE_ADERR:
		AfxMessageBox("FIFO sttoped by the error in A/D convert.", MB_OK | MB_ICONSTOP, 0);	
		return TRUE;
	case AIOM_AIE_END:
		AfxMessageBox("FIFO sttoped to reach the end.", MB_OK | MB_ICONSTOP, 0);	
		return TRUE;
	}	
	return CFormView::DefWindowProc(message, wParam, lParam);
}
