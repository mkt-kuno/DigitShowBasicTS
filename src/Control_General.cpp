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
// Control_General.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "DigitShowBasic.h"
#include "Control_General.h"
#include "DigitShowContext.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CControl_General ダイアログ

CControl_General::CControl_General(CWnd* pParent /*=NULL*/)
	: CDialog(CControl_General::IDD, pParent)
{
	DigitShowContext* ctx = GetContext();
	//{{AFX_DATA_INIT(CControl_General)
	m_ErrorStressAir = ctx->err.StressAir;
	m_ErrorStressMotor = ctx->err.StressMotor;
	m_ErrorStrainEz = ctx->err.StrainEz;
	m_ErrorStrainGzq = ctx->err.StrainGzq;
	//}}AFX_DATA_INIT
}


void CControl_General::DoDataExchange(CDataExchange* pDX)
{	DigitShowContext* ctx = GetContext();
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CControl_General)
	DDX_Text(pDX, IDC_EDIT_ErrorStressAir, m_ErrorStressAir);
	DDX_Text(pDX, IDC_EDIT_ErrorStressMotor, m_ErrorStressMotor);
	DDX_Text(pDX, IDC_EDIT_ErrorStrainEz, m_ErrorStrainEz);
	DDX_Text(pDX, IDC_EDIT_ErrorStrainGzq, m_ErrorStrainGzq);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CControl_General, CDialog)
	//{{AFX_MSG_MAP(CControl_General)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CControl_General メッセージ ハンドラ

void CControl_General::OnOK() 
{	DigitShowContext* ctx = GetContext();
	// TODO: この位置にその他の検証用のコードを追加してください
	UpdateData(TRUE);
	ctx->err.StressAir = m_ErrorStressAir;
	ctx->err.StressMotor = m_ErrorStressMotor;
	ctx->err.StrainEz = m_ErrorStrainEz;
	ctx->err.StrainGzq = m_ErrorStrainGzq;
	CDialog::OnOK();
}

