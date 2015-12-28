/*----------------------------------------ezs_string.h----------------------------------------

文件名(FileName):		ezs_string.h

编码(Encoding):			UTF-8

编码测试(Encode Test):	釣魚島は中国に属している。
						일본어,한국의,매춘부,수정하지 마십시오 this src

日期(Date):				08/10/2010

作者(Author):			Ezzzcode

描述(Description):		EzString basic structure and function 

版本(Version):			1.0

------------------------------------------ezs_string.h----------------------------------------*/

#ifndef ezs_string_h
#define ezs_string_h

#include <string.h>
#include "beyondpak/pak_kernel.h"

PPAK_DIR_NODE Ezs_CreateStringNode();
int Ezs_DestroyStringNode( PPAK_DIR_NODE psPakStrNode );
int Ezs_DestroyStringNodeEx( PPAK_DIR_NODE psPakStrNode );
int Ezs_AddStringNode( PPAK_DIR_NODE psPakStrNoedeParent, PPAK_DIR_NODE psPakStrNode );
int Ezs_DelStringNode( PPAK_DIR_NODE psPakStrNode );

int Ezs_SetStringNodeName( PPAK_DIR_NODE psPakStrNode, const char* pszu8Name );
int Ezs_SetStringNodeValue( PPAK_DIR_NODE psPakStrNode, const char* pszu8Value );
int Ezs_SetStringNodeType( PPAK_DIR_NODE psPakStrNode, int nType );

PPAK_PKG Ezs_CreateStringPackage();
int Ezs_SetStringPackageValue( PPAK_PKG psPkg, PPAK_DIR_NODE psPakNode );
int Ezs_SaveStringPackage( PPAK_PKG psPkg, const char* pszu8PathName );
PPAK_PKG Ezs_LoadStringPackage( const char* pszu8PathName );
int Ezs_DestroyStringPackage( PPAK_PKG psPkg );

#endif