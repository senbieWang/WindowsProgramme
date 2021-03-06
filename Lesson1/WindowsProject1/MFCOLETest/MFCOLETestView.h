﻿
// MFCOLETestView.h: CMFCOLETestView 类的接口
//

#pragma once

class CMFCOLETestCntrItem;

class CMFCOLETestView : public CView
{
protected: // 仅从序列化创建
	CMFCOLETestView() noexcept;
	DECLARE_DYNCREATE(CMFCOLETestView)

// 特性
public:
	CMFCOLETestDoc* GetDocument() const;
	// m_pSelection 将所选内容保存在当前 CMFCOLETestCntrItem 中。
	// 对于许多应用程序，这种成员变量不足以
	//  表示某个选择，例如在不属于
	//  CMFCOLETestCntrItem 的对象中选定的一个或多个对象。提供这种选择
	//  机制的目的只是帮助入门

	// TODO: 用适合应用程序的选择机制替换此选择机制
	CMFCOLETestCntrItem* m_pSelection;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL IsSelected(const CObject* pDocItem) const;// 容器支持

// 实现
public:
	virtual ~CMFCOLETestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnDestroy();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnInsertObject();
	afx_msg void OnCancelEditCntr();
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MFCOLETestView.cpp 中的调试版本
inline CMFCOLETestDoc* CMFCOLETestView::GetDocument() const
   { return reinterpret_cast<CMFCOLETestDoc*>(m_pDocument); }
#endif

