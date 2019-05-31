// stdafx.cpp : source file that includes just the standard includes
//	handInputTablet.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"


 long      g_lOrigResolutionX =  1366 ;//ԭ�ֱ���
 long      g_lOrigResolutionY =  768;//ԭ�ֱ���
 BOOL      g_bResolutionAdp = TRUE ;        //�Ƿ���зֱ�������Ӧ

 
//�ֱ�������Ӧ
void  ResolutionAdp( long &nx, long &ny)
{
    if ( !g_bResolutionAdp )
    {
        return;
    }
    long curX =  GetSystemMetrics(SM_CXSCREEN );
    long curY = GetSystemMetrics(SM_CYSCREEN);
    
    if ( g_lOrigResolutionX != 0 )
    {
        nx = nx* curX / g_lOrigResolutionX;
    }
    
    if ( g_lOrigResolutionY != 0 )
    {
        ny = ny* curY / g_lOrigResolutionY;
    }
    
}