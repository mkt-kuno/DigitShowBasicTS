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
// DigitShowBasicDoc.cpp : CDigitShowBasicDoc クラスの動作の定義を行います。
//

#include	"stdafx.h"
#include	"DigitShowBasic.h"
#include	"DigitShowBasicDoc.h"
#include	"DigitShowContext.h"
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


IMPLEMENT_DYNCREATE(CDigitShowBasicDoc, CDocument)

BEGIN_MESSAGE_MAP(CDigitShowBasicDoc, CDocument)
	//{{AFX_MSG_MAP(CDigitShowBasicDoc)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDigitShowBasicDoc クラスの構築/消滅

CDigitShowBasicDoc::CDigitShowBasicDoc()
{
	DigitShowContext* ctx = GetContext();
}

CDigitShowBasicDoc::~CDigitShowBasicDoc()
{
}

BOOL CDigitShowBasicDoc::OnNewDocument()
{	DigitShowContext* ctx = GetContext();
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDigitShowBasicDoc シリアライゼーション

void CDigitShowBasicDoc::Serialize(CArchive& ar)
{	DigitShowContext* ctx = GetContext();
	if (ar.IsStoring())
	{
		// TODO: この位置に保存用のコードを追加してください。
	}
	else
	{
		// TODO: この位置に読み込み用のコードを追加してください。
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDigitShowBasicDoc クラスの診断

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
// CDigitShowBasicDoc コマンド
void CDigitShowBasicDoc::OpenBoard()
{	DigitShowContext* ctx = GetContext();
	int	i;
	if( ctx->flags.SetBoard ){
		AfxMessageBox("Initialization has been already accomplished", MB_ICONSTOP | MB_OK );
		return;
	}
	else{
		// OPEN A/D BOARDS.
		if(ctx->NumAD > 0 ){
			ctx->Ret = AioInit ( "AIO000" , &ctx->ad[0].Id );
		    if(ctx->Ret != 0){
			    ctx->Ret2 = AioGetErrorString(ctx->Ret, ctx->ErrorString);
				ctx->TextString.Format("AioInit = %d : %s", ctx->Ret, ctx->ErrorString);
				AfxMessageBox(ctx->TextString, MB_ICONSTOP | MB_OK );
				return;
			}
			else{
				ctx->Ret = AioResetDevice(ctx->ad[0].Id);
			    if(ctx->Ret != 0){
				    ctx->Ret2 = AioGetErrorString(ctx->Ret, ctx->ErrorString);
					ctx->TextString.Format("AioResetDevice = %d : %s", ctx->Ret, ctx->ErrorString);
					AfxMessageBox(ctx->TextString, MB_ICONSTOP | MB_OK );
					return;
				}
			}
		}
		if(ctx->NumAD > 1 ){
			ctx->Ret = AioInit ( "AIO000" , &ctx->ad[1].Id );
		    if(ctx->Ret != 0){
				ctx->Ret2 = AioGetErrorString(ctx->Ret, ctx->ErrorString);
				ctx->TextString.Format("AioInit = %d : %s", ctx->Ret, ctx->ErrorString);
				AfxMessageBox(ctx->TextString, MB_ICONSTOP | MB_OK );
				return;
			}
			else{
				ctx->Ret = AioResetDevice(ctx->ad[1].Id);
			    if(ctx->Ret != 0){
					ctx->Ret2 = AioGetErrorString(ctx->Ret, ctx->ErrorString);
					ctx->TextString.Format("AioResetDevice = %d : %s", ctx->Ret, ctx->ErrorString);
					AfxMessageBox(ctx->TextString, MB_ICONSTOP | MB_OK );
					return;
				}
			}
		}
		// OPEN D/A BOARDS.
		if(ctx->NumDA > 0){
			ctx->Ret = AioInit ( "AIO001" , &ctx->da[0].Id );
		    if(ctx->Ret != 0){
			    ctx->Ret2 = AioGetErrorString(ctx->Ret, ctx->ErrorString);
				ctx->TextString.Format("AioInit = %d : %s", ctx->Ret, ctx->ErrorString);
				AfxMessageBox(ctx->TextString, MB_ICONSTOP | MB_OK );
				return;
			}
			else{
				ctx->Ret = AioResetDevice(ctx->da[0].Id);
			    if(ctx->Ret != 0){
				    ctx->Ret2 = AioGetErrorString(ctx->Ret, ctx->ErrorString);
					ctx->TextString.Format("AioResetDevice = %d : %s", ctx->Ret, ctx->ErrorString);
					AfxMessageBox(ctx->TextString, MB_ICONSTOP | MB_OK );
					return;
				}
			}
		}
		// Set Sampling Condition
		ctx->AdMaxCH=0;
		for(i=0;i<ctx->NumAD;i++){
			ctx->Ret = AioGetAiInputMethod ( ctx->ad[i].Id , &ctx->ad[i].InputMethod );
			ctx->Ret = AioGetAiResolution ( ctx->ad[i].Id , &ctx->ad[i].Resolution );
			ctx->Ret = AioGetAiMaxChannels ( ctx->ad[i].Id , &ctx->ad[i].Channels );
			ctx->Ret = AioSetAiChannels ( ctx->ad[i].Id , ctx->ad[i].Channels );
			ctx->Ret = AioGetAiChannels ( ctx->ad[i].Id , &ctx->ad[i].Channels );
			ctx->AdMaxCH=ctx->AdMaxCH+ctx->ad[i].Channels;
//			ctx->Ret = AioSetAiRangeAll ( ctx->ad[i].Id, 1 );	// (-5V, 5V)
			ctx->Ret = AioSetAiRangeAll ( ctx->ad[i].Id, 0 );	// (-10V, 10V)
			ctx->Ret = AioGetAiRange ( ctx->ad[i].Id , 0 , &ctx->ad[i].Range );
			ctx->Ret = GetRangeValue(ctx->ad[i].Range, &ctx->ad[i].RangeMax, &ctx->ad[i].RangeMin);
			ctx->Ret = AioGetAiMemoryType ( ctx->ad[i].Id , &ctx->ad[i].MemoryType );
			ctx->Ret = AioGetAiScanClock ( ctx->ad[i].Id , &ctx->ad[i].ScanClock );
			ctx->Ret = AioGetAiSamplingClock ( ctx->ad[i].Id , &ctx->ad[i].SamplingClock );
			ctx->Ret = AioGetAiEventSamplingTimes ( ctx->ad[i].Id , &ctx->ad[i].SamplingTimes );
		}
		ctx->SavingTime=300;
		ctx->TotalSamplingTimes=long(ctx->SavingTime*1000000/ctx->ad[0].SamplingClock);
		ctx->AllocatedMemory=4*ctx->AdMaxCH*ctx->TotalSamplingTimes/1024.0f/1024.0f;
		ctx->AvSmplNum=10;
		for(i=0;i<ctx->NumDA;i++){
			ctx->Ret = AioGetAoResolution ( ctx->da[i].Id , &ctx->da[i].Resolution );
			ctx->Ret = AioGetAoMaxChannels ( ctx->da[i].Id , &ctx->da[i].Channels );
//			ctx->Ret = AioSetAoRangeAll ( ctx->da[i].Id , 50 );	// 0 - 10V
			ctx->Ret = AioGetAoRange ( ctx->da[i].Id , 0 , &ctx->da[i].Range );
			ctx->Ret = GetRangeValue(ctx->da[i].Range, &ctx->da[i].RangeMax, &ctx->da[i].RangeMin);
		}
		ctx->flags.SetBoard=TRUE;
	}
	return;}

void CDigitShowBasicDoc::CloseBoard()
{	DigitShowContext* ctx = GetContext();
	// Close A/D and D/A board to end the application 
	if(ctx->flags.SetBoard){
		if(ctx->NumAD > 0)	ctx->Ret = AioExit(ctx->ad[0].Id);
		if(ctx->Ret != 0){
		    ctx->Ret2 = AioGetErrorString(ctx->Ret, ctx->ErrorString);
			ctx->TextString.Format("AioExit = %d : %s", ctx->Ret, ctx->ErrorString);
			AfxMessageBox(ctx->TextString, MB_ICONSTOP | MB_OK );
			return;	
		}
		if(ctx->NumAD > 1)	ctx->Ret = AioExit(ctx->ad[1].Id);
		if(ctx->Ret != 0){
		    ctx->Ret2 = AioGetErrorString(ctx->Ret, ctx->ErrorString);
			ctx->TextString.Format("AioExit = %d : %s", ctx->Ret, ctx->ErrorString);
			AfxMessageBox(ctx->TextString, MB_ICONSTOP | MB_OK );
			return;	
		}
		if(ctx->NumDA > 0)	ctx->Ret = AioExit(ctx->da[0].Id);
		if(ctx->Ret != 0){
		    ctx->Ret2 = AioGetErrorString(ctx->Ret, ctx->ErrorString);
			ctx->TextString.Format("AioExit = %d : %s", ctx->Ret, ctx->ErrorString);
			AfxMessageBox(ctx->TextString, MB_ICONSTOP | MB_OK );
			return;	
		}
	}
}

//--- Input from A/D Board ---
void CDigitShowBasicDoc::AD_INPUT()
{	DigitShowContext* ctx = GetContext();
	int	i,j,k;
	k=0;
	if(ctx->NumAD>0){
		for(i=0;i<ctx->ad[0].Channels;i++){
			ctx->ai.raw[k]=0.0f;
			for(j=0;j<ctx->AvSmplNum;j++){
				ctx->ai.raw[k] = ctx->ai.raw[k]+BinaryToVolt(ctx->ad[0].RangeMax, ctx->ad[0].RangeMin, ctx->ad[0].Resolution, ctx->AdData0[ctx->ad[0].Channels*j+i])/float(ctx->AvSmplNum);
			}
			k=k+1;
		}
	}
	if(ctx->NumAD>1){
		for(i=0;i<ctx->ad[1].Channels;i++){
			ctx->ai.raw[k]=0.0f;
			for(j=0;j<ctx->AvSmplNum;j++){
				ctx->ai.raw[k] = ctx->ai.raw[k]+BinaryToVolt(ctx->ad[1].RangeMax, ctx->ad[1].RangeMin, ctx->ad[1].Resolution, ctx->AdData1[ctx->ad[1].Channels*j+i])/float(ctx->AvSmplNum);
			}
			k=k+1;
		}
	}
}
//--- Output to D/A Board ---
void CDigitShowBasicDoc::DA_OUTPUT()
{	DigitShowContext* ctx = GetContext();
	int	i,j,k;
	k=0;
	for(i=0;i<ctx->NumDA;i++){
		for(j=0;j<ctx->da[i].Channels;j++){
			if(ctx->ao.raw[k]>9.999f) ctx->ao.raw[k]=9.999f;
			if(ctx->ao.raw[k]<0.0f) ctx->ao.raw[k]=0.0f;
			ctx->DaData[j] = VoltToBinary(ctx->da[i].RangeMax, ctx->da[i].RangeMin, ctx->da[i].Resolution, ctx->ao.raw[k]);
			k=k+1;
		}
		ctx->Ret = AioMultiAo(ctx->da[i].Id, ctx->da[i].Channels, &ctx->DaData[0]);
	}
}
//--- Calcuration of Physical Value ---
void CDigitShowBasicDoc::Cal_Physical()
{	DigitShowContext* ctx = GetContext();
	int	i;
	for(i=0;i<32;i++){
		ctx->ai.phy[i]=	ctx->ai.cal.a[i]*ctx->ai.raw[i]*ctx->ai.raw[i] + ctx->ai.cal.b[i]*ctx->ai.raw[i] + ctx->ai.cal.c[i];
	}
}

//--- Calcuration of the Other Parameters ---
void CDigitShowBasicDoc::Cal_Param()
{	DigitShowContext* ctx = GetContext();
 	//---Calculation of Parameter Data--- 
	//Current specimen size
	if(ctx->flags.SetBalance == FALSE) ctx->phys.BW2 = ctx->ai.phy[13];	// Volume change from LCDPT
	ctx->phys.height=ctx->specimen.Height[0]-ctx->ai.phy[5];
	ctx->phys.volume=ctx->specimen.Volume[0]-ctx->phys.BW2;
	ctx->phys.area=ctx->phys.volume/ctx->phys.height;
	ctx->phys.rotation1=ctx->ai.phy[2];
	ctx->phys.rotation2=ctx->ai.phy[3];
	ctx->phys.diameter_in=ctx->specimen.DiameterIn[0]*sqrt((1-ctx->phys.BW2/ctx->specimen.Volume[0])/(1-ctx->ai.phy[5]/ctx->specimen.Height[0]));
	ctx->phys.diameter_out=ctx->specimen.DiameterOut[0]*sqrt((1-ctx->phys.BW2/ctx->specimen.Volume[0])/(1-ctx->ai.phy[5]/ctx->specimen.Height[0]));
	//ctx->phys.diameterInM=ctx->phys.diameter_in+ctx->specimen.MembraneThickness/2.0; //@note Hashimoto fixed 2022.12.22
	ctx->phys.diameterInM = ctx->phys.diameter_in - ctx->specimen.MembraneThickness / 2.0;
	ctx->phys.diameterOutM=ctx->phys.diameter_out+ctx->specimen.MembraneThickness/2.0;
	ctx->phys.heightInM=ctx->specimen.HeightInMembrane[0]-ctx->ai.phy[5];
	ctx->phys.heightOutM=ctx->specimen.HeightOutMembrane[0]-ctx->ai.phy[5];
	//Strain in specimen
	ctx->phys.ez=ctx->ai.phy[5]/ctx->specimen.Height[0];
	ctx->phys.er=-((ctx->phys.diameter_out-ctx->specimen.DiameterOut[0])-(ctx->phys.diameter_in-ctx->specimen.DiameterIn[0]))/(ctx->phys.diameter_out-ctx->phys.diameter_in);
	ctx->phys.eq=-((ctx->phys.diameter_out-ctx->specimen.DiameterOut[0])+(ctx->phys.diameter_in-ctx->specimen.DiameterIn[0]))/(ctx->phys.diameter_out+ctx->phys.diameter_in);
	ctx->phys.gzq1=ctx->phys.rotation1*(pow(ctx->phys.diameter_out,3.0)-pow(ctx->phys.diameter_in, 3.0))/3.0/ctx->phys.height/(pow(ctx->phys.diameter_out, 2.0)-pow(ctx->phys.diameter_in, 2.0));	
	ctx->phys.gzq2=ctx->phys.rotation2*(pow(ctx->phys.diameter_out,3.0)-pow(ctx->phys.diameter_in, 3.0))/3.0/ctx->phys.height/(pow(ctx->phys.diameter_out, 2.0)-pow(ctx->phys.diameter_in, 2.0));
	ctx->phys.ev=ctx->phys.BW2/ctx->specimen.Volume[0];
	// Strain in membrane sleeve
	ctx->phys.ezInM=(ctx->specimen.RHeightInM-ctx->phys.heightInM)/ctx->specimen.RHeightInM;
	ctx->phys.ezOutM=(ctx->specimen.RHeightOutM-ctx->phys.heightOutM)/ctx->specimen.RHeightOutM;
	ctx->phys.eqInM=(ctx->specimen.RDiaInM-ctx->phys.diameterInM)/ctx->specimen.RDiaInM;
	ctx->phys.eqOutM=(ctx->specimen.RDiaOutM-ctx->phys.diameterOutM)/ctx->specimen.RDiaOutM;
	//ctx->phys.gzqInM=ctx->phys.diameter_in*ctx->phys.rotation1/ctx->specimen.RHeightInM;
	//ctx->phys.gzqOutM=ctx->phys.diameter_out*ctx->phys.rotation1/ctx->specimen.RHeightOutM;
	ctx->phys.gzqInM = ctx->phys.diameterInM / 2.0 * ctx->phys.rotation1 / ctx->specimen.RHeightInM; //@note Hashimoto modified 2022.2.28
	ctx->phys.gzqOutM = ctx->phys.diameterOutM / 2.0 * ctx->phys.rotation1 / ctx->specimen.RHeightOutM; //@note Hashimoto modified 2022.2.28
	//Membrane force 
	//@note Hashimoto modified 2022.12.28 (only considering ctx->phys.TorqueM)
	//ctx->phys.PressureInM=4.0/3.0*ctx->specimen.MembraneModulus*ctx->specimen.MembraneThickness*(ctx->phys.ezInM+2.0*ctx->phys.eqInM)/ctx->phys.diameter_in;
	//ctx->phys.PressureOutM=-4.0/3.0*ctx->specimen.MembraneModulus*ctx->specimen.MembraneThickness*(ctx->phys.ezOutM+2.0*ctx->phys.eqOutM)/ctx->phys.diameter_out;
	//ctx->phys.ForceM=-2.0/3.0*3.141592*ctx->specimen.MembraneModulus*ctx->specimen.MembraneThickness*(ctx->phys.diameter_in*(2.0*ctx->phys.ezInM+ctx->phys.eqInM)+ctx->phys.diameter_out*(2.0*ctx->phys.ezOutM+ctx->phys.eqOutM))/1000.0;
	ctx->phys.TorqueM=-1.0/6.0*3.141592*ctx->specimen.MembraneModulus*ctx->specimen.MembraneThickness*(pow(ctx->phys.diameter_in, 2.0)*ctx->phys.gzqInM+pow(ctx->phys.diameter_out, 2.0)*ctx->phys.gzqOutM)/1000000.0;
	ctx->phys.PressureInM = 0.0;
	ctx->phys.PressureOutM = 0.0;
	ctx->phys.ForceM = 0.0;

	// Adjusted Force and Pressure
	ctx->ai.phy[0]=ctx->ai.phy[0]+ctx->phys.ForceM+ctx->specimen.CapWeight;
	ctx->ai.phy[1]=ctx->ai.phy[1]+ctx->phys.TorqueM*100.0;
	ctx->phys.cell_out=ctx->ai.phy[4]+ctx->phys.PressureOutM;
	ctx->phys.cell_in=ctx->ai.phy[4]+ctx->phys.PressureInM;
	//Stress
	ctx->phys.sz=(ctx->ai.phy[0]+3.141592/4.0*(ctx->phys.cell_out*pow(ctx->phys.diameter_out, 2.0)-ctx->phys.cell_in*pow(ctx->phys.diameter_in, 2.0))/1000.0)/ctx->phys.area*1000.0;
	ctx->phys.sr=(ctx->phys.cell_out*ctx->phys.diameter_out+ctx->phys.cell_in*ctx->phys.diameter_in)/(ctx->phys.diameter_out+ctx->phys.diameter_in);
	ctx->phys.sq=(ctx->phys.cell_out*ctx->phys.diameter_out-ctx->phys.cell_in*ctx->phys.diameter_in)/(ctx->phys.diameter_out-ctx->phys.diameter_in);
	ctx->phys.szq=4.0*(ctx->ai.phy[1]/100.0)/3.141592*(3.0/2.0/(pow(ctx->phys.diameter_out, 3.0)-pow(ctx->phys.diameter_in, 3.0))+1.0/(pow(ctx->phys.diameter_out, 2.0)+pow(ctx->phys.diameter_in, 2.0))/(ctx->phys.diameter_out-ctx->phys.diameter_in))*1000000.0;
	ctx->phys.p=(ctx->phys.sz+ctx->phys.sr+ctx->phys.sq)/3.0;
	ctx->phys.q=ctx->phys.sz-ctx->phys.sr;
	//---The Value to display---
	ctx->ai.param[0]=ctx->phys.sz;
	ctx->ai.param[1]=ctx->phys.sr;
	ctx->ai.param[2]=ctx->phys.sq;
	ctx->ai.param[3]=ctx->phys.szq;
	ctx->ai.param[4]=ctx->phys.ev*100.0;
	ctx->ai.param[5]=ctx->phys.ez*100.0;
	ctx->ai.param[6]=ctx->ai.phy[6]; // LDT1
	ctx->ai.param[7]=ctx->ai.phy[11]; // LDT2
	ctx->ai.param[8]=ctx->ai.phy[8]; // CG1
	ctx->ai.param[9]=ctx->ai.phy[9]; // CG2
	ctx->ai.param[10]=ctx->ai.phy[10]; // CG3
	ctx->ai.param[11] = ctx->phys.p;
	ctx->ai.param[12] = ctx->phys.q;
	ctx->ai.param[13] = (ctx->phys.sz + ctx->phys.sq) / 2.0 + sqrt((ctx->phys.sz - ctx->phys.sq) * (ctx->phys.sz - ctx->phys.sq) / 4 + ctx->phys.szq * ctx->phys.szq); // sigma 1
	ctx->ai.param[14] = ctx->phys.sr; // sigma 2
	ctx->ai.param[15] = (ctx->phys.sz + ctx->phys.sq) / 2.0 - sqrt((ctx->phys.sz - ctx->phys.sq) * (ctx->phys.sz - ctx->phys.sq) / 4 + ctx->phys.szq * ctx->phys.szq); // sigma 3
	ctx->ai.param[16] = ctx->phys.gzq1 * 100.0;
	ctx->ai.param[17] = ctx->phys.gzq2 * 100.0;
	//ctx->ai.param[9]=ctx->phys.gzq1*100.0;
	//ctx->ai.param[10]=ctx->phys.gzq2*100.0;
	//ctx->ai.param[11]=ctx->ai.phy[10];
	//ctx->ai.param[12]=ctx->phys.p;
	//ctx->ai.param[13]=ctx->phys.q;
	//ctx->ai.param[14]=(ctx->phys.sz+ctx->phys.sq)/2.0+sqrt((ctx->phys.sz-ctx->phys.sq)*(ctx->phys.sz-ctx->phys.sq)/4+ctx->phys.szq*ctx->phys.szq);
	//ctx->ai.param[15]=ctx->phys.sr;
	//ctx->ai.param[16]=(ctx->phys.sz+ctx->phys.sq)/2.0-sqrt((ctx->phys.sz-ctx->phys.sq)*(ctx->phys.sz-ctx->phys.sq)/4+ctx->phys.szq*ctx->phys.szq);
	//ctx->ai.param[17]=atan2(ctx->phys.szq,(ctx->phys.sz-ctx->phys.sq)/2.0);
	//ctx->ai.param[17] = 0.5 * atan2(ctx->phys.szq, (ctx->phys.sz - ctx->phys.sq) / 2.0);  //@note Hashimoto modified 2022.12.22
	ctx->ai.param[18]=ctx->phys.cell_in;
	ctx->ai.param[19]=ctx->phys.cell_out;
	ctx->ai.param[20]=ctx->phys.diameter_in;
	ctx->ai.param[21]=ctx->phys.diameter_out;
	//ctx->ai.param[22]=ctx->ai.phy[9];
	//ctx->ai.param[23]=ctx->ai.phy[12];
	ctx->ai.param[22] = ctx->phys.height;
	ctx->ai.param[23] = ctx->phys.volume;

	// 2021.12.07 Edited by M.Kuno
	ctx->StepDisplay = ctx->controlFile.CurrentNum;
}
//--- Save the data to File ---
void CDigitShowBasicDoc::SaveToFile()
{	DigitShowContext* ctx = GetContext();
	// Save Voltage and Physical Data
	int	i,j,k;
	k=0;
	fprintf(ctx->FileSaveData0,"%.3lf	",ctx->SequentTime2);
	fprintf(ctx->FileSaveData1,"%.3lf	",ctx->SequentTime2);
	for(i=0;i<ctx->NumAD;i++){
		for(j=0;j<ctx->ad[i].Channels;j++){
			fprintf(ctx->FileSaveData0,"%lf	",ctx->ai.raw[k]);
			fprintf(ctx->FileSaveData1,"%lf	",ctx->ai.phy[k]);
			k=k+1;
		}
	}
	fprintf(ctx->FileSaveData0,"\n");
	fprintf(ctx->FileSaveData1,"\n");
	// Save Parameter Data
	fprintf(ctx->FileSaveData2,"%.3lf	",ctx->SequentTime2);	
	for(i=0;i<24;i++){
		fprintf(ctx->FileSaveData2,"%lf	",ctx->ai.param[i]);
	}
	// 2021.12.07 Edited by M.Kuno
	fprintf(ctx->FileSaveData2, "%d	", ctx->StepDisplay);
	fprintf(ctx->FileSaveData2, "%d	", ctx->NumCyclic);
	fprintf(ctx->FileSaveData2,"\n");
}

void CDigitShowBasicDoc::SaveToFile2()
{	DigitShowContext* ctx = GetContext();
	int	i,j,k;
	float	Vtmp;
	double	Ptmp;
	for(i=0;i<ctx->CurrentSamplingTimes;i++){
		k=0;
		fprintf(ctx->FileSaveData0,"%.3lf	",ctx->SavingClock/1000000.0*i);
		fprintf(ctx->FileSaveData1,"%.3lf	",ctx->SavingClock/1000000.0*i);
		if(ctx->NumAD>0){
			for(j=0;j<ctx->ad[0].Channels;j++){
				Vtmp = BinaryToVolt(ctx->ad[0].RangeMax, ctx->ad[0].RangeMin, ctx->ad[0].Resolution, *((PLONG)ctx->pSmplData[0]+i*ctx->ad[0].Channels+j));
				Ptmp = ctx->ai.cal.a[k]*Vtmp*Vtmp+ctx->ai.cal.b[k]*Vtmp+ctx->ai.cal.c[k];
				k=k+1;
				fprintf(ctx->FileSaveData0,"%lf	",Vtmp);
				fprintf(ctx->FileSaveData1,"%lf	",Ptmp);
			}
		}
		if(ctx->NumAD>1){
			for(j=0;j<ctx->ad[1].Channels;j++){
				Vtmp = BinaryToVolt(ctx->ad[1].RangeMax, ctx->ad[1].RangeMin, ctx->ad[1].Resolution, *((PLONG)ctx->pSmplData[1]+i*ctx->ad[1].Channels+j));
				Ptmp = ctx->ai.cal.a[k]*Vtmp*Vtmp+ctx->ai.cal.b[k]*Vtmp+ctx->ai.cal.c[k];
				k=k+1;
				fprintf(ctx->FileSaveData0,"%lf	",Vtmp);
				fprintf(ctx->FileSaveData1,"%lf	",Ptmp);
			}
		}
		fprintf(ctx->FileSaveData0,"\n");
		fprintf(ctx->FileSaveData1,"\n");
	}
}

void CDigitShowBasicDoc::Allocate_Memory()
{	DigitShowContext* ctx = GetContext();
	if(ctx->flags.SaveData){
		if(ctx->NumAD>0){
			ctx->hHeap[0] = GetProcessHeap();
			ctx->pSmplData[0] = HeapAlloc(ctx->hHeap[0],HEAP_ZERO_MEMORY,unsigned long(ctx->TotalSamplingTimes*ctx->ad[0].Channels*sizeof(LONG)));
		}
		if(ctx->NumAD>1){
			ctx->hHeap[1] = GetProcessHeap();
			ctx->pSmplData[1] = HeapAlloc(ctx->hHeap[1],HEAP_ZERO_MEMORY,unsigned long(ctx->TotalSamplingTimes*ctx->ad[1].Channels*sizeof(LONG)));
		}
	}
	else{
		if(ctx->NumAD>0)	HeapFree(ctx->hHeap[0],0,ctx->pSmplData[0]);
		if(ctx->NumAD>1)	HeapFree(ctx->hHeap[1],0,ctx->pSmplData[1]);
	}
}

//--- Control Statements ---
void CDigitShowBasicDoc::Control_DA()
{	DigitShowContext* ctx = GetContext();
	switch (ctx->ControlID)
	{
	case 0:
		{ 
		}
		break;
	case 1:
		{ 
			// Pre-Consolidation Process
			// ctx->control[1].AxisSpeed:	Maximum Speed
			// ctx->control[1].q:			Deviator stress when the motor speed become the max. value;
			// ctx->control[1].sigma[1]:		Target of Cell Pressure
			// ctx->control[1].sigmaRate[1]: Increment Rate of Cell Pressure 
			if( ctx->control[1].sigma[1] > 0.0 && ctx->control[1].sigmaRate[1] > 0.0 ){
				if(ctx->phys.sr <= ctx->control[1].sigma[1]-ctx->err.StressAir)		ctx->ao.raw[ctx->daCh.EP_Cell]=ctx->ao.raw[ctx->daCh.EP_Cell]+float(ctx->ao.cal.a[ctx->daCh.EP_Cell]*ctx->control[1].sigmaRate[1]*ctx->timeSettings.Interval2/1000.0/60.0);
				else if(ctx->phys.sr >= ctx->control[1].sigma[1]+ctx->err.StressAir)	ctx->ao.raw[ctx->daCh.EP_Cell]=ctx->ao.raw[ctx->daCh.EP_Cell]-float(ctx->ao.cal.a[ctx->daCh.EP_Cell]*ctx->control[1].sigmaRate[1]*ctx->timeSettings.Interval2/1000.0/60.0);
				else{
					ctx->target.sr=ctx->control[1].sigma[1];
					ctx->ao.raw[ctx->daCh.EP_Cell]=ctx->ao.raw[ctx->daCh.EP_Cell]+float(0.2*ctx->ao.cal.a[ctx->daCh.EP_Cell]*(ctx->target.sr-ctx->phys.sr));
				}
			}
			
			// Axial control
			ctx->ao.raw[ctx->daCh.AxisMotor]=5.0f;			// Motor: On
			if( ctx->phys.q > ctx->err.StressMotor ){
				ctx->ao.raw[ctx->daCh.AxisClutch]=ctx->volt.Up;	// Clutch: Unloading
				if( ctx->phys.q > ctx->control[1].q[0] )	ctx->ao.raw[ctx->daCh.AxisSpeed]=float(ctx->ao.cal.a[ctx->daCh.AxisSpeed]*ctx->control[1].AxisSpeed+ctx->ao.cal.b[ctx->daCh.AxisSpeed]);
				if( ctx->phys.q <= ctx->control[1].q[0] )	ctx->ao.raw[ctx->daCh.AxisSpeed]=float(ctx->ao.cal.a[ctx->daCh.AxisSpeed]*(ctx->phys.q/ctx->control[1].q[0])*ctx->control[1].AxisSpeed+ctx->ao.cal.b[ctx->daCh.AxisSpeed]);
			}
			else if( ctx->phys.q < -ctx->err.StressMotor ){
				ctx->ao.raw[ctx->daCh.AxisClutch]=ctx->volt.Down;		// Clutch: loading
				if( ctx->phys.q < -ctx->control[1].q[0] )	ctx->ao.raw[ctx->daCh.AxisSpeed]=float(ctx->ao.cal.a[ctx->daCh.AxisSpeed]*ctx->control[1].AxisSpeed+ctx->ao.cal.b[ctx->daCh.AxisSpeed]);
				if( ctx->phys.q >= -ctx->control[1].q[0] )	ctx->ao.raw[ctx->daCh.AxisSpeed]=float(ctx->ao.cal.a[ctx->daCh.AxisSpeed]*(-ctx->phys.q/ctx->control[1].q[0])*ctx->control[1].AxisSpeed+ctx->ao.cal.b[ctx->daCh.AxisSpeed]);
			}
			else {
				ctx->ao.raw[ctx->daCh.AxisSpeed]=0.0f;	// RPM->0
			}

			// Torque control @note Hashimoto modified 2022.12
			//float torsional_speed = 10.f; //10[RPM]
			//ctx->ao.raw[ctx->daCh.TorsionMotor] = 5.0f;			// Motor: On
			//ctx->target.tzq = 0;
			//if (ctx->phys.szq > ctx->target.tzq + ctx->err.StressMotor) {
			//	ctx->ao.raw[ctx->daCh.TorsionSpeed] = float(ctx->ao.cal.a[ctx->daCh.TorsionSpeed] * torsional_speed + ctx->ao.cal.b[ctx->daCh.TorsionSpeed]);
			//	ctx->ao.raw[ctx->daCh.TorsionClutch] = ctx->volt.CCW;
			//}
			//else if (ctx->phys.szq < ctx->target.tzq - ctx->err.StressMotor) {
			//	ctx->ao.raw[ctx->daCh.TorsionSpeed] = float(ctx->ao.cal.a[ctx->daCh.TorsionSpeed] * torsional_speed + ctx->ao.cal.b[ctx->daCh.TorsionSpeed]);
			//	ctx->ao.raw[ctx->daCh.TorsionClutch] = ctx->volt.CW;
			//}
			//else {
			//	ctx->ao.raw[ctx->daCh.TorsionSpeed] = 0.0f;
			//}

			DA_OUTPUT();
		}
		break;
	case 2:
		{ 
			// Consolidation Process
			// ctx->control[2].sigma[0]:		Axial effective stress
			// ctx->control[2].K0:			K0 value
			// ctx->control[2].AxisSpeed		Axial motor speed (RPM)
			// ctx->control[2].sigmaRate[2]: Increment rate of cell pressure
			if( ctx->control[2].sigmaRate[2] > 0.0 ){
				if( ctx->phys.sr < ctx->control[2].sigma[0]*ctx->control[2].K0 - ctx->err.StressAir){
					ctx->ao.raw[ctx->daCh.EP_Cell]=ctx->ao.raw[ctx->daCh.EP_Cell]+float(ctx->ao.cal.a[ctx->daCh.EP_Cell]*ctx->control[2].sigmaRate[2]/60.0*ctx->timeSettings.Interval2/1000.0);
				}	
				if( ctx->phys.sr > ctx->control[2].sigma[0]*ctx->control[2].K0 + ctx->err.StressAir){
					ctx->ao.raw[ctx->daCh.EP_Cell]=ctx->ao.raw[ctx->daCh.EP_Cell]-float(ctx->ao.cal.a[ctx->daCh.EP_Cell]*ctx->control[2].sigmaRate[2]/60.0*ctx->timeSettings.Interval2/1000.0);
				}
			}
			if( ctx->control[2].K0 != 0.0 ){
				ctx->target.sz = ctx->phys.sr / ctx->control[2].K0;
				ctx->ao.raw[ctx->daCh.AxisMotor] = 5.0f;			// Motor: On
				ctx->ao.raw[ctx->daCh.AxisSpeed] = float(ctx->ao.cal.a[ctx->daCh.AxisSpeed]*ctx->control[2].AxisSpeed+ctx->ao.cal.b[ctx->daCh.AxisSpeed]);
				if( ctx->phys.sz > ctx->target.sz + ctx->err.StressMotor )			ctx->ao.raw[ctx->daCh.AxisClutch]=ctx->volt.Up;	// Clutch: Unloading
				else if( ctx->phys.sz < ctx->target.sz - ctx->err.StressMotor )	ctx->ao.raw[ctx->daCh.AxisClutch]=ctx->volt.Down;	// Clutch: loading
				else											ctx->ao.raw[ctx->daCh.AxisSpeed]=0.0f;	// RPM->0
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
			if( ctx->controlFile.Num[ctx->controlFile.CurrentNum]==0 ){
				// 2023.11.29 Edited by Hashimoto
				// stop any loading if control Number is 0
				ctx->ao.raw[ctx->daCh.AxisMotor] = 0.0f;
				ctx->ao.raw[ctx->daCh.AxisSpeed] = 0.0f;
				ctx->ao.raw[ctx->daCh.TorsionMotor] = 0.0f;
				ctx->ao.raw[ctx->daCh.TorsionSpeed] = 0.0f;
			}
			else if( ctx->controlFile.Num[ctx->controlFile.CurrentNum]==1 ) EffectiveStressPathLoading();
			else if( ctx->controlFile.Num[ctx->controlFile.CurrentNum]==2 ) MonotonicTorsionalLoading();
			else if( ctx->controlFile.Num[ctx->controlFile.CurrentNum]==3 ) MonotonicTorsionalLoadingCNS();
			else if( ctx->controlFile.Num[ctx->controlFile.CurrentNum]==4 ) CyclicTorsionalLoading();
			else if( ctx->controlFile.Num[ctx->controlFile.CurrentNum]==5 ) CyclicTorsionalLoadingCNS();
			else if( ctx->controlFile.Num[ctx->controlFile.CurrentNum]==6 ) SmallCyclicTorsionalLoading();
			else if( ctx->controlFile.Num[ctx->controlFile.CurrentNum]==7 ) SmallCyclicTorsionalLoadingCNS();
			else if( ctx->controlFile.Num[ctx->controlFile.CurrentNum]==8 ) MonotonicAxialLoading();
			else if( ctx->controlFile.Num[ctx->controlFile.CurrentNum]==9 ) CyclicAxialLoading();
			else if( ctx->controlFile.Num[ctx->controlFile.CurrentNum]==10) SmallCyclicAxialLoading();
			else if( ctx->controlFile.Num[ctx->controlFile.CurrentNum]==11) Creep();
			// 2021.06.07 Edited by M.Kuno
			// customize for Sanjei
			else if( ctx->controlFile.Num[ctx->controlFile.CurrentNum]==12) MonotonicAxialLoadingConstP();
			else if( ctx->controlFile.Num[ctx->controlFile.CurrentNum]==13) MonotonicTorsionalLoadingConstPA();
			else if (ctx->controlFile.Num[ctx->controlFile.CurrentNum]==14) CyclicAxialLoading_OR();
			else if (ctx->controlFile.Num[ctx->controlFile.CurrentNum] == 15) FileControlableConsolidation();
			DA_OUTPUT();
		}
		break;
	}
}

void CDigitShowBasicDoc::Start_Control()
{	DigitShowContext* ctx = GetContext();

}

void CDigitShowBasicDoc::Stop_Control()
{	DigitShowContext* ctx = GetContext();
	ctx->ao.raw[ctx->daCh.AxisMotor]=0.0f;
	ctx->ao.raw[ctx->daCh.AxisSpeed]=0.0f;
	ctx->ao.raw[ctx->daCh.TorsionMotor]=0.0f;
	ctx->ao.raw[ctx->daCh.TorsionSpeed]=0.0f;
	DA_OUTPUT();
}

void CDigitShowBasicDoc::FileControlableConsolidation()
{	DigitShowContext* ctx = GetContext();
	// 0: sigma_z_ini, 
	// 1: sigma_r_ini, 
	// 2: tau_zq_ini, 
	// 3: sigma_z_end, 
	// 4: sigma_r_end, 
	// 5: tau_zq_end.
	// 6: Axial Motor Speed	(RPM)
	// 7: Torsion Motor Speed (RPM)
	// 8: Cell Pressure Rate (min/kPa)
	ctx->StepTime = ctx->StepTime + ctx->CtrlStepTime / 60.0;
	
	if (ctx->controlFile.Para[ctx->controlFile.CurrentNum][8] > 0.0) {
		if (ctx->phys.sr < ctx->controlFile.Para[ctx->controlFile.CurrentNum][4] - ctx->err.StressAir) {
			ctx->ao.raw[ctx->daCh.EP_Cell] = ctx->ao.raw[ctx->daCh.EP_Cell] + float(ctx->ao.cal.a[ctx->daCh.EP_Cell] * ctx->controlFile.Para[ctx->controlFile.CurrentNum][8] / 60.0 * ctx->timeSettings.Interval2 / 1000.0);
		}
		if (ctx->phys.sr > ctx->controlFile.Para[ctx->controlFile.CurrentNum][4] + ctx->err.StressAir) {
			ctx->ao.raw[ctx->daCh.EP_Cell] = ctx->ao.raw[ctx->daCh.EP_Cell] - float(ctx->ao.cal.a[ctx->daCh.EP_Cell] * ctx->controlFile.Para[ctx->controlFile.CurrentNum][8] / 60.0 * ctx->timeSettings.Interval2 / 1000.0);
		}
	}

	if (ctx->controlFile.Para[ctx->controlFile.CurrentNum][4] == ctx->controlFile.Para[ctx->controlFile.CurrentNum][1]) {
		ctx->controlFile.CurrentNum = ctx->controlFile.CurrentNum + 1;
		ctx->StepTime = 0.0;
	}
	else {
		float comp_rate = (ctx->phys.sr - ctx->controlFile.Para[ctx->controlFile.CurrentNum][1]) / (ctx->controlFile.Para[ctx->controlFile.CurrentNum][4] - ctx->controlFile.Para[ctx->controlFile.CurrentNum][1]);
		float Target_szq = ctx->controlFile.Para[ctx->controlFile.CurrentNum][2] + comp_rate * (ctx->controlFile.Para[ctx->controlFile.CurrentNum][5] - ctx->controlFile.Para[ctx->controlFile.CurrentNum][2]);
		ctx->target.sz = ctx->controlFile.Para[ctx->controlFile.CurrentNum][0] + comp_rate * (ctx->controlFile.Para[ctx->controlFile.CurrentNum][3] - ctx->controlFile.Para[ctx->controlFile.CurrentNum][0]);

		ctx->ao.raw[ctx->daCh.AxisMotor] = 5.0f;			// Axial Motor: On
		ctx->ao.raw[ctx->daCh.TorsionMotor] = 5.0f;         // Torsional Motor: On
		ctx->ao.raw[ctx->daCh.AxisSpeed] = float(ctx->ao.cal.a[ctx->daCh.AxisSpeed] * ctx->controlFile.Para[ctx->controlFile.CurrentNum][6] + ctx->ao.cal.b[ctx->daCh.AxisSpeed]);
		ctx->ao.raw[ctx->daCh.TorsionSpeed] = float(ctx->ao.cal.a[ctx->daCh.TorsionSpeed] * ctx->controlFile.Para[ctx->controlFile.CurrentNum][7] + ctx->ao.cal.b[ctx->daCh.TorsionSpeed]);

		if (ctx->phys.sz > ctx->target.sz + ctx->err.StressMotor)			ctx->ao.raw[ctx->daCh.AxisClutch] = ctx->volt.Up;	// Clutch: Unloading
		else if (ctx->phys.sz < ctx->target.sz - ctx->err.StressMotor)	ctx->ao.raw[ctx->daCh.AxisClutch] = ctx->volt.Down;	// Clutch: loading
		else											ctx->ao.raw[ctx->daCh.AxisSpeed] = 0.0f;	// RPM->0

		if (ctx->phys.szq > Target_szq + ctx->err.StressMotor)			ctx->ao.raw[ctx->daCh.TorsionClutch] = ctx->volt.CCW;	// Clutch: Unloading
		else if (ctx->phys.szq < Target_szq - ctx->err.StressMotor)	ctx->ao.raw[ctx->daCh.TorsionClutch] = ctx->volt.CW;	// Clutch: loading
		else											ctx->ao.raw[ctx->daCh.TorsionSpeed] = 0.0f;	// RPM->0
	}

	if (fabs(ctx->phys.sz - ctx->controlFile.Para[ctx->controlFile.CurrentNum][3]) <= ctx->err.StressMotor * 2.0 && fabs(ctx->phys.sr - ctx->controlFile.Para[ctx->controlFile.CurrentNum][4]) <= ctx->err.StressMotor * 2.0 && fabs(ctx->phys.szq - ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]) <= ctx->err.StressMotor * 2.0) {
		ctx->controlFile.CurrentNum = ctx->controlFile.CurrentNum + 1;
		ctx->StepTime = 0.0;
	}
}


void CDigitShowBasicDoc::EffectiveStressPathLoading()
{	DigitShowContext* ctx = GetContext();
	// 0: sigma_z_ini, 
	// 1: sigma_r_ini, 
	// 2: tau_zq_ini, 
	// 3: sigma_z_end, 
	// 4: sigma_r_end, 
	// 5: tau_zq_end.
	// 6: Axial Motor Speed	(RPM)
	// 7: Torsion Motor Speed (RPM)
	// 8: Cell Pressure Rate (min/kPa),
	ctx->StepTime=ctx->StepTime+ctx->CtrlStepTime/60.0;
	if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][1] != ctx->controlFile.Para[ctx->controlFile.CurrentNum][4] ){
		if(ctx->phys.sr < ctx->controlFile.Para[ctx->controlFile.CurrentNum][4]-ctx->err.StressAir) ctx->target.sr=ctx->phys.sr+ctx->controlFile.Para[ctx->controlFile.CurrentNum][8]*ctx->timeSettings.Interval2/1000/60;
		if(ctx->phys.sr > ctx->controlFile.Para[ctx->controlFile.CurrentNum][4]+ctx->err.StressAir) ctx->target.sr=ctx->phys.sr-ctx->controlFile.Para[ctx->controlFile.CurrentNum][8]*ctx->timeSettings.Interval2/1000/60;
		if(fabs(ctx->phys.sr-ctx->controlFile.Para[ctx->controlFile.CurrentNum][4]) <= ctx->err.StressAir) ctx->target.sr=ctx->controlFile.Para[ctx->controlFile.CurrentNum][4];
		ctx->target.sz=(ctx->controlFile.Para[ctx->controlFile.CurrentNum][3]-ctx->controlFile.Para[ctx->controlFile.CurrentNum][0])/(ctx->controlFile.Para[ctx->controlFile.CurrentNum][4]-ctx->controlFile.Para[ctx->controlFile.CurrentNum][1])*(ctx->phys.sr-ctx->controlFile.Para[ctx->controlFile.CurrentNum][1])+ctx->controlFile.Para[ctx->controlFile.CurrentNum][0];
		if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][3] > ctx->controlFile.Para[ctx->controlFile.CurrentNum][0] && ctx->target.sz > ctx->controlFile.Para[ctx->controlFile.CurrentNum][3]) ctx->target.sz=ctx->controlFile.Para[ctx->controlFile.CurrentNum][3]; 
		if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][3] < ctx->controlFile.Para[ctx->controlFile.CurrentNum][0] && ctx->target.sz < ctx->controlFile.Para[ctx->controlFile.CurrentNum][3]) ctx->target.sz=ctx->controlFile.Para[ctx->controlFile.CurrentNum][3]; 
		ctx->target.tzq=(ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]-ctx->controlFile.Para[ctx->controlFile.CurrentNum][2])/(ctx->controlFile.Para[ctx->controlFile.CurrentNum][4]-ctx->controlFile.Para[ctx->controlFile.CurrentNum][1])*(ctx->phys.sr-ctx->controlFile.Para[ctx->controlFile.CurrentNum][1])+ctx->controlFile.Para[ctx->controlFile.CurrentNum][2];
		if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][5] > ctx->controlFile.Para[ctx->controlFile.CurrentNum][2] && ctx->target.tzq > ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]) ctx->target.tzq=ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]; 
		if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][5] < ctx->controlFile.Para[ctx->controlFile.CurrentNum][2] && ctx->target.tzq < ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]) ctx->target.tzq=ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]; 
	}
	else if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][0] != ctx->controlFile.Para[ctx->controlFile.CurrentNum][3] && fabs(ctx->controlFile.Para[ctx->controlFile.CurrentNum][3]-ctx->controlFile.Para[ctx->controlFile.CurrentNum][0]) >= fabs(ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]-ctx->controlFile.Para[ctx->controlFile.CurrentNum][2])){
		ctx->target.sr=ctx->controlFile.Para[ctx->controlFile.CurrentNum][4];
		ctx->target.sz=ctx->controlFile.Para[ctx->controlFile.CurrentNum][3];
		ctx->target.tzq=(ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]-ctx->controlFile.Para[ctx->controlFile.CurrentNum][2])/(ctx->controlFile.Para[ctx->controlFile.CurrentNum][3]-ctx->controlFile.Para[ctx->controlFile.CurrentNum][0])*(ctx->phys.sz-ctx->controlFile.Para[ctx->controlFile.CurrentNum][0])+ctx->controlFile.Para[ctx->controlFile.CurrentNum][2];
		if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][5] > ctx->controlFile.Para[ctx->controlFile.CurrentNum][2] && ctx->target.tzq > ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]) ctx->target.tzq=ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]; 
		if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][5] < ctx->controlFile.Para[ctx->controlFile.CurrentNum][2] && ctx->target.tzq < ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]) ctx->target.tzq=ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]; 
	}
	else if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][2] != ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]){
		ctx->target.sr=ctx->controlFile.Para[ctx->controlFile.CurrentNum][4];
		ctx->target.sz=(ctx->controlFile.Para[ctx->controlFile.CurrentNum][3]-ctx->controlFile.Para[ctx->controlFile.CurrentNum][0])/(ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]-ctx->controlFile.Para[ctx->controlFile.CurrentNum][2])*(ctx->phys.szq-ctx->controlFile.Para[ctx->controlFile.CurrentNum][2])+ctx->controlFile.Para[ctx->controlFile.CurrentNum][0];
		if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][3] > ctx->controlFile.Para[ctx->controlFile.CurrentNum][0] && ctx->target.sz > ctx->controlFile.Para[ctx->controlFile.CurrentNum][3]) ctx->target.sz=ctx->controlFile.Para[ctx->controlFile.CurrentNum][3]; 
		if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][3] < ctx->controlFile.Para[ctx->controlFile.CurrentNum][0] && ctx->target.sz < ctx->controlFile.Para[ctx->controlFile.CurrentNum][3]) ctx->target.sz=ctx->controlFile.Para[ctx->controlFile.CurrentNum][3]; 
		ctx->target.tzq=ctx->controlFile.Para[ctx->controlFile.CurrentNum][5];
	}
	else {
		ctx->target.sr=ctx->controlFile.Para[ctx->controlFile.CurrentNum][4];
		ctx->target.sz=ctx->controlFile.Para[ctx->controlFile.CurrentNum][3];
		ctx->target.tzq=ctx->controlFile.Para[ctx->controlFile.CurrentNum][5];
	}
//
	ctx->ao.raw[ctx->daCh.AxisMotor]=5.0f;
	ctx->ao.raw[ctx->daCh.AxisSpeed]=float(ctx->ao.cal.a[ctx->daCh.AxisSpeed]*ctx->controlFile.Para[ctx->controlFile.CurrentNum][6]+ctx->ao.cal.b[ctx->daCh.AxisSpeed]);
	ctx->ao.raw[ctx->daCh.TorsionMotor]=5.0f;
	ctx->ao.raw[ctx->daCh.TorsionSpeed]=float(ctx->ao.cal.a[ctx->daCh.TorsionSpeed]*ctx->controlFile.Para[ctx->controlFile.CurrentNum][7]+ctx->ao.cal.b[ctx->daCh.TorsionSpeed]);
	// @note M.KUNO 2022.12.02 original code
	//if( ctx->controlFile.Para[ctx->controlFile.CurrentNum][8] != 0.0 )	ctx->ao.raw[ctx->daCh.EP_Cell]=ctx->ao.raw[ctx->daCh.EP_Cell]+float(0.3*ctx->ao.cal.a[ctx->daCh.EP_Cell]*(ctx->target.sr-ctx->phys.sr));
	// @note M.KUNO 2022.12.02 edited code
	if (ctx->controlFile.Para[ctx->controlFile.CurrentNum][8] != 0.0)	ctx->ao.raw[ctx->daCh.EP_Cell] = ctx->ao.raw[ctx->daCh.EP_Cell] + float(0.9 * ctx->ao.cal.a[ctx->daCh.EP_Cell] * (ctx->target.sr - ctx->phys.sr));
//
	if(ctx->phys.sz > ctx->target.sz+ctx->err.StressMotor)			ctx->ao.raw[ctx->daCh.AxisClutch]=ctx->volt.Up;
	else if(ctx->phys.sz < ctx->target.sz-ctx->err.StressMotor)	ctx->ao.raw[ctx->daCh.AxisClutch]=ctx->volt.Down;
	else										ctx->ao.raw[ctx->daCh.AxisSpeed]=0.0f;
//	
	if(ctx->phys.szq > ctx->target.tzq + ctx->err.StressMotor)			ctx->ao.raw[ctx->daCh.TorsionClutch]=ctx->volt.CCW;
	else if(ctx->phys.szq < ctx->target.tzq - ctx->err.StressMotor)	ctx->ao.raw[ctx->daCh.TorsionClutch]=ctx->volt.CW;
	else											ctx->ao.raw[ctx->daCh.TorsionSpeed]=0.0f;
//
	if( fabs(ctx->phys.sz-ctx->controlFile.Para[ctx->controlFile.CurrentNum][3])<=ctx->err.StressMotor*2.0 && fabs(ctx->phys.sr-ctx->controlFile.Para[ctx->controlFile.CurrentNum][4])<=ctx->err.StressMotor*2.0 && fabs(ctx->phys.szq-ctx->controlFile.Para[ctx->controlFile.CurrentNum][5])<=ctx->err.StressMotor*2.0 ){
		ctx->controlFile.CurrentNum=ctx->controlFile.CurrentNum+1;
		ctx->StepTime=0.0;
	}
}

void CDigitShowBasicDoc::MonotonicTorsionalLoading()
{	DigitShowContext* ctx = GetContext();
	//	0: Clockwise:0 / Countercloclwise:1
	//	1: sigma_zq
	//	2: gamma_zq
	//	3: Torsinal Speed
	ctx->StepTime=ctx->StepTime+ctx->CtrlStepTime/60.0;
	ctx->ao.raw[ctx->daCh.TorsionMotor]=5.0f;
	ctx->ao.raw[ctx->daCh.TorsionSpeed]=float(ctx->ao.cal.a[ctx->daCh.TorsionSpeed]*ctx->controlFile.Para[ctx->controlFile.CurrentNum][3]+ctx->ao.cal.b[ctx->daCh.TorsionSpeed]);
//
	if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][0]==0.0){
		if(ctx->phys.szq < ctx->controlFile.Para[ctx->controlFile.CurrentNum][1] && ctx->phys.gzq1 < ctx->controlFile.Para[ctx->controlFile.CurrentNum][2])	ctx->ao.raw[ctx->daCh.TorsionClutch] = ctx->volt.CW;
		else {
			ctx->StepTime=0.0;
			ctx->controlFile.CurrentNum=ctx->controlFile.CurrentNum+1;
		}
	}
	else if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][0]==1.0){
		if(ctx->phys.szq > ctx->controlFile.Para[ctx->controlFile.CurrentNum][1] && ctx->phys.gzq1 > ctx->controlFile.Para[ctx->controlFile.CurrentNum][2])	ctx->ao.raw[ctx->daCh.TorsionClutch] = ctx->volt.CCW;
		else {
			ctx->StepTime=0.0;
			ctx->controlFile.CurrentNum=ctx->controlFile.CurrentNum+1;
		}
	}
}

void CDigitShowBasicDoc::MonotonicTorsionalLoadingCNS()
{	DigitShowContext* ctx = GetContext();
	//	0: Clockwise:0 / Countercloclwise:1
	//	1: sigma_zq
	//	2: gamma_zq
	//	3: Torsinal Speed
	//	4: Axial Speed
	//	5: Cell Pressure Rate
	//	6: sigma_z
	//	7: sigma_r
	ctx->StepTime=ctx->StepTime+ctx->CtrlStepTime/60.0;
	ctx->ao.raw[ctx->daCh.AxisMotor]=5.0f;
	ctx->ao.raw[ctx->daCh.AxisSpeed]=float(ctx->ao.cal.a[ctx->daCh.AxisSpeed]*ctx->controlFile.Para[ctx->controlFile.CurrentNum][4]+ctx->ao.cal.b[ctx->daCh.AxisSpeed]);
	ctx->ao.raw[ctx->daCh.TorsionMotor]=5.0f;
	ctx->ao.raw[ctx->daCh.TorsionSpeed]=float(ctx->ao.cal.a[ctx->daCh.TorsionSpeed]*ctx->controlFile.Para[ctx->controlFile.CurrentNum][3]+ctx->ao.cal.b[ctx->daCh.TorsionSpeed]);
	if(ctx->phys.sz > ctx->controlFile.Para[ctx->controlFile.CurrentNum][6]+ctx->err.StressMotor)			ctx->ao.raw[ctx->daCh.AxisClutch]=ctx->volt.Up;
	else if(ctx->phys.sz < ctx->controlFile.Para[ctx->controlFile.CurrentNum][6]-ctx->err.StressMotor)	ctx->ao.raw[ctx->daCh.AxisClutch]=ctx->volt.Down;
	else												ctx->ao.raw[ctx->daCh.AxisSpeed]=0.0f;
	ctx->target.sr=ctx->controlFile.Para[ctx->controlFile.CurrentNum][7];
	// @note M.KUNO 2022.12.15 original code
	//if( ctx->controlFile.Para[ctx->controlFile.CurrentNum][5] != 0.0 )	ctx->ao.raw[ctx->daCh.EP_Cell]=ctx->ao.raw[ctx->daCh.EP_Cell]+float(0.3*ctx->ao.cal.a[ctx->daCh.EP_Cell]*(ctx->target.sr-ctx->phys.sr));
	// @note H.Hashimoto 2022.12.15 fixed code
	if (ctx->controlFile.Para[ctx->controlFile.CurrentNum][5] != 0.0) {
		if (ctx->phys.sr < ctx->target.sr - ctx->err.StressAir) {
			ctx->ao.raw[ctx->daCh.EP_Cell] = ctx->ao.raw[ctx->daCh.EP_Cell] + float(ctx->ao.cal.a[ctx->daCh.EP_Cell] * ctx->controlFile.Para[ctx->controlFile.CurrentNum][5] / 60.0 * ctx->timeSettings.Interval2 / 1000.0);
		}
		else if (ctx->phys.sr > ctx->target.sr + ctx->err.StressAir) {
			ctx->ao.raw[ctx->daCh.EP_Cell] = ctx->ao.raw[ctx->daCh.EP_Cell] - float(ctx->ao.cal.a[ctx->daCh.EP_Cell] * ctx->controlFile.Para[ctx->controlFile.CurrentNum][5] / 60.0 * ctx->timeSettings.Interval2 / 1000.0);
		}
	}
//
	if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][0]==0.0){
		if(ctx->phys.szq < ctx->controlFile.Para[ctx->controlFile.CurrentNum][1] && ctx->phys.gzq1 < ctx->controlFile.Para[ctx->controlFile.CurrentNum][2])	ctx->ao.raw[ctx->daCh.TorsionClutch] = ctx->volt.CW;
		else {
			ctx->StepTime=0.0;
			ctx->controlFile.CurrentNum=ctx->controlFile.CurrentNum+1;
		}
	}
	else if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][0]==1.0){
		if(ctx->phys.szq > ctx->controlFile.Para[ctx->controlFile.CurrentNum][1] && ctx->phys.gzq1 > ctx->controlFile.Para[ctx->controlFile.CurrentNum][2])	ctx->ao.raw[ctx->daCh.TorsionClutch] = ctx->volt.CCW;
		else {
			ctx->StepTime=0.0;
			ctx->controlFile.CurrentNum=ctx->controlFile.CurrentNum+1;
		}
	}
}

void CDigitShowBasicDoc::CyclicTorsionalLoading()
{	DigitShowContext* ctx = GetContext();
	//	0: Clockwise:0 / Countercloclwise:1
	//	1: sigma_zq_lower
	//	2: sigma_zq_upper
	//	3: gamma_zq_lower
	//	4: gamma_zq_upper
	//	5: Number
	//	6: Torsinal Speed
	ctx->StepTime=ctx->StepTime+ctx->CtrlStepTime/60.0;
	ctx->ao.raw[ctx->daCh.TorsionMotor] = 5.0f;
	ctx->ao.raw[ctx->daCh.TorsionSpeed]=float(ctx->ao.cal.a[ctx->daCh.TorsionSpeed]*ctx->controlFile.Para[ctx->controlFile.CurrentNum][6]+ctx->ao.cal.b[ctx->daCh.TorsionSpeed]);
	if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][0]==0.0){
		if(ctx->NumCyclic==0){
			ctx->flags.Cyclic=FALSE;
			ctx->NumCyclic=1;
		}
		if(ctx->NumCyclic != 0 && ctx->NumCyclic <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]){
			if(ctx->flags.Cyclic==FALSE){
				ctx->ao.raw[ctx->daCh.TorsionClutch] = ctx->volt.CW;
				if(ctx->phys.szq >= ctx->controlFile.Para[ctx->controlFile.CurrentNum][2] || ctx->phys.gzq1 >= ctx->controlFile.Para[ctx->controlFile.CurrentNum][4]) ctx->flags.Cyclic=TRUE;
			}
			if(ctx->flags.Cyclic==TRUE){
				ctx->ao.raw[ctx->daCh.TorsionClutch] = ctx->volt.CCW;
				if(ctx->phys.szq <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][1] || ctx->phys.gzq1 <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][3]){
					ctx->flags.Cyclic=FALSE;
					ctx->NumCyclic=ctx->NumCyclic+1;
				}
			}
		}
		if(ctx->NumCyclic > ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]){ 
			ctx->controlFile.CurrentNum=ctx->controlFile.CurrentNum+1;
			ctx->StepTime=0.0;
			ctx->NumCyclic=0;
		}
	}
	else if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][0]==1.0){
		if(ctx->NumCyclic==0){
			ctx->flags.Cyclic=TRUE;
			ctx->NumCyclic=1;
		}
		if(ctx->NumCyclic != 0 && ctx->NumCyclic <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]){
			if(ctx->flags.Cyclic==FALSE){
				ctx->ao.raw[ctx->daCh.TorsionClutch] = ctx->volt.CCW;
				if(ctx->phys.szq <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][1] || ctx->phys.gzq1 <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][3]) {
					ctx->flags.Cyclic=TRUE;
					ctx->NumCyclic=ctx->NumCyclic+1;
				}
			}
			if(ctx->flags.Cyclic==TRUE){
				ctx->ao.raw[ctx->daCh.TorsionClutch] = ctx->volt.CW;
				if(ctx->phys.szq >= ctx->controlFile.Para[ctx->controlFile.CurrentNum][2] || ctx->phys.gzq1 <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][4]){
					ctx->flags.Cyclic=FALSE;
				}
			}
		}
		if(ctx->NumCyclic > ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]){ 
			ctx->controlFile.CurrentNum=ctx->controlFile.CurrentNum+1;
			ctx->StepTime=0.0;
			ctx->NumCyclic=0;
		}
	} 
}

void CDigitShowBasicDoc::CyclicTorsionalLoadingCNS()
{	DigitShowContext* ctx = GetContext();
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
	ctx->StepTime=ctx->StepTime+ctx->CtrlStepTime/60.0;
	ctx->ao.raw[ctx->daCh.AxisMotor]=5.0f;
	ctx->ao.raw[ctx->daCh.AxisSpeed]=float(ctx->ao.cal.a[ctx->daCh.AxisSpeed]*ctx->controlFile.Para[ctx->controlFile.CurrentNum][7]+ctx->ao.cal.b[ctx->daCh.AxisSpeed]);
	ctx->ao.raw[ctx->daCh.TorsionMotor] = 5.0f;
	ctx->ao.raw[ctx->daCh.TorsionSpeed]=float(ctx->ao.cal.a[ctx->daCh.TorsionSpeed]*ctx->controlFile.Para[ctx->controlFile.CurrentNum][6]+ctx->ao.cal.b[ctx->daCh.TorsionSpeed]);
	if(ctx->phys.sz > ctx->controlFile.Para[ctx->controlFile.CurrentNum][9]+ctx->err.StressMotor)			ctx->ao.raw[ctx->daCh.AxisClutch]=ctx->volt.Up;
	else if(ctx->phys.sz < ctx->controlFile.Para[ctx->controlFile.CurrentNum][9]-ctx->err.StressMotor)	ctx->ao.raw[ctx->daCh.AxisClutch]=ctx->volt.Down;
	else												ctx->ao.raw[ctx->daCh.AxisSpeed]=0.0f;
	ctx->target.sr=ctx->controlFile.Para[ctx->controlFile.CurrentNum][10];
	if( ctx->controlFile.Para[ctx->controlFile.CurrentNum][8] != 0.0 )	ctx->ao.raw[ctx->daCh.EP_Cell]=ctx->ao.raw[ctx->daCh.EP_Cell]+float(0.3*ctx->ao.cal.a[ctx->daCh.EP_Cell]*(ctx->target.sr-ctx->phys.sr));
//	
	if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][0]==0.0){
		if(ctx->NumCyclic==0){
			ctx->flags.Cyclic=FALSE;
			ctx->NumCyclic=1;
		}
		if(ctx->NumCyclic != 0 && ctx->NumCyclic <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]){
			if(ctx->flags.Cyclic==FALSE){
				ctx->ao.raw[ctx->daCh.TorsionClutch] = ctx->volt.CW;
				if(ctx->phys.szq >= ctx->controlFile.Para[ctx->controlFile.CurrentNum][2] || ctx->phys.gzq1 >= ctx->controlFile.Para[ctx->controlFile.CurrentNum][4]) ctx->flags.Cyclic=TRUE;
			}
			if(ctx->flags.Cyclic==TRUE){
				ctx->ao.raw[ctx->daCh.TorsionClutch] = ctx->volt.CCW;
				if(ctx->phys.szq <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][1] || ctx->phys.gzq1 <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][3]){
					ctx->flags.Cyclic=FALSE;
					ctx->NumCyclic=ctx->NumCyclic+1;
				}
			}
		}
		if(ctx->NumCyclic > ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]){ 
			ctx->controlFile.CurrentNum=ctx->controlFile.CurrentNum+1;
			ctx->StepTime=0.0;
			ctx->NumCyclic=0;
		}
	}
	else if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][0]==1.0){
		if(ctx->NumCyclic==0){
			ctx->flags.Cyclic=TRUE;
			ctx->NumCyclic=1;
		}
		if(ctx->NumCyclic != 0 && ctx->NumCyclic <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]){
			if(ctx->flags.Cyclic==FALSE){
				ctx->ao.raw[ctx->daCh.TorsionClutch] = ctx->volt.CCW;
				if(ctx->phys.szq <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][1] || ctx->phys.gzq1 <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][3]) {
					ctx->flags.Cyclic=TRUE;
					ctx->NumCyclic=ctx->NumCyclic+1;
				}
			}
			if(ctx->flags.Cyclic==TRUE){
				ctx->ao.raw[ctx->daCh.TorsionClutch] = ctx->volt.CW;
				if(ctx->phys.szq >= ctx->controlFile.Para[ctx->controlFile.CurrentNum][2] || ctx->phys.gzq1 <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][4]){
					ctx->flags.Cyclic=FALSE;
				}
			}
		}
		if(ctx->NumCyclic > ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]){ 
			ctx->controlFile.CurrentNum=ctx->controlFile.CurrentNum+1;
			ctx->StepTime=0.0;
			ctx->NumCyclic=0;
		}
	} 
}

void CDigitShowBasicDoc::SmallCyclicTorsionalLoading()
{	DigitShowContext* ctx = GetContext();
	//	0: Clockwise:0 / Countercloclwise:1
	//	1: Delta[gamma_zq]
	//	2: Number
	//	3: Torsinal Speed
	ctx->StepTime=ctx->StepTime+ctx->CtrlStepTime/60.0;
	ctx->ao.raw[ctx->daCh.TorsionMotor] = 5.0f;
	ctx->ao.raw[ctx->daCh.TorsionSpeed]=float(ctx->ao.cal.a[ctx->daCh.TorsionSpeed]*ctx->controlFile.Para[ctx->controlFile.CurrentNum][3]+ctx->ao.cal.b[ctx->daCh.TorsionSpeed]);
	if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][0]==0.0){
		if(ctx->NumCyclic==0){
			ctx->target.gzq = ctx->phys.gzq2;
			ctx->NumCyclic=1;
			ctx->NumSmallCyclic=0;
		}
		if(ctx->NumCyclic != 0 && ctx->NumCyclic <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][2]){
			if(ctx->NumSmallCyclic==0){
				ctx->ao.raw[ctx->daCh.TorsionClutch] = ctx->volt.CCW;
				if(ctx->phys.gzq2 <= ctx->target.gzq - ctx->controlFile.Para[ctx->controlFile.CurrentNum][1]) ctx->NumSmallCyclic=1;
			}
			if(ctx->NumSmallCyclic==1){
				ctx->ao.raw[ctx->daCh.TorsionClutch] = ctx->volt.CW;
				if(ctx->phys.gzq2 >= ctx->target.gzq + ctx->controlFile.Para[ctx->controlFile.CurrentNum][1]) ctx->NumSmallCyclic=2;
			}
			if(ctx->NumSmallCyclic==2){
				ctx->ao.raw[ctx->daCh.TorsionClutch] = ctx->volt.CCW;
				if(ctx->phys.gzq2 <= ctx->target.gzq){;
					ctx->NumSmallCyclic=0;
					ctx->NumCyclic=ctx->NumCyclic+1;
				}
			}
		}
		if(ctx->NumCyclic > ctx->controlFile.Para[ctx->controlFile.CurrentNum][2]){ 
			ctx->controlFile.CurrentNum=ctx->controlFile.CurrentNum+1;
			ctx->StepTime=0.0;
			ctx->NumCyclic=0;
		}
	}
	else if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][0]==1.0){
		if(ctx->NumCyclic==0){
			ctx->target.gzq = ctx->phys.gzq2;
			ctx->NumCyclic=1;
			ctx->NumSmallCyclic=0;
		}
		if(ctx->NumCyclic != 0 && ctx->NumCyclic <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][2]){
			if(ctx->NumSmallCyclic==0){
				ctx->ao.raw[ctx->daCh.TorsionClutch] = ctx->volt.CW;
				if(ctx->phys.gzq2 >= ctx->target.gzq + ctx->controlFile.Para[ctx->controlFile.CurrentNum][1])	ctx->NumSmallCyclic=1;
			}
			if(ctx->NumSmallCyclic==1){
				ctx->ao.raw[ctx->daCh.TorsionClutch] = ctx->volt.CCW;
				if(ctx->phys.gzq2 <= ctx->target.gzq - ctx->controlFile.Para[ctx->controlFile.CurrentNum][1])	ctx->NumSmallCyclic=2;
			}
			if(ctx->NumSmallCyclic==2){
				ctx->ao.raw[ctx->daCh.TorsionClutch] = ctx->volt.CW;
				if(ctx->phys.gzq2 >= ctx->target.gzq) {
					ctx->NumSmallCyclic=0;
					ctx->NumCyclic=ctx->NumCyclic+1;
				}
			}
		}
		if(ctx->NumCyclic > ctx->controlFile.Para[ctx->controlFile.CurrentNum][2]){ 
			ctx->controlFile.CurrentNum=ctx->controlFile.CurrentNum+1;
			ctx->StepTime=0.0;
			ctx->NumCyclic=0;
		}
	} 
}


void CDigitShowBasicDoc::SmallCyclicTorsionalLoadingCNS()
{	DigitShowContext* ctx = GetContext();
	//	0: Clockwise:0 / Countercloclwise:1
	//	1: Delta[gamma_zq]
	//	2: Number
	//	3: Torsinal Speed
	//	4: Axial Speed
	//	5: Cell Pressure Rate
	//	6: sigma_z
	//	7: sigma_r
	ctx->StepTime=ctx->StepTime+ctx->CtrlStepTime/60.0;
	ctx->ao.raw[ctx->daCh.AxisMotor]=5.0f;
	ctx->ao.raw[ctx->daCh.AxisSpeed]=float(ctx->ao.cal.a[ctx->daCh.AxisSpeed]*ctx->controlFile.Para[ctx->controlFile.CurrentNum][4]+ctx->ao.cal.b[ctx->daCh.AxisSpeed]);
	ctx->ao.raw[ctx->daCh.TorsionMotor] = 5.0f;
	ctx->ao.raw[ctx->daCh.TorsionSpeed]=float(ctx->ao.cal.a[ctx->daCh.TorsionSpeed]*ctx->controlFile.Para[ctx->controlFile.CurrentNum][3]+ctx->ao.cal.b[ctx->daCh.TorsionSpeed]);
	if(ctx->phys.sz > ctx->controlFile.Para[ctx->controlFile.CurrentNum][6]+ctx->err.StressMotor)			ctx->ao.raw[ctx->daCh.AxisClutch]=ctx->volt.Up;
	else if(ctx->phys.sz < ctx->controlFile.Para[ctx->controlFile.CurrentNum][6]-ctx->err.StressMotor)	ctx->ao.raw[ctx->daCh.AxisClutch]=ctx->volt.Down;
	else												ctx->ao.raw[ctx->daCh.AxisSpeed]=0.0f;
	ctx->target.sr=ctx->controlFile.Para[ctx->controlFile.CurrentNum][7];
	if( ctx->controlFile.Para[ctx->controlFile.CurrentNum][5] != 0.0 )	ctx->ao.raw[ctx->daCh.EP_Cell]=ctx->ao.raw[ctx->daCh.EP_Cell]+float(0.3*ctx->ao.cal.a[ctx->daCh.EP_Cell]*(ctx->target.sr-ctx->phys.sr));
//
	if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][0]==0.0){
		if(ctx->NumCyclic==0){
			ctx->target.gzq = ctx->phys.gzq2;
			ctx->NumCyclic=1;
			ctx->NumSmallCyclic=0;
		}
		if(ctx->NumCyclic != 0 && ctx->NumCyclic <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][2]){
			if(ctx->NumSmallCyclic==0){
				ctx->ao.raw[ctx->daCh.TorsionClutch] = ctx->volt.CCW;
				if(ctx->phys.gzq2 <= ctx->target.gzq - ctx->controlFile.Para[ctx->controlFile.CurrentNum][1]) ctx->NumSmallCyclic=1;
			}
			if(ctx->NumSmallCyclic==1){
				ctx->ao.raw[ctx->daCh.TorsionClutch] = ctx->volt.CW;
				if(ctx->phys.gzq2 >= ctx->target.gzq + ctx->controlFile.Para[ctx->controlFile.CurrentNum][1]) ctx->NumSmallCyclic=2;
			}
			if(ctx->NumSmallCyclic==2){
				ctx->ao.raw[ctx->daCh.TorsionClutch] = ctx->volt.CCW;
				if(ctx->phys.gzq2 <= ctx->target.gzq){;
					ctx->NumSmallCyclic=0;
					ctx->NumCyclic=ctx->NumCyclic+1;
				}
			}
		}
		if(ctx->NumCyclic > ctx->controlFile.Para[ctx->controlFile.CurrentNum][2]){ 
			ctx->controlFile.CurrentNum=ctx->controlFile.CurrentNum+1;
			ctx->StepTime=0.0;
			ctx->NumCyclic=0;
		}
	}
	else if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][0]==1.0){
		if(ctx->NumCyclic==0){
			ctx->target.gzq = ctx->phys.gzq2;
			ctx->NumCyclic=1;
			ctx->NumSmallCyclic=0;
		}
		if(ctx->NumCyclic != 0 && ctx->NumCyclic <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][2]){
			if(ctx->NumSmallCyclic==0){
				ctx->ao.raw[ctx->daCh.TorsionClutch] = ctx->volt.CW;
				if(ctx->phys.gzq2 >= ctx->target.gzq + ctx->controlFile.Para[ctx->controlFile.CurrentNum][1])	ctx->NumSmallCyclic=1;
			}
			if(ctx->NumSmallCyclic==1){
				ctx->ao.raw[ctx->daCh.TorsionClutch] = ctx->volt.CCW;
				if(ctx->phys.gzq2 <= ctx->target.gzq - ctx->controlFile.Para[ctx->controlFile.CurrentNum][1])	ctx->NumSmallCyclic=2;
			}
			if(ctx->NumSmallCyclic==2){
				ctx->ao.raw[ctx->daCh.TorsionClutch] = ctx->volt.CW;
				if(ctx->phys.gzq2 >= ctx->target.gzq) {
					ctx->NumSmallCyclic=0;
					ctx->NumCyclic=ctx->NumCyclic+1;
				}
			}
		}
		if(ctx->NumCyclic > ctx->controlFile.Para[ctx->controlFile.CurrentNum][2]){ 
			ctx->controlFile.CurrentNum=ctx->controlFile.CurrentNum+1;
			ctx->StepTime=0.0;
			ctx->NumCyclic=0;
		}
	} 
}

void CDigitShowBasicDoc::MonotonicAxialLoading()
{	DigitShowContext* ctx = GetContext();
	// 0: Loading:0/Unloading:1, 
	// 1: sigma_z (kPa), 
	// 2: epsilon_z,
	// 3: Axial Speed
	ctx->StepTime=ctx->StepTime+ctx->CtrlStepTime/60.0;
	ctx->ao.raw[ctx->daCh.AxisMotor]=5.0f;
	ctx->ao.raw[ctx->daCh.AxisSpeed]=float(ctx->ao.cal.a[ctx->daCh.AxisSpeed]*ctx->controlFile.Para[ctx->controlFile.CurrentNum][3]+ctx->ao.cal.b[ctx->daCh.AxisSpeed]);
	if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][0]==0.0){
		if(ctx->phys.sz <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][1] && ctx->phys.ez < ctx->controlFile.Para[ctx->controlFile.CurrentNum][2]) ctx->ao.raw[ctx->daCh.AxisClutch]=ctx->volt.Down;
		else {
			ctx->controlFile.CurrentNum=ctx->controlFile.CurrentNum+1;
			ctx->StepTime=0.0;
		}
	}
	else if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][0]==1.0){
		if(ctx->phys.sz >= ctx->controlFile.Para[ctx->controlFile.CurrentNum][1] && ctx->phys.ez > ctx->controlFile.Para[ctx->controlFile.CurrentNum][2]) ctx->ao.raw[ctx->daCh.AxisClutch]=ctx->volt.Up;
		else {
			ctx->controlFile.CurrentNum=ctx->controlFile.CurrentNum+1;
			ctx->StepTime=0.0;
		}
	}
}


void CDigitShowBasicDoc::CyclicAxialLoading()
{	DigitShowContext* ctx = GetContext();
	// 0: Loading:0/Unloading:1, 
	// 1: sigma_z_lower, 
	// 2: sigma_z_upper, 
	// 3: epsilon_z_lower,
	// 4: epsilon_z_upper,
	// 5: Number,
	// 6: Axial Speed
	ctx->StepTime=ctx->StepTime+ctx->CtrlStepTime/60.0;
	ctx->ao.raw[ctx->daCh.AxisMotor]=5.0f;
	ctx->ao.raw[ctx->daCh.AxisSpeed]=float(ctx->ao.cal.a[ctx->daCh.AxisSpeed]*ctx->controlFile.Para[ctx->controlFile.CurrentNum][6]+ctx->ao.cal.b[ctx->daCh.AxisSpeed]);
	if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][0]==0.0){
		if(ctx->NumCyclic==0){
			ctx->flags.Cyclic=FALSE;
			ctx->NumCyclic=1;
		}
		if(ctx->NumCyclic!=0 && ctx->NumCyclic <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]){
			if(ctx->flags.Cyclic==FALSE){
				if(ctx->phys.sz <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][2] && ctx->phys.ez <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][4])	ctx->ao.raw[ctx->daCh.AxisClutch]=ctx->volt.Down;
				else	ctx->flags.Cyclic=TRUE;
			}
			else {
				if(ctx->phys.sz >= ctx->controlFile.Para[ctx->controlFile.CurrentNum][1] && ctx->phys.ez >= ctx->controlFile.Para[ctx->controlFile.CurrentNum][3]) ctx->ao.raw[ctx->daCh.AxisClutch]=ctx->volt.Up;
				else{
					ctx->flags.Cyclic=FALSE;
					ctx->NumCyclic=ctx->NumCyclic+1;
				}
			}
		}
		if(ctx->NumCyclic>ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]){ 
			ctx->controlFile.CurrentNum=ctx->controlFile.CurrentNum+1;
			ctx->StepTime=0.0;
			ctx->NumCyclic=0;
		}
	}
	else if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][0]==1.0){
		if(ctx->NumCyclic==0){
			ctx->flags.Cyclic=TRUE;
			ctx->NumCyclic=1;
		}
		if(ctx->NumCyclic!=0 && ctx->NumCyclic <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][2]){
			if(ctx->flags.Cyclic==FALSE){
				if(ctx->phys.sz <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][2] && ctx->phys.ez <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][4])	ctx->ao.raw[ctx->daCh.AxisClutch]=ctx->volt.Down;
				else{
					ctx->flags.Cyclic=TRUE;
					ctx->NumCyclic=ctx->NumCyclic+1;
				}
			}
			else{
				if(ctx->phys.sz >= ctx->controlFile.Para[ctx->controlFile.CurrentNum][1] && ctx->phys.ez >= ctx->controlFile.Para[ctx->controlFile.CurrentNum][3]) ctx->ao.raw[ctx->daCh.AxisClutch]=ctx->volt.Up;
				else	ctx->flags.Cyclic=FALSE;
			}
		}
		if(ctx->NumCyclic>ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]){ 
			ctx->controlFile.CurrentNum=ctx->controlFile.CurrentNum+1;
			ctx->StepTime=0.0;
			ctx->NumCyclic=0;
		}
	} 
}

void CDigitShowBasicDoc::SmallCyclicAxialLoading()
{	DigitShowContext* ctx = GetContext();
	//	0: Loading:0 / Unloading:1
	//	1: Delta[epsilon_z]
	//	2: Number
	//	3: Axial Speed
	ctx->StepTime=ctx->StepTime+ctx->CtrlStepTime/60.0;
	ctx->ao.raw[ctx->daCh.AxisMotor] = 5.0f;
	ctx->ao.raw[ctx->daCh.AxisSpeed]=float(ctx->ao.cal.a[ctx->daCh.AxisSpeed]*ctx->controlFile.Para[ctx->controlFile.CurrentNum][3]+ctx->ao.cal.b[ctx->daCh.AxisSpeed]);
	if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][0]==0.0){
		if(ctx->NumCyclic==0){
			ctx->target.ez = ctx->phys.ez;
			ctx->NumCyclic=1;
			ctx->NumSmallCyclic=0;
		}
		if(ctx->NumCyclic != 0 && ctx->NumCyclic <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][2]){
			if(ctx->NumSmallCyclic==0){
				ctx->ao.raw[ctx->daCh.AxisClutch] = ctx->volt.Down;
				if(ctx->phys.ez >= ctx->target.ez + ctx->controlFile.Para[ctx->controlFile.CurrentNum][1]) ctx->NumSmallCyclic=1;
			}
			if(ctx->NumSmallCyclic==1){
				ctx->ao.raw[ctx->daCh.AxisClutch] = ctx->volt.Up;
				if(ctx->phys.ez <= ctx->target.ez - ctx->controlFile.Para[ctx->controlFile.CurrentNum][1]) ctx->NumSmallCyclic=2;
			}
			if(ctx->NumSmallCyclic==2){
				ctx->ao.raw[ctx->daCh.AxisClutch] = ctx->volt.Down;
				if(ctx->phys.ez >= ctx->target.ez){;
					ctx->NumSmallCyclic=0;
					ctx->NumCyclic=ctx->NumCyclic+1;
				}
			}
		}
		if(ctx->NumCyclic > ctx->controlFile.Para[ctx->controlFile.CurrentNum][2]){ 
			ctx->controlFile.CurrentNum=ctx->controlFile.CurrentNum+1;
			ctx->StepTime=0.0;
			ctx->NumCyclic=0;
		}
	}
	else if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][0]==1.0){
		if(ctx->NumCyclic==0){
			ctx->target.ez = ctx->phys.ez;
			ctx->NumCyclic=1;
			ctx->NumSmallCyclic=0;
		}
		if(ctx->NumCyclic != 0 && ctx->NumCyclic <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][2]){
			if(ctx->NumSmallCyclic==0){
				ctx->ao.raw[ctx->daCh.AxisClutch] = ctx->volt.Up;
				if(ctx->phys.ez <= ctx->target.ez - ctx->controlFile.Para[ctx->controlFile.CurrentNum][1])	ctx->NumSmallCyclic=1;
			}
			if(ctx->NumSmallCyclic==1){
				ctx->ao.raw[ctx->daCh.AxisClutch] = ctx->volt.Down;
				if(ctx->phys.ez >= ctx->target.ez - ctx->controlFile.Para[ctx->controlFile.CurrentNum][1])	ctx->NumSmallCyclic=2;
			}
			if(ctx->NumSmallCyclic==2){
				ctx->ao.raw[ctx->daCh.AxisClutch] = ctx->volt.Up;
				if(ctx->phys.ez <= ctx->target.ez) {
					ctx->NumSmallCyclic=0;
					ctx->NumCyclic=ctx->NumCyclic+1;
				}
			}
		}
		if(ctx->NumCyclic > ctx->controlFile.Para[ctx->controlFile.CurrentNum][2]){ 
			ctx->controlFile.CurrentNum=ctx->controlFile.CurrentNum+1;
			ctx->StepTime=0.0;
			ctx->NumCyclic=0;
		}
	} 
}
void CDigitShowBasicDoc::Creep()
{	DigitShowContext* ctx = GetContext();
	// 0: sigma_z, 
	// 1: sigma_r,
	// 2: sigma_zq
	// 3: time (min)
	// 4: Torsinal Speed
	// 5: Axial Speed
	// 6: Cell Pressure Rate
	ctx->StepTime=ctx->StepTime+ctx->CtrlStepTime/60.0;
	ctx->ao.raw[ctx->daCh.AxisMotor]=5.0f;
	ctx->ao.raw[ctx->daCh.AxisSpeed]=float(ctx->ao.cal.a[ctx->daCh.AxisSpeed]*ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]+ctx->ao.cal.b[ctx->daCh.AxisSpeed]);
	ctx->ao.raw[ctx->daCh.TorsionMotor] = 5.0f;
	ctx->ao.raw[ctx->daCh.TorsionSpeed]=float(ctx->ao.cal.a[ctx->daCh.TorsionSpeed]*ctx->controlFile.Para[ctx->controlFile.CurrentNum][4]+ctx->ao.cal.b[ctx->daCh.TorsionSpeed]);
//
	if(ctx->phys.sz > ctx->controlFile.Para[ctx->controlFile.CurrentNum][0]+ctx->err.StressMotor)			ctx->ao.raw[ctx->daCh.AxisClutch]=ctx->volt.Up;
	else if(ctx->phys.sz < ctx->controlFile.Para[ctx->controlFile.CurrentNum][0]-ctx->err.StressMotor)	ctx->ao.raw[ctx->daCh.AxisClutch]=ctx->volt.Down;
	else												ctx->ao.raw[ctx->daCh.AxisSpeed]=0.0f;
	ctx->target.sr=ctx->controlFile.Para[ctx->controlFile.CurrentNum][1];
	if( ctx->controlFile.Para[ctx->controlFile.CurrentNum][6] != 0.0 )	{
		if(ctx->phys.sr < ctx->controlFile.Para[ctx->controlFile.CurrentNum][1]-ctx->err.StressAir) ctx->target.sr=ctx->phys.sr+ctx->controlFile.Para[ctx->controlFile.CurrentNum][6]*ctx->timeSettings.Interval2/1000/60;
		if(ctx->phys.sr > ctx->controlFile.Para[ctx->controlFile.CurrentNum][1]+ctx->err.StressAir) ctx->target.sr=ctx->phys.sr-ctx->controlFile.Para[ctx->controlFile.CurrentNum][6]*ctx->timeSettings.Interval2/1000/60;
		if(fabs(ctx->phys.sr-ctx->controlFile.Para[ctx->controlFile.CurrentNum][1]) <= ctx->err.StressAir) ctx->target.sr=ctx->controlFile.Para[ctx->controlFile.CurrentNum][1];
		ctx->ao.raw[ctx->daCh.EP_Cell]=ctx->ao.raw[ctx->daCh.EP_Cell]+float(0.3*ctx->ao.cal.a[ctx->daCh.EP_Cell]*(ctx->target.sr-ctx->phys.sr));
	}
	if(ctx->phys.szq > ctx->controlFile.Para[ctx->controlFile.CurrentNum][2]+ctx->err.StressMotor)		ctx->ao.raw[ctx->daCh.TorsionClutch]=ctx->volt.CCW;
	else if(ctx->phys.szq < ctx->controlFile.Para[ctx->controlFile.CurrentNum][2]-ctx->err.StressMotor)	ctx->ao.raw[ctx->daCh.TorsionClutch]=ctx->volt.CW;
	else												ctx->ao.raw[ctx->daCh.TorsionSpeed]=0.0f;
	if(ctx->StepTime >= ctx->controlFile.Para[ctx->controlFile.CurrentNum][3]){
		ctx->StepTime=0.0;
		ctx->controlFile.CurrentNum=ctx->controlFile.CurrentNum+1;
	} 
}

void CDigitShowBasicDoc::MonotonicAxialLoadingConstP()
{	DigitShowContext* ctx = GetContext();
	// 0: Compression:0/Extension:1, 
	// 1: sigma_z (kPa), 
	// 2: epsilon_z,
	// 3: Axial Speed,
	// 4: Mean effective principal stress ctx->phys.p' (kPa), 
	// 5: sigma_zq (kPa),
	// 6: Torsional Speed,
	ctx->StepTime=ctx->StepTime+ctx->CtrlStepTime/60.0;
	ctx->ao.raw[ctx->daCh.AxisMotor]=5.0f;
	ctx->ao.raw[ctx->daCh.AxisSpeed]=float(ctx->ao.cal.a[ctx->daCh.AxisSpeed]*ctx->controlFile.Para[ctx->controlFile.CurrentNum][3]+ctx->ao.cal.b[ctx->daCh.AxisSpeed]);
	ctx->ao.raw[ctx->daCh.TorsionMotor] = 5.0f;
	ctx->ao.raw[ctx->daCh.TorsionSpeed]=float(ctx->ao.cal.a[ctx->daCh.TorsionSpeed]*ctx->controlFile.Para[ctx->controlFile.CurrentNum][6]+ctx->ao.cal.b[ctx->daCh.TorsionSpeed]);
	if(ctx->phys.szq > ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]+ctx->err.StressMotor)		ctx->ao.raw[ctx->daCh.TorsionClutch]=ctx->volt.CCW;
	else if(ctx->phys.szq < ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]-ctx->err.StressMotor)	ctx->ao.raw[ctx->daCh.TorsionClutch]=ctx->volt.CW;
	else												ctx->ao.raw[ctx->daCh.TorsionSpeed]=0.0f;
	if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][0]==0.0){
		if(ctx->phys.sz <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][1] && ctx->phys.ez < ctx->controlFile.Para[ctx->controlFile.CurrentNum][2]) {
			ctx->ao.raw[ctx->daCh.AxisClutch]=ctx->volt.Down;
			ctx->target.sr= (3.0*ctx->controlFile.Para[ctx->controlFile.CurrentNum][4]-ctx->phys.sz)/2.0 +ctx->err.StressAir;
			ctx->ao.raw[ctx->daCh.EP_Cell]= ctx->ao.raw[ctx->daCh.EP_Cell] + float(0.1*ctx->ao.cal.a[ctx->daCh.EP_Cell]*(ctx->target.sr-ctx->phys.sr));
		}
		else {
			ctx->controlFile.CurrentNum=ctx->controlFile.CurrentNum+1;
			ctx->StepTime=0.0;
		}
	}
	else if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][0]==1.0){
		if(ctx->phys.sz >= ctx->controlFile.Para[ctx->controlFile.CurrentNum][1] && ctx->phys.ez > ctx->controlFile.Para[ctx->controlFile.CurrentNum][2]) {
			ctx->ao.raw[ctx->daCh.AxisClutch]=ctx->volt.Up;
			ctx->target.sr= (3.0*ctx->controlFile.Para[ctx->controlFile.CurrentNum][4]-ctx->phys.sz)/2.0 -ctx->err.StressAir ;
			ctx->ao.raw[ctx->daCh.EP_Cell]= ctx->ao.raw[ctx->daCh.EP_Cell] + float(0.1*ctx->ao.cal.a[ctx->daCh.EP_Cell]*(ctx->target.sr-ctx->phys.sr));
		}
		else {
			ctx->controlFile.CurrentNum=ctx->controlFile.CurrentNum+1;
			ctx->StepTime=0.0;
		}
	}
}

void CDigitShowBasicDoc::MonotonicTorsionalLoadingConstPA()
{	DigitShowContext* ctx = GetContext();
	//	0: Clockwise:0 / Countercloclwise:1
	//	1: sigma_zq
	//	2: gamma_zq
	//	3: Torsinal Speed
	//	4: Axial Speed
	//	5: Mean effective principal stress ctx->phys.p' (kPa),
	//	6: tan(2*alfa),
	ctx->StepTime=ctx->StepTime+ctx->CtrlStepTime/60.0;
	ctx->ao.raw[ctx->daCh.AxisMotor]=5.0f;
	ctx->ao.raw[ctx->daCh.AxisSpeed]=float(ctx->ao.cal.a[ctx->daCh.AxisSpeed]*ctx->controlFile.Para[ctx->controlFile.CurrentNum][4]+ctx->ao.cal.b[ctx->daCh.AxisSpeed]);
	ctx->ao.raw[ctx->daCh.TorsionMotor]=5.0f;
	ctx->ao.raw[ctx->daCh.TorsionSpeed]=float(ctx->ao.cal.a[ctx->daCh.TorsionSpeed]*ctx->controlFile.Para[ctx->controlFile.CurrentNum][3]+ctx->ao.cal.b[ctx->daCh.TorsionSpeed]);

	if(ctx->controlFile.Para[ctx->controlFile.CurrentNum][0]==0.0){
		if(ctx->phys.szq < ctx->controlFile.Para[ctx->controlFile.CurrentNum][1] && ctx->phys.gzq1 < ctx->controlFile.Para[ctx->controlFile.CurrentNum][2])	{
			ctx->ao.raw[ctx->daCh.TorsionClutch] = ctx->volt.CW;
			ctx->target.sr= (3.0*ctx->controlFile.Para[ctx->controlFile.CurrentNum][5] - 2.0*ctx->phys.szq/ctx->controlFile.Para[ctx->controlFile.CurrentNum][6])/3.0 +ctx->err.StressAir;
			ctx->ao.raw[ctx->daCh.EP_Cell]= ctx->ao.raw[ctx->daCh.EP_Cell] + float(0.1*ctx->ao.cal.a[ctx->daCh.EP_Cell]*(ctx->target.sr-ctx->phys.sr));
			ctx->target.sz= (3.0*ctx->controlFile.Para[ctx->controlFile.CurrentNum][5] + 4.0*ctx->phys.szq/ctx->controlFile.Para[ctx->controlFile.CurrentNum][6])/3.0 +ctx->err.StressMotor;
			if(ctx->phys.sz > ctx->target.sz+ctx->err.StressMotor)	ctx->ao.raw[ctx->daCh.AxisClutch]=ctx->volt.Up;
			else if(ctx->phys.sz < ctx->target.sz-ctx->err.StressMotor)	ctx->ao.raw[ctx->daCh.AxisClutch]=ctx->volt.Down;
			else	ctx->ao.raw[ctx->daCh.AxisSpeed]=0.0f;
		}
		else {
			ctx->StepTime = 0.0;
			ctx->controlFile.CurrentNum = ctx->controlFile.CurrentNum + 1;
		}
	}
	else if (ctx->controlFile.Para[ctx->controlFile.CurrentNum][0] == 1.0) {
		if (ctx->phys.szq > ctx->controlFile.Para[ctx->controlFile.CurrentNum][1] && ctx->phys.gzq1 > ctx->controlFile.Para[ctx->controlFile.CurrentNum][2]) {
			ctx->ao.raw[ctx->daCh.TorsionClutch] = ctx->volt.CCW;
			ctx->target.sr = (3.0 * ctx->controlFile.Para[ctx->controlFile.CurrentNum][5] - 2.0 * ctx->phys.szq / ctx->controlFile.Para[ctx->controlFile.CurrentNum][6]) / 3.0 - ctx->err.StressAir;
			ctx->ao.raw[ctx->daCh.EP_Cell] = ctx->ao.raw[ctx->daCh.EP_Cell] + float(0.1 * ctx->ao.cal.a[ctx->daCh.EP_Cell] * (ctx->target.sr - ctx->phys.sr));
			ctx->target.sz= (3.0*ctx->controlFile.Para[ctx->controlFile.CurrentNum][5] + 4.0*ctx->phys.szq/ctx->controlFile.Para[ctx->controlFile.CurrentNum][6])/3.0 -ctx->err.StressMotor;
			if(ctx->phys.sz > ctx->target.sz+ctx->err.StressMotor)	ctx->ao.raw[ctx->daCh.AxisClutch]=ctx->volt.Up;
			else if(ctx->phys.sz < ctx->target.sz-ctx->err.StressMotor)	ctx->ao.raw[ctx->daCh.AxisClutch]=ctx->volt.Down;
			else	ctx->ao.raw[ctx->daCh.AxisSpeed]=0.0f;
		}
		else {
			ctx->StepTime=0.0;
			ctx->controlFile.CurrentNum=ctx->controlFile.CurrentNum+1;
		}
	}
}

// 2021.06.07 Edited by M.Kuno
// customize for Sanjei	
void CDigitShowBasicDoc::CyclicAxialLoading_OR()
{	DigitShowContext* ctx = GetContext();
	// 0: Loading:0/Unloading:1, 
	// 1: sigma_z_lower, 
	// 2: sigma_z_upper, 
	// 3: epsilon_z_lower,
	// 4: epsilon_z_upper,
	// 5: Number,
	// 6: Axial Speed
	ctx->StepTime = ctx->StepTime + ctx->CtrlStepTime / 60.0;
	ctx->ao.raw[ctx->daCh.AxisMotor] = 5.0f;
	ctx->ao.raw[ctx->daCh.AxisSpeed] = float(ctx->ao.cal.a[ctx->daCh.AxisSpeed] * ctx->controlFile.Para[ctx->controlFile.CurrentNum][6] + ctx->ao.cal.b[ctx->daCh.AxisSpeed]);
	if (ctx->controlFile.Para[ctx->controlFile.CurrentNum][0] == 0.0) {
		if (ctx->NumCyclic == 0) {
			ctx->flags.Cyclic = FALSE;
			ctx->NumCyclic = 1;
		}
		if (ctx->NumCyclic != 0 && ctx->NumCyclic <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]) {
			if (ctx->flags.Cyclic == FALSE) {
				if (ctx->phys.sz <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][2] && ctx->phys.ez <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][4])	ctx->ao.raw[ctx->daCh.AxisClutch] = ctx->volt.Down;
				else	ctx->flags.Cyclic = TRUE;
			}
			else {
				if (ctx->phys.sz >= ctx->controlFile.Para[ctx->controlFile.CurrentNum][1] || ctx->phys.ez >= ctx->controlFile.Para[ctx->controlFile.CurrentNum][3]) ctx->ao.raw[ctx->daCh.AxisClutch] = ctx->volt.Up;
				else {
					ctx->flags.Cyclic = FALSE;
					ctx->NumCyclic = ctx->NumCyclic + 1;
				}
			}
		}
		if (ctx->NumCyclic > ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]) {
			ctx->controlFile.CurrentNum = ctx->controlFile.CurrentNum + 1;
			ctx->StepTime = 0.0;
			ctx->NumCyclic = 0;
		}
	}
	else if (ctx->controlFile.Para[ctx->controlFile.CurrentNum][0] == 1.0) {
		if (ctx->NumCyclic == 0) {
			ctx->flags.Cyclic = TRUE;
			ctx->NumCyclic = 1;
		}
		if (ctx->NumCyclic != 0 && ctx->NumCyclic <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][2]) {
			if (ctx->flags.Cyclic == FALSE) {
				if (ctx->phys.sz <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][2] || ctx->phys.ez <= ctx->controlFile.Para[ctx->controlFile.CurrentNum][4])	ctx->ao.raw[ctx->daCh.AxisClutch] = ctx->volt.Down;
				else {
					ctx->flags.Cyclic = TRUE;
					ctx->NumCyclic = ctx->NumCyclic + 1;
				}
			}
			else {
				if (ctx->phys.sz >= ctx->controlFile.Para[ctx->controlFile.CurrentNum][1] && ctx->phys.ez >= ctx->controlFile.Para[ctx->controlFile.CurrentNum][3]) ctx->ao.raw[ctx->daCh.AxisClutch] = ctx->volt.Up;
				else	ctx->flags.Cyclic = FALSE;
			}
		}
		if (ctx->NumCyclic > ctx->controlFile.Para[ctx->controlFile.CurrentNum][5]) {
			ctx->controlFile.CurrentNum = ctx->controlFile.CurrentNum + 1;
			ctx->StepTime = 0.0;
			ctx->NumCyclic = 0;
		}
	}
}

void CDigitShowBasicDoc::Rs232c_Open()
{	DigitShowContext* ctx = GetContext();
//---Open RS232C: COM1---
	ctx->rs232c.hEvent=CreateEvent(0, TRUE, FALSE, NULL);
	//Open COM1
	ctx->rs232c.hComm[0] = CreateFile(ctx->rs232c.CommName[0],GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
	if(ctx->rs232c.hComm[0]!=INVALID_HANDLE_VALUE){
		AfxMessageBox("Succeded in open of COM1", MB_ICONINFORMATION | MB_OK );
		ctx->flags.COM[0]=TRUE;
		GetCommState(ctx->rs232c.hComm[0],&ctx->rs232c.CommDCB[0]);
		ctx->rs232c.CommDCB[0].fBinary=TRUE;
		ctx->rs232c.CommDCB[0].fRtsControl = RTS_CONTROL_ENABLE;
		ctx->rs232c.CommDCB[0].fDtrControl = DTR_CONTROL_ENABLE;
		ctx->rs232c.CommDCB[0].BaudRate=CBR_2400;				// BaudRate 2400;
		ctx->rs232c.CommDCB[0].ByteSize=7;						// Bit length:7bit 
		ctx->rs232c.CommDCB[0].Parity=2;						// 0-4=no,odd,even,mark,space 
		ctx->rs232c.CommDCB[0].StopBits=0;						// 0,1,2 = 1Bit, 1.5Bit, 2Bit 
		SetCommState(ctx->rs232c.hComm[0],&ctx->rs232c.CommDCB[0]);
		ctx->flags.SetRs232c=TRUE;
	}
	ctx->rs232c.ReadBuffer1.Empty();
	ctx->rs232c.ReadBuffer2.Empty();
	ctx->rs232c.WriteBuffer1.Empty();
	ctx->rs232c.WriteBuffer2.Empty();
	ctx->rs232c.TmpBuffer.Empty();
}

void CDigitShowBasicDoc::Rs232c_Close()
{	DigitShowContext* ctx = GetContext();
	if(ctx->flags.SetRs232c){
		if(ctx->flags.COM[0])	{
			CloseHandle(ctx->rs232c.hComm[0]);
			ctx->flags.COM[0]=FALSE;
		}
		ctx->flags.SetRs232c=FALSE;
	}
	CloseHandle(ctx->rs232c.hEvent);
}

void CDigitShowBasicDoc::Rs232c_SendData()
{	DigitShowContext* ctx = GetContext();
	DWORD	NoOfByte;
	ctx->rs232c.WriteBuffer1+="\r\n";
	WriteFile(ctx->rs232c.hComm[0],ctx->rs232c.WriteBuffer1,ctx->rs232c.WriteBuffer1.GetLength(),&NoOfByte,NULL);
//	WaitForSingleObject(ctx->rs232c.hEvent,300);
//	ResetEvent(ctx->rs232c.hEvent);
}

void CDigitShowBasicDoc::Rs232c_GetData()
{	DigitShowContext* ctx = GetContext();
	DWORD NoOfByte,Error;
	ctx->rs232c.ReadBuffer1.Empty();
	ClearCommError(ctx->rs232c.hComm[0],&Error,&ctx->rs232c.Comstat1);
	if(ctx->rs232c.Comstat1.cbInQue){
		ReadFile(ctx->rs232c.hComm[0],ctx->rs232c.ReadBuffer1.GetBuffer(ctx->rs232c.Comstat1.cbInQue),ctx->rs232c.Comstat1.cbInQue,&NoOfByte,NULL);
		ctx->rs232c.ReadBuffer1.ReleaseBuffer();
	}
}

void CDigitShowBasicDoc::Rs232c_GetWeight()
{	DigitShowContext* ctx = GetContext();
	int		i,j;
	Rs232c_GetData();
	ctx->rs232c.TmpBuffer = ctx->rs232c.TmpBuffer + ctx->rs232c.ReadBuffer1;
	i=ctx->rs232c.TmpBuffer.Find('S',0);
	j=ctx->rs232c.TmpBuffer.Find('g',i+1);
	if( i != -1 && j != -1 ){
		ctx->rs232c.TmpBuffer = ctx->rs232c.TmpBuffer.Mid(i+4,8);
		ctx->phys.BW1=atof(ctx->rs232c.TmpBuffer)*1000.0;
		ctx->rs232c.TmpBuffer.Empty();
	}
	ctx->phys.BW2=ctx->phys.BW1;
}


