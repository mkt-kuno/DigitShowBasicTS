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

#ifndef __DIGITSHOWCONTEXT_H_INCLUDE__
#define __DIGITSHOWCONTEXT_H_INCLUDE__

#pragma once

#include <afxwin.h>
#include <stdio.h>

// ── Array sizes ──────────────────────────────────────────
#define AI_MAX_CHANNELS     32  // AI channels (primary board Ch00-15 + second board Ch16-31)
#define AO_MAX_CHANNELS     16  // AO channels
#define AD_MAX_BOARDS        2  // Number of A/D boards (NUMAD = 0-2)
#define DA_MAX_BOARDS        1  // Number of D/A boards (NUMDA = 0-1)
#define CONTROL_MAX         16  // Number of control target data sets
#define CONTROLFILE_STEPS  256  // Number of steps in a control file
#define CONTROLFILE_PARAS   16  // Number of parameters per control file step
#define NAME_DV_MAX          8  // Number of D/A channel names

// Raw transfer buffer size [samples] (64 MiB / board, same as legacy globals)
#define AD_BUFFER_SIZE 16777216L
#define DA_BUFFER_SIZE     262144L

// ── D/A channel index assignments (fixed hardware wiring) ──
#define DA_CH_EP_CELL         0  // EP cell pressure
#define DA_CH_AXIS_MOTOR      1  // Axial motor On/Off (0V = On, 5V = Off)
#define DA_CH_AXIS_CLUTCH     2  // Axial clutch
#define DA_CH_AXIS_SPEED      3  // Axial motor speed
#define DA_CH_TORSION_MOTOR   4  // Torsion motor On/Off (0V = On, 5V = Off)
#define DA_CH_TORSION_CLUTCH  5  // Torsion clutch
#define DA_CH_TORSION_SPEED   6  // Torsion motor speed

/**
 * CAIO board configuration (CONTEC AIO-WDM)
 */
struct AdBoardConfig {
	short  Id;              // ID returned by AioInit
	short  Channels;        // number of enabled channels
	short  Range;           // range code
	float  RangeMax;        // maximum voltage of the range
	float  RangeMin;        // minimum voltage of the range
	short  Resolution;      // resolution [bit]
	short  InputMethod;     // single-ended / differential
	short  MemoryType;      // FIFO / RING
	float  ScanClock;       // scan clock [us/ch]
	float  SamplingClock;   // sampling clock [us]
	long   SamplingTimes;   // sampling times per event
};

struct DaBoardConfig {
	short  Id;
	short  Channels;
	short  Range;
	float  RangeMax;
	float  RangeMin;
	short  Resolution;
};

/**
 * Specimen data (hollow cylinder)
 */
struct SpecimenData {
	double DiameterIn[4];       double DiameterOut[4];
	double Height[4];
	double Volume[4];
	double MembraneModulus;     double MembraneThickness;
	double RodArea;             double CapWeight;
	double RDiaInM;             double RDiaOutM;
	double RHeightInM;          double RHeightOutM;
	double DiaInMembrane[4];    double DiaOutMembrane[4];
	double HeightInMembrane[4]; double HeightOutMembrane[4];
};

/**
 * Control target data per control ID
 */
struct ControlData {
	bool   flag[3];
	int    time[3];
	double p[3];
	double q[3];
	double u[3];
	double sigma[3];
	double sigmaRate[3];
	double sigmaAmp[3];
	double strain[3];
	double strainRate[3];
	double strainAmp[3];
	double K0;
	double AxisClutch;
	double AxisSpeed;
	double TorsionClutch;
	double TorsionSpeed;
};

/**
 * Physical values computed by Cal_Physical() / Cal_Param()
 */
struct PhysicalValues {
	double rotation1;           // POT1 angle [rad]
	double rotation2;           // POT2 angle [rad]
	double BW1;                 // balance weight 1
	double BW2;                 // balance weight 2
	double height;              // current specimen height
	double area;                // current specimen area
	double volume;              // current specimen volume
	double diameter_in;         // current inner diameter
	double diameter_out;        // current outer diameter
	double diameterInM;         // current inner membrane diameter
	double diameterOutM;        // current outer membrane diameter
	double heightInM;           // current inner membrane height
	double heightOutM;          // current outer membrane height
	double cell_in;             // inner cell pressure
	double cell_out;            // outer cell pressure
	double sz;                  // axial stress
	double sr;                  // radial stress
	double sq;                  // circumferential stress
	double szq;                 // shear stress
	double p;                   // mean stress
	double q;                   // deviatoric stress
	double ez;                  // axial strain
	double er;                  // radial strain
	double eq;                  // circumferential strain
	double gzq1;                // shear strain 1
	double gzq2;                // shear strain 2
	double ev;                  // volumetric strain
	double ezInM;               // inner membrane axial strain
	double ezOutM;              // outer membrane axial strain
	double eqInM;               // inner membrane circumferential strain
	double eqOutM;              // outer membrane circumferential strain
	double gzqInM;              // inner membrane shear strain
	double gzqOutM;             // outer membrane shear strain
	double PressureInM;         // inner membrane pressure
	double PressureOutM;        // outer membrane pressure
	double ForceM;              // membrane axial force
	double TorqueM;             // membrane resistance torque
};

/**
 * Control file data (File Controllable Consolidation)
 */
struct ControlFileData {
	int    CurrentNum;
	int    Num[CONTROLFILE_STEPS];
	double Para[CONTROLFILE_STEPS][CONTROLFILE_PARAS];
};

/**
 * Timer intervals [ms]
 */
struct TimeSettings {
	unsigned int Interval1;  // Timer 1: acquisition / display
	unsigned int Interval2;  // Timer 2: control feedback
	unsigned int Interval3;  // Timer 3: data save
};

/**
 * System flags
 */
struct SystemFlags {
	bool SetBoard;    // board initialization accomplished
	bool SaveData;    // saving data to file
	bool FIFO;        // FIFO acquisition running
	bool Cyclic;      // cyclic loading running
	bool SetRs232c;   // RS232C port opened
	bool SetBalance;  // electronic balance connected
	bool COM[2];      // COM port status
};

/**
 * Main application context structure.
 * Single global instance replaces the former scattered extern variables.
 */
struct DigitShowContext {
	// CAIO return codes / error strings
	long   Ret;
	long   Ret2;
	char   ErrorString[256];
	CString TextString;

	// Boards
	int            NumAD;                    // number of A/D boards (0-2)
	int            NumDA;                    // number of D/A boards (0-1)
	AdBoardConfig  ad[AD_MAX_BOARDS];
	DaBoardConfig  da[DA_MAX_BOARDS];

	// Raw transfer buffers
	long   DaData[DA_BUFFER_SIZE];
	long   AdData0[AD_BUFFER_SIZE];
	long   AdData1[AD_BUFFER_SIZE];
	PVOID  pSmplData[AD_MAX_BOARDS];         // save buffer source
	HANDLE hHeap[AD_MAX_BOARDS];

	// Acquisition state
	int   AdMaxCH;
	long  AdEvent;
	float SavingClock;                       // [us] current saving clock
	int   SavingTime;                        // [s] total saving time
	long  TotalSamplingTimes;
	long  CurrentSamplingTimes;
	float AllocatedMemory;                   // [MiB]
	int   AvSmplNum;                         // number of samples averaged for display

	// Channel names
	CString NameV[AI_MAX_CHANNELS];          // voltage channel names
	CString NameP[AI_MAX_CHANNELS];          // physical channel names
	CString NameDV[NAME_DV_MAX];             // D/A channel names

	// Analog input measurement data
	struct {
		float  raw[AI_MAX_CHANNELS];         // averaged ADC voltages [V]
		double phy[AI_MAX_CHANNELS];         // calibrated physical values
		double param[AI_MAX_CHANNELS];       // derived parameters for display
		struct {
			double a[AI_MAX_CHANNELS];       // quadratic coefficient
			double b[AI_MAX_CHANNELS];       // linear coefficient
			double c[AI_MAX_CHANNELS];       // offset
		} cal;
	} ai;

	// Analog output setpoints
	struct {
		float  raw[AO_MAX_CHANNELS];         // output voltages [V]
		struct {
			double a[AO_MAX_CHANNELS];       // gain
			double b[AO_MAX_CHANNELS];       // offset
		} cal;
	} ao;

	// Physical values
	PhysicalValues phys;

	// Specimen and control
	SpecimenData  specimen;
	ControlData   control[CONTROL_MAX];
	ControlFileData controlFile;

	// D/A channel index assignments
	struct {
		int EP_Cell;
		int AxisMotor;
		int AxisClutch;
		int AxisSpeed;
		int TorsionMotor;
		int TorsionClutch;
		int TorsionSpeed;
	} daCh;

	// Motor drive voltages
	struct {
		float Up;                            // on voltage
		float Down;                          // off voltage
		float CW;                            // clockwise voltage
		float CCW;                           // counter-clockwise voltage
	} volt;

	// Control state
	int    ControlID;
	int    NumCyclic;
	int    NumSmallCyclic;
	double StepTime;
	int    StepDisplay;
	int    AmpID;                            // current amplifier / channel ID in calibration dialogs

	// Control targets
	struct {
		double sz;
		double sr;
		double tzq;
		double ez;
		double gzq;
	} target;

	// Error tolerances
	struct {
		double StressMotor;                  // stress control sensitivity (motor) [kPa]
		double StressAir;                    // stress control sensitivity (air) [kPa]
		double StrainEz;                     // axial strain sensitivity
		double StrainGzq;                    // shear strain sensitivity
	} err;

	// System flags
	SystemFlags flags;

	// Time management
	TimeSettings timeSettings;
	CTime        StartTime;
	CTime        NowTime;
	CTimeSpan    SpanTime;
	CString      SNowTime;
	long         SequentTime1;
	double       SequentTime2;
	double       CtrlStepTime;

	// Data file handles
	FILE* FileSaveData0;                     // voltage value log
	FILE* FileSaveData1;                     // physical value log
	FILE* FileSaveData2;                     // parameter value log

	// RS232C (electronic balance)
	struct {
		HANDLE   hComm[2];
		DCB      CommDCB[2];
		CString  CommName[2];
		COMSTAT  Comstat1;
		COMSTAT  Comstat2;
		CString  ReadBuffer1;
		CString  ReadBuffer2;
		CString  WriteBuffer1;
		CString  WriteBuffer2;
		CString  TmpBuffer;
		HANDLE   hEvent;
	} rs232c;
};

/**
 * Get the global context instance (singleton)
 */
DigitShowContext* GetContext();

/**
 * Initialize the context with default values
 */
void InitContext(DigitShowContext* ctx);

#endif // __DIGITSHOWCONTEXT_H_INCLUDE__
