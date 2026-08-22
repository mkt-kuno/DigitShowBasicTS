#if !defined(AFX_BOARDSETTINGS_H__863F8900_B83E_4A2D_859A_7A3A7A3EC91E__INCLUDED_)
#define AFX_BOARDSETTINGS_H__863F8900_B83E_4A2D_859A_7A3A7A3EC91E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BoardSettings.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CBoardSettings ダイアログ

class CBoardSettings : public CDialog
{
// コンストラクション
public:
	CBoardSettings(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CBoardSettings)
	enum { IDD = IDD_BoardSettings };
	CString	m_AdMaxChannel1;
	CString	m_AdMaxChannel2;
	CString	m_AdMethod1;
	CString	m_AdMethod2;
	CString	m_AdRange1;
	CString	m_AdRange2;
	CString	m_AdResolution1;
	CString	m_AdResolution2;
	CString	m_DaMaxChannel;
	CString	m_DaRange;
	CString	m_DaResolution;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CBoardSettings)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CBoardSettings)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_BOARDSETTINGS_H__863F8900_B83E_4A2D_859A_7A3A7A3EC91E__INCLUDED_)
