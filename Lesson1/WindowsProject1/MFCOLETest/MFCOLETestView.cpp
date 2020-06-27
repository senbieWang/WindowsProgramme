﻿
// MFCOLETestView.cpp: CMFCOLETestView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCOLETest.h"
#endif

#include "MFCOLETestDoc.h"
#include "CntrItem.h"
#include "resource.h"
#include "MFCOLETestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCOLETestView

IMPLEMENT_DYNCREATE(CMFCOLETestView, CView)

BEGIN_MESSAGE_MAP(CMFCOLETestView, CView)
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_OLE_INSERT_NEW, &CMFCOLETestView::OnInsertObject)
	ON_COMMAND(ID_CANCEL_EDIT_CNTR, &CMFCOLETestView::OnCancelEditCntr)
	ON_COMMAND(ID_FILE_PRINT, &CMFCOLETestView::OnFilePrint)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCOLETestView 构造/析构

CMFCOLETestView::CMFCOLETestView() noexcept
{
	m_pSelection = nullptr;
	// TODO: 在此处添加构造代码

}

CMFCOLETestView::~CMFCOLETestView()
{
}

BOOL CMFCOLETestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCOLETestView 绘图

void CMFCOLETestView::OnDraw(CDC* pDC)
{
	if (!pDC)
		return;

	CMFCOLETestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	// TODO: 同时绘制文档中的所有 OLE 项

	// 在任意位置绘制选定项。  一旦
	//  实现了真正的绘制代码后，应移除此代码。  此位置
	//  与 CMFCOLETestCntrItem 返回的矩形完全对应，
	//  从而产生就地编辑的效果。

	// TODO: 最终绘制代码完成后移除此代码。
	if (m_pSelection != nullptr)
	{
		CSize size;
		CRect rect(10, 10, 210, 210);

		if (m_pSelection->GetExtent(&size, m_pSelection->m_nDrawAspect))
		{
			pDC->HIMETRICtoLP(&size);
			rect.right = size.cx + 10;
			rect.bottom = size.cy + 10;
		}
		m_pSelection->Draw(pDC, rect);
	}
}

void CMFCOLETestView::OnInitialUpdate()
{
	CView::OnInitialUpdate();


	// TODO: 写入最终选择模式代码之后移除此代码
	m_pSelection = nullptr;    // 初始化所选内容

}

void CMFCOLETestView::OnDestroy()
{
	// 析构时停用此项；这在
	// 使用拆分器视图时非常重要 
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != nullptr && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == nullptr);
   }
   CView::OnDestroy();
}



// OLE 客户端支持和命令

BOOL CMFCOLETestView::IsSelected(const CObject* pDocItem) const
{
	//下面的实现是足够的，如果所选内容包括
	// CMFCOLETestCntrItem 对象，则以下实现就足够了。若要处理其他选择机制，
	//  则应替换此处的实现

	// TODO: 实现对所选 OLE 客户端项进行测试的函数

	return pDocItem == m_pSelection;
}

void CMFCOLETestView::OnInsertObject()
{
	// 调用标准的“插入对象”对话框以获得有关
	//  对于新的 CMFCOLETestCntrItem 对象
	COleInsertDialog dlg;
	if (dlg.DoModal() != IDOK)
		return;

	BeginWaitCursor();

	CMFCOLETestCntrItem* pItem = nullptr;
	TRY
	{
		// 创建与此文档相连接的新项
		CMFCOLETestDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pItem = new CMFCOLETestCntrItem(pDoc);
		ASSERT_VALID(pItem);

		// 通过对话框数据初始化该项
		if (!dlg.CreateItem(pItem))
			AfxThrowMemoryException();  // 任何异常都将导致该结果
		ASSERT_VALID(pItem);

        if (dlg.GetSelectionType() == COleInsertDialog::createNewItem)
			pItem->DoVerb(OLEIVERB_SHOW, this);

		ASSERT_VALID(pItem);
		// 作为任意用户界面设计，这会将所选内容
		//  设置为插入的最后一项

		// TODO: 重新实现所选内容，使其适合于您的应用程序
		m_pSelection = pItem;   // 将所选内容设置为插入的最后一项
		pDoc->UpdateAllViews(nullptr);
	}
	CATCH(CException, e)
	{
		if (pItem != nullptr)
		{
			ASSERT_VALID(pItem);
			pItem->Delete();
		}
		AfxMessageBox(IDP_FAILED_TO_CREATE);
	}
	END_CATCH

	EndWaitCursor();
}

// 以下命令处理程序提供了标准键盘
//  用户界面以取消就地编辑会话。  此处，
//  容器(而不是服务器)将导致停用
void CMFCOLETestView::OnCancelEditCntr()
{
	// 关闭此视图中的任何就地活动项。
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != nullptr)
	{
		pActiveItem->Close();
	}
	ASSERT(GetDocument()->GetInPlaceActiveItem(this) == nullptr);
}

// 在就地编辑一个对象时，容器需要对 OnSetFocus 和 OnSize 
//  进行特殊处理
void CMFCOLETestView::OnSetFocus(CWnd* pOldWnd)
{
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != nullptr &&
		pActiveItem->GetItemState() == COleClientItem::activeUIState)
	{
		// 如果该项处于同一视图中，则需要将焦点设置到该项
		CWnd* pWnd = pActiveItem->GetInPlaceWindow();
		if (pWnd != nullptr)
		{
			pWnd->SetFocus();   // 不要调用基类
			return;
		}
	}

	CView::OnSetFocus(pOldWnd);
}

void CMFCOLETestView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != nullptr)
		pActiveItem->SetItemRects();
}

void CMFCOLETestView::OnFilePrint()
{
	//默认情况下，要求活动文档使用 IOleCommandTarget 打印自身。
	//如果不需要此行为，
	//请移除对 COleDocObjectItem::DoDefaultPrinting 调用。
	//如果由于某种原因调用失败，则将尝试使用 IPrint 接口打印
	//该文档对象。
	CPrintInfo printInfo;
	ASSERT(printInfo.m_pPD != nullptr);
	if (S_OK == COleDocObjectItem::DoDefaultPrinting(this, &printInfo))
		return;

	CView::OnFilePrint();

}


void CMFCOLETestView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCOLETestView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCOLETestView 诊断

#ifdef _DEBUG
void CMFCOLETestView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCOLETestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCOLETestDoc* CMFCOLETestView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCOLETestDoc)));
	return (CMFCOLETestDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCOLETestView 消息处理程序
