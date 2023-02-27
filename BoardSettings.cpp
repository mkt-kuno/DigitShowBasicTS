// BoardSettings.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "DigitShowBasic.h"
#include "BoardSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBoardSettings ダイアログ
//---boards---
extern	int			NUMAD,NUMDA;
extern	short		AdChannels[2],DaChannels[1];		// The Number of Channel
extern	short		AdRange[2],DaRange[1];				// Range of A/D and D/A boards
extern	short		AdResolution[2],DaResolution[1];	// Resolution of A/D and D/A Boards
extern	short		AdInputMethod[2];					// Input Method of A/D


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
{
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
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	if(NUMAD >0 && AdInputMethod[0]==0) m_AdMethod1="Single Input";
	if(NUMAD >0 && AdInputMethod[0]==1) m_AdMethod1="Differential Input";
	if(NUMAD >0 && AdResolution[0]==12) m_AdResolution1="12 bit";
	if(NUMAD >0 && AdResolution[0]==16) m_AdResolution1="16 bit";
	if(NUMAD >0 && AdRange[0]==0)  m_AdRange1="-10V   +10V";
	if(NUMAD >0 && AdRange[0]==1)  m_AdRange1="-5V   +5V";
	if(NUMAD >0 && AdRange[0]==50) m_AdRange1="0V   +10V";
	if(NUMAD >0 && AdRange[0]==51) m_AdRange1="0V   +5V";
	if(NUMAD >0) m_AdMaxChannel1.Format("%3d",AdChannels[0]);
	if(NUMAD >1 && AdInputMethod[1]==0) m_AdMethod2="Single Input";
	if(NUMAD >1 && AdInputMethod[1]==1) m_AdMethod2="Differential Input";
	if(NUMAD >1 && AdResolution[1]==12) m_AdResolution2="12 bit";
	if(NUMAD >1 && AdResolution[1]==16) m_AdResolution2="16 bit";
	if(NUMAD >1 && AdRange[1]==0)  m_AdRange2="-10V   +10V";
	if(NUMAD >1 && AdRange[1]==1)  m_AdRange2="-5V   +5V";
	if(NUMAD >1 && AdRange[1]==50) m_AdRange2="0V   +10V";
	if(NUMAD >1 && AdRange[1]==51) m_AdRange2="0V   +5V";
	if(NUMAD >1) m_AdMaxChannel2.Format("%3d",AdChannels[1]);
	
	if(NUMDA >0 && DaResolution[0]==12) m_DaResolution="12 bit";
	if(NUMDA >0 && DaResolution[0]==16) m_DaResolution="16 bit";
	if(NUMDA >0 && DaRange[0]==0)  m_DaRange="-10V   +10V";
	if(NUMDA >0 && DaRange[0]==1)  m_DaRange="-5V   +5V";
	if(NUMDA >0 && DaRange[0]==50) m_DaRange="0V   +10V";
	if(NUMDA >0 && DaRange[0]==51) m_DaRange="0V   +5V";
	if(NUMDA >0) m_DaMaxChannel.Format("%3d",DaChannels[0]);
	UpdateData(FALSE);	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}
