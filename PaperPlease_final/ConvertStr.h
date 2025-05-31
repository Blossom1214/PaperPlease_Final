#pragma once
#include <Windows.h>
#include <string>
using namespace std;
inline wstring ConvertToWString(const string& str)
{
	if (str.empty())
		return L"";
	int size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1,NULL, 0); //��Ƽ����Ʈ ����
	wstring result(size, 0);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &result[0], size);
	if(!result.empty()&&result.back()==L'\0')//result�� ��������ʰ��� \0�� ������ ������
	result.pop_back();//�����Ϸ���?(null���������ε�?)
	return result;
}

inline string ConvertToString(const wstring& wstr)
{
	if (wstr.empty())
		return "";
	int size = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
	//���� �ڵ�� �����ϳ� �Ǹ����� 2���� �Ű������ǰ�� utf-8,utf-7�� ��� ã�� �����°�쿡�� null�� �ξ�� �Ķ���� ���� ������ ������������ Ȯ��
	string result(size, 0);
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &result[0], size,NULL,NULL);
	if (!result.empty() && result.back() == '\0')
		result.pop_back();
	return result;
}

//string->wstring
//���ڵ�� ���� msdn�� �̷��� �����Ǿ�����
//int MultiByteToWideChar(
//	[in]            UINT                              CodePage,
//	[in]            DWORD                             dwFlags,
//	[in]            _In_NLS_string_(cbMultiByte)LPCCH lpMultiByteStr,
//	[in]            int                               cbMultiByte,
//	[out, optional] LPWSTR                            lpWideCharStr,
//	[in]            int                               cchWideChar
//);
// 
// �׾Ʒ��� ���� �ٽ� Ȯ������ �ٲܶ� wstring->string
//int WideCharToMultiByte(
//	[in]            UINT                               CodePage,
//	[in]            DWORD                              dwFlags,
//	[in]            _In_NLS_string_(cchWideChar)LPCWCH lpWideCharStr,
//	[in]            int                                cchWideChar,
//	[out, optional] LPSTR                              lpMultiByteStr,
//	[in]            int                                cbMultiByte,
//	[in, optional]  LPCCH                              lpDefaultChar,
//	[out, optional] LPBOOL                             lpUsedDefaultChar
//);