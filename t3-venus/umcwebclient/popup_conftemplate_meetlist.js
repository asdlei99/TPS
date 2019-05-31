/**
 * @author xuhuaxiu
 */
var scroll_Popup_Meetlist = null;
$(document).ready(function(){
	adaptPopupPosition(410, 400);

	//添加滚动条
	scroll_Popup_Meetlist = new customBar($(".div_Popup_Meet_list_slider").get(0), $(".pannel_Popup_Meet_list").get(0), $(".drag_Popup_Meet_list").get(0));
});

function clearPopupMeetListItem()
{
	$(".div_list_item").remove(); 
};

//会议模板弹出会场列表
function setPopupMeetListItem(arrMeetList)
{
	clearPopupMeetListItem();
	
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

		var divListContent = $(".div_list_content").get(0);
		divListContent.appendChild(divListItem);

		$(divListItemNo).text(i+1);
		$(divListItemName).text(arrMeetList[i].achMeetName);
		$(divListItemNum).text(arrMeetList[i].achE164);
		$(divListItemIp).text(arrMeetList[i].achMeetIp);
	};
	
	//添加滚动条
	scroll_Popup_Meetlist.init();
};

//设置  会议模板弹出会场列表  界面标题
function setPopupMeetListTitle(strTitle)
{
	$(".div_top .div_title").text(strTitle);
};