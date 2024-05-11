#pragma once
#include <string>
#include <sstream>
#include <gc_cpp.h>
#include <gc_allocator.h>

// マルチバイト文字セット（MBCS）およびUNICODEのサポート
#ifdef UNICODE
using HMString = std::basic_string<wchar_t, std::char_traits<wchar_t>, gc_allocator<wchar_t>>;
using StringStream = std::basic_stringstream<wchar_t, std::char_traits<wchar_t>, gc_allocator<wchar_t>>;
using StringStreamBuf = std::basic_stringbuf<wchar_t, std::char_traits<wchar_t>, gc_allocator<wchar_t>>;
using InputStringStream = std::basic_istringstream<wchar_t, std::char_traits<wchar_t>, gc_allocator<wchar_t>>;
using OutputStringStream = std::basic_ostringstream<wchar_t, std::char_traits<wchar_t>, gc_allocator<wchar_t>>;
using TCHAR = wchar_t;
#define TSTR(str) L##str // ワイド文字列リテラル
#else
using HMString = std::basic_string<char, std::char_traits<char>, gc_allocator<char>>;
using StringStream = std::basic_stringstream<char, std::char_traits<char>, gc_allocator<char>>;
using StringStreamBuf = std::basic_stringbuf<char, std::char_traits<char>, gc_allocator<char>>;
using InputStringStream = std::basic_istringstream<char, std::char_traits<char>, gc_allocator<char>>;
using OutputStringStream = std::basic_ostringstream<char, std::char_traits<char>, gc_allocator<char>>;
using TCHAR = char;
#define TSTR(str) str 
#endif // UNICODE