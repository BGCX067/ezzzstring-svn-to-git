/**
**		File : pak_config.h
**		Author : beyondcode
**		Date : 2010/05/28
**		Des : 编译过程中和平台相关的配置信息
**
**/

#ifndef _PAK_CONFIG_H_
#define _PAK_CONFIG_H_

//检测外部宏定义合法性
#include "pak_check.h"


//platform define
#define PAK_PLAT_WIN32 1
#define PAK_PLAT_LINUX 2
#define PAK_PLAT_UNIX 3
//default platform
#ifndef PAK_PLAT
#define PAK_PLAT PAK_PLAT_WIN32
#endif

//library control define
#define PAK_LIB_IMPORT	1
#define PAK_LIB_EXPORT	2
#define PAK_LIB_SRC		3
//default library control
#ifndef PAK_LIB_CONTROL
#define PAK_LIB_CONTROL PAK_LIB_IMPORT
#endif

//function control define
#define PAK_FUNC_WIN32_IMPORT __declspec(dllimport)
#define PAK_FUNC_WIN32_EXPORT __declspec(dllexport)
#define PAK_FUNC_WIN32_SRC
#define PAK_FUNC_LINUX_ALL
#define PAK_FUNC_UNIX_ALL

//编译配置选项

//选项 : PAK_PLAT
//可取值 : PAK_PLAT_WIN32; PAK_PLAT_LINUX; PAK_PLAT_UNIX; 
//说明 : 指定针对哪一个平台进行编译
//演示 : #define PAK_PLAT PAK_PLAT_WIN32
//#define PAK_PLAT PAK_PLAT_WIN32

//选项 : PAK_LIB_CONTROL
//可取值 : PAK_LIB_IMPORT; PAK_LIB_EXPORT
//说明 : 指定库适用于被导入还是导出
//演示 : #define PAK_LIB_CONTROL PAK_LIB_IMPORT
//#define PAK_LIB_CONTROL PAK_LIB_IMPORT

//选项 : PAK_FUNC_CONTROL
//可取值 : PAK_FUNC_WIN32_IMPORT; PAK_FUNC_WIN32_EXPORT; PAK_FUNC_LINUX_ALL PAK_FUNC_UNIX_ALL
//说明 : 库函数的导出控制，根据PAK_PLAT和PAK_LIB_CONTROL自动被选择，所以不能自行配置。

#endif //_PAK_CONFIG_H_
//last line for linux

