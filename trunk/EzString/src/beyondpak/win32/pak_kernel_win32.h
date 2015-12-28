/**
**		File : pak_kernel_win32.h
**		Author : beyondcode
**		Date : 2010/05/31
**		Des : beyondpak win32平台核心函数声明
**
**/

#ifndef _PAK_KERNEL_WIN32_H_
#define _PAK_KERNEL_WIN32_H_

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "pak_kernel_common.h"

typedef struct _PAK_DIR_STATUS_WIN32
{
	HANDLE	hDir;
	PTCHAR	ptszDir;
	int bFirst;
	PAK_DIR PakDir;

} PAK_DIR_STATUS_WIN32, *PPAK_DIR_STATUS_WIN32;


PAK_DIR_STATUS_WIN32* _OpenDir_win32( const char* pszDir );
const PPAK_DIR _ReadDir_win32( PAK_DIR_STATUS_WIN32* pDirStatus );
int _CloseDir_win32( PAK_DIR_STATUS_WIN32* pDirStatus );

int _U2ToA_win32( const wchar_t* lpwszSrcU2, size_t nSrcU2Len, char* lpszDestA, size_t nDestALen );
int _U2ToU8_win32( const wchar_t* lpwszSrcU2, size_t nSrcU2Len, char* lpszDestU8, size_t nDestU8Len );
int _U8ToA_win32( const char* lpszSrcU8, size_t nSrcU8Len, char* lpszDestA, size_t nDestALen );
int _U8ToU2_win32( const char* lpszSrcU8, size_t nSrcU8Len, wchar_t* lpwszDestU2, size_t nDestU2Len );
int _AToU2_win32( const char* lpszSrcA, size_t nSrcALen, wchar_t* lpwszDestU2, size_t nDestU2Len );
int _AToU8_win32( const char* lpszSrcA, size_t nSrcALen, char* lpszDestU8, size_t nDestU8Len );


void _PrintConvertError_win32();
PPAK_DIR _ProcessDir_win32( PPAK_DIR_STATUS_WIN32 pDirStatus, WIN32_FIND_DATA* pwfd );
void _ProcessPath_win32( PTCHAR ptszPath, PTCHAR ptszExt );

#ifdef _UNICODE
#define _U8ToT _U8ToU2_win32
#define _TToU8 _U2ToU8_win32
#else
#define _U8ToT _U8ToA_win32
#define _TToU8 _AToU8_win32
#endif

#endif //_PAK_KERNEL_WIN32_H_
//Last line for linux

