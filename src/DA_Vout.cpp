// DA_Vout.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "DigitShowBasic.h"
#include "DA_Vout.h"
#include "DigitShowContext.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDA_Vout ダイアログ

CDA_Vout::CDA_Vout(CWnd* pParent /*=NULL*/)
	: CDialog(CDA_Vout::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDA_Vout)
	m_DAVout01 = 0.0;
	m_DAVout02 = 0.0;
	m_DAVout03 = 0.0;
	m_DAVout04 = 0.0;
	m_DAVout05 = 0.0;
	m_DAVout06 = 0.0;
	m_DAVout07 = 0.0;
	m_DAVout08 = 0.0;
	m_CH01 = _T("");
	m_CH02 = _T("");
	m_CH03 = _T("");
	m_CH04 = _T("");
	m_CH05 = _T("");
	m_CH06 = _T("");
	m_CH07 = _T("");
	m_CH08 = _T("");
	//}}AFX_DATA_INIT
}


void CDA_Vout::DoDataExchange(CDataExchange* pDX)
{	DigitShowContext* ctx = GetContext();
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDA_Vout)
	DDX_Text(pDX, IDC_EDIT_DAVout01, m_DAVout01);
	DDX_Text(pDX, IDC_EDIT_DAVout02, m_DAVout02);
	DDX_Text(pDX, IDC_EDIT_DAVout03, m_DAVout03);
	DDX_Text(pDX, IDC_EDIT_DAVout04, m_DAVout04);
	DDX_Text(pDX, IDC_EDIT_DAVout05, m_DAVout05);
	DDX_Text(pDX, IDC_EDIT_DAVout06, m_DAVout06);
	DDX_Text(pDX, IDC_EDIT_DAVout07, m_DAVout07);
	DDX_Text(pDX, IDC_EDIT_DAVout08, m_DAVout08);
	DDX_Text(pDX, IDC_STATIC_CH01, m_CH01);
	DDX_Text(pDX, IDC_STATIC_CH02, m_CH02);
	DDX_Text(pDX, IDC_STATIC_CH03, m_CH03);
	DDX_Text(pDX, IDC_STATIC_CH04, m_CH04);
	DDX_Text(pDX, IDC_STATIC_CH05, m_CH05);
	DDX_Text(pDX, IDC_STATIC_CH06, m_CH06);
	DDX_Text(pDX, IDC_STATIC_CH07, m_CH07);
	DDX_Text(pDX, IDC_STATIC_CH08, m_CH08);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDA_Vout, CDialog)
	//{{AFX_MSG_MAP(CDA_Vout)
	ON_BN_CLICKED(IDC_BUTTON_DA_Vout, OnBUTTONDAVout)
	ON_BN_CLICKED(IDC_BUTTON_Reflesh, OnBUTTONReflesh)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDA_Vout メッセージ ハンドラ
BOOL CDA_Vout::OnInitDialog() 
{	DigitShowContext* ctx = GetContext();
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_DAVout01 = ctx->ao.raw[0];
	m_DAVout02 = ctx->ao.raw[1];
	m_DAVout03 = ctx->ao.raw[2];
	m_DAVout04 = ctx->ao.raw[3];
	m_DAVout05 = ctx->ao.raw[4];
	m_DAVout06 = ctx->ao.raw[5];
	m_DAVout07 = ctx->ao.raw[6];
	m_DAVout08 = ctx->ao.raw[7];
	m_CH01 = ctx->NameDV[0];
	m_CH02 = ctx->NameDV[1];
	m_CH03 = ctx->NameDV[2];
	m_CH04 = ctx->NameDV[3];
	m_CH05 = ctx->NameDV[4];
	m_CH06 = ctx->NameDV[5];
	m_CH07 = ctx->NameDV[6];
	m_CH08 = ctx->NameDV[7];
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDA_Vout::OnBUTTONDAVout() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(TRUE);
	ctx->ao.raw[0]=m_DAVout01;
	ctx->ao.raw[1]=m_DAVout02;
	ctx->ao.raw[2]=m_DAVout03;
	ctx->ao.raw[3]=m_DAVout04;
	ctx->ao.raw[4]=m_DAVout05;
	ctx->ao.raw[5]=m_DAVout06;
	ctx->ao.raw[6]=m_DAVout07;
	ctx->ao.raw[7]=m_DAVout08;
	pDoc->DA_OUTPUT();
}

void CDA_Vout::OnBUTTONReflesh() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_DAVout01 = ctx->ao.raw[0];
	m_DAVout02 = ctx->ao.raw[1];
	m_DAVout03 = ctx->ao.raw[2];
	m_DAVout04 = ctx->ao.raw[3];
	m_DAVout05 = ctx->ao.raw[4];
	m_DAVout06 = ctx->ao.raw[5];
	m_DAVout07 = ctx->ao.raw[6];
	m_DAVout08 = ctx->ao.raw[7];
	UpdateData(FALSE);
}

