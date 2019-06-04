/*****************************************************************************
模块名      : filectl.h
文件名      : filectl.h
相关文件    : 
文件实现功能: 磁盘文件操作接口
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2014/02/24     1.0         刘德印      创建
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

class CFileCtrl : boost::noncopyable //防止拷贝、赋值 保护
{
public:
	CFileCtrl();
	~CFileCtrl();

	BOOL Close();

public:
	BOOL Open( const std::string& strFile = "", const std::string& strType = "at+" );  //r w at+
	u64  GetLen();
	BOOL Write( const u8* pBuf, u64 nBufLen, s16 nPos = SEEK_CUR, u64 nMaxLen = MAX_FILE_LENGTH, u64 nSeekPos = 0L );
	u64  Read( u8* pBuf, u64 nBufLen, u64 nSeekPos = 0L );   //从nSeekPos位置读取nBufLen到pBuf   默认文件头

private:
	FILE* m_pFile;

	enum { MAX_FILE_LENGTH = 200*1024*1024 };

};


#endif