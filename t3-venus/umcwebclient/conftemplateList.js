/**
 * @author xuhuaxiu
 */
//已选择的条目个数
var nChecked = 0;
var scroll = null;
var send_data = "";
//会议模版总数量
var nConftempNum = 0;

$(document).ready(function(){
	
	//立即召开
	$(".btn_startconf").click(function(){
		if( $(".div_list_content input:checked").length != 1 ){
			alert("请选择一个要召开的会议模板");
			return;
		}

		//点击checkbox可召开已选中模板会议
		top.showConfirmBox("请问你确定召开已选择的会议模板吗？");
	});

	//添加
	$(".btn_add").click(function(){
		parent.setCurConfTempID( "0" );
		parent.showCurPage("conftemplateEdit");
	});
	
	//修改
	$(".btn_modify").click(function(){
		if( $(".div_list_content input:checked").length != 1 ){
			alert("请选择一个要修改的会议模板");
			return;
		}
		
		$(".div_list_content input:checked").each(function(index,element){
			var strConfTempID = $(this).parents(".div_list_item").get(0).getAttribute("no");
			parent.setCurConfTempID(strConfTempID);
			parent.showCurPage("conftemplateEdit");
		});
	});
	
	//删除
	$(".btn_delete").click(function(){
		if( 0 == $(".div_list_content input:checked").length ){
			alert("请选择要删除的条目");
			return;
		}
		//点击checkbox可删除已选中模板
		top.showConfirmBox("是否删除所选模板信息？");
	});
	
	//搜索
	$(".img_search").unbind("click").click(function(){
		RefreshConftempList();
	});
	
	//添加滚动条
	scroll = new customBar($(".slider").get(0), $(".pannel").get(0), $(".drag").get(0));
	clearItem();
});

function onShowWnd()
{
	RefreshConftempList();
};

function sendNty(send_data)
{
    $.post(url,send_data,function(data,ts){
    	//返回通知消息
		switch( data.event ){
			case "ev_umcweb_RefreshConftempList_nty_res":{	//刷新会议模板列表通知型回应
				var arrConftemp = new Array();
				for (var i = 0; i < data.count; i++) {
					arrConftemp.push(data.items[i]);
				};
				updItem(arrConftemp);

				break;
			}
			case "ev_umcweb_StartConfTemplate_res":{		//召开会议结果回应
				$(".btn_startconf").removeAttr("disabled");
				parent.frames["conftemplateScan"].updStartconfBtnState(true);
				
				var strTip = "";	
				switch( data.emReason ){
					case "0":{		//TP_StartConf_UnKonw
						strTip = "开启会议失败";
						break;
					}
					case "1":{		//TP_StartConf_Success
						top.getConfListInfo();
						top.getConfbookListInfo();
						strTip = "会议开启成功";
						break;
					}
					case "2":{		//TP_StartConf_ConfTemplateUnExist
						strTip = "开启会议失败：会议模板不存在";
						break;
					}
					case "3":{		//TP_StartConf_ConfFull
						strTip = "开启会议失败：会议已满";
						break;
					}
					case "4":{		//TP_StartConf_ConfExist
						strTip = "开启会议失败：会议已存在";
						break;
					}
					case "5":{		//TP_StartConf_SipUnReg
						strTip = "开启会议失败：未注册网呈服务器";
						break;
					}
					case "6":{		//TP_StartConf_ResourceFull
						strTip = "开启会议失败：媒体资源不足";
						break;
					}
					default:{
						strTip = "开启会议失败";
						break;
					}
				}	
				
				top.addNtyMessageBox(strTip);					
				break;
			}
			case "ev_umcweb_DelAllConftemp_res":{			//删除全部模板回应
				if( "2" == data.emReason ){		//TP_ConfTemplate_DelSuccess
					RefreshConftempList();
				}
				else{
					top.addNtyMessageBox.show("删除全部模板失败");
				}
				break;
			}
			case "ev_umcweb_RefreshConfTempResult_res":{	//会议模板更新结果回应
				//刷新会议模板
				RefreshConftempList();
				break;
			}
			case "ev_umcweb_OperatorConfTemplate_res":{		//会议模板操作结果回应
				var strTip = "";	
				switch( data.emReason ){
					case "0":{		//TP_ConfTemplate_UnKonw
						strTip = "会议模板操作失败";
						break;
					}
					case "4":{		//TP_ConfTemplate_MaxNum
						strTip = "会议模板操作失败:模板数量到达上限";
						break;
					}
					case "5":{		//TP_ConfTemplate_E164Repeat
						strTip = "会议模板操作失败:e164号码重复";
						break;
					}
					case "6":{		//TP_ConfTemplate_UnFindConf
						strTip = "会议模板操作失败:未找到条目";
						break;
					}
					case "7":{		//TP_ConfTemplate_ParamInValid
						strTip = "会议模板操作失败:参数错误";
						break;
					}
					default:
						return;
				}	
				
				top.addNtyMessageBox(strTip);
				break;
			}
			case "ev_umcweb_RefreshConftemp_MeetNameList_nty_res":{	//刷新会议模板 与会会场列表 通知型回应
				RefreshConftempMeetNameListRes(data);
				break;
			}
			default:{
			    break;
			}
		}
    },'json');
};

function clearListItemSelState()
{	
	$(".div_list input").each(function(index,element){
		this.checked = false;
	});
	
	ctrlButtonState();
};

function clearItem()
{
	$(".div_list_item").remove(); 
	scroll.init();
	clearListItemSelState();
};

function updItem(arrConftemp)
{
	clearItem();
	
	var arrOrderedConftemp = ConfTemplateCompare(arrConftemp);
	
	for (var i=0; i < arrOrderedConftemp.length; i++) {
		var divListItem = document.createElement("div");
		divListItem.className="div_list_item";
		divListItem.setAttribute("onclick","onConftempItemClick(this)");
		divListItem.setAttribute("onmouseenter","onItemMouseenter(this)");
		divListItem.setAttribute("onmouseleave","onItemMouseleave(this)");
	
		var divListItemNo = document.createElement("div");
		divListItemNo.className="div_list_item_no";
		
		var checkboxItemNo = document.createElement("input");
		checkboxItemNo.type="checkbox";
		checkboxItemNo.setAttribute("onclick","onConftempItemCheckboxClick(this)");
	
		var divListItemName = document.createElement("div");
		divListItemName.className="div_list_item_name";
		
		var divListItemStartTime = document.createElement("div");
		divListItemStartTime.className="div_list_item_startTime";
		
		var divListItemMeetNum = document.createElement("div");
		divListItemMeetNum.className="div_list_item_meetNum";
		
		var aListItemMeetNum = document.createElement("a");
		aListItemMeetNum.href="javascript:void(0);"
		aListItemMeetNum.setAttribute("onclick","showMeetList(this)");
		
		var divListItemHomeMeetName = document.createElement("div");
		divListItemHomeMeetName.className="div_list_item_homeMeetName";
		
		var divListItemHandle = document.createElement("div");
		divListItemHandle.className="div_list_item_handle";
		
		var aListItemHandle = document.createElement("a");
		aListItemHandle.href="javascript:void(0);"
		aListItemHandle.setAttribute("onclick","showConfInfo(this)");
		$(aListItemHandle).text("详情");
	
		divListItem.appendChild(divListItemNo);
		divListItem.appendChild(checkboxItemNo);
		divListItem.appendChild(divListItemName);
		divListItem.appendChild(divListItemStartTime);
		divListItemMeetNum.appendChild(aListItemMeetNum);
		divListItem.appendChild(divListItemMeetNum);
		divListItem.appendChild(divListItemHomeMeetName);
		divListItemHandle.appendChild(aListItemHandle);
		divListItem.appendChild(divListItemHandle);
	
		var divListContent = $(".div_list_content").get(0);
		divListContent.appendChild(divListItem);
		
		$(divListItemNo).text(i+1);
		$(divListItemName).text(arrOrderedConftemp[i].achConfName);
		if( arrOrderedConftemp[i].achStartTime == "0" ){
			$(divListItemStartTime).text("即时");
		}
		else{
			$(divListItemStartTime).text("预约");	
		}
		$(aListItemMeetNum).text(arrOrderedConftemp[i].nMeetNum);
		$(divListItemHomeMeetName).text(arrOrderedConftemp[i].achHomeMeetName);
		
		//添加会议模板ID
		divListItem.setAttribute("no", arrOrderedConftemp[i].wConfTempID);
	};
	
	nConftempNum = arrOrderedConftemp.length;

	//添加滚动条
	scroll.init();
};

function onConftempListHeadCheckboxClick(obj)
{
	onListHeadCheckboxClick(obj);
	ctrlButtonState();
};

function onConftempItemClick(obj)
{
	onItemClick(obj);
	ctrlButtonState();
};

function onConftempItemCheckboxClick(obj)
{
	onItemCheckboxClick(obj);
	ctrlButtonState();
};

function ctrlButtonState()
{
	var nChecked = $(".div_list_wraper .div_list_content input:checked").length;
		
	if( 1 == nChecked ){
		$(".btn_startconf").removeAttr("disabled");
		$(".btn_modify").removeAttr("disabled");
	}else{
		$(".btn_startconf").attr("disabled","disabled");
		$(".btn_modify").attr("disabled","disabled");
	}

	if( 0 == nChecked ){
		$(".btn_delete").attr("disabled","disabled");
	}else{
		$(".btn_delete").removeAttr("disabled");
	}
};

//刷新会议模板 与会会场列表 通知型回应
function RefreshConftempMeetNameListRes(data)
{
	showPopup("popup_conftemplate_meetlist.html");
	
	var arrMeetList = new Array();
	for ( var i = 0; i < data.count; i++ ) {
		arrMeetList.push(data.items[i]);
	};
	top.setPopupMeetListTitle("会成员（" + data.count + "）");
	top.setPopupMeetListItem(arrMeetList);
}

//点击"会成员"响应函数
function showMeetList(obj)
{
	var strConfTempID = $(obj).parent().parents(".div_list_item").get(0).getAttribute("no");
	send_data = "{\"event\":\"ev_umcweb_RefreshConftemp_MeetNameList_nty_req\"" + "," + "\"wConfTempID\":" + "\"" + strConfTempID + "\"" + "}";
	sendNty(send_data);
	
	stopEvent();
};

//点击"详情"响应函数
function showConfInfo(obj)
{
	var strConfTempID = $(obj).parent().parents(".div_list_item").get(0).getAttribute("no");
	parent.setCurConfTempID(strConfTempID);
	parent.showCurPage("conftemplateScan");
	
	stopEvent();
};

//点击"立即召开"会议模板响应函数
function startConftemplate()
{
	$(".btn_startconf").attr("disabled","disabled");

	//立即召开已选择模板
	$(".div_list_content input:checked").each(function(index,element){
		var strConfTempID = $(this).parents(".div_list_item").get(0).getAttribute("no");
		send_data="{\"event\":\"ev_umcweb_StartConfTemplate_req\"" + "," + "\"wConfTempID\":" + "\"" + strConfTempID + "\"" + "}";
		sendNty(send_data);
	});
};

//点击"删除"会议模板响应函数
function delConftemplate()
{
	if( nChecked == nConftempNum ){
		//删除全部模板
		send_data="{\"event\":\"ev_umcweb_DelAllConftemp_req\"}";
		sendNty(send_data);
	}
	else{
		//删除已选择模板
		$(".div_list_content input:checked").each(function(index,element){
			var strConfTempID = $(this).parents(".div_list_item").get(0).getAttribute("no");
			send_data="{\"event\":\"ev_umcweb_DelConftemplate_req\"" + "," + "\"wConfTempID\":" + "\"" + strConfTempID + "\"" + "}";
			sendNty(send_data);
		});
	}
};

//刷新会议模板列表
function RefreshConftempList()
{
	var strSearch = $(".text_search").val();
	if( "搜索" == strSearch )
	{
		strSearch = "";
	}

	send_data="{\"event\":\"ev_umcweb_RefreshConftempList_nty_req\"" + "," + "\"strSearch\":" + "\"" + strSearch + "\"" + "}";
	sendNty(send_data);
};

//是否以汉字开头
function IsBeginWithChn(strName)
{
	var strBegin = strName.charAt(0);
	if( strBegin >= "A" && strBegin <="Z" ){
		return false;
	}
	else if( strBegin >= "a" && strBegin <= "z" ){
		return false;
	}
	else if( strBegin >= "0" && strBegin <= "9" ){
		return false;
	}
	
	return true;
};
         
//会议模板列表排序(兼容不同浏览器)
function ConfTemplateCompare(arrConftemp)
{
	var arrConfNameChn = new Array();
	var arrConfNameEng = new Array();
	for ( var i = 0; i < arrConftemp.length; i++ ) {
		if( IsBeginWithChn(arrConftemp[i].achConfName) ){
			arrConfNameChn.push(arrConftemp[i].achConfName);
		}
		else{
			arrConfNameEng.push(arrConftemp[i].achConfName);
		}
	};
	
	//汉字拼音排序方法
	arrConfNameChn.sort(function(x,y){return x.localeCompare(y)});
	arrConfNameEng.sort(function(x,y){return x.localeCompare(y)});

	var arrAllConfName = arrConfNameEng.concat(arrConfNameChn);
	var arrOrderedConftemp = new Array();
	for( var j = 0; j < arrAllConfName.length; j++ ){
		for( var k = 0; k < arrConftemp.length; k++ ){
			if( arrAllConfName[j] == arrConftemp[k].achConfName ){
				arrOrderedConftemp.push(arrConftemp[k]);
			}
		}
	}
	
	return arrOrderedConftemp;
};