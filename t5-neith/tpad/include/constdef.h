/** @defgroup tpad常量定义 
 *  @version V1.1.5
 *  @author  肖楚然
 *  @date    2016.5.19
 */
#pragma once

#if !defined(_CONSTDEF_H_)
#define _CONSTDEF_H_


#ifndef String 
typedef tstring String;	                            // String
#endif
#ifndef MbString                                    // MultiByteString 
typedef std::string MbString;
#endif

#define NOTIFY_MSG	ITPadCommonOp::NotifyMsg

#define WINDOW_MGR_PTR  IWindowManager::GetSingletonPtr()


#define REG_TPAD_MSG_OB(ob) ITPadMsgManager::GetSingletonPtr()->AddObserver(ob);
#define UNREG_TPAD_MSG_OB(ob) ITPadMsgManager::GetSingletonPtr()->RemoveObserver(ob);
#define REG_TPAD_MSG_WND_OB(hwnd) ITPadMsgManager::GetSingletonPtr()->AddWindowObserver(hwnd);
#define UNREG_TPAD_MSG_WND_OB(hwnd) ITPadMsgManager::GetSingletonPtr()->RemoveWindowObserver(hwnd);



#endif
