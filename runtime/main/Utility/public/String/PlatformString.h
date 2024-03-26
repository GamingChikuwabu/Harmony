#pragma once

// UNICODE マクロの定義に基づく TCHAR の定義
#ifdef UNICODE
#include<cwchar>
#define TEXT(str) L##str
using TCHAR = wchar_t;
#define TSTRCPY std::wcscpy
#define TSTRCAT std::wcscat
#define TSTRLEN std::wcslen
#define TSTRCMP std::wcscmp
#else
#define TEXT(str) str
using TCHAR = char;
#define TSTRCPY std::strcpy
#define TSTRCAT std::strcat
#define TSTRLEN std::strlen
#define TSTRCMP std::strcmp
#endif