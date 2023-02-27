// Specimen.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "DigitShowBasic.h"
#include "Specimen.h"
#include "DigitShowBasicDoc.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpecimen ダイアログ
extern	Specimen	SpecimenData;
extern	double		Phyout[32],Cal_c[32];
extern	int			Control_ID;
extern	double		height,area,volume,diameter_in,diameter_out;	// Current specimen size

CSpecimen::CSpecimen(CWnd* pParent /*=NULL*/)
	: CDialog(CSpecimen::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpecimen)
	m_Height0 = SpecimenData.Height[0];
	m_Height1 = SpecimenData.Height[1];
	m_Height2 = SpecimenData.Height[2];
	m_Height3 = SpecimenData.Height[3];
	m_MembraneE = SpecimenData.MembraneModulus;
	m_MembraneT = SpecimenData.MembraneThickness;
	m_RodArea = SpecimenData.RodArea;
	m_CapWeight = SpecimenData.CapWeight;
	m_RDInM = SpecimenData.RDiaInM;
	m_RDOutM = SpecimenData.RDiaOutM;
	m_RHInM = SpecimenData.RHeightInM;
	m_RHOutM = SpecimenData.RHeightOutM;
	m_DiaInM0 = SpecimenData.DiaInMembrane[0];
	m_DiaInM1 = SpecimenData.DiaInMembrane[1];
	m_DiaInM2 = SpecimenData.DiaInMembrane[2];
	m_DiaInM3 = SpecimenData.DiaInMembrane[3];
	m_DiameterIn0 = SpecimenData.DiameterIn[0];
	m_DiameterIn1 = SpecimenData.DiameterIn[1];
	m_DiameterIn2 = SpecimenData.DiameterIn[2];
	m_DiameterIn3 = SpecimenData.DiameterIn[3];
	m_DiameterOut0 = SpecimenData.DiameterOut[0];
	m_DiameterOut1 = SpecimenData.DiameterOut[1];
	m_DiameterOut2 = SpecimenData.DiameterOut[2];
	m_DiameterOut3 = SpecimenData.DiameterOut[3];
	m_DiaOutM0 = SpecimenData.DiaOutMembrane[0];
	m_DiaOutM1 = SpecimenData.DiaOutMembrane[1];
	m_DiaOutM2 = SpecimenData.DiaOutMembrane[2];
	m_DiaOutM3 = SpecimenData.DiaOutMembrane[3];
	m_HeightInM0 = SpecimenData.HeightInMembrane[0];
	m_HeightInM1 = SpecimenData.HeightInMembrane[1];
	m_HeightInM2 = SpecimenData.HeightInMembrane[2];
	m_HeightInM3 = SpecimenData.HeightInMembrane[3];
	m_HeightOutM0 = SpecimenData.HeightOutMembrane[0];
	m_HeightOutM1 = SpecimenData.HeightOutMembrane[0];
	m_HeightOutM2 = SpecimenData.HeightOutMembrane[0];
	m_HeightOutM3 = SpecimenData.HeightOutMembrane[3];
	m_Volume0 = SpecimenData.Volume[0];
	m_Volume1 = SpecimenData.Volume[1];
	m_Volume2 = SpecimenData.Volume[2];
	m_Volume3 = SpecimenData.Volume[3];
	//}}AFX_DATA_INIT
}


void CSpecimen::DoDataExchange(CDataExchange* pDX)
{
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
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_MembraneE = SpecimenData.MembraneModulus;
	m_MembraneT = SpecimenData.MembraneThickness;
	m_RodArea = SpecimenData.RodArea;
	m_CapWeight = SpecimenData.CapWeight;
	m_RDInM = SpecimenData.RDiaInM;
	m_RDOutM = SpecimenData.RDiaOutM;
	m_RHInM = SpecimenData.RHeightInM;
	m_RHOutM = SpecimenData.RHeightOutM;
	m_DiameterIn0 = SpecimenData.DiameterIn[0];
	m_DiameterIn1 = SpecimenData.DiameterIn[1];
	m_DiameterIn2 = SpecimenData.DiameterIn[2];
	m_DiameterIn3 = SpecimenData.DiameterIn[3];
	m_DiameterOut0 = SpecimenData.DiameterOut[0];
	m_DiameterOut1 = SpecimenData.DiameterOut[1];
	m_DiameterOut2 = SpecimenData.DiameterOut[2];
	m_DiameterOut3 = SpecimenData.DiameterOut[3];
	m_Height0 = SpecimenData.Height[0];
	m_Height1 = SpecimenData.Height[1];
	m_Height2 = SpecimenData.Height[2];
	m_Height3 = SpecimenData.Height[3];
	m_Volume0 = SpecimenData.Volume[0];
	m_Volume1 = SpecimenData.Volume[1];
	m_Volume2 = SpecimenData.Volume[2];
	m_Volume3 = SpecimenData.Volume[3];
	m_DiaInM0 = SpecimenData.DiaInMembrane[0];
	m_DiaInM1 = SpecimenData.DiaInMembrane[1];
	m_DiaInM2 = SpecimenData.DiaInMembrane[2];
	m_DiaInM3 = SpecimenData.DiaInMembrane[3];
	m_DiaOutM0 = SpecimenData.DiaOutMembrane[0];
	m_DiaOutM1 = SpecimenData.DiaOutMembrane[1];
	m_DiaOutM2 = SpecimenData.DiaOutMembrane[2];
	m_DiaOutM3 = SpecimenData.DiaOutMembrane[3];
	m_HeightInM0 = SpecimenData.HeightInMembrane[0];
	m_HeightInM1 = SpecimenData.HeightInMembrane[1];
	m_HeightInM2 = SpecimenData.HeightInMembrane[2];
	m_HeightInM3 = SpecimenData.HeightInMembrane[3];
	m_HeightOutM0 = SpecimenData.HeightOutMembrane[0];
	m_HeightOutM1 = SpecimenData.HeightOutMembrane[0];
	m_HeightOutM2 = SpecimenData.HeightOutMembrane[0];
	m_HeightOutM3 = SpecimenData.HeightOutMembrane[3];
	UpdateData(FALSE);
}

void CSpecimen::OnBUTTONUpdate() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(TRUE);
	SpecimenData.MembraneModulus = m_MembraneE;
	SpecimenData.MembraneThickness = m_MembraneT;
	SpecimenData.RodArea = m_RodArea;
	SpecimenData.CapWeight = m_CapWeight;
	SpecimenData.RDiaInM = m_RDInM;
	SpecimenData.RDiaOutM = m_RDOutM;
	SpecimenData.RHeightInM = m_RHInM;
	SpecimenData.RHeightOutM = m_RHOutM;
	SpecimenData.DiameterIn[0] = m_DiameterIn0;
	SpecimenData.DiameterIn[1] = m_DiameterIn1;
	SpecimenData.DiameterIn[2] = m_DiameterIn2;
	SpecimenData.DiameterIn[3] = m_DiameterIn3;
	SpecimenData.DiameterOut[0] = m_DiameterOut0;
	SpecimenData.DiameterOut[1] = m_DiameterOut1;
	SpecimenData.DiameterOut[2] = m_DiameterOut2;
	SpecimenData.DiameterOut[3] = m_DiameterOut3;
	SpecimenData.Height[0] = m_Height0;
	SpecimenData.Height[1] = m_Height1;
	SpecimenData.Height[2] = m_Height2;
	SpecimenData.Height[3] = m_Height3;
	SpecimenData.Volume[0] = 3.141592*(SpecimenData.DiameterOut[0]*SpecimenData.DiameterOut[0]-SpecimenData.DiameterIn[0]*SpecimenData.DiameterIn[0])/4.0*SpecimenData.Height[0];
	SpecimenData.Volume[1] = 3.141592*(SpecimenData.DiameterOut[1]*SpecimenData.DiameterOut[1]-SpecimenData.DiameterIn[1]*SpecimenData.DiameterIn[1])/4.0*SpecimenData.Height[1];
	SpecimenData.Volume[2] = 3.141592*(SpecimenData.DiameterOut[2]*SpecimenData.DiameterOut[2]-SpecimenData.DiameterIn[2]*SpecimenData.DiameterIn[2])/4.0*SpecimenData.Height[2];
	SpecimenData.Volume[3] = 3.141592*(SpecimenData.DiameterOut[3]*SpecimenData.DiameterOut[3]-SpecimenData.DiameterIn[3]*SpecimenData.DiameterIn[3])/4.0*SpecimenData.Height[3];
	SpecimenData.DiaInMembrane[0] = m_DiaInM0;
	SpecimenData.DiaInMembrane[1] = m_DiaInM1;
	SpecimenData.DiaInMembrane[2] = m_DiaInM2;
	SpecimenData.DiaInMembrane[3] = m_DiaInM3;
	SpecimenData.DiaOutMembrane[0] = m_DiaOutM0;
	SpecimenData.DiaOutMembrane[1] = m_DiaOutM1;
	SpecimenData.DiaOutMembrane[2] = m_DiaOutM2;
	SpecimenData.DiaOutMembrane[3] = m_DiaOutM3;
	SpecimenData.HeightInMembrane[0] = m_HeightInM0;
	SpecimenData.HeightInMembrane[1] = m_HeightInM1;
	SpecimenData.HeightInMembrane[2] = m_HeightInM2;
	SpecimenData.HeightInMembrane[3] = m_HeightInM3;
	SpecimenData.HeightOutMembrane[0] = m_HeightOutM0;
	SpecimenData.HeightOutMembrane[0] = m_HeightOutM1;
	SpecimenData.HeightOutMembrane[0] = m_HeightOutM2;
	SpecimenData.HeightOutMembrane[3] = m_HeightOutM3;
	Load();
}

void CSpecimen::OnBUTTONSave() 
{
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
		fprintf(FileSpcData,"%s	%lf	\n","ReferentialDiameter_InnerMembrane(mm)",SpecimenData.RDiaInM);
		fprintf(FileSpcData,"%s	%lf	\n","ReferentialDiameter_OuterMembrane(mm)",SpecimenData.RDiaOutM);
		fprintf(FileSpcData,"%s	%lf	\n","ReferentialHeight_InnerMembrane(mm)",SpecimenData.RHeightInM);
		fprintf(FileSpcData,"%s	%lf	\n","ReferentialHeight_OuterMembrane(mm)",SpecimenData.RHeightOutM);
		fprintf(FileSpcData,"%s	%lf	\n","Membrane_Young's_Modulus(kPa)",SpecimenData.MembraneModulus);
		fprintf(FileSpcData,"%s	%lf	\n","Membrane_Thickness(mm)",SpecimenData.MembraneThickness);
		fprintf(FileSpcData,"%s	%lf	\n","Rod_Area(mm2)",SpecimenData.RodArea);
		fprintf(FileSpcData,"%s	%lf	\n","Cap_Weight(N)",SpecimenData.CapWeight);
//
		fprintf(FileSpcData,"%s	%lf	%lf	%lf	%lf	\n","Inner_Diameter(mm)",SpecimenData.DiameterIn[0],SpecimenData.DiameterIn[1],SpecimenData.DiameterIn[2],SpecimenData.DiameterIn[3]);
		fprintf(FileSpcData,"%s	%lf	%lf	%lf	%lf	\n","Outer_Diameter(mm)",SpecimenData.DiameterOut[0],SpecimenData.DiameterOut[1],SpecimenData.DiameterOut[2],SpecimenData.DiameterOut[3]);
		fprintf(FileSpcData,"%s	%lf	%lf	%lf	%lf	\n","Height(mm)",SpecimenData.Height[0],SpecimenData.Height[1],SpecimenData.Height[2],SpecimenData.Height[3]);
		fprintf(FileSpcData,"%s	%lf	%lf	%lf	%lf	\n","Volume(mm3)",SpecimenData.Volume[0],SpecimenData.Volume[1],SpecimenData.Volume[2],SpecimenData.Volume[3]);
		fprintf(FileSpcData,"%s	%lf	%lf	%lf	%lf	\n","Diameter_InnerMembrane(mm)",SpecimenData.DiaInMembrane[0],SpecimenData.DiaInMembrane[1],SpecimenData.DiaInMembrane[2],SpecimenData.DiaInMembrane[3]);
		fprintf(FileSpcData,"%s	%lf	%lf	%lf	%lf	\n","Diameter_OuterMembrane(mm)",SpecimenData.DiaOutMembrane[0],SpecimenData.DiaOutMembrane[1],SpecimenData.DiaOutMembrane[2],SpecimenData.DiaOutMembrane[3]);
		fprintf(FileSpcData,"%s	%lf	%lf	%lf	%lf	\n","Height_InnerMembrane(mm)",SpecimenData.HeightInMembrane[0],SpecimenData.HeightInMembrane[1],SpecimenData.HeightInMembrane[2],SpecimenData.HeightInMembrane[3]);
		fprintf(FileSpcData,"%s	%lf	%lf	%lf	%lf	\n","Height_OuterMembrane(mm)",SpecimenData.HeightOutMembrane[0],SpecimenData.HeightOutMembrane[1],SpecimenData.HeightOutMembrane[2],SpecimenData.HeightOutMembrane[3]);
		fclose(FileSpcData);
	}	
}

void CSpecimen::OnBUTTONBeConsol() 
{
	double BeConsol_ez = 0.0, BeConsol_ev = 0.0;
	// TODO: Add your control notification handler code here
	//@note Hashimoto modified 2022/12/17
	SpecimenData.Height[2]=height;
	//SpecimenData.Volume[2]=height*3.141592*(pow(SpecimenData.DiameterOut[1],2.0)-pow(SpecimenData.DiameterIn[1],2.0))/4.0;
	//SpecimenData.DiameterIn[2]=SpecimenData.DiameterIn[1];
	//SpecimenData.DiameterOut[2]=SpecimenData.DiameterOut[1];
	//SpecimenData.DiaInMembrane[2] = SpecimenData.DiaInMembrane[1];
	//SpecimenData.DiaOutMembrane[2] = SpecimenData.DiaOutMembrane[1];
	//SpecimenData.HeightInMembrane[2] = SpecimenData.HeightInMembrane[1];
	//SpecimenData.HeightOutMembrane[2] = SpecimenData.HeightOutMembrane[1];
	BeConsol_ez = 1 - height / SpecimenData.Height[1];
	BeConsol_ev = BeConsol_ez * 3;  // assume isotropic deformation
	SpecimenData.Volume[2] = SpecimenData.Volume[1] * (1 - BeConsol_ev);
	SpecimenData.DiameterIn[2] = SpecimenData.DiameterIn[1] * sqrt((1 - BeConsol_ev) / (1 - BeConsol_ez));
	SpecimenData.DiameterOut[2] = SpecimenData.DiameterOut[1] * sqrt((1 - BeConsol_ev) / (1 - BeConsol_ez));
	SpecimenData.DiaInMembrane[2] = SpecimenData.DiameterIn[2] - SpecimenData.MembraneThickness / 2.0;
	SpecimenData.DiaOutMembrane[2] = SpecimenData.DiameterOut[2] + SpecimenData.MembraneThickness / 2.0;
	SpecimenData.HeightInMembrane[2] = height;
	SpecimenData.HeightOutMembrane[2] = height;
	
	//---Initialize Displacement transducer---
	Cal_c[5] -= Phyout[5]; // initialize ez
	//Cal_c[18]=Cal_c[18]-Phyout[18];
	Cal_c[13] -= Phyout[13]; // initialize ev
	Load();
	OnBUTTONToPresent2();
}

void CSpecimen::OnBUTTONAfConsolidation() 
{
	// TODO: Add your control notification handler code here
	//@note Hashimoto modified 2022/12/22
	SpecimenData.Height[3]=height;
	SpecimenData.Volume[3]=volume;
	SpecimenData.DiameterIn[3]=diameter_in;
	SpecimenData.DiameterOut[3]=diameter_out;
	//SpecimenData.DiaInMembrane[3] = SpecimenData.DiaInMembrane[2];
	//SpecimenData.DiaOutMembrane[3] = SpecimenData.DiaOutMembrane[2];
	//SpecimenData.HeightInMembrane[3] = SpecimenData.HeightInMembrane[2];
	//SpecimenData.HeightOutMembrane[3] = SpecimenData.HeightOutMembrane[2];
	SpecimenData.DiaInMembrane[3] = diameter_in - SpecimenData.MembraneThickness / 2.0;
	SpecimenData.DiaOutMembrane[3] = diameter_out + SpecimenData.MembraneThickness / 2.0;
	SpecimenData.HeightInMembrane[3] = height;
	SpecimenData.HeightOutMembrane[3] = height;

	//---Initialize Displacement transducer---
	Cal_c[5] -= Phyout[5]; // initialize ez
	//Cal_c[18]=Cal_c[18]-Phyout[18];
	Cal_c[13] -= Phyout[13]; // initialize ev
	Load();
	OnBUTTONToPresent3();
}

void CSpecimen::OnBUTTONToPresent1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONUpdate();
	SpecimenData.DiameterIn[0] = SpecimenData.DiameterIn[1];
	SpecimenData.DiameterOut[0] = SpecimenData.DiameterOut[1];
	SpecimenData.Height[0] = SpecimenData.Height[1];
	SpecimenData.Volume[0] = SpecimenData.Volume[1];
	SpecimenData.DiaInMembrane[0] = SpecimenData.DiaInMembrane[1];
	SpecimenData.DiaOutMembrane[0] = SpecimenData.DiaOutMembrane[1];
	SpecimenData.HeightInMembrane[0] = SpecimenData.HeightInMembrane[1];
	SpecimenData.HeightOutMembrane[0] = SpecimenData.HeightOutMembrane[1];
	Load();
}

void CSpecimen::OnBUTTONToPresent2() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONUpdate();
	SpecimenData.DiameterIn[0] = SpecimenData.DiameterIn[2];
	SpecimenData.DiameterOut[0] = SpecimenData.DiameterOut[2];
	SpecimenData.Height[0] = SpecimenData.Height[2];
	SpecimenData.Volume[0] = SpecimenData.Volume[2];
	SpecimenData.DiaInMembrane[0] = SpecimenData.DiaInMembrane[2];
	SpecimenData.DiaOutMembrane[0] = SpecimenData.DiaOutMembrane[2];
	SpecimenData.HeightInMembrane[0] = SpecimenData.HeightInMembrane[2];
	SpecimenData.HeightOutMembrane[0] = SpecimenData.HeightOutMembrane[2];
	Load();
}

void CSpecimen::OnBUTTONToPresent3() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnBUTTONUpdate();
	SpecimenData.DiameterIn[0] = SpecimenData.DiameterIn[3];
	SpecimenData.DiameterOut[0] = SpecimenData.DiameterOut[3];
	SpecimenData.Height[0] = SpecimenData.Height[3];
	SpecimenData.Volume[0] = SpecimenData.Volume[3];
	SpecimenData.DiaInMembrane[0] = SpecimenData.DiaInMembrane[3];
	SpecimenData.DiaOutMembrane[0] = SpecimenData.DiaOutMembrane[3];
	SpecimenData.HeightInMembrane[0] = SpecimenData.HeightInMembrane[3];
	SpecimenData.HeightOutMembrane[0] = SpecimenData.HeightOutMembrane[3];
	Load();
}


