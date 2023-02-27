#if !defined(AFX_CONTROL_FILE_H__B0F000B9_C3E1_46CF_8854_4D2FE6E59329__INCLUDED_)
#define AFX_CONTROL_FILE_H__B0F000B9_C3E1_46CF_8854_4D2FE6E59329__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Control_File.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CControl_File ダイアログ

class CControl_File : public CDialog
{
// コンストラクション
public:
	CControl_File(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CControl_File)
	enum { IDD = IDD_Control_File };
	int		m_CFNUM;
	int		m_CURNUM;
	double	m_CFPARA0;
	double	m_CFPARA1;
	double	m_CFPARA2;
	double	m_CFPARA3;
	double	m_CFPARA4;
	double	m_CFPARA5;
	double	m_CFPARA6;
	double	m_CFPARA7;
	double	m_CFPARA8;
	double	m_CFPARA9;
	int		m_CtrlNo;
	int		m_StepNo;
	double	m_CFPARA10;
	double	m_CFPARA11;
	double	m_CFPARA12;
	double	m_CFPARA13;
	double	m_CFPARA14;
	double	m_CFPARA15;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CControl_File)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CControl_File)
	//afx_msg void OnLoadFile();
	afx_msg void OnBUTTONReadFile();
	afx_msg void OnBUTTONSaveFile();
	afx_msg void OnBUTTONLoad();
	afx_msg void OnBUTTONUpdate();
	afx_msg void OnCHECKChangeNo();
	afx_msg void OnBUTTONStepDec();
	afx_msg void OnBUTTONStepInc();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_CONTROL_FILE_H__B0F000B9_C3E1_46CF_8854_4D2FE6E59329__INCLUDED_)
