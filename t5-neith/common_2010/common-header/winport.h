// 本头文件中包含一些处理vista及64、32位兼容问题的常用函数

#pragma once

// 修改窗口消息过滤器，解决因UIPI导致进程间窗口消息无法传递的问题
// uMessageID 要修改的消息号
// bAllow	  TRUE = 不过滤，FALSE = 过滤
// ChageWindowMessageFilter 在Vista及之后的系统中存在
// 返回值	  TRUE = 设置成功，FALSE = 设置失败
// 修改窗口消息过滤器
static BOOL ChangeWindowMessageFilterPort(UINT uMessageID, BOOL bAllow)
{
	BOOL bResult = FALSE;
#if(WINVER < 0x0600)
	typedef BOOL(WINAPI *ChangeWindowMessageFilterFun)(UINT, DWORD);
	HMODULE hUserMod = NULL;
	hUserMod = LoadLibrary(_T("user32.dll"));
	if (NULL != hUserMod)
	{
		ChangeWindowMessageFilterFun pChangeWindowMessageFilter = (ChangeWindowMessageFilterFun)GetProcAddress(hUserMod, "ChangeWindowMessageFilter");
		if (NULL != pChangeWindowMessageFilter)
		{
			bResult = pChangeWindowMessageFilter(uMessageID, bAllow ? 1 : 2);//MSGFLT_ADD: 1, MSGFLT_REMOVE: 2
		}
		::FreeLibrary(hUserMod);
	}
#else
	bResult = ChangeWindowMessageFilter(uMessageID, bAllow ? MSGFLT_ADD, MSGFLT_REMOVE);
#endif
	return bResult;
}

