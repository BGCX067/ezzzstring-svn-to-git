/************************************************************************

	File:			pak_io_win32.h
	Version:		1.0
	Changes:		A
	Author:			Stanley Lau
	Date:			2010.07.27
	Purpose:		File IO Module win32-platform Functions Declaration

************************************************************************/

#ifndef _PAK_IO_WIN32_H_
#define _PAK_IO_WIN32_H_


#include "pak_kernel_win32.h"
#include <debugheader.h>
#include <Windows.h>
#include <tchar.h>

//	Brief:				Open one file according the pstrMode
//	pstrFileName:		The file's name to open
//	pstrMode:			The mode how to open the file "r" "w" "b" "a"
//	return:				if success return the pointer to the FILE otherwise return NULL;
FILE* _OpenFile_win32( const char* pstrFileName, const char* pstrMode );

//	Brief:				Create Directory recursive
//	pszDirName:			The full directory name to create
//	return:				if success return 1 otherwise return 0
int _CreateDir_win32( const char* pszDirName );

int _IsDirExist_win32( const char* pszDirName );
static int _IsDirExist_win32T( LPCTSTR ptszDirName );
#endif
//Last line for linux

