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
#if !defined(AFX_CONTROL_GENERAL_H__532C5E62_C023_4BF0_A802_D247DC39A747__INCLUDED_)
#define AFX_CONTROL_SENERAL_H__532C5E62_C023_4BF0_A802_D247DC39A747__INCLUDED_

#include "DigitShowBasicDoc.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Control_General.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CControl_General ダイアログ

class CControl_General : public CDialog
{
// コンストラクション
public:
	CControl_General(CWnd* pParent = NULL);   // 標準のコンストラクタ
	CDigitShowBasicDoc* pDoc2;

// ダイアログ データ
	//{{AFX_DATA(CControl_General)
	enum { IDD = IDD_Control_General };
	double	m_ErrorStressAir;
	double	m_ErrorStressMotor;
	double	m_ErrorStrainEz;
	double	m_ErrorStrainGzq;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CControl_General)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CControl_General)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_CONTROL_GENERAL_H__532C5E62_C023_4BF0_A802_D247DC39A747__INCLUDED_)
