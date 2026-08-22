// SamplingSettings.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "DigitShowBasic.h"
#include "DigitShowBasicDoc.h"

#include "SamplingSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSamplingSettings �_�C�A���O
extern	int			NUMAD;
extern	int			AdMaxCH;
extern	short		AdMemoryType[2];
extern	float		AdSamplingClock[2];
extern	short		AdChannels[2];
extern	float		AdScanClock[2];
extern	long		AdSamplingTimes[2];
extern	int			SavingTime;
extern	long		TotalSamplingTimes;
extern	float		AllocatedMemory;
extern	int			AvSmplNum;

extern	bool		Flag_FIFO;

extern	unsigned int	TimeInterval_1;	// Time interval (ms) to display output data.		
extern	unsigned int	TimeInterval_2;	// Time interval (ms) to feed back.		
extern	unsigned int	TimeInterval_3;	// Time interval (ms) to save the data.


CSamplingSettings::CSamplingSettings(CWnd* pParent /*=NULL*/)
	: CDialog(CSamplingSettings::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSamplingSettings)
	m_TimeInterval1 = 0;
	m_TimeInterval2 = 0;
	m_TimeInterval3 = 0;
	m_TotalSamplingTimes = 0;
	m_AllocatedMemory = _T("");
	m_AvSmplNum = 0;
	m_Channels = 0;
	m_EventSamplingTimes = 0;
	m_MemoryType = _T("");
	m_SamplingClock = 0.0f;
	m_SavingTime = 0;
	//}}AFX_DATA_INIT
}


void CSamplingSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSamplingSettings)
	DDX_Text(pDX, IDC_EDIT_TimeInterval1, m_TimeInterval1);
	DDX_Text(pDX, IDC_EDIT_TimeInterval2, m_TimeInterval2);
	DDX_Text(pDX, IDC_EDIT_TimeInterval3, m_TimeInterval3);
	DDX_Text(pDX, IDC_EDIT_TotalSamplingTimes, m_TotalSamplingTimes);
	DDX_Text(pDX, IDC_EDIT_AllocatedMemory, m_AllocatedMemory);
	DDX_Text(pDX, IDC_EDIT_AvSmplNum, m_AvSmplNum);
	DDX_Text(pDX, IDC_EDIT_Channels, m_Channels);
	DDX_Text(pDX, IDC_EDIT_EventSamplingTimes, m_EventSamplingTimes);
	DDX_Text(pDX, IDC_EDIT_MemoryType, m_MemoryType);
	DDX_Text(pDX, IDC_EDIT_SamplingClock, m_SamplingClock);
	DDX_Text(pDX, IDC_EDIT_SavingTime, m_SavingTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSamplingSettings, CDialog)
	//{{AFX_MSG_MAP(CSamplingSettings)
	ON_BN_CLICKED(IDC_BUTTON_Check, OnBUTTONCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSamplingSettings ���b�Z�[�W �n���h��

BOOL CSamplingSettings::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	m_TimeInterval1 = TimeInterval_1;
	m_TimeInterval2 = TimeInterval_2;
	m_TimeInterval3 = TimeInterval_3;
//
	m_AllocatedMemory.Format("%.1f",AllocatedMemory);
	m_Channels = AdMaxCH;
	m_EventSamplingTimes = AdSamplingTimes[0];
	m_AvSmplNum = AvSmplNum;
	if(AdMemoryType[0]==0) m_MemoryType = _T("FIFO");
	if(AdMemoryType[0]==1) m_MemoryType = _T("RING");
	m_SamplingClock = AdSamplingClock[0]/1000.0f;
	m_SavingTime = SavingTime;
	m_TotalSamplingTimes = TotalSamplingTimes;
	UpdateData(FALSE);
//
	CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_Check);
	CButton* myBTN2=(CButton*)GetDlgItem(IDOK);
	if(Flag_FIFO==TRUE)	myBTN1->EnableWindow(FALSE);
	myBTN2->EnableWindow(FALSE);

	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

void CSamplingSettings::OnBUTTONCheck() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	UpdateData(TRUE);
	m_TotalSamplingTimes=long(m_SavingTime*1000/m_SamplingClock);
	m_AllocatedMemory.Format("%.1f",4*AdMaxCH*m_TotalSamplingTimes/1024.0f/1024.0f);
	m_EventSamplingTimes=long(TimeInterval_1/m_SamplingClock);
	UpdateData(FALSE);

	CButton* myBTN1=(CButton*)GetDlgItem(IDOK);
	myBTN1->EnableWindow(TRUE);
	
}

void CSamplingSettings::OnOK() 
{
	// TODO: ���̈ʒu�ɂ��̑��̌��ؗp�̃R�[�h��ǉ����Ă�������
	UpdateData(TRUE);
	AdSamplingClock[0] = m_SamplingClock*1000.0f;
	AdScanClock[0] = long(AdSamplingClock[0]/AdChannels[0]);	// Newer CONTEC drivers require ScanClock <= SamplingClock/CH (floor to the safe side)
	if(AdScanClock[0]<1){ AdScanClock[0]=1; }
	SavingTime = m_SavingTime;
	AdSamplingTimes[0] = m_EventSamplingTimes;
	TotalSamplingTimes=long(SavingTime*1000000/AdSamplingClock[0]);
	AllocatedMemory=4*AdMaxCH*m_TotalSamplingTimes/1024.0f/1024.0f;
	m_AllocatedMemory.Format("%.1f",AllocatedMemory);
	m_TotalSamplingTimes=TotalSamplingTimes;
	UpdateData(FALSE);

	if(NUMAD>1){
		AdSamplingClock[1]=AdSamplingClock[0];
		AdScanClock[1]=long(AdSamplingClock[1]/AdChannels[1]);
		if(AdScanClock[1]<1){ AdScanClock[1]=1; }
		AdSamplingTimes[1]=AdSamplingTimes[0];
	}
	CDialog::OnOK();
}
