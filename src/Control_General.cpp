// Control_General.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "DigitShowBasic.h"
#include "Control_General.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CControl_General ダイアログ
extern	double	ErrorStressMotor,ErrorStressAir;
extern	double	ErrorStrainEz,ErrorStrainGzq;

CControl_General::CControl_General(CWnd* pParent /*=NULL*/)
	: CDialog(CControl_General::IDD, pParent)
{
	//{{AFX_DATA_INIT(CControl_General)
	m_ErrorStressAir = ErrorStressAir;
	m_ErrorStressMotor = ErrorStressMotor;
	m_ErrorStrainEz = ErrorStrainEz;
	m_ErrorStrainGzq = ErrorStrainGzq;
	//}}AFX_DATA_INIT
}


void CControl_General::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CControl_General)
	DDX_Text(pDX, IDC_EDIT_ErrorStressAir, m_ErrorStressAir);
	DDX_Text(pDX, IDC_EDIT_ErrorStressMotor, m_ErrorStressMotor);
	DDX_Text(pDX, IDC_EDIT_ErrorStrainEz, m_ErrorStrainEz);
	DDX_Text(pDX, IDC_EDIT_ErrorStrainGzq, m_ErrorStrainGzq);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CControl_General, CDialog)
	//{{AFX_MSG_MAP(CControl_General)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CControl_General メッセージ ハンドラ

void CControl_General::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	UpdateData(TRUE);
	ErrorStressAir = m_ErrorStressAir;
	ErrorStressMotor = m_ErrorStressMotor;
	ErrorStrainEz = m_ErrorStrainEz;
	ErrorStrainGzq = m_ErrorStrainGzq;
	CDialog::OnOK();
}

