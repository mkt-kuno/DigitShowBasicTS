// DA_Channel.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "DigitShowBasic.h"
#include "DA_Channel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDA_Channel ダイアログ
extern	double		DA_Cal_a[16],DA_Cal_b[16];		// D/A Calibration Factor
extern	CString		NameDV[8];
CDA_Channel::CDA_Channel(CWnd* pParent /*=NULL*/)
	: CDialog(CDA_Channel::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDA_Channel)
	m_DACala1 = 0.0;
	m_DACala2 = 0.0;
	m_DACala3 = 0.0;
	m_DACala4 = 0.0;
	m_DACala5 = 0.0;
	m_DACala6 = 0.0;
	m_DACala7 = 0.0;
	m_DACala8 = 0.0;
	m_DACalb1 = 0.0;
	m_DACalb2 = 0.0;
	m_DACalb3 = 0.0;
	m_DACalb4 = 0.0;
	m_DACalb5 = 0.0;
	m_DACalb6 = 0.0;
	m_DACalb7 = 0.0;
	m_DACalb8 = 0.0;
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


void CDA_Channel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDA_Channel)
	DDX_Text(pDX, IDC_EDIT_DACala1, m_DACala1);
	DDX_Text(pDX, IDC_EDIT_DACala2, m_DACala2);
	DDX_Text(pDX, IDC_EDIT_DACala3, m_DACala3);
	DDX_Text(pDX, IDC_EDIT_DACala4, m_DACala4);
	DDX_Text(pDX, IDC_EDIT_DACala5, m_DACala5);
	DDX_Text(pDX, IDC_EDIT_DACala6, m_DACala6);
	DDX_Text(pDX, IDC_EDIT_DACala7, m_DACala7);
	DDX_Text(pDX, IDC_EDIT_DACala8, m_DACala8);
	DDX_Text(pDX, IDC_EDIT_DACalb1, m_DACalb1);
	DDX_Text(pDX, IDC_EDIT_DACalb2, m_DACalb2);
	DDX_Text(pDX, IDC_EDIT_DACalb3, m_DACalb3);
	DDX_Text(pDX, IDC_EDIT_DACalb4, m_DACalb4);
	DDX_Text(pDX, IDC_EDIT_DACalb5, m_DACalb5);
	DDX_Text(pDX, IDC_EDIT_DACalb6, m_DACalb6);
	DDX_Text(pDX, IDC_EDIT_DACalb7, m_DACalb7);
	DDX_Text(pDX, IDC_EDIT_DACalb8, m_DACalb8);
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


BEGIN_MESSAGE_MAP(CDA_Channel, CDialog)
	//{{AFX_MSG_MAP(CDA_Channel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDA_Channel メッセージ ハンドラ
BOOL CDA_Channel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_DACala1 = DA_Cal_a[0];
	m_DACala2 = DA_Cal_a[1];
	m_DACala3 = DA_Cal_a[2];
	m_DACala4 = DA_Cal_a[3];
	m_DACala5 = DA_Cal_a[4];
	m_DACala6 = DA_Cal_a[5];
	m_DACala7 = DA_Cal_a[6];
	m_DACala8 = DA_Cal_a[7];
	m_DACalb1 = DA_Cal_b[0];
	m_DACalb2 = DA_Cal_b[1];
	m_DACalb3 = DA_Cal_b[2];
	m_DACalb4 = DA_Cal_b[3];
	m_DACalb5 = DA_Cal_b[4];
	m_DACalb6 = DA_Cal_b[5];
	m_DACalb7 = DA_Cal_b[6];
	m_DACalb8 = DA_Cal_b[7];
	m_CH01 = NameDV[0];
	m_CH02 = NameDV[1];
	m_CH03 = NameDV[2];
	m_CH04 = NameDV[3];
	m_CH05 = NameDV[4];
	m_CH06 = NameDV[5];
	m_CH07 = NameDV[6];
	m_CH08 = NameDV[7];	
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDA_Channel::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	UpdateData(TRUE);
	DA_Cal_a[0] = m_DACala1;
	DA_Cal_a[1] = m_DACala2;
	DA_Cal_a[2] = m_DACala3;
	DA_Cal_a[3] = m_DACala4;
	DA_Cal_a[4] = m_DACala5;
	DA_Cal_a[5] = m_DACala6;
	DA_Cal_a[6] = m_DACala7;
	DA_Cal_a[7] = m_DACala8;
	DA_Cal_b[0] = m_DACalb1;
	DA_Cal_b[1] = m_DACalb2;
	DA_Cal_b[2] = m_DACalb3;
	DA_Cal_b[3] = m_DACalb4;
	DA_Cal_b[4] = m_DACalb5;
	DA_Cal_b[5] = m_DACalb6;
	DA_Cal_b[6] = m_DACalb7;
	DA_Cal_b[7] = m_DACalb8;
	CDialog::OnOK();
}

