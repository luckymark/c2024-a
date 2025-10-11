#pragma once
#ifndef COMMON_HPP
#define COMMON_HPP 1
#include <Windows.h>
#include <tchar.h>
#include <cstdlib>
#pragma comment(lib, "winmm.lib")
#ifndef _Tstr(name)
#define _Tstr(name) _T(#name)
#endif // _Tstr(name)
#ifndef _ASSERT_
#if defined _MSVC_LANG && !defined _DEBUG // MSVC RELEASE
#define _ASSERT_(expr, msg) __assume(expr)
#elif defined _DEBUG || defined DEBUG // DEBUG
#define _ASSERT_(expr, msg)                                                                                               \
    do {    									                                                                          \
        if(!expr) {     					                                                                              \
    		MessageBox(NULL, _T(msg), _Tstr(Error), MB_OK);                                                               \
            ShellExecute(NULL, _Tstr(open), _Tstr(D:/ÎÄµµ/Visual Studio 2022/C++/Push_Boxes/Push_Boxes.sln), 0, 0, 1);    \
            exit(-1);									                                                                  \
        }												                                                                  \
    } while(false)
#else // OTHERS RELEASE
#define _ASSERT_(expr, msg)
#endif
#endif // _ASSERT_
#endif // COMMON_HPP