// DigitShowBasicView.cpp : CDigitShowBasicView �N���X�̓���̒�`���s���܂��B
//

#include "stdafx.h"
#include "DigitShowBasic.h"

#include "DigitShowBasicDoc.h"
#include "DigitShowBasicView.h"

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
extern	long		Ret,Ret2;
extern	int			NUMAD,NUMDA;		// The Number of A/D and D/A boards
extern	short		AdId[2];			// ID of A/D boards
extern	short		AdChannels[2];		// The Number of Channel
extern	long		DaData[262144];
extern	long		AdData0[16777216],AdData1[16777216];
extern	int			AdMaxCH;
extern	short		AdMemoryType[2];
extern	float		AdScanClock[2];
extern	float		AdSamplingClock[2];
extern	long		AdSamplingTimes[2];
extern	long		AdEvent;
extern	float		SavingClock;
extern	int			SavingTime;
extern	long		TotalSamplingTimes;
extern	long		CurrentSamplingTimes;
extern	float		AllocatedMemory;
extern	char		ErrorString[256];
extern	CString		TextString;

extern	PVOID		pSmplData0,pSmplData1;	// Source of binary data
		long		tmp,tmp0,tmp1;

//------
extern  CString		NameV[32], NameP[32];
extern	float		Vout[32];	
extern	double		Phyout[32];				
extern	double		CalParam[32];				

//---Flag---
extern	bool		Flag_SetBoard;
extern	bool		Flag_FIFO;
extern	bool		Flag_SaveData;
		bool		Flag_Ctrl;
extern	bool		Flag_SetBalance;

//---Control---
extern	int			Control_ID;
extern	int			Num_Cyclic;
extern	double		StepTime;

//---Control File---
extern	int			CURNUM;
extern	int			CFNUM[256];

//---Time---
extern	CTime		StartTime, NowTime;
extern	CTimeSpan	SpanTime;
extern	CString		SNowTime;
extern	long		SequentTime1;
extern	double		SequentTime2;
extern	double		CtrlStepTime;
extern	unsigned int	TimeInterval_1;
extern	unsigned int	TimeInterval_2;
extern	unsigned int	TimeInterval_3;
//---File---
extern	FILE        *FileSaveData0;
extern	FILE		*FileSaveData1;
extern	FILE		*FileSaveData2;
//
extern	CString		ReadBuffer1,ReadBuffer2;

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
// CDigitShowBasicView �N���X�̍\�z/����

CDigitShowBasicView::CDigitShowBasicView()
	: CFormView(CDigitShowBasicView::IDD)
{
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
	m_SamplingTime = TimeInterval_3;
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
	// TODO: ���̏ꏊ�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B
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
{
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
{
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B
	return CFormView::PreCreateWindow(cs);
}

void CDigitShowBasicView::OnInitialUpdate()
{
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
	if(Flag_SetBoard){
		if(NUMAD>0)	{
			AdScanClock[0]=long(1000/AdChannels[0]);	// Newer CONTEC drivers require ScanClock <= SamplingClock/CH (floor to the safe side)
			if(AdScanClock[0]<1){ AdScanClock[0]=1; }
			Ret = AioSetAiScanClock ( AdId[0] , AdScanClock[0] );
			Ret = AioGetAiScanClock ( AdId[0] , &AdScanClock[0] );
			Ret = AioSetAiSamplingClock ( AdId[0] , 1000 );
			Ret = AioGetAiSamplingClock ( AdId[0] , &AdSamplingClock[0] );
			AdSamplingTimes[0]=long(TimeInterval_1*1000/AdSamplingClock[0]);
			Ret = AioSetAiEventSamplingTimes ( AdId[0] , AdSamplingTimes[0] );
			Ret = AioGetAiEventSamplingTimes ( AdId[0] , &AdSamplingTimes[0] );
			Ret = AioSetAiStopTrigger(AdId[0], 4);
			Ret = AioResetAiMemory(AdId[0]);
		}
		if(NUMAD>1)	{
			AdScanClock[1]=long(1000/AdChannels[1]);	// Newer CONTEC drivers require ScanClock <= SamplingClock/CH (floor to the safe side)
			if(AdScanClock[1]<1){ AdScanClock[1]=1; }
			Ret = AioSetAiScanClock ( AdId[1] , AdScanClock[1] );
			Ret = AioGetAiScanClock ( AdId[1] , &AdScanClock[1] );
			Ret = AioSetAiSamplingClock ( AdId[1] , 1000 );
			Ret = AioGetAiSamplingClock ( AdId[1] , &AdSamplingClock[1] );
			AdSamplingTimes[1]=long(TimeInterval_1*1000/AdSamplingClock[1]);
			Ret = AioSetAiEventSamplingTimes ( AdId[1] , AdSamplingTimes[1] );
			Ret = AioGetAiEventSamplingTimes ( AdId[1] , &AdSamplingTimes[1] );
			Ret = AioSetAiStopTrigger(AdId[1], 4);
			Ret = AioResetAiMemory(AdId[1]);
		}
		AdEvent = AIE_DATA_NUM | AIE_OFERR | AIE_SCERR | AIE_ADERR;
		Ret = AioSetAiEvent(AdId[NUMAD-1], m_hWnd, AdEvent);
		Ret = AioSetAiEventSamplingTimes(AdId[NUMAD-1], AdSamplingTimes[NUMAD-1]);
		if(NUMAD>0) Ret = AioStartAi(AdId[0]);
		if(NUMAD>1) Ret = AioStartAi(AdId[1]);
	}
	SetTimer(1,TimeInterval_1,NULL);
	CRS232C RS232C;
	RS232C.DoModal();	
}

/////////////////////////////////////////////////////////////////////////////
// CDigitShowBasicView �N���X�̐f�f

#ifdef _DEBUG
void CDigitShowBasicView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDigitShowBasicView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CDigitShowBasicDoc* CDigitShowBasicView::GetDocument() // ��f�o�b�O �o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDigitShowBasicDoc)));
	return (CDigitShowBasicDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDigitShowBasicView �N���X�̃��b�Z�[�W �n���h��

HBRUSH CDigitShowBasicView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
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
{
	CFormView::OnDestroy();
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����Ă�������
	delete	m_pEditBrush;
	delete	m_pStaticBrush;	
	delete	m_pDlgBrush;
}
void CDigitShowBasicView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������

	CDigitShowBasicDoc* pDoc=(CDigitShowBasicDoc *)GetDocument();

	switch (nIDEvent)
	{
	case 1:
		{ 
			NowTime=NowTime.GetCurrentTime();
			SNowTime=NowTime.Format("%m/%d  %H:%M:%S");
			if(Flag_SaveData){
				SpanTime=NowTime-StartTime;
				SequentTime1=SpanTime.GetTotalSeconds();
			}	
			if(Flag_SetBalance)	pDoc -> Rs232c_GetWeight();
			if(Flag_SetBoard)	pDoc -> AD_INPUT();
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
			CtrlStepTime=double(StepTime1.time-StepTime0.time)+double( (StepTime1.millitm-StepTime0.millitm)/1000.0 );
			StepTime0=StepTime1;
			if(Flag_SetBoard)	pDoc -> Control_DA(); 
		}
		break;
	case 3:
		{ 
			_ftime(&NowTime2);
			SequentTime2=double(NowTime2.time-StartTime2.time)+double( (NowTime2.millitm-StartTime2.millitm)/1000.0 );
			if(Flag_SetBoard)	pDoc -> AD_INPUT();
			pDoc -> Cal_Physical();
			pDoc -> Cal_Param();
			pDoc -> SaveToFile();
		}
		break;
	}	
	CFormView::OnTimer(nIDEvent);
}

void CDigitShowBasicView::ShowData()
{
	if(m_DChannel == "Ch.00-15"){
		m_Vout00.Format("%11.4f",Vout[0]);	m_Vout01.Format("%11.4f",Vout[1]);
		m_Vout02.Format("%11.4f",Vout[2]);	m_Vout03.Format("%11.4f",Vout[3]);
		m_Vout04.Format("%11.4f",Vout[4]); 	m_Vout05.Format("%11.4f",Vout[5]);
		m_Vout06.Format("%11.4f",Vout[6]); 	m_Vout07.Format("%11.4f",Vout[7]);
		m_Vout08.Format("%11.4f",Vout[8]);	m_Vout09.Format("%11.4f",Vout[9]);
		m_Vout10.Format("%11.4f",Vout[10]);	m_Vout11.Format("%11.4f",Vout[11]);
		m_Vout12.Format("%11.4f",Vout[12]);	m_Vout13.Format("%11.4f",Vout[13]);
		m_Vout14.Format("%11.4f",Vout[14]);	m_Vout15.Format("%11.4f",Vout[15]);		

		m_Phyout00.Format("%11.4f",Phyout[0]);	m_Phyout01.Format("%11.4f",Phyout[1]);
		m_Phyout02.Format("%11.4f",Phyout[2]);	m_Phyout03.Format("%11.4f",Phyout[3]);
		m_Phyout04.Format("%11.4f",Phyout[4]);	m_Phyout05.Format("%11.4f",Phyout[5]);
		m_Phyout06.Format("%11.4f",Phyout[6]);	m_Phyout07.Format("%11.4f",Phyout[7]);
		m_Phyout08.Format("%11.4f",Phyout[8]);	m_Phyout09.Format("%11.4f",Phyout[9]);
		m_Phyout10.Format("%11.4f",Phyout[10]);	m_Phyout11.Format("%11.4f",Phyout[11]);
		m_Phyout12.Format("%11.4f",Phyout[12]);	m_Phyout13.Format("%11.4f",Phyout[13]);
		m_Phyout14.Format("%11.4f",Phyout[14]);	m_Phyout15.Format("%11.4f",Phyout[15]);
	}
	else{
		m_Vout00.Format("%11.4f",Vout[16]);	m_Vout01.Format("%11.4f",Vout[17]);
		m_Vout02.Format("%11.4f",Vout[18]);	m_Vout03.Format("%11.4f",Vout[19]);
		m_Vout04.Format("%11.4f",Vout[20]); m_Vout05.Format("%11.4f",Vout[21]);
		m_Vout06.Format("%11.4f",Vout[22]); m_Vout07.Format("%11.4f",Vout[23]);
		m_Vout08.Format("%11.4f",Vout[24]);	m_Vout09.Format("%11.4f",Vout[25]);
		m_Vout10.Format("%11.4f",Vout[26]);	m_Vout11.Format("%11.4f",Vout[27]);
		m_Vout12.Format("%11.4f",Vout[28]);	m_Vout13.Format("%11.4f",Vout[29]);
		m_Vout14.Format("%11.4f",Vout[30]);	m_Vout15.Format("%11.4f",Vout[31]);		

		m_Phyout00.Format("%11.4f",Phyout[16]);	m_Phyout01.Format("%11.4f",Phyout[17]);
		m_Phyout02.Format("%11.4f",Phyout[18]);	m_Phyout03.Format("%11.4f",Phyout[19]);
		m_Phyout04.Format("%11.4f",Phyout[20]);	m_Phyout05.Format("%11.4f",Phyout[21]);
		m_Phyout06.Format("%11.4f",Phyout[22]);	m_Phyout07.Format("%11.4f",Phyout[23]);
		m_Phyout08.Format("%11.4f",Phyout[24]);	m_Phyout09.Format("%11.4f",Phyout[25]);
		m_Phyout10.Format("%11.4f",Phyout[26]);	m_Phyout11.Format("%11.4f",Phyout[27]);
		m_Phyout12.Format("%11.4f",Phyout[28]);	m_Phyout13.Format("%11.4f",Phyout[29]);
		m_Phyout14.Format("%11.4f",Phyout[30]);	m_Phyout15.Format("%11.4f",Phyout[31]);
	}
	m_Para00.Format("%11.5f",CalParam[0]);	m_Para01.Format("%11.5f",CalParam[1]);
	m_Para02.Format("%11.5f",CalParam[2]);	m_Para03.Format("%11.5f",CalParam[3]);
	m_Para04.Format("%11.5f",CalParam[4]);	m_Para05.Format("%11.5f",CalParam[5]);
	m_Para06.Format("%11.5f",CalParam[6]);	m_Para07.Format("%11.5f",CalParam[7]);
	m_Para08.Format("%11.5f",CalParam[8]);	m_Para09.Format("%11.5f",CalParam[9]);
	m_Para10.Format("%11.5f",CalParam[10]);	m_Para11.Format("%11.5f",CalParam[11]);
	m_Para12.Format("%11.5f",CalParam[12]);	m_Para13.Format("%11.5f",CalParam[13]);
	m_Para14.Format("%11.5f",CalParam[14]);	m_Para15.Format("%11.5f",CalParam[15]);
	m_Para16.Format("%11.5f",CalParam[16]);	m_Para17.Format("%11.5f",CalParam[17]);
	m_Para18.Format("%11.5f",CalParam[18]);	m_Para19.Format("%11.5f",CalParam[19]);
	m_Para20.Format("%11.5f",CalParam[20]);	m_Para21.Format("%11.5f",CalParam[21]);
	m_Para22.Format("%11.5f",CalParam[22]);	m_Para23.Format("%11.5f",CalParam[23]);
	
	m_Ctrl_ID=Control_ID;
	m_NowTime=SNowTime;
	m_SeqTime=SequentTime1;
	m_SamplingTime=TimeInterval_3;
	if(Flag_FIFO) m_SamplingTime=long(AdSamplingClock[0]/1000.0f);

	m_CFStepNo = CURNUM;
	m_CFCtrlPattern = CFNUM[CURNUM];
	m_CFCyclicNo = Num_Cyclic;
	m_CFStepTime = StepTime;
	UpdateData(FALSE);
}

void CDigitShowBasicView::OnBUTTONCtrlOn() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CDigitShowBasicDoc* pDoc=(CDigitShowBasicDoc *)GetDocument();
	if(Flag_SetBoard){
		SetTimer(2,TimeInterval_2,NULL);
		CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_CtrlOn);
		CButton* myBTN2=(CButton*)GetDlgItem(IDC_BUTTON_CtrlOff);
		myBTN1->EnableWindow(FALSE);	
		myBTN2->EnableWindow(TRUE);
		pDoc->Start_Control();
	}
}

void CDigitShowBasicView::OnBUTTONCtrlOff() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
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
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������

	CString	pFileName0, pFileName1, pFileName2, TmpString;
	CDigitShowBasicDoc* pDoc=(CDigitShowBasicDoc *)GetDocument();
	int		i;

	if(Flag_FIFO==FALSE){
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
			FileSaveData1 = fopen((LPCSTR)pFileName1 , "w" );
			fprintf(FileSaveData1,"%s	","Time(s)");
			for(i=0;i<32;i++){
				fprintf(FileSaveData1,"%s	",NameP[i]);
			}
			fprintf(FileSaveData1,"\n");
			// File for saving the voltage data
			pFileName0=pFileName1;
			pFileName0.Replace(".dat",".vlt");
			FileSaveData0 = fopen((LPCSTR)pFileName0 , "w" );
			fprintf(FileSaveData0,"%s	","Time(s)");
			for(i=0;i<32;i++){
				fprintf(FileSaveData0,"%s	",NameV[i]);
			}
			fprintf(FileSaveData0,"\n");
			// File for saving the parameter data
			// @ Hashimoto modified 2023.02.28
			pFileName2=pFileName1;
			pFileName2.Replace(".dat",".out");
			FileSaveData2 = fopen((LPCSTR)pFileName2 , "w" );
			fprintf(FileSaveData2,"%s	","Time(s)");
			fprintf(FileSaveData2,"%s	","sigma(z)(kPa)");
			fprintf(FileSaveData2,"%s	","sigma(r)(kPa)");
			fprintf(FileSaveData2,"%s	","sigma(q)(kPa)");
			fprintf(FileSaveData2,"%s	","tau(zq)(kPa)");
			fprintf(FileSaveData2,"%s	","e_(vol.)");
			fprintf(FileSaveData2,"%s	","e_(z)");
			fprintf(FileSaveData2,"%s	","LDT1(mm)");
			fprintf(FileSaveData2,"%s	","LDT2(mm)");
			fprintf(FileSaveData2,"%s	","CG1(mm)");
			fprintf(FileSaveData2,"%s	","CG2(mm)");
			fprintf(FileSaveData2,"%s	","CG3(mm)");
			fprintf(FileSaveData2,"%s	","p_(kPa)");
			fprintf(FileSaveData2,"%s	","q_(kPa)");
			fprintf(FileSaveData2,"%s	","sigma(1)(kPa)");
			fprintf(FileSaveData2,"%s	","sigma(2)(kPa)");
			fprintf(FileSaveData2,"%s	","sigma(3)(kPa)");
			fprintf(FileSaveData2,"%s	","g1_(zq)");
			fprintf(FileSaveData2,"%s	","g2_(zq)");
			fprintf(FileSaveData2,"%s	","InCellPre(kPa)");
			fprintf(FileSaveData2,"%s	","OutCellPre(kPa)");
			fprintf(FileSaveData2,"%s	","InnerDia.(mm)");
			fprintf(FileSaveData2,"%s	","OuterDia.(mm)");
			fprintf(FileSaveData2,"%s	","Height(mm)");
			fprintf(FileSaveData2,"%s	","Volume(mm3)");

			
			// 2021.12.07 Edited by M.Kuno
			// customize for Sanjei
			fprintf(FileSaveData2, "%s	", "ControlStep");
			fprintf(FileSaveData2, "%s	", "Cyclic");
			fprintf(FileSaveData2,"\n");

// Timer starts
			SetTimer(3,TimeInterval_3,NULL);
			NowTime=NowTime.GetCurrentTime();
			StartTime=NowTime;
			SpanTime=NowTime-StartTime;
			SequentTime1=SpanTime.GetTotalSeconds();
//
			_ftime(&NowTime2);
			StartTime2=NowTime2;
			SequentTime2=double(NowTime2.time-StartTime2.time)+double( (NowTime2.millitm-StartTime2.millitm)/1000.0 );
//
			Flag_SaveData=TRUE;
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
			if(Flag_SetBoard)	pDoc -> AD_INPUT();
			pDoc -> Cal_Physical();
			pDoc -> Cal_Param();
			pDoc -> SaveToFile();
		}
	}
	if(Flag_SetBoard==TRUE && Flag_FIFO==TRUE){
		NowTime=NowTime.GetCurrentTime();
		StartTime=NowTime;
		SpanTime=NowTime-StartTime;
		SequentTime1=SpanTime.GetTotalSeconds();
	    if(NUMAD>0) Ret = AioStopAi(AdId[0]);
		if(NUMAD>1) Ret = AioStopAi(AdId[1]);
		if(NUMAD>2) Ret = AioStopAi(AdId[2]);
		Flag_SaveData=TRUE;
		CurrentSamplingTimes=0;
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
		if(NUMAD>0) Ret = AioResetAiMemory(AdId[0]);
		if(NUMAD>1) Ret = AioResetAiMemory(AdId[1]);
		if(NUMAD>0) Ret = AioStartAi(AdId[0]);
		if(NUMAD>1) Ret = AioStartAi(AdId[1]);
	}
}

void CDigitShowBasicView::OnBUTTONStopSave() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������

	CDigitShowBasicDoc* pDoc=(CDigitShowBasicDoc *)GetDocument();

	if(Flag_SaveData==TRUE && Flag_FIFO==FALSE){
		KillTimer(3);
		NowTime=NowTime.GetCurrentTime();
		SpanTime=NowTime-StartTime;
		SequentTime1=SpanTime.GetTotalSeconds();
		_ftime(&NowTime2);
		SequentTime2=double(NowTime2.time-StartTime2.time)+double( (NowTime2.millitm-StartTime2.millitm)/1000.0 );
		if(Flag_SetBoard)	pDoc -> AD_INPUT();
		pDoc -> Cal_Physical();
		pDoc -> Cal_Param();
		pDoc -> SaveToFile();
		fclose(FileSaveData0);
		fclose(FileSaveData1);
		fclose(FileSaveData2);
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
		Flag_SaveData=FALSE;
	}
	if(Flag_SaveData==TRUE && Flag_FIFO==TRUE){
		Flag_SaveData=FALSE;
	    if(NUMAD>0) Ret = AioStopAi(AdId[0]);
		if(NUMAD>1) Ret = AioStopAi(AdId[1]);
		if(NUMAD>0) Ret = AioResetAiMemory(AdId[0]);
		if(NUMAD>1) Ret = AioResetAiMemory(AdId[1]);
		if(NUMAD>0) Ret = AioStartAi(AdId[0]);
		if(NUMAD>1) Ret = AioStartAi(AdId[1]);
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
{
	// TODO: Add your control notification handler code here
	CDigitShowBasicDoc* pDoc=(CDigitShowBasicDoc *)GetDocument();
	_ftime(&NowTime2);
	SequentTime2=double(NowTime2.time-StartTime2.time)+double( (NowTime2.millitm-StartTime2.millitm)/1000.0 );	
	if(Flag_SetBoard)	pDoc -> AD_INPUT();
	pDoc -> Cal_Physical();
	pDoc -> Cal_Param();
	pDoc -> SaveToFile();	
}
void CDigitShowBasicView::OnBUTTONFIFOStart() 
{
	// TODO: Add your control notification handler code here
	int	nResult;

	CDigitShowBasicDoc* pDoc=(CDigitShowBasicDoc *)GetDocument();
	CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_FIFOStart);
	CButton* myBTN2=(CButton*)GetDlgItem(IDC_BUTTON_FIFOStop);	

	if(Flag_SetBoard==TRUE){
		if(NUMAD>0) Ret = AioStopAi(AdId[0]);
	    if(NUMAD>1) Ret = AioStopAi(AdId[1]);
		CSamplingSettings SamplingSettings;
		nResult = SamplingSettings.DoModal();
		if(nResult==IDOK){
			if(NUMAD>0)	{
				Ret = AioSetAiScanClock ( AdId[0] , AdScanClock[0] );
				Ret = AioGetAiScanClock ( AdId[0] , &AdScanClock[0] );	
				Ret = AioSetAiSamplingClock ( AdId[0] , AdSamplingClock[0] );
				Ret = AioGetAiSamplingClock ( AdId[0] , &AdSamplingClock[0] );
				Ret = AioSetAiStopTrigger(AdId[0], 4);
				Ret = AioSetAiEventSamplingTimes ( AdId[0] , AdSamplingTimes[0] );
				Ret = AioGetAiEventSamplingTimes ( AdId[0] , &AdSamplingTimes[0] );
				Ret = AioResetAiMemory(AdId[0]);
			}
			if(NUMAD>1)	{
				Ret = AioSetAiScanClock ( AdId[1] , AdScanClock[1] );
				Ret = AioGetAiScanClock ( AdId[1] , &AdScanClock[1] );
				Ret = AioSetAiSamplingClock ( AdId[1] , AdSamplingClock[1] );
				Ret = AioGetAiSamplingClock ( AdId[1] , &AdSamplingClock[1] );
				Ret = AioSetAiStopTrigger(AdId[1], 4);
				Ret = AioSetAiEventSamplingTimes ( AdId[1] , AdSamplingTimes[1] );
				Ret = AioGetAiEventSamplingTimes ( AdId[1] , &AdSamplingTimes[1] );
				Ret = AioResetAiMemory(AdId[1]);
			}
			Ret = AioSetAiEventSamplingTimes(AdId[NUMAD-1], AdSamplingTimes[NUMAD-1]);
			SavingClock=AdSamplingClock[0];
			Flag_FIFO=TRUE;
			myBTN1->EnableWindow(FALSE);
			myBTN2->EnableWindow(TRUE);
		}
		if(NUMAD>0) Ret = AioStartAi(AdId[0]);
		if(NUMAD>1) Ret = AioStartAi(AdId[1]);
	}
	else{
		AfxMessageBox("Board Setting has not been accomplished yet.", MB_OK | MB_ICONSTOP, 0);	
	}
}

void CDigitShowBasicView::OnBUTTONFIFOStop() 
{
	// TODO: Add your control notification handler code here
	CDigitShowBasicDoc* pDoc=(CDigitShowBasicDoc *)GetDocument();
	CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_FIFOStart);
	CButton* myBTN2=(CButton*)GetDlgItem(IDC_BUTTON_FIFOStop);	
    if(NUMAD>0) Ret = AioStopAi(AdId[0]);
    if(NUMAD>1) Ret = AioStopAi(AdId[1]);
	Flag_FIFO=FALSE;
	myBTN1->EnableWindow(TRUE);
	myBTN2->EnableWindow(FALSE);
//
	if(NUMAD>0)	{
		AdScanClock[0]=long(1000/AdChannels[0]);	// Newer CONTEC drivers require ScanClock <= SamplingClock/CH (floor to the safe side)
		if(AdScanClock[0]<1){ AdScanClock[0]=1; }
		Ret = AioSetAiScanClock ( AdId[0] , AdScanClock[0] );
		Ret = AioGetAiScanClock ( AdId[0] , &AdScanClock[0] );
		Ret = AioSetAiSamplingClock ( AdId[0] , 1000 );
		Ret = AioGetAiSamplingClock ( AdId[0] , &AdSamplingClock[0] );
		AdSamplingTimes[0]=long(TimeInterval_1*1000/AdSamplingClock[0]);
		Ret = AioSetAiEventSamplingTimes ( AdId[0] , AdSamplingTimes[0] );
		Ret = AioGetAiEventSamplingTimes ( AdId[0] , &AdSamplingTimes[0] );
		Ret = AioSetAiStopTrigger(AdId[0], 4);
		Ret = AioResetAiMemory(AdId[0]);
	}
	if(NUMAD>1)	{
		AdScanClock[1]=long(1000/AdChannels[1]);	// Newer CONTEC drivers require ScanClock <= SamplingClock/CH (floor to the safe side)
		if(AdScanClock[1]<1){ AdScanClock[1]=1; }
		Ret = AioSetAiScanClock ( AdId[1] , AdScanClock[1] );
		Ret = AioGetAiScanClock ( AdId[1] , &AdScanClock[1] );
		Ret = AioSetAiSamplingClock ( AdId[1] , 1000 );
		Ret = AioGetAiSamplingClock ( AdId[1] , &AdSamplingClock[1] );
		AdSamplingTimes[1]=long(TimeInterval_1*1000/AdSamplingClock[1]);
		Ret = AioSetAiEventSamplingTimes ( AdId[1] , TimeInterval_1 );
		Ret = AioGetAiEventSamplingTimes ( AdId[1] , &AdSamplingTimes[1] );
		Ret = AioSetAiStopTrigger(AdId[1], 4);
		Ret = AioResetAiMemory(AdId[1]);
	}
	Ret = AioSetAiEventSamplingTimes(AdId[NUMAD-1], AdSamplingTimes[NUMAD-1]);
	if(NUMAD>0) Ret = AioStartAi(AdId[0]);
	if(NUMAD>1) Ret = AioStartAi(AdId[1]);
}
void CDigitShowBasicView::OnBUTTONWriteData() 
{
	// TODO: Add your control notification handler code here
	CString	pFileName0, pFileName1, TmpString;
	CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_WriteData);
	CDigitShowBasicDoc* pDoc=(CDigitShowBasicDoc *)GetDocument();
	int		i;

	if(Flag_FIFO)	OnBUTTONFIFOStop();
    if(NUMAD>0) Ret = AioStopAi(AdId[0]);
    if(NUMAD>1) Ret = AioStopAi(AdId[1]);

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
		FileSaveData1 = fopen((LPCSTR)pFileName1 , "w" );
		fprintf(FileSaveData1,"%s	","Time(s)");
		for(i=0;i<32;i++){
			fprintf(FileSaveData1,"%s	",NameP[i]);
		}
		fprintf(FileSaveData1,"\n");
		// File for saving the voltage data
		pFileName0=pFileName1;
		pFileName0.Replace(".dat",".vlt");
		FileSaveData0 = fopen((LPCSTR)pFileName0 , "w" );
		fprintf(FileSaveData0,"%s	","Time(s)");
		for(i=0;i<32;i++){
			fprintf(FileSaveData0,"%s	",NameV[i]);
		}
		fprintf(FileSaveData0,"\n");
		pDoc -> SaveToFile2();
		fclose(FileSaveData0);
		fclose(FileSaveData1);
		pDoc -> Allocate_Memory();
		myBTN1->EnableWindow(FALSE);
	}
	if(NUMAD>0)	{
		AdScanClock[0]=long(1000/AdChannels[0]);	// Newer CONTEC drivers require ScanClock <= SamplingClock/CH (floor to the safe side)
		if(AdScanClock[0]<1){ AdScanClock[0]=1; }
		Ret = AioSetAiScanClock ( AdId[0] , AdScanClock[0] );
		Ret = AioGetAiScanClock ( AdId[0] , &AdScanClock[0] );
		Ret = AioSetAiSamplingClock ( AdId[0] , 1000 );
		Ret = AioGetAiSamplingClock ( AdId[0] , &AdSamplingClock[0] );
		AdSamplingTimes[0]=long(TimeInterval_1*1000/AdSamplingClock[0]);
		Ret = AioSetAiEventSamplingTimes ( AdId[0] , AdSamplingTimes[0] );
		Ret = AioGetAiEventSamplingTimes ( AdId[0] , &AdSamplingTimes[0] );
		Ret = AioSetAiStopTrigger(AdId[0], 4);
		Ret = AioResetAiMemory(AdId[0]);
	}
	if(NUMAD>1)	{
		AdScanClock[1]=long(1000/AdChannels[1]);	// Newer CONTEC drivers require ScanClock <= SamplingClock/CH (floor to the safe side)
		if(AdScanClock[1]<1){ AdScanClock[1]=1; }
		Ret = AioSetAiScanClock ( AdId[1] , AdScanClock[1] );
		Ret = AioGetAiScanClock ( AdId[1] , &AdScanClock[1] );
		Ret = AioSetAiSamplingClock ( AdId[1] , 1000 );
		Ret = AioGetAiSamplingClock ( AdId[1] , &AdSamplingClock[1] );
		AdSamplingTimes[1]=long(TimeInterval_1*1000/AdSamplingClock[1]);
		Ret = AioSetAiEventSamplingTimes ( AdId[1] , TimeInterval_1 );
		Ret = AioGetAiEventSamplingTimes ( AdId[1] , &AdSamplingTimes[1] );
		Ret = AioSetAiStopTrigger(AdId[1], 4);
		Ret = AioResetAiMemory(AdId[1]);
	}
	Ret = AioSetAiEventSamplingTimes(AdId[NUMAD-1], AdSamplingTimes[NUMAD-1]);
	if(NUMAD>0) Ret = AioStartAi(AdId[0]);
	if(NUMAD>1) Ret = AioStartAi(AdId[1]);
}
void CDigitShowBasicView::OnBUTTONSetCtrlID() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString		tmp;
	CComboBox* m_Combo1 = (CComboBox*)GetDlgItem(IDC_COMBO_Control_ID);
	m_Combo1->GetWindowText(tmp);
	Control_ID=atoi(tmp);	
}

void CDigitShowBasicView::OnBUTTONSetSamplingTime() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString		tmp;
	CComboBox* m_Combo1 = (CComboBox*)GetDlgItem(IDC_COMBO_SamplingTime);
	m_Combo1->GetWindowText(tmp);
	if(tmp=="0.1 s")	TimeInterval_3=100;
	if(tmp=="0.2 s")	TimeInterval_3=200;
	if(tmp=="0.5 s")	TimeInterval_3=500;
	if(tmp=="1.0 s")	TimeInterval_3=1000;
	if(tmp=="2.0 s")	TimeInterval_3=2000;
	if(tmp=="3.0 s")	TimeInterval_3=3000;
	if(tmp=="5.0 s")	TimeInterval_3=5000;
	if(tmp=="10.0 s")	TimeInterval_3=10000;
	if(tmp=="20.0 s")	TimeInterval_3=20000;
	if(tmp=="30.0 s")	TimeInterval_3=30000;
	if(tmp=="1.0 min")	TimeInterval_3=60000;
	if(tmp=="2.0 min")	TimeInterval_3=120000;
	if(tmp=="3.0 min")	TimeInterval_3=180000;
	if(tmp=="5.0 min")	TimeInterval_3=300000;
	if(tmp=="10.0 min")	TimeInterval_3=600000;
	if(Flag_SaveData){
		KillTimer(3);
		SetTimer(3,TimeInterval_3,NULL);
	}	
}

void CDigitShowBasicView::OnBUTTONDChannel() 
{
	// TODO: Add your control notification handler code here
	if(m_DChannel == "Ch.00-15")	m_DChannel = "Ch.16-31";
	else							m_DChannel = "Ch.00-15";
	Reflesh();
}

void CDigitShowBasicView::Reflesh()
{
	if(m_DChannel == "Ch.00-15"){
		m_VLT00 = NameV[0];	m_VLT01 = NameV[1]; m_VLT02 = NameV[2]; m_VLT03 = NameV[3]; 
		m_VLT04 = NameV[4];	m_VLT05 = NameV[5]; m_VLT06 = NameV[6]; m_VLT07 = NameV[7];	
		m_VLT08 = NameV[8];	m_VLT09 = NameV[9]; m_VLT10 = NameV[10];m_VLT11 = NameV[11];
	    m_VLT12 = NameV[12];m_VLT13 = NameV[13];m_VLT14 = NameV[14];m_VLT15 = NameV[15];
		m_PHY00 = NameP[0];	m_PHY01 = NameP[1];	m_PHY02 = NameP[2]; m_PHY03 = NameP[3];
		m_PHY04 = NameP[4];	m_PHY05 = NameP[5];	m_PHY06 = NameP[6]; m_PHY07 = NameP[7];
		m_PHY08 = NameP[8];	m_PHY09 = NameP[9];	m_PHY10 = NameP[10];m_PHY11 = NameP[11];
		m_PHY12 = NameP[12];m_PHY13 = NameP[13];m_PHY14 = NameP[14];m_PHY15 = NameP[15];
	}
	if(m_DChannel == "Ch.16-31"){
		m_VLT00 = NameV[16]; m_VLT01 = NameV[17]; m_VLT02 = NameV[18]; m_VLT03 = NameV[19]; 
		m_VLT04 = NameV[20]; m_VLT05 = NameV[21]; m_VLT06 = NameV[22]; m_VLT07 = NameV[23];	
		m_VLT08 = NameV[24]; m_VLT09 = NameV[25]; m_VLT10 = NameV[26]; m_VLT11 = NameV[27];
	    m_VLT12 = NameV[28]; m_VLT13 = NameV[29]; m_VLT14 = NameV[30]; m_VLT15 = NameV[31];
		m_PHY00 = NameP[16]; m_PHY01 = NameP[17]; m_PHY02 = NameP[18]; m_PHY03 = NameP[19];
		m_PHY04 = NameP[20]; m_PHY05 = NameP[21]; m_PHY06 = NameP[22]; m_PHY07 = NameP[23];
		m_PHY08 = NameP[24]; m_PHY09 = NameP[25]; m_PHY10 = NameP[26]; m_PHY11 = NameP[27];
		m_PHY12 = NameP[28]; m_PHY13 = NameP[29]; m_PHY14 = NameP[30]; m_PHY15 = NameP[31];
	}
	UpdateData(FALSE);
}

LRESULT CDigitShowBasicView::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	int	i,j;

	switch(message){
	case AIOM_AIE_DATA_NUM:
		if(NUMAD>0)	{
			Ret = AioGetAiSamplingCount ( AdId[0] , &tmp0 );
			tmp=tmp0;
		}
		if(NUMAD>1)	{
			Ret = AioGetAiSamplingCount ( AdId[1] , &tmp1 );
			if(tmp>tmp1) tmp=tmp1;
		}
		if(NUMAD>0){
			Ret = AioGetAiSamplingData(AdId[0], &tmp, &AdData0[0]);
		    if(Ret != 0){
			    Ret2 = AioGetErrorString(Ret, ErrorString);
				TextString.Format("AioGetAiSamplingData = %d : %s", Ret, ErrorString);
				AfxMessageBox(TextString, MB_ICONSTOP | MB_OK );
			}
		}
		if(NUMAD>1){
			Ret = AioGetAiSamplingData(AdId[1], &tmp, &AdData1[0]);
		    if(Ret != 0){
			    Ret2 = AioGetErrorString(Ret, ErrorString);
				TextString.Format("AioGetAiSamplingData = %d : %s", Ret, ErrorString);
				AfxMessageBox(TextString, MB_ICONSTOP | MB_OK );
			}
		}
		if(Flag_SaveData==TRUE && Flag_FIFO==TRUE){
			for(i=0;i<tmp;i++){
				if(CurrentSamplingTimes>=TotalSamplingTimes) {
					OnBUTTONStopSave();
				}
				else{
					if(NUMAD > 0){
						for(j=0;j<AdChannels[0];j++){
							*((PLONG)pSmplData0+CurrentSamplingTimes*AdChannels[0]+j)=AdData0[i*AdChannels[0]+j];
						}
					}
					if(NUMAD > 1){
						for(j=0;j<AdChannels[1];j++){
							*((PLONG)pSmplData1+CurrentSamplingTimes*AdChannels[1]+j)=AdData1[i*AdChannels[1]+j];
						}
					}
					CurrentSamplingTimes=CurrentSamplingTimes+1;
				}
			}
		}
		return TRUE;
	case AIOM_AIE_OFERR:
		if(Flag_FIFO){
			AfxMessageBox("FIFO sttoped by the over flow int the memory of A/D board.", MB_OK | MB_ICONSTOP, 0);	
		}
		else{
			if(NUMAD>0){
				Ret = AioResetAiMemory(AdId[0]);
				Ret = AioStartAi(AdId[0]);
			}
			if(NUMAD>1){
				Ret = AioResetAiMemory(AdId[1]);
				Ret = AioStartAi(AdId[1]);
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
