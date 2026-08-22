#if !defined(AFX_CONTROL_PRECONSOLIDATION_H__30299FEF_AFE0_4C93_A84F_A279C82D5B6B__INCLUDED_)
#define AFX_CONTROL_PRECONSOLIDATION_H__30299FEF_AFE0_4C93_A84F_A279C82D5B6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Control_PreConsolidation.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CControl_PreConsolidation ダイアログ

class CControl_PreConsolidation : public CDialog
{
// コンストラクション
public:
	CControl_PreConsolidation(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CControl_PreConsolidation)
	enum { IDD = IDD_Control_PreConsolidation };
	double	m_CellPreRate;
	double	m_CellPreTarget;
	double	m_AxisMotorSpeed;
	double	m_q;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CControl_PreConsolidation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CControl_PreConsolidation)
	afx_msg void OnBUTTONUpdate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_CONTROL_PRECONSOLIDATION_H__30299FEF_AFE0_4C93_A84F_A279C82D5B6B__INCLUDED_)
