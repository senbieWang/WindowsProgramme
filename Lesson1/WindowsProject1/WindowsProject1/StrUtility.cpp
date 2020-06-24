#include "StrUtility.h"

void Utility::char_wcharTest() 
{
	wchar_t wch[] = L"He�й�o";
	int iLength = sizeof(wch);    // 12�ֽ�
	iLength = wcslen(wch);   //�м����ַ�  5 

	char ch[] = "He�й�o";
	iLength = sizeof(ch);    // 8�ֽ�
	iLength = strlen(ch);    // 7���ַ�  need note

	const wchar_t* cwch = L"He�й�o";
	iLength = sizeof(cwch);    // 4�ֽ�
	iLength = wcslen(cwch);   //  5�ַ� 

	const char* cch = "He�й�o";
	iLength = sizeof(cch);    // 4�ֽ�
	iLength = strlen(cch);    // 7�ַ�  need note
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