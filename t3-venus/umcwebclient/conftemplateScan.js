/**
 * @author xuhuaxiu
 */
var send_data = "";
var scroll_ConfInfo = null;
var scroll_Scanf_MeetList = null;
$(document).ready(function(){
	//添加滚动条
	scroll_ConfInfo = new customBar($(".div_conftemplateScan_confInfo").get(0), $(".div_conftemplateScan_pannel").get(0), $(".div_conftemplateScan_drag").get(0));
	scroll_Scanf_MeetList = new customBar($(".div_list_content").get(0), $(".pannel_Scanf_Meet_list").get(0), $(".drag_Scanf_Meet_list").get(0));

	//召开
	$(".btnStartConf").click(function(){
		top.showConfirmBox("请问你确定召开当前会议模板吗？");
	});
	
	//修改
	$(".btnModify").click(function(){
		parent.showCurPage("conftemplateEdit");
	});
	
	//返回
	$(".btnBack").click(function(){
		parent.showCurPage("conftemplateList");
	});
	
	//轮询成员
	$(".btnPollingMember").click(function(){
		RefreshConftempPollingListReq( parent.getCurConfTempID() );
	});
	
	//讨论成员
	$(".btnDiscussMember").click(function(){
		RefreshConftempDiscussListReq( parent.getCurConfTempID() );
	});
	
	//搜索
	$(".img_search").unbind("click").click(function(){
		RefreshConftempMeetNameListReq( parent.getCurConfTempID() );
	});
});

function onShowWnd(strConfName)
{
	RefreshConftempInfoReq( parent.getCurConfTempID() );
};

/*********************消息处理****************************************************************************/

function sendNty(send_data)
{
    $.post(url,send_data,function(data,ts){
    	//返回通知消息
		switch( data.event ){
			case "ev_umcweb_RefreshConftempInfo_nty_res":{			//刷新会议模板具体信息通知型回应
				var bRet = RefreshConftempInfoRes(data);
				if( false == bRet ){
					parent.showCurPage("conftemplateList");
				}
				break;
			}
			case "ev_umcweb_RefreshConftemp_MeetNameList_nty_res":{	//刷新会议模板 与会会场列表通知型回应
				RefreshConftempMeetNameListRes(data);
				break;
			}
			case "ev_umcweb_RefreshConftemp_PollingList_nty_res":{	//刷新会议模板 轮询列表 通知型回应
				RefreshConftempPollingListRes(data);
				break;
			}
			case "ev_umcweb_RefreshConftemp_DiscussList_nty_res":{	//刷新会议模板 讨论列表 通知型回应
				RefreshConftempDiscussListRes(data);
				break;
			}
			default:{
			    break;
			}
		}
    },'json');
};

//刷新会议模板信息   请求
function RefreshConftempInfoReq(strConfTempID)
{	
	send_data = "{\"event\":\"ev_umcweb_RefreshConftempInfo_nty_req\"" + "," + "\"wConfTempID\":" + "\"" + strConfTempID + "\"" + "}";
	sendNty(send_data);
	
	RefreshConftempMeetNameListReq(strConfTempID);
};

//刷新会议模板与会会场列表通知型  请求
function RefreshConftempMeetNameListReq(strConfTempID)
{
	var strSearch = $(".text_search").val();
	if( "搜索" == strSearch )
	{
		strSearch = "";
	}

	send_data = "{\"event\":\"ev_umcweb_RefreshConftemp_MeetNameList_nty_req\"" + "," + "\"wConfTempID\":" + "\"" + strConfTempID + "\"" + "," + "\"strSearch\":" + "\"" + strSearch + "\"" + "}";
	sendNty(send_data);
};

//刷新会议模板 轮询列表 请求
function RefreshConftempPollingListReq(strConfTempID)
{
	send_data = "{\"event\":\"ev_umcweb_RefreshConftemp_PollingList_nty_req\"" + "," + "\"wConfTempID\":" + "\"" + strConfTempID + "\"" + "}";
	sendNty(send_data);	
};

//刷新会议模板 讨论列表 请求
function RefreshConftempDiscussListReq(strConfTempID)
{
	send_data = "{\"event\":\"ev_umcweb_RefreshConftemp_DiscussList_nty_req\"" + "," + "\"wConfTempID\":" + "\"" + strConfTempID + "\"" + "}";
	sendNty(send_data);	
};

//点击"召开"会议模板响应函数
function startConftemplate()
{
	updStartconfBtnState(false);

	var strConfTempID = getCurConfTempID();
	send_data="{\"event\":\"ev_umcweb_StartConfTemplate_req\"" + "," + "\"wConfTempID\":" + "\"" + strConfTempID + "\"" + "}";
	parent.frames["conftemplateList"].sendNty(send_data);
};

function updStartconfBtnState(bAble)
{
	if( true == bAble ){
		$(".btnStartConf").removeAttr("disabled");
	}else{
		$(".btnStartConf").attr("disabled","disabled");
	}
};