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
#if !defined(AFX_SPECIMEN_H__417DC7FD_CE21_4B6B_988B_2D3050CBC61D__INCLUDED_)
#define AFX_SPECIMEN_H__417DC7FD_CE21_4B6B_988B_2D3050CBC61D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Specimen.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CSpecimen ダイアログ

class CSpecimen : public CDialog
{
// コンストラクション
public:
	void Load();
	CSpecimen(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CSpecimen)
	enum { IDD = IDD_SpecimenData };
	double	m_Height0;
	double	m_Height1;
	double	m_Height2;
	double	m_Height3;
	double	m_MembraneE;
	double	m_MembraneT;
	double	m_RodArea;
	double	m_CapWeight;
	double	m_RDInM;
	double	m_RDOutM;
	double	m_RHInM;
	double	m_RHOutM;
	double	m_DiaInM0;
	double	m_DiaInM1;
	double	m_DiaInM2;
	double	m_DiaInM3;
	double	m_DiameterIn0;
	double	m_DiameterIn1;
	double	m_DiameterIn2;
	double	m_DiameterIn3;
	double	m_DiameterOut0;
	double	m_DiameterOut1;
	double	m_DiameterOut2;
	double	m_DiameterOut3;
	double	m_DiaOutM0;
	double	m_DiaOutM1;
	double	m_DiaOutM2;
	double	m_DiaOutM3;
	double	m_HeightInM0;
	double	m_HeightInM1;
	double	m_HeightInM2;
	double	m_HeightInM3;
	double	m_HeightOutM0;
	double	m_HeightOutM1;
	double	m_HeightOutM2;
	double	m_HeightOutM3;
	double	m_Volume0;
	double	m_Volume1;
	double	m_Volume2;
	double	m_Volume3;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSpecimen)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CSpecimen)
	afx_msg void OnBUTTONSave();
	afx_msg void OnBUTTONUpdate();
	afx_msg void OnBUTTONBeConsol();
	afx_msg void OnBUTTONAfConsolidation();
	afx_msg void OnBUTTONToPresent1();
	afx_msg void OnBUTTONToPresent2();
	afx_msg void OnBUTTONToPresent3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SPECIMEN_H__417DC7FD_CE21_4B6B_988B_2D3050CBC61D__INCLUDED_)
