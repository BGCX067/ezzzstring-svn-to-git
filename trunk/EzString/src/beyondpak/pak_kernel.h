/**
**		File : pak_kernel.h
**		Author : beyondcode
**		Date : 2010/05/28
**		Des : beyondpak 跨平台核心函数声明/导出
**
**/


#ifndef _PAK_KERNEL_H_
#define _PAK_KERNEL_H_

#include "pak_kernel_crossplat.h"

#define PAK_FULLPATH_MAXLEN 260
#define PAK_CHILDREN_ID_COUNT 256
#define PAK_READ_BUFFER 2048

typedef int (*SAVE_NODE_VALUE)( FILE* pFile, PPAK_DIR_NODE pDirNode, long iValueOffset, size_t* punValueLen, PPAK_PKG pPkg, void* psExtra );
typedef void* (*LOAD_NODE_VALUE)( FILE* pFile, PPAK_DIR_NODE_RECORD pDirNodeRecord, void* psExtra );

PAK_CPP PAK_FUNC_CONTROL void GetPlatformInfo( void );

// character encoding convert function export
PAK_CPP PAK_FUNC_CONTROL int AToU2( const char* lpszSrcA, size_t nSrcALen, wchar_t* lpwszDestU2, size_t nDestU2Len );
PAK_CPP PAK_FUNC_CONTROL int AToU8( const char* lpszSrcA, size_t nSrcALen, char* lpszDestU8, size_t nDestU8Len );
PAK_CPP PAK_FUNC_CONTROL int U2ToA( const wchar_t* lpwszSrcU2, size_t nSrcU2Len, char* lpszDestA, size_t nDestALen );
PAK_CPP PAK_FUNC_CONTROL int U2ToU8( const wchar_t* lpwszSrcU2, size_t nSrcU2Len, char* lpszDestU8, size_t nDestU8Len );
PAK_CPP PAK_FUNC_CONTROL int U8ToA( const char* lpszSrcU8, size_t nSrcU8Len, char* lpszDestA, size_t nDestALen );
PAK_CPP PAK_FUNC_CONTROL int U8ToU2( const char* lpszSrcU8, size_t nSrcU8Len, wchar_t* lpwszDestU2, size_t nDestU2Len );

// io function export
PAK_CPP PAK_FUNC_CONTROL FILE* Pak_OpenFile( const char* pszu8FileName, const char* pszu8Mode );
PAK_CPP PAK_FUNC_CONTROL int Pak_ReadFile( FILE* hFile, char* pstrReadBuffer, size_t nReadLen, size_t* pnReadLen );
PAK_CPP PAK_FUNC_CONTROL int Pak_ReadFileAt( FILE* hFile, char* pstrReadBuffer, size_t nReadLen, size_t* pnReadLen, long lPos );
PAK_CPP PAK_FUNC_CONTROL int Pak_WriteFile( FILE* hFile, char* pstrWriteBuffer, size_t nWriteLen, size_t* pnWriteLen );
PAK_CPP PAK_FUNC_CONTROL int Pak_WriteFileAt( FILE* hFile, char* pstrWriteBuffer, size_t nWriteLen, size_t* pnWriteLen, long lPos );
PAK_CPP PAK_FUNC_CONTROL int Pak_SetFilePos( FILE* hFile, long lFilePos, int iBegin );
PAK_CPP PAK_FUNC_CONTROL int Pak_GetFilePos( FILE* hFile, long* plFilePos );
PAK_CPP PAK_FUNC_CONTROL int Pak_GetFileSize( FILE* hFile, long* plSize );
PAK_CPP PAK_FUNC_CONTROL int Pak_CloseFile( FILE* hFile );

// common package operation function
PAK_CPP PAK_FUNC_CONTROL PPAK_PKG CreatePackage();
PAK_CPP PAK_FUNC_CONTROL int SetPackageValue( PPAK_PKG psPkg, PPAK_DIR_NODE psPakNode );
PAK_CPP PAK_FUNC_CONTROL int SavePackage( PPAK_PKG pPkg, const char* pszSaveFileName, SAVE_NODE_VALUE pfnSaveNode );
PAK_CPP PAK_FUNC_CONTROL PPAK_PKG LoadPackage( const char* pszPkgFileName, LOAD_NODE_VALUE pfnLoadValue );
PAK_CPP PAK_FUNC_CONTROL int DeletePackage( PPAK_PKG pPkg );
PAK_CPP PAK_FUNC_CONTROL int SetPackageCallback( PPAK_PKG pPkg, int iType, PackageCallback pfnPkg );

// common package node operation function
PAK_CPP PAK_FUNC_CONTROL PPAK_DIR_NODE CreatePakNode( PAK_VALUE_CREATOR pfnValueCreator, PAK_VALUE_DESTROYER pfnValueDestroy );
PAK_CPP PAK_FUNC_CONTROL void* GetPakNodeValue( PPAK_DIR_NODE psPakNode );
PAK_CPP PAK_FUNC_CONTROL int AddPakNode( PPAK_DIR_NODE psPakNodeParent, PPAK_DIR_NODE psPakNode );
PAK_CPP PAK_FUNC_CONTROL int DelPakNode( PPAK_DIR_NODE psPakNode );
PAK_CPP PAK_FUNC_CONTROL int DestroyPakNode( PPAK_DIR_NODE psPakNode );
PAK_CPP PAK_FUNC_CONTROL int DestroyPakNodeEx( PPAK_DIR_NODE psPakNode );
PAK_CPP PAK_FUNC_CONTROL int GetPakNodeCount( PPAK_DIR_NODE pDirNodeRoot );
PAK_CPP PAK_FUNC_CONTROL int EnumPakNode( PPAK_DIR_NODE pDirNodeRoot, EnumDirTreeCallback pfnCallback );

// dir base operation function
// all the string are utf-8 encoding
PAK_CPP PAK_FUNC_CONTROL PPAK_DIR_STATUS OpenDir( const char* pszu8Dir );
PAK_CPP PAK_FUNC_CONTROL const PPAK_DIR ReadDir( PPAK_DIR_STATUS pDirStatus );
PAK_CPP PAK_FUNC_CONTROL int CloseDir( PPAK_DIR_STATUS pDirStatus );

// special package( dirtree ) wrapper operation function
PAK_CPP PAK_FUNC_CONTROL PPAK_PKG CreateDirTreePackage( const char* pszu8PathName );
PAK_CPP PAK_FUNC_CONTROL PPAK_PKG LoadDirTreePackage( const char* pszu8PathName );
PAK_CPP PAK_FUNC_CONTROL int SaveDirTreePackage( PPAK_PKG pPkg, const char* pszu8Pathname );
PAK_CPP PAK_FUNC_CONTROL int ExtractDirTreePackage( PPAK_PKG pPkg, const char* pszu8PathName );

// special package node( dirtree ) wrapper operation function
PAK_CPP PAK_FUNC_CONTROL PPAK_DIR_NODE GenerateDirTreeByPath( const char* pszu8RootDir );

#endif
//last line for linux

