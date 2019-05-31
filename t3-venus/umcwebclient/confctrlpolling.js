/**
 * @author xuhuaxiu
 */
var send_data = "";
var scroll = null;
var bPollListOper = false;

$(document).ready(function(){
	bPollListOper = false;

	$(".aBack").unbind("click").click(function(){
		parent.showCurPage("confoper");
	});
	
	$(".btnStart").unbind("click").click(function(){
		StartTurnReq();
	});
	
	$(".btnSuspend").unbind("click").click(function(){
		SuspendTurnReq();
	});
	
	//轮询列表操作
	$(".aPollingSetTop").unbind("click").click(function(){
		if( "false" == $(this).attr("unable") ){
			bPollListOper = true;
			setTop($(".div_list")[0]);
		}else{
			return false;
		}
	});
	
	$(".aPollingMoveUp").unbind("click").click(function(){
		if( "false" == $(this).attr("unable") ){
			bPollListOper = true;
			moveUp($(".div_list")[0]);
		}else{
			return false;
		}
	});
	
	$(".aPollingMoveDown").unbind("click").click(function(){
		if( "false" == $(this).attr("unable") ){
			bPollListOper = true;
			moveDown($(".div_list")[0]);
		}else{
			return false;
		}
	});
	
	$(".aPollingSetBottom").unbind("click").click(function(){
		if( "false" == $(this).attr("unable") ){
			bPollListOper = true;
			setBottom($(".div_list")[0]);
		}else{
			return false;
		}
	});
	
	$(".aPollingAdd").unbind("click").click(function(){
		if( "false" == $(this).attr("unable") ){
			bPollListOper = true;
			showPopup("popup_confctrl_addmeet.html");
		}else{
			return false;
		}
	});
	
	$(".aPollingRemove").unbind("click").click(function(){
		if( "false" == $(this).attr("unable") ){
			bPollListOper = true;
			var arrRestItems = getRestItems( $(".div_list")[0] );
			updItem( arrRestItems );
		}else{
			return false;
		}
	});
	
	//添加滚动条
	scroll = new customBar($(".slider").get(0), $(".pannel").get(0), $(".drag").get(0));
	clearItem();
	updateUIState();
});

/*********************界面显示处理**************************************************************************/

function onShowWnd()
{
	bPollListOper = false;
	RefreshConfinfoPollingListReq( parent.parent.getCurConfID() );
};

function updateUIState()
{
	var strTip = $(".btnStart").attr("value");
	if( "开启轮询" == strTip ){	//可编辑
		$(".div_list input").each(function(index,element){
			$(this).css("display", "block");
		});
		
		$(".div_list .div_list_item .div_list_item_no").each(function(index,element){
			$(this).css("display", "none");
		});
		
		$(".div_list .div_list_head .div_list_head_allsel").css("width", "60px");
		$(".div_list .div_list_head .div_list_head_allsel").text("全选");
		
		$(".textTime").removeAttr("disabled");
		$(".btnSuspend").removeAttr("disabled");
	}else{						//不可编辑
		$(".div_list input").each(function(index,element){
			$(this).css("display", "none");
		});
		
		$(".div_list .div_list_item .div_list_item_no").each(function(index,element){
			$(this).css("display", "block");
		});
		
		$(".div_list .div_list_head .div_list_head_allsel").css("width", "85px");
		$(".div_list .div_list_head .div_list_head_allsel").text("序号");
		
		$(".textTime").attr("disabled", "disabled");
		$(".btnSuspend").attr("disabled", "disabled");
	}
	clearListItemSelState();
};

function addPollingItem(nCount, strEpId, strMeetName, strE164, strMeetIp)
{
	if ( "" == strEpId ){
		return false;
	}
	
	if( "" == strMeetName && "" == strE164 && "" == strMeetIp){
		return false;
	}
	
	var divListItem = document.createElement("div");
	divListItem.className="div_list_item";
	divListItem.setAttribute("onclick","onPollingItemClick(this)");
	divListItem.setAttribute("onmouseenter","onItemMouseenter(this)");
	divListItem.setAttribute("onmouseleave","onItemMouseleave(this)");

	var checkboxItemNo = document.createElement("input");
	checkboxItemNo.type="checkbox";
	checkboxItemNo.setAttribute("onclick","onPollingItemCheckboxClick(this)");
	
	var divListItemNo = document.createElement("div");
	divListItemNo.className="div_list_item_no";

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
	divListItem.appendChild(divListItemName);
	divListItem.appendChild(divListItemNum);
	divListItem.appendChild(divListItemIp);
	
	var divListContent = $(".div_list .slider").get(0);
	divListContent.appendChild(divListItem);
	
	$(divListItemNo).text(nCount);
	$(divListItemName).text(strMeetName);
	$(divListItemNum).text(strE164);
	$(divListItemIp).text(strMeetIp);
	
	divListItem.setAttribute("no", strEpId);	
	
	updateUIState();
	scroll.init();
	
	return true;
};

function clearItem()
{
	$(".div_list_item").remove(); 
	scroll.init();
	clearListItemSelState();
};

function updItem(arrPolling)
{
	clearItem();

	for (var i=0; i < arrPolling.length; i++) {	
		addPollingItem( (i+1), arrPolling[i].epId, arrPolling[i].achMeetName,
			 arrPolling[i].achE164, arrPolling[i].achMeetIp );
	};
};

function onPollingListHeadCheckboxClick(obj)
{
	onListHeadCheckboxClick(obj);
	ctrlButtonState();
};

function onPollingItemClick(obj)
{
	onItemClick(obj);
	ctrlButtonState();
};

function onPollingItemCheckboxClick(obj)
{
	onItemCheckboxClick(obj);
	ctrlButtonState();
};

function clearListItemSelState()
{	
	$(".div_list input").each(function(index,element){
		this.checked = false;
	});
	
	ctrlButtonState();
};

function ctrlButtonState()
{
	var strTip = $(".btnStart").attr("value");
	if( "关闭轮询" == strTip ){	//不可编辑
		$("a[name='aPollingOper']").each(function(index){
			$(this).attr("unable", true);
		});
		setOperButtonColor();
		return;
	}
	
	var nChecked = $(".div_list .wraper input:checked").length;

	if( 1 == nChecked ){
		$("a[name='aPollingOper']").each(function(index){
			$(this).attr("unable", false);
		});
	}else{
		$("a[name='aPollingOper']").each(function(index){
			$(this).attr("unable", true);
		});
		
		$(".aPollingAdd").attr("unable", false);
	}

	if( 0 == nChecked ){
		$(".aPollingRemove").attr("unable", true);
	}else{
		$(".aPollingRemove").attr("unable", false);
	}
	
	setOperButtonColor();
};

/*********************消息处理****************************************************************************/

function sendNty(send_data)
{
    $.post(url,send_data,function(data,ts){
    	//返回通知消息
		switch( data.event ){
			case "ev_umcweb_RefreshConfinfo_PollingList_nty_res":{			//刷新会议管理  会议轮询 通知型回应
					RefreshConfinfoPollingListRes(data);
				break;
			}
			case "ev_umcweb_SuspendTurn_res":{			//暂停、恢复 轮询 回应
					SuspendTurnRes(data);
				break;
			}
			case "ev_umcweb_StartTurn_res":{			//开启、停止 轮询 回应
					StartTurnRes(data);
				break;
			}
			default:{
			    break;
			}
		}
    },'json');
};

//刷新会议管理 轮询列表 请求
function RefreshConfinfoPollingListReq(curconfID)
{
	send_data = "{\"event\":\"ev_umcweb_RefreshConfinfo_PollingList_nty_req\"" + "," + "\"wCurConfID\":" + "\"" + curconfID + "\"" + "}";
	sendNty(send_data);	
};

function RefreshConfinfoPollingListRes(data)
{
	$(".btnSuspend").attr("value", "暂停");
	$(".btnSuspend").attr("disabled", "disabled");
	//0: EmPollStat_Error; 1: EmPollStat_Stop; 2: EmPollStat_Start; 3: EmPollStat_Suspend
	if( "1" == data.emStat ){
		$(".btnStart").attr("value", "开启轮询");
	}else if( "2" == data.emStat ){
		$(".btnStart").attr("value", "关闭轮询");
		$(".btnSuspend").removeAttr("disabled");
	}else if( "3" == data.emStat ){
		$(".btnStart").attr("value", "关闭轮询");
		$(".btnSuspend").attr("value", "恢复");
		$(".btnSuspend").removeAttr("disabled");
	}else{
		$(".btnStart").attr("value", "开启轮询");
	}
	
	$(".textTime").val(data.wInterval + " s");
	
	var arrPollingList = new Array();
	for ( var i = 0; i < data.count; i++ ) {
		arrPollingList.push(data.items[i]);
	};
	updItem(arrPollingList);
};

//暂停、恢复轮询 请求
function SuspendTurnReq()
{
	var strIsPollingSuspend = "0";
	if( $(".btnSuspend").attr("value") == "暂停" )
	{
		strIsPollingSuspend = "1";
	}
	
	send_data = "{\"event\":\"ev_umcweb_SuspendTurn_req\"" + "," 
				+ "\"wCurConfID\":" + "\"" + parent.parent.getCurConfID() + "\"" + "," 
				+ "\"bSuspend\":" + "\"" + strIsPollingSuspend + "\"" + "}";
	sendNty(send_data);	
};

function SuspendTurnRes(data)
{
	var strTip = $(".btnSuspend").attr("value");
	if( "0" == data.emTPPollResult ){	//0: emPollSucceed
		if( strTip == "暂停" ){
			$(".btnSuspend").attr("value", "恢复");
		}else{
			$(".btnSuspend").attr("value", "暂停");
		}
	}else{
		showErrorMsg(strTip, data.emTPPollResult);
	}
};

//更新轮询列表 请求
function UpdateTurnReq()
{
	var strTime = $(".textTime").val();
	strTime = strTime.substring(0, strTime.lastIndexOf(" s"));
	
	var arrMeetList = "\"\"";
	var nMeetCount = $(".div_list .div_list_item").length;
	if( nMeetCount > 0 ){
		arrMeetList = "[";
		$(".div_list .div_list_item").each(function(index,element){
			var strId = this.getAttribute("no");
			var strMeetName = $(this).children(".div_list_item_name").val();
			var strMeetNum = $(this).children(".div_list_item_number").val();
			var strMeetIp = $(this).children(".div_list_item_ip").val();
			
			var itemMeet = "{\"epId\":" + "\"" + strId + "\"" + "," + 
						    "\"achMeetName\":" + "\"" + strMeetName + "\"" + "," + 
						    "\"achE164\":" + "\"" + strMeetNum + "\"" + "," + 
							"\"achMeetIp\":" + "\"" + strMeetIp + "\"" +"}" + ",";
	
			arrMeetList += itemMeet;
		});

		arrMeetList = arrMeetList.substring(0, arrMeetList.length - 1);
		arrMeetList += "]";	
	}
	arrMeetList += "," + "\"wPollingCount\":" + "\"" + nMeetCount + "\"";	
	
	send_data = "{\"event\":\"ev_umcweb_UpdateTurn_req\"" + ","
	+ "\"wCurConfID\":" + "\"" + parent.parent.getCurConfID() + "\"" + "," 
	+ "\"wInterval\":" + "\"" + strTime + "\"" + "," 
	+ "\"arrPolling\":" + arrMeetList + "}";
	sendNty(send_data);
};

//开启、关闭轮询 请求
function StartTurnReq()
{
	var strIsPollingStart = "1";
	if( $(".btnStart").attr("value") == "关闭轮询" )
	{
		strIsPollingStart = "0";
	}
	
	if( "1" == strIsPollingStart && true == bPollListOper )
	{
		UpdateTurnReq();
	}
	
	send_data = "{\"event\":\"ev_umcweb_StartTurn_req\"" + "," 
				+ "\"wCurConfID\":" + "\"" + parent.parent.getCurConfID() + "\"" + "," 
				+ "\"bStart\":" + "\"" + strIsPollingStart + "\"" + "}";
	sendNty(send_data);
};

function StartTurnRes(data)
{
	var strTip = $(".btnStart").attr("value");
	if( "0" == data.emTPPollResult ){	//0: emPollSucceed
		if( "0" == data.bStart ){
			$(".btnStart").attr("value", "开启轮询");
		}else{
			$(".btnStart").attr("value", "关闭轮询");
		}
		updateUIState();
	}else{
		showErrorMsg(strTip, data.emTPPollResult);
	}
};

//提示错误信息
function showErrorMsg(strTip, emTPPollResult)
{
	switch( emTPPollResult ){
		case "1":{	//1: emPollFailUnKown
			alert(strTip + "失败：emPollFailUnKown");
			break;
		}
		case "2":{	//2: emPollInvalidEp
			alert(strTip + "失败：无有效轮训会场");
			break;
		}
		case "3":{	//3: emPollResFull
			alert(strTip + "失败：资源不足：带宽、适配");
			break;
		}
		case "4":{	//4: emPollNoChair
			alert(strTip + "失败：无主席权限");
			break;
		}
		case "5":{	//5: emPollChairNoLine
			alert(strTip + "失败：主席不在线");
			break;
		}
		case "6":{	//6: emPollServerBusy
			alert(strTip + "失败：服务器忙");
			break;
		}
		default:{
			break;
		}
	}
};