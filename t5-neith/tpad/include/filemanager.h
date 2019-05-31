/** @defgroup 文件管理逻辑单元 
 *  @version V1.1.4
 *  @author  邓莹莹
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

//记录是新建文件夹还是重命名
enum EmNameEdtType{
	emNameEdtNon,
	emNameEdtNewFolder,
	emNameEdtReName,
};
typedef struct tagPathDirItem
{
	CString strName;	            //显示文件夹名称
	CString strFullPath;            //对应文件夹全路径
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

    //退出
    bool OnBtnExit(TNotifyUI& msg);
protected:
	/** 窗口创建 
	*  @param[in] 消息
	*  @return 是否成功
	*/
	bool OnCreate(TNotifyUI& msg);

	/** 初始化消息 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnInit(TNotifyUI& msg);

	/** 点击列表条目消息 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnFileItemClick(TNotifyUI& msg);

	/** 点击刷新按钮 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnSelAll(TNotifyUI& msg);
	
	/** 断链 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);

	/** 关键字搜索
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnSearchEditChange(TNotifyUI& msg);
	void SearchItem(TCHAR * lpPath );
	char FirstDriveFromMask( ULONG unitmask );
	void RebuildUdiskList();
	//letterindex点击
	bool OnLetterIndex(TNotifyUI& msg);
	//点击目录按钮
	bool OnBtnFilePath(TNotifyUI& msg);
	//点击条目图标
	bool OnFileItemPicClick(TNotifyUI& msg);
	bool IsImgFile( LPCTSTR szFile );
	//文件管理操作
	bool OnBtnNewFolder(TNotifyUI& msg);
	bool OnBtnManager(TNotifyUI& msg);
	bool OnBtnCopy(TNotifyUI& msg);
	bool OnBtnCut(TNotifyUI& msg);
	bool OnBtnDelete(TNotifyUI& msg);
	bool OnBtnRename(TNotifyUI& msg);
	bool OnBtnDone(TNotifyUI& msg);
	bool OnBtnPaste(TNotifyUI& msg);
	bool OnBtnCancel(TNotifyUI& msg);
	//新建文件夹
	bool OnBtnSaveName(TNotifyUI& msg);
	bool OnBtnCancelMakeFolder(TNotifyUI& msg);
	//删除文件
	bool OnBtnCancelDel(TNotifyUI& msg);
	bool OnBtnConfirmDel(TNotifyUI& msg);
	//点击选中文件夹
	bool OnCheckItemSel(TNotifyUI& msg);
	//得到配置文件中开启的文件预览文件夹
	void GetItemFromIni( TFileItem& tKeyItem, CString strKey );
	bool RecursiveDelete(CString strPath);
	BOOL32 SetFileAttributesEx( LPCWSTR lpFileName, DWORD dwFileAttributes );
	DWORD GetFileErr( LPCWSTR lpFileName );
	//读取配置文件是否显示	
	bool IsShow( CString& strKey );

	/**  
	 *  @param[in] strDst 目的目录
	 *  @param[in] strSrc 源文目录
	 *  @param[in] uOprFunType  操作类型 FO_MOVE  FO_COPY FO_DELETE FO_RENAME
	 *  @writer    yujinjin
	 */
	bool FileOprate( CString& strDst, CString& strSrc, UINT uOprFunType );
    //重命名文件
	bool MakeFileName( CString& strPath, bool bfolder );
	//返回
	bool OnBtnBack(TNotifyUI& msg);

    bool OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle);
	
public:
		/** 更新数据刷新列表
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	void UpdateFileList();
	//刷新列表
	void UpdateShowFileList();
	//更新文件夹面包屑目录
	void UpdateNavigation(CString strFolderPath);
	//获取文件夹中的文件
	DWORD GetFolderFiles( CString strFolderPath, vector<TFileItem>& tListFileInfo );
	
	bool CBCopyFiles( CString &strCurPath );
	void CBCutFiles( CString& strCurPath );
	void CBDelFiles();
	//线程调用搜索
	bool CBSearch();

	vector<TFileItem> GetImgFileLst(){ return m_vctImgFileItem; };
	void PageChange(bool bIsPrePage);
	//设备插拔	
	LRESULT OnDongleChange( WPARAM wParam, LPARAM lParam );
	//更新时间
	void UpdateShowTime();
	bool IsOperating(){return m_bIsOperating;};
	void SetOperating(bool bIsOperating){ m_bIsOperating = bIsOperating;};
	void UpdateAftOperat();
	APP_DECLARE_MSG_MAP()

public:

	vector <TPathDirItem> m_vctPathDirItem;  
	EmFileOptType m_emFileOptType;//操作类型

    bool m_bIsSearchTimer;//点击搜索延时一秒

private:

	vector<TFileItem>     m_vctFileItem;             //当前文件夹下的文件
	vector<TFileItem>     m_vctSearchItem;           //搜索到的文件 
	vector<TFileItem>     m_vctShowFileList;           //当前显示的文件
	vector<TFileItem>	  m_vctRootItem;   //根目录的文件夹
	vector<TFileItem>     m_vctTransItem;   //选中的文件
	
	vector <TFileItem>	  m_vctImgFileItem;  //当前文件夹下所有的图片文件
	TFileItem      m_tCurtPreviewFile;//当前显示的图片
	static const String m_strFileListItem;
	static const String m_strFileName;
	static const String m_strSeachEdit;	     //搜索框edit
	static const String m_strCheckBoxItemSel;//选择按钮
	
	DWORD m_dwRemDevice;
	
	bool m_bIsSelAll;  //是否全选
	bool m_bSearchEdit;//是否搜索
	bool m_bInRootDir;//是否在根目录
	bool m_bIsManage;//是否管理状态

	DWORD m_dwTrimCount;  //根目录最开始层数

	CString m_strRootSelItemPath;  //根目录选中的条目的目录
	CString m_strEditFileFolder;  //进行编辑(复制粘贴操作)的文件夹目录

	EmNameEdtType m_emNameEdt;//记录当前名字保存类型

	bool m_bPreview; //是否进行预览
	bool m_bInRemoteDir; //是否进入移动设备的文件夹
	bool m_bDeviceChange; //是否有设备插拔
	Window* m_pPrePage;
	Window* m_pNextPage;

	bool m_bIsOperating;//是否正在操作

};