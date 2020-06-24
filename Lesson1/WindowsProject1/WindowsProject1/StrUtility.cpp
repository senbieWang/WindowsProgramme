#include "StrUtility.h"

void Utility::char_wcharTest() 
{
	wchar_t wch[] = L"He中国o";
	int iLength = sizeof(wch);    // 12字节
	iLength = wcslen(wch);   //有几个字符  5 

	char ch[] = "He中国o";
	iLength = sizeof(ch);    // 8字节
	iLength = strlen(ch);    // 7个字符  need note

	const wchar_t* cwch = L"He中国o";
	iLength = sizeof(cwch);    // 4字节
	iLength = wcslen(cwch);   //  5字符 

	const char* cch = "He中国o";
	iLength = sizeof(cch);    // 4字节
	iLength = strlen(cch);    // 7字符  need note
}

int Utility::MessageBoxPrintf(const TCHAR* szCaption, const TCHAR* szFormate, ...)
{
	TCHAR szBuffer[1024];
	va_list pArgList;
	va_start(pArgList, szFormate);
	_vsntprintf_s(szBuffer,sizeof(szBuffer)/sizeof(TCHAR), szFormate, pArgList);
	va_end(pArgList);

	return  MessageBox(NULL, szBuffer, szCaption,MB_OK);
}