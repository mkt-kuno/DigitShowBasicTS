// CalibrationFactor.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "DigitShowBasic.h"
#include "CalibrationFactor.h"
#include "DigitShowContext.h"

#include "CalibrationAmp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalibrationFactor ダイアログ
// CDigitShowBasicView
CCalibrationFactor::CCalibrationFactor(CWnd* pParent /*=NULL*/)
	: CDialog(CCalibrationFactor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalibrationFactor)
	m_CFP00 = _T("");
	m_CFP01 = _T("");	m_CFP02 = _T("");	m_CFP03 = _T("");
	m_CFP04 = _T("");	m_CFP05 = _T("");	m_CFP06 = _T("");
	m_CFP07 = _T("");	m_CFP08 = _T("");	m_CFP09 = _T("");
	m_CFP10 = _T("");	m_CFP11 = _T("");	m_CFP12 = _T("");
	m_CFP13 = _T("");	m_CFP14 = _T("");	m_CFP15 = _T("");	
	m_CFA00=0.0;	m_CFB00=0.0;	m_CFC00=0.0;
	m_CFA01=0.0;	m_CFB01=0.0;	m_CFC01=0.0;
	m_CFA02=0.0;	m_CFB02=0.0;	m_CFC02=0.0;
	m_CFA03=0.0;	m_CFB03=0.0;	m_CFC03=0.0;
	m_CFA04=0.0;	m_CFB04=0.0;	m_CFC04=0.0;
	m_CFA05=0.0;	m_CFB05=0.0;	m_CFC05=0.0;
	m_CFA06=0.0;	m_CFB06=0.0;	m_CFC06=0.0;
	m_CFA07=0.0;	m_CFB07=0.0;	m_CFC07=0.0;
	m_CFA08=0.0;	m_CFB08=0.0;	m_CFC08=0.0;
	m_CFA09=0.0;	m_CFB09=0.0;	m_CFC09=0.0;
	m_CFA10=0.0;	m_CFB10=0.0;	m_CFC10=0.0;
	m_CFA11=0.0;	m_CFB11=0.0;	m_CFC11=0.0;
	m_CFA12=0.0;	m_CFB12=0.0;	m_CFC12=0.0;	
	m_CFA13=0.0;	m_CFB13=0.0;	m_CFC13=0.0;
	m_CFA14=0.0;	m_CFB14=0.0;	m_CFC14=0.0;	
	m_CFA15=0.0;	m_CFB15=0.0;	m_CFC15=0.0;		
	m_CH00 = _T("");
	m_CH01 = _T("");
	m_CH02 = _T("");
	m_CH03 = _T("");
	m_CH04 = _T("");
	m_CH05 = _T("");
	m_CH06 = _T("");
	m_CH07 = _T("");
	m_CH08 = _T("");
	m_CH09 = _T("");
	m_CH10 = _T("");
	m_CH11 = _T("");
	m_CH12 = _T("");
	m_CH13 = _T("");
	m_CH14 = _T("");
	m_CH15 = _T("");
	m_DChannel = _T("");
	//}}AFX_DATA_INIT
}

void CCalibrationFactor::DoDataExchange(CDataExchange* pDX)
{	DigitShowContext* ctx = GetContext();
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalibrationFactor)
	DDX_Control(pDX, IDC_BUTTON_Amp15, m_Amp15);
	DDX_Control(pDX, IDC_BUTTON_Amp14, m_Amp14);
	DDX_Control(pDX, IDC_BUTTON_Amp13, m_Amp13);
	DDX_Control(pDX, IDC_BUTTON_Amp12, m_Amp12);
	DDX_Control(pDX, IDC_BUTTON_Amp11, m_Amp11);
	DDX_Control(pDX, IDC_BUTTON_Amp10, m_Amp10);
	DDX_Control(pDX, IDC_BUTTON_Amp09, m_Amp09);
	DDX_Control(pDX, IDC_BUTTON_Amp08, m_Amp08);
	DDX_Control(pDX, IDC_BUTTON_Amp07, m_Amp07);
	DDX_Control(pDX, IDC_BUTTON_Amp06, m_Amp06);
	DDX_Control(pDX, IDC_BUTTON_Amp05, m_Amp05);
	DDX_Control(pDX, IDC_BUTTON_Amp04, m_Amp04);
	DDX_Control(pDX, IDC_BUTTON_Amp03, m_Amp03);
	DDX_Control(pDX, IDC_BUTTON_Amp02, m_Amp02);
	DDX_Control(pDX, IDC_BUTTON_Amp01, m_Amp01);
	DDX_Control(pDX, IDC_BUTTON_Amp00, m_Amp00);
	DDX_Text(pDX, IDC_EDIT_CFP00, m_CFP00);
	DDX_Text(pDX, IDC_EDIT_CFP01, m_CFP01);
	DDX_Text(pDX, IDC_EDIT_CFP02, m_CFP02);
	DDX_Text(pDX, IDC_EDIT_CFP03, m_CFP03);
	DDX_Text(pDX, IDC_EDIT_CFP04, m_CFP04);
	DDX_Text(pDX, IDC_EDIT_CFP05, m_CFP05);
	DDX_Text(pDX, IDC_EDIT_CFP06, m_CFP06);
	DDX_Text(pDX, IDC_EDIT_CFP07, m_CFP07);
	DDX_Text(pDX, IDC_EDIT_CFP08, m_CFP08);
	DDX_Text(pDX, IDC_EDIT_CFP09, m_CFP09);
	DDX_Text(pDX, IDC_EDIT_CFP10, m_CFP10);
	DDX_Text(pDX, IDC_EDIT_CFP11, m_CFP11);
	DDX_Text(pDX, IDC_EDIT_CFP12, m_CFP12);
	DDX_Text(pDX, IDC_EDIT_CFP13, m_CFP13);	
	DDX_Text(pDX, IDC_EDIT_CFP14, m_CFP14);
	DDX_Text(pDX, IDC_EDIT_CFP15, m_CFP15);
	DDX_Text(pDX, IDC_EDIT_CFA00, m_CFA00);
	DDX_Text(pDX, IDC_EDIT_CFA01, m_CFA01);
	DDX_Text(pDX, IDC_EDIT_CFA02, m_CFA02);
	DDX_Text(pDX, IDC_EDIT_CFA03, m_CFA03);
	DDX_Text(pDX, IDC_EDIT_CFA04, m_CFA04);
	DDX_Text(pDX, IDC_EDIT_CFA05, m_CFA05);
	DDX_Text(pDX, IDC_EDIT_CFA06, m_CFA06);
	DDX_Text(pDX, IDC_EDIT_CFA07, m_CFA07);
	DDX_Text(pDX, IDC_EDIT_CFA08, m_CFA08);
	DDX_Text(pDX, IDC_EDIT_CFA09, m_CFA09);
	DDX_Text(pDX, IDC_EDIT_CFA10, m_CFA10);
	DDX_Text(pDX, IDC_EDIT_CFA11, m_CFA11);
	DDX_Text(pDX, IDC_EDIT_CFA12, m_CFA12);
	DDX_Text(pDX, IDC_EDIT_CFA13, m_CFA13);
	DDX_Text(pDX, IDC_EDIT_CFA14, m_CFA14);
	DDX_Text(pDX, IDC_EDIT_CFA15, m_CFA15);
	DDX_Text(pDX, IDC_EDIT_CFB00, m_CFB00);
	DDX_Text(pDX, IDC_EDIT_CFB01, m_CFB01);
	DDX_Text(pDX, IDC_EDIT_CFB02, m_CFB02);
	DDX_Text(pDX, IDC_EDIT_CFB03, m_CFB03);
	DDX_Text(pDX, IDC_EDIT_CFB04, m_CFB04);
	DDX_Text(pDX, IDC_EDIT_CFB05, m_CFB05);
	DDX_Text(pDX, IDC_EDIT_CFB06, m_CFB06);
	DDX_Text(pDX, IDC_EDIT_CFB07, m_CFB07);
	DDX_Text(pDX, IDC_EDIT_CFB08, m_CFB08);
	DDX_Text(pDX, IDC_EDIT_CFB09, m_CFB09);
	DDX_Text(pDX, IDC_EDIT_CFB10, m_CFB10);
	DDX_Text(pDX, IDC_EDIT_CFB11, m_CFB11);
	DDX_Text(pDX, IDC_EDIT_CFB12, m_CFB12);
	DDX_Text(pDX, IDC_EDIT_CFB13, m_CFB13);
	DDX_Text(pDX, IDC_EDIT_CFB14, m_CFB14);
	DDX_Text(pDX, IDC_EDIT_CFB15, m_CFB15);
	DDX_Text(pDX, IDC_EDIT_CFC00, m_CFC00);
	DDX_Text(pDX, IDC_EDIT_CFC01, m_CFC01);
	DDX_Text(pDX, IDC_EDIT_CFC02, m_CFC02);
	DDX_Text(pDX, IDC_EDIT_CFC03, m_CFC03);
	DDX_Text(pDX, IDC_EDIT_CFC04, m_CFC04);
	DDX_Text(pDX, IDC_EDIT_CFC05, m_CFC05);
	DDX_Text(pDX, IDC_EDIT_CFC06, m_CFC06);
	DDX_Text(pDX, IDC_EDIT_CFC07, m_CFC07);
	DDX_Text(pDX, IDC_EDIT_CFC08, m_CFC08);
	DDX_Text(pDX, IDC_EDIT_CFC09, m_CFC09);
	DDX_Text(pDX, IDC_EDIT_CFC10, m_CFC10);
	DDX_Text(pDX, IDC_EDIT_CFC11, m_CFC11);
	DDX_Text(pDX, IDC_EDIT_CFC12, m_CFC12);
	DDX_Text(pDX, IDC_EDIT_CFC13, m_CFC13);
	DDX_Text(pDX, IDC_EDIT_CFC14, m_CFC14);
	DDX_Text(pDX, IDC_EDIT_CFC15, m_CFC15);
	DDX_Text(pDX, IDC_STATIC_CH00, m_CH00);
	DDX_Text(pDX, IDC_STATIC_CH01, m_CH01);
	DDX_Text(pDX, IDC_STATIC_CH02, m_CH02);
	DDX_Text(pDX, IDC_STATIC_CH03, m_CH03);
	DDX_Text(pDX, IDC_STATIC_CH04, m_CH04);
	DDX_Text(pDX, IDC_STATIC_CH05, m_CH05);
	DDX_Text(pDX, IDC_STATIC_CH06, m_CH06);
	DDX_Text(pDX, IDC_STATIC_CH07, m_CH07);
	DDX_Text(pDX, IDC_STATIC_CH08, m_CH08);
	DDX_Text(pDX, IDC_STATIC_CH09, m_CH09);
	DDX_Text(pDX, IDC_STATIC_CH10, m_CH10);
	DDX_Text(pDX, IDC_STATIC_CH11, m_CH11);
	DDX_Text(pDX, IDC_STATIC_CH12, m_CH12);
	DDX_Text(pDX, IDC_STATIC_CH13, m_CH13);
	DDX_Text(pDX, IDC_STATIC_CH14, m_CH14);
	DDX_Text(pDX, IDC_STATIC_CH15, m_CH15);
	DDX_Text(pDX, IDC_EDIT_DChannel, m_DChannel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCalibrationFactor, CDialog)
	//{{AFX_MSG_MAP(CCalibrationFactor)
	ON_BN_CLICKED(IDC_BUTTON_CFUpdate, OnBUTTONCFUpdate)
	ON_BN_CLICKED(IDC_BUTTON_Zero00, OnBUTTONZero00)
	ON_BN_CLICKED(IDC_BUTTON_Zero01, OnBUTTONZero01)
	ON_BN_CLICKED(IDC_BUTTON_Zero02, OnBUTTONZero02)
	ON_BN_CLICKED(IDC_BUTTON_Zero03, OnBUTTONZero03)
	ON_BN_CLICKED(IDC_BUTTON_Zero04, OnBUTTONZero04)
	ON_BN_CLICKED(IDC_BUTTON_Zero05, OnBUTTONZero05)
	ON_BN_CLICKED(IDC_BUTTON_Zero06, OnBUTTONZero06)
	ON_BN_CLICKED(IDC_BUTTON_Zero07, OnBUTTONZero07)
	ON_BN_CLICKED(IDC_BUTTON_Zero08, OnBUTTONZero08)
	ON_BN_CLICKED(IDC_BUTTON_Zero09, OnBUTTONZero09)
	ON_BN_CLICKED(IDC_BUTTON_Zero10, OnBUTTONZero10)
	ON_BN_CLICKED(IDC_BUTTON_Zero11, OnBUTTONZero11)
	ON_BN_CLICKED(IDC_BUTTON_Zero12, OnBUTTONZero12)
	ON_BN_CLICKED(IDC_BUTTON_Zero13, OnBUTTONZero13)
	ON_BN_CLICKED(IDC_BUTTON_Zero14, OnBUTTONZero14)
	ON_BN_CLICKED(IDC_BUTTON_Zero15, OnBUTTONZero15)
	ON_BN_CLICKED(IDC_BUTTON_Amp00, OnBUTTONAmp00)
	ON_BN_CLICKED(IDC_BUTTON_Amp01, OnBUTTONAmp01)
	ON_BN_CLICKED(IDC_BUTTON_Amp02, OnBUTTONAmp02)
	ON_BN_CLICKED(IDC_BUTTON_Amp03, OnBUTTONAmp03)
	ON_BN_CLICKED(IDC_BUTTON_Amp04, OnBUTTONAmp04)
	ON_BN_CLICKED(IDC_BUTTON_Amp05, OnBUTTONAmp05)
	ON_BN_CLICKED(IDC_BUTTON_Amp06, OnBUTTONAmp06)
	ON_BN_CLICKED(IDC_BUTTON_Amp07, OnBUTTONAmp07)
	ON_BN_CLICKED(IDC_BUTTON_Amp08, OnBUTTONAmp08)
	ON_BN_CLICKED(IDC_BUTTON_Amp09, OnBUTTONAmp09)
	ON_BN_CLICKED(IDC_BUTTON_Amp10, OnBUTTONAmp10)
	ON_BN_CLICKED(IDC_BUTTON_Amp11, OnBUTTONAmp11)
	ON_BN_CLICKED(IDC_BUTTON_Amp12, OnBUTTONAmp12)
	ON_BN_CLICKED(IDC_BUTTON_Amp13, OnBUTTONAmp13)
	ON_BN_CLICKED(IDC_BUTTON_Amp14, OnBUTTONAmp14)
	ON_BN_CLICKED(IDC_BUTTON_Amp15, OnBUTTONAmp15)
	ON_BN_CLICKED(IDC_BUTTON_CFSave, OnBUTTONCFSave)
	ON_BN_CLICKED(IDC_BUTTON_CFLoadFile, OnBUTTONCFLoadFile)
	ON_BN_CLICKED(IDC_BUTTON_Channel, OnBUTTONChannel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalibrationFactor メッセージ ハンドラ

BOOL CCalibrationFactor::OnInitDialog() 
{	DigitShowContext* ctx = GetContext();
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_DChannel = _T("Ch.00-15");
	Load();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCalibrationFactor::OnBUTTONChannel() 
{	DigitShowContext* ctx = GetContext();
	// TODO: Add your control notification handler code here
	if(m_DChannel == "Ch.00-15")	m_DChannel = _T("Ch.16-31");
	else							m_DChannel = _T("Ch.00-15");
	Load();
}

void CCalibrationFactor::Load()
{	DigitShowContext* ctx = GetContext();
	pDoc -> AD_INPUT();
	pDoc -> Cal_Physical();
	if( m_DChannel == "Ch.00-15"){ 
		m_CH00 = "CH00: "+ctx->NameP[0];		m_Amp00.SetWindowText("Amp.00");	
		m_CH01 = "CH01: "+ctx->NameP[1];		m_Amp01.SetWindowText("Amp.01");	
		m_CH02 = "CH02: "+ctx->NameP[2];		m_Amp02.SetWindowText("Amp.02");	
		m_CH03 = "CH03: "+ctx->NameP[3];		m_Amp03.SetWindowText("Amp.03");	
		m_CH04 = "CH04: "+ctx->NameP[4];		m_Amp04.SetWindowText("Amp.04");	
		m_CH05 = "CH05: "+ctx->NameP[5];		m_Amp05.SetWindowText("Amp.05");	
		m_CH06 = "CH06: "+ctx->NameP[6];		m_Amp06.SetWindowText("Amp.06");	
		m_CH07 = "CH07: "+ctx->NameP[7];		m_Amp07.SetWindowText("Amp.07");	
		m_CH08 = "CH08: "+ctx->NameP[8];		m_Amp08.SetWindowText("Amp.08");	
		m_CH09 = "CH09: "+ctx->NameP[9];		m_Amp09.SetWindowText("Amp.09");	
		m_CH10 = "CH10: "+ctx->NameP[10];	m_Amp10.SetWindowText("Amp.10");	
		m_CH11 = "CH11: "+ctx->NameP[11];	m_Amp11.SetWindowText("Amp.11");	
		m_CH12 = "CH12: "+ctx->NameP[12];	m_Amp12.SetWindowText("Amp.12");	
		m_CH13 = "CH13: "+ctx->NameP[13];	m_Amp13.SetWindowText("Amp.13");	
		m_CH14 = "CH14: "+ctx->NameP[14];	m_Amp14.SetWindowText("Amp.14");	
		m_CH15 = "CH15: "+ctx->NameP[15];	m_Amp15.SetWindowText("Amp.15");	
		m_CFA00=ctx->ai.cal.a[0];	m_CFB00=ctx->ai.cal.b[0];	m_CFC00=ctx->ai.cal.c[0];	m_CFP00.Format("%11.5f",ctx->ai.phy[0]);	
		m_CFA01=ctx->ai.cal.a[1];	m_CFB01=ctx->ai.cal.b[1];	m_CFC01=ctx->ai.cal.c[1];	m_CFP01.Format("%11.5f",ctx->ai.phy[1]);	
		m_CFA02=ctx->ai.cal.a[2];	m_CFB02=ctx->ai.cal.b[2];	m_CFC02=ctx->ai.cal.c[2];	m_CFP02.Format("%11.5f",ctx->ai.phy[2]);	
		m_CFA03=ctx->ai.cal.a[3];	m_CFB03=ctx->ai.cal.b[3];	m_CFC03=ctx->ai.cal.c[3];	m_CFP03.Format("%11.5f",ctx->ai.phy[3]);	
		m_CFA04=ctx->ai.cal.a[4];	m_CFB04=ctx->ai.cal.b[4];	m_CFC04=ctx->ai.cal.c[4];	m_CFP04.Format("%11.5f",ctx->ai.phy[4]);	
		m_CFA05=ctx->ai.cal.a[5];	m_CFB05=ctx->ai.cal.b[5];	m_CFC05=ctx->ai.cal.c[5];	m_CFP05.Format("%11.5f",ctx->ai.phy[5]);	
		m_CFA06=ctx->ai.cal.a[6];	m_CFB06=ctx->ai.cal.b[6];	m_CFC06=ctx->ai.cal.c[6];	m_CFP06.Format("%11.5f",ctx->ai.phy[6]);	
		m_CFA07=ctx->ai.cal.a[7];	m_CFB07=ctx->ai.cal.b[7];	m_CFC07=ctx->ai.cal.c[7];	m_CFP07.Format("%11.5f",ctx->ai.phy[7]);	
		m_CFA08=ctx->ai.cal.a[8];	m_CFB08=ctx->ai.cal.b[8];	m_CFC08=ctx->ai.cal.c[8];	m_CFP08.Format("%11.5f",ctx->ai.phy[8]);	
		m_CFA09=ctx->ai.cal.a[9];	m_CFB09=ctx->ai.cal.b[9];	m_CFC09=ctx->ai.cal.c[9];	m_CFP09.Format("%11.5f",ctx->ai.phy[9]);	
		m_CFA10=ctx->ai.cal.a[10];	m_CFB10=ctx->ai.cal.b[10];	m_CFC10=ctx->ai.cal.c[10];	m_CFP10.Format("%11.5f",ctx->ai.phy[10]);	
		m_CFA11=ctx->ai.cal.a[11];	m_CFB11=ctx->ai.cal.b[11];	m_CFC11=ctx->ai.cal.c[11];	m_CFP11.Format("%11.5f",ctx->ai.phy[11]);	
		m_CFA12=ctx->ai.cal.a[12];	m_CFB12=ctx->ai.cal.b[12];	m_CFC12=ctx->ai.cal.c[12];	m_CFP12.Format("%11.5f",ctx->ai.phy[12]);	
		m_CFA13=ctx->ai.cal.a[13];	m_CFB13=ctx->ai.cal.b[13];	m_CFC13=ctx->ai.cal.c[13];	m_CFP13.Format("%11.5f",ctx->ai.phy[13]);	
		m_CFA14=ctx->ai.cal.a[14];	m_CFB14=ctx->ai.cal.b[14];	m_CFC14=ctx->ai.cal.c[14];	m_CFP14.Format("%11.5f",ctx->ai.phy[14]);	
		m_CFA15=ctx->ai.cal.a[15];	m_CFB15=ctx->ai.cal.b[15];	m_CFC15=ctx->ai.cal.c[15];	m_CFP15.Format("%11.5f",ctx->ai.phy[15]);	
	}
	else{
		m_CH00 = "CH16: "+ctx->NameP[16];	m_Amp00.SetWindowText("Amp.16");	
		m_CH01 = "CH17: "+ctx->NameP[17];	m_Amp01.SetWindowText("Amp.17");	
		m_CH02 = "CH18: "+ctx->NameP[18];	m_Amp02.SetWindowText("Amp.18");	
		m_CH03 = "CH19: "+ctx->NameP[19];	m_Amp03.SetWindowText("Amp.19");	
		m_CH04 = "CH20: "+ctx->NameP[20];	m_Amp04.SetWindowText("Amp.20");	
		m_CH05 = "CH21: "+ctx->NameP[21];	m_Amp05.SetWindowText("Amp.21");	
		m_CH06 = "CH22: "+ctx->NameP[22];	m_Amp06.SetWindowText("Amp.22");	
		m_CH07 = "CH23: "+ctx->NameP[23];	m_Amp07.SetWindowText("Amp.23");	
		m_CH08 = "CH24: "+ctx->NameP[24];	m_Amp08.SetWindowText("Amp.24");	
		m_CH09 = "CH25: "+ctx->NameP[25];	m_Amp09.SetWindowText("Amp.25");	
		m_CH10 = "CH26: "+ctx->NameP[26];	m_Amp10.SetWindowText("Amp.26");	
		m_CH11 = "CH27: "+ctx->NameP[27];	m_Amp11.SetWindowText("Amp.27");	
		m_CH12 = "CH28: "+ctx->NameP[28];	m_Amp12.SetWindowText("Amp.28");	
		m_CH13 = "CH29: "+ctx->NameP[29];	m_Amp13.SetWindowText("Amp.29");	
		m_CH14 = "CH30: "+ctx->NameP[30];	m_Amp14.SetWindowText("Amp.30");	
		m_CH15 = "CH31: "+ctx->NameP[31];	m_Amp15.SetWindowText("Amp.31");	
		m_CFA00=ctx->ai.cal.a[16];	m_CFB00=ctx->ai.cal.b[16];	m_CFC00=ctx->ai.cal.c[16];	m_CFP00.Format("%11.5f",ctx->ai.phy[16]);	
		m_CFA01=ctx->ai.cal.a[17];	m_CFB01=ctx->ai.cal.b[17];	m_CFC01=ctx->ai.cal.c[17];	m_CFP01.Format("%11.5f",ctx->ai.phy[17]);	
		m_CFA02=ctx->ai.cal.a[18];	m_CFB02=ctx->ai.cal.b[18];	m_CFC02=ctx->ai.cal.c[18];	m_CFP02.Format("%11.5f",ctx->ai.phy[18]);	
		m_CFA03=ctx->ai.cal.a[19];	m_CFB03=ctx->ai.cal.b[19];	m_CFC03=ctx->ai.cal.c[19];	m_CFP03.Format("%11.5f",ctx->ai.phy[19]);	
		m_CFA04=ctx->ai.cal.a[20];	m_CFB04=ctx->ai.cal.b[20];	m_CFC04=ctx->ai.cal.c[20];	m_CFP04.Format("%11.5f",ctx->ai.phy[20]);	
		m_CFA05=ctx->ai.cal.a[21];	m_CFB05=ctx->ai.cal.b[21];	m_CFC05=ctx->ai.cal.c[21];	m_CFP05.Format("%11.5f",ctx->ai.phy[21]);	
		m_CFA06=ctx->ai.cal.a[22];	m_CFB06=ctx->ai.cal.b[22];	m_CFC06=ctx->ai.cal.c[22];	m_CFP06.Format("%11.5f",ctx->ai.phy[22]);	
		m_CFA07=ctx->ai.cal.a[23];	m_CFB07=ctx->ai.cal.b[23];	m_CFC07=ctx->ai.cal.c[23];	m_CFP07.Format("%11.5f",ctx->ai.phy[23]);	
		m_CFA08=ctx->ai.cal.a[24];	m_CFB08=ctx->ai.cal.b[24];	m_CFC08=ctx->ai.cal.c[24];	m_CFP08.Format("%11.5f",ctx->ai.phy[24]);	
		m_CFA09=ctx->ai.cal.a[25];	m_CFB09=ctx->ai.cal.b[25];	m_CFC09=ctx->ai.cal.c[25];	m_CFP09.Format("%11.5f",ctx->ai.phy[25]);	
		m_CFA10=ctx->ai.cal.a[26];	m_CFB10=ctx->ai.cal.b[26];	m_CFC10=ctx->ai.cal.c[26];	m_CFP10.Format("%11.5f",ctx->ai.phy[26]);	
		m_CFA11=ctx->ai.cal.a[27];	m_CFB11=ctx->ai.cal.b[27];	m_CFC11=ctx->ai.cal.c[27];	m_CFP11.Format("%11.5f",ctx->ai.phy[27]);	
		m_CFA12=ctx->ai.cal.a[28];	m_CFB12=ctx->ai.cal.b[28];	m_CFC12=ctx->ai.cal.c[28];	m_CFP12.Format("%11.5f",ctx->ai.phy[28]);	
		m_CFA13=ctx->ai.cal.a[29];	m_CFB13=ctx->ai.cal.b[29];	m_CFC13=ctx->ai.cal.c[29];	m_CFP13.Format("%11.5f",ctx->ai.phy[29]);	
		m_CFA14=ctx->ai.cal.a[30];	m_CFB14=ctx->ai.cal.b[30];	m_CFC14=ctx->ai.cal.c[30];	m_CFP14.Format("%11.5f",ctx->ai.phy[30]);	
		m_CFA15=ctx->ai.cal.a[31];	m_CFB15=ctx->ai.cal.b[31];	m_CFC15=ctx->ai.cal.c[31];	m_CFP15.Format("%11.5f",ctx->ai.phy[31]);	
	}
	UpdateData(FALSE);
}

void CCalibrationFactor::OnBUTTONCFUpdate() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(TRUE);
	if(m_DChannel == "Ch.00-15"){
		ctx->ai.cal.a[0]=m_CFA00;	ctx->ai.cal.b[0]=m_CFB00;	ctx->ai.cal.c[0]=m_CFC00;	
		ctx->ai.cal.a[1]=m_CFA01;	ctx->ai.cal.b[1]=m_CFB01;	ctx->ai.cal.c[1]=m_CFC01;	
		ctx->ai.cal.a[2]=m_CFA02;	ctx->ai.cal.b[2]=m_CFB02;	ctx->ai.cal.c[2]=m_CFC02;	
		ctx->ai.cal.a[3]=m_CFA03;	ctx->ai.cal.b[3]=m_CFB03;	ctx->ai.cal.c[3]=m_CFC03;	
		ctx->ai.cal.a[4]=m_CFA04;	ctx->ai.cal.b[4]=m_CFB04;	ctx->ai.cal.c[4]=m_CFC04;	
		ctx->ai.cal.a[5]=m_CFA05;	ctx->ai.cal.b[5]=m_CFB05;	ctx->ai.cal.c[5]=m_CFC05;	
		ctx->ai.cal.a[6]=m_CFA06;	ctx->ai.cal.b[6]=m_CFB06;	ctx->ai.cal.c[6]=m_CFC06;	
		ctx->ai.cal.a[7]=m_CFA07;	ctx->ai.cal.b[7]=m_CFB07;	ctx->ai.cal.c[7]=m_CFC07;	
		ctx->ai.cal.a[8]=m_CFA08;	ctx->ai.cal.b[8]=m_CFB08;	ctx->ai.cal.c[8]=m_CFC08;	
		ctx->ai.cal.a[9]=m_CFA09;	ctx->ai.cal.b[9]=m_CFB09;	ctx->ai.cal.c[9]=m_CFC09;	
		ctx->ai.cal.a[10]=m_CFA10;	ctx->ai.cal.b[10]=m_CFB10;	ctx->ai.cal.c[10]=m_CFC10;	
		ctx->ai.cal.a[11]=m_CFA11;	ctx->ai.cal.b[11]=m_CFB11;	ctx->ai.cal.c[11]=m_CFC11;	
		ctx->ai.cal.a[12]=m_CFA12;	ctx->ai.cal.b[12]=m_CFB12;	ctx->ai.cal.c[12]=m_CFC12;	
		ctx->ai.cal.a[13]=m_CFA13;	ctx->ai.cal.b[13]=m_CFB13;	ctx->ai.cal.c[13]=m_CFC13;	
		ctx->ai.cal.a[14]=m_CFA14;	ctx->ai.cal.b[14]=m_CFB14;	ctx->ai.cal.c[14]=m_CFC14;	
		ctx->ai.cal.a[15]=m_CFA15;	ctx->ai.cal.b[15]=m_CFB15;	ctx->ai.cal.c[15]=m_CFC15;	
	}
	else{
		ctx->ai.cal.a[16]=m_CFA00;	ctx->ai.cal.b[16]=m_CFB00;	ctx->ai.cal.c[16]=m_CFC00;	
		ctx->ai.cal.a[17]=m_CFA01;	ctx->ai.cal.b[17]=m_CFB01;	ctx->ai.cal.c[17]=m_CFC01;	
		ctx->ai.cal.a[18]=m_CFA02;	ctx->ai.cal.b[18]=m_CFB02;	ctx->ai.cal.c[18]=m_CFC02;	
		ctx->ai.cal.a[19]=m_CFA03;	ctx->ai.cal.b[19]=m_CFB03;	ctx->ai.cal.c[19]=m_CFC03;	
		ctx->ai.cal.a[20]=m_CFA04;	ctx->ai.cal.b[20]=m_CFB04;	ctx->ai.cal.c[20]=m_CFC04;	
		ctx->ai.cal.a[21]=m_CFA05;	ctx->ai.cal.b[21]=m_CFB05;	ctx->ai.cal.c[21]=m_CFC05;	
		ctx->ai.cal.a[22]=m_CFA06;	ctx->ai.cal.b[22]=m_CFB06;	ctx->ai.cal.c[22]=m_CFC06;	
		ctx->ai.cal.a[23]=m_CFA07;	ctx->ai.cal.b[23]=m_CFB07;	ctx->ai.cal.c[23]=m_CFC07;	
		ctx->ai.cal.a[24]=m_CFA08;	ctx->ai.cal.b[24]=m_CFB08;	ctx->ai.cal.c[24]=m_CFC08;	
		ctx->ai.cal.a[25]=m_CFA09;	ctx->ai.cal.b[25]=m_CFB09;	ctx->ai.cal.c[25]=m_CFC09;	
		ctx->ai.cal.a[26]=m_CFA10;	ctx->ai.cal.b[26]=m_CFB10;	ctx->ai.cal.c[26]=m_CFC10;	
		ctx->ai.cal.a[27]=m_CFA11;	ctx->ai.cal.b[27]=m_CFB11;	ctx->ai.cal.c[27]=m_CFC11;	
		ctx->ai.cal.a[28]=m_CFA12;	ctx->ai.cal.b[28]=m_CFB12;	ctx->ai.cal.c[28]=m_CFC12;	
		ctx->ai.cal.a[29]=m_CFA13;	ctx->ai.cal.b[29]=m_CFB13;	ctx->ai.cal.c[29]=m_CFC13;	
		ctx->ai.cal.a[30]=m_CFA14;	ctx->ai.cal.b[30]=m_CFB14;	ctx->ai.cal.c[30]=m_CFC14;	
		ctx->ai.cal.a[31]=m_CFA15;	ctx->ai.cal.b[31]=m_CFB15;	ctx->ai.cal.c[31]=m_CFC15;	
	}
}


void CCalibrationFactor::OnBUTTONZero00() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	ctx->ai.cal.c[0]=ctx->ai.cal.c[0]-ctx->ai.phy[0];
	else							ctx->ai.cal.c[16]=ctx->ai.cal.c[16]-ctx->ai.phy[16];
	Load();
}

void CCalibrationFactor::OnBUTTONZero01() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	ctx->ai.cal.c[1]=ctx->ai.cal.c[1]-ctx->ai.phy[1];
	else							ctx->ai.cal.c[17]=ctx->ai.cal.c[17]-ctx->ai.phy[17];
	Load();
}

void CCalibrationFactor::OnBUTTONZero02() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	ctx->ai.cal.c[2]=ctx->ai.cal.c[2]-ctx->ai.phy[2];
	else							ctx->ai.cal.c[18]=ctx->ai.cal.c[18]-ctx->ai.phy[18];
	Load();
}

void CCalibrationFactor::OnBUTTONZero03() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	ctx->ai.cal.c[3]=ctx->ai.cal.c[3]-ctx->ai.phy[3];
	else							ctx->ai.cal.c[19]=ctx->ai.cal.c[19]-ctx->ai.phy[19];
	Load();	
}

void CCalibrationFactor::OnBUTTONZero04() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	ctx->ai.cal.c[4]=ctx->ai.cal.c[4]-ctx->ai.phy[4];
	else							ctx->ai.cal.c[20]=ctx->ai.cal.c[20]-ctx->ai.phy[20];
	Load();	
}

void CCalibrationFactor::OnBUTTONZero05() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	ctx->ai.cal.c[5]=ctx->ai.cal.c[5]-ctx->ai.phy[5];
	else							ctx->ai.cal.c[21]=ctx->ai.cal.c[21]-ctx->ai.phy[21];
	Load();
}

void CCalibrationFactor::OnBUTTONZero06() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	ctx->ai.cal.c[6]=ctx->ai.cal.c[6]-ctx->ai.phy[6];
	else							ctx->ai.cal.c[22]=ctx->ai.cal.c[22]-ctx->ai.phy[22];
	Load();
}

void CCalibrationFactor::OnBUTTONZero07() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	ctx->ai.cal.c[7]=ctx->ai.cal.c[7]-ctx->ai.phy[7];
	else							ctx->ai.cal.c[23]=ctx->ai.cal.c[23]-ctx->ai.phy[23];
	Load();
}

void CCalibrationFactor::OnBUTTONZero08() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	ctx->ai.cal.c[8]=ctx->ai.cal.c[8]-ctx->ai.phy[8];
	else							ctx->ai.cal.c[24]=ctx->ai.cal.c[24]-ctx->ai.phy[24];
	Load();
}

void CCalibrationFactor::OnBUTTONZero09() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	ctx->ai.cal.c[9]=ctx->ai.cal.c[9]-ctx->ai.phy[9];
	else							ctx->ai.cal.c[25]=ctx->ai.cal.c[25]-ctx->ai.phy[25];
	Load();
}

void CCalibrationFactor::OnBUTTONZero10() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	ctx->ai.cal.c[10]=ctx->ai.cal.c[10]-ctx->ai.phy[10];
	else							ctx->ai.cal.c[26]=ctx->ai.cal.c[26]-ctx->ai.phy[26];
	Load();
}

void CCalibrationFactor::OnBUTTONZero11() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	ctx->ai.cal.c[11]=ctx->ai.cal.c[11]-ctx->ai.phy[11];
	else							ctx->ai.cal.c[27]=ctx->ai.cal.c[27]-ctx->ai.phy[27];
	Load();	
}

void CCalibrationFactor::OnBUTTONZero12() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	ctx->ai.cal.c[12]=ctx->ai.cal.c[12]-ctx->ai.phy[12];
	else							ctx->ai.cal.c[28]=ctx->ai.cal.c[28]-ctx->ai.phy[28];
	Load();	
}

void CCalibrationFactor::OnBUTTONZero13() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	ctx->ai.cal.c[13]=ctx->ai.cal.c[13]-ctx->ai.phy[13];
	else							ctx->ai.cal.c[29]=ctx->ai.cal.c[29]-ctx->ai.phy[29];
	Load();	
}

void CCalibrationFactor::OnBUTTONZero14() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	ctx->ai.cal.c[14]=ctx->ai.cal.c[14]-ctx->ai.phy[14];
	else							ctx->ai.cal.c[30]=ctx->ai.cal.c[30]-ctx->ai.phy[30];
	Load();	
}

void CCalibrationFactor::OnBUTTONZero15() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	ctx->ai.cal.c[15]=ctx->ai.cal.c[15]-ctx->ai.phy[15];
	else							ctx->ai.cal.c[31]=ctx->ai.cal.c[31]-ctx->ai.phy[31];
	Load();
}

void CCalibrationFactor::OnBUTTONAmp00() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	ctx->AmpID=0;
	else							ctx->AmpID=16;
	if( ctx->AmpID<=ctx->AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}
}

void CCalibrationFactor::OnBUTTONAmp01() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	ctx->AmpID=1;
	else							ctx->AmpID=17;
	if( ctx->AmpID<=ctx->AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}
}

void CCalibrationFactor::OnBUTTONAmp02() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	ctx->AmpID=2;
	else							ctx->AmpID=18;
	if( ctx->AmpID<=ctx->AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}	
}

void CCalibrationFactor::OnBUTTONAmp03() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	ctx->AmpID=3;
	else							ctx->AmpID=19;
	if( ctx->AmpID<=ctx->AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}	
}

void CCalibrationFactor::OnBUTTONAmp04() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	ctx->AmpID=4;
	else							ctx->AmpID=20;
	if( ctx->AmpID<=ctx->AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}	
}

void CCalibrationFactor::OnBUTTONAmp05() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	ctx->AmpID=5;
	else							ctx->AmpID=21;
	if( ctx->AmpID<=ctx->AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}	
}

void CCalibrationFactor::OnBUTTONAmp06() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	ctx->AmpID=6;
	else							ctx->AmpID=22;
	if( ctx->AmpID<=ctx->AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}
}

void CCalibrationFactor::OnBUTTONAmp07() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	ctx->AmpID=7;
	else							ctx->AmpID=23;
	if( ctx->AmpID<=ctx->AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}	
}

void CCalibrationFactor::OnBUTTONAmp08() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	ctx->AmpID=8;
	else							ctx->AmpID=24;
	if( ctx->AmpID<=ctx->AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}	
}

void CCalibrationFactor::OnBUTTONAmp09() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	ctx->AmpID=9;
	else							ctx->AmpID=25;
	if( ctx->AmpID<=ctx->AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}	
}

void CCalibrationFactor::OnBUTTONAmp10() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	ctx->AmpID=10;
	else							ctx->AmpID=26;
	if( ctx->AmpID<=ctx->AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}	
}

void CCalibrationFactor::OnBUTTONAmp11() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	ctx->AmpID=11;
	else							ctx->AmpID=27;
	if( ctx->AmpID<=ctx->AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}	
}

void CCalibrationFactor::OnBUTTONAmp12() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	ctx->AmpID=12;
	else							ctx->AmpID=28;
	if( ctx->AmpID<=ctx->AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}	
}

void CCalibrationFactor::OnBUTTONAmp13() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	ctx->AmpID=13;
	else							ctx->AmpID=29;
	if( ctx->AmpID<=ctx->AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}	
}

void CCalibrationFactor::OnBUTTONAmp14() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	ctx->AmpID=14;
	else							ctx->AmpID=30;
	if( ctx->AmpID<=ctx->AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}	
}

void CCalibrationFactor::OnBUTTONAmp15() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	ctx->AmpID=15;
	else							ctx->AmpID=31;
	if( ctx->AmpID<=ctx->AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}	
}


void CCalibrationFactor::OnBUTTONCFSave() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください

	CString	pFileName;
	FILE	*FileCalData;
	int		i;

	CFileDialog CalSaveFile_dlg( FALSE, NULL, "*.cal",  OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT,
		"Calibration Files(*.cal)|*.cal| All Files(*.*)|*.*| |",NULL);

	if (CalSaveFile_dlg.DoModal()==IDOK)	{
	    pFileName = CalSaveFile_dlg.GetPathName();	
		FileCalData = fopen((LPCSTR)pFileName , "w" );
		fprintf(FileCalData,"32 \n");
		for(i=0;i<32;i++){
			fprintf(FileCalData,"%d	%lf	%lf	%lf\n",i,ctx->ai.cal.a[i],ctx->ai.cal.b[i],ctx->ai.cal.c[i]);
		}
		fclose(FileCalData);
	}	
}

void CCalibrationFactor::OnBUTTONCFLoadFile() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください

	CString	pFileName;
	FILE	*FileCalData;
	int		i,l,m;

	CFileDialog CalLoadFile_dlg( TRUE, NULL, "*.cal",  OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		"Calibration Files(*.cal)|*.cal| All Files(*.*)|*.*| |",NULL);

	if (CalLoadFile_dlg.DoModal()==IDOK){
	    pFileName = CalLoadFile_dlg.GetPathName();	
		FileCalData = fopen((LPCSTR)pFileName , "r" );
		fscanf(FileCalData,"%d",&l);
		for(i=0;i<l;i++){
			fscanf(FileCalData,"%d%lf%lf%lf",&m,&ctx->ai.cal.a[i],&ctx->ai.cal.b[i],&ctx->ai.cal.c[i]);
		}
		fclose(FileCalData);
		Load();
	}	
}


