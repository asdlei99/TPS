/**
 * @author Administrator
 */

var hostname = window.location.hostname;

var url= "http://"+hostname+"/fcgi-bin/umcwebserver.fcgi";

var g_strInvalidAliasForShow = "; / ? : @ & = + $ ， % ^ "; //提示给用户的非法字符，别名中不可以包含，否则会引起呼叫失败

var SCREEN_WIDTH = 1280;
var SCREEN_HEIGHT = 720;

$(document).ready(function(){
	//搜索框
	$(".text_search").val("搜索");
	
	$(".text_search").focus(function(){
		var strSearch = $(".text_search").val();
		if( strSearch == "搜索" )
		{
			$(".text_search").val("");
		}
	});
	
	$(".text_search").blur(function(){
		var strSearch = $(".text_search").val();
		if( strSearch == "" )
		{
			//$(".text_search").val("搜索");
		}
	});
});

/*-----------------秒转换成时间“XX小时XX秒”--------------*/
function secondToDate(second) {
    if (!second) {
        return 0;
    }
    
    var time = '';

    if (second >= 24 * 3600) {
        //time += parseInt(second / 24 * 3600) + '天';
        second %= 24 * 3600;
    }
    if (second >= 3600) {
        time += parseInt(second / 3600) + '小时';
        second %= 3600;
    }
    if (second >= 60) {
		time += parseInt(second / 60) + '分钟';
        second %= 60;
    }
    if (second > 0) {
		//time += second + '秒';
    }
    
    return time;
}

/*-----------------获取当前的日期时间 格式“yyyy-MM-dd HH:MM:SS”--------------*/
function getNowFormatDate() {
    var date = new Date();
    var seperator1 = "-";
    var seperator2 = ":";
    var month = date.getMonth() + 1;
    var strDate = date.getDate();
    if (month >= 1 && month <= 9) {
        month = "0" + month;
    }
    if (strDate >= 0 && strDate <= 9) {
        strDate = "0" + strDate;
    }
    var currentdate = date.getFullYear() + seperator1 + month + seperator1 + strDate
            + " " + date.getHours() + seperator2 + date.getMinutes()
            + seperator2 + date.getSeconds();
    return currentdate;
};

/*-----------------检验ip地址--------------*/
function checkIP(sIPAddress, str)
{
     var exp=/^([1-9]|[1-9][0-9]|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$/;
     var reg = sIPAddress.match(exp);
     var ErrMsg=str+"非法\n"+"你输入的是一个非法的IP地址段！\nIP段为：yyy.xxx.xxx.xxx（yyy为1-255，xxx为0-255)"
     var Msg="你输入的是一个合法的IP地址段"
     if(reg==null)
     {
     	top.showMessageBox(ErrMsg);
     	return false;
     }
     
     return true;
};

/*-----------------检验E164号是否有效--------------*/
//若全部为数字或[*#,]组合，返回true
function IsValidE164(strE164)
{
	if( "" == strE164){
		return false;
	}
	
	var strTemp = strE164;
	var numReg = /(\d)/gi;
	var strResNum = strTemp.replace( numReg, "" );
	if( "" == strResNum ){
		return true;
	}
	
	var symbolReg = /#|,|\*/gi;
	var strResSymbol = strResNum.replace( symbolReg, "" );
	if( "" == strResSymbol ){
		return true;
	}
	
	return false;
};

/*-----------------" ;/?:@&=+$%^；？：，"等特殊字符包含判断--------------*/
//若包含，返回false
function IsValidTPStr(strText)
{
	var SpecialChReg = /;|\/|\?|:|@|&|=|\+|\$|%|\^|；|\？|：|，/gi;
	var strRes = strText.match(SpecialChReg);
	if( strRes != null ){
		return false;
	}
	return true;
};

/*-----------------AttachEvent（支持ie、ff，并且可以传递参数）--------------*/
function AttachEvent(target, eventName, handler, argsObject)  
{  
    var eventHandler = handler;  
    if(argsObject)  
    {  
        eventHander = function(e)  
        {  
            handler.call(argsObject, e);  
        }  
    }  
    if(window.attachEvent)//IE  
        target.attachEvent("on" + eventName, eventHander );  
    else//FF  
        target.addEventListener(eventName, eventHander, false);  
};

/*-----------------阻止事件冒泡--------------*/
//得到事件
function getEvent(){
     if(window.event)    {return window.event;}
     func=getEvent.caller;
     while(func!=null){
         var arg0=func.arguments[0];
         if(arg0){
             if((arg0.constructor==Event || arg0.constructor ==MouseEvent
                || arg0.constructor==KeyboardEvent)
                ||(typeof(arg0)=="object" && arg0.preventDefault
                && arg0.stopPropagation)){
                 return arg0;
             }
         }
         func=func.caller;
     }
     return null;
};

//阻止冒泡
function stopEvent()
{
    var e=getEvent();
    if(window.event){
        //e.returnValue=false;//阻止自身行为
        e.cancelBubble=true;//阻止冒泡
     }else if(e.preventDefault){
        //e.preventDefault();//阻止自身行为
        e.stopPropagation();//阻止冒泡
     }
};

/*-----------------公共列表事件--------------*/
function onListHeadCheckboxClick(obj)
{
	var bChecked = $(obj).parents(".div_list").find(".div_list_head input:checked").length;
	
	var arr$DomItem = $(obj).parents(".div_list").find(".div_list_content input");
	for( var i = 0; i < arr$DomItem.length; i++ )
	{
		var domItem = arr$DomItem[i];
		
		if( $(domItem).css("visibility") == "hidden" )
		{
			continue;
		}
		
		if(bChecked)
		{
			domItem.checked = true;
			$(domItem).parents(".div_list_item").css('background-color','#EFF2F4');
		}
		else
		{
			domItem.checked = false;
			$(domItem).parents(".div_list_item").css('background-color','white');
		}
	}
	
	nChecked = getCurChecked(obj);
	
	if( $(".div_choose_number").length > 0 )
	{
		$(".div_choose_number").text("已选择（"+nChecked+"）");
	}
};

function onItemMouseenter(obj)
{
	$(obj).css('background-color','#007AC0');
	$(obj).children().css('color','white');
	$(obj).children().children().css('color','white');
};

function onItemMouseleave(obj)
{
	$(obj).children().css('color','black');
	$(obj).children().children().css('color','black');
	$(obj).find($("a")).css('color','#007AC0');
	
	if($(obj).children("input:checked").length > 0)
	{
		$(obj).css('background-color','#EFF2F4');
	}
	else
	{
		$(obj).css('background-color','white');
	}
	
	if( obj.getAttribute("selected") == "true" )
	{
		$(obj).css('background-color','#EFF2F4');
	}
	else
	{
		$(obj).css('background-color','white');
	}
};

function onItemClick(obj)
{
	if( $(obj).children("input").css("visibility") == "hidden" )
	{
		return;
	}
	
	if( $(obj).children("input:checked").length > 0 ){
		$(obj).children("input").get(0).checked = false;
	}
	else{
		$(obj).children("input").get(0).checked = true;
	}
	
	onItemCheckboxClick(obj);
};

/*
function onItemClick_NoChecked(obj)
{
	var arr$DomItem = $(obj).parents(".div_list").find(".div_list_item");
	for( var i = 0; i < arr$DomItem.length; i++ )
	{
		arr$DomItem[i].setAttribute("selected","false");
	}
	
	obj.setAttribute("selected","true");
	
	for( var i = 0; i < arr$DomItem.length; i++ )
	{
		if( arr$DomItem[i].getAttribute("selected") != "true" )
		{
			$(arr$DomItem[i]).css('background-color','white');
		}
	}
};
*/

function onItemCheckboxClick(obj)
{
	nChecked = getCurChecked(obj);
	nItem = $(obj).parents(".div_list").find(".div_list_item").length;
	
	if( $(".div_choose_number").length > 0  )
	{
		$(".div_choose_number").text("已选择（"+nChecked+"）");
	}
	
	if( $(obj).parents(".div_list").find(".div_list_head input").length > 0 )
	{
		if(nChecked == nItem)
		{
			$(obj).parents(".div_list").find(".div_list_head input").get(0).checked = true;
		}
		else
		{
			$(obj).parents(".div_list").find(".div_list_head input").get(0).checked = false;
		}
	}
	
	
	stopEvent();
};

function getCurChecked(obj)
{
	var nChecked = $(obj).parents(".div_list").find(".div_list_content input:checked").length;
	
	return nChecked;
};

/*获取选择items 参数obj：列表dom*/
function getCheckedItems(obj)
{
	/*
	var $Items = $(obj).find($(".div_list_item"));
	for( var i = 0; i < $Items.length; i++ )
	{
		if( $Items.find("input:checked").lenrth > 0 )
		var strIdChecked = arrItem.get(i).getAttribute("no");
		
		if( strIdChecked == strId )
		{
			return true;
		}
	}
	*/
	
	return $(obj).find(".div_list_content input:checked").parents(".div_list_item");
}

/*-----------------PopupDialog事件--------------*/
function OnPopupBtnOkClick(obj)
{
	OnPopupBtnCloseClick(obj);
};

function OnPopupBtnCloseClick(obj)
{
	top.$(".div_popup iframe").get(0).setAttribute("src","");
	
	top.$(".div_popupdialogbg").css("visibility","hidden");
	top.$(".div_popup").css("visibility","hidden");
};

/*会场列表*/
/*被选择的列表*/
//清空所有条目
function clearListItem_MeettingroomBechecked()
{
	$(".div_list_meettingroom_bechecked .div_list_item").remove(); 
};

//添加一条条目
//有全局在线状态
function addListItem_MeettingroomBechecked(strId,strOnline,strType,strName,strNumber,strIp)
{
	var divListItem = document.createElement("div");
	divListItem.className="div_list_item";
	divListItem.setAttribute("onmouseenter","onItemMouseenter(this)");
	divListItem.setAttribute("onmouseleave","onItemMouseleave(this)");
	divListItem.setAttribute("onclick","onItemClick(this)");
	
	var inputListItemCheckbox = document.createElement("input");
	inputListItemCheckbox.type="checkbox";
	inputListItemCheckbox.setAttribute("onclick","onItemCheckboxClick(this)");

	var divListItemOnline = document.createElement("div");
	divListItemOnline.className="div_list_item_online";
	
	var divListItemType = document.createElement("div");
	divListItemType.className="div_list_item_type";
	
	var divListItemName = document.createElement("div");
	divListItemName.className="div_list_item_name";
	
	var divListItemNumber = document.createElement("div");
	divListItemNumber.className="div_list_item_number";
	
	var divListItemIp = document.createElement("div");
	divListItemIp.className="div_list_item_ip";

	
	divListItem.appendChild(inputListItemCheckbox);
	divListItem.appendChild(divListItemOnline);
	divListItem.appendChild(divListItemType);
	divListItem.appendChild(divListItemName);
	divListItem.appendChild(divListItemNumber);
	divListItem.appendChild(divListItemIp);

	var divListContent = $(".div_list_meettingroom_bechecked .div_list_content").get(0);

	divListContent.appendChild(divListItem);
	
	$(divListItemOnline).text(strOnline);
	$(divListItemType).text(strType);
	$(divListItemName).text(strName);
	$(divListItemNumber).text(strNumber);
	$(divListItemIp).text(strIp);
	
	divListItem.setAttribute("no",strId);
};

//添加一条条目
//无状态
function addListItem_MeettingroomBechecked_nostate(strId,strName,strNumber,strIp)
{
	var divListItem = document.createElement("div");
	divListItem.className="div_list_item";
	divListItem.setAttribute("onmouseenter","onItemMouseenter(this)");
	divListItem.setAttribute("onmouseleave","onItemMouseleave(this)");
	divListItem.setAttribute("onclick","onItemClick(this)");
	
	var inputListItemCheckbox = document.createElement("input");
	inputListItemCheckbox.type="checkbox";
	inputListItemCheckbox.setAttribute("onclick","onItemCheckboxClick(this)");
	
	var divListItemName = document.createElement("div");
	divListItemName.className="div_list_item_name";
	
	var divListItemNumber = document.createElement("div");
	divListItemNumber.className="div_list_item_number";
	
	var divListItemIp = document.createElement("div");
	divListItemIp.className="div_list_item_ip";

	
	divListItem.appendChild(inputListItemCheckbox);
	divListItem.appendChild(divListItemName);
	divListItem.appendChild(divListItemNumber);
	divListItem.appendChild(divListItemIp);

	var divListContent = $(".div_list_meettingroom_bechecked .div_list_content").get(0);

	divListContent.appendChild(divListItem);
	
	$(divListItemName).text(strName);
	$(divListItemNumber).text(strNumber);
	$(divListItemIp).text(strIp);
	
	divListItem.setAttribute("no",strId);
};

/*选择的列表*/
//清空所有条目
function clearListItem_MeettingroomChecked()
{
	$(".div_list_meettingroom_checked .div_list_item").remove(); 
};

//添加一条条目
//有全局在线状态
function addListItem_MeettingroomChecked(strId,strOnline,strType,strName,strNumber,strIp)
{
	var divListItem = document.createElement("div");
	divListItem.className="div_list_item";
	divListItem.setAttribute("onmouseenter","onItemMouseenter(this)");
	divListItem.setAttribute("onmouseleave","onItemMouseleave(this)");
	divListItem.setAttribute("onclick","onItemClick(this)");
	
	var inputListItemCheckbox = document.createElement("input");
	inputListItemCheckbox.type="checkbox";
	inputListItemCheckbox.setAttribute("onclick","onItemCheckboxClick(this)");

	var divListItemOnline = document.createElement("div");
	divListItemOnline.className="div_list_item_online";
	
	var divListItemType = document.createElement("div");
	divListItemType.className="div_list_item_type";
	
	var divListItemName = document.createElement("div");
	divListItemName.className="div_list_item_name";
	
	var divListItemNumber = document.createElement("div");
	divListItemNumber.className="div_list_item_number";
	
	var divListItemIp = document.createElement("div");
	divListItemIp.className="div_list_item_ip";

	
	divListItem.appendChild(inputListItemCheckbox);
	divListItem.appendChild(divListItemOnline);
	divListItem.appendChild(divListItemType);
	divListItem.appendChild(divListItemName);
	divListItem.appendChild(divListItemNumber);
	divListItem.appendChild(divListItemIp);

	var divListContent = $(".div_list_meettingroom_checked .div_list_content").get(0);

	divListContent.appendChild(divListItem);
	
	$(divListItemOnline).text(strOnline);
	$(divListItemType).text(strType);
	$(divListItemName).text(strName);
	$(divListItemNumber).text(strNumber);
	$(divListItemIp).text(strIp);
	
	divListItem.setAttribute("no",strId);
};

//添加一条条目
//无状态
function addListItem_MeettingroomChecked_nostate(strId,strName,strNumber,strIp)
{
	var divListItem = document.createElement("div");
	divListItem.className="div_list_item";
	divListItem.setAttribute("onmouseenter","onItemMouseenter(this)");
	divListItem.setAttribute("onmouseleave","onItemMouseleave(this)");
	divListItem.setAttribute("onclick","onItemClick(this)");
	
	var inputListItemCheckbox = document.createElement("input");
	inputListItemCheckbox.type="checkbox";
	inputListItemCheckbox.setAttribute("onclick","onItemCheckboxClick(this)");
	
	var divListItemName = document.createElement("div");
	divListItemName.className="div_list_item_name";
	
	var divListItemNumber = document.createElement("div");
	divListItemNumber.className="div_list_item_number";
	
	var divListItemIp = document.createElement("div");
	divListItemIp.className="div_list_item_ip";

	
	divListItem.appendChild(inputListItemCheckbox);
	divListItem.appendChild(divListItemName);
	divListItem.appendChild(divListItemNumber);
	divListItem.appendChild(divListItemIp);

	var divListContent = $(".div_list_meettingroom_checked .div_list_content").get(0);

	divListContent.appendChild(divListItem);
	
	$(divListItemName).text(strName);
	$(divListItemNumber).text(strNumber);
	$(divListItemIp).text(strIp);
	
	divListItem.setAttribute("no",strId);
};

function hasSameItem(strId)
{
	var arrItem = $(".div_list_meettingroom_checked .div_list_item");
	for( var i = 0; i < arrItem.length; i++ )
	{
		var strIdChecked = arrItem.get(i).getAttribute("no");
		
		if( strIdChecked == strId )
		{
			return true;
		}
	}
	
	return false;
};

//type:"globlestate","nostate"
function CheckOne(type)
{
	var arrItem = $(".div_list_meettingroom_bechecked .div_list_item");
	for( var i = 0; i < arrItem.length; i++ )
	{
		var domItem = arrItem[i];
		if($(domItem).children("input:checked").length)
		{
			if(type == "globlestate")
			{
				var strId = domItem.getAttribute("no");
				var strOnline = $(domItem).children(".div_list_item_online").text();
				var strType = $(domItem).children(".div_list_item_type").text();
				var strName = $(domItem).children(".div_list_item_name").text();
				var strNumber = $(domItem).children(".div_list_item_number").text();
				var strIp = $(domItem).children(".div_list_item_ip").text();
				
				if( hasSameItem(strId) == false )
				{
					addListItem_MeettingroomChecked(strId,strOnline,strType,strName,strNumber,strIp);
				}
			}
			else if(type == "nostate")
			{
				var strId = domItem.getAttribute("no");
				var strName = $(domItem).children(".div_list_item_name").text();
				var strNumber = $(domItem).children(".div_list_item_number").text();
				var strIp = $(domItem).children(".div_list_item_ip").text();
				
				if( hasSameItem(strId) == false )
				{
					addListItem_MeettingroomChecked_nostate(strId,strName,strNumber,strIp);
				}
			}
		}
	}
};

function CheckAll(type)
{
	var $domItem = $(".div_list_meettingroom_bechecked .div_list_item");
	for( var i = 0; i < $domItem.length; i++ )
	{
		var domItem = $domItem[i];
		if( $(domItem).find("input").css("visibility") == "hidden" )
		{
			continue;
		}
		
		if(type == "globlestate")
		{
			var strId = domItem.getAttribute("no");
			var strOnline = $(domItem).children(".div_list_item_online").text();
			var strType = $(domItem).children(".div_list_item_type").text();
			var strName = $(domItem).children(".div_list_item_name").text();
			var strNumber = $(domItem).children(".div_list_item_number").text();
			var strIp = $(domItem).children(".div_list_item_ip").text();
			
			if( hasSameItem(strId) == false )
			{
				addListItem_MeettingroomChecked(strId,strOnline,strType,strName,strNumber,strIp);
			}
		}
		else (type == "nostate")
		{
			var strId = domItem.getAttribute("no");
			var strName = $(domItem).children(".div_list_item_name").text();
			var strNumber = $(domItem).children(".div_list_item_number").text();
			var strIp = $(domItem).children(".div_list_item_ip").text();
			
			if( hasSameItem(strId) == false )
			{
				addListItem_MeettingroomChecked_nostate(strId,strName,strNumber,strIp);
			}
		}
	}
};

function UncheckOne(type)
{
	$(".div_list_meettingroom_checked .div_list_item").each(function(index,element){
		if($(this).children("input:checked").length)
		{
			$(this).remove(); 
		}
	});
};

function UncheckAll(type)
{
	clearListItem_MeettingroomChecked();
};

//伸缩框
//点击伸缩框的tab
function onClickStretchTab(obj)
{
	var $dom_div_stretch_content = $(obj).parent(".div_stretch").children(".div_stretch_content");
	var strDisplay = $dom_div_stretch_content.css("display");
	
	$(".div_stretch_content").css("display", "none");
	$(".font_stretch_tab").text(">");
	
	if( strDisplay == "none" )
	{
		$dom_div_stretch_content.css("display", "block");
		$(obj).children(".font_stretch_tab").text("∨");
	}
	else
	{
		$dom_div_stretch_content.css("display", "none");
		$(obj).children(".font_stretch_tab").text(">");
	}
};

//列表操作：上移、下移、置顶、置底、删除
//删除
//注：该函数返回删除操作后应剩余的条目信息
function getRestItems(objlist)
{
	var $domItems = $(objlist).find(".div_list_item");
	var nItems = $domItems.length;
	
	var arrListInfo = new Array();
	for( var i = 0; i < nItems; i++ )
	{
		var domItem = $domItems[i];
		if( $(domItem).children("input:checked").length == 0 )
		{
			var strId = domItem.getAttribute("no");
			var strName = $(domItem).children(".div_list_item_name").text();
			var strNumber = $(domItem).children(".div_list_item_number").text();
			var strIp = $(domItem).children(".div_list_item_ip").text();

			var strItemInfo = new Object();
			strItemInfo.epId = strId;
			strItemInfo.achMeetName = strName;
			strItemInfo.achE164 = strNumber;
			strItemInfo.achMeetIp = strIp;
			arrListInfo.push(strItemInfo);
		}
	}
	
	return arrListInfo;
};

//上移
function moveUp(objlist)
{	
	var $domItems = $(objlist).find(".div_list_item");
	var nItems = $domItems.length;
	for( var i = 0; i < nItems; i++ )
	{
		var domItem = $domItems[i];
		if( $(domItem).find("input:checked").length > 0 )
		{
			var domItemCur = domItem;
			if( i == 0 ){
				alert("already top");
				break;
			}
			var itemPre = $domItems[i-1];

			swapElement(itemPre, domItemCur);

			break;
		}
	}
};

//下移
function moveDown(objlist)
{
	var $domItems = $(objlist).find(".div_list_item");
	var nItems = $domItems.length;
	for( var i = 0; i < nItems; i++ )
	{
		var domItem = $domItems[i];
		if( $(domItem).find("input:checked").length > 0 )
		{
			var domItemCur = domItem;
			if( i == nItems - 1 ){
				alert("already bottom");
				break;
			}
			var itemNext = $domItems[i+1];

			swapElement(domItemCur, itemNext);

			break;
		}
	}	
};

//置顶
function setTop(objlist)
{
	var $domItems = $(objlist).find(".div_list_item");
	var nItems = $domItems.length;
	for( var i = 0; i < nItems; i++ )
	{
		var domItem = $domItems[i];
		if( $(domItem).find("input:checked").length > 0 )
		{
			var domItemCur = domItem;
			if( i == 0 ){
				alert("already top");
				break;
			}
			var itemTop = $domItems[0];

			insertElement(domItemCur, itemTop, "before");

			break;
		}
	}		
};

//置底
function setBottom(objlist)
{
	var $domItems = $(objlist).find(".div_list_item");
	var nItems = $domItems.length;
	for( var i = 0; i < nItems; i++ )
	{
		var domItem = $domItems[i];
		if( $(domItem).find("input:checked").length > 0 )
		{
			var domItemCur = domItem;
			if( i == nItems - 1 ){
				alert("already bottom");
				break;
			}
			var itemBottom = $domItems[nItems-1];

			insertElement(domItemCur, itemBottom, "after");

			break;
		}
	}		
};

function insertbefore(nodeInsert, nodeTo)
{
	if(nodeInsert.insertAdjacentElement){
		nodeTo.insertAdjacentElement('beforeBegin', nodeInsert);
	}else{
		nodeTo.parentNode.insertBefore(nodeInsert, nodeTo);
	}
};

function insertafter(nodeInsert, nodeTo)
{
	if(nodeInsert.insertAdjacentElement){
		nodeTo.insertAdjacentElement('afterEnd', nodeInsert);
	}else{
		nodeTo.parentNode.insertAfter(nodeInsert, nodeTo);
	}
};

function swapElement(dom_1,dom_2)
{
	var obj = document.createElement("a"); 
	insertbefore(obj, dom_2);
	insertbefore(dom_2, dom_1);
	insertbefore(dom_1, obj);
	
	if ( obj && obj.parentNode ){
		obj.parentNode.removeChild(obj);  
	}else{
		alert("obj already del");
	}
};

function insertElement(domInsert,domTo,strType)
{
	var obj = document.createElement("a"); 
	if( "before" == strType ){
		insertbefore(obj, domTo);
		insertbefore(domInsert, obj);
	}else if( "after" == strType){
		insertafter(obj, domTo);
		insertafter(domInsert, obj);
	}else{
		alert("no insert type");
	}
	
	if ( obj && obj.parentNode ){
		obj.parentNode.removeChild(obj);  
	}else{
		alert("obj already del");
	}
};

//设置列表操作按键颜色
function setOperButtonColor()
{
	$("a").each(function(index){
		if( "true" == $(this).attr("unable") ){
			$(this).css("color", "#D7D7D7");
		}else{
			$(this).css("color", "#3FA9F5");
		}
	});
};

//显示弹出框
function showPopup(page)
{
	top.$(".div_popup iframe").get(0).setAttribute("src",page);
	
	top.$(".div_popupdialogbg").css("visibility","visible");
	top.$(".div_popup").css("visibility","visible");
};

//弹出框自适应分辨率
function adaptPopupPosition(width,height)
{
	var strWidth = width + "px";
	var strHeight = height + "px";
	
	top.$(".div_popup").css("width",strWidth);
	top.$(".div_popup").css("height",strHeight);
	
	var strMarginLeft = (SCREEN_WIDTH - width)/2 + "px";
	var strMarginTop = (SCREEN_HEIGHT - height)/2 + "px";
	
	top.$(".div_popup").css("margin-left",strMarginLeft);
	top.$(".div_popup").css("margin-top",strMarginTop);
};
