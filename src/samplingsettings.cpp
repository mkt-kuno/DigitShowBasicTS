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
// SamplingSettings.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "DigitShowBasic.h"
#include "DigitShowBasicDoc.h"

#include "SamplingSettings.h"
#include "DigitShowContext.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSamplingSettings ダイアログ




CSamplingSettings::CSamplingSettings(CWnd* pParent /*=NULL*/)
	: CDialog(CSamplingSettings::IDD, pParent)
{
	DigitShowContext* ctx = GetContext();
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
{	DigitShowContext* ctx = GetContext();
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
// CSamplingSettings メッセージ ハンドラ

BOOL CSamplingSettings::OnInitDialog() 
{	DigitShowContext* ctx = GetContext();
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	m_TimeInterval1 = ctx->timeSettings.Interval1;
	m_TimeInterval2 = ctx->timeSettings.Interval2;
	m_TimeInterval3 = ctx->timeSettings.Interval3;
//
	m_AllocatedMemory.Format("%.1f",ctx->AllocatedMemory);
	m_Channels = ctx->AdMaxCH;
	m_EventSamplingTimes = ctx->ad[0].SamplingTimes;
	m_AvSmplNum = ctx->AvSmplNum;
	if(ctx->ad[0].MemoryType==0) m_MemoryType = _T("FIFO");
	if(ctx->ad[0].MemoryType==1) m_MemoryType = _T("RING");
	m_SamplingClock = ctx->ad[0].SamplingClock/1000.0f;
	m_SavingTime = ctx->SavingTime;
	m_TotalSamplingTimes = ctx->TotalSamplingTimes;
	UpdateData(FALSE);
//
	CButton* myBTN1=(CButton*)GetDlgItem(IDC_BUTTON_Check);
	CButton* myBTN2=(CButton*)GetDlgItem(IDOK);
	if(ctx->flags.FIFO==TRUE)	myBTN1->EnableWindow(FALSE);
	myBTN2->EnableWindow(FALSE);

	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CSamplingSettings::OnBUTTONCheck() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(TRUE);
	m_TotalSamplingTimes=long(m_SavingTime*1000/m_SamplingClock);
	m_AllocatedMemory.Format("%.1f",4*ctx->AdMaxCH*m_TotalSamplingTimes/1024.0f/1024.0f);
	m_EventSamplingTimes=long(ctx->timeSettings.Interval1/m_SamplingClock);
	UpdateData(FALSE);

	CButton* myBTN1=(CButton*)GetDlgItem(IDOK);
	myBTN1->EnableWindow(TRUE);
	
}

void CSamplingSettings::OnOK() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にその他の検証用のコードを追加してください
	UpdateData(TRUE);
	ctx->ad[0].SamplingClock = m_SamplingClock*1000.0f;
	ctx->SavingTime = m_SavingTime;
	ctx->ad[0].SamplingTimes = m_EventSamplingTimes;
	ctx->TotalSamplingTimes=long(ctx->SavingTime*1000000/ctx->ad[0].SamplingClock);
	ctx->AllocatedMemory=4*ctx->AdMaxCH*m_TotalSamplingTimes/1024.0f/1024.0f;
	m_AllocatedMemory.Format("%.1f",ctx->AllocatedMemory);
	m_TotalSamplingTimes=ctx->TotalSamplingTimes;
	UpdateData(FALSE);

	if(ctx->NumAD>1){
		ctx->ad[1].SamplingClock=ctx->ad[0].SamplingClock;
		ctx->ad[1].SamplingTimes=ctx->ad[0].SamplingTimes;
	}
	CDialog::OnOK();
}
