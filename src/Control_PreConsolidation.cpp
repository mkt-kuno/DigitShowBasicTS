// Control_PreConsolidation.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "DigitShowBasic.h"
#include "Control_PreConsolidation.h"
#include "DigitShowBasicDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CControl_PreConsolidation ダイアログ
extern	Control		ControlData[16];


CControl_PreConsolidation::CControl_PreConsolidation(CWnd* pParent /*=NULL*/)
	: CDialog(CControl_PreConsolidation::IDD, pParent)
{
	//{{AFX_DATA_INIT(CControl_PreConsolidation)
	m_CellPreRate = ControlData[1].sigmaRate[1];
	m_CellPreTarget = ControlData[1].sigma[1];
	m_AxisMotorSpeed = ControlData[1].AxisSpeed;
	m_q = ControlData[1].q[0];
	//}}AFX_DATA_INIT
}


void CControl_PreConsolidation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CControl_PreConsolidation)
	DDX_Text(pDX, IDC_EDIT_CellPreRate, m_CellPreRate);
	DDX_Text(pDX, IDC_EDIT_CellPreTarget, m_CellPreTarget);
	DDX_Text(pDX, IDC_EDIT_AxialMotorSpeed, m_AxisMotorSpeed);
	DDX_Text(pDX, IDC_EDIT_q, m_q);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CControl_PreConsolidation, CDialog)
	//{{AFX_MSG_MAP(CControl_PreConsolidation)
	ON_BN_CLICKED(IDC_BUTTON_Update, OnBUTTONUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CControl_PreConsolidation メッセージ ハンドラ

void CControl_PreConsolidation::OnBUTTONUpdate() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(TRUE);
	ControlData[1].AxisSpeed = m_AxisMotorSpeed;
	ControlData[1].q[0] = m_q;
	ControlData[1].sigmaRate[1] = m_CellPreRate;
	ControlData[1].sigma[1] = m_CellPreTarget;
}
