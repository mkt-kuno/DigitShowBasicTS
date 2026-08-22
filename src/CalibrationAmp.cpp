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
// CalibrationAmp.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "DigitShowBasic.h"
#include "CalibrationAmp.h"
#include "DigitShowContext.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalibrationAmp ダイアログ


CCalibrationAmp::CCalibrationAmp(CWnd* pParent /*=NULL*/)
	: CDialog(CCalibrationAmp::IDD, pParent)
{
	DigitShowContext* ctx = GetContext();
	//{{AFX_DATA_INIT(CCalibrationAmp)
	m_AmpNo = ctx->AmpID;
	m_AmpPB = 0.0f;
	m_AmpPO = 0.0f;
	m_AmpVB = 0.0f;
	m_AmpVO = 0.0f;
	//}}AFX_DATA_INIT
}

void CCalibrationAmp::DoDataExchange(CDataExchange* pDX)
{	DigitShowContext* ctx = GetContext();
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalibrationAmp)
	DDX_Text(pDX, IDC_EDIT_AmpNO, m_AmpNo);
	DDX_Text(pDX, IDC_EDIT_AmpPB, m_AmpPB);
	DDX_Text(pDX, IDC_EDIT_AmpPO, m_AmpPO);
	DDX_Text(pDX, IDC_EDIT_AmpVB, m_AmpVB);
	DDX_Text(pDX, IDC_EDIT_AmpVO, m_AmpVO);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCalibrationAmp, CDialog)
	//{{AFX_MSG_MAP(CCalibrationAmp)
	ON_BN_CLICKED(IDC_BUTTON_AmpBase, OnBUTTONAmpBase)
	ON_BN_CLICKED(IDC_BUTTON_AmpOffset, OnBUTTONAmpOffset)
	ON_BN_CLICKED(IDC_BUTTON_AmpUpdate, OnBUTTONAmpUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalibrationAmp メッセージ ハンドラ

void CCalibrationAmp::OnBUTTONAmpBase() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(TRUE);
	pDoc->AD_INPUT();
	m_AmpVB=ctx->ai.raw[ctx->AmpID-1];
	UpdateData(FALSE);	
}

void CCalibrationAmp::OnBUTTONAmpOffset() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(TRUE);
	pDoc->AD_INPUT();
	m_AmpVO=ctx->ai.raw[ctx->AmpID-1];
	UpdateData(FALSE);	
}

void CCalibrationAmp::OnBUTTONAmpUpdate() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(TRUE);
	if(m_AmpVO-m_AmpVB==0.0){
		AfxMessageBox("Can not get calibration factors!",MB_ICONEXCLAMATION | MB_OK );
	}
	else{
		ctx->ai.cal.b[ctx->AmpID-1]=(m_AmpPO-m_AmpPB)/(m_AmpVO-m_AmpVB);
		ctx->ai.cal.c[ctx->AmpID-1]=m_AmpPB-ctx->ai.cal.b[ctx->AmpID-1]*m_AmpVB;
		AfxMessageBox("Get calibration factors!",MB_ICONEXCLAMATION | MB_OK );
	}	
}
