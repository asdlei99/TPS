/**
 * @author shicheng
 */
var scroll = null;
$(document).ready(function(){
	$(".btnBack").click(function(){
		parent.showCurPage("conflist");
	});
	
	$(".img_search").click(function(){
		getMTList();
	});
	
	scroll = new customBar($(".slider").get(0), $(".pannel").get(0), $(".drag").get(0));
	
	showCurPage("confoper"); //设置默认显示界面
});

function getMTList()
{
	var confid = parent.getCurConfID();
					
	var strSearch = $(".text_search").val();
	if(strSearch == "搜索")
	{
		strSearch = "";
	}
	
	var send_data='{"event":"ev_umcweb_list_meetingroom_get_req","confid":"'+confid+"\",\"search\":\""+strSearch+'"}';
	sendNty(send_data);
};

function onShowWnd()
{
	getMTList();
	
	showCurPage("confoper"); //设置默认显示界面
};

function onListMTItemClick(obj)
{
	onItemClick(obj);
	
	window.frames["confoper"].updBtnState();
};

function onListMTItemCheckboxClick(obj)
{
	onItemCheckboxClick(obj);
	
	window.frames["confoper"].updBtnState();
};

function onListMTHeadCheckboxClick(obj)
{
	onListHeadCheckboxClick(obj);
	
	window.frames["confoper"].updBtnState();
};

function clearMtList()
{
	parent.$(".div_list_item").remove();
};

function updMtList(data)
{
	clearMtList();
	
	var arrItem=new Array();
				
	for (var i=0; i < data.count; i++) {
		arrItem.push(data.items[i]);
	};
	
	for (var i=0; i < arrItem.length; i++) {
		var divListItem = document.createElement("div");
		divListItem.className="div_list_item";
		divListItem.setAttribute("onmouseenter","onItemMouseenter(this)");
		divListItem.setAttribute("onmouseleave","onItemMouseleave(this)");
		divListItem.setAttribute("onclick","onListMTItemClick(this)");
	
		var checkboxItemNo = document.createElement("input");
		checkboxItemNo.type="checkbox";
		checkboxItemNo.setAttribute("onclick","onListMTItemCheckboxClick(this)");
		
		var divListItemOnline = document.createElement("div");
		divListItemOnline.className="div_list_item_online";
		
		var divListItemName = document.createElement("div");
		divListItemName.className="div_list_item_name";
		
		var divListItemOper = document.createElement("div");
		divListItemOper.className="div_list_item_oper";
		
		var fontDual = document.createElement("font");
		fontDual.className="font_dual";
		var fontSpeaker = document.createElement("font");
		fontSpeaker.className="font_speaker";
		var fontQuiet = document.createElement("font");
		fontQuiet.className="font_quiet";
		var fontMute = document.createElement("font");
		fontMute.className="font_mute";
		var fontSelview = document.createElement("font");
		fontSelview.className="font_selview";
		
		divListItemOper.appendChild(fontDual);
		divListItemOper.appendChild(fontSpeaker);
		divListItemOper.appendChild(fontQuiet);
		divListItemOper.appendChild(fontMute);
		divListItemOper.appendChild(fontSelview);
		
		divListItem.appendChild(checkboxItemNo);
		divListItem.appendChild(divListItemOnline);
		divListItem.appendChild(divListItemName);
		divListItem.appendChild(divListItemOper);
	
		var divListContent = $(".div_list_content").get(0);
	
		divListContent.appendChild(divListItem);
		
		var strOnline = "不在线";
		if( arrItem[i].bOnline == "1" )
		{
			strOnline = "在线";
		}
		$(divListItemOnline).text(strOnline);
		
		var strName;
		if( arrItem[i].epName != "" )
		{
			strName = arrItem[i].epName;
		}
		else if( arrItem[i].epNo != "" )
		{
			strName = arrItem[i].epNo;
		}
		else
		{
			strName = arrItem[i].epIp;
		}
		$(divListItemName).text(strName);
		
		var strDual = "未双流";
		if( arrItem[i].bDual == "1" )
		{
			strOnline = "双流";
		}
		$(fontDual).text(strOnline);
		
		var strSpeaker = "未发言";
		if( arrItem[i].bSpeaker == "1" )
		{
			strSpeaker = "发言";
		}
		$(fontSpeaker).text(strSpeaker);
		
		var strQuiet = "未静音";
		if( arrItem[i].bQuiet == "1" )
		{
			strQuiet = "静音";
		}
		$(fontQuiet).text(strQuiet);
		
		var strMute = "未哑音";
		if( arrItem[i].bMute == "1" )
		{
			strMute = "哑音";
		}
		$(fontMute).text(strMute);
		
		var strSelview = "未选看";
		if( arrItem[i].bSelview == "1" )
		{
			strSelview = "哑音";
		}
		$(fontSelview).text(strSelview);
		
		divListItem.setAttribute("no",arrItem[i].epId);
	};
	
	//添加滚动条
	scroll.init();
};

function sendNty(send_data)
{
    $.post(url,send_data,function(data,ts){
    	//返回通知消息
		switch(data.event){
			case "ev_umcweb_list_meetingroom_get_res":{
				updMtList(data);
				
				break;
			}
			default:{
			    break;
			}
		}
    },'json');
};

function showCurPage(pageid)
{
	$("#confoper").css("width", "0px");
	$("#confoper").css("height", "0px");
	$("#confctrldiscuss").css("width", "0px");
	$("#confctrldiscuss").css("height", "0px");
	$("#confctrlpolling").css("width", "0px");
	$("#confctrlpolling").css("height", "0px");

	switch(pageid){
		case "confoper":{
			$("#confoper").css("width", "100%");
			$("#confoper").css("height", "100%");
			break;
		}
		case "confctrldiscuss":{
			$("#confctrldiscuss").css("width", "100%");
			$("#confctrldiscuss").css("height", "100%");
			break;
		}
		case "confctrlpolling":{
			$("#confctrlpolling").css("width", "100%");
			$("#confctrlpolling").css("height", "100%");
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

function getCurMtID()
{
	var arr$DomItem = $(".div_list_item");
	for ( var i=0; i < arr$DomItem.length; i++ )
	{
		var bChecked = $(arr$DomItem[i]).find("input:checked").length;
		if(bChecked)
		{
			return arr$DomItem[i].getAttribute("no");
		}
	};
	
	return 0;
};
