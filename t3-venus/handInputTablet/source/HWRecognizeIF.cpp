// HWRecognizeIF.cpp: implementation of the CHWRecognizeIF class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h" 
#include "HWRecognizeIF.h"

#include "msinkaut.h"
#include "msinkaut_i.c"
 

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHWRecognizeIF::CHWRecognizeIF()
:m_pIInkCollector( NULL )
,m_pIInkDisp( NULL )
/*,m_pIInkRecoContext( NULL )*/
,m_hWnd(NULL)
,m_nRecResultSize(5)
{
   // CoInitialize(NULL);
    Clear();
}

CHWRecognizeIF::~CHWRecognizeIF()
{
   Clear();
  // CoUninitialize();
}

 

  //初始化手写环境 
VOID CHWRecognizeIF::Initialize(VOID)
{
    HRESULT hr = NULL;    
    
    // Create a recognition context that uses the default recognizer.
    // The single context will be used for all the recognition.
//     hr = CoCreateInstance(CLSID_InkRecognizerContext, 
//         NULL, CLSCTX_INPROC_SERVER,
//         IID_IInkRecognizerContext, 
//         (void **) &m_pIInkRecoContext);
//     if (FAILED(hr)) 
//     {
//         AfxMessageBox("尚未安装手写识别支持!");
//         return ;
//     }
    
    // Create the InkCollector object.
    hr = CoCreateInstance(CLSID_InkCollector, 
        NULL, CLSCTX_INPROC_SERVER, 
        IID_IInkCollector, 
        (void **) &m_pIInkCollector);
    if (FAILED(hr)) 
    {
        AfxMessageBox("创建手写识别失败!");
        return ;
    }
    
    // Get a pointer to the Ink object
    hr = m_pIInkCollector->get_Ink(&m_pIInkDisp);
    if (FAILED(hr)) 
    {
        AfxMessageBox("获取墨迹收集接口失败!");
        return ;
    }
    
    m_pIInkCollector->put_MousePointer(IMP_Arrow);
    IInkDrawingAttributes* pInkDrawAttrib = NULL;
    
    hr = m_pIInkCollector->get_DefaultDrawingAttributes( &pInkDrawAttrib );
    
    if (FAILED(hr)) 
    {
        return ;
    }
    
    if ( NULL != pInkDrawAttrib )
    {
        //设置笔迹颜色
        pInkDrawAttrib->put_Color( RGB( 0,0,255) ); 
        
        //设置笔迹大小
        pInkDrawAttrib->put_Width(  100 );
    }
    
    hr = m_pIInkCollector->putref_DefaultDrawingAttributes( pInkDrawAttrib );
    
    if (FAILED(hr)) 
    {
        return ;
    }

    
    return;
}

VOID CHWRecognizeIF::Clear()
{
//     if ( NULL != m_pIInkRecoContext)
//     {
//         m_pIInkRecoContext->Release();
//         m_pIInkRecoContext = NULL;
//     }
    
    if ( NULL != m_pIInkDisp )
    {
        m_pIInkDisp->Release();
        m_pIInkDisp = NULL;
    }
    
    if ( NULL != m_pIInkCollector )
    {
        m_pIInkCollector->Release();
        m_pIInkCollector = NULL;
    }
}


//hWnd, 输入窗口句柄，nEnable:VARIANT_TRUE ink墨迹输入启用控制 VARIANT_FALSE
VOID CHWRecognizeIF::SetHandWriteParm( HWND hWnd, short nEnable /* = VARIANT_TRUE  */)
{ 
	m_hWnd = hWnd;
   
	if ( NULL == m_pIInkCollector )
	{
		return ;
	}

	HRESULT hr = NULL;
    // Tell InkCollector the window to collect ink in
    hr = m_pIInkCollector->put_hWnd((long)m_hWnd);
    if (FAILED(hr)) 
    {
		AfxMessageBox("设置手写窗口失败!");
		return ;
	}

    // Enable ink input in the window
    hr = m_pIInkCollector->put_Enabled(VARIANT_TRUE);
   
    if (FAILED(hr)) 
    {   
        
        if ( hr == E_INK_WINDOW_NOT_SET )
        {
            TRACE("窗口启用手写失败 E_INK_WINDOW_NOT_SET!");
        }
        else if ( hr == E_INVALIDARG  )
        {
            TRACE("窗口启用手写失败 E_INVALIDARG!");
        }
        else if (  hr == E_POINTER )
        {
            TRACE("窗口启用手写失败 E_POINTER!");
        }
        else if (  hr == E_INK_OVERLAPPING_INPUT_RECT )
        {
            TRACE("窗口启用手写失败 E_INK_OVERLAPPING_INPUT_RECT!");
        }
        else if (  hr == E_INK_EXCEPTION )
        {
            TRACE("窗口启用手写失败 E_INK_EXCEPTION!");

        } 
        else if (  hr == E_INK_COLLECTOR_BUSY )
        {
            TRACE("窗口启用手写失败 E_INK_COLLECTOR_BUSY!");

        }
        else
        {
            TRACE("窗口启用手写失败 %d ",hr);

        }
 

		return ;
	}

    TRACE("窗口启用手写ok");
    		
}


VOID CHWRecognizeIF::ResetTablet()
{
	// Delete all strokes from the Ink
	if ( NULL != m_pIInkDisp )
	{
		m_pIInkDisp->DeleteStrokes(0);
	}
  
}

BOOL CHWRecognizeIF::Recognize( std::vector<CString>& vectResult )
{
	 
    IInkRecognizerContext* m_pIInkRecoContext = NULL ;  
	IInkRecognitionResult* pIInkRecoResult = NULL;


	// change cursor to the system's Hourglass
    HCURSOR hCursor = ::SetCursor(::LoadCursor(NULL, IDC_WAIT));
    // Get a pointer to the ink stroke collection
    // This collection is a snapshot of the entire ink object
    IInkStrokes* pIInkStrokes = NULL;
    HRESULT hr = m_pIInkDisp->get_Strokes(&pIInkStrokes);
    if (SUCCEEDED(hr)) 
    {   
        
        hr = CoCreateInstance(CLSID_InkRecognizerContext, 
            NULL, CLSCTX_INPROC_SERVER,
            IID_IInkRecognizerContext, 
            (void **) &m_pIInkRecoContext);
        if (FAILED(hr)) 
        {
            AfxOutputDebugString("尚未安装手写识别支持!");
            return FALSE;
        }  
 
        // Pass the stroke collection to the recognition context
        hr = m_pIInkRecoContext->putref_Strokes(pIInkStrokes);
  
      
        if (SUCCEEDED(hr)) 
        {
            // Recognize
            //IInkRecognitionResult* pIInkRecoResult = NULL;
            InkRecognitionStatus RecognitionStatus;
            hr = m_pIInkRecoContext->Recognize(&RecognitionStatus, &pIInkRecoResult);
 

            if (SUCCEEDED(hr) && (pIInkRecoResult!= NULL)) 
            {
				///////////////////////////////////gq///////////////////////////////////////							
				IInkRecognitionAlternates* spIInkRecoAlternates;
				HRESULT hr2 = pIInkRecoResult->AlternatesFromSelection(
					0,                              // in: selection start 
					-1,                             // in: selection length; -1 means "up to the last one"
					m_nRecResultSize, // in: the number of alternates we're interested in
					&spIInkRecoAlternates           // out: the receiving pointer
					);

				long lCount = 0;
				if (SUCCEEDED(hr2) && SUCCEEDED(spIInkRecoAlternates->get_Count(&lCount)))
				{
					// Get the alternate strings
					IInkRecognitionAlternate* pIInkRecoAlternate = NULL;
					for (LONG iItem = 0; (iItem < lCount) /*&& (iItem < m_nRecResultSize)*/; iItem++)
					{
						// Get the alternate string if there is one
						if (SUCCEEDED(spIInkRecoAlternates->Item(iItem, &pIInkRecoAlternate)))
						{
							BSTR bstr = NULL;
							if (SUCCEEDED(pIInkRecoAlternate->get_String(&bstr)))
							{				
								// Show the result string
								if (SUCCEEDED(hr2) && bstr)
								{
									//MessageBoxW(m_hWnd, bstr, L"Recognition Results", MB_OK);
									CString strResult = bstr;
									vectResult.push_back( strResult );
									SysFreeString(bstr);
								}
							}
							pIInkRecoAlternate->Release();
						}   
					}
				}
			  
                if ( spIInkRecoAlternates != NULL )
                {
                    pIInkRecoResult->Release();
                    pIInkRecoResult = NULL;

                    spIInkRecoAlternates->Release();
                    spIInkRecoAlternates = NULL;
                }
               

            }
            // Reset the recognition context
            m_pIInkRecoContext->putref_Strokes(NULL);
        }


        if ( m_pIInkRecoContext != NULL)
        {  
            // m_pIInkRecoContext->putref_Strokes(NULL);
            m_pIInkRecoContext->Release();
            m_pIInkRecoContext = NULL; 
            
            m_pIInkDisp->DeleteStrokes( pIInkStrokes ); 
            m_pIInkDisp->DeleteStrokes();
           
            
            if ( pIInkRecoResult != NULL )
            {
                pIInkRecoResult->Release();
                pIInkRecoResult = NULL;
            } 
            
        }
        
    }
    // restore the cursor
    ::SetCursor(hCursor);
    ResetTablet();
	return TRUE;

}


void  CHWRecognizeIF::SetRecResultCnt( UINT nCnt )
{
	if ( nCnt <= 0 || nCnt > 21 )
	{
		m_nRecResultSize = 12;
	}
	else
	{
		m_nRecResultSize = nCnt;	
	}
}