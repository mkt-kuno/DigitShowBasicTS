/*
 * DigitShowBasicTS - Hollow Torsional Shear Triaxial Test Control Software
 * Copyright (C) 2026 Makoto KUNO
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
// Control_File.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "DigitShowBasic.h"
#include "Control_File.h"
#include "DigitShowContext.h"
#include "DigitShowBasicDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CControl_File ダイアログ

CControl_File::CControl_File(CWnd* pParent /*=NULL*/)
	: CDialog(CControl_File::IDD, pParent)
{
	DigitShowContext* ctx = GetContext();
	//{{AFX_DATA_INIT(CControl_File)
	m_CFNUM = ctx->controlFile.Num[ctx->controlFile.CurrentNum];
	m_CURNUM = ctx->controlFile.CurrentNum;
	m_CFPARA0 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][0];
	m_CFPARA1 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][1];
	m_CFPARA2 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][2];
	m_CFPARA3 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][3];
	m_CFPARA4 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][4];
	m_CFPARA5 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][5];
	m_CFPARA6 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][6];
	m_CFPARA7 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][7];
	m_CFPARA8 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][8];
	m_CFPARA9 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][9];
	m_CFPARA10 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][10];
	m_CFPARA11 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][11];
	m_CFPARA12 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][12];
	m_CFPARA13 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][13];
	m_CFPARA14 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][14];
	m_CFPARA15 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][15];
	m_CtrlNo = ctx->controlFile.Num[ctx->controlFile.CurrentNum];
	m_StepNo = ctx->controlFile.CurrentNum;
	//}}AFX_DATA_INIT
}


void CControl_File::DoDataExchange(CDataExchange* pDX)
{	DigitShowContext* ctx = GetContext();
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
{	DigitShowContext* ctx = GetContext();
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
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	ctx->controlFile.CurrentNum=0;
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
			fscanf(FileCtlData,"%d",&ctx->controlFile.Num[i]);
			for(j=0;j<16;j++){
				fscanf(FileCtlData,"%lf",&ctx->controlFile.Para[i][j]);
			}
		}
		fclose(FileCtlData);
		ctx->controlFile.CurrentNum = 0;
		ctx->StepTime = 0.0;
		ctx->NumCyclic = 0;
	}
#pragma warning(pop)
	m_CURNUM = ctx->controlFile.CurrentNum;
	m_CFNUM=ctx->controlFile.Num[ctx->controlFile.CurrentNum];
	m_StepNo = ctx->controlFile.CurrentNum;
	m_CtrlNo = ctx->controlFile.Num[ctx->controlFile.CurrentNum];
	m_CFPARA0 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][0];
	m_CFPARA1 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][1];
	m_CFPARA2 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][2];
	m_CFPARA3 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][3];
	m_CFPARA4 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][4];
	m_CFPARA5 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][5];
	m_CFPARA6 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][6];
	m_CFPARA7 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][7];
	m_CFPARA8 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][8];
	m_CFPARA9 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][9];
	m_CFPARA10 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][10];
	m_CFPARA11 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][11];
	m_CFPARA12 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][12];
	m_CFPARA13 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][13];
	m_CFPARA14 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][14];
	m_CFPARA15 = ctx->controlFile.Para[ctx->controlFile.CurrentNum][15];
	UpdateData(FALSE);
}

void CControl_File::OnBUTTONSaveFile() 
{	DigitShowContext* ctx = GetContext();
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
				fprintf(FileCtlData,"%d	",ctx->controlFile.Num[i]);
				for(j=0;j<16;j++){
					fprintf(FileCtlData,"%lf	",ctx->controlFile.Para[i][j]);
				}
				fprintf(FileCtlData,"\n");
			}
			fclose(FileCtlData);
		}
	}		
}

void CControl_File::OnBUTTONLoad() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(TRUE);
	m_CtrlNo = ctx->controlFile.Num[m_StepNo];
	m_CFPARA0 = ctx->controlFile.Para[m_StepNo][0];
	m_CFPARA1 = ctx->controlFile.Para[m_StepNo][1];
	m_CFPARA2 = ctx->controlFile.Para[m_StepNo][2];
	m_CFPARA3 = ctx->controlFile.Para[m_StepNo][3];
	m_CFPARA4 = ctx->controlFile.Para[m_StepNo][4];
	m_CFPARA5 = ctx->controlFile.Para[m_StepNo][5];
	m_CFPARA6 = ctx->controlFile.Para[m_StepNo][6];
	m_CFPARA7 = ctx->controlFile.Para[m_StepNo][7];
	m_CFPARA8 = ctx->controlFile.Para[m_StepNo][8];
	m_CFPARA9 = ctx->controlFile.Para[m_StepNo][9];
	m_CFPARA10 = ctx->controlFile.Para[m_StepNo][10];
	m_CFPARA11 = ctx->controlFile.Para[m_StepNo][11];
	m_CFPARA12 = ctx->controlFile.Para[m_StepNo][12];
	m_CFPARA13 = ctx->controlFile.Para[m_StepNo][13];
	m_CFPARA14 = ctx->controlFile.Para[m_StepNo][14];
	m_CFPARA15 = ctx->controlFile.Para[m_StepNo][15];
	UpdateData(FALSE);
}

void CControl_File::OnBUTTONUpdate() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(TRUE);
	ctx->controlFile.Num[m_StepNo] = m_CtrlNo;
	ctx->controlFile.Para[m_StepNo][0] = m_CFPARA0;
	ctx->controlFile.Para[m_StepNo][1] = m_CFPARA1;
	ctx->controlFile.Para[m_StepNo][2] = m_CFPARA2;
	ctx->controlFile.Para[m_StepNo][3] = m_CFPARA3;
	ctx->controlFile.Para[m_StepNo][4] = m_CFPARA4;
	ctx->controlFile.Para[m_StepNo][5] = m_CFPARA5;
	ctx->controlFile.Para[m_StepNo][6] = m_CFPARA6;
	ctx->controlFile.Para[m_StepNo][7] = m_CFPARA7;
	ctx->controlFile.Para[m_StepNo][8] = m_CFPARA8;
	ctx->controlFile.Para[m_StepNo][9] = m_CFPARA9;
	ctx->controlFile.Para[m_StepNo][10] = m_CFPARA10;
	ctx->controlFile.Para[m_StepNo][11] = m_CFPARA11;
	ctx->controlFile.Para[m_StepNo][12] = m_CFPARA12;
	ctx->controlFile.Para[m_StepNo][13] = m_CFPARA13;
	ctx->controlFile.Para[m_StepNo][14] = m_CFPARA14;
	ctx->controlFile.Para[m_StepNo][15] = m_CFPARA15;
	UpdateData(FALSE);
}

void CControl_File::OnCHECKChangeNo() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_StepDec);
	CButton* myBTN2=(CButton*)GetDlgItem(IDC_BUTTON_StepInc);
	CButton* chkbox1=(CButton*)GetDlgItem(IDC_CHECK_ChangeNo);
	if(chkbox1->GetCheck()){
		if(ctx->controlFile.CurrentNum > 0)		myBTN1->EnableWindow(TRUE);
		if(ctx->controlFile.CurrentNum < 255)	myBTN2->EnableWindow(TRUE);
	}
	else{
		myBTN1->EnableWindow(FALSE);
		myBTN2->EnableWindow(FALSE);
	}
}

void CControl_File::OnBUTTONStepDec() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	ctx->controlFile.CurrentNum=ctx->controlFile.CurrentNum-1;
	ctx->NumCyclic=0;
	ctx->StepTime=0.0;
	m_CURNUM = ctx->controlFile.CurrentNum;
	m_CFNUM = ctx->controlFile.Num[ctx->controlFile.CurrentNum];
	CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_StepDec);
	CButton* myBTN2=(CButton*)GetDlgItem(IDC_BUTTON_StepInc);
	if(ctx->controlFile.CurrentNum > 0)		myBTN1->EnableWindow(TRUE);
	else				myBTN1->EnableWindow(FALSE);
	if(ctx->controlFile.CurrentNum < 255)	myBTN2->EnableWindow(TRUE);
	else				myBTN2->EnableWindow(FALSE);
	UpdateData(FALSE);
}

void CControl_File::OnBUTTONStepInc() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	ctx->controlFile.CurrentNum=ctx->controlFile.CurrentNum+1;
	ctx->NumCyclic=0;
	ctx->StepTime=0.0;
	m_CURNUM = ctx->controlFile.CurrentNum;
	m_CFNUM = ctx->controlFile.Num[ctx->controlFile.CurrentNum];
	CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_StepDec);
	CButton* myBTN2=(CButton*)GetDlgItem(IDC_BUTTON_StepInc);
	if(ctx->controlFile.CurrentNum > 0)		myBTN1->EnableWindow(TRUE);
	else				myBTN1->EnableWindow(FALSE);
	if(ctx->controlFile.CurrentNum < 255)	myBTN2->EnableWindow(TRUE);
	else				myBTN2->EnableWindow(FALSE);
	UpdateData(FALSE);
}
