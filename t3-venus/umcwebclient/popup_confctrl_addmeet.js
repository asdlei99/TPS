/**
 * @author xuhuaxiu
 */
var send_data = "";
var strCurOperType = "";	//当前加入会场操作界面："confctrlpolling" ; "confctrldiscuss"
var scroll_popup_confctrl_addmeet_bechecked = null;
var scroll_popup_confctrl_addmeet_checked = null;
$(document).ready(function(){
	adaptPopupPosition(720, 540);
	strCurOperType = "";
	
	$(".img_search").unbind("click").click(function(){
		getMeetList();
	});
	
	$(".btn_close").unbind("click").click(function(){
		saveAddmeetList();
		OnPopupBtnCloseClick(this);
	});

	//添加滚动条
	scroll_popup_confctrl_addmeet_bechecked = new customBar(
		$(".div_list_meettingroom_bechecked .slider").get(0), 
		$(".div_list_meettingroom_bechecked .pannel").get(0), 
		$(".div_list_meettingroom_bechecked .drag").get(0) );
		
	scroll_popup_confctrl_addmeet_checked = new customBar(
		$(".div_list_meettingroom_checked .slider").get(0), 
		$(".div_list_meettingroom_checked .pannel").get(0), 
		$(".div_list_meettingroom_checked .drag").get(0) );

	//更新弹出框显示数据
	onShowWnd();
});

/*********************界面显示处理**************************************************************************/

//更新弹出框显示数据
function onShowWnd()
{
	//更新与会会场列表
	getMeetList();

	//更新 轮询、讨论 会场列表
	if( "0px" != top.frames["confmng"].frames["confctrl"].$("#confctrlpolling").css("width") )
	{
		strCurOperType = "confctrlpolling";

		clearListItem_MeettingroomChecked();
		//从轮询列表中取出数据
		var $domList = top.frames["confmng"].frames["confctrl"].frames["confctrlpolling"].$(".div_list");
		var $domItems = $domList.find(".div_list_item");
		for( var i = 0; i < $domItems.length; i++)
		{
			var domItem = $domItems[i];

			var strId = domItem.getAttribute("no");
			var strOnline = "在线";//$(domItem).children(".div_list_item_online").text();
			var strType = "";//$(domItem).children(".div_list_item_type").text();
			var strName = $(domItem).children(".div_list_item_name").text();
			var strNumber = $(domItem).children(".div_list_item_number").text();
			var strIp = $(domItem).children(".div_list_item_ip").text();

			addListItem_MeettingroomChecked(strId,strOnline,strType,strName,strNumber,strIp);
		}

		scroll_popup_confctrl_addmeet_checked.init();	
	}
	else if( "0px" != top.frames["confmng"].frames["confctrl"].$("#confctrldiscuss").css("width") )
	{
		strCurOperType = "confctrldiscuss";
		
		var curconfID = top.frames["confmng"].getCurConfID();
		send_data = "{\"event\":\"ev_umcweb_RefreshConfinfo_DiscussList_nty_req\"" + "," + "\"wCurConfID\":" + "\"" + curconfID + "\"" + "}";
		sendNty(send_data);
	}
	else
	{
		alert("error: can not find polling or discuss info");
	}
};

function saveAddmeetList()
{
	if( strCurOperType == "confctrlpolling" )
	{
		top.frames["confmng"].frames["confctrl"].frames["confctrlpolling"].clearItem();

		var $domItems = $(".div_list_meettingroom_checked .div_list_item");
		for( var i = 0; i < $domItems.length; i++ )
		{
			var domItem = $domItems[i];
			
			var strId = domItem.getAttribute("no");
			var strOnline = $(domItem).children(".div_list_item_online").text();
			var strType = $(domItem).children(".div_list_item_type").text();
			var strName = $(domItem).children(".div_list_item_name").text();
			var strNumber = $(domItem).children(".div_list_item_number").text();
			var strIp = $(domItem).children(".div_list_item_ip").text();
			
			top.frames["confmng"].frames["confctrl"].frames["confctrlpolling"].addPollingItem(
				i+1, strId, strName, strNumber, strIp );
		}
	}
	else if( strCurOperType == "confctrldiscuss" )
	{
		return;
	}
	else
	{
		alert("error: can not find polling or discuss info");
	}
};

function isDiscussState()
{
	var strTip = top.frames["confmng"].frames["confctrl"].frames["confctrldiscuss"].$(".btnStart").attr("value");
	if( "开启讨论" == strTip ){			//状态：讨论关闭
		return false;
	}else if( "关闭讨论" == strTip ){		//状态：讨论开启
		return true;
	}else{
		alert("error: can not get current discuss state")
	}
};

//操作会议讨论列表
//emOprType - 0: em_DisListOpr_Add; 1: em_DisListOpr_Del
//$domItems - 讨论开启时：添加or删除的会场成员；讨论关闭时：操作后讨论列表
function operDiscussMeet(emOprType, $domItems)
{
	var nItems = $domItems.length;
	if( 0 == emOprType && nItems > 27 ){
		top.showMessageBox("最多支持27个屏参与讨论");
		return false;
	}

	if( !isDiscussState() ){
		top.frames["confmng"].frames["confctrl"].frames["confctrldiscuss"].StartAuxMixReq( $domItems );
	}else{
		top.frames["confmng"].frames["confctrl"].frames["confctrldiscuss"].UpdateAudMixInfoReq( emOprType, $domItems );
	}
};

function onBtnAddMeetCheckAllClick()
{
	if( strCurOperType == "confctrldiscuss" ){
		operDiscussMeet( 0, $(".div_list_meettingroom_bechecked").find(".div_list_item") );
	}else{
		CheckAll("globlestate");
	}
	
	scroll_popup_confctrl_addmeet_checked.init();
};

function onBtnAddMeetCheckOneClick()
{
	if( strCurOperType == "confctrldiscuss" ){
		if( !isDiscussState() ){
			CheckOne("globlestate");
			operDiscussMeet( 0, $(".div_list_meettingroom_checked").find(".div_list_item") );
		}else{
			var $domItems = $(".div_list_meettingroom_bechecked").find(".div_list_item input:checked").parents(".div_list_item");
			operDiscussMeet( 0, $domItems );
		}
	}else{
		CheckOne("globlestate");
	}

	scroll_popup_confctrl_addmeet_checked.init();
};

function onBtnAddMeetUncheckOneClick()
{
	if( strCurOperType == "confctrldiscuss" ){
		if( !isDiscussState() ){
			UncheckOne("globlestate");
			operDiscussMeet( 1, $(".div_list_meettingroom_checked").find(".div_list_item") );
		}else{
			var $domItems = $(".div_list_meettingroom_bechecked").find(".div_list_item input:checked").parents(".div_list_item");
			operDiscussMeet( 1, $domItems );
		}
	}else{
		UncheckOne("globlestate");
	}

	scroll_popup_confctrl_addmeet_checked.init();
};

function onBtnAddMeetUncheckAllClick()
{
	if( strCurOperType == "confctrldiscuss" ){
		if( !isDiscussState() ){
			UncheckAll("globlestate");
			operDiscussMeet( 1, $(".div_list_meettingroom_checked").find(".div_list_item") );
		}else{
			var $domItems = $(".div_list_meettingroom_checked").find(".div_list_item").parents(".div_list_item");
			operDiscussMeet( 1, $domItems );
		}
	}else{
		UncheckAll("globlestate");
	}

	scroll_popup_confctrl_addmeet_checked.init();
};

/*********************消息处理****************************************************************************/

function sendNty(send_data)
{
    $.post(url,send_data,function(data,ts){
    	//返回通知消息
		switch( data.event ){
			case "ev_umcweb_list_meetingroom_get_res":{				//会场列表获取回应
				getMeetListRes(data);
				break;
			}
			case "ev_umcweb_RefreshConfinfo_DiscussList_nty_res":{	//刷新 会议管理-会议信息-讨论列表 通知型回应
				RefreshDiscussListInfoRes(data);
				break;
			}
			default:{
			    break;
			}
		}
    },'json');
};

//更新与会会场列表
function getMeetList()
{
	var curconfID = top.frames["confmng"].getCurConfID();
					
	var strSearch = $(".text_search").val();
	if(strSearch == "搜索")
	{
		strSearch = "";
	}
	
	send_data = "{\"event\":\"ev_umcweb_list_meetingroom_get_req\"" + "," + "\"confid\":" + "\"" + curconfID + "\""+ "," + "\"search\":" + "\"" + strSearch + "\"" + "}";
	sendNty(send_data);	
};

function getMeetListRes(data)
{
	clearListItem_MeettingroomBechecked();
	
	var arrItem = new Array();
				
	for (var i=0; i < data.count; i++) {
		arrItem.push(data.items[i]);
	};
	
	for (var i=0; i < arrItem.length; i++) {
		var strId = arrItem[i].epId;
		var strName = arrItem[i].achMeetName;
		var strNumber = arrItem[i].achE164;
		var strIp = arrItem[i].achMeetIp;
		
		var strOnline = "在线";
		if( arrItem[i].bOnline == "0" ){
			strOnline = "不在线";
		}
		
		var strType = "";

		addListItem_MeettingroomBechecked(strId,strOnline,strType,strName,strNumber,strIp);
	};
	
	scroll_popup_confctrl_addmeet_bechecked.init();	
};

//更新会议讨论列表信息回应
function RefreshDiscussListInfoRes(data)
{
	clearListItem_MeettingroomChecked();
	
	var arrItem = new Array();
	for (var i=0; i < data.count; i++) {
		arrItem.push(data.items[i]);
	};
	
	for (var i=0; i < arrItem.length; i++) {
		var strId = arrItem[i].epId;
		var strName = arrItem[i].achMeetName;
		var strNumber = arrItem[i].achE164;
		var strIp = arrItem[i].achMeetIp;
		
		var strOnline = "在线";
		if( arrItem[i].bOnline == "0" ){
			strOnline = "不在线";
		}	
		var strType = "";

		addListItem_MeettingroomChecked(strId,strOnline,strType,strName,strNumber,strIp);
	};
	
	scroll_popup_confctrl_addmeet_checked.init();		
};