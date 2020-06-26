#pragma once
#include <tchar.h>
#include <WinUser.h>
#define NUMLINES ((int)(sizeof sysmetrics /sizeof sysmetrics[0]))

struct 
{
    int iIndex;
    const TCHAR* szLabel;
    const TCHAR* szDesc;
}
sysmetrics[] =
{
    {SM_CXSCREEN,  L"SM_CXSCREEN", L"screen width in pixels"},  //��Ļ���  ����
    {SM_CYSCREEN,  L"SM_CYSCREEN", L"screen height in pixels"},   //��Ļ�߶�  ����
    {SM_CXVSCROLL,  L"SM_CXVSCROLL", L"Vertical scroll width"},   //��ֱ  ���������
    {SM_CYVSCROLL,  L"SM_CYVSCROLL", L"Horizontal scroll heigth"},   //ˮƽ  �������߶�
    {SM_CYCAPTION,  L"SM_CYCAPTION", L"Caption bar heigth"},         // 
    {SM_CXBORDER,  L"SM_CXBORDER", L"Window border width"},         // 
    {SM_CYBORDER,  L"SM_CYBORDER", L"Window border heigth"},        //
    {SM_CXFIXEDFRAME,  L"SM_CXFIXEDFRAME", L"Dialog  window frame width"},      // 
    {SM_CYFIXEDFRAME,  L"SM_CYFIXEDFRAME", L"Dialog  window frame heigth"},      // 
};
