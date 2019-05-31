/**
 * @author shicheng
 */
var nCurConfID = 0;
$(document).ready(function(){
	showCurPage("conflist"); //设置默认显示界面
});

function showCurPage(pageid)
{
	$("#conflist").css("width", "0px");
	$("#confinfo").css("height", "0px");
	$("#confctl").css("width", "0px");

	switch(pageid){
		case "conflist":{
			$("#conflist").css("width", "100%");
			$("#conflist").css("height", "100%");
			break;
		}
		case "confinfo":{
			$("#confinfo").css("width", "100%");
			$("#confinfo").css("height", "100%");
			break;
		}
		case "confctrl":{
			$("#confctrl").css("width", "100%");
			$("#confctrl").css("height", "100%");
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

function setCurConfID(id)
{
	nCurConfID = id;
};

function getCurConfID()
{
	return nCurConfID;
};