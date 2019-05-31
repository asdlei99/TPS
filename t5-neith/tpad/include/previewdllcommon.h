#ifndef PREVIEWDLLCOMMON_H
#define PREVIEWDLLCOMMON_H

#ifndef DLL_EXPORTS
#define DLL_DECL __declspec(dllexport)
#else
#define DLL_DECL __declspec(dllimport)
#endif



typedef struct TPdfImageInfo {
	int nTotalPages;
	int nCurrentPage;

	CString strOutPutFilePath;
	CString strOriFilePath;
	CString strFileName;

	TPdfImageInfo()
	{
		nTotalPages = -1;
		nCurrentPage = -1;
		strOutPutFilePath = _T("");
		strOriFilePath = _T(""); 
		strFileName = _T(""); 
	}

	void SetNull()
	{
		nTotalPages = -1;
		nCurrentPage = -1;
		strOutPutFilePath = _T("");
		strOriFilePath = _T(""); 
		strFileName = _T(""); 
	}

}tPdfImageInfo;


//显示预览窗口
// szFile 预览文件路径， nTop 显示窗口顶点坐标
DLL_DECL BOOL APIShowPre( char* szFile, int nTop = 0  );

//关闭预览窗口
DLL_DECL BOOL APIClearPre();

DLL_DECL VOID APIPreInit( HWND hWnd );

DLL_DECL VOID APIPreQuit();

//返回pdf页数
DLL_DECL int APIGetGif( char* szFile );

#endif