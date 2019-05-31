/** @defgroup cnc�������� 
 *  @version V1.1.4
 *  @author  Ф��Ȼ
 *  @date    2014.8.5
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

#define NOTIFY_MSG	ICncCommonOp::NotifyMsg

#define WINDOW_MGR_PTR  IWindowManager::GetSingletonPtr()


#define REG_CNC_MSG_OB(ob) ICncMsgManager::GetSingletonPtr()->AddObserver(ob);
#define UNREG_CNC_MSG_OB(ob) ICncMsgManager::GetSingletonPtr()->RemoveObserver(ob);
#define REG_CNC_MSG_WND_OB(hwnd) ICncMsgManager::GetSingletonPtr()->AddWindowObserver(hwnd);
#define UNREG_CNC_MSG_WND_OB(hwnd) ICncMsgManager::GetSingletonPtr()->RemoveWindowObserver(hwnd);


#define DEFAULT_TITLE_HEIGHT   79

#define  CNSCONF_FILE_PATH		_T("/usr/conf/")				//̨����λ��
#define CFG_FILE    _T("configure.ini")							//tpad�����ļ�
#define CFG_PATH    _T("path")									//tpad�����ļ�

#define TP_TEMPFILE_PATH       _T("temp/")

#define  MAX_SEAT_COUNT      3                                //�᳡�������

#endif
