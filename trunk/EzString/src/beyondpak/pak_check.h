/**
**		File : pak_check.h
**		Author : beyondcode
**		Date : 2010/05/31
**		Des : 检测宏是否能在外部被定义或者在外部被定义的宏是否合法
**
**/

#ifndef _PAK_CHECK_H_
#define _PAK_CHECK_H_

#ifdef PAK_PLAT_WIN32
#undef PAK_PLAT_WIN32
#pragma message("warning: PAK_PLAT_WIN32 is not allowed to define by user,it value will be reset!")
#endif

#ifdef PAK_PLAT_LINUX
#undef PAK_PLAT_LINUX
#pragma message("warning: PAK_PLAT_LINUX is not allowed to define by user,it value will be reset!")
#endif

#ifdef PAK_PLAT_UNIX
#undef PAK_PLAT_UNIX
#pragma message("warning: PAK_PLAT_UNIX is not allowed to define by user,it value will be reset!")
#endif

#ifdef PAK_LIB_IMPORT
#undef PAK_LIB_IMPORT
#pragma message("warning: PAK_PLAT_IMPORT PAK_LIB_EXPORT is not allowed to define by user,it value will be reset!")
#endif

#ifdef PAK_LIB_EXPORT
#undef PAK_LIB_EXPORT
#pragma message("warning: PAK_LIB_EXPORT is not allowed to define by user,it value will be reset!")
#endif

#ifdef PAK_FUNC_WIN32_IMPORT
#undef PAK_FUNC_WIN32_IMPORT
#pragma message("waning: PAK_FUNC_WIN32_IMPORT is not allowed to define by user,it value will be reset!")
#endif

#ifdef PAK_FUNC_WIN32_EXPORT
#undef PAK_FUNC_WIN32_EXPORT
#pragma message("warning: PAK_FUNC_WIN32_EXPORT is not allowed to define by user,it value will be reset!")
#endif

#ifdef PAK_FUNC_LINUX_ALL
#undef PAK_FUNC_LINUX_ALL
#pragma message("warning: PAK_FUNC_LINUX_ALL is not allowed to define by user,it value will be reset!")
#endif

#ifdef PAK_FUNC_UNIX_ALL
#undef PAK_FUNC_UNIX_ALL
#pragma message("warning: PAK_FUNC_UNIX_ALL is not allowed to define by user,it value will be reset!")
#endif

#ifdef PAK_FUNC_CONTROL
#undef PAK_FUNC_CONTROL
#pragma message("warning: PAK_FUNC_CONTROL is not allowed to define by user,it value will be reset!")
#endif

#endif //_PAK_CHECK_H_
//last line for linux

