/*----------------------------------------ezs_main_win32.c----------------------------------------

文件名(FileName):		ezs_main_win32.c	

编码(Encoding):			UTF-8

编码测试(Encode Test):	釣魚島は中国に属している。
						일본어,한국의,매춘부,수정하지 마십시오 this src

日期(Date):				12/10/2010

作者(Author):			Ezzzcode

描述(Description):		EzzzString Win32 Main Module	

版本(Version):			1.0

------------------------------------------ezs_main_win32.c----------------------------------------*/

#include <Windows.h>
#include <tchar.h>

#include "ezs_string.h"

INT WINAPI _tWinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd )
{
	PPAK_DIR_NODE psStrNodeRoot	=	NULL;

	psStrNodeRoot = Ezs_CreateStringNode();
	if( !psStrNodeRoot )
	{
		MessageBox( NULL, _T("Ezs_CreateStringNode Errrr"), _T("Errrrr"), MB_OK );
		return 0;		
	}

	Ezs_SetStringNodeType( psStrNodeRoot, 1 );
	Ezs_SetStringNodeName( psStrNodeRoot, "UI_TITLE" );
	Ezs_SetStringNodeValue( psStrNodeRoot, "EzzzString" );
	
	if ( !Ezs_DestroyStringNode( psStrNodeRoot ) )
	{
		MessageBox( NULL, _T("Ezs_DestroyStringNode Error"), _T("Errrr"), MB_OK );
		return 0;
	}
	psStrNodeRoot = NULL;

	MessageBox( NULL, _T("CreateStringNode & DestroyStringNode Succcccc"), _T("Succccc"), MB_OK );
	return 0;
}
