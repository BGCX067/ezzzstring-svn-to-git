/*----------------------------------------ezs_string.c----------------------------------------

文件名(FileName):		ezs_string.c

编码(Encoding):			UTF-8

编码测试(Encode Test):	釣魚島は中国に属している。
						일본어,한국의,매춘부,수정하지 마십시오 this src

日期(Date):				08/10/2010

作者(Author):			Ezzzcode

描述(Description):		EzString basic structure and function implements	

版本(Version):			1.0

------------------------------------------ezs_string.c----------------------------------------*/

#include "ezs_string.h"
#include "EzzzUtility/EzzzUtility.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>

struct Ezs_StringNode;
struct Ezs_StringNodeHeader;
typedef struct Ezs_StringNode Ezs_StringNode;
typedef struct Ezs_StringNode* PEzs_StringNode;
typedef struct Ezs_StringNodeHeader Ezs_StringNodeHeader;
typedef struct Ezs_StringNodeHeader* PEzs_StringNodeHeader;

#define EZS_MAX_STRINGNAME	128
#define EZS_INIT_STRING		32

struct Ezs_StringNode
{
	int					nNodeType;
	char				szName[EZS_MAX_STRINGNAME];
	char*				pszu8Value;
	size_t				unValueLen;
};

struct Ezs_StringNodeHeader
{
	int					nNodeType;
	long				nNameOffset;
	size_t				nNameLen;
	long				nValueOffset;
	size_t				nValueLen;
};


static PEzs_StringNode _Ezs_NewStringNode();
static int _Ezs_FreeStringNode( PEzs_StringNode psStr );
static int _Ezs_SetStringNodeType( PEzs_StringNode psStrNode, int nType );
static int _Ezs_SetStringNodeName( PEzs_StringNode psStr, const char* pszName );
static int _Ezs_SetStringNodeValue( PEzs_StringNode psStr, const char* pszu8Value );

static int _Ezs_SaveValue( FILE* pFile, PPAK_DIR_NODE pDirNode, long iValueOffset, size_t* punValueLen, PPAK_PKG pPkg, void* psExtra );
static void* _Ezs_LoadValue( FILE* pFile, PPAK_DIR_NODE_RECORD pDirNodeRecord, void* psExtra );

PEzs_StringNode _Ezs_NewStringNode()
{
	PEzs_StringNode psStrNode	=	NULL;

	psStrNode = (PEzs_StringNode)calloc( 1, sizeof( Ezs_StringNode ) );
	
	return psStrNode;
}
int _Ezs_FreeStringNode( PEzs_StringNode psStr )
{
	assert( psStr );

	if ( psStr->pszu8Value )
	{
		free( psStr->pszu8Value );
		psStr->pszu8Value = NULL;
		psStr->unValueLen = 0;
	}

	free( psStr );
	return 1;
}

int _Ezs_SetStringNodeType( PEzs_StringNode psStrNode, int nType )
{
	assert( psStrNode );
	psStrNode->nNodeType = nType;
	return 1;
}

int _Ezs_SetStringNodeName( PEzs_StringNode psStr, const char* pszName )
{
	size_t	unNameLen	=	0;

	assert( psStr && pszName );

	unNameLen = strlen( pszName ) + 1;
	if ( unNameLen > EZS_MAX_STRINGNAME )
		return 0;

	strcpy( psStr->szName, pszName );
	return 1;
}
int _Ezs_SetStringNodeValue( PEzs_StringNode psStr, const char* pszu8Value )
{
	char*	pszu8NewValue	=	NULL;
	size_t	unValueLen		=	0;

	assert( psStr && pszu8Value );

	if ( psStr->pszu8Value )
	{
		free( psStr->pszu8Value );
		psStr->pszu8Value;
		psStr->unValueLen = 0;
	}
	unValueLen = strlen( pszu8Value ) + 1;
	pszu8NewValue = (char*)calloc( 1, unValueLen );
	if ( pszu8NewValue ) return 0;

	psStr->pszu8Value = pszu8NewValue;
	psStr->unValueLen = unValueLen;

	return 1;
}

PPAK_DIR_NODE Ezs_CreateStringNode()
{
	int				bRet			=	0;
	PPAK_DIR_NODE	psPakStrNode	=	NULL;
	PEzs_StringNode	psStrNode		=	NULL;

	Ezu_Error( psPakStrNode = CreatePakNode( &_Ezs_NewStringNode, &_Ezs_FreeStringNode ) );

	Ezu_Error( psStrNode = ( PEzs_StringNode )GetPakNodeValue( psPakStrNode ) );
	Ezu_Error( _Ezs_SetStringNodeType( psStrNode , 1 ) );
	
	bRet = 1;

	Ezu_ExitGate( 1 )
	if ( 0 == bRet )
	{
		Ezu_Release( psPakStrNode, DestroyPakNode );
	}
	return psPakStrNode;
}

int Ezs_DestroyStringNode( PPAK_DIR_NODE psPakStrNode )
{
	int	bRet	=	0;
	
	Ezu_Error( psPakStrNode );
	Ezu_Error( DestroyPakNode( psPakStrNode ) );
	
	bRet = 1;

	Ezu_ExitGate(1)
	return bRet;
}

int Ezs_DestroyStringNodeEx( PPAK_DIR_NODE psPakStrNode )
{
	int	bRet	=	0;
	
	Ezu_Error( psPakStrNode );
	Ezu_Error( DestroyPakNodeEx( psPakStrNode ) );
	
	bRet = 1;

	Ezu_ExitGate(1)
	return bRet;
}

int Ezs_AddStringNode( PPAK_DIR_NODE psPakStrNoedeParent, PPAK_DIR_NODE psPakStrNode )
{
	int				bRet		=	0;
	PEzs_StringNode	psStrNode	=	NULL;

	Ezu_Error( psPakStrNoedeParent && psPakStrNode );
	Ezu_Error( psStrNode = ( PEzs_StringNode)GetPakNodeValue( psPakStrNoedeParent ) );
	Ezu_Error( psStrNode->nNodeType == 0 );
	Ezu_Error( AddPakNode( psPakStrNoedeParent, psPakStrNode ) );
	bRet =1;

	Ezu_ExitGate(1)
	return bRet;
}
int Ezs_DelStringNode( PPAK_DIR_NODE psPakStrNode )
{
	int	bRet	=	0;

	Ezu_Error( psPakStrNode );
	Ezu_Error( DelPakNode( psPakStrNode ) );
	bRet = 1;

	Ezu_ExitGate(1)
	return bRet;
}

int Ezs_SetStringNodeName( PPAK_DIR_NODE psPakStrNode, const char* pszu8Name )
{
	int				bRet		=	0;
	PEzs_StringNode	psStrNode	=	NULL;

	Ezu_Error( psPakStrNode && pszu8Name );
	Ezu_Error( psStrNode = ( PEzs_StringNode)GetPakNodeValue( psPakStrNode) );
	Ezu_Error( _Ezs_SetStringNodeName( psStrNode, pszu8Name ) );
	
	bRet = 1;

	Ezu_ExitGate(1)
	return bRet;
}
int Ezs_SetStringNodeValue( PPAK_DIR_NODE psPakStrNode, const char* pszu8Value )
{
	int				bRet		=	0;
	PEzs_StringNode	psStrNode	=	NULL;

	Ezu_Error( psPakStrNode && pszu8Value );
	Ezu_Error( psStrNode = ( PEzs_StringNode )GetPakNodeValue( psPakStrNode ) );
	Ezu_Error( psStrNode->nNodeType == 0 );
	Ezu_Error( _Ezs_SetStringNodeValue( psStrNode, pszu8Value ) );

	bRet = 1;

	Ezu_ExitGate( 1 )
	return bRet;
}
int Ezs_SetStringNodeType( PPAK_DIR_NODE psPakStrNode, int nType )
{
	int				bRet		=	0;
	PEzs_StringNode	psStrNode	=	NULL;

	Ezu_Error( psPakStrNode );
	Ezu_Error( psStrNode = ( PEzs_StringNode )GetPakNodeValue( psPakStrNode ) );
	Ezu_Error( _Ezs_SetStringNodeType( psStrNode, nType ) );

	bRet = 1;

	Ezu_ExitGate(1)
	return bRet;
}

PPAK_PKG Ezs_CreateStringPackage()
{
	int			bRet	=	0;
	PPAK_PKG	psPkg	=	NULL;

	Ezu_Error( psPkg = CreatePackage() );
	bRet = 1;

	Ezu_ExitGate(1)
	return psPkg;
}

int Ezs_SetStringPackageValue( PPAK_PKG psPkg, PPAK_DIR_NODE psPakNode )
{
	int	bRet	=	0;

	Ezu_Error( psPkg && psPakNode );
	Ezu_Error( SetPackageValue( psPkg, psPakNode ) );
	
	bRet = 1;

	Ezu_ExitGate(1)
	return bRet;
}

int Ezs_SaveStringPackage( PPAK_PKG psPkg, const char* pszu8PathName )
{
	int	bRet	=	0;

	Ezu_Error( psPkg && pszu8PathName );
	Ezu_Error( SavePackage( psPkg, pszu8PathName, &_Ezs_SaveValue ) );
	bRet = 1;

	Ezu_ExitGate(1)
	return bRet;
}

PPAK_PKG Ezs_LoadStringPackage( const char* pszu8PathName )
{
	int			bRet	=	0;
	PPAK_PKG	psPkg	=	NULL;

	Ezu_Error( pszu8PathName );
	Ezu_Error( psPkg = LoadPackage( pszu8PathName, &_Ezs_LoadValue ) );

	bRet = 1;
	
	Ezu_ExitGate(1)
	return psPkg;
}

int Ezs_DestroyStringPackage( PPAK_PKG psPkg )
{
	int	bRet	=	0;

	Ezu_Error( psPkg );
	Ezu_Error( DeletePackage( psPkg ) );
	psPkg = NULL;

	bRet = 1;

	Ezu_ExitGate(1)
	return bRet;
}


int _Ezs_SaveValue( FILE* pFile, PPAK_DIR_NODE pDirNode, long iValueOffset, size_t* punValueLen, PPAK_PKG pPkg, void* psExtra )
{
	int						bRet					=	0;
	PEzs_StringNode			psStrNode				=	NULL;
	Ezs_StringNodeHeader	sStrNodeHeader			=	{ 0 };
	size_t					nValueLen				=	0;
	long					nStrNodeHeaderOffset	=	0;
	long					nStrNodeNameOffset		=	0;
	long					nStrNodeValueOffset		=	0;
	size_t					nLen					=	0;
	size_t					nRealWrite				=	0;
	

	Ezu_Error( pFile && pDirNode && punValueLen && pPkg );
	Ezu_Error( psStrNode = (PEzs_StringNode)GetPakNodeValue( pDirNode ) );

	nStrNodeHeaderOffset = iValueOffset;
	nValueLen += sizeof( Ezs_StringNodeHeader );

	sStrNodeHeader.nNodeType = psStrNode->nNodeType;

	nStrNodeNameOffset = iValueOffset + (long)nValueLen;
	nLen = EZS_MAX_STRINGNAME;	
	sStrNodeHeader.nNameOffset = nStrNodeNameOffset;
	sStrNodeHeader.nNameLen = nLen;
	Ezu_Error( Pak_WriteFileAt( pFile, psStrNode->szName, nLen, &nRealWrite, nStrNodeNameOffset) ); 
	Ezu_Error( nLen = nRealWrite );
	nValueLen += nLen;

	Ezu_Error( psStrNode->pszu8Value );
	nStrNodeValueOffset = iValueOffset + (long)nValueLen;
	nLen = psStrNode->unValueLen;
	sStrNodeHeader.nValueOffset = nStrNodeValueOffset;
	sStrNodeHeader.nValueLen = nLen;
	Ezu_Error( Pak_WriteFileAt( pFile, psStrNode->pszu8Value, nLen, &nRealWrite, nStrNodeValueOffset ) );
	Ezu_Error( nLen = nRealWrite );
	nValueLen += nLen;

	nLen = sizeof( Ezs_StringNodeHeader );
	Ezu_Error( Pak_WriteFileAt( pFile, (char*)&sStrNodeHeader, nLen, &nRealWrite, nStrNodeHeaderOffset ) );
	Ezu_Error( nLen = nRealWrite );
	
	*punValueLen = nValueLen;
	
	bRet = 1;

	Ezu_ExitGate(1)
	return bRet;
}
void* _Ezs_LoadValue( FILE* pFile, PPAK_DIR_NODE_RECORD pDirNodeRecord, void* psExtra )
{
	int						bRet			=	0;
	PEzs_StringNode			psStrNode		=	NULL;
	Ezs_StringNodeHeader	sStrNodeHeader	=	{ 0 };

	long					nStrNodeHeaderOffset	=	0;
	long					nStrNodeNameOffset		=	0;
	long					nStrNodeValueOffset		=	0;
	size_t					nLen					=	0;
	size_t					nRealRead				=	0;

	char*					pszStr					=	0;

	Ezu_Error( pFile && pDirNodeRecord );
	
	nStrNodeHeaderOffset = pDirNodeRecord->nValueRecord;
	nLen = sizeof( Ezs_StringNodeHeader );
	Ezu_Error( Pak_ReadFileAt( pFile, (char*)&sStrNodeHeader, nLen, &nRealRead, nStrNodeHeaderOffset ) );
	Ezu_Error( nLen == nRealRead );

	Ezu_Error( psStrNode = _Ezs_NewStringNode() );

	Ezu_Error( pszStr = (char*)malloc( sStrNodeHeader.nNameLen + 1 ) ); //多分配一个字节，置零，防止原本文件中的零结尾的字符串被篡改后出错
	nStrNodeNameOffset = sStrNodeHeader.nNameOffset;
	nLen = sStrNodeHeader.nNameLen;
	Ezu_Error( Pak_ReadFileAt( pFile, pszStr, nLen, &nRealRead, nStrNodeNameOffset ) );
	Ezu_Error( nLen == nRealRead );
	Ezu_Error( _Ezs_SetStringNodeName( psStrNode, pszStr ) );
	Ezu_Free( pszStr );
	
	Ezu_Error( pszStr = (char*)malloc( sStrNodeHeader.nValueLen + 1 ) );
	nStrNodeValueOffset = sStrNodeHeader.nValueOffset;
	nLen = sStrNodeHeader.nValueLen;
	Ezu_Error( Pak_ReadFileAt( pFile, pszStr, nLen, &nRealRead, nStrNodeValueOffset ) );
	Ezu_Error( nLen == nRealRead );
	Ezu_Error( _Ezs_SetStringNodeValue( psStrNode, pszStr ) );

	Ezu_Error( _Ezs_SetStringNodeType( psStrNode, sStrNodeHeader.nNodeType ) );
	Ezu_Free( pszStr );
	
	bRet = 1;

	Ezu_ExitGate(1)
	Ezu_Free( pszStr );
	if ( 0 == bRet )
	{
		_Ezs_FreeStringNode( psStrNode );
		psStrNode = NULL;
	}
	return (void*)psStrNode;
}