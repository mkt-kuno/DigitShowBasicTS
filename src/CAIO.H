//==============================================================================================
//	API-AIO(WDM) Definition File																
//==============================================================================================

//----------------------------------------------------------------------------------------------
//	External Control Signal																		
//----------------------------------------------------------------------------------------------
#define	AIO_AIF_CLOCK				0	//Analog input external clock
#define	AIO_AIF_START				1	//Analog input external start trigger
#define	AIO_AIF_STOP				2	//Analog input external stop trigger
#define	AIO_AOF_CLOCK				3	//Analog output external clock
#define	AIO_AOF_START				4	//Analog output external start trigger
#define	AIO_AOF_STOP				5	//Analog output external stop trigger

//----------------------------------------------------------------------------------------------
//	Input/Output Range																			
//----------------------------------------------------------------------------------------------
#define	PM10						0	//+/-10V
#define	PM5							1	//+/-5V
#define	PM25						2	//+/-2.5V
#define	PM125						3	//+/-1.25V
#define	PM1							4	//+/-1V
#define	PM0625						5	//+/-0.625V
#define	PM05						6	//+/-0.5V
#define	PM03125						7	//+/-0.3125V
#define	PM025						8	//+/-0.25V
#define	PM0125						9	//+/-0.125V
#define	PM01						10	//+/-0.1V
#define	PM005						11	//+/-0.05V
#define	PM0025						12	//+/-0.025V
#define	PM00125						13	//+/-0.0125V
#define	PM001						14	//+/-0.01V
#define	P10							50	//0 ~ 10V
#define	P5							51	//0 ~ 5V
#define	P4095						52	//0 ~ 4.095V
#define	P25							53	//0 ~ 2.5V
#define	P125						54	//0 ~ 1.25V
#define	P1							55	//0 ~ 1V
#define	P05							56	//0 ~ 0.5V
#define	P025						57	//0 ~ 0.25V
#define	P01							58	//0 ~ 0.1V
#define	P005						59	//0 ~ 0.05V
#define	P0025						60	//0 ~ 0.025V
#define	P00125						61	//0 ~ 0.0125V
#define	P001						62	//0 ~ 0.01V
#define	P20MA						100	//0 ~ 20mA
#define	P4TO20MA					101	//4 ~ 20mA
#define PM20MA						102 //+/20mA
#define	P1TO5						150	//1 ~ 5V

//----------------------------------------------------------------------------------------------
//	Analog Input Event																
//----------------------------------------------------------------------------------------------
#define	AIE_START			0x00000002	//Event that AD converting start conditions are satisfied
#define	AIE_RPTEND			0x00000010	//Event of repeat end
#define	AIE_END				0x00000020	//Event of device operation end
#define	AIE_DATA_NUM		0x00000080	//Event that data of the specified sampling times are stored
#define	AIE_DATA_TSF		0x00000100	//Event that data of the specified number are transferred
#define	AIE_OFERR			0x00010000	//Event of Overflow
#define	AIE_SCERR			0x00020000	//Event of sampling clock error
#define	AIE_ADERR			0x00040000	//Event of AD converting error

//----------------------------------------------------------------------------------------------
//	Analog Output Event																		
//----------------------------------------------------------------------------------------------
#define	AOE_START			0x00000002	//Event that DA converting start conditions are satisfied
#define	AOE_RPTEND			0x00000010	//Event of repeat end
#define	AOE_END				0x00000020	//Event of device operation end
#define	AOE_DATA_NUM		0x00000080	//Event that data of the specified sampling times are output
#define	AOE_DATA_TSF		0x00000100	//Event that data of the specified number are transferred
#define	AOE_SCERR			0x00020000	//Event of sampling clock error
#define	AOE_DAERR			0x00040000	//Event of DA converting error

//----------------------------------------------------------------------------------------------
//	Counter Event																			
//----------------------------------------------------------------------------------------------
#define	CNTE_DATA_NUM		0x00000010	//Event of count comparison match
#define	CNTE_ORERR			0x00010000	//Event of count overrun
#define	CNTE_ERR			0x00020000	//Counter operating error

//----------------------------------------------------------------------------------------------
//	Timer Event																				
//----------------------------------------------------------------------------------------------
#define	TME_INT				0x00000001	//Event that interval is satisfied

//----------------------------------------------------------------------------------------------
//	Analog Input Status																		
//----------------------------------------------------------------------------------------------
#define	AIS_BUSY			0x00000001	//Device is working
#define	AIS_START_TRG		0x00000002	//Wait the start trigger
#define	AIS_DATA_NUM		0x00000010	//Store the data of the specified number of samplings
#define	AIS_OFERR			0x00010000	//Overflow
#define	AIS_SCERR			0x00020000	//Sampling clock error
#define	AIS_AIERR			0x00040000	//AD converting error
#define	AIS_DRVERR			0x00080000	//Driver spec error

//----------------------------------------------------------------------------------------------
//	Analog Output Status																		
//----------------------------------------------------------------------------------------------
#define	AOS_BUSY			0x00000001	//Device is working
#define	AOS_START_TRG		0x00000002	///Wait the start trigger
#define	AOS_DATA_NUM		0x00000010	//Output the data of the specified number of samplings
#define	AOS_SCERR			0x00020000	//Sampling clock error
#define	AOS_AOERR			0x00040000	//DA converting error
#define	AOS_DRVERR			0x00080000	//Driver spec error

//----------------------------------------------------------------------------------------------
//	Counter Status																			
//----------------------------------------------------------------------------------------------
#define	CNTS_BUSY			0x00000001	//Counter is working
#define	CNTS_DATA_NUM		0x00000010	//Count comparison match
#define	CNTS_ORERR			0x00010000	//Overrun
#define	CNTS_ERR			0x00020000	//Count operating error

//----------------------------------------------------------------------------------------------
//	Analog Input Message																		
//----------------------------------------------------------------------------------------------
#define AIOM_AIE_START			0x1000	//Event that AD converting start condition are satisfied
#define AIOM_AIE_RPTEND			0x1001	//Event of repeat end
#define AIOM_AIE_END			0x1002	//Event of device operation end
#define AIOM_AIE_DATA_NUM		0x1003	//Event that data of the specified sampling times are stored
#define AIOM_AIE_DATA_TSF		0x1007	//Event that data of the specified number are transferred
#define AIOM_AIE_OFERR			0x1004	//Event of Overflow
#define AIOM_AIE_SCERR			0x1005	//Event of sampling clock error
#define AIOM_AIE_ADERR			0x1006	//Event of AD converting error

//----------------------------------------------------------------------------------------------
//	Analog Output Message																		
//----------------------------------------------------------------------------------------------
#define AIOM_AOE_START			0x1020	//Event that DA converting start conditions are satisfied
#define AIOM_AOE_RPTEND			0x1021	//Event of repeat end
#define AIOM_AOE_END			0x1022	//Event of device operation end
#define AIOM_AOE_DATA_NUM		0x1023	//Event that data of the specified sampling times are output
#define AIOM_AOE_DATA_TSF		0x1027	//Event that data of the specified number are transferred
#define AIOM_AOE_SCERR			0x1025	//Event of sampling clock error
#define AIOM_AOE_DAERR			0x1026	//Event of DA converting error

//----------------------------------------------------------------------------------------------
//	Counter Message																			
//----------------------------------------------------------------------------------------------
#define AIOM_CNTE_DATA_NUM		0x1042	//Event of count comparison match
#define AIOM_CNTE_ORERR			0x1043	//Event of count overrun
#define AIOM_CNTE_ERR			0x1044	//Event of counter operating error

//----------------------------------------------------------------------------------------------
//	Timer Message																			
//----------------------------------------------------------------------------------------------
#define AIOM_TME_INT			0x1060	//Event that interval is satisfied

//----------------------------------------------------------------------------------------------
//	Analog Input Attached Data																		
//----------------------------------------------------------------------------------------------
#define	AIAT_AI				0x00000001	//Analog input attached information
#define	AIAT_AO0			0x00000100	//Analong output data
#define	AIAT_DIO0			0x00010000	//Digital input and output data
#define	AIAT_CNT0			0x01000000	//Data of counter channel 0
#define	AIAT_CNT1			0x02000000	//Data of counter channel 1

//----------------------------------------------------------------------------------------------
//	Counter Action Mode																			
//----------------------------------------------------------------------------------------------
#define	CNT_LOADPRESET		0x0000001	//Load the preset count value
#define	CNT_LOADCOMP		0x0000002	//Load the count comparison value

//----------------------------------------------------------------------------------------------
//	Event Controller Destination Signal																
//----------------------------------------------------------------------------------------------
#define	AIOECU_DEST_AI_CLK			4	//Analog input sampling clock
#define	AIOECU_DEST_AI_START		0	//Analog input converting start signal
#define	AIOECU_DEST_AI_STOP			2	//Analog input converting stop signal
#define	AIOECU_DEST_AO_CLK			36	//Analog output sampling clock
#define	AIOECU_DEST_AO_START		32	//Analog output converting start signal
#define	AIOECU_DEST_AO_STOP			34	//Analog output converting stop signal
#define	AIOECU_DEST_CNT0_UPCLK		134	//Up clock signal of counter 0
#define	AIOECU_DEST_CNT1_UPCLK		135	//Up clock signal of counter 1
#define	AIOECU_DEST_CNT0_START		128	//Start signal of counter 0, timer 0
#define	AIOECU_DEST_CNT1_START		129	//Start signal of counter 1, timer 1
#define	AIOECU_DEST_CNT0_STOP		130	//Stop signal of counter 0, timer 0
#define	AIOECU_DEST_CNT1_STOP		131	//Stop signal of counter 1, timer 1
#define	AIOECU_DEST_MASTER1			104	//Synchronization bus master signal 1
#define	AIOECU_DEST_MASTER2			105	//Synchronization bus master signal 2
#define	AIOECU_DEST_MASTER3			106	//Synchronization bus master signal 3

//----------------------------------------------------------------------------------------------
//	Event Controller Source Signal																
//----------------------------------------------------------------------------------------------
#define	AIOECU_SRC_OPEN				0	//Not connect
#define	AIOECU_SRC_AI_CLK			4	//Analog input internal clock signal
#define	AIOECU_SRC_AI_EXTCLK		146	//Analog input external clock signal
#define	AIOECU_SRC_AI_TRGSTART		144	//Analog input external trigger start signal
#define	AIOECU_SRC_AI_LVSTART		28	//Analog input level trigger start signal
#define	AIOECU_SRC_AI_STOP			17	//Analog input signal that data of the specified sampling times have been converted (No delay)
#define	AIOECU_SRC_AI_STOP_DELAY	18	//Analog input signal that data of the specified sampling times have been converted (delay)
#define	AIOECU_SRC_AI_LVSTOP		29	//Analog input level trigger stop signal
#define	AIOECU_SRC_AI_TRGSTOP		145	//Analog input external trigger stop signal
#define	AIOECU_SRC_AO_CLK			66	//Analog output internal clock signal
#define	AIOECU_SRC_AO_EXTCLK		149	//Analog output external clock signal
#define	AIOECU_SRC_AO_TRGSTART		147	//Analog output external trigger start signal
#define	AIOECU_SRC_AO_STOP_FIFO		352	//Analog output signal that data of the specified sampling times have been output (FIFO)
#define	AIOECU_SRC_AO_STOP_RING		80	//Analog output signal that data of the specified sampling times have been output (RING)
#define	AIOECU_SRC_AO_TRGSTOP		148	//Analog output external trigger stop signal
#define	AIOECU_SRC_CNT0_UPCLK		150	//Up clock signal of counter 0
#define	AIOECU_SRC_CNT1_UPCLK		152	//Up clock signal of counter 1
#define	AIOECU_SRC_CNT0_CMP			288	//Count comparison match of counter 0
#define	AIOECU_SRC_CNT1_CMP			289	//Count comparison match of counter 1
#define	AIOECU_SRC_SLAVE1			136	//Synchronization bus master signal 1
#define	AIOECU_SRC_SLAVE2			137	//Synchronization bus master signal 2
#define	AIOECU_SRC_SLAVE3			138	//Synchronization bus master signal 3
#define	AIOECU_SRC_START			384	//Ai, Ao, Cnt, Tm software start signal
#define	AIOECU_SRC_STOP				385	//Ai, Ao, Cnt, Tm software stop signal

//----------------------------------------------------------------------------------------------
//	Analog Input Transfer Size
//----------------------------------------------------------------------------------------------
#define	AI_TRANSFERSIZE_MANUAL		0	//Analog input transfer size manual setting
#define	AI_TRANSFERSIZE_AUTO		1	//Analog input transfer size auto setting

//----------------------------------------------------------------------------------------------
//	Analog Output Transfer Size
//----------------------------------------------------------------------------------------------
#define	AO_TRANSFERSIZE_MANUAL		0	//Analog output transfer size manual setting
#define	AO_TRANSFERSIZE_AUTO		1	//Analog output transfer size auto setting

//----------------------------------------------------------------------------------------------
//	Function Prototype																			
//----------------------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C"{
#endif
//Common Function
long WINAPI AioInit(char * DeviceName, short * Id);
long WINAPI AioExit(short Id);
long WINAPI AioResetDevice(short Id);
long WINAPI AioGetErrorString(long ErrorCode, char * ErrorString);
long WINAPI AioQueryDeviceName(short Index, char * DeviceName, char * Device);
long WINAPI AioGetDeviceType(char * Device, short * DeviceType);
long WINAPI AioSetReferenceClockType(short Id, unsigned short ReferenceClockType);
long WINAPI AioGetReferenceClockType(short Id, unsigned short * ReferenceClockType);
long WINAPI AioSetControlFilter(short Id, short Signal, float Value);
long WINAPI AioGetControlFilter(short Id, short Signal, float *Value);
long WINAPI AioResetProcess(short Id);

//Analog Input Function
long WINAPI AioSingleAi(short Id, short AiChannel, long * AiData);
long WINAPI AioSingleAiEx(short Id, short AiChannel, float * AiData);
long WINAPI AioMultiAi(short Id, short AiChannels, long * AiData);
long WINAPI AioMultiAiEx(short Id, short AiChannels, float * AiData);
long WINAPI AioSingleAiSR(short Id, short AiChannel, long * AiData, unsigned short * Timestamp, BYTE Mode);
long WINAPI AioSingleAiExSR(short Id, short AiChannel, float * AiData, unsigned short * Timestamp, BYTE Mode);
long WINAPI AioMultiAiSR(short Id, short AiChannels, long * AiData, unsigned short * Timestamp, BYTE Mode);
long WINAPI AioMultiAiExSR(short Id, short AiChannels, float * AiData, unsigned short * Timestamp, BYTE Mode);
long WINAPI AioGetAiResolution(short Id, short * AiResolution);
long WINAPI AioSetAiInputMethod(short Id, short AiInputMethod);
long WINAPI AioGetAiInputMethod(short Id, short * AiInputMethod);
long WINAPI AioGetAiMaxChannels(short Id, short * AiMaxChannels);
long WINAPI AioSetAiChannel(short Id, short AiChannel, short Enabled);
long WINAPI AioGetAiChannel(short Id, short AiChannel, short *Enabled);
long WINAPI AioSetAiChannels(short Id, short AiChannels);
long WINAPI AioGetAiChannels(short Id, short * AiChannels);
long WINAPI AioSetAiChannelSequence(short Id, short AiSequence, short AiChannel);
long WINAPI AioGetAiChannelSequence(short Id, short AiSequence, short * AiChannel);
long WINAPI AioSetAiRange(short Id, short AiChannel, short AiRange);
long WINAPI AioSetAiRangeAll(short Id, short AiRange);
long WINAPI AioGetAiRange(short Id, short AiChannel, short * AiRange);
long WINAPI AioSetAiTransferMode(short Id, short AiTransferMode);
long WINAPI AioGetAiTransferMode(short Id, short *AiTransferMode);
long WINAPI AioSetAiDeviceBufferMode(short Id, short AiDeviceBufferMode);
long WINAPI AioGetAiDeviceBufferMode(short Id, short *AiDeviceBufferMode);
long WINAPI AioSetAiMemorySize(short Id, long AiMemorySize);
long WINAPI AioGetAiMemorySize(short Id, long *AiMemorySize);
long WINAPI AioSetAiTransferData(short Id, long DataNumber, long *Buffer);
long WINAPI AioSetAiAttachedData(short Id, long AttachedData);
long WINAPI AioGetAiSamplingDataSize(short Id, short *DataSize);
long WINAPI AioSetAiTransferSize(short Id, short AutoMode, long TransferSize);
long WINAPI AioGetAiTransferSize(short Id, short *AutoMode, long *TransferSize);
long WINAPI AioSetAiMemoryType(short Id, short AiMemoryType);
long WINAPI AioGetAiMemoryType(short Id, short * AiMemoryType);
long WINAPI AioSetAiRepeatTimes(short Id, long AiRepeatTimes);
long WINAPI AioGetAiRepeatTimes(short Id, long * AiRepeatTimes);
long WINAPI AioSetAiClockType(short Id, short AiClockType);
long WINAPI AioGetAiClockType(short Id, short * AiClockType);
long WINAPI AioSetAiSamplingClock(short Id, float AiSamplingClock);
long WINAPI AioGetAiSamplingClock(short Id, float * AiSamplingClock);
long WINAPI AioSetAiScanClock(short Id, float AiScanClock);
long WINAPI AioGetAiScanClock(short Id, float * AiScanClock);
long WINAPI AioSetAiClockEdge(short Id, short AoClockEdge);
long WINAPI AioGetAiClockEdge(short Id, short * AoClockEdge);
long WINAPI AioSetAiStartTrigger(short Id, short AiStartTrigger);
long WINAPI AioGetAiStartTrigger(short Id, short * AiStartTrigger);
long WINAPI AioSetAiStartLevel(short Id, short AiChannel, long AiStartLevel, short AiDirection);
long WINAPI AioSetAiStartLevelEx(short Id, short AiChannel, float AiStartLevel, short AiDirection);
long WINAPI AioGetAiStartLevel(short Id, short AiChannel, long * AiStartLevel, short * AiDirection);
long WINAPI AioGetAiStartLevelEx(short Id, short AiChannel, float * AiStartLevel, short * AiDirection);
long WINAPI AioSetAiStartInRange(short Id, short AiChannel, long Level1, long Level2, long StateTimes);
long WINAPI AioSetAiStartInRangeEx(short Id, short AiChannel, float Level1, float Level2, long StateTimes);
long WINAPI AioGetAiStartInRange(short Id, short AiChannel, long *Level1, long *Level2, long *StateTimes);
long WINAPI AioGetAiStartInRangeEx(short Id, short AiChannel, float *Level1, float *Level2, long *StateTimes);
long WINAPI AioSetAiStartOutRange(short Id, short AiChannel, long Level1, long Level2, long StateTimes);
long WINAPI AioSetAiStartOutRangeEx(short Id, short AiChannel, float Level1, float Level2, long StateTimes);
long WINAPI AioGetAiStartOutRange(short Id, short AiChannel, long *Level1, long *Level2, long *StateTimes);
long WINAPI AioGetAiStartOutRangeEx(short Id, short AiChannel, float *Level1, float *Level2, long *StateTimes);
long WINAPI AioSetAiStopTrigger(short Id, short AiStopTrigger);
long WINAPI AioGetAiStopTrigger(short Id, short * AiStopTrigger);
long WINAPI AioSetAiStopTimes(short Id, long AiStopTimes);
long WINAPI AioGetAiStopTimes(short Id, long * AiStopTimes);
long WINAPI AioSetAiStopLevel(short Id, short AiChannel, long AiStopLevel, short AiDirection);
long WINAPI AioSetAiStopLevelEx(short Id, short AiChannel, float AiStopLevel, short AiDirection);
long WINAPI AioGetAiStopLevel(short Id, short AiChannel, long * AiStopLevel, short * AiDirection);
long WINAPI AioGetAiStopLevelEx(short Id, short AiChannel, float * AiStopLevel, short * AiDirection);
long WINAPI AioSetAiStopInRange(short Id, short AiChannel, long Level1, long Level2, long StateTimes);
long WINAPI AioSetAiStopInRangeEx(short Id, short AiChannel, float Level1, float Level2, long StateTimes);
long WINAPI AioGetAiStopInRange(short Id, short AiChannel, long *Level1, long *Level2, long *StateTimes);
long WINAPI AioGetAiStopInRangeEx(short Id, short AiChannel, float *Level1, float *Level2, long *StateTimes);
long WINAPI AioSetAiStopOutRange(short Id, short AiChannel, long Level1, long Level2, long StateTimes);
long WINAPI AioSetAiStopOutRangeEx(short Id, short AiChannel, float Level1, float Level2, long StateTimes);
long WINAPI AioGetAiStopOutRange(short Id, short AiChannel, long *Level1, long *Level2, long *StateTimes);
long WINAPI AioGetAiStopOutRangeEx(short Id, short AiChannel, float *Level1, float *Level2, long *StateTimes);
long WINAPI AioSetAiStopDelayTimes(short Id, long AiStopDelayTimes);
long WINAPI AioGetAiStopDelayTimes(short Id, long * AiStopDelayTimes);
long WINAPI AioSetAiEvent(short Id, HWND hWnd, long AiEvent);
long WINAPI AioGetAiEvent(short Id, HWND * hWnd, long * AiEvent);
long WINAPI AioSetAiCallBackProc(short Id,
	long (_stdcall *pProc)(short Id, short AiEvent, WPARAM wParam, LPARAM lParam, void *Param), long AiEvent, void *Param);
long WINAPI AioSetAiEventSamplingTimes(short Id, long AiSamplingTimes);
long WINAPI AioGetAiEventSamplingTimes(short Id, long * AiSamplingTimes);
long WINAPI AioSetAiEventTransferTimes(short Id, long AiTransferTimes);
long WINAPI AioGetAiEventTransferTimes(short Id, long *AiTransferTimes);
long WINAPI AioStartAi(short Id);
long WINAPI AioStartAiSync(short Id, long TimeOut);
long WINAPI AioStopAi(short Id);
long WINAPI AioGetAiStatus(short Id, long * AiStatus);
long WINAPI AioGetAiSamplingCount(short Id, long * AiSamplingCount);
long WINAPI AioGetAiStopTriggerCount(short Id, long * AiStopTriggerCount);
long WINAPI AioGetAiTransferCount(short Id, long *AiTransferCount);
long WINAPI AioGetAiTransferLap(short Id, long *Lap);
long WINAPI AioGetAiStopTriggerTransferCount(short Id, long *Count);
long WINAPI AioGetAiRepeatCount(short Id, long * AiRepeatCount);
long WINAPI AioGetAiSamplingData(short Id, long * AiSamplingTimes, long * AiData);
long WINAPI AioGetAiSamplingDataEx(short Id, long * AiSamplingTimes, float * AiData);
long WINAPI AioResetAiStatus(short Id);
long WINAPI AioResetAiMemory(short Id);
long WINAPI AioSetAiDigitalFilter(short Id, short AiChannel, short FilterType, short FilterValue);
long WINAPI AioGetAiDigitalFilter(short Id, short AiChannel, short *FilterType, short *FilterValue);
long WINAPI AioSetAiFilter(short Id, unsigned short * AiChannelNo, unsigned short AiChannelNum, unsigned short * FilterType, unsigned long long * FilterValueLow, unsigned long long * FilterValueHigh, unsigned short * FilterUnit);
long WINAPI AioGetAiFilter(short Id, unsigned short * AiChannelNo, unsigned short AiChannelNum, unsigned short * FilterType, unsigned long long * FilterValueLow, unsigned long long * FilterValueHigh, unsigned short * FilterUnit);

//Analog Output Function
long WINAPI AioSingleAo(short Id, short AoChannel, long AoData);
long WINAPI AioSingleAoEx(short Id, short AoChannel, float AoData);
long WINAPI AioMultiAo(short Id, short AoChannels, long * AoData);
long WINAPI AioMultiAoEx(short Id, short AoChannels, float * AoData);
long WINAPI AioGetAoResolution(short Id, short * AoResolution);
long WINAPI AioSetAoChannels(short Id, short AoChannels);
long WINAPI AioGetAoChannels(short Id, short * AoChannels);
long WINAPI AioGetAoMaxChannels(short Id, short * AoMaxChannels);
long WINAPI AioSetAoRange(short Id, short AoChannel, short AoRange);
long WINAPI AioSetAoRangeAll(short Id, short AoRange);
long WINAPI AioGetAoRange(short Id, short AoChannel, short * AoRange);
long WINAPI AioSetAoTransferMode(short Id, short AoTransferMode);
long WINAPI AioGetAoTransferMode(short Id, short *AoTransferMode);
long WINAPI AioSetAoDeviceBufferMode(short Id, short AoDeviceBufferMode);
long WINAPI AioGetAoDeviceBufferMode(short Id, short *AoDeviceBufferMode);
long WINAPI AioSetAoMemorySize(short Id, long AoMemorySize);
long WINAPI AioGetAoMemorySize(short Id, long *AoMemorySize);
long WINAPI AioSetAoTransferData(short Id, long DataNumber, long *Buffer);
long WINAPI AioGetAoSamplingDataSize(short Id, short *DataSize);
long WINAPI AioSetAoTransferSize(short Id, short AutoMode, long TransferSize);
long WINAPI AioGetAoTransferSize(short Id, short *AutoMode, long *TransferSize);
long WINAPI AioSetAoMemoryType(short Id, short AoMemoryType);
long WINAPI AioGetAoMemoryType(short Id, short * AoMemoryType);
long WINAPI AioSetAoRepeatTimes(short Id, long AoRepeatTimes);
long WINAPI AioGetAoRepeatTimes(short Id, long * AoRepeatTimes);
long WINAPI AioSetAoClockType(short Id, short AoClockType);
long WINAPI AioGetAoClockType(short Id, short * AoClockType);
long WINAPI AioSetAoSamplingClock(short Id, float AoSamplingClock);
long WINAPI AioGetAoSamplingClock(short Id, float * AoSamplingClock);
long WINAPI AioSetAoClockEdge(short Id, short AoClockEdge);
long WINAPI AioGetAoClockEdge(short Id, short * AoClockEdge);
long WINAPI AioSetAoSamplingData(short Id, long AoSamplingTimes, long * AoData);
long WINAPI AioSetAoSamplingDataEx(short Id, long AoSamplingTimes, float * AoData);
long WINAPI AioGetAoSamplingTimes(short Id, long * AoSamplingTimes);
long WINAPI AioSetAoStartTrigger(short Id, short AoStartTrigger);
long WINAPI AioGetAoStartTrigger(short Id, short * AoStartTrigger);
long WINAPI AioSetAoStopTrigger(short Id, short AoStopTrigger);
long WINAPI AioGetAoStopTrigger(short Id, short * AoStopTrigger);
long WINAPI AioSetAoEvent(short Id, HWND hWnd, long AoEvent);
long WINAPI AioGetAoEvent(short Id, HWND * hWnd, long * AoEvent);
long WINAPI AioSetAoCallBackProc(short Id,
	long (_stdcall *pProc)(short Id, short AiEvent, WPARAM wParam, LPARAM lParam, void *Param), long AoEvent, void *Param);
long WINAPI AioSetAoEventSamplingTimes(short Id, long AoSamplingTimes);
long WINAPI AioGetAoEventSamplingTimes(short Id, long * AoSamplingTimes);
long WINAPI AioSetAoEventTransferTimes(short Id, long AoTransferTimes);
long WINAPI AioGetAoEventTransferTimes(short Id, long *AoTransferTimes);
long WINAPI AioStartAo(short Id);
long WINAPI AioStopAo(short Id);
long WINAPI AioEnableAo(short Id, short AoChannel);
long WINAPI AioDisableAo(short Id, short AoChannel);
long WINAPI AioGetAoStatus(short Id, long * AoStatus);
long WINAPI AioGetAoSamplingCount(short Id, long * AoSamplingCount);
long WINAPI AioGetAoTransferCount(short Id, long *AoTransferCount);
long WINAPI AioGetAoTransferLap(short Id, long *Lap);
long WINAPI AioGetAoRepeatCount(short Id, long * AoRepeatCount);
long WINAPI AioResetAoStatus(short Id);
long WINAPI AioResetAoMemory(short Id);

//Digital Input and Output Function
long WINAPI AioSetDiFilter(short Id, short Bit, float Value);
long WINAPI AioGetDiFilter(short Id, short Bit, float *Value);
long WINAPI AioInputDiBit(short Id, short DiBit, short * DiData);
long WINAPI AioOutputDoBit(short Id, short DoBit, short DoData);
long WINAPI AioInputDiByte(short Id, short DiPort, short * DiData);
long WINAPI AioOutputDoByte(short Id, short DoPort, short DoData);
long WINAPI AioSetDioDirection(short Id, long Dir);
long WINAPI AioGetDioDirection (short Id, long * Dir);

//Counter Function
long WINAPI AioGetCntMaxChannels(short Id, short * CntMaxChannels);
long WINAPI AioSetCntComparisonMode(short Id, short CntChannel, short CntMode);
long WINAPI AioGetCntComparisonMode(short Id, short CntChannel, short *CntMode);
long WINAPI AioSetCntPresetReg(short Id, short CntChannel, long PresetNumber, long *PresetData, short Flag);
long WINAPI AioSetCntComparisonReg(short Id, short CntChannel, long ComparisonNumber, long *ComparisonData, short Flag);
long WINAPI AioSetCntInputSignal(short Id, short CntChannel, short CntInputSignal);
long WINAPI AioGetCntInputSignal(short Id, short CntChannel, short *CntInputSignal);
long WINAPI AioSetCntEvent(short Id, short CntChannel, HWND hWnd, long CntEvent);
long WINAPI AioGetCntEvent(short Id, short CntChannel, HWND *hWnd, long *CntEvent);
long WINAPI AioSetCntCallBackProc(short Id, short CntChannel,
	long (_stdcall *pProc)(short Id, short CntEvent, WPARAM wParam, LPARAM lParam, void *Param), long CntEvent, void *Param);
long WINAPI AioSetCntFilter(short Id, short CntChannel, short Signal, float Value);
long WINAPI AioGetCntFilter(short Id, short CntChannel, short Signal, float *Value);
long WINAPI AioStartCnt(short Id, short CntChannel);
long WINAPI AioStopCnt(short Id, short CntChannel);
long WINAPI AioPresetCnt(short Id, short CntChannel, long PresetData);
long WINAPI AioGetCntStatus(short Id, short CntChannel, long *CntStatus);
long WINAPI AioGetCntCount(short Id, short CntChannel, long *Count);
long WINAPI AioResetCntStatus(short Id, short CntChannel, long CntStatus);

//Timer Function
long WINAPI AioSetTmEvent(short Id, short TimerId, HWND hWnd, long TmEvent);
long WINAPI AioGetTmEvent(short Id, short TimerId, HWND * hWnd, long * TmEvent);
long WINAPI AioSetTmCallBackProc(short Id, short TimerId,
	long (_stdcall *pProc)(short Id, short TmEvent, WPARAM wParam, LPARAM lParam, void *Param), long TmEvent, void *Param);
long WINAPI AioStartTmTimer(short Id, short TimerId, float Interval);
long WINAPI AioStopTmTimer(short Id, short TimerId);
long WINAPI AioStartTmCount(short Id, short TimerId);
long WINAPI AioStopTmCount(short Id, short TimerId);
long WINAPI AioLapTmCount(short Id, short TimerId, long *Lap);
long WINAPI AioResetTmCount(short Id, short TimerId);
long WINAPI AioTmWait(short Id, short TimerId, long Wait);

//Event Controller
long WINAPI AioSetEcuSignal(short Id, short Destination, short Source);
long WINAPI AioGetEcuSignal(short Id, short Destination, short *Source);

#ifdef __cplusplus
};
#endif
