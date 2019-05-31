// HWRecognizeIF.h: interface for the CHWRecognizeIF class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HWRECOGNIZEIF_H__885453D1_D4D5_40E4_8F82_F52860D95B05__INCLUDED_)
#define AFX_HWRECOGNIZEIF_H__885453D1_D4D5_40E4_8F82_F52860D95B05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#include <vector>



class IInkCollector;
class IInkDisp;
class IInkRecognizerContext;


class CHWRecognizeIF  
{
public:
	CHWRecognizeIF();
	virtual ~CHWRecognizeIF();
    
    void Initialize();   //初始化手写环境
    void Clear();        //清空手写环境 

    //hWnd, 输入窗口句柄，nEnable:VARIANT_TRUE ink墨迹输入启用控制 VARIANT_FALSE
    VOID  SetHandWriteParm( HWND hWnd, short nEnable  = VARIANT_TRUE  ); 
    BOOL  Recognize( std::vector<CString>& vectResult );
    void  SetRecResultCnt( UINT nCnt );

 
    VOID  ResetTablet();
private:
    IInkCollector*         m_pIInkCollector;         //墨迹收集,  收集后存放到IInkDisp 
    /*
        Remarks
        This object can be instantiated by calling the CoCreateInstance method in C++.

        The InkCollector object collects only ink and gestures that are input into 
        the specific window with which it is associated. 
        The sole purpose of the InkCollector is to collect ink from the hardware 
        (for example, through an IInkCursor and IInkTablet object) and deliver it to an application. 
        It essentially acts as the source that distributes ink into one or many different InkDisp objects, 
        which act as container that hold the distributed ink.

        To use an InkCollector, you create it, tell it on which window to collect drawn ink, and enable it. 
        After it is enabled, it can be set to collect in only one of three modes 
        (the mode is specified in the InkCollectionMode enumeration):

        InkOnly, in which an IInkStrokeDisp object is created. 
        GestureOnly, in which an IInkGesture object is created. 
        InkAndGesture, in which a stroke, a gesture, or potentially both are created, 
        depending on how the application handles events. 
        This means that, for every movement of a cursor that is within range of a tablet,
        the InkCollector always collects either a stroke or a gesture and sometimes both. 
        Gesture support is built in using the Microsoft gesture recognizer.

        An InkCollector handles all tablet input. Ink can be collected from all attached 
        tablets (including the mouse) simultaneously. Changes in the IInkCursor and 
        IInkCursorButton objects can cause InkCollector object to fire an event.

        An InkCollector also manages the list of cursors that it encounters during its existence. 
        When the InkCollector encounters a new cursor, the CursorInRange event fires with 
        the newCursor parameter set to VARIANT_TRUE. Applications use the InkCollector to manage new cursors.

        More than one InkCollector can be associated with a particular window handle, even if their collection areas, 
        set in the constructor or with the SetWindowInputRectangle method, overlap. However, 
        the only way this scenario works is if each InkCollector calls SetSingleTabletIntegratedMode
        and uses a unique tablet. This behavior makes it easy to store ink in a separate object for each tablet.

        An error occurs if the window input rectangle of one enabled InkCollectors 
        (set with the Enabled property) overlaps the window input rectangle of another enabled InkCollector.

        Note  Overlap can occur without an error as long as only one of the input rectangles is enabled at any known time.

        The MouseDown, MouseMove, MouseUp, and MouseWheel events return x and y-coordinates in pixels, 
        and not the HIMETRIC units that are associated with the ink space. This is because these events 
        replace the mouse events of pen-unaware applications and these applications understand only pixels.

        Note  The InkCollector object cannot be safely released on a non-UI thread.

        To improve your application's performance, dispose of your InkCollector object when it is no longer needed.  
    */

    IInkDisp*              m_pIInkDisp;              //墨迹存放 
    /*
        Note  The first instantiation of this object causes GDI+ to be instantiated as well.
        A side-effect is that if you are using a single ink object in a loop and create and 
        destroy it within the loop, you will cause GDI+ to be instantiated over and over. 
        This can cause a performance degradation in your application. To prevent this,
        keep a single instance of an ink object at all times while your application is using ink.

        An InkDisp object is a container of stroke (point) data. The stroke data, or the points 
        collected by the pen, are put into an InkDisp object. The Strokes property contains 
        the data for all strokes within the InkDisp object.

        The InkCollector object, InkOverlay object, and InkPicture control collects points 
        from the input device and puts them into an InkDisp object. These objects essentially act
        as the source that distributes ink into one or many different InkDisp objects, which act as containers that hold the distributed ink.

        The ink space is a virtual coordinate space to which the coordinates of the tablet 
        context are mapped. This space is fixed to a HIMETRIC coordinate system. In ink space coordinates, 
        a move from 0 to 1 equals 1 HIMETRIC unit. This mapping makes it easy to relate multiple InkDisp objects.

        The InkRenderer object manages the mappings between ink and the display window. 

    */

    //IInkRecognizerContext* m_pIInkRecoContext;       //通过从IInkDisp中获取到的墨迹来进行识别
    /*
        Remarks
        This object can be instantiated by calling the CoCreateInstance method in C++.

        There are two types of recognition: background (asynchronous) or foreground (synchronous). 
        Background recognition is started by a call to the BackgroundRecognize or BackgroundRecognizeWithAlternates methods, 
        occurs on a background thread, and reports results to the application through an event mechanism. 
        Foreground recognition does not return until all recognition is completed, thus making recognition 
        results available to the calling thread without listening for the recognition event.

        Ink is processed continuously in the background. If an IInkStrokeDisp is added to the InkStrokes 
        collection to which the InkRecognizerContext refers, then the IInkStrokeDisp is then recognized immediately. 
        See remarks in the EndInkInput method topic for more details.

        All recognition occurs through a recognizer context. The context defines the settings for a single recognition session. 
        It receives the ink that must be recognized and defines the constraints on the ink input and on the recognition output. 
        The constraints that can be set on the context include the language, the dictionary, and grammar that is being used.

        Note  Setting properties other than the Strokes or CharacterAutoCompletion properties succeeds only if the InkStrokes collection is NULL. 
        You must set the other properties before you attach the InkStrokes collection to the InkRecognizerContext, 
        or you must set the InkStrokes collection to NULL and then set the other properties. 
        If you set the InkStrokes collection to NULL and then set the other properties, you may have to reattach the InkStrokes collection. 
        This is because the recognition starts right after you assign the InkStrokes to the InkRecognizerContext.
        When a call is made to Recognize Method [InkRecognizeContext Class] or BackgroundRecognize, call results might be available already.

        To improve your application's performance, dispose of your InkRecognizerContext object when it is no longer needed.  
    */


    HWND                   m_hWnd;                   //手写窗口句柄
	int                    m_nRecResultSize;         //识别结果数量
};

#endif // !defined(AFX_HWRECOGNIZEIF_H__885453D1_D4D5_40E4_8F82_F52860D95B05__INCLUDED_)
