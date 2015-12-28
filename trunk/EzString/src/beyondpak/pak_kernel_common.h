/**
**		File : pak_kernel_common.h
**		Author : beyondcode
**		Date : 2010/06/10
**		Des : beyondpak 通用平台核心
**
**/

#ifndef _PAK_KERNEL_COMMON_H_
#define _PAK_KERNEL_COMMON_H_

#include <string.h>
#include <stdlib.h>

#define DIRTYPE_DIR 1
#define DIRTYPE_FILE 2

#define ON_PRE_PACKFILE 0
#define ON_PACKFILE 1
#define ON_POST_PACKFILE 2
#define ON_PRE_EXTRACTFILE 3
#define ON_EXTRACTFILE 4
#define ON_POST_EXTRACTFILE 5
#define MAX_PACKAGE_CALLBACK 6

struct _PAK_STACK;
struct _PAK_STACK_ITEM;
struct _PAK_DIR;
struct _PAK_DIR_NODE;
struct _PAK_DIR_NODE_RECORD;
struct _PAK_PKG_HEAD;
struct _PAK_PKG;
struct _PAK_VALUE_RECORD;
typedef struct _PAK_STACK		PAK_STACK;
typedef struct _PAK_STACK*		PPAK_STACK;
typedef struct _PAK_STACK_ITEM	PAK_STACK_ITEM;
typedef struct _PAK_STACK_ITEM*	PPAK_STACK_ITEM;
typedef struct _PAK_DIR			PAK_DIR;
typedef struct _PAK_DIR*		PPAK_DIR;
typedef struct _PAK_DIR_NODE	PAK_DIR_NODE;
typedef struct _PAK_DIR_NODE*	PPAK_DIR_NODE;
typedef struct _PAK_DIR_NODE_RECORD	PAK_DIR_NODE_RECORD;
typedef struct _PAK_DIR_NODE_RECORD*	PPAK_DIR_NODE_RECORD;
typedef struct _PAK_PKG_HEAD	PAK_PKG_HEAD;
typedef struct _PAK_PKG_HEAD*	PPAK_PKG_HEAD;
typedef struct _PAK_PKG			PAK_PKG;
typedef struct _PAK_PKG*		PPAK_PKG;
typedef struct _PAK_VALUE_RECORD PAK_VALUE_RECORD;
typedef struct _PAK_VALUE_RECORD* PPAK_VALUE_RECORD;

typedef int (*EnumDirTreeCallback)( PPAK_DIR_NODE pPakNode );
typedef int (*PackageCallback)( const PPAK_DIR_NODE pPakNode, size_t nCur, size_t nTotal, void* pParam );


struct _PAK_STACK_ITEM
{
	void*			pValue;
	void*			pValueExtra1;
	PPAK_STACK_ITEM	pNext;
};

struct _PAK_STACK
{
	PPAK_STACK_ITEM	pStackTop;
};

struct _PAK_DIR
{
	char*	pszName;		//Directory Name Buffer
	size_t	nNameLen;		//Directory Name Buffer length
	long	nContent;
	size_t	nContentLen;
	int		nType;			//Directory Type
};
struct _PAK_VALUE_RECORD
{
	int				iType;			//Dir type
	long			nName;			//Dir name offset
	size_t			nNameLen;		//Dir name len
	long			nConten;		//Contents offset
	size_t			nContenLen;		//Contents len
};

typedef void* (*PAK_VALUE_CREATOR)();
typedef int (*PAK_VALUE_DESTROYER)(void* pValue );

struct _PAK_DIR_NODE
{
	void*				psValue;	
	PAK_VALUE_CREATOR	pfnValueCreator;
	PAK_VALUE_DESTROYER	pfnValueDestroy;

	PPAK_DIR_NODE		pParentPakDir;
	PPAK_DIR_NODE		pBrotherPakDir;
	PPAK_DIR_NODE		pChildPakDir;
	size_t				nNodeID;
};


struct _PAK_PKG_HEAD
{
	char			szMagic[2];
	size_t			nRecordCount;
};

struct _PAK_DIR_NODE_RECORD
{
	size_t			nID;			//Record ID
	long			nChildren;		//Sub directory record number array(size_t) offset
	size_t			nChildrenLen;	//Sub directory record number len;
	long			nValueRecord;
	size_t			nValueRecordLen;
};

struct _PAK_PKG
{
	char*				pszPkgName;
	PAK_PKG_HEAD		PkgHeader;
	PPAK_DIR_NODE_RECORD		pPkgRecords;
	size_t				nPkgRecordCount;
	PPAK_DIR_NODE		pDirTree;
	PackageCallback		apfnCallbacks[MAX_PACKAGE_CALLBACK];

};

typedef int (*DirFilterCallback)( PPAK_DIR pPakDir );
PPAK_DIR _CreatePakDir();
int _DestroyPakDir( PPAK_DIR psPakDir );
int _InitDir( PPAK_DIR pPakDir );
int _ClearDir( PPAK_DIR pPakDir );
int _CopyDir( PPAK_DIR pPakSrcDir, PPAK_DIR pPakDestDir );
int _SetDirName( PPAK_DIR pPakDestDir, const char* pszDirName );
int _SetDirType( PPAK_DIR pDirDest, int nType );
int _ReleaseDir( PPAK_DIR pPakSrcDir );
int _CheckDir( PPAK_DIR pPakDir );
size_t _GetDirBufferLen( PPAK_DIR pPakDir );
size_t _GetDirNameLen( PPAK_DIR pPakDir );
int _MallocDir( PPAK_DIR pPakDir, size_t NameLen );

//Filter
//return
//0:Filter this PAK_DIR
//1:No Filter this PAK_DIR
int	_FilterDir( PPAK_DIR pPakDir, DirFilterCallback pfnCallback );

//Default DirFilter function
//return
//0:Filter this PAK_DIR
//1:No Filter this PAK_DIR
int DefaultDirFilter( PPAK_DIR pPakDir );



PPAK_DIR_NODE _GetDirNode( PAK_VALUE_CREATOR pfnValueCreator, PAK_VALUE_DESTROYER pfnValueDestroy );
int _AddDirNode( PPAK_DIR_NODE psParentNode, PPAK_DIR_NODE psNode );
int _DeleteDirNode( PPAK_DIR_NODE psNode );
int _DestroyDirNode( PPAK_DIR_NODE psDestroy );
int _DestroyDirNodeEx( PPAK_DIR_NODE psDestroy );

int _InitDirNode( PPAK_DIR_NODE pDirNode, PAK_VALUE_CREATOR pfnValueCreator, PAK_VALUE_DESTROYER pfnValueDestroy );
int _RecycleDirNode( PPAK_DIR_NODE pPakNode );
int _SetDirNodeParent( PPAK_DIR_NODE pDirNode, PPAK_DIR_NODE pDirNodeParent );
int _SetDirNodeID( PPAK_DIR_NODE pDirNode, size_t nID );
int _SetDirNodeValue( PPAK_DIR_NODE pDirNode, void* psValue );
void* _GetDirNodeValue( PPAK_DIR_NODE pDirNode );

int	_GetDirNodeFullPath( PPAK_DIR_NODE pPakNode, char* pszPathBuffer, size_t* punPathBufferSize );
int	_GetDirNodeFullName( PPAK_DIR_NODE pPakNode, char* pszPathBuffer, size_t* punPathBufferSize );
int _SetDirNodeName( PPAK_DIR_NODE pDirNode, const char* pszDirName );
int _SetDirNodeType( PPAK_DIR_NODE pDirNode, int nType );

PPAK_STACK _NewStack();
int _DelStack( PPAK_STACK pStack );
int _PushStack( PPAK_STACK pStack, PPAK_STACK_ITEM pItem );
PPAK_STACK_ITEM _PopStack( PPAK_STACK pStack );
PPAK_STACK_ITEM _TopStack( PPAK_STACK pStack );
PPAK_STACK_ITEM _NewStackItem();
int _DelStackItem( PPAK_STACK_ITEM pStackItem );
int _RemoveStackItem( PPAK_STACK pStack, PPAK_STACK_ITEM pItem );
#endif //_PAK_KERNEL_COMMON_H_
//last line for linux

