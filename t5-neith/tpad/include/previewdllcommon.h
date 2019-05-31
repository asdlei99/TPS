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


//��ʾԤ������
// szFile Ԥ���ļ�·���� nTop ��ʾ���ڶ�������
DLL_DECL BOOL APIShowPre( char* szFile, int nTop = 0  );

//�ر�Ԥ������
DLL_DECL BOOL APIClearPre();

DLL_DECL VOID APIPreInit( HWND hWnd );

DLL_DECL VOID APIPreQuit();

//����pdfҳ��
DLL_DECL int APIGetGif( char* szFile );

#endif