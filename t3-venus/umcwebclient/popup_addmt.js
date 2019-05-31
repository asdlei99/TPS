/**
 * @author shicheng
 */
var arrCurGroupID = new Array;
arrCurGroupID[0] = 1;		//当前进入的组
var scroll_bechecked = null;
var scroll_checked = null;

$(document).ready(function(){
	top.$(".div_popup").css("width","720px");
	top.$(".div_popup").css("height","540px");
	
	//添加滚动条
	scroll_bechecked = new customBar($(".div_middle_bechecked .slider").get(0), $(".div_middle_bechecked .pannel").get(0), $(".div_middle_bechecked .drag").get(0));
	scroll_checked = new customBar($(".div_middle_checked .slider").get(0), $(".div_middle_checked .pannel").get(0), $(".div_middle_checked .drag").get(0));
	
	send_data="{\"event\":\"ev_umcweb_addrbook_itemgroup_search_req\",\"gid\":\"1\",\"search\":\"\"}";
	sendNty(send_data);
	
	$(".btn_back").click(function(){
		$(".text_search").val("");
		
		arrCurGroupID.pop();
		
		strTemp = $(".div_level").text();
		strTemp = strTemp.substring(0,strTemp.lastIndexOf(" > "));
		$(".div_level").text(strTemp);
		
		getAddrbookInfo(arrCurGroupID[arrCurGroupID.length-1]);
		
		if(arrCurGroupID.length == 1)
		{
			$(".btn_back")[0].setAttribute("disabled","disabled");
		}
	});
	
	$(".img_search").click(function(){
		getAddrbookInfo(arrCurGroupID[arrCurGroupID.length-1]);
	});
});

function updListBechecked(data)
{
	$(".div_middle_bechecked .div_list_item").remove(); 
	
	var arrGroup=new Array();
				
	for (var i=0; i < data.groupcount; i++) {
		arrGroup.push(data.groupitems[i]);
	};
	
	for (var i=0; i < arrGroup.length; i++) {
		var divListItem = document.createElement("div");
		divListItem.className="div_list_item";
		divListItem.setAttribute("onmouseenter","onItemMouseenter(this)");
		divListItem.setAttribute("onmouseleave","onItemMouseleave(this)");
		divListItem.setAttribute("onclick","onListItemClick(this)");
		
		var checkboxItemNo = document.createElement("input");
		checkboxItemNo.type="checkbox";
		checkboxItemNo.setAttribute("style","visibility: hidden;");
		
		var divListItemOnline = document.createElement("div");
		divListItemOnline.className="div_list_item_online";
	
		var divListItemName = document.createElement("div");
		divListItemName.className="div_list_item_name";
	
		
		divListItem.appendChild(checkboxItemNo);
		divListItem.appendChild(divListItemOnline);
		divListItem.appendChild(divListItemName);
		divListItem.setAttribute("no",arrGroup[i].id);
		
	
		var divListContent = $(".div_middle_bechecked .div_list_content").get(0);
	
		divListContent.appendChild(divListItem);
		
		$(divListItemOnline).text("--");
		$(divListItemName).text(arrGroup[i].name);
	};
	
	var arrItem=new Array();
				
	for (var i=0; i < data.count; i++) {
		arrItem.push(data.items[i]);
	};
	
	
	for (var i=0; i < arrItem.length; i++) {
		var divListItem = document.createElement("div");
		divListItem.className="div_list_item";
		divListItem.setAttribute("onmouseenter","onItemMouseenter(this)");
		divListItem.setAttribute("onmouseleave","onItemMouseleave(this)");
		divListItem.setAttribute("onclick","onItemClick(this)");
		
		var checkboxItemNo = document.createElement("input");
		checkboxItemNo.type="checkbox";
		checkboxItemNo.setAttribute("onclick","onItemCheckboxClick(this)");
		
		var divListItemOnline = document.createElement("div");
		divListItemOnline.className="div_list_item_online";
		
		var divListItemType = document.createElement("div");
		divListItemType.className="div_list_item_type";
	
		var divListItemName = document.createElement("div");
		divListItemName.className="div_list_item_name";
		
		var divListItemIp = document.createElement("div");
		divListItemIp.className="div_list_item_ip";
		
		var divListItemNumber = document.createElement("div");
		divListItemNumber.className="div_list_item_number";
	
		
		divListItem.appendChild(checkboxItemNo);
		divListItem.appendChild(divListItemOnline);
		divListItem.appendChild(divListItemType);
		divListItem.appendChild(divListItemName);
		divListItem.appendChild(divListItemIp);
		divListItem.appendChild(divListItemNumber);
		divListItem.setAttribute("no",arrItem[i].id);
	
		var divListContent = $(".div_middle_bechecked .div_list_content").get(0);
	
		divListContent.appendChild(divListItem);
		
		var strOnline;
		if(arrItem[i].online=="1")
		{
			strOnline="在线";
		}
		else
		{
			strOnline="不在线";
		}
		$(divListItemOnline).text(strOnline);
		
		var strType;
		if(arrItem[i].type=="1" || arrItem[i].type=="2")
		{
			strType="sip";
		}
		else if(arrItem[i].type=="0")
		{
			strType="本地";
		}
		else
		{
			strType="gk";
		}
		$(divListItemType).text(strType);
		$(divListItemName).text(arrItem[i].name);
		$(divListItemIp).text(arrItem[i].ip);
		$(divListItemNumber).text(arrItem[i].number);
	};
	
	//添加滚动条
	scroll_bechecked.init();
};

function onListItemClick(obj)
{
	onItemClick(obj);
	
	if( $(obj).children("input").css("visibility") == "hidden" )
	{
		$(".text_search").val("");
		
		arrCurGroupID.push(parseInt(obj.getAttribute("no")));
		
		strTemp = $(".div_level").text();
		strTemp = strTemp + " > " + $(obj).children(".div_list_item_name").text();
		$(".div_level").text(strTemp);
		
		getAddrbookInfo(arrCurGroupID[arrCurGroupID.length-1]);
		
		$(".btn_back")[0].removeAttribute("disabled");
	}
};

function getAddrbookInfo(gid)
{
	var strSearch = $(".text_search").val();
	if(strSearch == "搜索")
	{
		strSearch = "";
	}
	send_data="{\"event\":\"ev_umcweb_addrbook_itemgroup_search_req\",\"gid\":\""+gid+"\",\"search\":\""+strSearch+"\"}";
	sendNty(send_data);
};

function onBtnCheckOneClick()
{
	CheckOne("globlestate");
	
	scroll_checked.init();
};

function onBtnCheckAllClick()
{
	CheckAll("globlestate");
	
	scroll_checked.init();
};

function onBtnUncheckOneClick()
{
	UncheckOne("globlestate");
	
	scroll_checked.init();
};

function onBtnUncheckAllClick()
{
	UncheckAll("globlestate");
	
	scroll_checked.init();
};

function sendNty(send_data)
{
    $.post(url,send_data,function(data,ts){
    	//返回通知消息
		switch(data.event){
			case "ev_umcweb_addrbook_itemgroup_search_res":{
				updListBechecked(data);
				break;
			}
			default:{
			    break;
			}
		}
    },'json');
};

function OnPopupAddmtBtnOkClick(obj)
{
	OnPopupBtnCloseClick(obj);
	
	var $domItem = $(".div_list_meettingroom_checked .div_list_item");
	for( var i = 0; i < $domItem.length; i++ )
	{
		var domItem = $domItem[i];
		
		var strId = domItem.getAttribute("no");
		var strType;
		if( $(domItem).children(".div_list_item_type").text() == "sip" )
		{
			strType = "1";
		}
		else
		{
			strType = "2";
		}
		var strName = $(domItem).children(".div_list_item_name").text();
		var strNumber = $(domItem).children(".div_list_item_number").text();
		var strIp = $(domItem).children(".div_list_item_ip").text();
		
		top.frames["conftemplate"].frames["conftemplateEdit"].addConftempMeetListItem( 
		"meetlist", strId, strName, strNumber, strIp, "", strType );
	}
};
