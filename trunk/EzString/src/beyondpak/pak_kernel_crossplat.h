/**
**		File : pak_kernel_crossplat.h
**		Author : beyondcode
**		Date : 2010/05/28
**		Des : 跨平台标志宏和函数宏
**
**/

#ifndef _PAK_PLATFORM_H_
#define _PAK_PLATFORM_H_

#include "pak_config.h"

//compiler about macro definetion
#ifdef __cplusplus
#define PAK_CPP extern "C"
#else
#define PAK_CPP
#endif

//common header file include
#include "pak_kernel_common.h"

//platform about header file include
#if PAK_PLAT==PAK_PLAT_WIN32
#include "win32\pak_kernel_win32.h"
#define PAK_DIR_STATUS PAK_DIR_STATUS_WIN32
#define PPAK_DIR_STATUS PPAK_DIR_STATUS_WIN32
#define _OpenDir _OpenDir_win32
#define _ReadDir _ReadDir_win32
#define _CloseDir _CloseDir_win32

#define _AToU2 _AToU2_win32
#define _AToU8 _AToU8_win32
#define _U2ToA _U2ToA_win32
#define _U2ToU8 _U2ToU8_win32
#define _U8ToA _U8ToA_win32
#define _U8ToU2 _U8ToU2_win32

#elif PAK_PALT==PAK_PLAT_LINUX
#include "linux/pak_kernel_linux.h"
#elif PAK_PLAT==PAK_PLAT_UNIX
#include "unix/pak_kernel_unix.h"
#endif

//platform about macro definetion
#if PAK_PLAT==PAK_PLAT_WIN32

	#if PAK_LIB_CONTROL==PAK_LIB_IMPORT
	#define PAK_FUNC_CONTROL PAK_FUNC_WIN32_IMPORT
	#elif PAK_LIB_CONTROL==PAK_LIB_EXPORT
	#define PAK_FUNC_CONTROL PAK_FUNC_WIN32_EXPORT
	#elif PAK_LIB_CONTROL==PAK_LIB_SRC
	#define PAK_FUNC_CONTROL PAK_FUNC_WIN32_SRC
	#else
	#error "PAK_LIB_CONTROL is a error value"
	#endif
	
#elif PAK_PLAT==PAK_PLAT_LINUX

	#define PAK_FUNC_CONTROL PAK_FUNC_LINUX_ALL

#elif PAK_PLAT==PAK_PLAT_UNIX

	#define PAK_FUNC_CONTROL PAK_FUNC_UNIX_ALL

#else
	#error "PAK_PLAT is a error value"
#endif


#endif //_PAK_CONFIG_H_
//last line for linux

