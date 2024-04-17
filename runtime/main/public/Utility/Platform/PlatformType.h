#pragma once
#ifdef WIN32
#include<Windows.h>
using WindowHandle = HWND;
#else
using WindowHandle = unsigned long; // X11のWindow型は通常 unsigned long
#endif