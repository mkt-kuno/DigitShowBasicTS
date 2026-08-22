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
#if !defined(AFX_CALIBRATIONAMP_H__D2AF5789_8CAB_4A3E_906B_ADADB31CA9D1__INCLUDED_)
#define AFX_CALIBRATIONAMP_H__D2AF5789_8CAB_4A3E_906B_ADADB31CA9D1__INCLUDED_

#include "DigitShowBasicDoc.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CalibrationAmp.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CCalibrationAmp ダイアログ

class CCalibrationAmp : public CDialog
{
// コンストラクション
public:
	CCalibrationAmp(CWnd* pParent = NULL);   // 標準のコンストラクタ
	CDigitShowBasicDoc* pDoc;
// ダイアログ データ
	//{{AFX_DATA(CCalibrationAmp)
	enum { IDD = IDD_Calibration_Amp };
	int		m_AmpNo;
	float	m_AmpPB;
	float	m_AmpPO;
	float	m_AmpVB;
	float	m_AmpVO;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CCalibrationAmp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CCalibrationAmp)
	afx_msg void OnBUTTONAmpBase();
	afx_msg void OnBUTTONAmpOffset();
	afx_msg void OnBUTTONAmpUpdate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_CALIBRATIONAMP_H__D2AF5789_8CAB_4A3E_906B_ADADB31CA9D1__INCLUDED_)
