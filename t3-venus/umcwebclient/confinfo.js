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

	$(".btnBack").click(function(){
		parent.showCurPage("conflist");
	});
	
	$(".btnConfctrl").click(function(){
		//parent.setCurConfID(parent.getCurConfID());
		parent.showCurPage("confctrl");
	});

	//轮询成员
	$(".btnPollingMember").click(function(){
		RefreshConftempPollingListReq(parent.getCurConfID());
	});
	
	//讨论成员
	$(".btnDiscussMember").click(function(){
		RefreshConftempDiscussListReq(parent.getCurConfID());
	});	
	
	//搜索
	$(".img_search").unbind("click").click(function(){
		RefreshConftempMeetNameListReq(parent.getCurConfID());
	});
});

function onShowWnd()
{
	RefreshConftempInfoReq(parent.getCurConfID());
};

/*********************消息处理****************************************************************************/

function sendNty(send_data)
{
    $.post(url,send_data,function(data,ts){
    	//返回通知消息
		switch( data.event ){
			case "ev_umcweb_RefreshConfinfoInfo_nty_res":{			//刷新会议管理  会议信息 通知型回应
				var bRet = RefreshConftempInfoRes(data);
				if( false == bRet ){
					parent.showCurPage("conflist");
				}
				break;
			}
			case "ev_umcweb_list_meetingroom_get_res":{				//刷新会议管理  会议信息 与会会场列表通知型回应
				RefreshConftempMeetNameListRes(data);
				break;
			}
			case "ev_umcweb_RefreshConfinfo_PollingList_nty_res":{	//刷新会议管理  会议信息 轮询列表 通知型回应
				RefreshConftempPollingListRes(data);
				break;
			}
			case "ev_umcweb_RefreshConfinfo_DiscussList_nty_res":{	//刷新会议管理  会议信息 讨论列表 通知型回应
				RefreshConftempDiscussListRes(data);
				break;
			}
			default:{
			    break;
			}
		}
    },'json');
};

//刷新会议管理信息   请求
function RefreshConftempInfoReq(curconfID)
{	
	send_data = "{\"event\":\"ev_umcweb_RefreshConfinfoInfo_nty_req\"" + "," + "\"wCurConfID\":" + "\"" + curconfID + "\"" + "}";
	sendNty(send_data);
	
	RefreshConftempMeetNameListReq(curconfID);
};

//会场列表获取  请求
function RefreshConftempMeetNameListReq(curconfID)
{
	var strSearch = $(".text_search").val();
	if( "搜索" == strSearch )
	{
		strSearch = "";
	}

	send_data = "{\"event\":\"ev_umcweb_list_meetingroom_get_req\"" + "," + "\"confid\":" + "\"" + curconfID + "\"" + "," + "\"search\":" + "\"" + strSearch + "\"" + "}";
	sendNty(send_data);
};

//刷新会议管理 轮询列表 请求
function RefreshConftempPollingListReq(curconfID)
{
	send_data = "{\"event\":\"ev_umcweb_RefreshConfinfo_PollingList_nty_req\"" + "," + "\"wCurConfID\":" + "\"" + curconfID + "\"" + "}";
	sendNty(send_data);	
};

//刷新会议管理 讨论列表 请求
function RefreshConftempDiscussListReq(curconfID)
{
	send_data = "{\"event\":\"ev_umcweb_RefreshConfinfo_DiscussList_nty_req\"" + "," + "\"wCurConfID\":" + "\"" + curconfID + "\"" + "}";
	sendNty(send_data);	
};