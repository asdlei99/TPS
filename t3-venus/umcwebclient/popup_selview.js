/**
 * @author shicheng
 */
var scroll_popup_selview = null;
$(document).ready(function(){
	$(".div_popup_selview .img_search").click(function(){
		getMTList_popup_selview();
	});
	
	scroll_popup_selview = new customBar($(".div_popup_selview .slider").get(0), $(".div_popup_selview .pannel").get(0), $(".div_popup_selview .drag").get(0));
});

function onShowWnd_popup_selview()
{
	$(".div_popup_selview .text_search").val("搜索");
	clearMtList_popup_selview();
	
	getMTList_popup_selview();
	getSelviewInfo_popup_selview();
};

function OnListMatrixItemClick(obj)
{
	var arr$DomItem = $(obj).parents(".div_popup_selview .div_list_matrix").find(".div_list_matrix_item");
	for (var i=0; i < arr$DomItem.length; i++) {
	  $(arr$DomItem[i]).css('border-color','#B5B4B4');
	  arr$DomItem[i].setAttribute("selected","false");
	};
	
	$(obj).css('border-color','#007AC0');
	obj.setAttribute("selected","true");
};

function onListMatrixItemMouseenter(obj)
{
	$(obj).find('input').css("visibility","visible");
	$(obj).css('background-color','#F3F3F3');
};

function onListMatrixItemMouseleave(obj)
{
	$(obj).find('input').css("visibility","hidden");
	$(obj).css('background-color','white');
};

function sendNty_popup_selview(send_data)
{
    $.post(url,send_data,function(data,ts){
    	//返回通知消息
		switch(data.event){
			case "ev_umcweb_list_meetingroom_get_res":{
				updMtList_popup_selview(data);
				
				break;
			}
			case "ev_umcweb_selviewinfo_get_res":{
				updSelviewInfo_popup_selview(data);
				
				break;
			}
			case "ev_umcweb_epoper_selview_res":{
				if(data.emRet == "0")
				{
					getSelviewInfo_popup_selview();
				}
				else
				{
					alert("选看失败");
				}
				
				break;
			}
			default:{
			    break;
			}
		}
    },'json');
};

function clearMtList_popup_selview()
{
	parent.$(".div_popup_selview .div_list .div_list_item").remove();
};

function updMtList_popup_selview(data)
{
	clearMtList_popup_selview();
	
	var arrItem=new Array();
				
	for (var i=0; i < data.count; i++) {
		arrItem.push(data.items[i]);
	};
	
	for (var i=0; i < arrItem.length; i++) {
		var divListItem = document.createElement("div");
		divListItem.className="div_list_item";
		divListItem.setAttribute("onmouseenter","onItemMouseenter(this)");
		divListItem.setAttribute("onmouseleave","onItemMouseleave(this)");
		divListItem.setAttribute("onclick","onItemClick_selview(this)");
	
		var divListItemNo = document.createElement("div");
		divListItemNo.className="div_Meet_list_item_no";
		
		var divListItemOnline = document.createElement("div");
		divListItemOnline.className="div_Meet_list_item_online";
		
		var divListItemName = document.createElement("div");
		divListItemName.className="div_Meet_list_item_name";
		
		var divListItemNum = document.createElement("div");
		divListItemNum.className="div_Meet_list_item_num";
		
		var divListItemIP = document.createElement("div");
		divListItemIP.className="div_Meet_list_item_ip";
		
		divListItem.appendChild(divListItemNo);
		divListItem.appendChild(divListItemOnline);
		divListItem.appendChild(divListItemName);
		divListItem.appendChild(divListItemNum);
		divListItem.appendChild(divListItemIP);
	
		var divListContent = $(".div_popup_selview .div_list_content").get(0);
	
		divListContent.appendChild(divListItem);
		
		$(divListItemNo).text(i+1);
		
		var strOnline = "不在线";
		if( arrItem[i].bOnline == "1" )
		{
			strOnline = "在线";
		}
		$(divListItemOnline).text(strOnline);
		
		
		$(divListItemName).text(arrItem[i].epName);
		$(divListItemNum).text(arrItem[i].epNo);
		$(divListItemIP).text(arrItem[i].epIp);
		
		divListItem.setAttribute("no",arrItem[i].epId);
	};
	
	//添加滚动条
	scroll_popup_selview.init();
};

function getMTList_popup_selview()
{
	var confid = window.frames["confmng"].getCurConfID();
					
	var strSearch = $(".div_popup_selview .text_search").val();
	if(strSearch == "搜索")
	{
		strSearch = "";
	}
	
	var send_data='{"event":"ev_umcweb_list_meetingroom_get_req","confid":"'+confid+"\",\"search\":\""+strSearch+'"}';
	sendNty_popup_selview(send_data);
};

function getSelviewInfo_popup_selview()
{
	var confid = window.frames["confmng"].getCurConfID();
	
	var epid = window.frames["confmng"].frames["confctrl"].getCurMtID();
	
	var send_data='{"event":"ev_umcweb_selviewinfo_get_req","confid":"'+confid+"\",\"epid\":\""+epid+'"}';
	sendNty_popup_selview(send_data);
};

function updSelviewInfo_popup_selview(data)
{
    var arrItem=new Array();
				
	for (var i=0; i < data.count; i++) {
		arrItem.push(data.items[i]);
	};
	
	if( data.count == "1" )
	{
		$(".div_screen_three").css('display','none');
		$(".div_screen_one").css('display','block');
		
		var domScreenOne = $(".div_screen_one")[0];
		
		if( arrItem[0].selName == "" )
		{
			$(".div_screen_one .div_mtname").text("未选看");
			$(".div_screen_one img")[0].setAttribute("src", "src/matrixlist/matrix_list_noitem.png");
		}
		else
		{
			domScreenOne.setAttribute("no",arrItem[0].selId);
			domScreenOne.setAttribute("type",arrItem[0].selType);
			$(".div_screen_one .div_mtname").text(arrItem[0].selName);
			$(".div_screen_one img")[0].setAttribute("src", "src/matrixlist/matrix_list_item.png");
		}
	}
	else
	{
		$(".div_screen_three").css('display','block');
		$(".div_screen_one").css('display','none');
		
		var arr$DomScreenThree = $(".div_screen_three");
		for (var i=0; i < arr$DomScreenThree.length; i++)
		{
			if( arrItem[i].selName == "" )
			{
				arr$DomScreenThree.find(".div_mtname").text("未选看");
				arr$DomScreenThree.find("img")[i].setAttribute("src", "src/matrixlist/matrix_list_noitem.png");
			}
			else
			{
				arr$DomScreenThree[i].setAttribute("no",arrItem[i].selId);
				arr$DomScreenThree[i].setAttribute("type",arrItem[i].selType);
				arr$DomScreenThree.find(".div_mtname").text(arrItem[i].selName);
				arr$DomScreenThree.find("img")[i].setAttribute("src", "src/matrixlist/matrix_list_item.png");
			}
		};
	}
};


function onItemClick_selview()
{
	var confid = window.frames["confmng"].getCurConfID();
	
	var epid = window.frames["confmng"].frames["confctrl"].getCurMtID();
	
	var arr$DomItem = $(".div_popup_selview .div_list_matrix_item");
	for( var i=0; i < arr$DomItem.length; i++ )
	{
		if( arr$DomItem[i].getAttribute("selected") == "true" )
		{
			var screenIndex = arr$DomItem[i].getAttribute("no");
		};
	};
	
	var send_data='{"event":"ev_umcweb_epoper_selview_req","confid":"'+confid+"\",\"epid\":\""+epid
	+"\",\"screenIndex\":\""+screenIndex+"\",\"bSel\":\""+1+'"}';
	
	sendNty_popup_selview(send_data);
};
