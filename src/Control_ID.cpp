// Control_ID.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "DigitShowBasic.h"
#include "Control_ID.h"
#include "DigitShowContext.h"
#include "DigitShowBasicDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CControl_ID ダイアログ
		int			tmp;

CControl_ID::CControl_ID(CWnd* pParent /*=NULL*/)
	: CDialog(CControl_ID::IDD, pParent)
{
	DigitShowContext* ctx = GetContext();
	//{{AFX_DATA_INIT(CControl_ID)
	m_Control_ID = 0;
	m_flag0 = ctx->control[0].flag[0];
	m_flag1 = ctx->control[0].flag[1];
	m_flag2 = ctx->control[0].flag[2];
	m_K0 = ctx->control[0].K0;
	m_p0 = ctx->control[0].p[0];
	m_p1 = ctx->control[0].p[1];
	m_p2 = ctx->control[0].p[2];
	m_q0 = ctx->control[0].q[0];
	m_q1 = ctx->control[0].q[1];
	m_q2 = ctx->control[0].q[2];
	m_sigma0 = ctx->control[0].sigma[0];
	m_sigma1 = ctx->control[0].sigma[1];
	m_sigma2 = ctx->control[0].sigma[2];
	m_sigmaAmp0 = ctx->control[0].sigmaAmp[0];
	m_sigmaAmp1 = ctx->control[0].sigmaAmp[1];
	m_sigmaAmp2 = ctx->control[0].sigmaAmp[2];
	m_sigmaRate0 = ctx->control[0].sigmaRate[0];
	m_sigmaRate1 = ctx->control[0].sigmaRate[1];
	m_sigmaRate2 = ctx->control[0].sigmaRate[2];
	m_strain0 = ctx->control[0].strain[0];
	m_strain1 = ctx->control[0].strain[1];
	m_strain2 = ctx->control[0].strain[2];
	m_strainAmp0 = ctx->control[0].strainAmp[0];
	m_strainAmp1 = ctx->control[0].strainAmp[1];
	m_strainAmp2 = ctx->control[0].strainAmp[2];
	m_strainRate0 = ctx->control[0].strainRate[0];
	m_strainRate1 = ctx->control[0].strainRate[1];
	m_strainRate2 = ctx->control[0].strainRate[2];
	m_time0 = ctx->control[0].time[0];
	m_time1 = ctx->control[0].time[1];
	m_time2 = ctx->control[0].time[2];
	m_u0 = ctx->control[0].u[0];
	m_u1 = ctx->control[0].u[1];
	m_u2 = ctx->control[0].u[2];
	//}}AFX_DATA_INIT
}


void CControl_ID::DoDataExchange(CDataExchange* pDX)
{	DigitShowContext* ctx = GetContext();
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CControl_ID)
	DDX_Text(pDX, IDC_EDIT_Contrl_ID, m_Control_ID);
	DDV_MinMaxInt(pDX, m_Control_ID, 0, 15);
	DDX_Text(pDX, IDC_EDIT_flag0, m_flag0);
	DDX_Text(pDX, IDC_EDIT_flag1, m_flag1);
	DDX_Text(pDX, IDC_EDIT_flag2, m_flag2);
	DDX_Text(pDX, IDC_EDIT_K0, m_K0);
	DDX_Text(pDX, IDC_EDIT_p0, m_p0);
	DDX_Text(pDX, IDC_EDIT_p1, m_p1);
	DDX_Text(pDX, IDC_EDIT_p2, m_p2);
	DDX_Text(pDX, IDC_EDIT_q0, m_q0);
	DDX_Text(pDX, IDC_EDIT_q1, m_q1);
	DDX_Text(pDX, IDC_EDIT_q2, m_q2);
	DDX_Text(pDX, IDC_EDIT_sigma0, m_sigma0);
	DDX_Text(pDX, IDC_EDIT_sigma1, m_sigma1);
	DDX_Text(pDX, IDC_EDIT_sigma2, m_sigma2);
	DDX_Text(pDX, IDC_EDIT_sigmaAmp0, m_sigmaAmp0);
	DDX_Text(pDX, IDC_EDIT_sigmaAmp1, m_sigmaAmp1);
	DDX_Text(pDX, IDC_EDIT_sigmaAmp2, m_sigmaAmp2);
	DDX_Text(pDX, IDC_EDIT_sigmaRate0, m_sigmaRate0);
	DDX_Text(pDX, IDC_EDIT_sigmaRate1, m_sigmaRate1);
	DDX_Text(pDX, IDC_EDIT_sigmaRate2, m_sigmaRate2);
	DDX_Text(pDX, IDC_EDIT_strain0, m_strain0);
	DDX_Text(pDX, IDC_EDIT_strain1, m_strain1);
	DDX_Text(pDX, IDC_EDIT_strain2, m_strain2);
	DDX_Text(pDX, IDC_EDIT_strainAmp0, m_strainAmp0);
	DDX_Text(pDX, IDC_EDIT_strainAmp1, m_strainAmp1);
	DDX_Text(pDX, IDC_EDIT_strainAmp2, m_strainAmp2);
	DDX_Text(pDX, IDC_EDIT_strainRate0, m_strainRate0);
	DDX_Text(pDX, IDC_EDIT_strainRate1, m_strainRate1);
	DDX_Text(pDX, IDC_EDIT_strainRate2, m_strainRate2);
	DDX_Text(pDX, IDC_EDIT_time0, m_time0);
	DDX_Text(pDX, IDC_EDIT_time1, m_time1);
	DDX_Text(pDX, IDC_EDIT_time2, m_time2);
	DDX_Text(pDX, IDC_EDIT_u0, m_u0);
	DDX_Text(pDX, IDC_EDIT_u1, m_u1);
	DDX_Text(pDX, IDC_EDIT_u2, m_u2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CControl_ID, CDialog)
	//{{AFX_MSG_MAP(CControl_ID)
	ON_BN_CLICKED(IDC_BUTTON_Load, OnBUTTONLoad)
	ON_BN_CLICKED(IDC_BUTTON_Update, OnBUTTONUpdate)
	ON_BN_CLICKED(IDC_BUTTON_Loadfromfile, OnBUTTONLoadfromfile)
	ON_BN_CLICKED(IDC_BUTTON_SaveFile, OnBUTTONSaveFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CControl_ID メッセージ ハンドラ

void CControl_ID::OnBUTTONLoad() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください

	UpdateData(TRUE);
	tmp=m_Control_ID;
	m_flag0 = ctx->control[tmp].flag[0];
	m_flag1 = ctx->control[tmp].flag[1];
	m_flag2 = ctx->control[tmp].flag[2];
	m_K0 = ctx->control[tmp].K0;
	m_p0 = ctx->control[tmp].p[0];
	m_p1 = ctx->control[tmp].p[1];
	m_p2 = ctx->control[tmp].p[2];
	m_q0 = ctx->control[tmp].q[0];
	m_q1 = ctx->control[tmp].q[1];
	m_q2 = ctx->control[tmp].q[2];
	m_sigma0 = ctx->control[tmp].sigma[0];
	m_sigma1 = ctx->control[tmp].sigma[1];
	m_sigma2 = ctx->control[tmp].sigma[2];
	m_sigmaAmp0 = ctx->control[tmp].sigmaAmp[0];
	m_sigmaAmp1 = ctx->control[tmp].sigmaAmp[1];
	m_sigmaAmp2 = ctx->control[tmp].sigmaAmp[2];
	m_sigmaRate0 = ctx->control[tmp].sigmaRate[0];
	m_sigmaRate1 = ctx->control[tmp].sigmaRate[1];
	m_sigmaRate2 = ctx->control[tmp].sigmaRate[2];
	m_strain0 = ctx->control[tmp].strain[0];
	m_strain1 = ctx->control[tmp].strain[1];
	m_strain2 = ctx->control[tmp].strain[2];
	m_strainAmp0 = ctx->control[tmp].strainAmp[0];
	m_strainAmp1 = ctx->control[tmp].strainAmp[1];
	m_strainAmp2 = ctx->control[tmp].strainAmp[2];
	m_strainRate0 = ctx->control[tmp].strainRate[0];
	m_strainRate1 = ctx->control[tmp].strainRate[1];
	m_strainRate2 = ctx->control[tmp].strainRate[2];
	m_time0 = ctx->control[tmp].time[0];
	m_time1 = ctx->control[tmp].time[1];
	m_time2 = ctx->control[tmp].time[2];
	m_u0 = ctx->control[tmp].u[0];
	m_u1 = ctx->control[tmp].u[1];
	m_u2 = ctx->control[tmp].u[2];
	UpdateData(FALSE);
}

void CControl_ID::OnBUTTONUpdate() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください

	UpdateData(TRUE);
	tmp=m_Control_ID;
	if(m_flag0 == 0) ctx->control[tmp].flag[0]=FALSE;
	if(m_flag0 == 1) ctx->control[tmp].flag[0]=TRUE;
	if(m_flag1 == 0) ctx->control[tmp].flag[1]=FALSE;
	if(m_flag1 == 1) ctx->control[tmp].flag[1]=TRUE;
	if(m_flag2 == 0) ctx->control[tmp].flag[2]=FALSE;
	if(m_flag2 == 1) ctx->control[tmp].flag[2]=TRUE;
	ctx->control[tmp].K0 = m_K0;
	ctx->control[tmp].p[0] = m_p0;
	ctx->control[tmp].p[1] = m_p1;
	ctx->control[tmp].p[2] = m_p2;
	ctx->control[tmp].q[0] = m_q0;
	ctx->control[tmp].q[1] = m_q1;
	ctx->control[tmp].q[2] = m_q2;
	ctx->control[tmp].sigma[0] = m_sigma0;
	ctx->control[tmp].sigma[1] = m_sigma1;
	ctx->control[tmp].sigma[2] = m_sigma2;
	ctx->control[tmp].sigmaAmp[0] = m_sigmaAmp0;
	ctx->control[tmp].sigmaAmp[1] = m_sigmaAmp1;
	ctx->control[tmp].sigmaAmp[2] = m_sigmaAmp2;
	ctx->control[tmp].sigmaRate[0] = m_sigmaRate0;
	ctx->control[tmp].sigmaRate[1] = m_sigmaRate1;
	ctx->control[tmp].sigmaRate[2] = m_sigmaRate2;
	ctx->control[tmp].strain[0] = m_strain0;
	ctx->control[tmp].strain[1] = m_strain1;
	ctx->control[tmp].strain[2] = m_strain2;	
	ctx->control[tmp].strainAmp[0] = m_strainAmp0;
	ctx->control[tmp].strainAmp[1] = m_strainAmp1;
	ctx->control[tmp].strainAmp[2] = m_strainAmp2;
	ctx->control[tmp].strainRate[0] = m_strainRate0;
	ctx->control[tmp].strainRate[1] = m_strainRate1;
	ctx->control[tmp].strainRate[2] = m_strainRate2;
	ctx->control[tmp].time[0] = m_time0;
	ctx->control[tmp].time[1] = m_time1;
	ctx->control[tmp].time[2] = m_time2;
	ctx->control[tmp].u[0] = m_u0;
	ctx->control[tmp].u[1] = m_u1;
	ctx->control[tmp].u[2] = m_u2;
}

void CControl_ID::OnBUTTONLoadfromfile() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int	i;
	CString	pFileName;
	FILE	*FileCtlData;

	CFileDialog CtlReadFile_dlg( TRUE, NULL, "*.ctl",  OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		"Specimen Files(*.ctl)|*.ctl| All Files(*.*)|*.*| |",NULL);

	if (CtlReadFile_dlg.DoModal()==IDOK)
	{
	    pFileName = CtlReadFile_dlg.GetPathName();	
		FileCtlData = fopen((LPCSTR)pFileName , "r" );
		for(i=0;i<16;i++){
			fscanf(FileCtlData,"%d",&i);
			fscanf(FileCtlData,"%d%d%d",&ctx->control[i].flag[0],&ctx->control[i].flag[1],&ctx->control[i].flag[2]);
			fscanf(FileCtlData,"%d%d%d",&ctx->control[i].time[0],&ctx->control[i].time[1],&ctx->control[i].time[2]);
			fscanf(FileCtlData,"%lf%lf%lf",&ctx->control[i].p[0],&ctx->control[i].p[1],&ctx->control[i].p[2]);
			fscanf(FileCtlData,"%lf%lf%lf",&ctx->control[i].q[0],&ctx->control[i].q[1],&ctx->control[i].q[2]);
			fscanf(FileCtlData,"%lf%lf%lf",&ctx->control[i].u[0],&ctx->control[i].u[1],&ctx->control[i].u[2]);
			fscanf(FileCtlData,"%lf%lf%lf",&ctx->control[i].sigma[0],&ctx->control[i].sigma[1],&ctx->control[i].sigma[2]);
			fscanf(FileCtlData,"%lf%lf%lf",&ctx->control[i].sigmaRate[0],&ctx->control[i].sigmaRate[1],&ctx->control[i].sigmaRate[2]);
			fscanf(FileCtlData,"%lf%lf%lf",&ctx->control[i].sigmaAmp[0],&ctx->control[i].sigmaAmp[1],&ctx->control[i].sigmaAmp[2]);
			fscanf(FileCtlData,"%lf%lf%lf",&ctx->control[i].strain[0],&ctx->control[i].strain[1],&ctx->control[i].strain[2]);
			fscanf(FileCtlData,"%lf%lf%lf",&ctx->control[i].strainAmp[0],&ctx->control[i].strainAmp[1],&ctx->control[i].strainAmp[2]);
			fscanf(FileCtlData,"%lf%lf%lf",&ctx->control[i].strainRate[0],&ctx->control[i].strainRate[1],&ctx->control[i].strainRate[2]);
			fscanf(FileCtlData,"%lf",&ctx->control[i].K0);
		}
		fclose(FileCtlData);
		OnBUTTONLoad();
	}	
	else{
				AfxMessageBox("Opening file is failed.", MB_ICONEXCLAMATION | MB_OK );
	}
}

void CControl_ID::OnBUTTONSaveFile() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int	i;
	CString	pFileName;
	FILE	*FileCtlData;

	CFileDialog CtlSaveFile_dlg( FALSE, NULL, "*.ctl",  OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT,
		"Specimen Files(*.ctl)|*.ctl| All Files(*.*)|*.*| |",NULL);

	if (CtlSaveFile_dlg.DoModal()==IDOK)
	{
	    pFileName = CtlSaveFile_dlg.GetPathName();	
		FileCtlData = fopen((LPCSTR)pFileName , "w" );
		for(i=0;i<16;i++){
			fprintf(FileCtlData,"%d\n",i);
			fprintf(FileCtlData,"%d	%d	%d\n",ctx->control[i].flag[0],ctx->control[i].flag[1],ctx->control[i].flag[2]);
			fprintf(FileCtlData,"%d	%d	%d\n",ctx->control[i].time[0],ctx->control[i].time[1],ctx->control[i].time[2]);
			fprintf(FileCtlData,"%lf	%lf %lf\n",ctx->control[i].p[0],ctx->control[i].p[1],ctx->control[i].p[2]);
			fprintf(FileCtlData,"%lf	%lf	%lf\n",ctx->control[i].q[0],ctx->control[i].q[1],ctx->control[i].q[2]);
			fprintf(FileCtlData,"%lf	%lf	%lf\n",ctx->control[i].u[0],ctx->control[i].u[1],ctx->control[i].u[2]);
			fprintf(FileCtlData,"%lf	%lf	%lf\n",ctx->control[i].sigma[0],ctx->control[i].sigma[1],ctx->control[i].sigma[2]);
			fprintf(FileCtlData,"%lf	%lf	%lf\n",ctx->control[i].sigmaRate[0],ctx->control[i].sigmaRate[1],ctx->control[i].sigmaRate[2]);
			fprintf(FileCtlData,"%lf	%lf	%lf\n",ctx->control[i].sigmaAmp[0],ctx->control[i].sigmaAmp[1],ctx->control[i].sigmaAmp[2]);
			fprintf(FileCtlData,"%lf	%lf	%lf\n",ctx->control[i].strain[0],ctx->control[i].strain[1],ctx->control[i].strain[2]);
			fprintf(FileCtlData,"%lf	%lf	%lf\n",ctx->control[i].strainRate[0],ctx->control[i].strainRate[1],ctx->control[i].strainRate[2]);
			fprintf(FileCtlData,"%lf	%lf	%lf\n",ctx->control[i].strainAmp[0],ctx->control[i].strainAmp[1],ctx->control[i].strainAmp[2]);
			fprintf(FileCtlData,"%lf\n",ctx->control[i].K0);
		}
		fclose(FileCtlData);
	}
	else{
		AfxMessageBox("Opening file is failed.", MB_ICONEXCLAMATION | MB_OK );
	}		
}
