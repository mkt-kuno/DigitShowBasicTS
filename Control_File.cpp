// Control_File.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "DigitShowBasic.h"
#include "Control_File.h"
#include "DigitShowBasicDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CControl_File ダイアログ
extern	int			CURNUM;
extern	int			CFNUM[256];
extern	double		CFPARA[256][16];
extern	int			Num_Cyclic;
extern	double		StepTime;

CControl_File::CControl_File(CWnd* pParent /*=NULL*/)
	: CDialog(CControl_File::IDD, pParent)
{
	//{{AFX_DATA_INIT(CControl_File)
	m_CFNUM = CFNUM[CURNUM];
	m_CURNUM = CURNUM;
	m_CFPARA0 = CFPARA[CURNUM][0];
	m_CFPARA1 = CFPARA[CURNUM][1];
	m_CFPARA2 = CFPARA[CURNUM][2];
	m_CFPARA3 = CFPARA[CURNUM][3];
	m_CFPARA4 = CFPARA[CURNUM][4];
	m_CFPARA5 = CFPARA[CURNUM][5];
	m_CFPARA6 = CFPARA[CURNUM][6];
	m_CFPARA7 = CFPARA[CURNUM][7];
	m_CFPARA8 = CFPARA[CURNUM][8];
	m_CFPARA9 = CFPARA[CURNUM][9];
	m_CFPARA10 = CFPARA[CURNUM][10];
	m_CFPARA11 = CFPARA[CURNUM][11];
	m_CFPARA12 = CFPARA[CURNUM][12];
	m_CFPARA13 = CFPARA[CURNUM][13];
	m_CFPARA14 = CFPARA[CURNUM][14];
	m_CFPARA15 = CFPARA[CURNUM][15];
	m_CtrlNo = CFNUM[CURNUM];
	m_StepNo = CURNUM;
	//}}AFX_DATA_INIT
}


void CControl_File::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CControl_File)
	DDX_Text(pDX, IDC_EDIT_CFNUM, m_CFNUM);
	DDX_Text(pDX, IDC_EDIT_CURNUM, m_CURNUM);
	DDX_Text(pDX, IDC_EDIT_CFPARA0, m_CFPARA0);
	DDX_Text(pDX, IDC_EDIT_CFPARA1, m_CFPARA1);
	DDX_Text(pDX, IDC_EDIT_CFPARA2, m_CFPARA2);
	DDX_Text(pDX, IDC_EDIT_CFPARA3, m_CFPARA3);
	DDX_Text(pDX, IDC_EDIT_CFPARA4, m_CFPARA4);
	DDX_Text(pDX, IDC_EDIT_CFPARA5, m_CFPARA5);
	DDX_Text(pDX, IDC_EDIT_CFPARA6, m_CFPARA6);
	DDX_Text(pDX, IDC_EDIT_CFPARA7, m_CFPARA7);
	DDX_Text(pDX, IDC_EDIT_CFPARA8, m_CFPARA8);
	DDX_Text(pDX, IDC_EDIT_CFPARA9, m_CFPARA9);
	DDX_Text(pDX, IDC_EDIT_CtrlNo, m_CtrlNo);
	DDX_Text(pDX, IDC_EDIT_StepNo, m_StepNo);
	DDX_Text(pDX, IDC_EDIT_CFPARA10, m_CFPARA10);
	DDX_Text(pDX, IDC_EDIT_CFPARA11, m_CFPARA11);
	DDX_Text(pDX, IDC_EDIT_CFPARA12, m_CFPARA12);
	DDX_Text(pDX, IDC_EDIT_CFPARA13, m_CFPARA13);
	DDX_Text(pDX, IDC_EDIT_CFPARA14, m_CFPARA14);
	DDX_Text(pDX, IDC_EDIT_CFPARA15, m_CFPARA15);
	DDV_MinMaxInt(pDX, m_StepNo, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CControl_File, CDialog)
	//{{AFX_MSG_MAP(CControl_File)
	//ON_BN_CLICKED(IDC_LoadFile, OnLoadFile)
	ON_BN_CLICKED(IDC_BUTTON_Load, OnBUTTONLoad)
	ON_BN_CLICKED(IDC_BUTTON_Update, OnBUTTONUpdate)
	ON_BN_CLICKED(IDC_BUTTON_ReadFile, OnBUTTONReadFile)
	ON_BN_CLICKED(IDC_BUTTON_SaveFile, OnBUTTONSaveFile)
	ON_BN_CLICKED(IDC_CHECK_ChangeNo, OnCHECKChangeNo)
	ON_BN_CLICKED(IDC_BUTTON_StepDec, OnBUTTONStepDec)
	ON_BN_CLICKED(IDC_BUTTON_StepInc, OnBUTTONStepInc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CControl_File メッセージ ハンドラ

/////////////////////////////////////////////////////////////////////////////
// CControl_File メッセージ ハンドラ
BOOL CControl_File::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_StepDec);
	CButton* myBTN2=(CButton*)GetDlgItem(IDC_BUTTON_StepInc);
	myBTN1->EnableWindow(FALSE);
	myBTN2->EnableWindow(FALSE);
	CButton* chkbox1=(CButton*)GetDlgItem(IDC_CHECK_ChangeNo);
	chkbox1->SetCheck(0);
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CControl_File::OnBUTTONReadFile() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CURNUM=0;
	CString	pFileName;
	FILE	*FileCtlData;
	int		i,j;

	CFileDialog CtlLoadFile_dlg( TRUE, NULL, "*.ctl",  OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		"Control Files(*.ctl)|*.ctl| All Files(*.*)|*.*| |",NULL);

#pragma warning(push)
#pragma warning(disable:4996)
	if (CtlLoadFile_dlg.DoModal()==IDOK)	{
	    pFileName = CtlLoadFile_dlg.GetPathName();	
		FileCtlData = fopen((LPCSTR)pFileName , "r" );
		for(i=0;i<256;i++){
			fscanf(FileCtlData,"%d",&CFNUM[i]);
			for(j=0;j<16;j++){
				fscanf(FileCtlData,"%lf",&CFPARA[i][j]);
			}
		}
		fclose(FileCtlData);
		CURNUM = 0;
		StepTime = 0.0;
		Num_Cyclic = 0;
	}
#pragma warning(pop)
	m_CURNUM = CURNUM;
	m_CFNUM=CFNUM[CURNUM];
	m_StepNo = CURNUM;
	m_CtrlNo = CFNUM[CURNUM];
	m_CFPARA0 = CFPARA[CURNUM][0];
	m_CFPARA1 = CFPARA[CURNUM][1];
	m_CFPARA2 = CFPARA[CURNUM][2];
	m_CFPARA3 = CFPARA[CURNUM][3];
	m_CFPARA4 = CFPARA[CURNUM][4];
	m_CFPARA5 = CFPARA[CURNUM][5];
	m_CFPARA6 = CFPARA[CURNUM][6];
	m_CFPARA7 = CFPARA[CURNUM][7];
	m_CFPARA8 = CFPARA[CURNUM][8];
	m_CFPARA9 = CFPARA[CURNUM][9];
	m_CFPARA10 = CFPARA[CURNUM][10];
	m_CFPARA11 = CFPARA[CURNUM][11];
	m_CFPARA12 = CFPARA[CURNUM][12];
	m_CFPARA13 = CFPARA[CURNUM][13];
	m_CFPARA14 = CFPARA[CURNUM][14];
	m_CFPARA15 = CFPARA[CURNUM][15];
	UpdateData(FALSE);
}

void CControl_File::OnBUTTONSaveFile() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString	pFileName;
	FILE	*FileCtlData;
	errno_t err;
	int		i,j;

	CFileDialog CtlSaveFile_dlg( FALSE, NULL, "*.ctl",  OFN_OVERWRITEPROMPT,
		"Control Files(*.ctl)|*.ctl| All Files(*.*)|*.*| |",NULL);

	if (CtlSaveFile_dlg.DoModal()==IDOK)
	{
	    pFileName = CtlSaveFile_dlg.GetPathName();	
	//	FileCtlData = fopen((LPCSTR)pFileName , "w" );
		if((err = fopen_s(&FileCtlData,(LPCSTR)pFileName , _T("w"))) == 0)
		{
			for(i=0;i<256;i++){
				fprintf(FileCtlData,"%d	",CFNUM[i]);
				for(j=0;j<16;j++){
					fprintf(FileCtlData,"%lf	",CFPARA[i][j]);
				}
				fprintf(FileCtlData,"\n");
			}
			fclose(FileCtlData);
		}
	}		
}

void CControl_File::OnBUTTONLoad() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(TRUE);
	m_CtrlNo = CFNUM[m_StepNo];
	m_CFPARA0 = CFPARA[m_StepNo][0];
	m_CFPARA1 = CFPARA[m_StepNo][1];
	m_CFPARA2 = CFPARA[m_StepNo][2];
	m_CFPARA3 = CFPARA[m_StepNo][3];
	m_CFPARA4 = CFPARA[m_StepNo][4];
	m_CFPARA5 = CFPARA[m_StepNo][5];
	m_CFPARA6 = CFPARA[m_StepNo][6];
	m_CFPARA7 = CFPARA[m_StepNo][7];
	m_CFPARA8 = CFPARA[m_StepNo][8];
	m_CFPARA9 = CFPARA[m_StepNo][9];
	m_CFPARA10 = CFPARA[m_StepNo][10];
	m_CFPARA11 = CFPARA[m_StepNo][11];
	m_CFPARA12 = CFPARA[m_StepNo][12];
	m_CFPARA13 = CFPARA[m_StepNo][13];
	m_CFPARA14 = CFPARA[m_StepNo][14];
	m_CFPARA15 = CFPARA[m_StepNo][15];
	UpdateData(FALSE);
}

void CControl_File::OnBUTTONUpdate() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(TRUE);
	CFNUM[m_StepNo] = m_CtrlNo;
	CFPARA[m_StepNo][0] = m_CFPARA0;
	CFPARA[m_StepNo][1] = m_CFPARA1;
	CFPARA[m_StepNo][2] = m_CFPARA2;
	CFPARA[m_StepNo][3] = m_CFPARA3;
	CFPARA[m_StepNo][4] = m_CFPARA4;
	CFPARA[m_StepNo][5] = m_CFPARA5;
	CFPARA[m_StepNo][6] = m_CFPARA6;
	CFPARA[m_StepNo][7] = m_CFPARA7;
	CFPARA[m_StepNo][8] = m_CFPARA8;
	CFPARA[m_StepNo][9] = m_CFPARA9;
	CFPARA[m_StepNo][10] = m_CFPARA10;
	CFPARA[m_StepNo][11] = m_CFPARA11;
	CFPARA[m_StepNo][12] = m_CFPARA12;
	CFPARA[m_StepNo][13] = m_CFPARA13;
	CFPARA[m_StepNo][14] = m_CFPARA14;
	CFPARA[m_StepNo][15] = m_CFPARA15;
	UpdateData(FALSE);
}

void CControl_File::OnCHECKChangeNo() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_StepDec);
	CButton* myBTN2=(CButton*)GetDlgItem(IDC_BUTTON_StepInc);
	CButton* chkbox1=(CButton*)GetDlgItem(IDC_CHECK_ChangeNo);
	if(chkbox1->GetCheck()){
		if(CURNUM > 0)		myBTN1->EnableWindow(TRUE);
		if(CURNUM < 255)	myBTN2->EnableWindow(TRUE);
	}
	else{
		myBTN1->EnableWindow(FALSE);
		myBTN2->EnableWindow(FALSE);
	}
}

void CControl_File::OnBUTTONStepDec() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CURNUM=CURNUM-1;
	Num_Cyclic=0;
	StepTime=0.0;
	m_CURNUM = CURNUM;
	m_CFNUM = CFNUM[CURNUM];
	CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_StepDec);
	CButton* myBTN2=(CButton*)GetDlgItem(IDC_BUTTON_StepInc);
	if(CURNUM > 0)		myBTN1->EnableWindow(TRUE);
	else				myBTN1->EnableWindow(FALSE);
	if(CURNUM < 255)	myBTN2->EnableWindow(TRUE);
	else				myBTN2->EnableWindow(FALSE);
	UpdateData(FALSE);
}

void CControl_File::OnBUTTONStepInc() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CURNUM=CURNUM+1;
	Num_Cyclic=0;
	StepTime=0.0;
	m_CURNUM = CURNUM;
	m_CFNUM = CFNUM[CURNUM];
	CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_StepDec);
	CButton* myBTN2=(CButton*)GetDlgItem(IDC_BUTTON_StepInc);
	if(CURNUM > 0)		myBTN1->EnableWindow(TRUE);
	else				myBTN1->EnableWindow(FALSE);
	if(CURNUM < 255)	myBTN2->EnableWindow(TRUE);
	else				myBTN2->EnableWindow(FALSE);
	UpdateData(FALSE);
}
