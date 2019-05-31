/**
 * @author shicheng
 */
var scroll_conf = null;
var scroll_confbook= null;

$(document).ready(function(){
	//clearConfListItem();
	clearConfbookListItem();
	
	scroll_conf = new customBar($(".div_conf_list .slider").get(0), $(".div_conf_list .pannel").get(0), $(".div_conf_list .drag").get(0));
	scroll_confbook = new customBar($(".div_confbook_list .slider").get(0), $(".div_confbook_list .pannel").get(0), $(".div_confbook_list .drag").get(0));
});

function clearConfListItem()
{
	$(".div_conf_list .div_conf_list_item").remove(); 
};

function setConfListInfo(data)
{
	clearConfListItem();
	
	var arrItem=new Array();
				
	for (var i=0; i < data.count; i++) {
		arrItem.push(data.items[i]);
	};
	
	for (var i=0; i < arrItem.length; i++) {
		var divListItem = document.createElement("div");
		divListItem.className="div_conf_list_item";
	
		var divListItemType = document.createElement("div");
		divListItemType.className="div_conf_list_item_type";
		
		var divListItemTypeImg = document.createElement("img");
		divListItemType.appendChild(divListItemTypeImg);
		
		var divListItemName = document.createElement("div");
		divListItemName.className="div_conf_list_item_name";
		divListItemName.setAttribute("onclick","OnShowConfinfoClick(this)");
		
		var divListItemTime = document.createElement("div");
		divListItemTime.className="div_conf_list_item_time";
		
		var divListItemChair = document.createElement("div");
		divListItemChair.className="div_conf_list_item_chair";
	
		var divListItemRoomnumber = document.createElement("div");
		divListItemRoomnumber.className="div_conf_list_item_roomnumber";
		
		var BtnHangupConf = document.createElement("input");
		BtnHangupConf.type="button";
		BtnHangupConf.value="结束会议";
		BtnHangupConf.setAttribute("onclick","OnBtnHangupClick(this)");
		
		var BtnCtrlConf = document.createElement("input");
		BtnCtrlConf.type="button";
		BtnCtrlConf.value="会议控制";
		
		divListItem.appendChild(divListItemType);
		divListItem.appendChild(divListItemName);
		divListItem.appendChild(divListItemTime);
		divListItem.appendChild(divListItemChair);
		divListItem.appendChild(divListItemRoomnumber);
		divListItem.appendChild(BtnHangupConf);
		divListItem.appendChild(BtnCtrlConf);
	
		var divListContent = $(".div_conf_list .div_conf_list_content").get(0);
	
		divListContent.appendChild(divListItem);

		$(divListItemName).text(arrItem[i].confName);
		$(divListItemTime).text(arrItem[i].startTime+" 开始，时长 "+secondToDate(arrItem[i].interval));
		$(divListItemChair).text("主会场："+arrItem[i].chairroomName);
		$(divListItemRoomnumber).text("会成员："+arrItem[i].roomNumber);
		
		divListItem.setAttribute("no",arrItem[i].confId);
	};
	
	//添加滚动条
	
	scroll_conf.init();
};

function clearConfbookListItem()
{
	$(".div_confbook_list .div_conf_list_item").remove(); 
};

function setConfbookListInfo(data)
{
	clearConfbookListItem();
	
	var arrItem=new Array();
				
	for (var i=0; i < data.count; i++) {
		arrItem.push(data.items[i]);
	};
	
	for (var i=0; i < arrItem.length; i++) {
		var divListItem = document.createElement("div");
		divListItem.className="div_conf_list_item";
	
		var divListItemType = document.createElement("div");
		divListItemType.className="div_conf_list_item_type";
		
		var divListItemTypeImg = document.createElement("img");
		divListItemType.appendChild(divListItemTypeImg);
		
		var divListItemName = document.createElement("div");
		divListItemName.className="div_conf_list_item_name";
		
		var divListItemTime = document.createElement("div");
		divListItemTime.className="div_conf_list_item_time";
		
		var divListItemChair = document.createElement("div");
		divListItemChair.className="div_conf_list_item_chair";
	
		var divListItemRoomnumber = document.createElement("div");
		divListItemRoomnumber.className="div_conf_list_item_roomnumber";
		
		var divListItemInterval = document.createElement("div");
		divListItemInterval.className="div_conf_list_item_interval";
		
		
		var BtnStartConf = document.createElement("input");
		BtnStartConf.type="button";
		BtnStartConf.className="btnStartConf";
		BtnStartConf.value="立即召开";
		BtnStartConf.setAttribute("onclick","onBtnStartConfClick(this)");
		
		divListItem.appendChild(divListItemType);
		divListItem.appendChild(divListItemName);
		divListItem.appendChild(divListItemTime);
		divListItem.appendChild(divListItemChair);
		divListItem.appendChild(divListItemRoomnumber);
		divListItem.appendChild(divListItemInterval);
		divListItem.appendChild(BtnStartConf);
	
		var divListContent = $(".div_confbook_list .div_conf_list_content").get(0);
	
		divListContent.appendChild(divListItem);

		$(divListItemName).text(arrItem[i].confName);
		$(divListItemTime).text(arrItem[i].startTime+" 开始");
		$(divListItemChair).text("主会场："+arrItem[i].chairroomName);
		$(divListItemRoomnumber).text("会成员："+arrItem[i].roomNumber);
		$(divListItemInterval).text("距离会议开启时间："+secondToDate(arrItem[i].interval));
		
		divListItem.setAttribute("no",arrItem[i].confId);
	};
	
	//添加滚动条
	
	scroll_confbook.init();
};


function OnBtnHangupClick(obj)
{
	var id = $(obj).parents(".div_conf_list_item").get(0).getAttribute("no");
	var send_data="{\"event\":\"ev_umcweb_hangupconf_req\"" + "," + "\"confid\":" + "\"" + id + "\"" + "}";

	$.post(url,send_data,function(data,ts){
		if(data.emRet == 0)
		{
			top.getConfListInfo();
		}
		else
		{
			alert("挂断会议失败");
		}
    },'json');
};

function onBtnStartConfClick(obj)
{
	var strConfName = $(obj).siblings(".div_conf_list_item_name").text();
	send_data="{\"event\":\"ev_umcweb_StartConfTemplate_req\"" + "," + "\"ConfName\":" + "\"" + strConfName + "\"" + "}";
	top.frames["conftemplate"].frames["conftemplateList"].sendNty(send_data);
};

function OnBtnConfctrlClick(obj)
{
	parent.setCurConfID($(obj).parents(".div_conf_list_item").get(0).getAttribute("no"));

	parent.showCurPage("confctrl");
};

function OnShowConfinfoClick(obj)
{
	parent.setCurConfID($(obj).parents(".div_conf_list_item").get(0).getAttribute("no"));

	parent.showCurPage("confinfo");
};

function onClickStretchTab_conf(obj)
{
	onClickStretchTab(obj);
	
	//临时解决问题：display:none的元素无法获取子元素的真实高度
	scroll_conf.init();
};

function onClickStretchTab_confbook(obj)
{
	onClickStretchTab(obj);
	
	//临时解决问题：display:none的元素无法获取子元素的真实高度
	scroll_confbook.init();
};

function onShowWnd()
{
	
};
