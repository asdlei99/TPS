/**
 * @author xuhuaxiu
 */
var nCurConfTempID = "-1";	//-1->模板列表界面； 0->新建模板；1~128->浏览/编辑模板
function showCurPage(pageid)
{
	$("#conftemplateList").css("width", "0px");
	$("#conftemplateList").css("height", "0px");
	$("#conftemplateScan").css("width", "0px");
	$("#conftemplateScan").css("height", "0px");
	$("#conftemplateEdit").css("width", "0px");
	$("#conftemplateEdit").css("height", "0px");
	
	switch(pageid){
		case "conftemplateList":{
			setCurConfTempID( "-1" );
			
			$("#conftemplateList").css("width", "100%");
			$("#conftemplateList").css("height", "100%");
			break;
		}
		case "conftemplateScan":{
			$("#conftemplateScan").css("width", "100%");
			$("#conftemplateScan").css("height", "100%");
			break;
		}
		case "conftemplateEdit":{
			$("#conftemplateEdit").css("width", "100%");
			$("#conftemplateEdit").css("height", "100%");
			break;
		}
		default:{
			break;
		}
	}
	
	if(window.frames[pageid].document.readyState == "complete")
	{
		window.frames[pageid].onShowWnd();
	}
};

function onShowWnd()
{
	showCurPage("conftemplateList");
};

function setCurConfTempID(id)
{
	nCurConfTempID = id;
};

function getCurConfTempID()
{
	return nCurConfTempID;
};