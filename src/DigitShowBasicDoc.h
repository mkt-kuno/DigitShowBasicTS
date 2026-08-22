// DigitShowBasicDoc.h : CDigitShowBasicDoc クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_DIGITSHOWBASICDOC_H__0F5B25DB_9338_44C6_9841_265C5A221957__INCLUDED_)
#define AFX_DIGITSHOWBASICDOC_H__0F5B25DB_9338_44C6_9841_265C5A221957__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//---Specimen Data---
typedef	struct{	
		double	DiameterIn[4];			double	DiameterOut[4];	
		double	Height[4];
		double	Volume[4];
		double	MembraneModulus;		double	MembraneThickness;
		double	RodArea;				double	CapWeight;
		double	RDiaInM;				double	RDiaOutM;	
		double	RHeightInM;				double	RHeightOutM;
		double	DiaInMembrane[4];		double	DiaOutMembrane[4];
		double	HeightInMembrane[4];	double	HeightOutMembrane[4];
	} Specimen;
		
//---Control Data---	
typedef	struct{
		bool	flag[3];	int		time[3];
		double	p[3];		double	q[3];			double	u[3];
		double	sigma[3];	double	sigmaRate[3];	double	sigmaAmp[3];
		double	strain[3];	double	strainRate[3];	double	strainAmp[3];
		double	K0;
		double	AxisClutch;		double	AxisSpeed;
		double	TorsionClutch;	double	TorsionSpeed;
	} Control;

class CDigitShowBasicDoc : public CDocument
{
protected: // シリアライズ機能のみから作成します。
	CDigitShowBasicDoc();
	DECLARE_DYNCREATE(CDigitShowBasicDoc)

// アトリビュート
public:

// オペレーション
public:

//オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDigitShowBasicDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	void Rs232c_GetWeight();
	void Rs232c_GetData();
	void Rs232c_SendData();
	void Rs232c_Close();
	void Rs232c_Open();
	void MonotonicTorsionalLoadingConstPA();
	void MonotonicAxialLoadingConstP();
	void CyclicAxialLoading_OR();
	void Creep();
	void SmallCyclicAxialLoading();
	void CyclicAxialLoading();
	void MonotonicAxialLoading();
	void SmallCyclicTorsionalLoadingCNS();
	void SmallCyclicTorsionalLoading();
	void CyclicTorsionalLoadingCNS();
	void CyclicTorsionalLoading();
	void MonotonicTorsionalLoadingCNS();
	void MonotonicTorsionalLoading();
	void EffectiveStressPathLoading();
	void FileControlableConsolidation();
	void SaveToFile2();
	void Allocate_Memory();
	void Stop_Control();
	void Start_Control();
	void CloseBoard();
	void OpenBoard();
	void SaveToFile();
	void Control_DA();
	void Cal_Param();
	void Cal_Physical();
	void DA_OUTPUT();
	void AD_INPUT();
	virtual ~CDigitShowBasicDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CDigitShowBasicDoc)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DIGITSHOWBASICDOC_H__0F5B25DB_9338_44C6_9841_265C5A221957__INCLUDED_)
