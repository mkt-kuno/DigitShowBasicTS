// MainFrm.cpp : CMainFrame ・ｽN・ｽ・ｽ・ｽX・ｽﾌ難ｿｽ・ｽ・ｽﾌ抵ｿｽ`・ｽ・ｽ・ｽs・ｽ・ｽ・ｽﾜゑｿｽ・ｽB
//

#include "stdafx.h"
#include "DigitShowBasic.h"
#include "DigitShowBasicDoc.h"
#include "DigitShowContext.h"

#include "MainFrm.h"
#include "BoardSettings.h"
#include "SamplingSettings.h"
#include "RS232C.h"
#include "CalibrationFactor.h"
#include "Specimen.h"
#include "Control_ID.h"
#include "Control_File.h"
#include "Control_General.h"
#include "Control_PreConsolidation.h"
#include "Control_Consolidation.h"
#include "DA_Vout.h"
#include "DA_Channel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//---Flag---

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_COMMAND(ID_DA_Vout, OnDAVout)
	ON_COMMAND(ID_DA_Channel, OnDAChannel)
	ON_COMMAND(ID_Control_File, OnControlFile)
	ON_COMMAND(ID_Consolidation, OnConsolidation)
	ON_COMMAND(ID_Control_PreConsolidation, OnControlPreConsolidation)
	ON_COMMAND(ID_Control_ID, OnControlID)
	ON_COMMAND(ID_Control_General, OnControlGeneral)
	ON_COMMAND(ID_SpecimenData, OnSpecimenData)
	ON_COMMAND(ID_Calibration_Factor, OnCalibrationFactor)
	ON_COMMAND(ID_SamplingSettings, OnSamplingSettings)
	ON_COMMAND(ID_BoardSettings, OnBoardSettings)
	ON_COMMAND(ID_Rs232cPannel, OnRs232cPannel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame ・ｽN・ｽ・ｽ・ｽX・ｽﾌ構・ｽz/・ｽ・ｽ・ｽ・ｽ

CMainFrame::CMainFrame()
{
	// TODO: ・ｽ・ｽ・ｽﾌ位置・ｽﾉ・ｿｽ・ｽ・ｽ・ｽo・ｽﾌ擾ｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽR・ｽ[・ｽh・ｽ・ｽﾇ会ｿｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽB
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ・ｽ・ｽ・ｽﾌ位置・ｽ・ｽ CREATESTRUCT cs ・ｽ・ｽ・ｽC・ｽ・ｽ・ｽ・ｽ・ｽﾄ、Window ・ｽN・ｽ・ｽ・ｽX・ｽ・ｽX・ｽ^・ｽC・ｽ・ｽ・ｽ・ｽ
	//       ・ｽC・ｽ・ｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽB

	//Get system height and widths- added later
	cs.cy = ::GetSystemMetrics(SM_CYSCREEN);
	cs.cx = ::GetSystemMetrics(SM_CXSCREEN);
	cs.y = 0;
	cs.x = 0;
	//over: Get...added later
	//If previous saved Window_size could not be read,Set default value

	cs.style ^=(LONG)FWS_ADDTOTITLE;     //Not showing title of child window in main window

	return CFrameWnd::PreCreateWindow(cs);

}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame ・ｽN・ｽ・ｽ・ｽX・ｽﾌ診・ｽf

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame ・ｽ・ｽ・ｽb・ｽZ・ｽ[・ｽW ・ｽn・ｽ・ｽ・ｽh・ｽ・ｽ

void CMainFrame::OnBoardSettings() 
{	DigitShowContext* ctx = GetContext();
	// TODO: ・ｽ・ｽ・ｽﾌ位置・ｽﾉコ・ｽ}・ｽ・ｽ・ｽh ・ｽn・ｽ・ｽ・ｽh・ｽ・ｽ・ｽp・ｽﾌコ・ｽ[・ｽh・ｽ・ｽﾇ会ｿｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
	int	nResult;
	CBoardSettings BoardSettings;
	nResult = BoardSettings.DoModal();
}

void CMainFrame::OnSamplingSettings() 
{	DigitShowContext* ctx = GetContext();
	// TODO: ・ｽ・ｽ・ｽﾌ位置・ｽﾉコ・ｽ}・ｽ・ｽ・ｽh ・ｽn・ｽ・ｽ・ｽh・ｽ・ｽ・ｽp・ｽﾌコ・ｽ[・ｽh・ｽ・ｽﾇ会ｿｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
	int	nResult;
	CSamplingSettings SamplingSettings;
	nResult = SamplingSettings.DoModal();
}

void CMainFrame::OnRs232cPannel() 
{	DigitShowContext* ctx = GetContext();
	// TODO: Add your command handler code here
	int	nResult;
	CRS232C RS232C;
	nResult = RS232C.DoModal();	
}

void CMainFrame::OnCalibrationFactor() 
{	DigitShowContext* ctx = GetContext();
	// TODO: ・ｽ・ｽ・ｽﾌ位置・ｽﾉコ・ｽ}・ｽ・ｽ・ｽh ・ｽn・ｽ・ｽ・ｽh・ｽ・ｽ・ｽp・ｽﾌコ・ｽ[・ｽh・ｽ・ｽﾇ会ｿｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
	int	nResult;
	if(ctx->flags.SetBoard==FALSE){
		AfxMessageBox("SamplingCondition has not been accomplished !",MB_ICONEXCLAMATION | MB_OK );
		return;
	}
	else{
		CCalibrationFactor CalibrationFactor;
		nResult = CalibrationFactor.DoModal();		
	}
}

void CMainFrame::OnSpecimenData() 
{	DigitShowContext* ctx = GetContext();
	// TODO: ・ｽ・ｽ・ｽﾌ位置・ｽﾉコ・ｽ}・ｽ・ｽ・ｽh ・ｽn・ｽ・ｽ・ｽh・ｽ・ｽ・ｽp・ｽﾌコ・ｽ[・ｽh・ｽ・ｽﾇ会ｿｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
	int	nResult;
	CSpecimen Specimen;
	nResult = Specimen.DoModal();		
}

void CMainFrame::OnDAChannel() 
{	DigitShowContext* ctx = GetContext();
	// TODO: ・ｽ・ｽ・ｽﾌ位置・ｽﾉコ・ｽ}・ｽ・ｽ・ｽh ・ｽn・ｽ・ｽ・ｽh・ｽ・ｽ・ｽp・ｽﾌコ・ｽ[・ｽh・ｽ・ｽﾇ会ｿｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
	int	nResult;
	CDA_Channel DA_Channel;
	nResult = DA_Channel.DoModal();	
}

void CMainFrame::OnDAVout() 
{	DigitShowContext* ctx = GetContext();
	// TODO: ・ｽ・ｽ・ｽﾌ位置・ｽﾉコ・ｽ}・ｽ・ｽ・ｽh ・ｽn・ｽ・ｽ・ｽh・ｽ・ｽ・ｽp・ｽﾌコ・ｽ[・ｽh・ｽ・ｽﾇ会ｿｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
	int	nResult;
	if(ctx->flags.SetBoard==FALSE){
		AfxMessageBox("SamplingCondition has not been accomplished !",MB_ICONEXCLAMATION | MB_OK );
		return;
	}
	CDA_Vout DA_Vout;
	nResult = DA_Vout.DoModal();		
}

void CMainFrame::OnControlID() 
{	DigitShowContext* ctx = GetContext();
	// TODO: ・ｽ・ｽ・ｽﾌ位置・ｽﾉコ・ｽ}・ｽ・ｽ・ｽh ・ｽn・ｽ・ｽ・ｽh・ｽ・ｽ・ｽp・ｽﾌコ・ｽ[・ｽh・ｽ・ｽﾇ会ｿｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
	int	nResult;
	CControl_ID CtrlIDDlg;
	nResult = CtrlIDDlg.DoModal();
}

void CMainFrame::OnControlFile() 
{	DigitShowContext* ctx = GetContext();
	// TODO: ・ｽ・ｽ・ｽﾌ位置・ｽﾉコ・ｽ}・ｽ・ｽ・ｽh ・ｽn・ｽ・ｽ・ｽh・ｽ・ｽ・ｽp・ｽﾌコ・ｽ[・ｽh・ｽ・ｽﾇ会ｿｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
	int	nResult;
	CControl_File Control_File;
	nResult = Control_File.DoModal();	
}

void CMainFrame::OnControlGeneral() 
{	DigitShowContext* ctx = GetContext();
	// TODO: ・ｽ・ｽ・ｽﾌ位置・ｽﾉコ・ｽ}・ｽ・ｽ・ｽh ・ｽn・ｽ・ｽ・ｽh・ｽ・ｽ・ｽp・ｽﾌコ・ｽ[・ｽh・ｽ・ｽﾇ会ｿｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
	int	nResult;
	CControl_General Control_General;
	nResult = Control_General.DoModal();	
}

void CMainFrame::OnControlPreConsolidation() 
{	DigitShowContext* ctx = GetContext();
	// TODO: ・ｽ・ｽ・ｽﾌ位置・ｽﾉコ・ｽ}・ｽ・ｽ・ｽh ・ｽn・ｽ・ｽ・ｽh・ｽ・ｽ・ｽp・ｽﾌコ・ｽ[・ｽh・ｽ・ｽﾇ会ｿｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
	int	nResult;
	CControl_PreConsolidation Control_PreConsolidation;
	nResult = Control_PreConsolidation.DoModal();	
}

void CMainFrame::OnConsolidation() 
{	DigitShowContext* ctx = GetContext();
	// TODO: ・ｽ・ｽ・ｽﾌ位置・ｽﾉコ・ｽ}・ｽ・ｽ・ｽh ・ｽn・ｽ・ｽ・ｽh・ｽ・ｽ・ｽp・ｽﾌコ・ｽ[・ｽh・ｽ・ｽﾇ会ｿｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
	int	nResult;
	CControl_Consolidation Control_Consolidation;
	nResult = Control_Consolidation.DoModal();	
}
