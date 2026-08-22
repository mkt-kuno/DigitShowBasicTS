// BoardSettings.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "DigitShowBasic.h"
#include "BoardSettings.h"
#include "DigitShowContext.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBoardSettings ダイアログ
//---boards---


CBoardSettings::CBoardSettings(CWnd* pParent /*=NULL*/)
	: CDialog(CBoardSettings::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBoardSettings)
	m_AdMaxChannel1 = _T("");
	m_AdMaxChannel2 = _T("");
	m_AdMethod1 = _T("");
	m_AdMethod2 = _T("");
	m_AdRange1 = _T("");
	m_AdRange2 = _T("");
	m_AdResolution1 = _T("");
	m_AdResolution2 = _T("");
	m_DaMaxChannel = _T("");
	m_DaRange = _T("");
	m_DaResolution = _T("");
	//}}AFX_DATA_INIT
}


void CBoardSettings::DoDataExchange(CDataExchange* pDX)
{	DigitShowContext* ctx = GetContext();
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBoardSettings)
	DDX_Text(pDX, IDC_EDIT_AdMaxChannel1, m_AdMaxChannel1);
	DDX_Text(pDX, IDC_EDIT_AdMaxChannel2, m_AdMaxChannel2);
	DDX_Text(pDX, IDC_EDIT_AdMethod1, m_AdMethod1);
	DDX_Text(pDX, IDC_EDIT_AdMethod2, m_AdMethod2);
	DDX_Text(pDX, IDC_EDIT_AdRange1, m_AdRange1);
	DDX_Text(pDX, IDC_EDIT_AdRange2, m_AdRange2);
	DDX_Text(pDX, IDC_EDIT_AdResolution1, m_AdResolution1);
	DDX_Text(pDX, IDC_EDIT_AdResolution2, m_AdResolution2);
	DDX_Text(pDX, IDC_EDIT_DaMaxChannel, m_DaMaxChannel);
	DDX_Text(pDX, IDC_EDIT_DaRange, m_DaRange);
	DDX_Text(pDX, IDC_EDIT_DaResolution, m_DaResolution);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBoardSettings, CDialog)
	//{{AFX_MSG_MAP(CBoardSettings)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBoardSettings メッセージ ハンドラ

BOOL CBoardSettings::OnInitDialog() 
{	DigitShowContext* ctx = GetContext();
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	if(ctx->NumAD >0 && ctx->ad[0].InputMethod==0) m_AdMethod1="Single Input";
	if(ctx->NumAD >0 && ctx->ad[0].InputMethod==1) m_AdMethod1="Differential Input";
	if(ctx->NumAD >0 && ctx->ad[0].Resolution==12) m_AdResolution1="12 bit";
	if(ctx->NumAD >0 && ctx->ad[0].Resolution==16) m_AdResolution1="16 bit";
	if(ctx->NumAD >0 && ctx->ad[0].Range==0)  m_AdRange1="-10V   +10V";
	if(ctx->NumAD >0 && ctx->ad[0].Range==1)  m_AdRange1="-5V   +5V";
	if(ctx->NumAD >0 && ctx->ad[0].Range==50) m_AdRange1="0V   +10V";
	if(ctx->NumAD >0 && ctx->ad[0].Range==51) m_AdRange1="0V   +5V";
	if(ctx->NumAD >0) m_AdMaxChannel1.Format("%3d",ctx->ad[0].Channels);
	if(ctx->NumAD >1 && ctx->ad[1].InputMethod==0) m_AdMethod2="Single Input";
	if(ctx->NumAD >1 && ctx->ad[1].InputMethod==1) m_AdMethod2="Differential Input";
	if(ctx->NumAD >1 && ctx->ad[1].Resolution==12) m_AdResolution2="12 bit";
	if(ctx->NumAD >1 && ctx->ad[1].Resolution==16) m_AdResolution2="16 bit";
	if(ctx->NumAD >1 && ctx->ad[1].Range==0)  m_AdRange2="-10V   +10V";
	if(ctx->NumAD >1 && ctx->ad[1].Range==1)  m_AdRange2="-5V   +5V";
	if(ctx->NumAD >1 && ctx->ad[1].Range==50) m_AdRange2="0V   +10V";
	if(ctx->NumAD >1 && ctx->ad[1].Range==51) m_AdRange2="0V   +5V";
	if(ctx->NumAD >1) m_AdMaxChannel2.Format("%3d",ctx->ad[1].Channels);
	
	if(ctx->NumDA >0 && ctx->da[0].Resolution==12) m_DaResolution="12 bit";
	if(ctx->NumDA >0 && ctx->da[0].Resolution==16) m_DaResolution="16 bit";
	if(ctx->NumDA >0 && ctx->da[0].Range==0)  m_DaRange="-10V   +10V";
	if(ctx->NumDA >0 && ctx->da[0].Range==1)  m_DaRange="-5V   +5V";
	if(ctx->NumDA >0 && ctx->da[0].Range==50) m_DaRange="0V   +10V";
	if(ctx->NumDA >0 && ctx->da[0].Range==51) m_DaRange="0V   +5V";
	if(ctx->NumDA >0) m_DaMaxChannel.Format("%3d",ctx->da[0].Channels);
	UpdateData(FALSE);	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}
