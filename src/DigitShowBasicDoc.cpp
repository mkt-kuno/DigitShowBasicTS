// DigitShowBasicDoc.cpp : CDigitShowBasicDoc �N���X�̓���̒�`���s���܂��B
//

#include	"stdafx.h"
#include	"DigitShowBasic.h"
#include	"DigitShowBasicDoc.h"
#include	"CAIO.H"
#include	"dataconvert.h"

#include	"time.h"
#include	"math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDigitShowBasicDoc

//---A/D---
	long		Ret,Ret2;
	int			NUMAD,NUMDA;						// The Number of A/D and D/A boards
	short		AdId[2],DaId[1];					// ID No. of A/D and D/A boards
	short		AdChannels[2],DaChannels[1];		// The Number of Channel
	short		AdRange[2],DaRange[1];				// Range of A/D and D/A boards
	float		AdRangeMax[2], AdRangeMin[2];		// Maximum and Minimum in the range of A/D
	float		DaRangeMax[1], DaRangeMin[1];		// Maximum and Minimum in the range of D/A
	short		AdResolution[2],DaResolution[1];	// Resolution of A/D and D/A Boards
	short		AdInputMethod[2];					// Input Method of A/D
	long		DaData[262144];
	long		AdData0[16777216],AdData1[16777216];
	int			AdMaxCH;
	short		AdMemoryType[2];
	float		AdScanClock[2];
	float		AdSamplingClock[2];
	long		AdSamplingTimes[2];
	long		AdEvent;
	float		SavingClock;
	int			SavingTime;
	long		TotalSamplingTimes;
	long		CurrentSamplingTimes;
	float		AllocatedMemory;
	int			AvSmplNum;

	char		ErrorString[256];
	CString		TextString;

	PVOID		pSmplData0,pSmplData1;			// Source of binary data
	HANDLE		hHeap0,hHeap1;					// Handle to make the source area

//---Array---
	CString		NameV[32], NameP[32], NameDV[8];// Name of Channles
	float		Vout[32],Vtmp;					// Output Voltage from A/D board
	double		Phyout[32],Ptmp;				// Physical Value Calcurated from Vout
	double		CalParam[32];					// The others of the above to display
	double		Cal_a[32],Cal_b[32],Cal_c[32];	// Calibration Factor
	float		DAVout[16];						// Output Voltage to D/A board
	double		DA_Cal_a[16],DA_Cal_b[16];		// D/A Calibration Factor

//---Physical Value---
	double		rotation1,rotation2;							// [rad]
	double		BW1,BW2;										// Balance Weight	
	double		height,area,volume,diameter_in,diameter_out;	// Current specimen size
	double		diameterInM,diameterOutM,heightInM,heightOutM;	// Current membrane size
	double		cell_in,cell_out;
	double		sz,sr,sq,szq,p,q;									// Current stress and pressure
	double		ez,er,eq,gzq1,gzq2,ev;								// Current strain
	double		ezInM,ezOutM,eqInM,eqOutM,gzqInM,gzqOutM;		// Current membrane strain
	double		PressureInM,PressureOutM,ForceM,TorqueM;		// Current membrane pressure

//---Flag---
	bool		Flag_SetBoard;
	bool		Flag_SaveData;
	bool		Flag_FIFO;
	bool		Flag_Cyclic;

//---SpecimenData---
	Specimen	SpecimenData;						// Structure of Specimen Data
		
//---Control---	
	int         CH_EP_Cell;				// D/A Channel of EP (Cell Pressure)
	int			CH_AxisMotor;			// 0V:On, 5V:Off
	int			CH_AxisClutch;			// 
	int			CH_AxisSpeed;			//
	int			CH_TorsionMotor;		// 0V:On, 5V:Off
	int			CH_TorsionClutch;		// 
	int			CH_TorsionSpeed;		//
	float		VoltUp,VoltDown;		//
	float		VoltCW,VoltCCW;			//

	int			Control_ID;
	Control		ControlData[16];					// Structure of Control Data
	double		ErrorStressMotor,ErrorStressAir;	// Sencitivity of Stress Control
	double		ErrorStrainEz,ErrorStrainGzq;		// Sencitivity of Strain Control
	double		Target_sz,Target_sr,Target_tzq;
	double		Target_ez,Target_gzq;
	int			Num_Cyclic,Num_SmallCyclic;
	double		StepTime;

//---Control File---
	int			CURNUM;
	int			CFNUM[256];
	double		CFPARA[256][16];

//---Time---
	CTime		StartTime, NowTime;
	CTimeSpan	SpanTime;
	CString		SNowTime;
	long		SequentTime1;
	double		SequentTime2;
	double		CtrlStepTime;

	unsigned int	TimeInterval_1;	// Time interval (ms) to display output data.		
	unsigned int	TimeInterval_2;	// Time interval (ms) to control.		
	unsigned int	TimeInterval_3;	// Time interval (ms) to save the data.

//---File---
	FILE        *FileSaveData0;						// File to save the voltage value
	FILE		*FileSaveData1;						// File to save the physical value
	FILE		*FileSaveData2;						// File to save the parameter value

//---Rs232c Class---
	HANDLE		hComm[2];
	DCB			CommDCB[2];
	CString		CommName[2]={"COM1","COM2"};
	bool		Flag_COM[2];
	COMSTAT		Comstat1,Comstat2;
	CString		ReadBuffer1,ReadBuffer2;
	CString		WriteBuffer1,WriteBuffer2;
	CString		TmpBuffer;
	HANDLE		hEvent;
	bool		Flag_SetRs232c;
	bool		Flag_SetBalance;

    // 2021.12.07 Edited by M.Kuno
    int			StepDisplay;

IMPLEMENT_DYNCREATE(CDigitShowBasicDoc, CDocument)

BEGIN_MESSAGE_MAP(CDigitShowBasicDoc, CDocument)
	//{{AFX_MSG_MAP(CDigitShowBasicDoc)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDigitShowBasicDoc �N���X�̍\�z/����

CDigitShowBasicDoc::CDigitShowBasicDoc()
{
	// TODO: ���̈ʒu�ɂP�x�����Ă΂��\�z�p�̃R�[�h��ǉ����Ă��������B
	// Initialize of data
	int	i,j;
	Flag_SetBoard=FALSE;
	Flag_SaveData=FALSE;
	Flag_FIFO=FALSE;
	NUMAD=1;		// The Number of A/D Board ( NUMAD=0-2 )
	NUMDA=1;		// The Number of D/A Board ( NUMDA=0-1 )

//  @note Hashimoto modified 2022.2.28
	NameV[0]=_T("V.Load");		NameP[0]=_T("V.Load,N");
	NameV[1]=_T("T.Load ");		NameP[1]=_T("Torque,Ncm");
	NameV[2]=_T("POT1");		NameP[2]=_T("POT1,rad");
	NameV[3]=_T("POT2");		NameP[3]=_T("POT2,rad");
	NameV[4]=_T("HCDPT");		NameP[4]=_T("EffectiveStress,kPa");
	NameV[5]=_T("ExtLVDT");		NameP[5]=_T("V.DispEXT,mm");
	NameV[6]=_T("LDT1");	    NameP[6]=_T("LDT1,mm");
	NameV[7]=_T("CH7");			NameP[7]=_T("CH7");
	NameV[8]=_T("CG1");			NameP[8]=_T("CG1,mm");
	NameV[9]=_T("CG2");		NameP[9]=_T("CG2,mm");
	NameV[10]=_T("CG3");		NameP[10]=_T("CG3,mm");
	NameV[11]=_T("LDT2");	NameP[11]=_T("LDT2,mm");
	NameV[12]=_T("CH12");		NameP[12]=_T("CH12");
	NameV[13]=_T("LCDPT");		NameP[13]=_T("DeltaVol.,mm3");
	NameV[14]=_T("CH14");		NameP[14]=_T("CH14");
	NameV[15]=_T("CH15");		NameP[15]=_T("CH15");
	NameV[16]=_T("CH16");		NameP[16]=_T("CH16");
	NameV[17]=_T("CH17");		NameP[17]=_T("CH17");
	NameV[18]=_T("CH18");		NameP[18]=_T("CH18");
	NameV[19]=_T("CH19");		NameP[19]=_T("CH19");
	NameV[20]=_T("CH20");		NameP[20]=_T("CH20");
	NameV[21]=_T("CH21");		NameP[21]=_T("CH21");
	NameV[22]=_T("CH22");		NameP[22]=_T("CH22");
	NameV[23]=_T("CH23");		NameP[23]=_T("CH23");
	NameV[24]=_T("CH24");		NameP[24]=_T("CH24");
	NameV[25]=_T("CH25");		NameP[25]=_T("CH25");
	NameV[26]=_T("CH26");		NameP[26]=_T("CH26");
	NameV[27]=_T("CH27");		NameP[27]=_T("CH27");
	NameV[28]=_T("CH28");		NameP[28]=_T("CH28");
	NameV[29]=_T("CH29");		NameP[29]=_T("CH29");
	NameV[30]=_T("CH30");		NameP[30]=_T("CH30");
	NameV[31]=_T("CH31");		NameP[31]=_T("CH31");
//
	for(i=0;i<32;i++){
		Vout[i]=0.0;	
		Phyout[i]=0.0;		CalParam[i]=0.0;
		Cal_a[i]=0.0;		Cal_b[i]=1.0;			Cal_c[i]=0.0;
	}
	for(i=0;i<16;i++){
		DAVout[i]=0.0;		DA_Cal_a[i]=0.0;	DA_Cal_b[i]=0.0;
	}
	rotation1=0.0;		rotation2=0.0;
	BW1=0.0;			BW2=0.0;
	Control_ID=0;
	SequentTime1=0;
	TimeInterval_1=200;
	TimeInterval_2=500;
	TimeInterval_3=1000;
	for(j=0;j<4;j++){
		SpecimenData.DiameterIn[j]=60.0;
		SpecimenData.DiameterOut[j]=100.0;
		SpecimenData.Height[j]=150.0;
		SpecimenData.Volume[j]=3.141592*(100.0*100.0-60.0*60.0)/4*150.0;
		SpecimenData.DiaInMembrane[j]=60.0;
		SpecimenData.DiaOutMembrane[j]=100.0;
		SpecimenData.HeightInMembrane[j]=150.0;
		SpecimenData.HeightOutMembrane[j]=150.0;
	}
	SpecimenData.MembraneModulus=1400.0;
	SpecimenData.MembraneThickness=0.3;
	//SpecimenData.RDiaInM=60.0;
	//SpecimenData.RDiaOutM=100.0;
	SpecimenData.RDiaInM = 59.85; //@note Hashimoto fixed 2022.12.22
	SpecimenData.RDiaOutM = 100.15; //@note Hashimoto fixed 2022.12.22
	SpecimenData.RHeightInM=150.0; //@note Hashimoto fixed 2022.12.22
	SpecimenData.RHeightOutM=150.0; //@note Hashimoto fixed 2022.12.22
	SpecimenData.RodArea=0.0;
	SpecimenData.CapWeight=0.0;
//
	for(i=0;i<16;i++){
		for(j=0;j<3;j++){
			ControlData[i].flag[j]=FALSE;
			ControlData[i].time[j]=0;
			ControlData[i].p[j]=0.0;
			ControlData[i].q[j]=0.0;
			ControlData[i].u[j]=0.0;
			ControlData[i].sigma[j]=0.0;
			ControlData[i].sigmaRate[j]=0.0;
			ControlData[i].sigmaAmp[j]=0.0;	
			ControlData[i].strain[j]=0.0;
			ControlData[i].strainRate[j]=0.0;
			ControlData[i].strainAmp[j]=0.0;
		}
		ControlData[i].K0=1.0;
	}
	ControlData[1].q[0]=1.0;
	ControlData[1].AxisSpeed = 100.0;
//
	Target_sz = 0.0;
	Target_sr = 0.0;
	Target_tzq = 0.0;
	Target_ez = 0.0;
	Target_gzq = 0.0;
	Num_Cyclic=0;	Num_SmallCyclic=0;
	StepTime=0.0;
//
	CURNUM=0;
	for(i=0;i<256;i++){
		CFNUM[i]=0;
		for(j=0;j<16;j++){
			CFPARA[i][j]=0.0;
		}
	}
//
	ErrorStressMotor= 0.5;				// (kPa)
	ErrorStressAir  = 0.5;				// (kPa)
	ErrorStrainEz   = 0.0005;			// (---)
	ErrorStrainGzq  = 0.0005;			// (---)
//
	NameDV[0]=_T("CH00: EP cell pressure");
	NameDV[1]=_T("CH01: Axial Motor");
	NameDV[2]=_T("CH02: Axial Clutch");
	NameDV[3]=_T("CH03: Axial Motor Speed");
	NameDV[4]=_T("CH04: Torsional Motor");
	NameDV[5]=_T("CH05: Torsional Clutch");
	NameDV[6]=_T("CH06: Torsional Motor Speed");
	CH_EP_Cell		= 0;				// D/A Channel of EP (Cell Pressure)
	CH_AxisMotor	= 1;				// 0V:On, 5V:Off
	CH_AxisClutch	= 2;				// 
	CH_AxisSpeed	= 3;				//
	CH_TorsionMotor	= 4;				// 0V:On, 5V:Off
	CH_TorsionClutch= 5;				// 
	CH_TorsionSpeed	= 6;				//
	VoltDown = 0.0f;
	VoltUp   = 5.0f;	
	VoltCW   = 0.0f;
	VoltCCW  = 5.0f;
	DA_Cal_a[CH_AxisSpeed]=0.0033333;	// D/A Calibration Factor, Axial Motor Speed (V/RPM)
	DA_Cal_b[CH_AxisSpeed]=0.0;			// D/A Calibration Factor, Axial Motor Speed (V) 
	DA_Cal_a[CH_TorsionSpeed]=0.0034483;// D/A Calibration Factor, Torsion Motor Speed (V/RPM)
	DA_Cal_b[CH_TorsionSpeed]=0.0;		// D/A Calibration Factor, Torsion Motor Speed (V) 
	DA_Cal_a[CH_EP_Cell]=0.0175;		// D/A Calibration Factor, EP of Cell Pressure (V/kPa)
	DA_Cal_b[CH_EP_Cell]=0.0;			// D/A Calibration Factor, EP of Cell Pressure (V)
//
	Flag_SetRs232c = FALSE;
	Flag_SetBalance= FALSE;

	// 2021.12.07 Edited by M.Kuno
	StepDisplay = 0;
}

CDigitShowBasicDoc::~CDigitShowBasicDoc()
{
}

BOOL CDigitShowBasicDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���̈ʒu�ɍď�����������ǉ����Ă��������B
	// (SDI �h�L�������g�͂��̃h�L�������g���ė��p���܂��B)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDigitShowBasicDoc �V���A���C�[�[�V����

void CDigitShowBasicDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���̈ʒu�ɕۑ��p�̃R�[�h��ǉ����Ă��������B
	}
	else
	{
		// TODO: ���̈ʒu�ɓǂݍ��ݗp�̃R�[�h��ǉ����Ă��������B
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDigitShowBasicDoc �N���X�̐f�f

#ifdef _DEBUG
void CDigitShowBasicDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDigitShowBasicDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDigitShowBasicDoc �R�}���h
void CDigitShowBasicDoc::OpenBoard()
{
	int	i;
	if( Flag_SetBoard ){
		AfxMessageBox("Initialization has been already accomplished", MB_ICONSTOP | MB_OK );
		return;
	}
	else{
		// OPEN A/D BOARDS.
		if(NUMAD > 0 ){
			Ret = AioInit ( "AIO000" , &AdId[0] );
		    if(Ret != 0){
			    Ret2 = AioGetErrorString(Ret, ErrorString);
				TextString.Format("AioInit = %d : %s", Ret, ErrorString);
				AfxMessageBox(TextString, MB_ICONSTOP | MB_OK );
				return;
			}
			else{
				Ret = AioResetDevice(AdId[0]);
			    if(Ret != 0){
				    Ret2 = AioGetErrorString(Ret, ErrorString);
					TextString.Format("AioResetDevice = %d : %s", Ret, ErrorString);
					AfxMessageBox(TextString, MB_ICONSTOP | MB_OK );
					return;
				}
			}
		}
		if(NUMAD > 1 ){
			Ret = AioInit ( "AIO000" , &AdId[1] );
		    if(Ret != 0){
				Ret2 = AioGetErrorString(Ret, ErrorString);
				TextString.Format("AioInit = %d : %s", Ret, ErrorString);
				AfxMessageBox(TextString, MB_ICONSTOP | MB_OK );
				return;
			}
			else{
				Ret = AioResetDevice(AdId[1]);
			    if(Ret != 0){
					Ret2 = AioGetErrorString(Ret, ErrorString);
					TextString.Format("AioResetDevice = %d : %s", Ret, ErrorString);
					AfxMessageBox(TextString, MB_ICONSTOP | MB_OK );
					return;
				}
			}
		}
		// OPEN D/A BOARDS.
		if(NUMDA > 0){
			Ret = AioInit ( "AIO001" , &DaId[0] );
		    if(Ret != 0){
			    Ret2 = AioGetErrorString(Ret, ErrorString);
				TextString.Format("AioInit = %d : %s", Ret, ErrorString);
				AfxMessageBox(TextString, MB_ICONSTOP | MB_OK );
				return;
			}
			else{
				Ret = AioResetDevice(DaId[0]);
			    if(Ret != 0){
				    Ret2 = AioGetErrorString(Ret, ErrorString);
					TextString.Format("AioResetDevice = %d : %s", Ret, ErrorString);
					AfxMessageBox(TextString, MB_ICONSTOP | MB_OK );
					return;
				}
			}
		}
		// Set Sampling Condition
		AdMaxCH=0;
		for(i=0;i<NUMAD;i++){
			Ret = AioGetAiInputMethod ( AdId[i] , &AdInputMethod[i] );
			Ret = AioGetAiResolution ( AdId[i] , &AdResolution[i] );
			Ret = AioGetAiMaxChannels ( AdId[i] , &AdChannels[i] );
			Ret = AioSetAiChannels ( AdId[i] , AdChannels[i] );
			Ret = AioGetAiChannels ( AdId[i] , &AdChannels[i] );
			AdMaxCH=AdMaxCH+AdChannels[i];
//			Ret = AioSetAiRangeAll ( AdId[i], 1 );	// (-5V, 5V)
			Ret = AioSetAiRangeAll ( AdId[i], 0 );	// (-10V, 10V)
			Ret = AioGetAiRange ( AdId[i] , 0 , &AdRange[i] );
			Ret = GetRangeValue(AdRange[i], &AdRangeMax[i], &AdRangeMin[i]);
			Ret = AioGetAiMemoryType ( AdId[i] , &AdMemoryType[i] );
			Ret = AioGetAiScanClock ( AdId[i] , &AdScanClock[i] );
			Ret = AioGetAiSamplingClock ( AdId[i] , &AdSamplingClock[i] );
			Ret = AioGetAiEventSamplingTimes ( AdId[i] , &AdSamplingTimes[i] );
		}
		SavingTime=300;
		TotalSamplingTimes=long(SavingTime*1000000/AdSamplingClock[0]);
		AllocatedMemory=4*AdMaxCH*TotalSamplingTimes/1024.0f/1024.0f;
		AvSmplNum=10;
		for(i=0;i<NUMDA;i++){
			Ret = AioGetAoResolution ( DaId[i] , &DaResolution[i] );
			Ret = AioGetAoMaxChannels ( DaId[i] , &DaChannels[i] );
//			Ret = AioSetAoRangeAll ( DaId[i] , 50 );	// 0 - 10V
			Ret = AioGetAoRange ( DaId[i] , 0 , &DaRange[i] );
			Ret = GetRangeValue(DaRange[i], &DaRangeMax[i], &DaRangeMin[i]);
		}
		Flag_SetBoard=TRUE;
	}
	return;}

void CDigitShowBasicDoc::CloseBoard()
{
	// Close A/D and D/A board to end the application 
	if(Flag_SetBoard){
		if(NUMAD > 0)	Ret = AioExit(AdId[0]);
		if(Ret != 0){
		    Ret2 = AioGetErrorString(Ret, ErrorString);
			TextString.Format("AioExit = %d : %s", Ret, ErrorString);
			AfxMessageBox(TextString, MB_ICONSTOP | MB_OK );
			return;	
		}
		if(NUMAD > 1)	Ret = AioExit(AdId[1]);
		if(Ret != 0){
		    Ret2 = AioGetErrorString(Ret, ErrorString);
			TextString.Format("AioExit = %d : %s", Ret, ErrorString);
			AfxMessageBox(TextString, MB_ICONSTOP | MB_OK );
			return;	
		}
		if(NUMDA > 0)	Ret = AioExit(DaId[0]);
		if(Ret != 0){
		    Ret2 = AioGetErrorString(Ret, ErrorString);
			TextString.Format("AioExit = %d : %s", Ret, ErrorString);
			AfxMessageBox(TextString, MB_ICONSTOP | MB_OK );
			return;	
		}
	}
}

//--- Input from A/D Board ---
void CDigitShowBasicDoc::AD_INPUT()
{
	int	i,j,k;
	k=0;
	if(NUMAD>0){
		for(i=0;i<AdChannels[0];i++){
			Vout[k]=0.0f;
			for(j=0;j<AvSmplNum;j++){
				Vout[k] = Vout[k]+BinaryToVolt(AdRangeMax[0], AdRangeMin[0], AdResolution[0], AdData0[AdChannels[0]*j+i])/float(AvSmplNum);
			}
			k=k+1;
		}
	}
	if(NUMAD>1){
		for(i=0;i<AdChannels[1];i++){
			Vout[k]=0.0f;
			for(j=0;j<AvSmplNum;j++){
				Vout[k] = Vout[k]+BinaryToVolt(AdRangeMax[1], AdRangeMin[1], AdResolution[1], AdData1[AdChannels[1]*j+i])/float(AvSmplNum);
			}
			k=k+1;
		}
	}
}
//--- Output to D/A Board ---
void CDigitShowBasicDoc::DA_OUTPUT()
{
	int	i,j,k;
	k=0;
	for(i=0;i<NUMDA;i++){
		for(j=0;j<DaChannels[i];j++){
			if(DAVout[k]>9.999f) DAVout[k]=9.999f;
			if(DAVout[k]<0.0f) DAVout[k]=0.0f;
			DaData[j] = VoltToBinary(DaRangeMax[i], DaRangeMin[i], DaResolution[i], DAVout[k]);
			k=k+1;
		}
		Ret = AioMultiAo(DaId[i], DaChannels[i], &DaData[0]);
	}
}
//--- Calcuration of Physical Value ---
void CDigitShowBasicDoc::Cal_Physical()
{
	int	i;
	for(i=0;i<32;i++){
		Phyout[i]=	Cal_a[i]*Vout[i]*Vout[i] + Cal_b[i]*Vout[i] + Cal_c[i];
	}
}

//--- Calcuration of the Other Parameters ---
void CDigitShowBasicDoc::Cal_Param()
{
 	//---Calculation of Parameter Data--- 
	//Current specimen size
	if(Flag_SetBalance == FALSE) BW2 = Phyout[13];	// Volume change from LCDPT
	height=SpecimenData.Height[0]-Phyout[5];
	volume=SpecimenData.Volume[0]-BW2;
	area=volume/height;
	rotation1=Phyout[2];
	rotation2=Phyout[3];
	diameter_in=SpecimenData.DiameterIn[0]*sqrt((1-BW2/SpecimenData.Volume[0])/(1-Phyout[5]/SpecimenData.Height[0]));
	diameter_out=SpecimenData.DiameterOut[0]*sqrt((1-BW2/SpecimenData.Volume[0])/(1-Phyout[5]/SpecimenData.Height[0]));
	//diameterInM=diameter_in+SpecimenData.MembraneThickness/2.0; //@note Hashimoto fixed 2022.12.22
	diameterInM = diameter_in - SpecimenData.MembraneThickness / 2.0;
	diameterOutM=diameter_out+SpecimenData.MembraneThickness/2.0;
	heightInM=SpecimenData.HeightInMembrane[0]-Phyout[5];
	heightOutM=SpecimenData.HeightOutMembrane[0]-Phyout[5];
	//Strain in specimen
	ez=Phyout[5]/SpecimenData.Height[0];
	er=-((diameter_out-SpecimenData.DiameterOut[0])-(diameter_in-SpecimenData.DiameterIn[0]))/(diameter_out-diameter_in);
	eq=-((diameter_out-SpecimenData.DiameterOut[0])+(diameter_in-SpecimenData.DiameterIn[0]))/(diameter_out+diameter_in);
	gzq1=rotation1*(pow(diameter_out,3.0)-pow(diameter_in, 3.0))/3.0/height/(pow(diameter_out, 2.0)-pow(diameter_in, 2.0));	
	gzq2=rotation2*(pow(diameter_out,3.0)-pow(diameter_in, 3.0))/3.0/height/(pow(diameter_out, 2.0)-pow(diameter_in, 2.0));
	ev=BW2/SpecimenData.Volume[0];
	// Strain in membrane sleeve
	ezInM=(SpecimenData.RHeightInM-heightInM)/SpecimenData.RHeightInM;
	ezOutM=(SpecimenData.RHeightOutM-heightOutM)/SpecimenData.RHeightOutM;
	eqInM=(SpecimenData.RDiaInM-diameterInM)/SpecimenData.RDiaInM;
	eqOutM=(SpecimenData.RDiaOutM-diameterOutM)/SpecimenData.RDiaOutM;
	//gzqInM=diameter_in*rotation1/SpecimenData.RHeightInM;
	//gzqOutM=diameter_out*rotation1/SpecimenData.RHeightOutM;
	gzqInM = diameterInM / 2.0 * rotation1 / SpecimenData.RHeightInM; //@note Hashimoto modified 2022.2.28
	gzqOutM = diameterOutM / 2.0 * rotation1 / SpecimenData.RHeightOutM; //@note Hashimoto modified 2022.2.28
	//Membrane force 
	//@note Hashimoto modified 2022.12.28 (only considering TorqueM)
	//PressureInM=4.0/3.0*SpecimenData.MembraneModulus*SpecimenData.MembraneThickness*(ezInM+2.0*eqInM)/diameter_in;
	//PressureOutM=-4.0/3.0*SpecimenData.MembraneModulus*SpecimenData.MembraneThickness*(ezOutM+2.0*eqOutM)/diameter_out;
	//ForceM=-2.0/3.0*3.141592*SpecimenData.MembraneModulus*SpecimenData.MembraneThickness*(diameter_in*(2.0*ezInM+eqInM)+diameter_out*(2.0*ezOutM+eqOutM))/1000.0;
	TorqueM=-1.0/6.0*3.141592*SpecimenData.MembraneModulus*SpecimenData.MembraneThickness*(pow(diameter_in, 2.0)*gzqInM+pow(diameter_out, 2.0)*gzqOutM)/1000000.0;
	PressureInM = 0.0;
	PressureOutM = 0.0;
	ForceM = 0.0;

	// Adjusted Force and Pressure
	Phyout[0]=Phyout[0]+ForceM+SpecimenData.CapWeight;
	Phyout[1]=Phyout[1]+TorqueM*100.0;
	cell_out=Phyout[4]+PressureOutM;
	cell_in=Phyout[4]+PressureInM;
	//Stress
	sz=(Phyout[0]+3.141592/4.0*(cell_out*pow(diameter_out, 2.0)-cell_in*pow(diameter_in, 2.0))/1000.0)/area*1000.0;
	sr=(cell_out*diameter_out+cell_in*diameter_in)/(diameter_out+diameter_in);
	sq=(cell_out*diameter_out-cell_in*diameter_in)/(diameter_out-diameter_in);
	szq=4.0*(Phyout[1]/100.0)/3.141592*(3.0/2.0/(pow(diameter_out, 3.0)-pow(diameter_in, 3.0))+1.0/(pow(diameter_out, 2.0)+pow(diameter_in, 2.0))/(diameter_out-diameter_in))*1000000.0;
	p=(sz+sr+sq)/3.0;
	q=sz-sr;
	//---The Value to display---
	CalParam[0]=sz;
	CalParam[1]=sr;
	CalParam[2]=sq;
	CalParam[3]=szq;
	CalParam[4]=ev*100.0;
	CalParam[5]=ez*100.0;
	CalParam[6]=Phyout[6]; // LDT1
	CalParam[7]=Phyout[11]; // LDT2
	CalParam[8]=Phyout[8]; // CG1
	CalParam[9]=Phyout[9]; // CG2
	CalParam[10]=Phyout[10]; // CG3
	CalParam[11] = p;
	CalParam[12] = q;
	CalParam[13] = (sz + sq) / 2.0 + sqrt((sz - sq) * (sz - sq) / 4 + szq * szq); // sigma 1
	CalParam[14] = sr; // sigma 2
	CalParam[15] = (sz + sq) / 2.0 - sqrt((sz - sq) * (sz - sq) / 4 + szq * szq); // sigma 3
	CalParam[16] = gzq1 * 100.0;
	CalParam[17] = gzq2 * 100.0;
	//CalParam[9]=gzq1*100.0;
	//CalParam[10]=gzq2*100.0;
	//CalParam[11]=Phyout[10];
	//CalParam[12]=p;
	//CalParam[13]=q;
	//CalParam[14]=(sz+sq)/2.0+sqrt((sz-sq)*(sz-sq)/4+szq*szq);
	//CalParam[15]=sr;
	//CalParam[16]=(sz+sq)/2.0-sqrt((sz-sq)*(sz-sq)/4+szq*szq);
	//CalParam[17]=atan2(szq,(sz-sq)/2.0);
	//CalParam[17] = 0.5 * atan2(szq, (sz - sq) / 2.0);  //@note Hashimoto modified 2022.12.22
	CalParam[18]=cell_in;
	CalParam[19]=cell_out;
	CalParam[20]=diameter_in;
	CalParam[21]=diameter_out;
	//CalParam[22]=Phyout[9];
	//CalParam[23]=Phyout[12];
	CalParam[22] = height;
	CalParam[23] = volume;

	// 2021.12.07 Edited by M.Kuno
	StepDisplay = CURNUM;
}
//--- Save the data to File ---
void CDigitShowBasicDoc::SaveToFile()
{
	// Save Voltage and Physical Data
	int	i,j,k;
	k=0;
	fprintf(FileSaveData0,"%.3lf	",SequentTime2);
	fprintf(FileSaveData1,"%.3lf	",SequentTime2);
	for(i=0;i<NUMAD;i++){
		for(j=0;j<AdChannels[i];j++){
			fprintf(FileSaveData0,"%lf	",Vout[k]);
			fprintf(FileSaveData1,"%lf	",Phyout[k]);
			k=k+1;
		}
	}
	fprintf(FileSaveData0,"\n");
	fprintf(FileSaveData1,"\n");
	// Save Parameter Data
	fprintf(FileSaveData2,"%.3lf	",SequentTime2);	
	for(i=0;i<24;i++){
		fprintf(FileSaveData2,"%lf	",CalParam[i]);
	}
	// 2021.12.07 Edited by M.Kuno
	fprintf(FileSaveData2, "%d	", StepDisplay);
	fprintf(FileSaveData2, "%d	", Num_Cyclic);
	fprintf(FileSaveData2,"\n");
}

void CDigitShowBasicDoc::SaveToFile2()
{
	int	i,j,k;
	for(i=0;i<CurrentSamplingTimes;i++){
		k=0;
		fprintf(FileSaveData0,"%.3lf	",SavingClock/1000000.0*i);
		fprintf(FileSaveData1,"%.3lf	",SavingClock/1000000.0*i);
		if(NUMAD>0){
			for(j=0;j<AdChannels[0];j++){
				Vtmp = BinaryToVolt(AdRangeMax[0], AdRangeMin[0], AdResolution[0], *((PLONG)pSmplData0+i*AdChannels[0]+j));
				Ptmp = Cal_a[k]*Vtmp*Vtmp+Cal_b[k]*Vtmp+Cal_c[k];
				k=k+1;
				fprintf(FileSaveData0,"%lf	",Vtmp);
				fprintf(FileSaveData1,"%lf	",Ptmp);
			}
		}
		if(NUMAD>1){
			for(j=0;j<AdChannels[1];j++){
				Vtmp = BinaryToVolt(AdRangeMax[1], AdRangeMin[1], AdResolution[1], *((PLONG)pSmplData1+i*AdChannels[1]+j));
				Ptmp = Cal_a[k]*Vtmp*Vtmp+Cal_b[k]*Vtmp+Cal_c[k];
				k=k+1;
				fprintf(FileSaveData0,"%lf	",Vtmp);
				fprintf(FileSaveData1,"%lf	",Ptmp);
			}
		}
		fprintf(FileSaveData0,"\n");
		fprintf(FileSaveData1,"\n");
	}
}

void CDigitShowBasicDoc::Allocate_Memory()
{
	if(Flag_SaveData){
		if(NUMAD>0){
			hHeap0 = GetProcessHeap();
			pSmplData0 = HeapAlloc(hHeap0,HEAP_ZERO_MEMORY,unsigned long(TotalSamplingTimes*AdChannels[0]*sizeof(LONG)));
		}
		if(NUMAD>1){
			hHeap1 = GetProcessHeap();
			pSmplData1 = HeapAlloc(hHeap1,HEAP_ZERO_MEMORY,unsigned long(TotalSamplingTimes*AdChannels[1]*sizeof(LONG)));
		}
	}
	else{
		if(NUMAD>0)	HeapFree(hHeap0,0,pSmplData0);
		if(NUMAD>1)	HeapFree(hHeap1,0,pSmplData1);
	}
}

//--- Control Statements ---
void CDigitShowBasicDoc::Control_DA()
{
	switch (Control_ID)
	{
	case 0:
		{ 
		}
		break;
	case 1:
		{ 
			// Pre-Consolidation Process
			// ControlData[1].AxisSpeed:	Maximum Speed
			// ControlData[1].q:			Deviator stress when the motor speed become the max. value;
			// ControlData[1].sigma[1]:		Target of Cell Pressure
			// ControlData[1].sigmaRate[1]: Increment Rate of Cell Pressure 
			if( ControlData[1].sigma[1] > 0.0 && ControlData[1].sigmaRate[1] > 0.0 ){
				if(sr <= ControlData[1].sigma[1]-ErrorStressAir)		DAVout[CH_EP_Cell]=DAVout[CH_EP_Cell]+float(DA_Cal_a[CH_EP_Cell]*ControlData[1].sigmaRate[1]*TimeInterval_2/1000.0/60.0);
				else if(sr >= ControlData[1].sigma[1]+ErrorStressAir)	DAVout[CH_EP_Cell]=DAVout[CH_EP_Cell]-float(DA_Cal_a[CH_EP_Cell]*ControlData[1].sigmaRate[1]*TimeInterval_2/1000.0/60.0);
				else{
					Target_sr=ControlData[1].sigma[1];
					DAVout[CH_EP_Cell]=DAVout[CH_EP_Cell]+float(0.2*DA_Cal_a[CH_EP_Cell]*(Target_sr-sr));
				}
			}
			
			// Axial control
			DAVout[CH_AxisMotor]=5.0f;			// Motor: On
			if( q > ErrorStressMotor ){
				DAVout[CH_AxisClutch]=VoltUp;	// Clutch: Unloading
				if( q > ControlData[1].q[0] )	DAVout[CH_AxisSpeed]=float(DA_Cal_a[CH_AxisSpeed]*ControlData[1].AxisSpeed+DA_Cal_b[CH_AxisSpeed]);
				if( q <= ControlData[1].q[0] )	DAVout[CH_AxisSpeed]=float(DA_Cal_a[CH_AxisSpeed]*(q/ControlData[1].q[0])*ControlData[1].AxisSpeed+DA_Cal_b[CH_AxisSpeed]);
			}
			else if( q < -ErrorStressMotor ){
				DAVout[CH_AxisClutch]=VoltDown;		// Clutch: loading
				if( q < -ControlData[1].q[0] )	DAVout[CH_AxisSpeed]=float(DA_Cal_a[CH_AxisSpeed]*ControlData[1].AxisSpeed+DA_Cal_b[CH_AxisSpeed]);
				if( q >= -ControlData[1].q[0] )	DAVout[CH_AxisSpeed]=float(DA_Cal_a[CH_AxisSpeed]*(-q/ControlData[1].q[0])*ControlData[1].AxisSpeed+DA_Cal_b[CH_AxisSpeed]);
			}
			else {
				DAVout[CH_AxisSpeed]=0.0f;	// RPM->0
			}

			// Torque control @note Hashimoto modified 2022.12
			//float torsional_speed = 10.f; //10[RPM]
			//DAVout[CH_TorsionMotor] = 5.0f;			// Motor: On
			//Target_tzq = 0;
			//if (szq > Target_tzq + ErrorStressMotor) {
			//	DAVout[CH_TorsionSpeed] = float(DA_Cal_a[CH_TorsionSpeed] * torsional_speed + DA_Cal_b[CH_TorsionSpeed]);
			//	DAVout[CH_TorsionClutch] = VoltCCW;
			//}
			//else if (szq < Target_tzq - ErrorStressMotor) {
			//	DAVout[CH_TorsionSpeed] = float(DA_Cal_a[CH_TorsionSpeed] * torsional_speed + DA_Cal_b[CH_TorsionSpeed]);
			//	DAVout[CH_TorsionClutch] = VoltCW;
			//}
			//else {
			//	DAVout[CH_TorsionSpeed] = 0.0f;
			//}

			DA_OUTPUT();
		}
		break;
	case 2:
		{ 
			// Consolidation Process
			// ControlData[2].sigma[0]:		Axial effective stress
			// ControlData[2].K0:			K0 value
			// ControlData[2].AxisSpeed		Axial motor speed (RPM)
			// ControlData[2].sigmaRate[2]: Increment rate of cell pressure
			if( ControlData[2].sigmaRate[2] > 0.0 ){
				if( sr < ControlData[2].sigma[0]*ControlData[2].K0 - ErrorStressAir){
					DAVout[CH_EP_Cell]=DAVout[CH_EP_Cell]+float(DA_Cal_a[CH_EP_Cell]*ControlData[2].sigmaRate[2]/60.0*TimeInterval_2/1000.0);
				}	
				if( sr > ControlData[2].sigma[0]*ControlData[2].K0 + ErrorStressAir){
					DAVout[CH_EP_Cell]=DAVout[CH_EP_Cell]-float(DA_Cal_a[CH_EP_Cell]*ControlData[2].sigmaRate[2]/60.0*TimeInterval_2/1000.0);
				}
			}
			if( ControlData[2].K0 != 0.0 ){
				Target_sz = sr / ControlData[2].K0;
				DAVout[CH_AxisMotor] = 5.0f;			// Motor: On
				DAVout[CH_AxisSpeed] = float(DA_Cal_a[CH_AxisSpeed]*ControlData[2].AxisSpeed+DA_Cal_b[CH_AxisSpeed]);
				if( sz > Target_sz + ErrorStressMotor )			DAVout[CH_AxisClutch]=VoltUp;	// Clutch: Unloading
				else if( sz < Target_sz - ErrorStressMotor )	DAVout[CH_AxisClutch]=VoltDown;	// Clutch: loading
				else											DAVout[CH_AxisSpeed]=0.0f;	// RPM->0
			}		
			DA_OUTPUT();
		}
		break;
	case 3:
		{ 
			DA_OUTPUT();
		}
		break;
	case 4:
		{ 
		DA_OUTPUT();
		}
		break;
	case 5:
		{	
			DA_OUTPUT();
		}
		break;
	case 6:
		{ 
			DA_OUTPUT();
		}
		break;
	case 7:
		{ 
			DA_OUTPUT();
		}
		break;
	case 8:
		{ 
			DA_OUTPUT();
		}
		break;
	case 9:
		{ 
			DA_OUTPUT();
		}
		break;
	case 10:
		{ 
			DA_OUTPUT();
		}
		break;
	case 11:
		{ 
			DA_OUTPUT();
		}
		break;
	case 12:
		{ 
			DA_OUTPUT();
		}
		break;
	case 13:
		{ 
			DA_OUTPUT();
		}
		break;
	case 14:
		{ 
			DA_OUTPUT();
		}
		break;
	case 15:
		{ 
			if( CFNUM[CURNUM]==0 ){
				// 2023.11.29 Edited by Hashimoto
				// stop any loading if control Number is 0
				DAVout[CH_AxisMotor] = 0.0f;
				DAVout[CH_AxisSpeed] = 0.0f;
				DAVout[CH_TorsionMotor] = 0.0f;
				DAVout[CH_TorsionSpeed] = 0.0f;
			}
			else if( CFNUM[CURNUM]==1 ) EffectiveStressPathLoading();
			else if( CFNUM[CURNUM]==2 ) MonotonicTorsionalLoading();
			else if( CFNUM[CURNUM]==3 ) MonotonicTorsionalLoadingCNS();
			else if( CFNUM[CURNUM]==4 ) CyclicTorsionalLoading();
			else if( CFNUM[CURNUM]==5 ) CyclicTorsionalLoadingCNS();
			else if( CFNUM[CURNUM]==6 ) SmallCyclicTorsionalLoading();
			else if( CFNUM[CURNUM]==7 ) SmallCyclicTorsionalLoadingCNS();
			else if( CFNUM[CURNUM]==8 ) MonotonicAxialLoading();
			else if( CFNUM[CURNUM]==9 ) CyclicAxialLoading();
			else if( CFNUM[CURNUM]==10) SmallCyclicAxialLoading();
			else if( CFNUM[CURNUM]==11) Creep();
			// 2021.06.07 Edited by M.Kuno
			// customize for Sanjei
			else if( CFNUM[CURNUM]==12) MonotonicAxialLoadingConstP();
			else if( CFNUM[CURNUM]==13) MonotonicTorsionalLoadingConstPA();
			else if (CFNUM[CURNUM]==14) CyclicAxialLoading_OR();
			else if (CFNUM[CURNUM] == 15) FileControlableConsolidation();
			DA_OUTPUT();
		}
		break;
	}
}

void CDigitShowBasicDoc::Start_Control()
{

}

void CDigitShowBasicDoc::Stop_Control()
{
	DAVout[CH_AxisMotor]=0.0f;
	DAVout[CH_AxisSpeed]=0.0f;
	DAVout[CH_TorsionMotor]=0.0f;
	DAVout[CH_TorsionSpeed]=0.0f;
	DA_OUTPUT();
}

void CDigitShowBasicDoc::FileControlableConsolidation()
{
	// 0: sigma_z_ini, 
	// 1: sigma_r_ini, 
	// 2: tau_zq_ini, 
	// 3: sigma_z_end, 
	// 4: sigma_r_end, 
	// 5: tau_zq_end.
	// 6: Axial Motor Speed	(RPM)
	// 7: Torsion Motor Speed (RPM)
	// 8: Cell Pressure Rate (min/kPa)
	StepTime = StepTime + CtrlStepTime / 60.0;
	
	if (CFPARA[CURNUM][8] > 0.0) {
		if (sr < CFPARA[CURNUM][4] - ErrorStressAir) {
			DAVout[CH_EP_Cell] = DAVout[CH_EP_Cell] + float(DA_Cal_a[CH_EP_Cell] * CFPARA[CURNUM][8] / 60.0 * TimeInterval_2 / 1000.0);
		}
		if (sr > CFPARA[CURNUM][4] + ErrorStressAir) {
			DAVout[CH_EP_Cell] = DAVout[CH_EP_Cell] - float(DA_Cal_a[CH_EP_Cell] * CFPARA[CURNUM][8] / 60.0 * TimeInterval_2 / 1000.0);
		}
	}

	if (CFPARA[CURNUM][4] == CFPARA[CURNUM][1]) {
		CURNUM = CURNUM + 1;
		StepTime = 0.0;
	}
	else {
		float comp_rate = (sr - CFPARA[CURNUM][1]) / (CFPARA[CURNUM][4] - CFPARA[CURNUM][1]);
		float Target_szq = CFPARA[CURNUM][2] + comp_rate * (CFPARA[CURNUM][5] - CFPARA[CURNUM][2]);
		Target_sz = CFPARA[CURNUM][0] + comp_rate * (CFPARA[CURNUM][3] - CFPARA[CURNUM][0]);

		DAVout[CH_AxisMotor] = 5.0f;			// Axial Motor: On
		DAVout[CH_TorsionMotor] = 5.0f;         // Torsional Motor: On
		DAVout[CH_AxisSpeed] = float(DA_Cal_a[CH_AxisSpeed] * CFPARA[CURNUM][6] + DA_Cal_b[CH_AxisSpeed]);
		DAVout[CH_TorsionSpeed] = float(DA_Cal_a[CH_TorsionSpeed] * CFPARA[CURNUM][7] + DA_Cal_b[CH_TorsionSpeed]);

		if (sz > Target_sz + ErrorStressMotor)			DAVout[CH_AxisClutch] = VoltUp;	// Clutch: Unloading
		else if (sz < Target_sz - ErrorStressMotor)	DAVout[CH_AxisClutch] = VoltDown;	// Clutch: loading
		else											DAVout[CH_AxisSpeed] = 0.0f;	// RPM->0

		if (szq > Target_szq + ErrorStressMotor)			DAVout[CH_TorsionClutch] = VoltCCW;	// Clutch: Unloading
		else if (szq < Target_szq - ErrorStressMotor)	DAVout[CH_TorsionClutch] = VoltCW;	// Clutch: loading
		else											DAVout[CH_TorsionSpeed] = 0.0f;	// RPM->0
	}

	if (fabs(sz - CFPARA[CURNUM][3]) <= ErrorStressMotor * 2.0 && fabs(sr - CFPARA[CURNUM][4]) <= ErrorStressMotor * 2.0 && fabs(szq - CFPARA[CURNUM][5]) <= ErrorStressMotor * 2.0) {
		CURNUM = CURNUM + 1;
		StepTime = 0.0;
	}
}


void CDigitShowBasicDoc::EffectiveStressPathLoading()
{
	// 0: sigma_z_ini, 
	// 1: sigma_r_ini, 
	// 2: tau_zq_ini, 
	// 3: sigma_z_end, 
	// 4: sigma_r_end, 
	// 5: tau_zq_end.
	// 6: Axial Motor Speed	(RPM)
	// 7: Torsion Motor Speed (RPM)
	// 8: Cell Pressure Rate (min/kPa),
	StepTime=StepTime+CtrlStepTime/60.0;
	if(CFPARA[CURNUM][1] != CFPARA[CURNUM][4] ){
		if(sr < CFPARA[CURNUM][4]-ErrorStressAir) Target_sr=sr+CFPARA[CURNUM][8]*TimeInterval_2/1000/60;
		if(sr > CFPARA[CURNUM][4]+ErrorStressAir) Target_sr=sr-CFPARA[CURNUM][8]*TimeInterval_2/1000/60;
		if(fabs(sr-CFPARA[CURNUM][4]) <= ErrorStressAir) Target_sr=CFPARA[CURNUM][4];
		Target_sz=(CFPARA[CURNUM][3]-CFPARA[CURNUM][0])/(CFPARA[CURNUM][4]-CFPARA[CURNUM][1])*(sr-CFPARA[CURNUM][1])+CFPARA[CURNUM][0];
		if(CFPARA[CURNUM][3] > CFPARA[CURNUM][0] && Target_sz > CFPARA[CURNUM][3]) Target_sz=CFPARA[CURNUM][3]; 
		if(CFPARA[CURNUM][3] < CFPARA[CURNUM][0] && Target_sz < CFPARA[CURNUM][3]) Target_sz=CFPARA[CURNUM][3]; 
		Target_tzq=(CFPARA[CURNUM][5]-CFPARA[CURNUM][2])/(CFPARA[CURNUM][4]-CFPARA[CURNUM][1])*(sr-CFPARA[CURNUM][1])+CFPARA[CURNUM][2];
		if(CFPARA[CURNUM][5] > CFPARA[CURNUM][2] && Target_tzq > CFPARA[CURNUM][5]) Target_tzq=CFPARA[CURNUM][5]; 
		if(CFPARA[CURNUM][5] < CFPARA[CURNUM][2] && Target_tzq < CFPARA[CURNUM][5]) Target_tzq=CFPARA[CURNUM][5]; 
	}
	else if(CFPARA[CURNUM][0] != CFPARA[CURNUM][3] && fabs(CFPARA[CURNUM][3]-CFPARA[CURNUM][0]) >= fabs(CFPARA[CURNUM][5]-CFPARA[CURNUM][2])){
		Target_sr=CFPARA[CURNUM][4];
		Target_sz=CFPARA[CURNUM][3];
		Target_tzq=(CFPARA[CURNUM][5]-CFPARA[CURNUM][2])/(CFPARA[CURNUM][3]-CFPARA[CURNUM][0])*(sz-CFPARA[CURNUM][0])+CFPARA[CURNUM][2];
		if(CFPARA[CURNUM][5] > CFPARA[CURNUM][2] && Target_tzq > CFPARA[CURNUM][5]) Target_tzq=CFPARA[CURNUM][5]; 
		if(CFPARA[CURNUM][5] < CFPARA[CURNUM][2] && Target_tzq < CFPARA[CURNUM][5]) Target_tzq=CFPARA[CURNUM][5]; 
	}
	else if(CFPARA[CURNUM][2] != CFPARA[CURNUM][5]){
		Target_sr=CFPARA[CURNUM][4];
		Target_sz=(CFPARA[CURNUM][3]-CFPARA[CURNUM][0])/(CFPARA[CURNUM][5]-CFPARA[CURNUM][2])*(szq-CFPARA[CURNUM][2])+CFPARA[CURNUM][0];
		if(CFPARA[CURNUM][3] > CFPARA[CURNUM][0] && Target_sz > CFPARA[CURNUM][3]) Target_sz=CFPARA[CURNUM][3]; 
		if(CFPARA[CURNUM][3] < CFPARA[CURNUM][0] && Target_sz < CFPARA[CURNUM][3]) Target_sz=CFPARA[CURNUM][3]; 
		Target_tzq=CFPARA[CURNUM][5];
	}
	else {
		Target_sr=CFPARA[CURNUM][4];
		Target_sz=CFPARA[CURNUM][3];
		Target_tzq=CFPARA[CURNUM][5];
	}
//
	DAVout[CH_AxisMotor]=5.0f;
	DAVout[CH_AxisSpeed]=float(DA_Cal_a[CH_AxisSpeed]*CFPARA[CURNUM][6]+DA_Cal_b[CH_AxisSpeed]);
	DAVout[CH_TorsionMotor]=5.0f;
	DAVout[CH_TorsionSpeed]=float(DA_Cal_a[CH_TorsionSpeed]*CFPARA[CURNUM][7]+DA_Cal_b[CH_TorsionSpeed]);
	// @note M.KUNO 2022.12.02 original code
	//if( CFPARA[CURNUM][8] != 0.0 )	DAVout[CH_EP_Cell]=DAVout[CH_EP_Cell]+float(0.3*DA_Cal_a[CH_EP_Cell]*(Target_sr-sr));
	// @note M.KUNO 2022.12.02 edited code
	if (CFPARA[CURNUM][8] != 0.0)	DAVout[CH_EP_Cell] = DAVout[CH_EP_Cell] + float(0.9 * DA_Cal_a[CH_EP_Cell] * (Target_sr - sr));
//
	if(sz > Target_sz+ErrorStressMotor)			DAVout[CH_AxisClutch]=VoltUp;
	else if(sz < Target_sz-ErrorStressMotor)	DAVout[CH_AxisClutch]=VoltDown;
	else										DAVout[CH_AxisSpeed]=0.0f;
//	
	if(szq > Target_tzq + ErrorStressMotor)			DAVout[CH_TorsionClutch]=VoltCCW;
	else if(szq < Target_tzq - ErrorStressMotor)	DAVout[CH_TorsionClutch]=VoltCW;
	else											DAVout[CH_TorsionSpeed]=0.0f;
//
	if( fabs(sz-CFPARA[CURNUM][3])<=ErrorStressMotor*2.0 && fabs(sr-CFPARA[CURNUM][4])<=ErrorStressMotor*2.0 && fabs(szq-CFPARA[CURNUM][5])<=ErrorStressMotor*2.0 ){
		CURNUM=CURNUM+1;
		StepTime=0.0;
	}
}

void CDigitShowBasicDoc::MonotonicTorsionalLoading()
{
	//	0: Clockwise:0 / Countercloclwise:1
	//	1: sigma_zq
	//	2: gamma_zq
	//	3: Torsinal Speed
	StepTime=StepTime+CtrlStepTime/60.0;
	DAVout[CH_TorsionMotor]=5.0f;
	DAVout[CH_TorsionSpeed]=float(DA_Cal_a[CH_TorsionSpeed]*CFPARA[CURNUM][3]+DA_Cal_b[CH_TorsionSpeed]);
//
	if(CFPARA[CURNUM][0]==0.0){
		if(szq < CFPARA[CURNUM][1] && gzq1 < CFPARA[CURNUM][2])	DAVout[CH_TorsionClutch] = VoltCW;
		else {
			StepTime=0.0;
			CURNUM=CURNUM+1;
		}
	}
	else if(CFPARA[CURNUM][0]==1.0){
		if(szq > CFPARA[CURNUM][1] && gzq1 > CFPARA[CURNUM][2])	DAVout[CH_TorsionClutch] = VoltCCW;
		else {
			StepTime=0.0;
			CURNUM=CURNUM+1;
		}
	}
}

void CDigitShowBasicDoc::MonotonicTorsionalLoadingCNS()
{
	//	0: Clockwise:0 / Countercloclwise:1
	//	1: sigma_zq
	//	2: gamma_zq
	//	3: Torsinal Speed
	//	4: Axial Speed
	//	5: Cell Pressure Rate
	//	6: sigma_z
	//	7: sigma_r
	StepTime=StepTime+CtrlStepTime/60.0;
	DAVout[CH_AxisMotor]=5.0f;
	DAVout[CH_AxisSpeed]=float(DA_Cal_a[CH_AxisSpeed]*CFPARA[CURNUM][4]+DA_Cal_b[CH_AxisSpeed]);
	DAVout[CH_TorsionMotor]=5.0f;
	DAVout[CH_TorsionSpeed]=float(DA_Cal_a[CH_TorsionSpeed]*CFPARA[CURNUM][3]+DA_Cal_b[CH_TorsionSpeed]);
	if(sz > CFPARA[CURNUM][6]+ErrorStressMotor)			DAVout[CH_AxisClutch]=VoltUp;
	else if(sz < CFPARA[CURNUM][6]-ErrorStressMotor)	DAVout[CH_AxisClutch]=VoltDown;
	else												DAVout[CH_AxisSpeed]=0.0f;
	Target_sr=CFPARA[CURNUM][7];
	// @note M.KUNO 2022.12.15 original code
	//if( CFPARA[CURNUM][5] != 0.0 )	DAVout[CH_EP_Cell]=DAVout[CH_EP_Cell]+float(0.3*DA_Cal_a[CH_EP_Cell]*(Target_sr-sr));
	// @note H.Hashimoto 2022.12.15 fixed code
	if (CFPARA[CURNUM][5] != 0.0) {
		if (sr < Target_sr - ErrorStressAir) {
			DAVout[CH_EP_Cell] = DAVout[CH_EP_Cell] + float(DA_Cal_a[CH_EP_Cell] * CFPARA[CURNUM][5] / 60.0 * TimeInterval_2 / 1000.0);
		}
		else if (sr > Target_sr + ErrorStressAir) {
			DAVout[CH_EP_Cell] = DAVout[CH_EP_Cell] - float(DA_Cal_a[CH_EP_Cell] * CFPARA[CURNUM][5] / 60.0 * TimeInterval_2 / 1000.0);
		}
	}
//
	if(CFPARA[CURNUM][0]==0.0){
		if(szq < CFPARA[CURNUM][1] && gzq1 < CFPARA[CURNUM][2])	DAVout[CH_TorsionClutch] = VoltCW;
		else {
			StepTime=0.0;
			CURNUM=CURNUM+1;
		}
	}
	else if(CFPARA[CURNUM][0]==1.0){
		if(szq > CFPARA[CURNUM][1] && gzq1 > CFPARA[CURNUM][2])	DAVout[CH_TorsionClutch] = VoltCCW;
		else {
			StepTime=0.0;
			CURNUM=CURNUM+1;
		}
	}
}

void CDigitShowBasicDoc::CyclicTorsionalLoading()
{
	//	0: Clockwise:0 / Countercloclwise:1
	//	1: sigma_zq_lower
	//	2: sigma_zq_upper
	//	3: gamma_zq_lower
	//	4: gamma_zq_upper
	//	5: Number
	//	6: Torsinal Speed
	StepTime=StepTime+CtrlStepTime/60.0;
	DAVout[CH_TorsionMotor] = 5.0f;
	DAVout[CH_TorsionSpeed]=float(DA_Cal_a[CH_TorsionSpeed]*CFPARA[CURNUM][6]+DA_Cal_b[CH_TorsionSpeed]);
	if(CFPARA[CURNUM][0]==0.0){
		if(Num_Cyclic==0){
			Flag_Cyclic=FALSE;
			Num_Cyclic=1;
		}
		if(Num_Cyclic != 0 && Num_Cyclic <= CFPARA[CURNUM][5]){
			if(Flag_Cyclic==FALSE){
				DAVout[CH_TorsionClutch] = VoltCW;
				if(szq >= CFPARA[CURNUM][2] || gzq1 >= CFPARA[CURNUM][4]) Flag_Cyclic=TRUE;
			}
			if(Flag_Cyclic==TRUE){
				DAVout[CH_TorsionClutch] = VoltCCW;
				if(szq <= CFPARA[CURNUM][1] || gzq1 <= CFPARA[CURNUM][3]){
					Flag_Cyclic=FALSE;
					Num_Cyclic=Num_Cyclic+1;
				}
			}
		}
		if(Num_Cyclic > CFPARA[CURNUM][5]){ 
			CURNUM=CURNUM+1;
			StepTime=0.0;
			Num_Cyclic=0;
		}
	}
	else if(CFPARA[CURNUM][0]==1.0){
		if(Num_Cyclic==0){
			Flag_Cyclic=TRUE;
			Num_Cyclic=1;
		}
		if(Num_Cyclic != 0 && Num_Cyclic <= CFPARA[CURNUM][5]){
			if(Flag_Cyclic==FALSE){
				DAVout[CH_TorsionClutch] = VoltCCW;
				if(szq <= CFPARA[CURNUM][1] || gzq1 <= CFPARA[CURNUM][3]) {
					Flag_Cyclic=TRUE;
					Num_Cyclic=Num_Cyclic+1;
				}
			}
			if(Flag_Cyclic==TRUE){
				DAVout[CH_TorsionClutch] = VoltCW;
				if(szq >= CFPARA[CURNUM][2] || gzq1 <= CFPARA[CURNUM][4]){
					Flag_Cyclic=FALSE;
				}
			}
		}
		if(Num_Cyclic > CFPARA[CURNUM][5]){ 
			CURNUM=CURNUM+1;
			StepTime=0.0;
			Num_Cyclic=0;
		}
	} 
}

void CDigitShowBasicDoc::CyclicTorsionalLoadingCNS()
{
	//	0: Clockwise:0 / Countercloclwise:1
	//	1: sigma_zq_lower
	//	2: sigma_zq_upper
	//	3: gamma_zq_lower
	//	4: gamma_zq_upper
	//	5: Number
	//	6: Torsinal Speed
	//	7: Axial Speed
	//	8: Cell Pressure Rate
	//	9: sigma_z
	//	10: sigma_r
	StepTime=StepTime+CtrlStepTime/60.0;
	DAVout[CH_AxisMotor]=5.0f;
	DAVout[CH_AxisSpeed]=float(DA_Cal_a[CH_AxisSpeed]*CFPARA[CURNUM][7]+DA_Cal_b[CH_AxisSpeed]);
	DAVout[CH_TorsionMotor] = 5.0f;
	DAVout[CH_TorsionSpeed]=float(DA_Cal_a[CH_TorsionSpeed]*CFPARA[CURNUM][6]+DA_Cal_b[CH_TorsionSpeed]);
	if(sz > CFPARA[CURNUM][9]+ErrorStressMotor)			DAVout[CH_AxisClutch]=VoltUp;
	else if(sz < CFPARA[CURNUM][9]-ErrorStressMotor)	DAVout[CH_AxisClutch]=VoltDown;
	else												DAVout[CH_AxisSpeed]=0.0f;
	Target_sr=CFPARA[CURNUM][10];
	if( CFPARA[CURNUM][8] != 0.0 )	DAVout[CH_EP_Cell]=DAVout[CH_EP_Cell]+float(0.3*DA_Cal_a[CH_EP_Cell]*(Target_sr-sr));
//	
	if(CFPARA[CURNUM][0]==0.0){
		if(Num_Cyclic==0){
			Flag_Cyclic=FALSE;
			Num_Cyclic=1;
		}
		if(Num_Cyclic != 0 && Num_Cyclic <= CFPARA[CURNUM][5]){
			if(Flag_Cyclic==FALSE){
				DAVout[CH_TorsionClutch] = VoltCW;
				if(szq >= CFPARA[CURNUM][2] || gzq1 >= CFPARA[CURNUM][4]) Flag_Cyclic=TRUE;
			}
			if(Flag_Cyclic==TRUE){
				DAVout[CH_TorsionClutch] = VoltCCW;
				if(szq <= CFPARA[CURNUM][1] || gzq1 <= CFPARA[CURNUM][3]){
					Flag_Cyclic=FALSE;
					Num_Cyclic=Num_Cyclic+1;
				}
			}
		}
		if(Num_Cyclic > CFPARA[CURNUM][5]){ 
			CURNUM=CURNUM+1;
			StepTime=0.0;
			Num_Cyclic=0;
		}
	}
	else if(CFPARA[CURNUM][0]==1.0){
		if(Num_Cyclic==0){
			Flag_Cyclic=TRUE;
			Num_Cyclic=1;
		}
		if(Num_Cyclic != 0 && Num_Cyclic <= CFPARA[CURNUM][5]){
			if(Flag_Cyclic==FALSE){
				DAVout[CH_TorsionClutch] = VoltCCW;
				if(szq <= CFPARA[CURNUM][1] || gzq1 <= CFPARA[CURNUM][3]) {
					Flag_Cyclic=TRUE;
					Num_Cyclic=Num_Cyclic+1;
				}
			}
			if(Flag_Cyclic==TRUE){
				DAVout[CH_TorsionClutch] = VoltCW;
				if(szq >= CFPARA[CURNUM][2] || gzq1 <= CFPARA[CURNUM][4]){
					Flag_Cyclic=FALSE;
				}
			}
		}
		if(Num_Cyclic > CFPARA[CURNUM][5]){ 
			CURNUM=CURNUM+1;
			StepTime=0.0;
			Num_Cyclic=0;
		}
	} 
}

void CDigitShowBasicDoc::SmallCyclicTorsionalLoading()
{
	//	0: Clockwise:0 / Countercloclwise:1
	//	1: Delta[gamma_zq]
	//	2: Number
	//	3: Torsinal Speed
	StepTime=StepTime+CtrlStepTime/60.0;
	DAVout[CH_TorsionMotor] = 5.0f;
	DAVout[CH_TorsionSpeed]=float(DA_Cal_a[CH_TorsionSpeed]*CFPARA[CURNUM][3]+DA_Cal_b[CH_TorsionSpeed]);
	if(CFPARA[CURNUM][0]==0.0){
		if(Num_Cyclic==0){
			Target_gzq = gzq2;
			Num_Cyclic=1;
			Num_SmallCyclic=0;
		}
		if(Num_Cyclic != 0 && Num_Cyclic <= CFPARA[CURNUM][2]){
			if(Num_SmallCyclic==0){
				DAVout[CH_TorsionClutch] = VoltCCW;
				if(gzq2 <= Target_gzq - CFPARA[CURNUM][1]) Num_SmallCyclic=1;
			}
			if(Num_SmallCyclic==1){
				DAVout[CH_TorsionClutch] = VoltCW;
				if(gzq2 >= Target_gzq + CFPARA[CURNUM][1]) Num_SmallCyclic=2;
			}
			if(Num_SmallCyclic==2){
				DAVout[CH_TorsionClutch] = VoltCCW;
				if(gzq2 <= Target_gzq){;
					Num_SmallCyclic=0;
					Num_Cyclic=Num_Cyclic+1;
				}
			}
		}
		if(Num_Cyclic > CFPARA[CURNUM][2]){ 
			CURNUM=CURNUM+1;
			StepTime=0.0;
			Num_Cyclic=0;
		}
	}
	else if(CFPARA[CURNUM][0]==1.0){
		if(Num_Cyclic==0){
			Target_gzq = gzq2;
			Num_Cyclic=1;
			Num_SmallCyclic=0;
		}
		if(Num_Cyclic != 0 && Num_Cyclic <= CFPARA[CURNUM][2]){
			if(Num_SmallCyclic==0){
				DAVout[CH_TorsionClutch] = VoltCW;
				if(gzq2 >= Target_gzq + CFPARA[CURNUM][1])	Num_SmallCyclic=1;
			}
			if(Num_SmallCyclic==1){
				DAVout[CH_TorsionClutch] = VoltCCW;
				if(gzq2 <= Target_gzq - CFPARA[CURNUM][1])	Num_SmallCyclic=2;
			}
			if(Num_SmallCyclic==2){
				DAVout[CH_TorsionClutch] = VoltCW;
				if(gzq2 >= Target_gzq) {
					Num_SmallCyclic=0;
					Num_Cyclic=Num_Cyclic+1;
				}
			}
		}
		if(Num_Cyclic > CFPARA[CURNUM][2]){ 
			CURNUM=CURNUM+1;
			StepTime=0.0;
			Num_Cyclic=0;
		}
	} 
}


void CDigitShowBasicDoc::SmallCyclicTorsionalLoadingCNS()
{
	//	0: Clockwise:0 / Countercloclwise:1
	//	1: Delta[gamma_zq]
	//	2: Number
	//	3: Torsinal Speed
	//	4: Axial Speed
	//	5: Cell Pressure Rate
	//	6: sigma_z
	//	7: sigma_r
	StepTime=StepTime+CtrlStepTime/60.0;
	DAVout[CH_AxisMotor]=5.0f;
	DAVout[CH_AxisSpeed]=float(DA_Cal_a[CH_AxisSpeed]*CFPARA[CURNUM][4]+DA_Cal_b[CH_AxisSpeed]);
	DAVout[CH_TorsionMotor] = 5.0f;
	DAVout[CH_TorsionSpeed]=float(DA_Cal_a[CH_TorsionSpeed]*CFPARA[CURNUM][3]+DA_Cal_b[CH_TorsionSpeed]);
	if(sz > CFPARA[CURNUM][6]+ErrorStressMotor)			DAVout[CH_AxisClutch]=VoltUp;
	else if(sz < CFPARA[CURNUM][6]-ErrorStressMotor)	DAVout[CH_AxisClutch]=VoltDown;
	else												DAVout[CH_AxisSpeed]=0.0f;
	Target_sr=CFPARA[CURNUM][7];
	if( CFPARA[CURNUM][5] != 0.0 )	DAVout[CH_EP_Cell]=DAVout[CH_EP_Cell]+float(0.3*DA_Cal_a[CH_EP_Cell]*(Target_sr-sr));
//
	if(CFPARA[CURNUM][0]==0.0){
		if(Num_Cyclic==0){
			Target_gzq = gzq2;
			Num_Cyclic=1;
			Num_SmallCyclic=0;
		}
		if(Num_Cyclic != 0 && Num_Cyclic <= CFPARA[CURNUM][2]){
			if(Num_SmallCyclic==0){
				DAVout[CH_TorsionClutch] = VoltCCW;
				if(gzq2 <= Target_gzq - CFPARA[CURNUM][1]) Num_SmallCyclic=1;
			}
			if(Num_SmallCyclic==1){
				DAVout[CH_TorsionClutch] = VoltCW;
				if(gzq2 >= Target_gzq + CFPARA[CURNUM][1]) Num_SmallCyclic=2;
			}
			if(Num_SmallCyclic==2){
				DAVout[CH_TorsionClutch] = VoltCCW;
				if(gzq2 <= Target_gzq){;
					Num_SmallCyclic=0;
					Num_Cyclic=Num_Cyclic+1;
				}
			}
		}
		if(Num_Cyclic > CFPARA[CURNUM][2]){ 
			CURNUM=CURNUM+1;
			StepTime=0.0;
			Num_Cyclic=0;
		}
	}
	else if(CFPARA[CURNUM][0]==1.0){
		if(Num_Cyclic==0){
			Target_gzq = gzq2;
			Num_Cyclic=1;
			Num_SmallCyclic=0;
		}
		if(Num_Cyclic != 0 && Num_Cyclic <= CFPARA[CURNUM][2]){
			if(Num_SmallCyclic==0){
				DAVout[CH_TorsionClutch] = VoltCW;
				if(gzq2 >= Target_gzq + CFPARA[CURNUM][1])	Num_SmallCyclic=1;
			}
			if(Num_SmallCyclic==1){
				DAVout[CH_TorsionClutch] = VoltCCW;
				if(gzq2 <= Target_gzq - CFPARA[CURNUM][1])	Num_SmallCyclic=2;
			}
			if(Num_SmallCyclic==2){
				DAVout[CH_TorsionClutch] = VoltCW;
				if(gzq2 >= Target_gzq) {
					Num_SmallCyclic=0;
					Num_Cyclic=Num_Cyclic+1;
				}
			}
		}
		if(Num_Cyclic > CFPARA[CURNUM][2]){ 
			CURNUM=CURNUM+1;
			StepTime=0.0;
			Num_Cyclic=0;
		}
	} 
}

void CDigitShowBasicDoc::MonotonicAxialLoading()
{
	// 0: Loading:0/Unloading:1, 
	// 1: sigma_z (kPa), 
	// 2: epsilon_z,
	// 3: Axial Speed
	StepTime=StepTime+CtrlStepTime/60.0;
	DAVout[CH_AxisMotor]=5.0f;
	DAVout[CH_AxisSpeed]=float(DA_Cal_a[CH_AxisSpeed]*CFPARA[CURNUM][3]+DA_Cal_b[CH_AxisSpeed]);
	if(CFPARA[CURNUM][0]==0.0){
		if(sz <= CFPARA[CURNUM][1] && ez < CFPARA[CURNUM][2]) DAVout[CH_AxisClutch]=VoltDown;
		else {
			CURNUM=CURNUM+1;
			StepTime=0.0;
		}
	}
	else if(CFPARA[CURNUM][0]==1.0){
		if(sz >= CFPARA[CURNUM][1] && ez > CFPARA[CURNUM][2]) DAVout[CH_AxisClutch]=VoltUp;
		else {
			CURNUM=CURNUM+1;
			StepTime=0.0;
		}
	}
}


void CDigitShowBasicDoc::CyclicAxialLoading()
{
	// 0: Loading:0/Unloading:1, 
	// 1: sigma_z_lower, 
	// 2: sigma_z_upper, 
	// 3: epsilon_z_lower,
	// 4: epsilon_z_upper,
	// 5: Number,
	// 6: Axial Speed
	StepTime=StepTime+CtrlStepTime/60.0;
	DAVout[CH_AxisMotor]=5.0f;
	DAVout[CH_AxisSpeed]=float(DA_Cal_a[CH_AxisSpeed]*CFPARA[CURNUM][6]+DA_Cal_b[CH_AxisSpeed]);
	if(CFPARA[CURNUM][0]==0.0){
		if(Num_Cyclic==0){
			Flag_Cyclic=FALSE;
			Num_Cyclic=1;
		}
		if(Num_Cyclic!=0 && Num_Cyclic <= CFPARA[CURNUM][5]){
			if(Flag_Cyclic==FALSE){
				if(sz <= CFPARA[CURNUM][2] && ez <= CFPARA[CURNUM][4])	DAVout[CH_AxisClutch]=VoltDown;
				else	Flag_Cyclic=TRUE;
			}
			else {
				if(sz >= CFPARA[CURNUM][1] && ez >= CFPARA[CURNUM][3]) DAVout[CH_AxisClutch]=VoltUp;
				else{
					Flag_Cyclic=FALSE;
					Num_Cyclic=Num_Cyclic+1;
				}
			}
		}
		if(Num_Cyclic>CFPARA[CURNUM][5]){ 
			CURNUM=CURNUM+1;
			StepTime=0.0;
			Num_Cyclic=0;
		}
	}
	else if(CFPARA[CURNUM][0]==1.0){
		if(Num_Cyclic==0){
			Flag_Cyclic=TRUE;
			Num_Cyclic=1;
		}
		if(Num_Cyclic!=0 && Num_Cyclic <= CFPARA[CURNUM][2]){
			if(Flag_Cyclic==FALSE){
				if(sz <= CFPARA[CURNUM][2] && ez <= CFPARA[CURNUM][4])	DAVout[CH_AxisClutch]=VoltDown;
				else{
					Flag_Cyclic=TRUE;
					Num_Cyclic=Num_Cyclic+1;
				}
			}
			else{
				if(sz >= CFPARA[CURNUM][1] && ez >= CFPARA[CURNUM][3]) DAVout[CH_AxisClutch]=VoltUp;
				else	Flag_Cyclic=FALSE;
			}
		}
		if(Num_Cyclic>CFPARA[CURNUM][5]){ 
			CURNUM=CURNUM+1;
			StepTime=0.0;
			Num_Cyclic=0;
		}
	} 
}

void CDigitShowBasicDoc::SmallCyclicAxialLoading()
{
	//	0: Loading:0 / Unloading:1
	//	1: Delta[epsilon_z]
	//	2: Number
	//	3: Axial Speed
	StepTime=StepTime+CtrlStepTime/60.0;
	DAVout[CH_AxisMotor] = 5.0f;
	DAVout[CH_AxisSpeed]=float(DA_Cal_a[CH_AxisSpeed]*CFPARA[CURNUM][3]+DA_Cal_b[CH_AxisSpeed]);
	if(CFPARA[CURNUM][0]==0.0){
		if(Num_Cyclic==0){
			Target_ez = ez;
			Num_Cyclic=1;
			Num_SmallCyclic=0;
		}
		if(Num_Cyclic != 0 && Num_Cyclic <= CFPARA[CURNUM][2]){
			if(Num_SmallCyclic==0){
				DAVout[CH_AxisClutch] = VoltDown;
				if(ez >= Target_ez + CFPARA[CURNUM][1]) Num_SmallCyclic=1;
			}
			if(Num_SmallCyclic==1){
				DAVout[CH_AxisClutch] = VoltUp;
				if(ez <= Target_ez - CFPARA[CURNUM][1]) Num_SmallCyclic=2;
			}
			if(Num_SmallCyclic==2){
				DAVout[CH_AxisClutch] = VoltDown;
				if(ez >= Target_ez){;
					Num_SmallCyclic=0;
					Num_Cyclic=Num_Cyclic+1;
				}
			}
		}
		if(Num_Cyclic > CFPARA[CURNUM][2]){ 
			CURNUM=CURNUM+1;
			StepTime=0.0;
			Num_Cyclic=0;
		}
	}
	else if(CFPARA[CURNUM][0]==1.0){
		if(Num_Cyclic==0){
			Target_ez = ez;
			Num_Cyclic=1;
			Num_SmallCyclic=0;
		}
		if(Num_Cyclic != 0 && Num_Cyclic <= CFPARA[CURNUM][2]){
			if(Num_SmallCyclic==0){
				DAVout[CH_AxisClutch] = VoltUp;
				if(ez <= Target_ez - CFPARA[CURNUM][1])	Num_SmallCyclic=1;
			}
			if(Num_SmallCyclic==1){
				DAVout[CH_AxisClutch] = VoltDown;
				if(ez >= Target_ez - CFPARA[CURNUM][1])	Num_SmallCyclic=2;
			}
			if(Num_SmallCyclic==2){
				DAVout[CH_AxisClutch] = VoltUp;
				if(ez <= Target_ez) {
					Num_SmallCyclic=0;
					Num_Cyclic=Num_Cyclic+1;
				}
			}
		}
		if(Num_Cyclic > CFPARA[CURNUM][2]){ 
			CURNUM=CURNUM+1;
			StepTime=0.0;
			Num_Cyclic=0;
		}
	} 
}
void CDigitShowBasicDoc::Creep()
{
	// 0: sigma_z, 
	// 1: sigma_r,
	// 2: sigma_zq
	// 3: time (min)
	// 4: Torsinal Speed
	// 5: Axial Speed
	// 6: Cell Pressure Rate
	StepTime=StepTime+CtrlStepTime/60.0;
	DAVout[CH_AxisMotor]=5.0f;
	DAVout[CH_AxisSpeed]=float(DA_Cal_a[CH_AxisSpeed]*CFPARA[CURNUM][5]+DA_Cal_b[CH_AxisSpeed]);
	DAVout[CH_TorsionMotor] = 5.0f;
	DAVout[CH_TorsionSpeed]=float(DA_Cal_a[CH_TorsionSpeed]*CFPARA[CURNUM][4]+DA_Cal_b[CH_TorsionSpeed]);
//
	if(sz > CFPARA[CURNUM][0]+ErrorStressMotor)			DAVout[CH_AxisClutch]=VoltUp;
	else if(sz < CFPARA[CURNUM][0]-ErrorStressMotor)	DAVout[CH_AxisClutch]=VoltDown;
	else												DAVout[CH_AxisSpeed]=0.0f;
	Target_sr=CFPARA[CURNUM][1];
	if( CFPARA[CURNUM][6] != 0.0 )	{
		if(sr < CFPARA[CURNUM][1]-ErrorStressAir) Target_sr=sr+CFPARA[CURNUM][6]*TimeInterval_2/1000/60;
		if(sr > CFPARA[CURNUM][1]+ErrorStressAir) Target_sr=sr-CFPARA[CURNUM][6]*TimeInterval_2/1000/60;
		if(fabs(sr-CFPARA[CURNUM][1]) <= ErrorStressAir) Target_sr=CFPARA[CURNUM][1];
		DAVout[CH_EP_Cell]=DAVout[CH_EP_Cell]+float(0.3*DA_Cal_a[CH_EP_Cell]*(Target_sr-sr));
	}
	if(szq > CFPARA[CURNUM][2]+ErrorStressMotor)		DAVout[CH_TorsionClutch]=VoltCCW;
	else if(szq < CFPARA[CURNUM][2]-ErrorStressMotor)	DAVout[CH_TorsionClutch]=VoltCW;
	else												DAVout[CH_TorsionSpeed]=0.0f;
	if(StepTime >= CFPARA[CURNUM][3]){
		StepTime=0.0;
		CURNUM=CURNUM+1;
	} 
}

void CDigitShowBasicDoc::MonotonicAxialLoadingConstP()
{
	// 0: Compression:0/Extension:1, 
	// 1: sigma_z (kPa), 
	// 2: epsilon_z,
	// 3: Axial Speed,
	// 4: Mean effective principal stress p' (kPa), 
	// 5: sigma_zq (kPa),
	// 6: Torsional Speed,
	StepTime=StepTime+CtrlStepTime/60.0;
	DAVout[CH_AxisMotor]=5.0f;
	DAVout[CH_AxisSpeed]=float(DA_Cal_a[CH_AxisSpeed]*CFPARA[CURNUM][3]+DA_Cal_b[CH_AxisSpeed]);
	DAVout[CH_TorsionMotor] = 5.0f;
	DAVout[CH_TorsionSpeed]=float(DA_Cal_a[CH_TorsionSpeed]*CFPARA[CURNUM][6]+DA_Cal_b[CH_TorsionSpeed]);
	if(szq > CFPARA[CURNUM][5]+ErrorStressMotor)		DAVout[CH_TorsionClutch]=VoltCCW;
	else if(szq < CFPARA[CURNUM][5]-ErrorStressMotor)	DAVout[CH_TorsionClutch]=VoltCW;
	else												DAVout[CH_TorsionSpeed]=0.0f;
	if(CFPARA[CURNUM][0]==0.0){
		if(sz <= CFPARA[CURNUM][1] && ez < CFPARA[CURNUM][2]) {
			DAVout[CH_AxisClutch]=VoltDown;
			Target_sr= (3.0*CFPARA[CURNUM][4]-sz)/2.0 +ErrorStressAir;
			DAVout[CH_EP_Cell]= DAVout[CH_EP_Cell] + float(0.1*DA_Cal_a[CH_EP_Cell]*(Target_sr-sr));
		}
		else {
			CURNUM=CURNUM+1;
			StepTime=0.0;
		}
	}
	else if(CFPARA[CURNUM][0]==1.0){
		if(sz >= CFPARA[CURNUM][1] && ez > CFPARA[CURNUM][2]) {
			DAVout[CH_AxisClutch]=VoltUp;
			Target_sr= (3.0*CFPARA[CURNUM][4]-sz)/2.0 -ErrorStressAir ;
			DAVout[CH_EP_Cell]= DAVout[CH_EP_Cell] + float(0.1*DA_Cal_a[CH_EP_Cell]*(Target_sr-sr));
		}
		else {
			CURNUM=CURNUM+1;
			StepTime=0.0;
		}
	}
}

void CDigitShowBasicDoc::MonotonicTorsionalLoadingConstPA()
{
	//	0: Clockwise:0 / Countercloclwise:1
	//	1: sigma_zq
	//	2: gamma_zq
	//	3: Torsinal Speed
	//	4: Axial Speed
	//	5: Mean effective principal stress p' (kPa),
	//	6: tan(2*alfa),
	StepTime=StepTime+CtrlStepTime/60.0;
	DAVout[CH_AxisMotor]=5.0f;
	DAVout[CH_AxisSpeed]=float(DA_Cal_a[CH_AxisSpeed]*CFPARA[CURNUM][4]+DA_Cal_b[CH_AxisSpeed]);
	DAVout[CH_TorsionMotor]=5.0f;
	DAVout[CH_TorsionSpeed]=float(DA_Cal_a[CH_TorsionSpeed]*CFPARA[CURNUM][3]+DA_Cal_b[CH_TorsionSpeed]);

	if(CFPARA[CURNUM][0]==0.0){
		if(szq < CFPARA[CURNUM][1] && gzq1 < CFPARA[CURNUM][2])	{
			DAVout[CH_TorsionClutch] = VoltCW;
			Target_sr= (3.0*CFPARA[CURNUM][5] - 2.0*szq/CFPARA[CURNUM][6])/3.0 +ErrorStressAir;
			DAVout[CH_EP_Cell]= DAVout[CH_EP_Cell] + float(0.1*DA_Cal_a[CH_EP_Cell]*(Target_sr-sr));
			Target_sz= (3.0*CFPARA[CURNUM][5] + 4.0*szq/CFPARA[CURNUM][6])/3.0 +ErrorStressMotor;
			if(sz > Target_sz+ErrorStressMotor)	DAVout[CH_AxisClutch]=VoltUp;
			else if(sz < Target_sz-ErrorStressMotor)	DAVout[CH_AxisClutch]=VoltDown;
			else	DAVout[CH_AxisSpeed]=0.0f;
		}
		else {
			StepTime = 0.0;
			CURNUM = CURNUM + 1;
		}
	}
	else if (CFPARA[CURNUM][0] == 1.0) {
		if (szq > CFPARA[CURNUM][1] && gzq1 > CFPARA[CURNUM][2]) {
			DAVout[CH_TorsionClutch] = VoltCCW;
			Target_sr = (3.0 * CFPARA[CURNUM][5] - 2.0 * szq / CFPARA[CURNUM][6]) / 3.0 - ErrorStressAir;
			DAVout[CH_EP_Cell] = DAVout[CH_EP_Cell] + float(0.1 * DA_Cal_a[CH_EP_Cell] * (Target_sr - sr));
			Target_sz= (3.0*CFPARA[CURNUM][5] + 4.0*szq/CFPARA[CURNUM][6])/3.0 -ErrorStressMotor;
			if(sz > Target_sz+ErrorStressMotor)	DAVout[CH_AxisClutch]=VoltUp;
			else if(sz < Target_sz-ErrorStressMotor)	DAVout[CH_AxisClutch]=VoltDown;
			else	DAVout[CH_AxisSpeed]=0.0f;
		}
		else {
			StepTime=0.0;
			CURNUM=CURNUM+1;
		}
	}
}

// 2021.06.07 Edited by M.Kuno
// customize for Sanjei	
void CDigitShowBasicDoc::CyclicAxialLoading_OR()
{
	// 0: Loading:0/Unloading:1, 
	// 1: sigma_z_lower, 
	// 2: sigma_z_upper, 
	// 3: epsilon_z_lower,
	// 4: epsilon_z_upper,
	// 5: Number,
	// 6: Axial Speed
	StepTime = StepTime + CtrlStepTime / 60.0;
	DAVout[CH_AxisMotor] = 5.0f;
	DAVout[CH_AxisSpeed] = float(DA_Cal_a[CH_AxisSpeed] * CFPARA[CURNUM][6] + DA_Cal_b[CH_AxisSpeed]);
	if (CFPARA[CURNUM][0] == 0.0) {
		if (Num_Cyclic == 0) {
			Flag_Cyclic = FALSE;
			Num_Cyclic = 1;
		}
		if (Num_Cyclic != 0 && Num_Cyclic <= CFPARA[CURNUM][5]) {
			if (Flag_Cyclic == FALSE) {
				if (sz <= CFPARA[CURNUM][2] && ez <= CFPARA[CURNUM][4])	DAVout[CH_AxisClutch] = VoltDown;
				else	Flag_Cyclic = TRUE;
			}
			else {
				if (sz >= CFPARA[CURNUM][1] || ez >= CFPARA[CURNUM][3]) DAVout[CH_AxisClutch] = VoltUp;
				else {
					Flag_Cyclic = FALSE;
					Num_Cyclic = Num_Cyclic + 1;
				}
			}
		}
		if (Num_Cyclic > CFPARA[CURNUM][5]) {
			CURNUM = CURNUM + 1;
			StepTime = 0.0;
			Num_Cyclic = 0;
		}
	}
	else if (CFPARA[CURNUM][0] == 1.0) {
		if (Num_Cyclic == 0) {
			Flag_Cyclic = TRUE;
			Num_Cyclic = 1;
		}
		if (Num_Cyclic != 0 && Num_Cyclic <= CFPARA[CURNUM][2]) {
			if (Flag_Cyclic == FALSE) {
				if (sz <= CFPARA[CURNUM][2] || ez <= CFPARA[CURNUM][4])	DAVout[CH_AxisClutch] = VoltDown;
				else {
					Flag_Cyclic = TRUE;
					Num_Cyclic = Num_Cyclic + 1;
				}
			}
			else {
				if (sz >= CFPARA[CURNUM][1] && ez >= CFPARA[CURNUM][3]) DAVout[CH_AxisClutch] = VoltUp;
				else	Flag_Cyclic = FALSE;
			}
		}
		if (Num_Cyclic > CFPARA[CURNUM][5]) {
			CURNUM = CURNUM + 1;
			StepTime = 0.0;
			Num_Cyclic = 0;
		}
	}
}

void CDigitShowBasicDoc::Rs232c_Open()
{
//---Open RS232C: COM1---
	hEvent=CreateEvent(0, TRUE, FALSE, NULL);
	//Open COM1
	hComm[0] = CreateFile(CommName[0],GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
	if(hComm[0]!=INVALID_HANDLE_VALUE){
		AfxMessageBox("Succeded in open of COM1", MB_ICONINFORMATION | MB_OK );
		Flag_COM[0]=TRUE;
		GetCommState(hComm[0],&CommDCB[0]);
		CommDCB[0].fBinary=TRUE;
		CommDCB[0].fRtsControl = RTS_CONTROL_ENABLE;
		CommDCB[0].fDtrControl = DTR_CONTROL_ENABLE;
		CommDCB[0].BaudRate=CBR_2400;				// BaudRate 2400;
		CommDCB[0].ByteSize=7;						// Bit length:7bit 
		CommDCB[0].Parity=2;						// 0-4=no,odd,even,mark,space 
		CommDCB[0].StopBits=0;						// 0,1,2 = 1Bit, 1.5Bit, 2Bit 
		SetCommState(hComm[0],&CommDCB[0]);
		Flag_SetRs232c=TRUE;
	}
	ReadBuffer1.Empty();
	ReadBuffer2.Empty();
	WriteBuffer1.Empty();
	WriteBuffer2.Empty();
	TmpBuffer.Empty();
}

void CDigitShowBasicDoc::Rs232c_Close()
{
	if(Flag_SetRs232c){
		if(Flag_COM[0])	{
			CloseHandle(hComm[0]);
			Flag_COM[0]=FALSE;
		}
		Flag_SetRs232c=FALSE;
	}
	CloseHandle(hEvent);
}

void CDigitShowBasicDoc::Rs232c_SendData()
{
	DWORD	NoOfByte;
	WriteBuffer1+="\r\n";
	WriteFile(hComm[0],WriteBuffer1,WriteBuffer1.GetLength(),&NoOfByte,NULL);
//	WaitForSingleObject(hEvent,300);
//	ResetEvent(hEvent);
}

void CDigitShowBasicDoc::Rs232c_GetData()
{
	DWORD NoOfByte,Error;
	ReadBuffer1.Empty();
	ClearCommError(hComm[0],&Error,&Comstat1);
	if(Comstat1.cbInQue){
		ReadFile(hComm[0],ReadBuffer1.GetBuffer(Comstat1.cbInQue),Comstat1.cbInQue,&NoOfByte,NULL);
		ReadBuffer1.ReleaseBuffer();
	}
}

void CDigitShowBasicDoc::Rs232c_GetWeight()
{
	int		i,j;
	Rs232c_GetData();
	TmpBuffer = TmpBuffer + ReadBuffer1;
	i=TmpBuffer.Find('S',0);
	j=TmpBuffer.Find('g',i+1);
	if( i != -1 && j != -1 ){
		TmpBuffer = TmpBuffer.Mid(i+4,8);
		BW1=atof(TmpBuffer)*1000.0;
		TmpBuffer.Empty();
	}
	BW2=BW1;
}


