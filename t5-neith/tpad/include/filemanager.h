/** @defgroup �ļ������߼���Ԫ 
 *  @version V1.1.4
 *  @author  ��ӨӨ
 *  @date    2016.7.10
 */
#pragma once

#define CONFIG_FILE			_T(".\\configure.ini")

#define CFG_NAME           _T("name")
#define CFG_PATH           _T("path")
#define CFG_USE            _T("use")

#define BTN_WIDTH           90

enum EmFileOptType{
	emFileOptTypeNon,
	emFileOptTypeCpy,
	emFileOptTypeCut,
	emFileOptTypeDel,
	emFileOptTypSearch,
};

//��¼���½��ļ��л���������
enum EmNameEdtType{
	emNameEdtNon,
	emNameEdtNewFolder,
	emNameEdtReName,
};
typedef struct tagPathDirItem
{
	CString strName;	            //��ʾ�ļ�������
	CString strFullPath;            //��Ӧ�ļ���ȫ·��
	int nItemLenth;

	tagPathDirItem()
	{
		SetNull();
	}

	void SetNull()
	{
		strName = _T("");
		strFullPath = _T("");
		nItemLenth = 0;
	}
}TPathDirItem;

class CFileManagerLogic : public CNotifyUIImpl, public Singleton<CFileManagerLogic>
{
public:
	CFileManagerLogic(void);
	~CFileManagerLogic(void);

    //�˳�
    bool OnBtnExit(TNotifyUI& msg);
protected:
	/** ���ڴ��� 
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
	bool OnCreate(TNotifyUI& msg);

	/** ��ʼ����Ϣ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnInit(TNotifyUI& msg);

	/** ����б���Ŀ��Ϣ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnFileItemClick(TNotifyUI& msg);

	/** ���ˢ�°�ť 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnSelAll(TNotifyUI& msg);
	
	/** ���� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);

	/** �ؼ�������
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnSearchEditChange(TNotifyUI& msg);
	void SearchItem(TCHAR * lpPath );
	char FirstDriveFromMask( ULONG unitmask );
	void RebuildUdiskList();
	//letterindex���
	bool OnLetterIndex(TNotifyUI& msg);
	//���Ŀ¼��ť
	bool OnBtnFilePath(TNotifyUI& msg);
	//�����Ŀͼ��
	bool OnFileItemPicClick(TNotifyUI& msg);
	bool IsImgFile( LPCTSTR szFile );
	//�ļ��������
	bool OnBtnNewFolder(TNotifyUI& msg);
	bool OnBtnManager(TNotifyUI& msg);
	bool OnBtnCopy(TNotifyUI& msg);
	bool OnBtnCut(TNotifyUI& msg);
	bool OnBtnDelete(TNotifyUI& msg);
	bool OnBtnRename(TNotifyUI& msg);
	bool OnBtnDone(TNotifyUI& msg);
	bool OnBtnPaste(TNotifyUI& msg);
	bool OnBtnCancel(TNotifyUI& msg);
	//�½��ļ���
	bool OnBtnSaveName(TNotifyUI& msg);
	bool OnBtnCancelMakeFolder(TNotifyUI& msg);
	//ɾ���ļ�
	bool OnBtnCancelDel(TNotifyUI& msg);
	bool OnBtnConfirmDel(TNotifyUI& msg);
	//���ѡ���ļ���
	bool OnCheckItemSel(TNotifyUI& msg);
	//�õ������ļ��п������ļ�Ԥ���ļ���
	void GetItemFromIni( TFileItem& tKeyItem, CString strKey );
	bool RecursiveDelete(CString strPath);
	BOOL32 SetFileAttributesEx( LPCWSTR lpFileName, DWORD dwFileAttributes );
	DWORD GetFileErr( LPCWSTR lpFileName );
	//��ȡ�����ļ��Ƿ���ʾ	
	bool IsShow( CString& strKey );

	/**  
	 *  @param[in] strDst Ŀ��Ŀ¼
	 *  @param[in] strSrc Դ��Ŀ¼
	 *  @param[in] uOprFunType  �������� FO_MOVE  FO_COPY FO_DELETE FO_RENAME
	 *  @writer    yujinjin
	 */
	bool FileOprate( CString& strDst, CString& strSrc, UINT uOprFunType );
    //�������ļ�
	bool MakeFileName( CString& strPath, bool bfolder );
	//����
	bool OnBtnBack(TNotifyUI& msg);

    bool OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle);
	
public:
		/** ��������ˢ���б�
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	void UpdateFileList();
	//ˢ���б�
	void UpdateShowFileList();
	//�����ļ������мĿ¼
	void UpdateNavigation(CString strFolderPath);
	//��ȡ�ļ����е��ļ�
	DWORD GetFolderFiles( CString strFolderPath, vector<TFileItem>& tListFileInfo );
	
	bool CBCopyFiles( CString &strCurPath );
	void CBCutFiles( CString& strCurPath );
	void CBDelFiles();
	//�̵߳�������
	bool CBSearch();

	vector<TFileItem> GetImgFileLst(){ return m_vctImgFileItem; };
	void PageChange(bool bIsPrePage);
	//�豸���	
	LRESULT OnDongleChange( WPARAM wParam, LPARAM lParam );
	//����ʱ��
	void UpdateShowTime();
	bool IsOperating(){return m_bIsOperating;};
	void SetOperating(bool bIsOperating){ m_bIsOperating = bIsOperating;};
	void UpdateAftOperat();
	APP_DECLARE_MSG_MAP()

public:

	vector <TPathDirItem> m_vctPathDirItem;  
	EmFileOptType m_emFileOptType;//��������

    bool m_bIsSearchTimer;//���������ʱһ��

private:

	vector<TFileItem>     m_vctFileItem;             //��ǰ�ļ����µ��ļ�
	vector<TFileItem>     m_vctSearchItem;           //���������ļ� 
	vector<TFileItem>     m_vctShowFileList;           //��ǰ��ʾ���ļ�
	vector<TFileItem>	  m_vctRootItem;   //��Ŀ¼���ļ���
	vector<TFileItem>     m_vctTransItem;   //ѡ�е��ļ�
	
	vector <TFileItem>	  m_vctImgFileItem;  //��ǰ�ļ��������е�ͼƬ�ļ�
	TFileItem      m_tCurtPreviewFile;//��ǰ��ʾ��ͼƬ
	static const String m_strFileListItem;
	static const String m_strFileName;
	static const String m_strSeachEdit;	     //������edit
	static const String m_strCheckBoxItemSel;//ѡ��ť
	
	DWORD m_dwRemDevice;
	
	bool m_bIsSelAll;  //�Ƿ�ȫѡ
	bool m_bSearchEdit;//�Ƿ�����
	bool m_bInRootDir;//�Ƿ��ڸ�Ŀ¼
	bool m_bIsManage;//�Ƿ����״̬

	DWORD m_dwTrimCount;  //��Ŀ¼�ʼ����

	CString m_strRootSelItemPath;  //��Ŀ¼ѡ�е���Ŀ��Ŀ¼
	CString m_strEditFileFolder;  //���б༭(����ճ������)���ļ���Ŀ¼

	EmNameEdtType m_emNameEdt;//��¼��ǰ���ֱ�������

	bool m_bPreview; //�Ƿ����Ԥ��
	bool m_bInRemoteDir; //�Ƿ�����ƶ��豸���ļ���
	bool m_bDeviceChange; //�Ƿ����豸���
	Window* m_pPrePage;
	Window* m_pNextPage;

	bool m_bIsOperating;//�Ƿ����ڲ���

};