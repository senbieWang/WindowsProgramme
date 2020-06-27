// TextOutLearn.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "TextOutLearn.h"
#include "sysmets.h"
#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TEXTOUTLEARN, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEXTOUTLEARN));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;  //水平和垂直改变窗口时触发客户去重绘
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEXTOUTLEARN));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)::GetStockObject(WHITE_BRUSH) ;//(HBRUSH)(COLOR_WINDOW+1);  黑色背景
    wcex.lpszMenuName   = nullptr;//MAKEINTRESOURCEW(IDC_TEXTOUTLEARN);  //不加载菜单
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_VSCROLL/* | WS_HSCROLL */,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int  cxChar, cxCaps, cyChar;
    static int  cxClient, cyClient, iVscrollPos;
    HDC  hdc;
    int i;
    PAINTSTRUCT ps;
    TCHAR  szBuffer[10];
    TEXTMETRIC tm;  //字符的尺寸信息

    switch (message)
    {
    case WM_CREATE:
        hdc = GetDC(hWnd);
        GetTextMetrics(hdc,&tm);
        cxChar = tm.tmAveCharWidth; //字符平均宽度
        cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2; //大写字符的平均宽度
        cyChar = tm.tmHeight + tm.tmExternalLeading;  //总高度 + 外部间距
        ReleaseDC(hWnd, hdc);
        SetScrollRange(hWnd,SB_VERT,0, NUMLINES-1,FALSE );
        SetScrollPos(hWnd,SB_VERT,iVscrollPos,TRUE);
        return 0;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            hdc = BeginPaint(hWnd, &ps);
            for (int i = 0; i < NUMLINES ;i ++ ) 
            {
                TextOut(hdc,0,cyChar*i,sysmetrics[i].szLabel,lstrlen(sysmetrics[i].szLabel));
                TextOut(hdc, 22 * cxCaps, cyChar * i, sysmetrics[i].szDesc, lstrlen(sysmetrics[i].szDesc));
                SetTextAlign(hdc,TA_RIGHT |TA_TOP);  //后续的输出 从由上对齐
                TextOut(hdc, 22 * cxCaps +40*cxChar, cyChar * i, szBuffer, wsprintf(szBuffer,L"%5d",GetSystemMetrics(sysmetrics[i].iIndex)));
                SetTextAlign(hdc, TA_LEFT| TA_TOP);  //后续的输出
            }
            EndPaint(hWnd, &ps);
            return 0;
        }
    case WM_SIZE:
        cxClient = LOWORD(lParam);
        cyClient = HIWORD(lParam);
        return 0;
    case WM_VSCROLL:
        switch (LOWORD(lParam))
        {
        case SB_LINEUP:
            iVscrollPos -=1;
            break;
        case SB_LINEDOWN:
            iVscrollPos += 1;
            break;
        }
        iVscrollPos = max(0,min(iVscrollPos, NUMLINES-1));
        if (iVscrollPos!=GetScrollPos(hWnd,SB_VERT))
        {
            SetScrollPos(hWnd, SB_VERT, iVscrollPos,TRUE);
            InvalidateRect(hWnd,NULL,TRUE);
        }
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
