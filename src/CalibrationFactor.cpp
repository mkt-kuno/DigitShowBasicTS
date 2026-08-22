// CalibrationFactor.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "DigitShowBasic.h"
#include "CalibrationFactor.h"

#include "CalibrationAmp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalibrationFactor ダイアログ
// CDigitShowBasicView
extern	CString		NameP[32];
extern	float		Vout[32];	
extern	double		Phyout[32];				
extern	double		Cal_a[32],Cal_b[32],Cal_c[32];				
extern	int			AdMaxCH;
		int			AmpID;

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
{
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
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_DChannel = _T("Ch.00-15");
	Load();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCalibrationFactor::OnBUTTONChannel() 
{
	// TODO: Add your control notification handler code here
	if(m_DChannel == "Ch.00-15")	m_DChannel = _T("Ch.16-31");
	else							m_DChannel = _T("Ch.00-15");
	Load();
}

void CCalibrationFactor::Load()
{
	pDoc -> AD_INPUT();
	pDoc -> Cal_Physical();
	if( m_DChannel == "Ch.00-15"){ 
		m_CH00 = "CH00: "+NameP[0];		m_Amp00.SetWindowText("Amp.00");	
		m_CH01 = "CH01: "+NameP[1];		m_Amp01.SetWindowText("Amp.01");	
		m_CH02 = "CH02: "+NameP[2];		m_Amp02.SetWindowText("Amp.02");	
		m_CH03 = "CH03: "+NameP[3];		m_Amp03.SetWindowText("Amp.03");	
		m_CH04 = "CH04: "+NameP[4];		m_Amp04.SetWindowText("Amp.04");	
		m_CH05 = "CH05: "+NameP[5];		m_Amp05.SetWindowText("Amp.05");	
		m_CH06 = "CH06: "+NameP[6];		m_Amp06.SetWindowText("Amp.06");	
		m_CH07 = "CH07: "+NameP[7];		m_Amp07.SetWindowText("Amp.07");	
		m_CH08 = "CH08: "+NameP[8];		m_Amp08.SetWindowText("Amp.08");	
		m_CH09 = "CH09: "+NameP[9];		m_Amp09.SetWindowText("Amp.09");	
		m_CH10 = "CH10: "+NameP[10];	m_Amp10.SetWindowText("Amp.10");	
		m_CH11 = "CH11: "+NameP[11];	m_Amp11.SetWindowText("Amp.11");	
		m_CH12 = "CH12: "+NameP[12];	m_Amp12.SetWindowText("Amp.12");	
		m_CH13 = "CH13: "+NameP[13];	m_Amp13.SetWindowText("Amp.13");	
		m_CH14 = "CH14: "+NameP[14];	m_Amp14.SetWindowText("Amp.14");	
		m_CH15 = "CH15: "+NameP[15];	m_Amp15.SetWindowText("Amp.15");	
		m_CFA00=Cal_a[0];	m_CFB00=Cal_b[0];	m_CFC00=Cal_c[0];	m_CFP00.Format("%11.5f",Phyout[0]);	
		m_CFA01=Cal_a[1];	m_CFB01=Cal_b[1];	m_CFC01=Cal_c[1];	m_CFP01.Format("%11.5f",Phyout[1]);	
		m_CFA02=Cal_a[2];	m_CFB02=Cal_b[2];	m_CFC02=Cal_c[2];	m_CFP02.Format("%11.5f",Phyout[2]);	
		m_CFA03=Cal_a[3];	m_CFB03=Cal_b[3];	m_CFC03=Cal_c[3];	m_CFP03.Format("%11.5f",Phyout[3]);	
		m_CFA04=Cal_a[4];	m_CFB04=Cal_b[4];	m_CFC04=Cal_c[4];	m_CFP04.Format("%11.5f",Phyout[4]);	
		m_CFA05=Cal_a[5];	m_CFB05=Cal_b[5];	m_CFC05=Cal_c[5];	m_CFP05.Format("%11.5f",Phyout[5]);	
		m_CFA06=Cal_a[6];	m_CFB06=Cal_b[6];	m_CFC06=Cal_c[6];	m_CFP06.Format("%11.5f",Phyout[6]);	
		m_CFA07=Cal_a[7];	m_CFB07=Cal_b[7];	m_CFC07=Cal_c[7];	m_CFP07.Format("%11.5f",Phyout[7]);	
		m_CFA08=Cal_a[8];	m_CFB08=Cal_b[8];	m_CFC08=Cal_c[8];	m_CFP08.Format("%11.5f",Phyout[8]);	
		m_CFA09=Cal_a[9];	m_CFB09=Cal_b[9];	m_CFC09=Cal_c[9];	m_CFP09.Format("%11.5f",Phyout[9]);	
		m_CFA10=Cal_a[10];	m_CFB10=Cal_b[10];	m_CFC10=Cal_c[10];	m_CFP10.Format("%11.5f",Phyout[10]);	
		m_CFA11=Cal_a[11];	m_CFB11=Cal_b[11];	m_CFC11=Cal_c[11];	m_CFP11.Format("%11.5f",Phyout[11]);	
		m_CFA12=Cal_a[12];	m_CFB12=Cal_b[12];	m_CFC12=Cal_c[12];	m_CFP12.Format("%11.5f",Phyout[12]);	
		m_CFA13=Cal_a[13];	m_CFB13=Cal_b[13];	m_CFC13=Cal_c[13];	m_CFP13.Format("%11.5f",Phyout[13]);	
		m_CFA14=Cal_a[14];	m_CFB14=Cal_b[14];	m_CFC14=Cal_c[14];	m_CFP14.Format("%11.5f",Phyout[14]);	
		m_CFA15=Cal_a[15];	m_CFB15=Cal_b[15];	m_CFC15=Cal_c[15];	m_CFP15.Format("%11.5f",Phyout[15]);	
	}
	else{
		m_CH00 = "CH16: "+NameP[16];	m_Amp00.SetWindowText("Amp.16");	
		m_CH01 = "CH17: "+NameP[17];	m_Amp01.SetWindowText("Amp.17");	
		m_CH02 = "CH18: "+NameP[18];	m_Amp02.SetWindowText("Amp.18");	
		m_CH03 = "CH19: "+NameP[19];	m_Amp03.SetWindowText("Amp.19");	
		m_CH04 = "CH20: "+NameP[20];	m_Amp04.SetWindowText("Amp.20");	
		m_CH05 = "CH21: "+NameP[21];	m_Amp05.SetWindowText("Amp.21");	
		m_CH06 = "CH22: "+NameP[22];	m_Amp06.SetWindowText("Amp.22");	
		m_CH07 = "CH23: "+NameP[23];	m_Amp07.SetWindowText("Amp.23");	
		m_CH08 = "CH24: "+NameP[24];	m_Amp08.SetWindowText("Amp.24");	
		m_CH09 = "CH25: "+NameP[25];	m_Amp09.SetWindowText("Amp.25");	
		m_CH10 = "CH26: "+NameP[26];	m_Amp10.SetWindowText("Amp.26");	
		m_CH11 = "CH27: "+NameP[27];	m_Amp11.SetWindowText("Amp.27");	
		m_CH12 = "CH28: "+NameP[28];	m_Amp12.SetWindowText("Amp.28");	
		m_CH13 = "CH29: "+NameP[29];	m_Amp13.SetWindowText("Amp.29");	
		m_CH14 = "CH30: "+NameP[30];	m_Amp14.SetWindowText("Amp.30");	
		m_CH15 = "CH31: "+NameP[31];	m_Amp15.SetWindowText("Amp.31");	
		m_CFA00=Cal_a[16];	m_CFB00=Cal_b[16];	m_CFC00=Cal_c[16];	m_CFP00.Format("%11.5f",Phyout[16]);	
		m_CFA01=Cal_a[17];	m_CFB01=Cal_b[17];	m_CFC01=Cal_c[17];	m_CFP01.Format("%11.5f",Phyout[17]);	
		m_CFA02=Cal_a[18];	m_CFB02=Cal_b[18];	m_CFC02=Cal_c[18];	m_CFP02.Format("%11.5f",Phyout[18]);	
		m_CFA03=Cal_a[19];	m_CFB03=Cal_b[19];	m_CFC03=Cal_c[19];	m_CFP03.Format("%11.5f",Phyout[19]);	
		m_CFA04=Cal_a[20];	m_CFB04=Cal_b[20];	m_CFC04=Cal_c[20];	m_CFP04.Format("%11.5f",Phyout[20]);	
		m_CFA05=Cal_a[21];	m_CFB05=Cal_b[21];	m_CFC05=Cal_c[21];	m_CFP05.Format("%11.5f",Phyout[21]);	
		m_CFA06=Cal_a[22];	m_CFB06=Cal_b[22];	m_CFC06=Cal_c[22];	m_CFP06.Format("%11.5f",Phyout[22]);	
		m_CFA07=Cal_a[23];	m_CFB07=Cal_b[23];	m_CFC07=Cal_c[23];	m_CFP07.Format("%11.5f",Phyout[23]);	
		m_CFA08=Cal_a[24];	m_CFB08=Cal_b[24];	m_CFC08=Cal_c[24];	m_CFP08.Format("%11.5f",Phyout[24]);	
		m_CFA09=Cal_a[25];	m_CFB09=Cal_b[25];	m_CFC09=Cal_c[25];	m_CFP09.Format("%11.5f",Phyout[25]);	
		m_CFA10=Cal_a[26];	m_CFB10=Cal_b[26];	m_CFC10=Cal_c[26];	m_CFP10.Format("%11.5f",Phyout[26]);	
		m_CFA11=Cal_a[27];	m_CFB11=Cal_b[27];	m_CFC11=Cal_c[27];	m_CFP11.Format("%11.5f",Phyout[27]);	
		m_CFA12=Cal_a[28];	m_CFB12=Cal_b[28];	m_CFC12=Cal_c[28];	m_CFP12.Format("%11.5f",Phyout[28]);	
		m_CFA13=Cal_a[29];	m_CFB13=Cal_b[29];	m_CFC13=Cal_c[29];	m_CFP13.Format("%11.5f",Phyout[29]);	
		m_CFA14=Cal_a[30];	m_CFB14=Cal_b[30];	m_CFC14=Cal_c[30];	m_CFP14.Format("%11.5f",Phyout[30]);	
		m_CFA15=Cal_a[31];	m_CFB15=Cal_b[31];	m_CFC15=Cal_c[31];	m_CFP15.Format("%11.5f",Phyout[31]);	
	}
	UpdateData(FALSE);
}

void CCalibrationFactor::OnBUTTONCFUpdate() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(TRUE);
	if(m_DChannel == "Ch.00-15"){
		Cal_a[0]=m_CFA00;	Cal_b[0]=m_CFB00;	Cal_c[0]=m_CFC00;	
		Cal_a[1]=m_CFA01;	Cal_b[1]=m_CFB01;	Cal_c[1]=m_CFC01;	
		Cal_a[2]=m_CFA02;	Cal_b[2]=m_CFB02;	Cal_c[2]=m_CFC02;	
		Cal_a[3]=m_CFA03;	Cal_b[3]=m_CFB03;	Cal_c[3]=m_CFC03;	
		Cal_a[4]=m_CFA04;	Cal_b[4]=m_CFB04;	Cal_c[4]=m_CFC04;	
		Cal_a[5]=m_CFA05;	Cal_b[5]=m_CFB05;	Cal_c[5]=m_CFC05;	
		Cal_a[6]=m_CFA06;	Cal_b[6]=m_CFB06;	Cal_c[6]=m_CFC06;	
		Cal_a[7]=m_CFA07;	Cal_b[7]=m_CFB07;	Cal_c[7]=m_CFC07;	
		Cal_a[8]=m_CFA08;	Cal_b[8]=m_CFB08;	Cal_c[8]=m_CFC08;	
		Cal_a[9]=m_CFA09;	Cal_b[9]=m_CFB09;	Cal_c[9]=m_CFC09;	
		Cal_a[10]=m_CFA10;	Cal_b[10]=m_CFB10;	Cal_c[10]=m_CFC10;	
		Cal_a[11]=m_CFA11;	Cal_b[11]=m_CFB11;	Cal_c[11]=m_CFC11;	
		Cal_a[12]=m_CFA12;	Cal_b[12]=m_CFB12;	Cal_c[12]=m_CFC12;	
		Cal_a[13]=m_CFA13;	Cal_b[13]=m_CFB13;	Cal_c[13]=m_CFC13;	
		Cal_a[14]=m_CFA14;	Cal_b[14]=m_CFB14;	Cal_c[14]=m_CFC14;	
		Cal_a[15]=m_CFA15;	Cal_b[15]=m_CFB15;	Cal_c[15]=m_CFC15;	
	}
	else{
		Cal_a[16]=m_CFA00;	Cal_b[16]=m_CFB00;	Cal_c[16]=m_CFC00;	
		Cal_a[17]=m_CFA01;	Cal_b[17]=m_CFB01;	Cal_c[17]=m_CFC01;	
		Cal_a[18]=m_CFA02;	Cal_b[18]=m_CFB02;	Cal_c[18]=m_CFC02;	
		Cal_a[19]=m_CFA03;	Cal_b[19]=m_CFB03;	Cal_c[19]=m_CFC03;	
		Cal_a[20]=m_CFA04;	Cal_b[20]=m_CFB04;	Cal_c[20]=m_CFC04;	
		Cal_a[21]=m_CFA05;	Cal_b[21]=m_CFB05;	Cal_c[21]=m_CFC05;	
		Cal_a[22]=m_CFA06;	Cal_b[22]=m_CFB06;	Cal_c[22]=m_CFC06;	
		Cal_a[23]=m_CFA07;	Cal_b[23]=m_CFB07;	Cal_c[23]=m_CFC07;	
		Cal_a[24]=m_CFA08;	Cal_b[24]=m_CFB08;	Cal_c[24]=m_CFC08;	
		Cal_a[25]=m_CFA09;	Cal_b[25]=m_CFB09;	Cal_c[25]=m_CFC09;	
		Cal_a[26]=m_CFA10;	Cal_b[26]=m_CFB10;	Cal_c[26]=m_CFC10;	
		Cal_a[27]=m_CFA11;	Cal_b[27]=m_CFB11;	Cal_c[27]=m_CFC11;	
		Cal_a[28]=m_CFA12;	Cal_b[28]=m_CFB12;	Cal_c[28]=m_CFC12;	
		Cal_a[29]=m_CFA13;	Cal_b[29]=m_CFB13;	Cal_c[29]=m_CFC13;	
		Cal_a[30]=m_CFA14;	Cal_b[30]=m_CFB14;	Cal_c[30]=m_CFC14;	
		Cal_a[31]=m_CFA15;	Cal_b[31]=m_CFB15;	Cal_c[31]=m_CFC15;	
	}
}


void CCalibrationFactor::OnBUTTONZero00() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	Cal_c[0]=Cal_c[0]-Phyout[0];
	else							Cal_c[16]=Cal_c[16]-Phyout[16];
	Load();
}

void CCalibrationFactor::OnBUTTONZero01() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	Cal_c[1]=Cal_c[1]-Phyout[1];
	else							Cal_c[17]=Cal_c[17]-Phyout[17];
	Load();
}

void CCalibrationFactor::OnBUTTONZero02() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	Cal_c[2]=Cal_c[2]-Phyout[2];
	else							Cal_c[18]=Cal_c[18]-Phyout[18];
	Load();
}

void CCalibrationFactor::OnBUTTONZero03() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	Cal_c[3]=Cal_c[3]-Phyout[3];
	else							Cal_c[19]=Cal_c[19]-Phyout[19];
	Load();	
}

void CCalibrationFactor::OnBUTTONZero04() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	Cal_c[4]=Cal_c[4]-Phyout[4];
	else							Cal_c[20]=Cal_c[20]-Phyout[20];
	Load();	
}

void CCalibrationFactor::OnBUTTONZero05() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	Cal_c[5]=Cal_c[5]-Phyout[5];
	else							Cal_c[21]=Cal_c[21]-Phyout[21];
	Load();
}

void CCalibrationFactor::OnBUTTONZero06() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	Cal_c[6]=Cal_c[6]-Phyout[6];
	else							Cal_c[22]=Cal_c[22]-Phyout[22];
	Load();
}

void CCalibrationFactor::OnBUTTONZero07() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	Cal_c[7]=Cal_c[7]-Phyout[7];
	else							Cal_c[23]=Cal_c[23]-Phyout[23];
	Load();
}

void CCalibrationFactor::OnBUTTONZero08() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	Cal_c[8]=Cal_c[8]-Phyout[8];
	else							Cal_c[24]=Cal_c[24]-Phyout[24];
	Load();
}

void CCalibrationFactor::OnBUTTONZero09() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	Cal_c[9]=Cal_c[9]-Phyout[9];
	else							Cal_c[25]=Cal_c[25]-Phyout[25];
	Load();
}

void CCalibrationFactor::OnBUTTONZero10() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	Cal_c[10]=Cal_c[10]-Phyout[10];
	else							Cal_c[26]=Cal_c[26]-Phyout[26];
	Load();
}

void CCalibrationFactor::OnBUTTONZero11() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	Cal_c[11]=Cal_c[11]-Phyout[11];
	else							Cal_c[27]=Cal_c[27]-Phyout[27];
	Load();	
}

void CCalibrationFactor::OnBUTTONZero12() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	Cal_c[12]=Cal_c[12]-Phyout[12];
	else							Cal_c[28]=Cal_c[28]-Phyout[28];
	Load();	
}

void CCalibrationFactor::OnBUTTONZero13() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	Cal_c[13]=Cal_c[13]-Phyout[13];
	else							Cal_c[29]=Cal_c[29]-Phyout[29];
	Load();	
}

void CCalibrationFactor::OnBUTTONZero14() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	Cal_c[14]=Cal_c[14]-Phyout[14];
	else							Cal_c[30]=Cal_c[30]-Phyout[30];
	Load();	
}

void CCalibrationFactor::OnBUTTONZero15() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONCFUpdate();
	if(m_DChannel == "Ch.00-15")	Cal_c[15]=Cal_c[15]-Phyout[15];
	else							Cal_c[31]=Cal_c[31]-Phyout[31];
	Load();
}

void CCalibrationFactor::OnBUTTONAmp00() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	AmpID=0;
	else							AmpID=16;
	if( AmpID<=AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}
}

void CCalibrationFactor::OnBUTTONAmp01() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	AmpID=1;
	else							AmpID=17;
	if( AmpID<=AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}
}

void CCalibrationFactor::OnBUTTONAmp02() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	AmpID=2;
	else							AmpID=18;
	if( AmpID<=AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}	
}

void CCalibrationFactor::OnBUTTONAmp03() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	AmpID=3;
	else							AmpID=19;
	if( AmpID<=AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}	
}

void CCalibrationFactor::OnBUTTONAmp04() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	AmpID=4;
	else							AmpID=20;
	if( AmpID<=AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}	
}

void CCalibrationFactor::OnBUTTONAmp05() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	AmpID=5;
	else							AmpID=21;
	if( AmpID<=AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}	
}

void CCalibrationFactor::OnBUTTONAmp06() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	AmpID=6;
	else							AmpID=22;
	if( AmpID<=AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}
}

void CCalibrationFactor::OnBUTTONAmp07() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	AmpID=7;
	else							AmpID=23;
	if( AmpID<=AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}	
}

void CCalibrationFactor::OnBUTTONAmp08() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	AmpID=8;
	else							AmpID=24;
	if( AmpID<=AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}	
}

void CCalibrationFactor::OnBUTTONAmp09() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	AmpID=9;
	else							AmpID=25;
	if( AmpID<=AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}	
}

void CCalibrationFactor::OnBUTTONAmp10() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	AmpID=10;
	else							AmpID=26;
	if( AmpID<=AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}	
}

void CCalibrationFactor::OnBUTTONAmp11() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	AmpID=11;
	else							AmpID=27;
	if( AmpID<=AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}	
}

void CCalibrationFactor::OnBUTTONAmp12() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	AmpID=12;
	else							AmpID=28;
	if( AmpID<=AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}	
}

void CCalibrationFactor::OnBUTTONAmp13() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	AmpID=13;
	else							AmpID=29;
	if( AmpID<=AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}	
}

void CCalibrationFactor::OnBUTTONAmp14() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	AmpID=14;
	else							AmpID=30;
	if( AmpID<=AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}	
}

void CCalibrationFactor::OnBUTTONAmp15() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int		nResult;

	if(m_DChannel == "Ch.00-15")	AmpID=15;
	else							AmpID=31;
	if( AmpID<=AdMaxCH ){
		CCalibrationAmp CalibrationAmp;
		nResult = CalibrationAmp.DoModal();
		if(nResult==IDOK)	Load();
	}	
}


void CCalibrationFactor::OnBUTTONCFSave() 
{
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
			fprintf(FileCalData,"%d	%lf	%lf	%lf\n",i,Cal_a[i],Cal_b[i],Cal_c[i]);
		}
		fclose(FileCalData);
	}	
}

void CCalibrationFactor::OnBUTTONCFLoadFile() 
{
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
			fscanf(FileCalData,"%d%lf%lf%lf",&m,&Cal_a[i],&Cal_b[i],&Cal_c[i]);
		}
		fclose(FileCalData);
		Load();
	}	
}


