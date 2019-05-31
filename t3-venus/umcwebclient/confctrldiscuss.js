/**
 * @author xuhuaxiu
 */
var send_data = "";
var scroll = null;

$(document).ready(function(){

	$(".aBack").unbind("click").click(function(){
		parent.showCurPage("confoper");
	});
	
	$(".btnStart").unbind("click").click(function(){
		var strTip = $(this).attr("value");
		if( "开启讨论" == strTip ){
			$(this).attr("value", "关闭讨论");
		}else{
			$(this).attr("value", "开启讨论");
		}
		StartAuxMixReq( $(".div_list").find(".div_list_item") );
	});
	
	$("#switchAMixVac").unbind("click").click(function(){
		AuxMixVacSwitchReq();
	});
	
	//讨论列表操作
	$(".aDiscussSetSpeaker").unbind("click").click(function(){
		if( "false" == $(this).attr("unable") ){
			ApplySpeakerReq();
		}else{
			return false;
		}
	});

	$(".aDiscussAdd").attr("unable", false);
	$(".aDiscussAdd").unbind("click").click(function(){
		if( "false" == $(this).attr("unable") ){
			showPopup("popup_confctrl_addmeet.html");
		}else{
			return false;
		}
	});
	
	$(".aDiscussRemove").unbind("click").click(function(){
		if( "false" == $(this).attr("unable") ){
			removeDiscussMeet();
		}else{
			return false;
		}
	});
	
	//添加滚动条
	scroll = new customBar($(".slider").get(0), $(".pannel").get(0), $(".drag").get(0));
	clearItem();
});

/*********************界面显示处理**************************************************************************/

function onShowWnd()
{
	RefreshConfinfoDiscussListReq( parent.parent.getCurConfID() );
};

function clearItem()
{
	$(".div_list_item").remove(); 
	scroll.init();
	clearListItemSelState();
};

function updItem(arrDiscuss, wSpeakerIndex)
{
	clearItem();

	for (var i=0; i < arrDiscuss.length; i++) {	
		if ( "" == arrDiscuss[i].epId ){
			continue;
		}
		
		if( "" == arrDiscuss[i].achMeetName && "" == arrDiscuss[i].achE164 && "" == arrDiscuss[i].achMeetIp ){
			continue;
		}
		
		var divListItem = document.createElement("div");
		divListItem.className="div_list_item";
		divListItem.setAttribute("onclick","onDiscussItemClick(this)");
		divListItem.setAttribute("onmouseenter","onItemMouseenter(this)");
		divListItem.setAttribute("onmouseleave","onItemMouseleave(this)");

		var checkboxItemNo = document.createElement("input");
		checkboxItemNo.type="checkbox";
		checkboxItemNo.setAttribute("onclick","onDiscussItemCheckboxClick(this)");
		
		//var divListItemNo = document.createElement("div");
		//divListItemNo.className="div_list_item_no";

		var divListItemImg = document.createElement("div");
		divListItemImg.className="div_list_item_img";
		
		var divListItemName = document.createElement("div");
		divListItemName.className="div_list_item_name";
		
		var divListItemNum = document.createElement("div");
		divListItemNum.className="div_list_item_number";
		
		var divListItemIp = document.createElement("div");
		divListItemIp.className="div_list_item_ip";

		divListItem.appendChild(checkboxItemNo);
		divListItem.appendChild(divListItemImg);
		
		//发言人会场
		if( wSpeakerIndex == arrDiscuss[i].epId ){
			var spanSetSpeaker = document.createElement("span");
			spanSetSpeaker.className="spanSpeaker";
			divListItemName.appendChild(spanSetSpeaker);
			spanSetSpeaker.text("（发言人）");
		}

		divListItem.appendChild(divListItemName);
		divListItem.appendChild(divListItemNum);
		divListItem.appendChild(divListItemIp);
		
		var divListContent = $(".div_list .slider").get(0);
		divListContent.appendChild(divListItem);

		//$(divListItemNo).text(i+1);
		$(divListItemName).text(arrDiscuss[i].achMeetName);
		$(divListItemNum).text(arrDiscuss[i].achE164);
		$(divListItemIp).text(arrDiscuss[i].achMeetIp);
		
		divListItem.setAttribute("no", arrDiscuss[i].epId);
	};
	
	clearListItemSelState();
	//添加滚动条
	scroll.init();
};

function onDiscussListHeadCheckboxClick(obj)
{
	onListHeadCheckboxClick(obj);
	ctrlButtonState();
};

function onDiscussItemClick(obj)
{
	onItemClick(obj);
	ctrlButtonState();
};

function onDiscussItemCheckboxClick(obj)
{
	onItemCheckboxClick(obj);
	ctrlButtonState();
};

function onDiscussItemMouseleave(obj)
{
	onItemMouseleave(obj);
	$(obj).find( $(".spanSpeaker") ).css("color", "#64AAD7");
}

function clearListItemSelState()
{	
	$(".div_list input").each(function(index,element){
		this.checked = false;
	});
	
	ctrlButtonState();
};

function ctrlButtonState()
{
	var nChecked = $(".div_list .wraper input:checked").length;
	if( 0 == nChecked ){
		$(".aDiscussSetSpeaker").attr("unable", true);
		$(".aDiscussRemove").attr("unable", true);
	}else{
		$(".aDiscussRemove").attr("unable", false);

		var strTip = $(".btnStart").attr("value");
		if( "关闭讨论" == strTip ){		//状态：讨论开启
			if( 1 == nChecked ){
				var $domItems = getCheckedItems( $(".div_list")[0] );
				if( $( $domItems[0] ).find(".spanSpeaker").length > 0 ){
					$(".aDiscussSetSpeaker").attr("unable", true);
				}else{
					$(".aDiscussSetSpeaker").attr("unable", false);
				}	
			}else{
				$(".aDiscussSetSpeaker").attr("unable", true);
			}
		}else{							//状态：讨论关闭
			$(".aDiscussSetSpeaker").attr("unable", true);
		}
	}
	
	setOperButtonColor();
};

//查找发言人会场ID
function findSpeakerID()
{
	var $domItems = $(".div_list").find(".div_list_item");
	var nItems = $domItems.length;
	
	var wSpeakerID = -1;
	for( var i = 0; i < nItems; i++ )
	{
		var domItem = $domItems[i];
		if( $(domItem).find(".spanSpeaker").length > 0 )
		{		
			wSpeakerID = domItem.getAttribute("no");
			break;
		}
	}
	
	return wSpeakerID;
};

function removeDiscussMeet()
{
	var strTip = (".btnStart").attr("value");
	if( "开启讨论" == strTip ){	//状态：讨论关闭
		var arrRestItems = getRestItems( $(".div_list")[0] );
		var wSpeakerID = findSpeakerID();
		updItem( arrRestItems, wSpeakerID );
		StartAuxMixReq( $(".div_list").find(".div_list_item") );
	}else{						//状态：讨论开启
		var $items = getCheckedItems(parent.$(".div_list")[0]);
		UpdateAudMixInfoReq( 1, $items );
	}
};

/*********************消息处理****************************************************************************/

function sendNty(send_data)
{
	$.post(url,send_data,function(data,ts){
		//返回通知消息
		switch( data.event ){
			case "ev_umcweb_RefreshConfinfo_DiscussList_nty_res":{	//刷新会议管理  会议轮询 通知型回应
				RefreshConfinfoDiscussListRes(data);
				break;
			}
			case "ev_umcweb_AuxMixVacSwitch_res":{			//语音激励开启和关闭 回应
				AuxMixVacSwitchRes(data);
				break;
			}
			case "ev_umcweb_epoper_applyspeaker_res":{		//指定发言人 回应
				ApplySpeakerRes(data);
				break;
			}
			default:{
				break;
			}
		}
	},'json');
};

//刷新会议管理 轮询列表 请求
function RefreshConfinfoDiscussListReq(curconfID)
{
	send_data = "{\"event\":\"ev_umcweb_RefreshConfinfo_DiscussList_nty_req\"" + "," + "\"wCurConfID\":" + "\"" + curconfID + "\"" + "}";
	sendNty(send_data);	
};

function RefreshConfinfoDiscussListRes(data)
{
	if( "0" == data.bDiscussOn ){
		$(".btnStart").attr("value", "开启讨论");
	}else{
		$(".btnStart").attr("value", "关闭讨论");
	}
	
	if( "0" == data.bVacOn ){
		$("#switchAMixVac").removeClass("switchbtnOpen").addClass("switchbtnOff");
	}else{
		$("#switchAMixVac").removeClass("switchbtnOff").addClass("switchbtnOpen");
	}			
	
	var arrDiscussList = new Array();
	for ( var i = 0; i < data.count; i++ ) {
		arrDiscussList.push(data.items[i]);
	};
	updItem(arrDiscussList, data.wSpeakerIndex);
	
	//当前操作为：已点击加入，使用弹出框来操作讨论会场
	if( "720px" == top.$(".div_popup").css("width") ){
		top.frames["popup"].RefreshDiscussListInfoRes(data);
	}
};

//开启和关闭讨论，开启和关闭语音激励， 或者非讨论下，更新讨论成员 请求
//$domItems - 会议讨论成员
function StartAuxMixReq($domItems)
{
	var strIsStart = "0";
	if( "关闭讨论" == $(".btnStart").attr("value") ){
		strIsStart = "1";
	}
	
	var strIsVacOn = "1";
	if( $("#switchAMixVac").attr("class") == "switchbtnOff" ){
		strIsVacOn = "0";
	}
	
	var wSpeakerID = findSpeakerID();
	
	var arrMeetList = "\"\"";
	var nItems = $domItems.length;
	if( nItems > 0 ){
		arrMeetList = "[";
		for( var i = 0; i < nItems; i++ ){
			var strId = this.getAttribute("no");
			var strMeetName = $(this).children(".div_list_item_name").val();
			var strMeetNum = $(this).children(".div_list_item_number").val();
			var strMeetIp = $(this).children(".div_list_item_ip").val();
			
			var itemMeet = "{\"epId\":" + "\"" + strId + "\"" + "," + 
						    "\"achMeetName\":" + "\"" + strMeetName + "\"" + "," + 
						    "\"achE164\":" + "\"" + strMeetNum + "\"" + "," + 
							"\"achMeetIp\":" + "\"" + strMeetIp + "\"" +"}" + ",";
			arrMeetList += itemMeet;
		}
		arrMeetList = arrMeetList.substring(0, arrMeetList.length - 1);
		arrMeetList += "]";	
	}
	arrMeetList += "," + "\"wDiscussCount\":" + "\"" + nMeetCount + "\"";

	send_data = "{\"event\":\"ev_umcweb_StartAuxMix_req\"" + "," 
				+ "\"wCurConfID\":" + "\"" + parent.parent.getCurConfID() + "\"" + "," 
				+ "\"bStart\":" + "\"" + strIsStart + "\"" + ","
				+ "\"bVacOn\":" + "\"" + strIsVacOn + "\"" + "," 
				+ "\"wSpeakerIndex\":" + "\"" + wSpeakerID + "\"" + "," 
				+ "\"arrDiscuss\":" + "\"" + arrDiscuss + "\"" + "}";
	sendNty(send_data);	
};

//语音激励开启和关闭 请求
function AuxMixVacSwitchReq()
{
	var strIsVacOn = "0";
	if( $("#switchAMixVac").attr("class") == "switchbtnOff" )
	{
		strIsVacOn = "1";
	}
	
	send_data = "{\"event\":\"ev_umcweb_AuxMixVacSwitch_req\"" + "," 
				+ "\"wCurConfID\":" + "\"" + parent.parent.getCurConfID() + "\"" + "," 
				+ "\"bVacOn\":" + "\"" + strIsVacOn + "\"" + "}";
	sendNty(send_data);	
};

function AuxMixVacSwitchRes(data)
{
	//0: TP_RET_OK; 0xFFFF: TP_RET_ERROR
	if( data.wOprRet != "0"){
		alert("语音激励请求失败！");
	}
	
	if( "0" == data.bVacOn ){
		$("#switchAMixVac").removeClass("switchbtnOpen").addClass("switchbtnOff");
	}else{
		$("#switchAMixVac").removeClass("switchbtnOff").addClass("switchbtnOpen");
	}
};

//指定发言人 请求
function ApplySpeakerReq()
{
	var $items = getCheckedItems(parent.$(".div_list")[0]);
	var epid = $items[0].getAttribute("no");

	send_data = "{\"event\":\"ev_umcweb_epoper_applyspeaker_req\"" + "," 
				+ "\"confid\":" + "\"" + parent.parent.getCurConfID() + "\"" + "," 
				+ "\"epid\":" + "\"" + epid + "\"" + "}";
	sendNty(send_data);	
};

function ApplySpeakerRes(data)
{
	switch( data.emRet ){
		case "0":{		//TP_ApplySpeaker_Success
			RefreshConfinfoDiscussListReq( parent.parent.getCurConfID() );
			break;
		}
		case "1":{		//TP_ApplySpeaker_ConfUnExist
			alert("指定发言人失败：会议不存在");
			break;
		}
		case "2":{		//TP_ApplySpeaker_EpIDError
			alert("指定发言人失败：会场不存在");
			break;
		}
		case "3":{		//TP_ApplySpeaker_EpStateError
			alert("指定发言人失败：会场未在线或通道未建立");
			break;
		}
		default:{
			break;
		}
	}
};

//添加和删除讨论成员（讨论下用） 请求
//emOprType - 0: em_DisListOpr_Add; 1: em_DisListOpr_Del
//$domItems - 添加or删除的会场成员
function UpdateAudMixInfoReq(emOprType, $domItems)
{
	var arrMeetList = "\"\"";
	var nItems = $domItems.length;
	if( nItems > 0 ){
		arrMeetList = "[";
		for( var i = 0; i < nItems; i++ ){
			var wEpID = $domItems[i].getAttribute("no");
			
			var itemMeet = "{\"epId\":" + "\"" + wEpID + "\"" +"}" + ",";
			arrMeetList += itemMeet;
		}
		arrMeetList = arrMeetList.substring(0, arrMeetList.length - 1);
		arrMeetList += "]";	
	}
	arrMeetList += "," + "\"wDiscussCount\":" + "\"" + nMeetCount + "\"";
	
	send_data = "{\"event\":\"ev_umcweb_UpdateAudMixInfo_req\"" + "," 
				+ "\"wCurConfID\":" + "\"" + parent.parent.getCurConfID() + "\"" + "," 
				+ "\"emOprType\":" + "\"" + emOprType + "\"" + ","
				+ "\"arrDiscuss\":" + "\"" + arrDiscuss + "\"" + "}";
	sendNty(send_data);		
};