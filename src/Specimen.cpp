// Specimen.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "DigitShowBasic.h"
#include "Specimen.h"
#include "DigitShowContext.h"
#include "DigitShowBasicDoc.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpecimen ダイアログ

CSpecimen::CSpecimen(CWnd* pParent /*=NULL*/)
	: CDialog(CSpecimen::IDD, pParent)
{
	DigitShowContext* ctx = GetContext();
	//{{AFX_DATA_INIT(CSpecimen)
	m_Height0 = ctx->specimen.Height[0];
	m_Height1 = ctx->specimen.Height[1];
	m_Height2 = ctx->specimen.Height[2];
	m_Height3 = ctx->specimen.Height[3];
	m_MembraneE = ctx->specimen.MembraneModulus;
	m_MembraneT = ctx->specimen.MembraneThickness;
	m_RodArea = ctx->specimen.RodArea;
	m_CapWeight = ctx->specimen.CapWeight;
	m_RDInM = ctx->specimen.RDiaInM;
	m_RDOutM = ctx->specimen.RDiaOutM;
	m_RHInM = ctx->specimen.RHeightInM;
	m_RHOutM = ctx->specimen.RHeightOutM;
	m_DiaInM0 = ctx->specimen.DiaInMembrane[0];
	m_DiaInM1 = ctx->specimen.DiaInMembrane[1];
	m_DiaInM2 = ctx->specimen.DiaInMembrane[2];
	m_DiaInM3 = ctx->specimen.DiaInMembrane[3];
	m_DiameterIn0 = ctx->specimen.DiameterIn[0];
	m_DiameterIn1 = ctx->specimen.DiameterIn[1];
	m_DiameterIn2 = ctx->specimen.DiameterIn[2];
	m_DiameterIn3 = ctx->specimen.DiameterIn[3];
	m_DiameterOut0 = ctx->specimen.DiameterOut[0];
	m_DiameterOut1 = ctx->specimen.DiameterOut[1];
	m_DiameterOut2 = ctx->specimen.DiameterOut[2];
	m_DiameterOut3 = ctx->specimen.DiameterOut[3];
	m_DiaOutM0 = ctx->specimen.DiaOutMembrane[0];
	m_DiaOutM1 = ctx->specimen.DiaOutMembrane[1];
	m_DiaOutM2 = ctx->specimen.DiaOutMembrane[2];
	m_DiaOutM3 = ctx->specimen.DiaOutMembrane[3];
	m_HeightInM0 = ctx->specimen.HeightInMembrane[0];
	m_HeightInM1 = ctx->specimen.HeightInMembrane[1];
	m_HeightInM2 = ctx->specimen.HeightInMembrane[2];
	m_HeightInM3 = ctx->specimen.HeightInMembrane[3];
	m_HeightOutM0 = ctx->specimen.HeightOutMembrane[0];
	m_HeightOutM1 = ctx->specimen.HeightOutMembrane[1];
	m_HeightOutM2 = ctx->specimen.HeightOutMembrane[2];
	m_HeightOutM3 = ctx->specimen.HeightOutMembrane[3];
	m_Volume0 = ctx->specimen.Volume[0];
	m_Volume1 = ctx->specimen.Volume[1];
	m_Volume2 = ctx->specimen.Volume[2];
	m_Volume3 = ctx->specimen.Volume[3];
	//}}AFX_DATA_INIT
}


void CSpecimen::DoDataExchange(CDataExchange* pDX)
{	DigitShowContext* ctx = GetContext();
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpecimen)
	DDX_Text(pDX, IDC_EDIT_Height0, m_Height0);
	DDX_Text(pDX, IDC_EDIT_Height1, m_Height1);
	DDX_Text(pDX, IDC_EDIT_Height2, m_Height2);
	DDX_Text(pDX, IDC_EDIT_Height3, m_Height3);
	DDX_Text(pDX, IDC_EDIT_MembraneE, m_MembraneE);
	DDX_Text(pDX, IDC_EDIT_MembraneT, m_MembraneT);
	DDX_Text(pDX, IDC_EDIT_RodArea, m_RodArea);
	DDX_Text(pDX, IDC_EDIT_CapWeight, m_CapWeight);
	DDX_Text(pDX, IDC_EDIT_RDInM, m_RDInM);
	DDX_Text(pDX, IDC_EDIT_RDOutM, m_RDOutM);
	DDX_Text(pDX, IDC_EDIT_RHInM, m_RHInM);
	DDX_Text(pDX, IDC_EDIT_RHOutM, m_RHOutM);
	DDX_Text(pDX, IDC_EDIT_DiaInM0, m_DiaInM0);
	DDX_Text(pDX, IDC_EDIT_DiaInM1, m_DiaInM1);
	DDX_Text(pDX, IDC_EDIT_DiaInM2, m_DiaInM2);
	DDX_Text(pDX, IDC_EDIT_DiaInM3, m_DiaInM3);
	DDX_Text(pDX, IDC_EDIT_DiameterIn0, m_DiameterIn0);
	DDX_Text(pDX, IDC_EDIT_DiameterIn1, m_DiameterIn1);
	DDX_Text(pDX, IDC_EDIT_DiameterIn2, m_DiameterIn2);
	DDX_Text(pDX, IDC_EDIT_DiameterIn3, m_DiameterIn3);
	DDX_Text(pDX, IDC_EDIT_DiameterOut0, m_DiameterOut0);
	DDX_Text(pDX, IDC_EDIT_DiameterOut1, m_DiameterOut1);
	DDX_Text(pDX, IDC_EDIT_DiameterOut2, m_DiameterOut2);
	DDX_Text(pDX, IDC_EDIT_DiameterOut3, m_DiameterOut3);
	DDX_Text(pDX, IDC_EDIT_DiaOutM0, m_DiaOutM0);
	DDX_Text(pDX, IDC_EDIT_DiaOutM1, m_DiaOutM1);
	DDX_Text(pDX, IDC_EDIT_DiaOutM2, m_DiaOutM2);
	DDX_Text(pDX, IDC_EDIT_DiaOutM3, m_DiaOutM3);
	DDX_Text(pDX, IDC_EDIT_HeightInM0, m_HeightInM0);
	DDX_Text(pDX, IDC_EDIT_HeightInM1, m_HeightInM1);
	DDX_Text(pDX, IDC_EDIT_HeightInM2, m_HeightInM2);
	DDX_Text(pDX, IDC_EDIT_HeightInM3, m_HeightInM3);
	DDX_Text(pDX, IDC_EDIT_HeightOutM0, m_HeightOutM0);
	DDX_Text(pDX, IDC_EDIT_HeightOutM1, m_HeightOutM1);
	DDX_Text(pDX, IDC_EDIT_HeightOutM2, m_HeightOutM2);
	DDX_Text(pDX, IDC_EDIT_HeightOutM3, m_HeightOutM3);
	DDX_Text(pDX, IDC_EDIT_Volume0, m_Volume0);
	DDX_Text(pDX, IDC_EDIT_Volume1, m_Volume1);
	DDX_Text(pDX, IDC_EDIT_Volume2, m_Volume2);
	DDX_Text(pDX, IDC_EDIT_Volume3, m_Volume3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSpecimen, CDialog)
	//{{AFX_MSG_MAP(CSpecimen)
	ON_BN_CLICKED(IDC_BUTTON_Save, OnBUTTONSave)
	ON_BN_CLICKED(IDC_BUTTON_Update, OnBUTTONUpdate)
	ON_BN_CLICKED(IDC_BUTTON_BeConsol, OnBUTTONBeConsol)
	ON_BN_CLICKED(IDC_BUTTON_AfConsolidation, OnBUTTONAfConsolidation)
	ON_BN_CLICKED(IDC_BUTTON_ToPresent1, OnBUTTONToPresent1)
	ON_BN_CLICKED(IDC_BUTTON_ToPresent2, OnBUTTONToPresent2)
	ON_BN_CLICKED(IDC_BUTTON_ToPresent3, OnBUTTONToPresent3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpecimen メッセージ ハンドラ
void CSpecimen::Load()
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_MembraneE = ctx->specimen.MembraneModulus;
	m_MembraneT = ctx->specimen.MembraneThickness;
	m_RodArea = ctx->specimen.RodArea;
	m_CapWeight = ctx->specimen.CapWeight;
	m_RDInM = ctx->specimen.RDiaInM;
	m_RDOutM = ctx->specimen.RDiaOutM;
	m_RHInM = ctx->specimen.RHeightInM;
	m_RHOutM = ctx->specimen.RHeightOutM;
	m_DiameterIn0 = ctx->specimen.DiameterIn[0];
	m_DiameterIn1 = ctx->specimen.DiameterIn[1];
	m_DiameterIn2 = ctx->specimen.DiameterIn[2];
	m_DiameterIn3 = ctx->specimen.DiameterIn[3];
	m_DiameterOut0 = ctx->specimen.DiameterOut[0];
	m_DiameterOut1 = ctx->specimen.DiameterOut[1];
	m_DiameterOut2 = ctx->specimen.DiameterOut[2];
	m_DiameterOut3 = ctx->specimen.DiameterOut[3];
	m_Height0 = ctx->specimen.Height[0];
	m_Height1 = ctx->specimen.Height[1];
	m_Height2 = ctx->specimen.Height[2];
	m_Height3 = ctx->specimen.Height[3];
	m_Volume0 = ctx->specimen.Volume[0];
	m_Volume1 = ctx->specimen.Volume[1];
	m_Volume2 = ctx->specimen.Volume[2];
	m_Volume3 = ctx->specimen.Volume[3];
	m_DiaInM0 = ctx->specimen.DiaInMembrane[0];
	m_DiaInM1 = ctx->specimen.DiaInMembrane[1];
	m_DiaInM2 = ctx->specimen.DiaInMembrane[2];
	m_DiaInM3 = ctx->specimen.DiaInMembrane[3];
	m_DiaOutM0 = ctx->specimen.DiaOutMembrane[0];
	m_DiaOutM1 = ctx->specimen.DiaOutMembrane[1];
	m_DiaOutM2 = ctx->specimen.DiaOutMembrane[2];
	m_DiaOutM3 = ctx->specimen.DiaOutMembrane[3];
	m_HeightInM0 = ctx->specimen.HeightInMembrane[0];
	m_HeightInM1 = ctx->specimen.HeightInMembrane[1];
	m_HeightInM2 = ctx->specimen.HeightInMembrane[2];
	m_HeightInM3 = ctx->specimen.HeightInMembrane[3];
	m_HeightOutM0 = ctx->specimen.HeightOutMembrane[0];
	m_HeightOutM1 = ctx->specimen.HeightOutMembrane[1];
	m_HeightOutM2 = ctx->specimen.HeightOutMembrane[2];
	m_HeightOutM3 = ctx->specimen.HeightOutMembrane[3];
	UpdateData(FALSE);
}

void CSpecimen::OnBUTTONUpdate() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(TRUE);
	ctx->specimen.MembraneModulus = m_MembraneE;
	ctx->specimen.MembraneThickness = m_MembraneT;
	ctx->specimen.RodArea = m_RodArea;
	ctx->specimen.CapWeight = m_CapWeight;
	ctx->specimen.RDiaInM = m_RDInM;
	ctx->specimen.RDiaOutM = m_RDOutM;
	ctx->specimen.RHeightInM = m_RHInM;
	ctx->specimen.RHeightOutM = m_RHOutM;
	ctx->specimen.DiameterIn[0] = m_DiameterIn0;
	ctx->specimen.DiameterIn[1] = m_DiameterIn1;
	ctx->specimen.DiameterIn[2] = m_DiameterIn2;
	ctx->specimen.DiameterIn[3] = m_DiameterIn3;
	ctx->specimen.DiameterOut[0] = m_DiameterOut0;
	ctx->specimen.DiameterOut[1] = m_DiameterOut1;
	ctx->specimen.DiameterOut[2] = m_DiameterOut2;
	ctx->specimen.DiameterOut[3] = m_DiameterOut3;
	ctx->specimen.Height[0] = m_Height0;
	ctx->specimen.Height[1] = m_Height1;
	ctx->specimen.Height[2] = m_Height2;
	ctx->specimen.Height[3] = m_Height3;
	ctx->specimen.Volume[0] = 3.141592*(ctx->specimen.DiameterOut[0]*ctx->specimen.DiameterOut[0]-ctx->specimen.DiameterIn[0]*ctx->specimen.DiameterIn[0])/4.0*ctx->specimen.Height[0];
	ctx->specimen.Volume[1] = 3.141592*(ctx->specimen.DiameterOut[1]*ctx->specimen.DiameterOut[1]-ctx->specimen.DiameterIn[1]*ctx->specimen.DiameterIn[1])/4.0*ctx->specimen.Height[1];
	ctx->specimen.Volume[2] = 3.141592*(ctx->specimen.DiameterOut[2]*ctx->specimen.DiameterOut[2]-ctx->specimen.DiameterIn[2]*ctx->specimen.DiameterIn[2])/4.0*ctx->specimen.Height[2];
	ctx->specimen.Volume[3] = 3.141592*(ctx->specimen.DiameterOut[3]*ctx->specimen.DiameterOut[3]-ctx->specimen.DiameterIn[3]*ctx->specimen.DiameterIn[3])/4.0*ctx->specimen.Height[3];
	ctx->specimen.DiaInMembrane[0] = m_DiaInM0;
	ctx->specimen.DiaInMembrane[1] = m_DiaInM1;
	ctx->specimen.DiaInMembrane[2] = m_DiaInM2;
	ctx->specimen.DiaInMembrane[3] = m_DiaInM3;
	ctx->specimen.DiaOutMembrane[0] = m_DiaOutM0;
	ctx->specimen.DiaOutMembrane[1] = m_DiaOutM1;
	ctx->specimen.DiaOutMembrane[2] = m_DiaOutM2;
	ctx->specimen.DiaOutMembrane[3] = m_DiaOutM3;
	ctx->specimen.HeightInMembrane[0] = m_HeightInM0;
	ctx->specimen.HeightInMembrane[1] = m_HeightInM1;
	ctx->specimen.HeightInMembrane[2] = m_HeightInM2;
	ctx->specimen.HeightInMembrane[3] = m_HeightInM3;
	ctx->specimen.HeightOutMembrane[0] = m_HeightOutM0;
	ctx->specimen.HeightOutMembrane[1] = m_HeightOutM1;
	ctx->specimen.HeightOutMembrane[2] = m_HeightOutM2;
	ctx->specimen.HeightOutMembrane[3] = m_HeightOutM3;
	Load();
}

void CSpecimen::OnBUTTONSave() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	
	OnBUTTONUpdate();

	CString	pFileName;
	FILE	*FileSpcData;

	CFileDialog SpcSaveFile_dlg( FALSE, NULL, "*.spe",  OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT,
		"Specimen Files(*.spe)|*.spe| All Files(*.*)|*.*| |",NULL);

	if (SpcSaveFile_dlg.DoModal()==IDOK)
	{
	    pFileName = SpcSaveFile_dlg.GetPathName();	
		FileSpcData = fopen((LPCSTR)pFileName , "w" );
		fprintf(FileSpcData,"%s	%lf	\n","ReferentialDiameter_InnerMembrane(mm)",ctx->specimen.RDiaInM);
		fprintf(FileSpcData,"%s	%lf	\n","ReferentialDiameter_OuterMembrane(mm)",ctx->specimen.RDiaOutM);
		fprintf(FileSpcData,"%s	%lf	\n","ReferentialHeight_InnerMembrane(mm)",ctx->specimen.RHeightInM);
		fprintf(FileSpcData,"%s	%lf	\n","ReferentialHeight_OuterMembrane(mm)",ctx->specimen.RHeightOutM);
		fprintf(FileSpcData,"%s	%lf	\n","Membrane_Young's_Modulus(kPa)",ctx->specimen.MembraneModulus);
		fprintf(FileSpcData,"%s	%lf	\n","Membrane_Thickness(mm)",ctx->specimen.MembraneThickness);
		fprintf(FileSpcData,"%s	%lf	\n","Rod_Area(mm2)",ctx->specimen.RodArea);
		fprintf(FileSpcData,"%s	%lf	\n","Cap_Weight(N)",ctx->specimen.CapWeight);
//
		fprintf(FileSpcData,"%s	%lf	%lf	%lf	%lf	\n","Inner_Diameter(mm)",ctx->specimen.DiameterIn[0],ctx->specimen.DiameterIn[1],ctx->specimen.DiameterIn[2],ctx->specimen.DiameterIn[3]);
		fprintf(FileSpcData,"%s	%lf	%lf	%lf	%lf	\n","Outer_Diameter(mm)",ctx->specimen.DiameterOut[0],ctx->specimen.DiameterOut[1],ctx->specimen.DiameterOut[2],ctx->specimen.DiameterOut[3]);
		fprintf(FileSpcData,"%s	%lf	%lf	%lf	%lf	\n","Height(mm)",ctx->specimen.Height[0],ctx->specimen.Height[1],ctx->specimen.Height[2],ctx->specimen.Height[3]);
		fprintf(FileSpcData,"%s	%lf	%lf	%lf	%lf	\n","Volume(mm3)",ctx->specimen.Volume[0],ctx->specimen.Volume[1],ctx->specimen.Volume[2],ctx->specimen.Volume[3]);
		fprintf(FileSpcData,"%s	%lf	%lf	%lf	%lf	\n","Diameter_InnerMembrane(mm)",ctx->specimen.DiaInMembrane[0],ctx->specimen.DiaInMembrane[1],ctx->specimen.DiaInMembrane[2],ctx->specimen.DiaInMembrane[3]);
		fprintf(FileSpcData,"%s	%lf	%lf	%lf	%lf	\n","Diameter_OuterMembrane(mm)",ctx->specimen.DiaOutMembrane[0],ctx->specimen.DiaOutMembrane[1],ctx->specimen.DiaOutMembrane[2],ctx->specimen.DiaOutMembrane[3]);
		fprintf(FileSpcData,"%s	%lf	%lf	%lf	%lf	\n","Height_InnerMembrane(mm)",ctx->specimen.HeightInMembrane[0],ctx->specimen.HeightInMembrane[1],ctx->specimen.HeightInMembrane[2],ctx->specimen.HeightInMembrane[3]);
		fprintf(FileSpcData,"%s	%lf	%lf	%lf	%lf	\n","Height_OuterMembrane(mm)",ctx->specimen.HeightOutMembrane[0],ctx->specimen.HeightOutMembrane[1],ctx->specimen.HeightOutMembrane[2],ctx->specimen.HeightOutMembrane[3]);
		fclose(FileSpcData);
	}	
}

void CSpecimen::OnBUTTONBeConsol() 
{	DigitShowContext* ctx = GetContext();
	double BeConsol_ez = 0.0, BeConsol_ev = 0.0;
	// TODO: Add your control notification handler code here
	//@note Hashimoto modified 2022/12/17
	ctx->specimen.Height[2]=ctx->phys.height;
	//ctx->specimen.Volume[2]=ctx->phys.height*3.141592*(pow(ctx->specimen.DiameterOut[1],2.0)-pow(ctx->specimen.DiameterIn[1],2.0))/4.0;
	//ctx->specimen.DiameterIn[2]=ctx->specimen.DiameterIn[1];
	//ctx->specimen.DiameterOut[2]=ctx->specimen.DiameterOut[1];
	//ctx->specimen.DiaInMembrane[2] = ctx->specimen.DiaInMembrane[1];
	//ctx->specimen.DiaOutMembrane[2] = ctx->specimen.DiaOutMembrane[1];
	//ctx->specimen.HeightInMembrane[2] = ctx->specimen.HeightInMembrane[1];
	//ctx->specimen.HeightOutMembrane[2] = ctx->specimen.HeightOutMembrane[1];
	BeConsol_ez = 1 - ctx->phys.height / ctx->specimen.Height[1];
	BeConsol_ev = BeConsol_ez * 3;  // assume isotropic deformation
	ctx->specimen.Volume[2] = ctx->specimen.Volume[1] * (1 - BeConsol_ev);
	ctx->specimen.DiameterIn[2] = ctx->specimen.DiameterIn[1] * sqrt((1 - BeConsol_ev) / (1 - BeConsol_ez));
	ctx->specimen.DiameterOut[2] = ctx->specimen.DiameterOut[1] * sqrt((1 - BeConsol_ev) / (1 - BeConsol_ez));
	ctx->specimen.DiaInMembrane[2] = ctx->specimen.DiameterIn[2] - ctx->specimen.MembraneThickness / 2.0;
	ctx->specimen.DiaOutMembrane[2] = ctx->specimen.DiameterOut[2] + ctx->specimen.MembraneThickness / 2.0;
	ctx->specimen.HeightInMembrane[2] = ctx->phys.height;
	ctx->specimen.HeightOutMembrane[2] = ctx->phys.height;
	
	//---Initialize Displacement transducer---
	ctx->ai.cal.c[5] -= ctx->ai.phy[5]; // initialize ez
	//ctx->ai.cal.c[18]=ctx->ai.cal.c[18]-ctx->ai.phy[18];
	ctx->ai.cal.c[13] -= ctx->ai.phy[13]; // initialize ev
	Load();
	OnBUTTONToPresent2();
}

void CSpecimen::OnBUTTONAfConsolidation() 
{	DigitShowContext* ctx = GetContext();
	// TODO: Add your control notification handler code here
	//@note Hashimoto modified 2022/12/22
	ctx->specimen.Height[3]=ctx->phys.height;
	ctx->specimen.Volume[3]=ctx->phys.volume;
	ctx->specimen.DiameterIn[3]=ctx->phys.diameter_in;
	ctx->specimen.DiameterOut[3]=ctx->phys.diameter_out;
	//ctx->specimen.DiaInMembrane[3] = ctx->specimen.DiaInMembrane[2];
	//ctx->specimen.DiaOutMembrane[3] = ctx->specimen.DiaOutMembrane[2];
	//ctx->specimen.HeightInMembrane[3] = ctx->specimen.HeightInMembrane[2];
	//ctx->specimen.HeightOutMembrane[3] = ctx->specimen.HeightOutMembrane[2];
	ctx->specimen.DiaInMembrane[3] = ctx->phys.diameter_in - ctx->specimen.MembraneThickness / 2.0;
	ctx->specimen.DiaOutMembrane[3] = ctx->phys.diameter_out + ctx->specimen.MembraneThickness / 2.0;
	ctx->specimen.HeightInMembrane[3] = ctx->phys.height;
	ctx->specimen.HeightOutMembrane[3] = ctx->phys.height;

	//---Initialize Displacement transducer---
	ctx->ai.cal.c[5] -= ctx->ai.phy[5]; // initialize ez
	//ctx->ai.cal.c[18]=ctx->ai.cal.c[18]-ctx->ai.phy[18];
	ctx->ai.cal.c[13] -= ctx->ai.phy[13]; // initialize ev
	Load();
	OnBUTTONToPresent3();
}

void CSpecimen::OnBUTTONToPresent1() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONUpdate();
	ctx->specimen.DiameterIn[0] = ctx->specimen.DiameterIn[1];
	ctx->specimen.DiameterOut[0] = ctx->specimen.DiameterOut[1];
	ctx->specimen.Height[0] = ctx->specimen.Height[1];
	ctx->specimen.Volume[0] = ctx->specimen.Volume[1];
	ctx->specimen.DiaInMembrane[0] = ctx->specimen.DiaInMembrane[1];
	ctx->specimen.DiaOutMembrane[0] = ctx->specimen.DiaOutMembrane[1];
	ctx->specimen.HeightInMembrane[0] = ctx->specimen.HeightInMembrane[1];
	ctx->specimen.HeightOutMembrane[0] = ctx->specimen.HeightOutMembrane[1];
	Load();
}

void CSpecimen::OnBUTTONToPresent2() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONUpdate();
	ctx->specimen.DiameterIn[0] = ctx->specimen.DiameterIn[2];
	ctx->specimen.DiameterOut[0] = ctx->specimen.DiameterOut[2];
	ctx->specimen.Height[0] = ctx->specimen.Height[2];
	ctx->specimen.Volume[0] = ctx->specimen.Volume[2];
	ctx->specimen.DiaInMembrane[0] = ctx->specimen.DiaInMembrane[2];
	ctx->specimen.DiaOutMembrane[0] = ctx->specimen.DiaOutMembrane[2];
	ctx->specimen.HeightInMembrane[0] = ctx->specimen.HeightInMembrane[2];
	ctx->specimen.HeightOutMembrane[0] = ctx->specimen.HeightOutMembrane[2];
	Load();
}

void CSpecimen::OnBUTTONToPresent3() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONUpdate();
	ctx->specimen.DiameterIn[0] = ctx->specimen.DiameterIn[3];
	ctx->specimen.DiameterOut[0] = ctx->specimen.DiameterOut[3];
	ctx->specimen.Height[0] = ctx->specimen.Height[3];
	ctx->specimen.Volume[0] = ctx->specimen.Volume[3];
	ctx->specimen.DiaInMembrane[0] = ctx->specimen.DiaInMembrane[3];
	ctx->specimen.DiaOutMembrane[0] = ctx->specimen.DiaOutMembrane[3];
	ctx->specimen.HeightInMembrane[0] = ctx->specimen.HeightInMembrane[3];
	ctx->specimen.HeightOutMembrane[0] = ctx->specimen.HeightOutMembrane[3];
	Load();
}


