
// CntrItem.h: CMFCOLETestCntrItem 类的接口
//

#pragma once

class CMFCOLETestDoc;
class CMFCOLETestView;

class CMFCOLETestCntrItem : public COleClientItem
{
	DECLARE_SERIAL(CMFCOLETestCntrItem)

// 构造函数
public:
	CMFCOLETestCntrItem(CMFCOLETestDoc* pContainer = nullptr);
		// 注意: 允许 pContainer 为 NULL 以启用 IMPLEMENT_SERIALIZE
		//  IMPLEMENT_SERIALIZE 要求类具有带零
		//  参数的构造函数。  OLE 项通常是用
		//  非 null 文档指针

// 特性
public:
	CMFCOLETestDoc* GetDocument()
		{ return reinterpret_cast<CMFCOLETestDoc*>(COleClientItem::GetDocument()); }
	CMFCOLETestView* GetActiveView()
		{ return reinterpret_cast<CMFCOLETestView*>(COleClientItem::GetActiveView()); }

public:
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	virtual void OnActivate();

protected:
	virtual void OnGetItemPosition(CRect& rPosition);
	virtual void OnDeactivateUI(BOOL bUndoable);
	virtual BOOL OnChangeItemPosition(const CRect& rectPos);
	virtual BOOL OnShowControlBars(CFrameWnd* pFrameWnd, BOOL bShow);

// 实现
public:
	~CMFCOLETestCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void Serialize(CArchive& ar);
};

