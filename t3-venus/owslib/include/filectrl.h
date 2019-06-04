/*****************************************************************************
ģ����      : filectl.h
�ļ���      : filectl.h
����ļ�    : 
�ļ�ʵ�ֹ���: �����ļ������ӿ�
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2014/02/24     1.0         ����ӡ      ����
******************************************************************************/
#ifndef FILECTRL_H
#define FILECTRL_H

#ifdef _WIN32
#include <direct.h>
#include <io.h>
#else
#include <stdarg.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>
#endif

#ifdef _WIN32
#define ACCESS _access
#define MKDIR(a) _mkdir((a))
#else
#define ACCESS access
#define MKDIR(a) mkdir((a),0755)
#endif

class CFileCtrl : boost::noncopyable //��ֹ��������ֵ ����
{
public:
	CFileCtrl();
	~CFileCtrl();

	BOOL Close();

public:
	BOOL Open( const std::string& strFile = "", const std::string& strType = "at+" );  //r w at+
	u64  GetLen();
	BOOL Write( const u8* pBuf, u64 nBufLen, s16 nPos = SEEK_CUR, u64 nMaxLen = MAX_FILE_LENGTH, u64 nSeekPos = 0L );
	u64  Read( u8* pBuf, u64 nBufLen, u64 nSeekPos = 0L );   //��nSeekPosλ�ö�ȡnBufLen��pBuf   Ĭ���ļ�ͷ

private:
	FILE* m_pFile;

	enum { MAX_FILE_LENGTH = 200*1024*1024 };

};


#endif