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
// Control_Consolidation.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "DigitShowBasic.h"
#include "Control_Consolidation.h"
#include "DigitShowContext.h"
#include "DigitShowBasicDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CControl_Consolidation ダイアログ


CControl_Consolidation::CControl_Consolidation(CWnd* pParent /*=NULL*/)
	: CDialog(CControl_Consolidation::IDD, pParent)
{
	DigitShowContext* ctx = GetContext();
	//{{AFX_DATA_INIT(CControl_Consolidation)
	m_K0 = ctx->control[2].K0;
	m_sr_rate = ctx->control[2].sigmaRate[2];
	m_sa = ctx->control[2].sigma[0];
	m_AxialMotorSpeed = ctx->control[2].AxisSpeed;
	//}}AFX_DATA_INIT
}


void CControl_Consolidation::DoDataExchange(CDataExchange* pDX)
{	DigitShowContext* ctx = GetContext();
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CControl_Consolidation)
	DDX_Text(pDX, IDC_EDIT_K0, m_K0);
	DDX_Text(pDX, IDC_EDIT_sr_rate, m_sr_rate);
	DDX_Text(pDX, IDC_EDIT_sa, m_sa);
	DDX_Text(pDX, IDC_EDIT_AxialMotorSpeed, m_AxialMotorSpeed);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CControl_Consolidation, CDialog)
	//{{AFX_MSG_MAP(CControl_Consolidation)
	ON_BN_CLICKED(IDC_BUTTON_Update, OnBUTTONUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CControl_Consolidation メッセージ ハンドラ

void CControl_Consolidation::OnBUTTONUpdate() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(TRUE);
	ctx->control[2].sigma[0] = m_sa;
	ctx->control[2].K0 = m_K0;
	ctx->control[2].AxisSpeed = m_AxialMotorSpeed;
	ctx->control[2].sigmaRate[2] = m_sr_rate;	
}
