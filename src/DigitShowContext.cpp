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

#include "stdafx.h"
#include "DigitShowContext.h"

// Singleton instance
static DigitShowContext g_Context;
static bool g_ContextInitialized = false;

DigitShowContext* GetContext()
{
	if (!g_ContextInitialized) {
		InitContext(&g_Context);
		g_ContextInitialized = true;
	}
	return &g_Context;
}

void InitContext(DigitShowContext* ctx)
{
	if (ctx == NULL) return;

	int	i, j;

	// CAIO return codes / error strings
	ctx->Ret = 0;
	ctx->Ret2 = 0;
	memset(ctx->ErrorString, 0, sizeof(ctx->ErrorString));
	ctx->TextString = _T("");

	// Boards (zero all POD fields)
	for (i = 0; i < AD_MAX_BOARDS; i++) {
		memset(&ctx->ad[i], 0, sizeof(ctx->ad[i]));
	}
	for (i = 0; i < DA_MAX_BOARDS; i++) {
		memset(&ctx->da[i], 0, sizeof(ctx->da[i]));
	}
	ctx->NumAD = 1;		// The Number of A/D Board ( NUMAD=0-2 )
	ctx->NumDA = 1;		// The Number of D/A Board ( NUMDA=0-1 )

	// Raw transfer buffers
	memset(ctx->DaData, 0, sizeof(ctx->DaData));
	memset(ctx->AdData0, 0, sizeof(ctx->AdData0));
	memset(ctx->AdData1, 0, sizeof(ctx->AdData1));
	for (i = 0; i < AD_MAX_BOARDS; i++) {
		ctx->pSmplData[i] = NULL;
		ctx->hHeap[i] = NULL;
	}

	// Acquisition state
	ctx->AdMaxCH = 0;
	ctx->AdEvent = 0;
	ctx->SavingClock = 0.0f;
	ctx->SavingTime = 300;
	ctx->TotalSamplingTimes = 0;
	ctx->CurrentSamplingTimes = 0;
	ctx->AllocatedMemory = 0.0f;
	ctx->AvSmplNum = 10;

	// Analog input measurement data
	for (i = 0; i < AI_MAX_CHANNELS; i++) {
		ctx->ai.raw[i] = 0.0f;
		ctx->ai.phy[i] = 0.0;
		ctx->ai.param[i] = 0.0;
		ctx->ai.cal.a[i] = 0.0;
		ctx->ai.cal.b[i] = 1.0;
		ctx->ai.cal.c[i] = 0.0;
	}

	// Analog output setpoints
	for (i = 0; i < AO_MAX_CHANNELS; i++) {
		ctx->ao.raw[i] = 0.0f;
		ctx->ao.cal.a[i] = 0.0;
		ctx->ao.cal.b[i] = 0.0;
	}

	// Channel names
//  @note Hashimoto modified 2022.2.28
	ctx->NameV[0]=_T("V.Load");		ctx->NameP[0]=_T("V.Load,N");
	ctx->NameV[1]=_T("T.Load ");	ctx->NameP[1]=_T("Torque,Ncm");
	ctx->NameV[2]=_T("POT1");		ctx->NameP[2]=_T("POT1,rad");
	ctx->NameV[3]=_T("POT2");		ctx->NameP[3]=_T("POT2,rad");
	ctx->NameV[4]=_T("HCDPT");		ctx->NameP[4]=_T("EffectiveStress,kPa");
	ctx->NameV[5]=_T("ExtLVDT");	ctx->NameP[5]=_T("V.DispEXT,mm");
	ctx->NameV[6]=_T("LDT1");	    ctx->NameP[6]=_T("LDT1,mm");
	ctx->NameV[7]=_T("CH7");		ctx->NameP[7]=_T("CH7");
	ctx->NameV[8]=_T("CG1");		ctx->NameP[8]=_T("CG1,mm");
	ctx->NameV[9]=_T("CG2");		ctx->NameP[9]=_T("CG2,mm");
	ctx->NameV[10]=_T("CG3");		ctx->NameP[10]=_T("CG3,mm");
	ctx->NameV[11]=_T("LDT2");		ctx->NameP[11]=_T("LDT2,mm");
	ctx->NameV[12]=_T("CH12");		ctx->NameP[12]=_T("CH12");
	ctx->NameV[13]=_T("LCDPT");		ctx->NameP[13]=_T("DeltaVol.,mm3");
	ctx->NameV[14]=_T("CH14");		ctx->NameP[14]=_T("CH14");
	ctx->NameV[15]=_T("CH15");		ctx->NameP[15]=_T("CH15");
	for (i = 16; i < AI_MAX_CHANNELS; i++) {
		CString tmp;
		tmp.Format("CH%d", i);
		ctx->NameV[i]=tmp;
		ctx->NameP[i]=tmp;
	}
	ctx->NameDV[0]=_T("CH00: EP cell pressure");
	ctx->NameDV[1]=_T("CH01: Axial Motor");
	ctx->NameDV[2]=_T("CH02: Axial Clutch");
	ctx->NameDV[3]=_T("CH03: Axial Motor Speed");
	ctx->NameDV[4]=_T("CH04: Torsional Motor");
	ctx->NameDV[5]=_T("CH05: Torsional Clutch");
	ctx->NameDV[6]=_T("CH06: Torsional Motor Speed");

	// Physical values
	memset(&ctx->phys, 0, sizeof(ctx->phys));

	// Specimen data
	for (j = 0; j < 4; j++) {
		ctx->specimen.DiameterIn[j]=60.0;
		ctx->specimen.DiameterOut[j]=100.0;
		ctx->specimen.Height[j]=150.0;
		ctx->specimen.Volume[j]=3.141592*(100.0*100.0-60.0*60.0)/4*150.0;
		ctx->specimen.DiaInMembrane[j]=60.0;
		ctx->specimen.DiaOutMembrane[j]=100.0;
		ctx->specimen.HeightInMembrane[j]=150.0;
		ctx->specimen.HeightOutMembrane[j]=150.0;
	}
	ctx->specimen.MembraneModulus=1400.0;
	ctx->specimen.MembraneThickness=0.3;
	//ctx->specimen.RDiaInM=60.0;
	//ctx->specimen.RDiaOutM=100.0;
	ctx->specimen.RDiaInM = 59.85; //@note Hashimoto fixed 2022.12.22
	ctx->specimen.RDiaOutM = 100.15; //@note Hashimoto fixed 2022.12.22
	ctx->specimen.RHeightInM=150.0; //@note Hashimoto fixed 2022.12.22
	ctx->specimen.RHeightOutM=150.0; //@note Hashimoto fixed 2022.12.22
	ctx->specimen.RodArea=0.0;
	ctx->specimen.CapWeight=0.0;

	// Control target data
	for (i = 0; i < CONTROL_MAX; i++) {
		for (j = 0; j < 3; j++) {
			ctx->control[i].flag[j]=FALSE;
			ctx->control[i].time[j]=0;
			ctx->control[i].p[j]=0.0;
			ctx->control[i].q[j]=0.0;
			ctx->control[i].u[j]=0.0;
			ctx->control[i].sigma[j]=0.0;
			ctx->control[i].sigmaRate[j]=0.0;
			ctx->control[i].sigmaAmp[j]=0.0;
			ctx->control[i].strain[j]=0.0;
			ctx->control[i].strainRate[j]=0.0;
			ctx->control[i].strainAmp[j]=0.0;
		}
		ctx->control[i].K0=1.0;
		ctx->control[i].AxisSpeed=0.0;
		ctx->control[i].TorsionSpeed=0.0;
	}
	ctx->control[1].q[0]=1.0;
	ctx->control[1].AxisSpeed = 100.0;

	// D/A channel index assignments
	ctx->daCh.EP_Cell         = DA_CH_EP_CELL;        // D/A Channel of EP (Cell Pressure)
	ctx->daCh.AxisMotor       = DA_CH_AXIS_MOTOR;     // 0V:On, 5V:Off
	ctx->daCh.AxisClutch      = DA_CH_AXIS_CLUTCH;    //
	ctx->daCh.AxisSpeed       = DA_CH_AXIS_SPEED;     //
	ctx->daCh.TorsionMotor    = DA_CH_TORSION_MOTOR;  // 0V:On, 5V:Off
	ctx->daCh.TorsionClutch   = DA_CH_TORSION_CLUTCH; //
	ctx->daCh.TorsionSpeed    = DA_CH_TORSION_SPEED;  //

	// Motor drive voltages
	ctx->volt.Down = 0.0f;
	ctx->volt.Up   = 5.0f;
	ctx->volt.CW   = 0.0f;
	ctx->volt.CCW  = 5.0f;

	// D/A calibration factors
	ctx->ao.cal.a[DA_CH_AXIS_SPEED]=0.0033333;     // Axial Motor Speed (V/RPM)
	ctx->ao.cal.b[DA_CH_AXIS_SPEED]=0.0;
	ctx->ao.cal.a[DA_CH_TORSION_SPEED]=0.0034483;  // Torsion Motor Speed (V/RPM)
	ctx->ao.cal.b[DA_CH_TORSION_SPEED]=0.0;
	ctx->ao.cal.a[DA_CH_EP_CELL]=0.0175;           // EP of Cell Pressure (V/kPa)
	ctx->ao.cal.b[DA_CH_EP_CELL]=0.0;

	// Control state
	ctx->ControlID = 0;
	ctx->NumCyclic = 0;
	ctx->NumSmallCyclic = 0;
	ctx->StepTime = 0.0;
	ctx->StepDisplay = 0;                          // 2021.12.07 Edited by M.Kuno

	// Control targets
	ctx->target.sz = 0.0;
	ctx->target.sr = 0.0;
	ctx->target.tzq = 0.0;
	ctx->target.ez = 0.0;
	ctx->target.gzq = 0.0;

	// Error tolerances
	ctx->err.StressMotor= 0.5;                     // (kPa)
	ctx->err.StressAir  = 0.5;                     // (kPa)
	ctx->err.StrainEz   = 0.0005;                  // (---)
	ctx->err.StrainGzq  = 0.0005;                  // (---)

	// System flags
	ctx->flags.SetBoard = FALSE;
	ctx->flags.SaveData = FALSE;
	ctx->flags.FIFO = FALSE;
	ctx->flags.Cyclic = FALSE;

	// Time management
	ctx->timeSettings.Interval1 = 200;             // Time interval (ms) to display output data.
	ctx->timeSettings.Interval2 = 500;             // Time interval (ms) to control.
	ctx->timeSettings.Interval3 = 1000;            // Time interval (ms) to save the data.
	ctx->SequentTime1 = 0;
	ctx->SequentTime2 = 0.0;
	ctx->CtrlStepTime = 0.0;

	// Data file handles
	ctx->FileSaveData0 = NULL;
	ctx->FileSaveData1 = NULL;
	ctx->FileSaveData2 = NULL;

	// Control file data
	ctx->controlFile.CurrentNum = 0;
	for (i = 0; i < CONTROLFILE_STEPS; i++) {
		ctx->controlFile.Num[i] = 0;
		for (j = 0; j < CONTROLFILE_PARAS; j++) {
			ctx->controlFile.Para[i][j] = 0.0;
		}
	}
}
