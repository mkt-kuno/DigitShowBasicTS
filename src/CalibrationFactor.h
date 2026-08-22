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
#if !defined(AFX_CALIBRATIONFACTOR_H__180C3E2C_AEA3_469C_B493_87EF9EE3B75D__INCLUDED_)
#define AFX_CALIBRATIONFACTOR_H__180C3E2C_AEA3_469C_B493_87EF9EE3B75D__INCLUDED_

#include "DigitShowBasicDoc.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CalibrationFactor.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CCalibrationFactor ダイアログ

class CCalibrationFactor : public CDialog
{
// コンストラクション
public:
	void Load();
	CCalibrationFactor(CWnd* pParent = NULL);   // 標準のコンストラクタ
	CDigitShowBasicDoc* pDoc;
// ダイアログ データ
	//{{AFX_DATA(CCalibrationFactor)
	enum { IDD = IDD_Calibration_Factor };
	CButton	m_Amp15;
	CButton	m_Amp14;
	CButton	m_Amp13;
	CButton	m_Amp12;
	CButton	m_Amp11;
	CButton	m_Amp10;
	CButton	m_Amp09;
	CButton	m_Amp08;
	CButton	m_Amp07;
	CButton	m_Amp06;
	CButton	m_Amp05;
	CButton	m_Amp04;
	CButton	m_Amp03;
	CButton	m_Amp02;
	CButton	m_Amp01;
	CButton	m_Amp00;
	CString	m_CFP00;
	CString	m_CFP01;
	CString	m_CFP02;
	CString	m_CFP03;
	CString	m_CFP04;
	CString	m_CFP05;
	CString	m_CFP06;
	CString	m_CFP07;
	CString	m_CFP08;
	CString	m_CFP09;
	CString	m_CFP10;
	CString	m_CFP11;
	CString	m_CFP12;
	CString	m_CFP13;
	CString	m_CFP14;
	CString	m_CFP15;
	double	m_CFA00;
	double	m_CFA01;
	double	m_CFA02;
	double	m_CFA03;
	double	m_CFA04;
	double	m_CFA05;
	double	m_CFA06;
	double	m_CFA07;
	double	m_CFA08;
	double	m_CFA09;
	double	m_CFA10;
	double	m_CFA11;
	double	m_CFA12;
	double	m_CFA13;
	double	m_CFA14;
	double	m_CFA15;
	double	m_CFB00;
	double	m_CFB01;
	double	m_CFB02;
	double	m_CFB03;
	double	m_CFB04;
	double	m_CFB05;
	double	m_CFB06;
	double	m_CFB07;
	double	m_CFB08;
	double	m_CFB09;
	double	m_CFB10;
	double	m_CFB11;
	double	m_CFB12;
	double	m_CFB13;
	double	m_CFB14;
	double	m_CFB15;
	double	m_CFC00;
	double	m_CFC01;
	double	m_CFC02;
	double	m_CFC03;
	double	m_CFC04;
	double	m_CFC05;
	double	m_CFC06;
	double	m_CFC07;
	double	m_CFC08;
	double	m_CFC09;
	double	m_CFC10;
	double	m_CFC11;
	double	m_CFC12;
	double	m_CFC13;
	double	m_CFC14;
	double	m_CFC15;
	CString	m_CH00;
	CString	m_CH01;
	CString	m_CH02;
	CString	m_CH03;
	CString	m_CH04;
	CString	m_CH05;
	CString	m_CH06;
	CString	m_CH07;
	CString	m_CH08;
	CString	m_CH09;
	CString	m_CH10;
	CString	m_CH11;
	CString	m_CH12;
	CString	m_CH13;
	CString	m_CH14;
	CString	m_CH15;
	CString	m_DChannel;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CCalibrationFactor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CCalibrationFactor)
	afx_msg void OnBUTTONCFUpdate();
	afx_msg void OnBUTTONZero00();
	afx_msg void OnBUTTONZero01();
	afx_msg void OnBUTTONZero02();
	afx_msg void OnBUTTONZero03();
	afx_msg void OnBUTTONZero04();
	afx_msg void OnBUTTONZero05();
	afx_msg void OnBUTTONZero06();
	afx_msg void OnBUTTONZero07();
	afx_msg void OnBUTTONZero08();
	afx_msg void OnBUTTONZero09();
	afx_msg void OnBUTTONZero10();
	afx_msg void OnBUTTONZero11();
	afx_msg void OnBUTTONZero12();
	afx_msg void OnBUTTONZero13();
	afx_msg void OnBUTTONZero14();
	afx_msg void OnBUTTONZero15();
	afx_msg void OnBUTTONAmp00();
	afx_msg void OnBUTTONAmp01();
	afx_msg void OnBUTTONAmp02();
	afx_msg void OnBUTTONAmp03();
	afx_msg void OnBUTTONAmp04();
	afx_msg void OnBUTTONAmp05();
	afx_msg void OnBUTTONAmp06();
	afx_msg void OnBUTTONAmp07();
	afx_msg void OnBUTTONAmp08();
	afx_msg void OnBUTTONAmp09();
	afx_msg void OnBUTTONAmp10();
	afx_msg void OnBUTTONAmp11();
	afx_msg void OnBUTTONAmp12();
	afx_msg void OnBUTTONAmp13();
	afx_msg void OnBUTTONAmp14();
	afx_msg void OnBUTTONAmp15();
	afx_msg void OnBUTTONCFSave();
	afx_msg void OnBUTTONCFLoadFile();
	afx_msg void OnBUTTONChannel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_CALIBRATIONFACTOR_H__180C3E2C_AEA3_469C_B493_87EF9EE3B75D__INCLUDED_)
