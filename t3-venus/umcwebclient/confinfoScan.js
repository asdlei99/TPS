/**
 * @author xuhuaxiu
 */

/*********************界面显示处理**************************************************************************/

function clearScanfMeetListItem()
{
	$(".div_Scanf_Meet_list_content .div_list_item").remove(); 
};

//浏览界面  与会会场列表
function updScanfMeetListItem(arrMeetList)
{
	clearScanfMeetListItem();
	
	for (var i=0; i < arrMeetList.length; i++) {
		var divListItem = document.createElement("div");
		divListItem.className="div_list_item";
		divListItem.setAttribute("onclick","onItemClick(this)");
		divListItem.setAttribute("onmouseenter","onItemMouseenter(this)");
		divListItem.setAttribute("onmouseleave","onItemMouseleave(this)");
		
		var divListItemNo = document.createElement("div");
		divListItemNo.className="div_Meet_list_item_no";
		
		var divListItemImg = document.createElement("div");
		divListItemImg.className="div_Meet_list_item_img";
	
		var divListItemName = document.createElement("div");
		divListItemName.className="div_Meet_list_item_name";

		var divListItemNum = document.createElement("div");
		divListItemNum.className="div_Meet_list_item_num";
		
		var divListItemIp = document.createElement("div");
		divListItemIp.className="div_Meet_list_item_ip";

		divListItem.appendChild(divListItemNo);
		divListItem.appendChild(divListItemImg);
		divListItem.appendChild(divListItemName);
		divListItem.appendChild(divListItemNum);
		divListItem.appendChild(divListItemIp);

		var divListContent = $(".div_Scanf_Meet_list_content .div_list_content").get(0);
		divListContent.appendChild(divListItem);

		$(divListItemNo).text(i+1);
		$(divListItemName).text(arrMeetList[i].achMeetName);
		$(divListItemNum).text(arrMeetList[i].achE164);
		$(divListItemIp).text(arrMeetList[i].achMeetIp);
		
		divListItem.setAttribute("no", arrMeetList[i].epId);
	};
	
	//添加滚动条
	scroll_Scanf_MeetList.init();
};

/*********************消息处理****************************************************************************/

//接到会议模板信息   回应，刷新界面
function RefreshConftempInfoRes(data)
{
	if( "" == data.wConfTempID )
	{
		alert("fail to find this conftemplate info");
		return false;
	}

	$(".div_conftempname").text(data.achConfName);
	
	$(".spanConfName").text(data.achConfName);
	$(".spanConfNum").text(data.achConfNum);
	
	if( "0" == data.achStartTime ){
		$(".spanConfType").text("即时会议");
		$(".spanConfTime").text("");
	}
	else{
		$(".spanConfType").text("预约会议");
		$(".spanConfTime").text(data.achStartTime);
	}
	
	//会议格式
	var strMainVideo = "";
	for( var i = 0; i < data.wMainNum; i++ ){
		strMainVideo = strMainVideo + data.atTpMainVideoRes[i].chFormatName + "; ";
	}
	strMainVideo = strMainVideo.substring(0, strMainVideo.lastIndexOf(";"));
	$(".spanConfFormat").text(strMainVideo);
	
	//演示格式
	var strMinorVideo = "";
	for( var i = 0; i < data.wMinorNum; i++ ){
		strMinorVideo = strMinorVideo + data.atTpMinorVideoRes[i].chFormatName + "; ";
	}
	strMinorVideo = strMinorVideo.substring(0, strMinorVideo.lastIndexOf(";"));
	$(".spanShowFormat").text(strMinorVideo);
	
	//音频格式
	var strAudioVideo = "";
	for( var i = 0; i < data.wAudFmtNum; i++ ){
		strAudioVideo = strAudioVideo + data.atAudFmt[i].chFormatName + "; ";
	}
	strAudioVideo = strAudioVideo.substring(0, strAudioVideo.lastIndexOf(";"));
	$(".spanAudioFormat").val(strAudioVideo);
	
	var strAdaptRes = "当前模板所需适配通道：" + data.wResNum + "/系统总适配通道：" + data.wResUsedCount;
	$(".spanAdaptRes").text(strAdaptRes);
	
	$(".spanSingleRate").text(data.nSingleRate + " Kbps");
	$(".spanShowRate").text(data.nShowRate + " Kbps");
	
	$(".spanUpBandWidth").text(data.nUpBandWidth + " Kbps");
	$(".spanDownBandWidth").text(data.nDownBandWidth + " Kbps");
	
	$(".spanEncrypt").text(data.achEncrypt);
	
	$(".spanPollingTime").text(data.nPollingTime + "s");
	
	return true;
};

//刷新会议模板 与会会场列表通知型回应
function RefreshConftempMeetNameListRes(data)
{
	var arrMeetList = new Array();
	for ( var i = 0; i < data.count; i++ ) {
		arrMeetList.push(data.items[i]);
	};
	updScanfMeetListItem(arrMeetList);
};

//刷新会议模板 轮询列表 回应
function RefreshConftempPollingListRes(data)
{
	showPopup("popup_conftemplate_meetlist.html");
	
	var arrMeetList = new Array();
	for ( var i = 0; i < data.count; i++ ) {
		arrMeetList.push(data.items[i]);
	};
	top.setPopupMeetListTitle("轮询成员（" + data.count + "）");
	top.setPopupMeetListItem(arrMeetList);
};

//刷新会议模板 讨论列表 回应
function RefreshConftempDiscussListRes(data)
{
	showPopup("popup_conftemplate_meetlist.html");
	
	var arrMeetList = new Array();
	for ( var i = 0; i < data.count; i++ ) {
		arrMeetList.push(data.items[i]);
	};
	top.setPopupMeetListTitle("讨论成员（" + data.count + "）");
	top.setPopupMeetListItem(arrMeetList);
};