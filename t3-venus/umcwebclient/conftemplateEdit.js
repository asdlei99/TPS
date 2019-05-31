/**
 * @author xuhuaxiu
 */
var send_data = "";
var scroll_Settings = null;
var scroll_Polling = null;
var scroll_Discuss = null;
var scroll_MeetList = null;

$(document).ready(function(){
	//添加滚动条
	scroll_Settings = new customBar($(".div_ConfSettings_content").get(0), $(".pannel_ConfSettings").get(0), $(".drag_ConfSettings").get(0));
	scroll_Polling = new customBar($(".div_Polling_list_content .div_list_content").get(0), $(".pannel_Polling_list").get(0), $(".drag_Polling_list").get(0));
	scroll_Discuss = new customBar($(".div_Discuss_list_content .div_list_content").get(0), $(".pannel_Discuss_list").get(0), $(".drag_Discuss_list").get(0));
	scroll_MeetList = new customBar($(".div_Meet_list_content .div_list_content").get(0), $(".pannel_Meet_list").get(0), $(".drag_Meet_list").get(0));

	//界面初始化
	showConftemplateEditInitLogic();
	
	var conftapmenu = document.getElementsByName("btnTap");		
	//点击显示基本设置界面
	$(".btnConfSettings").click(function(){
		for (var i=0; i < conftapmenu.length; i++) {
			conftapmenu[i].disabled = false;
		};
		$(this).attr("disabled", "disabled");
		
		$("#div_ConfSettings_Logic").css("display", "block");
		$("#div_ConfPolling_Logic").css("display", "none");
		$("#div_ConfDiscuss_Logic").css("display", "none");
		
		$(".div_MeetOper_handle").css("display", "none");
		
		clearMeetListItemSelState();
	});
	
	//点击显示会议轮询界面
	$(".btnConfPolling").click(function(){
		for (var i=0; i < conftapmenu.length; i++) {
			conftapmenu[i].disabled = false;
		};
		$(this).attr("disabled", "disabled");

		$("#div_ConfSettings_Logic").css("display", "none");
		$("#div_ConfPolling_Logic").css("display", "block");
		$("#div_ConfDiscuss_Logic").css("display", "none");
		
		$(".div_MeetOper_handle").css("display", "block");
		
		clearMeetListItemSelState();
	});
	
	//点击显示会议讨论界面
	$(".btnConfDiscuss").click(function(){
		for (var i=0; i < conftapmenu.length; i++) {
			conftapmenu[i].disabled = false;
		};
		$(this).attr("disabled", "disabled");
		
		$("#div_ConfSettings_Logic").css("display", "none");
		$("#div_ConfPolling_Logic").css("display", "none");
		$("#div_ConfDiscuss_Logic").css("display", "block");
		
		$(".div_MeetOper_handle").css("display", "block");
		
		clearMeetListItemSelState();
	});
	
	//保存
	$(".btnSave").click(function(){
		saveConfTemplateInfo();
	});
	
	//取消
	$(".btnCancel").click(function(){
		parent.showCurPage("conftemplateList");
	});
	
	/*************************************基本设置界面*************************************/
	//点击开启AES加密
	$("#switchStartEncrypt").unbind("click").click(function(){
		var self=$(this);
		if( self.attr("class") == "switchbtnOff" ){
			self.removeClass("switchbtnOff").addClass("switchbtnOpen");
		}
		else if( self.attr("class") == "switchbtnOpen" ){
			self.removeClass("switchbtnOpen").addClass("switchbtnOff");
		}
		
		setAESEncryptState();
	});
	
	//AES密钥自定义输入框
	$(".textAESCustom").val("自定义");
	
	$(".textAESCustom").focus(function(){
		var strCustom = $(".textAESCustom").val();
		if( strCustom == "自定义" )
		{
			$(".textAESCustom").val("");
		}
	});
	
	$(".textAESCustom").blur(function(){
		var strCustom = $(".textAESCustom").val();
		if( strCustom == "" )
		{
			//$(".textAESCustom").val("自定义");
		}
	});
	
	/*************************************与会会场界面*************************************/
	//临时添加会场
	$(".btnTempInvite").click(function(){
		top.$(".div_popupdialogbg").css("visibility","visible");
		top.$(".div_popup_tempaddmt").css("visibility","visible");
	});
	
	//添加会成员
	$(".btnAddMeet").click(function(){
		showPopup("popup_addmt.html");
	});

	//删除会成员
	$(".btnDelMeet").click(function(){
		var arrRestItems = getRestItems( $(".div_Meet_list")[0] );
		updMeetListItem( arrRestItems );
	});
	
	//搜索
	$(".img_search").unbind("click").click(function(){
		showSearchRestItems();
	});
	
	/*************************************会议轮询界面*************************************/
	//点击开启轮询
	$("#switchStartPolling").unbind("click").click(function(){
		var self=$(this);
		if( self.attr("class") == "switchbtnOff" ){
			self.removeClass("switchbtnOff").addClass("switchbtnOpen");
		}
		else if( self.attr("class") == "switchbtnOpen" ){
			self.removeClass("switchbtnOpen").addClass("switchbtnOff");
		}
	});
	
	//轮询列表操作
	$(".divPollingOper .aPollingSetTop").unbind("click").click(function(){
		if( "false" == $(this).attr("unable") ){
			setTop($(".div_Polling_list")[0]);
		}else{
			return false;
		}
	});
	
	$(".divPollingOper .aPollingMoveUp").unbind("click").click(function(){
		if( "false" == $(this).attr("unable") ){
			moveUp($(".div_Polling_list")[0]);
		}else{
			return false;
		}
	});
	
	$(".divPollingOper .aPollingMoveDown").unbind("click").click(function(){
		if( "false" == $(this).attr("unable") ){
			moveDown($(".div_Polling_list")[0]);
		}else{
			return false;
		}
	});
	
	$(".divPollingOper .aPollingSetBottom").unbind("click").click(function(){
		if( "false" == $(this).attr("unable") ){
			setBottom($(".div_Polling_list")[0]);
		}else{
			return false;
		}
	});
	
	$(".divPollingOper .aPollingRemove").unbind("click").click(function(){
		if( "false" == $(this).attr("unable") ){
			var arrRestItems = getRestItems( $(".div_Polling_list")[0] );
			updPollingListItem( arrRestItems );
		}else{
			return false;
		}
	});
	
	/*************************************会议讨论界面*************************************/
	//点击开启讨论
	$("#switchStartDiscuss").unbind("click").click(function(){
		var self=$(this);
		if( self.attr("class") == "switchbtnOff" ){
			self.removeClass("switchbtnOff").addClass("switchbtnOpen");
		}
		else if( self.attr("class") == "switchbtnOpen" ){
			self.removeClass("switchbtnOpen").addClass("switchbtnOff");
		}
	});
	
	//讨论列表操作
	$(".divDiscussOper .aDiscussRemove").unbind("click").click(function(){
		if( "false" == $(this).attr("unable") ){
			var arrRestItems = getRestItems( $(".div_Discuss_list")[0] );
			updDiscussListItem( arrRestItems );
		}else{
			return false;
		}
	});
});

/*********************界面显示处理**************************************************************************/

function onShowWnd()
{
	var strConfTempID = parent.getCurConfTempID();
	if( strConfTempID > "0" ){
		//编辑
		RefreshConftempInfoReq(strConfTempID);
		RefreshConftempMeetNameListReq(strConfTempID);
		RefreshConftempPollingListReq(strConfTempID);
		RefreshConftempDiscussListReq(strConfTempID);
		showConfSettingsLogic();
	}else if( strConfTempID == "0" ){
		//新建
		ConfBasUsedNtyReq();
	}else{
		//error
		parent.showCurPage("conftemplateList");
		return;
	}
};

//显示基本设置界面
function showConfSettingsLogic()
{
	var conftapmenu = document.getElementsByName("btnTap");
	for (var i=0; i < conftapmenu.length; i++) {
		conftapmenu[i].disabled = false;
	};
	$(".btnConfSettings").attr("disabled", "disabled");

	$("#div_ConfSettings_Logic").css("display", "block");
	//js中设置轮询、讨论界面隐藏，否则轮询、讨论界面滚动条失效
	$("#div_ConfPolling_Logic").css("display", "none");
	$("#div_ConfDiscuss_Logic").css("display", "none");
	
	$(".div_MeetOper_handle").css("display", "none");
};

//显示会议模板编辑界面初始化状态
function showConftemplateEditInitLogic()
{
	//默认显示基本设置界面
	showConfSettingsLogic();
	
	//初始化界面显示内容
	//基本设置页面
	$(".div_ConfSettings_content input:text").each(function(index,element){
		this.value = "";
	});
	
	$("#switchStartEncrypt").removeClass("switchbtnOpen").addClass("switchbtnOff");
	setAESEncryptState();	
	$(".divAESEncrypt .radioAESDefault").attr("checked", true);
	$(".textAESCustom").val("");

	clearMeetListItem();
	
	//会议轮询页面
	$("#switchStartPolling").removeClass("switchbtnOff").addClass("switchbtnOpen");
	$(".textPollingTime").val("20  秒");
	clearPollingListItem();
	
	//会议讨论页面
	$("#switchStartDiscuss").removeClass("switchbtnOpen").addClass("switchbtnOff");
	clearDiscussListItem();
};

//控制AES密钥显示状态
function setAESEncryptState()
{
	if( $("#switchStartEncrypt").attr("class") == "switchbtnOff" ){
		$(".divAESEncrypt .radioAESDefault").attr("disabled","disabled");
		$(".divAESEncrypt .radioAESCustom").attr("disabled","disabled");
		$(".divAESEncrypt .textAESCustom").attr("disabled","disabled");
	}
	else if( $("#switchStartEncrypt").attr("class") == "switchbtnOpen" ){
		$(".divAESEncrypt .radioAESDefault").removeAttr("disabled");
		$(".divAESEncrypt .radioAESCustom").removeAttr("disabled");
		$(".divAESEncrypt .textAESCustom").removeAttr("disabled");
	}
};

/**********会场操作相关**********************************************************************/

function onBtnCheckAllClick()
{
	var strCurList = "";
	if( "block" == $("#div_ConfPolling_Logic").css("display") ){
		strCurList = "pollinglist";
	}else if( "block" == $("#div_ConfDiscuss_Logic").css("display") ){
		strCurList = "discusslist";
	}else{
		return;
	}
	
	var arrItem = $(".div_Meet_list .div_list_item");
	for( var i = 0; i < arrItem.length; i++ )
	{
		var domItem = arrItem[i];

		var strId = domItem.getAttribute("no");
		var strName = $(domItem).children(".div_list_item_name").text();
		var strNumber = $(domItem).children(".div_list_item_number").text();
		var strIp = $(domItem).children(".div_list_item_ip").text();
		
		if( hasSameId(strId) == false )
		{
			addConftempMeetListItem(strCurList, strId, strName, strNumber, strIp, "", "");
		}
	}
};

function onBtnCheckOneClick()
{
	var strCurList = "";
	if( "block" == $("#div_ConfPolling_Logic").css("display") ){
		strCurList = "pollinglist";
	}else if( "block" == $("#div_ConfDiscuss_Logic").css("display") ){
		strCurList = "discusslist";
	}else{
		return;
	}
	
	var arrItem = $(".div_Meet_list .div_list_item");
	for( var i = 0; i < arrItem.length; i++ )
	{
		var domItem = arrItem[i];
		if( $(domItem).children("input:checked").length > 0 )
		{
			var strId = domItem.getAttribute("no");
			var strName = $(domItem).children(".div_list_item_name").text();
			var strNumber = $(domItem).children(".div_list_item_number").text();
			var strIp = $(domItem).children(".div_list_item_ip").text();
			
			if( hasSameId(strId) == false )
			{
				addConftempMeetListItem(strCurList, strId, strName, strNumber, strIp, "", "");
			}
		}
	}
};

function onBtnUncheckOneClick()
{
	var arrItem = "";
	if( "block" == $("#div_ConfPolling_Logic").css("display") ){
		arrItem = $(".div_Polling_list .div_list_item");
	}else if( "block" == $("#div_ConfDiscuss_Logic").css("display") ){
		arrItem = $(".div_Discuss_list .div_list_item");
	}else{
		return;
	}
	
	for( var i = 0; i < arrItem.length; i++ )
	{
		var domItem = arrItem[i];
		if( $(domItem).children("input:checked").length > 0 )
		{
			$(domItem).remove();
		}
	}

	if( "block" == $("#div_ConfPolling_Logic").css("display") ){
		scroll_Polling.init();
		clearPollingListItemSelState();
	}else if( "block" == $("#div_ConfDiscuss_Logic").css("display") ){
		scroll_Discuss.init();
		clearDiscussListItemSelState();
	}else{
		return;
	}
};

function onBtnUncheckAllClick()
{
	var strCurList = "";
	if( "block" == $("#div_ConfPolling_Logic").css("display") ){
		clearPollingListItem();
	}else if( "block" == $("#div_ConfDiscuss_Logic").css("display") ){
		clearDiscussListItem();
	}else{
		return;
	}
};

//条目Id是否重复
function hasSameId(strId)
{
	var arrItem = "";
	if( "block" == $("#div_ConfPolling_Logic").css("display") ){
		arrItem = $(".div_Polling_list .div_list_item");
	}else if( "block" == $("#div_ConfDiscuss_Logic").css("display") ){
		arrItem = $(".div_Discuss_list .div_list_item");
	}else{
		return;
	}
	
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

//条目信息是否重复(名称、e164号、ip 任一重复即为重复条目)
function hasSameMeetItem(strMeetName, strE164, strMeetIp)
{
	var $domItems = $( $(".div_Meet_list")[0] ).find(".div_list_item");
	var nItems = $domItems.length;
	
	for( var i = 0; i < nItems; i++ )
	{
		var domItem = $domItems[i];

		var strName = $(domItem).children(".div_list_item_name").text();
		var strNumber = $(domItem).children(".div_list_item_number").text();
		var strIp = $(domItem).children(".div_list_item_ip").text();
		
		if( strMeetName != "" && strMeetName == strName ){
			return true;
		}
		if( strE164 != "" && strE164 == strNumber ){
			return true;
		}
		if( strMeetIp != "" && strMeetIp == strIp ){
			return true;
		}
	}

	return false;
};

//添加会议模板中  与会会场、会议轮询、会议讨论  列表条目
//strListType -> "meetlist"; "pollinglist"; "discusslist"
//nCount -> 条目序号(显示用)
//strCallType -> 1: 呼叫会场终端; 2: 呼叫监控终端
function addConftempMeetListItem(strListType, strEpId, strMeetName, strE164, strMeetIp, nCount, strCallType )
{
	if ( "" == strListType ){
		return false;
	}
	
	if( "" == strMeetName && "" == strE164 && "" == strMeetIp ){
		return false;
	}
	
	if( "meetlist" == strListType && "" == strCallType ){
		return false;
	}
	
	if( "" == strEpId ){
		if( "meetlist" == strListType && strCallType != "" ){
			var nMeetCount = $(".div_Meet_list_content .div_list_item").length;
			strEpId = nMeetCount;
			nCount = nMeetCount + 1;
		}else{
			return false;
		}
	}
	
	var divListItem = document.createElement("div");
	divListItem.className="div_list_item";
	
	var checkboxItemNo = document.createElement("input");
	checkboxItemNo.type="checkbox";
	
	var divListContent = "";
	switch( strListType )
	{
		case "meetlist":{		//与会会场列表
			divListItem.setAttribute("onclick","onMeetItemClick(this)");
			checkboxItemNo.setAttribute("onclick","onMeetItemCheckboxClick(this)");
		
			divListContent = $(".div_Meet_list .div_list_content").get(0);
			break;
		}
		case "pollinglist":{	//轮询列表
			divListItem.setAttribute("onclick","onPollingItemClick(this)");
			checkboxItemNo.setAttribute("onclick","onPollingItemCheckboxClick(this)");
		
			divListContent = $(".div_Polling_list .div_list_content").get(0);
			break;
		}
		case "discusslist":{	//讨论列表
			divListItem.setAttribute("onclick","onDiscussItemClick(this)");
			checkboxItemNo.setAttribute("onclick","onDiscussItemCheckboxClick(this)");
		
			divListContent = $(".div_Discuss_list .div_list_content").get(0);
			break;
		}
		default:{				//error
			break;
		}
	}
	
	if( "" == divListContent ){
		return false;
	}

	divListItem.setAttribute("onmouseenter","onItemMouseenter(this)");
	divListItem.setAttribute("onmouseleave","onItemMouseleave(this)");
	
	var divListItemImg = document.createElement("div");
	divListItemImg.className="div_list_item_img";

	var divListItemName = document.createElement("div");
	divListItemName.className="div_list_item_name";

	var divListItemNum = document.createElement("div");
	divListItemNum.className="div_list_item_number";
	
	var divListItemIp = document.createElement("div");
	divListItemIp.className="div_list_item_ip";

	var divListItemNo;
	if( "meetlist" == strListType ){
		divListItemNo = document.createElement("div");
		divListItemNo.className="div_list_item_no";
		divListItem.appendChild(divListItemNo);
	}
	
	divListItem.appendChild(checkboxItemNo);
	divListItem.appendChild(divListItemImg);
	divListItem.appendChild(divListItemName);
	divListItem.appendChild(divListItemNum);
	divListItem.appendChild(divListItemIp);

	divListContent.appendChild(divListItem);

	$(divListItemName).text(strMeetName);
	$(divListItemNum).text(strE164);
	$(divListItemIp).text(strMeetIp);

	if( "meetlist" == strListType ){
		$(divListItemNo).text(nCount);
		//strCallType -> 1: 呼叫会场终端; 2: 呼叫监控终端
		divListItem.setAttribute("calltype", strCallType);
	}

	divListItem.setAttribute("no", strEpId);
	
	switch( strListType )
	{
		case "meetlist":{		//与会会场列表
			scroll_MeetList.init();
			break;
		}
		case "pollinglist":{	//轮询列表
			scroll_Polling.init();
			break;
		}
		case "discusslist":{	//讨论列表
			scroll_Discuss.init();
			break;
		}
		default:{				//error
			break;
		}
	}
	
	return true;
};

/**********与会会场列表相关*******************************************************************/

function clearMeetListItemSelState()
{	
	$(".div_MeetList_content .div_list input").each(function(index,element){
		this.checked = false;
	});
	
	ctrlMeetButtonState();
};

function clearMeetListItem()
{
	$(".div_Meet_list_content .div_list_item").remove(); 
	scroll_MeetList.init();
	//清除列表选中状态
	clearMeetListItemSelState();
};

function updMeetListItem(arrMeetList)
{
	clearMeetListItem();
	
	for (var i=0; i < arrMeetList.length; i++) {
		addConftempMeetListItem("meetlist", arrMeetList[i].epId,
		 arrMeetList[i].achMeetName, arrMeetList[i].achE164, arrMeetList[i].achMeetIp, (i+1), arrMeetList[i].calltype);
	};
	
	//添加滚动条
	//scroll_MeetList.init();
};

function onMeetListHeadCheckboxClick(obj)
{
	var bChecked = $(obj).parents(".div_list").find(".div_list_head input:checked").length;
	$(obj).parents(".div_list").find(".div_list_content input").each(function(index,element)
	{
		var isDisplay = $(this).parents(".div_list_item").css("display");
		if( "block" == isDisplay )
		{
			if( bChecked )
			{
				this.checked = true;
				$(this).parents(".div_list_item").css('background-color','#EFF2F4');
			}
			else
			{
				this.checked = false;
				$(this).parents(".div_list_item").css('background-color','white');
			}
		}
	});

	ctrlMeetButtonState();
};

function onMeetItemClick(obj)
{
	onItemClick(obj);
	ctrlMeetButtonState();
	ctrlMeetButtonState();
};

function onMeetItemCheckboxClick(obj)
{
	onItemCheckboxClick(obj);
	ctrlMeetButtonState();
	ctrlMeetButtonState();
};

function ctrlMeetButtonState()
{
	var nChecked = $(".div_MeetList_content .div_Meet_list_content input:checked").length;

	if( 0 == nChecked ){
		$(".btnDelMeet").attr("disabled","disabled");
	}else{
		$(".btnDelMeet").removeAttr("disabled");
	}
};

//控制与会会场列表全选按键状态
function ctrlMeetListAllselState()
{
	var bAllSel = true;
	$(".div_Meet_list").find(".div_list_content input").each(function(index,element)
	{
		var isDisplay = $(this).parents(".div_list_item").css("display");
		if( "block" == isDisplay && false == this.checked ){
			bAllSel = false;
		}
	});

	if( bAllSel ){
		$(".div_Meet_list .div_list_head input").prop("checked", true);
	}else{
		$(".div_Meet_list .div_list_head input").prop("checked", false);
	}
};

//显示符合搜索条件的条目信息
function showSearchRestItems()
{
	var $domItems = $( $(".div_Meet_list")[0] ).find(".div_list_item");
	var nItems = $domItems.length;

	var strSearch = $(".text_search").val();
	if( "搜索" == strSearch || "" == strSearch )
	{
		for( var i = 0; i < nItems; i++ )
		{
			var domItem = $domItems[i];
			domItem.style.display = "block";
			$(domItem).children(".div_list_item_no").text(i+1);
		}
	}
	else
	{
		var no = 1;
		for( var i = 0; i < nItems; i++ )
		{
			var domItem = $domItems[i];

			var strName = $(domItem).children(".div_list_item_name").text();
			var strNumber = $(domItem).children(".div_list_item_number").text();
			var strIp = $(domItem).children(".div_list_item_ip").text();
			
			if( strName.indexOf(strSearch) == -1 && strNumber.indexOf(strSearch) == -1 && 
			    strIp.indexOf(strSearch) == -1 )
			{
				domItem.style.display = "none";
			}
			else
			{
				domItem.style.display = "block";
				$(domItem).children(".div_list_item_no").text(no);
				no++;
			}
		}
	}

	ctrlMeetListAllselState();
};

/**********轮询会场列表相关*******************************************************************/

function clearPollingListItem()
{
	$(".div_Polling_list_content .div_list_item").remove(); 
	scroll_Polling.init();
	//清除列表选中状态
	clearPollingListItemSelState();
};

function updPollingListItem(arrPolling)
{
	clearPollingListItem();
	
	for (var i=0; i < arrPolling.length; i++) {	
		addConftempMeetListItem("pollinglist", arrPolling[i].epId,
		 arrPolling[i].achMeetName, arrPolling[i].achE164, arrPolling[i].achMeetIp, "", "");
	};
	
	//添加滚动条
	//scroll_Polling.init();
};

function onPollingListHeadCheckboxClick(obj)
{
	onListHeadCheckboxClick(obj);
	ctrlPollingButtonState();
};

function onPollingItemClick(obj)
{
	onItemClick(obj);
	ctrlPollingButtonState();
};

function onPollingItemCheckboxClick(obj)
{
	onItemCheckboxClick(obj);
	ctrlPollingButtonState();
};

function clearPollingListItemSelState()
{
	$(".div_ConfPolling_content .div_list input").each(function(index,element){
		this.checked = false;
	});
	
	ctrlPollingButtonState();
};

function ctrlPollingButtonState()
{
	var nChecked = $(".div_ConfPolling_content .div_Polling_list_content input:checked").length;

	if( 1 == nChecked ){
		$("a[name='aPollingOper']").each(function(index){
			$(this).attr("unable", false);
		});
	}else{
		$("a[name='aPollingOper']").each(function(index){
			$(this).attr("unable", true);
		});
	}

	if( 0 == nChecked ){
		$(".divPollingOper .aPollingRemove").attr("unable", true);
	}else{
		$(".divPollingOper .aPollingRemove").attr("unable", false);
	}
	
	setOperButtonColor();
};

/**********讨论会场列表相关*******************************************************************/

function clearDiscussListItem()
{
	$(".div_Discuss_list_content .div_list_item").remove(); 
	scroll_Discuss.init();
	//清除列表选中状态
	clearDiscussListItemSelState();
};

function updDiscussListItem(arrDiscuss)
{
	clearDiscussListItem();
	
	for (var i=0; i < arrDiscuss.length; i++) {
		addConftempMeetListItem("discusslist", arrDiscuss[i].epId,
		 arrDiscuss[i].achMeetName, arrDiscuss[i].achE164, arrDiscuss[i].achMeetIp, "", "");
	};
	
	//添加滚动条
	//scroll_Discuss.init();
};

function onDiscussListHeadCheckboxClick(obj)
{
	onListHeadCheckboxClick(obj);
	ctrlDiscussButtonState();
};

function onDiscussItemClick(obj)
{
	onItemClick(obj);
	ctrlDiscussButtonState();
};

function onDiscussItemCheckboxClick(obj)
{
	onItemCheckboxClick(obj);
	ctrlDiscussButtonState();
};

function clearDiscussListItemSelState()
{
	$(".div_ConfDiscuss_content .div_list input").each(function(index,element){
		this.checked = false;
	});
	
	ctrlDiscussButtonState();
};

function ctrlDiscussButtonState()
{
	var nChecked = $(".div_ConfDiscuss_content .div_Discuss_list_content input:checked").length;

	if( 0 == nChecked ){
		$(".divDiscussOper .ulDiscussOper .aDiscussRemove").attr("unable", true);
	}else{
		$(".divDiscussOper .ulDiscussOper .aDiscussRemove").attr("unable", false);
	}
	
	setOperButtonColor();
};

//检测会议模板页面数据
function checkTmpMeetInfo()
{
	//模板名称
	var strConfName = $(".textConfName").val();
	if( "" == strConfName ){
		top.showMessageBox("会议模板名称不能为空");
		return false;
	}
	
	if( IsValidE164(strConfName) ){
		top.showMessageBox("名称不可以全部为数字或[*#,]组合");
		return false;
	}
	
	if( !IsValidTPStr(strConfName) ){
		top.showMessageBox("会议名不可以包含空格及括号中的任意字符 [" + g_strInvalidAliasForShow + "]");
		return false;
	}
	
	//模板号码
	var strConfNum = $(".textConfNum").val();
	if( "" != strConfNum ){
		if( !IsValidE164(strConfNum) ){
			top.showMessageBox("号码必须全部为数字或[*#,]组合");
			return false;
		}
	}
	
	//todo:
	//会议类型
	var strConfType = $(".textConfType").val();
	if( "预约会议" == strConfType ){
		var strStartTime = $(".textStartTime").val();
	}
	
	//todo:
	//媒体格式
	
	//会议码率
	
	//会议级联

	//传输加密
	//密钥长度限制为16个字符
	
	return true;
};

//点击"保存"按键
function saveConfTemplateInfo()
{
	if( !checkTmpMeetInfo() ){
		return;
	}
	
	CheckConftempRepeatReq();
};
	
//发送模板信息
function sendConfTemplateInfo()
{	
	//基本配置
	var strConfName = $(".textConfName").val();
	var strConfNum = $(".textConfNum").val();

	//todo:
	//会议类型
	var strConfType = $(".textConfType").val();
	var strStartTime = "0";
	if( "预约会议" == strConfType ){
		strStartTime = $(".textStartTime").val();
	}

	//媒体格式
	//会议格式
	var strConfFormat = $(".textConfFormat").val();
	var arrConfFormat = strConfFormat.split("; ");
	var wMainNum = strConfFormat.split("; ").length;
	var arrTpMainVideoRes = "\"\"";
	if( wMainNum > 0 ){
		var arrTpMainVideoRes = "[";
		for ( var i = 0; i < wMainNum; i++ ) {
			var itemMainVideoRes = "{\"chFormatName\":" + "\"" + arrConfFormat[i] + "\"" +"}" + ",";
			arrTpMainVideoRes += itemMainVideoRes;
		};
		arrTpMainVideoRes = arrTpMainVideoRes.substring(0, arrTpMainVideoRes.length - 1);
		arrTpMainVideoRes += "]";	
	}
	if( 0 == strConfFormat.length ){
		wMainNum = 0;
	}
	arrTpMainVideoRes += "," + "\"wMainNum\":" + "\"" + wMainNum + "\"";	

	//演示格式	
	var strShowFormat = $(".textShowFormat").val();
	var arrShowFormat = strShowFormat.split("; ");
	var wMinorNum = strShowFormat.split("; ").length;
	var arrTpMinorVideoRes = "\"\"";
	if( wMinorNum > 0 ){
		arrTpMinorVideoRes = "[";
		for ( var i = 0; i < wMinorNum; i++ ) {
			var itemMinorVideoRes = "{\"chFormatName\":" + "\"" + arrShowFormat[i] + "\"" +"}" + ",";
			arrTpMinorVideoRes += itemMinorVideoRes;
		};
		arrTpMinorVideoRes = arrTpMinorVideoRes.substring(0, arrTpMinorVideoRes.length - 1);
		arrTpMinorVideoRes += "]";
	}
	if( 0 == strShowFormat.length ){
		wMinorNum = 0;
	}
	arrTpMinorVideoRes += "," + "\"wMinorNum\":" + "\"" + wMinorNum + "\"";

	//音频格式
	var strAudioFormat = $(".textAudioFormat").val();
	var arrAudioFormat = strAudioFormat.split("; ");
	var wAudFmtNum = strAudioFormat.split("; ").length;
	var arrAudioFormat = "\"\"";
	if( wAudFmtNum > 0 ){
		arrAudioFormat = "[";
		for ( var i = 0; i < wAudFmtNum; i++ ) {
			var itemAudioRes = "{\"chFormatName\":" + "\"" + arrAudioFormat[i] + "\"" +"}" + ",";
			arrAudioFormat += itemAudioRes;
		};
		arrAudioFormat = arrAudioFormat.substring(0, arrAudioFormat.length - 1);
		arrAudioFormat += "]";
	}
	if( 0 == strAudioFormat.length ){
		wAudFmtNum = 0;
	}
	arrAudioFormat += "," + "\"wAudFmtNum\":" + "\"" + wAudFmtNum + "\"";
	
	//会议码率
	var strSingleRate = $(".textSingleRate").val();
	strSingleRate = strSingleRate.substring(0, strSingleRate.lastIndexOf(" Kbps"));
	var strShowRate = $(".textShowRate").val();
	strShowRate = strShowRate.substring(0, strShowRate.lastIndexOf(" Kbps"));
	
	//会议级联
	var strUpBandWidth = $(".textUpBandWidth").val();
	strUpBandWidth = strUpBandWidth.substring(0, strUpBandWidth.lastIndexOf(" Kbps"));
	var strDownBandWidth = $(".textDownBandWidth").val();
	strDownBandWidth = strDownBandWidth.substring(0, strDownBandWidth.lastIndexOf(" Kbps"));
	
	//传输加密
	var emTPEncryptTypeAES = "0";
	if( $("#switchStartEncrypt").attr("class") == "switchbtnOpen" ){
		emTPEncryptTypeAES = "2";	//emTPEncryptTypeAES = 2
	}
	
	var strEncrypt = "";
	if( $(".divAESEncrypt .radioAESCustom").is(":checked") ){
		strEncrypt = $(".textAESCustom").val();
	}
	
	//与会会场
	var arrMeetList = "\"\"";
	var nMeetCount = $(".div_Meet_list_content .div_list_item").length;
	if( nMeetCount > 0 ){
		arrMeetList = "[";
		$(".div_Meet_list_content .div_list_item").each(function(index,element){
			var strId = this.getAttribute("no");
			var strCallType = this.getAttribute("calltype");
			var strMeetName = $(this).children(".div_list_item_name").val();
			var strMeetNum = $(this).children(".div_list_item_number").val();
			var strMeetIp = $(this).children(".div_list_item_ip").val();
			
			var itemMeet = "{\"epId\":" + "\"" + strId + "\"" + "," + 
			                "\"calltype\":" + "\"" + strCallType + "\"" + "," + 
						    "\"achMeetName\":" + "\"" + strMeetName + "\"" + "," + 
						    "\"achE164\":" + "\"" + strMeetNum + "\"" + "," + 
							"\"achMeetIp\":" + "\"" + strMeetIp + "\"" +"}" + ",";
	
			arrMeetList += itemMeet;
		});

		arrMeetList = arrMeetList.substring(0, arrMeetList.length - 1);
		arrMeetList += "]";	
	}
	arrMeetList += "," + "\"wMeetCount\":" + "\"" + nMeetCount + "\"";	

	//会议轮询
	var bPollingOn = "0";
	if( $("#switchStartPolling").attr("class") == "switchbtnOpen" ){
		bPollingOn = "1";
	}
	var strPollingTime = $(".textPollingTime").val();
	strPollingTime.substring(0, strPollingTime.lastIndexOf(" 秒"));
	
	var arrPolling = "\"\"";
	var nPollingCount = $(".div_Polling_list_content .div_list_item").length;
	if( nPollingCount > 0 ){
		arrPolling = "[";
		$(".div_Polling_list_content .div_list_item").each(function(index,element){
			var strId = this.getAttribute("no");
			var strMeetName = $(this).children(".div_list_item_name").val();
			var strMeetNum = $(this).children(".div_list_item_number").val();
			var strMeetIp = $(this).children(".div_list_item_ip").val();
			
			var itemPolling = "{\"epId\":" + "\"" + strId + "\"" + "," + 
						    "\"achMeetName\":" + "\"" + strMeetName + "\"" + "," + 
						    "\"achE164\":" + "\"" + strMeetNum + "\"" + "," + 
							"\"achMeetIp\":" + "\"" + strMeetIp + "\"" +"}" + ",";
	
			arrPolling += itemPolling;
		});

		arrPolling = arrPolling.substring(0, arrPolling.length - 1);
		arrPolling += "]";	
	}
	arrPolling += "," + "\"wPollingCount\":" + "\"" + nPollingCount + "\"";	
	
	//会议讨论
	var bDiscussOn = "0";
	if( $("#switchStartDiscuss").attr("class") == "switchbtnOpen" ){
		bDiscussOn = "1";
	}
	
	var arrDiscuss = "\"\"";
	var nDiscussCount = $(".div_Discuss_list_content .div_list_item").length;
	if( nDiscussCount > 0 ){
		arrDiscuss = "[";
		$(".div_Discuss_list_content .div_list_item").each(function(index,element){
			var strId = this.getAttribute("no");
			var strMeetName = $(this).children(".div_list_item_name").val();
			var strMeetNum = $(this).children(".div_list_item_number").val();
			var strMeetIp = $(this).children(".div_list_item_ip").val();
			
			var itemDiscuss = "{\"epId\":" + "\"" + strId + "\"" + "," + 
						    "\"achMeetName\":" + "\"" + strMeetName + "\"" + "," + 
						    "\"achE164\":" + "\"" + strMeetNum + "\"" + "," + 
							"\"achMeetIp\":" + "\"" + strMeetIp + "\"" +"}" + ",";
	
			arrDiscuss += itemDiscuss;
		});
	
		arrDiscuss = arrDiscuss.substring(0, arrDiscuss.length - 1);
		arrDiscuss += "]";		
	}
	arrDiscuss += "," + "\"wDiscussCount\":" + "\"" + nDiscussCount + "\"";	

	//拼接json字符串
	var curOperEvent = "";
	var strConfTempID = parent.getCurConfTempID();
	if( strConfTempID > "0" ){
		curOperEvent = "ev_umcweb_UpdateConftemplate_req";
	}else if( strConfTempID == "0" ){
		curOperEvent = "ev_umcweb_AddConftemplate_req";
	}else{
		//error
		return;
	}
	
	send_data = "{\"event\":" + "\"" + curOperEvent + "\"" + "," 
	+ "\"wConfTempID\":" + "\"" + strConfTempID + "\"" + "," 
	+ "\"achConfName\":" + "\"" + strConfName + "\"" + ","
	+ "\"achConfNum\":" + "\"" + strConfNum + "\"" + "," 
	+ "\"achStartTime\":" + "\"" + strStartTime + "\"" + "," 
	+ "\"atTpMainVideoRes\":" + arrTpMainVideoRes + ","
	+ "\"atTpMinorVideoRes\":" + arrTpMinorVideoRes + ","
	+ "\"atAudFmt\":" + "\"" + arrAudioFormat + "\"" + ","
	+ "\"nSingleRate\":" + "\"" + strSingleRate + "\"" + ","
	+ "\"nShowRate\":" + "\"" + strShowRate + "\"" + ","
	+ "\"nUpBandWidth\":" + "\"" + strUpBandWidth + "\"" + ","
	+ "\"nDownBandWidth\":" + "\"" + strDownBandWidth + "\"" + ","
	+ "\"emEncryptModel\":" + "\"" + emTPEncryptTypeAES + "\"" + ","
	+ "\"achEncrypt\":" + "\"" + strEncrypt + "\"" + ","
	+ "\"arrMeetList\":" + arrMeetList + ","
	+ "\"bPollOn\":" + "\"" + bPollingOn + "\"" + ","
	+ "\"wInterval\":" + "\"" + strPollingTime + "\"" + ","
	+ "\"arrPolling\":" + arrPolling + ","
	+ "\"bDiscussOn\":" + "\"" + bDiscussOn + "\"" + ","
	+ "\"arrDiscuss\":" + arrDiscuss + "}";
	parent.frames["conftemplateList"].sendNty(send_data);
};

/*********************消息处理****************************************************************************/

function sendNty(send_data)
{
	$.post(url,send_data,function(data,ts){
		//返回通知消息
		switch( data.event ){
			case "ev_umcweb_ConfBasUsed_nty_res":{					//当前资源数 通知型回应
				ConfBasUsedNtyRes(data);
				break;
			}
			case "ev_umcweb_RefreshConftempInfo_nty_res":{			//刷新会议模板具体信息通知型回应
				RefreshConftempInfoRes(data);
				break;
			}
			case "ev_umcweb_RefreshConftemp_MeetNameList_nty_res":{	//刷新会议模板 与会会场列表通知型回应
				RefreshConftempMeetNameListRes(data);
				break;
			}
			case "ev_umcweb_RefreshConftemp_PollingList_nty_res":{	//刷新会议模板 轮询列表 通知型回应
				RefreshConftempPollingListRes(data);
				break;
			}
			case "ev_umcweb_RefreshConftemp_DiscussList_nty_res":{	//刷新会议模板 讨论列表 通知型回应
				RefreshConftempDiscussListRes(data);
				break;
			}
			case "ev_umcweb_CheckConftempRepeat_res":{				//校验模板名称、号码是否重复 回应
				CheckConftempRepeatRes(data);
				break;
			}
			default:{
			    break;
			}
		}
	},'json');
};

//刷新会议模板信息   请求
function RefreshConftempInfoReq(strConfTempID)
{	
	send_data = "{\"event\":\"ev_umcweb_RefreshConftempInfo_nty_req\"" + "," + "\"wConfTempID\":" + "\"" + strConfTempID + "\"" + "}";
	sendNty(send_data);
};

//接到会议模板信息   回应，刷新界面
function RefreshConftempInfoRes(data)
{
	if( "" == data.wConfTempID )
	{
		alert("fail to find this conftemplate info");
		parent.showCurPage("conftemplateList");
		return;
	}
	
	//默认显示基本设置界面
	//showConfSettingsLogic();
	
	$("#div_ConfSettings_Logic").css("display", "block");
	
	//设置界面显示内容
	$(".textConfName").val(data.achConfName);
	$(".textConfNum").val(data.achConfNum);
	
	if( "0" == data.achStartTime ){
		$(".textConfType").val("即时会议");
		$(".textStartTime").val("");
	}
	else{
		$(".textConfType").val("预约会议");
		$(".textStartTime").val(data.achStartTime);
	}
	
	//会议格式
	var strMainVideo = "";
	for( var i = 0; i < data.wMainNum; i++ ){
		strMainVideo = strMainVideo + data.atTpMainVideoRes[i].chFormatName + "; ";
	}
	strMainVideo = strMainVideo.substring(0, strMainVideo.lastIndexOf(";"));
	$(".textConfFormat").val(strMainVideo);
	
	//演示格式
	var strMinorVideo = "";
	for( var i = 0; i < data.wMinorNum; i++ ){
		strMinorVideo = strMinorVideo + data.atTpMinorVideoRes[i].chFormatName + "; ";
	}
	strMinorVideo = strMinorVideo.substring(0, strMinorVideo.lastIndexOf(";"));
	$(".textShowFormat").val(strMinorVideo);
	
	//音频格式
	var strAudioVideo = "";
	for( var i = 0; i < data.wAudFmtNum; i++ ){
		strAudioVideo = strAudioVideo + data.atAudFmt[i].chFormatName + "; ";
	}
	strAudioVideo = strAudioVideo.substring(0, strAudioVideo.lastIndexOf(";"));
	$(".textAudioFormat").val(strAudioVideo);
	
	var strAdaptRes = "当前模板所需适配通道：" + data.wResNum + " /系统总适配通道：" + data.wResUsedCount;
	$(".spanAdaptRes").text(strAdaptRes);
	
	$(".textSingleRate").val(data.nSingleRate + " Kbps");
	$(".textShowRate").val(data.nShowRate + " Kbps");
	
	$(".textUpBandWidth").val(data.nUpBandWidth + " Kbps");
	$(".textDownBandWidth").val(data.nDownBandWidth + " Kbps");
	
	//emTPEncryptTypeAES = 2
	if( "2" == data.emEncryptModel){
		$("#switchStartEncrypt").removeClass("switchbtnOff").addClass("switchbtnOpen");
	}else{
		$("#switchStartEncrypt").removeClass("switchbtnOpen").addClass("switchbtnOff");
	}
	
	setAESEncryptState();
	
	if( "" == data.achEncrypt ){
		$(".divAESEncrypt .radioAESDefault").attr("checked", true);
	}else{
		$(".divAESEncrypt .radioAESCustom").attr("checked", true);
	}
	$(".textAESCustom").val(data.achEncrypt);
};

//当前资源数 通知型请求
function ConfBasUsedNtyReq()
{
	send_data = "{\"event\":\"ev_umcweb_ConfBasUsed_nty_req\"}";
	sendNty(send_data);
};

function ConfBasUsedNtyRes(data)
{
	showConftemplateEditInitLogic();

	var strAdaptRes = "当前模板所需适配通道：0 /系统总适配通道：" + data.wResUsedCount;
	$(".spanAdaptRes").text(strAdaptRes);
};

//刷新会议模板  与会会场列表  请求
function RefreshConftempMeetNameListReq(strConfTempID)
{
	send_data = "{\"event\":\"ev_umcweb_RefreshConftemp_MeetNameList_nty_req\"" + "," + "\"wConfTempID\":" + "\"" + strConfTempID + "\"" + "}";
	sendNty(send_data);
};

function RefreshConftempMeetNameListRes(data)
{
	var arrMeetList = new Array();
	for ( var i = 0; i < data.count; i++ ) {
		arrMeetList.push(data.items[i]);
	};
	updMeetListItem(arrMeetList);
};

//刷新会议模板 轮询列表 请求
function RefreshConftempPollingListReq(strConfTempID)
{
	send_data = "{\"event\":\"ev_umcweb_RefreshConftemp_PollingList_nty_req\"" + "," + "\"wConfTempID\":" + "\"" + strConfTempID + "\"" + "}";
	sendNty(send_data);
};

function RefreshConftempPollingListRes(data)
{
	$("#div_ConfPolling_Logic").css("display", "block");
	
	if( "1" == data.bPollOn ){
		$("#switchStartPolling").removeClass("switchbtnOff").addClass("switchbtnOpen");
	}else{
		$("#switchStartPolling").removeClass("switchbtnOpen").addClass("switchbtnOff");
	}
	
	$(".textPollingTime").val(data.wInterval + " 秒");
	
	var arrPollingList = new Array();
	for ( var i = 0; i < data.count; i++ ) {
		arrPollingList.push(data.items[i]);
	};
	updPollingListItem(arrPollingList);
	
	$("#div_ConfPolling_Logic").css("display", "none");
};

//刷新会议模板  讨论列表 请求
function RefreshConftempDiscussListReq(strConfTempID)
{
	send_data = "{\"event\":\"ev_umcweb_RefreshConftemp_DiscussList_nty_req\"" + "," + "\"wConfTempID\":" + "\"" + strConfTempID + "\"" + "}";
	sendNty(send_data);
};

function RefreshConftempDiscussListRes(data)
{
	$("#div_ConfDiscuss_Logic").css("display", "block");
	
	if( "1" == data.bDiscussOn ){
		$("#switchStartDiscuss").removeClass("switchbtnOff").addClass("switchbtnOpen");
	}else{
		$("#switchStartDiscuss").removeClass("switchbtnOpen").addClass("switchbtnOff");
	}
	
	var arrDiscussList = new Array();
	for( var i = 0; i < data.count; i++ ){
		arrDiscussList.push(data.items[i]);
	};
	updDiscussListItem(arrDiscussList);
	
	$("#div_ConfDiscuss_Logic").css("display", "none");
};

//校验模板名称、号码是否重复 请求
function CheckConftempRepeatReq()
{
	var strConfName = $(".textConfName").val();
	var strConfNum = $(".textConfNum").val();

	send_data = "{\"event\":\"ev_umcweb_CheckConftempRepeat_req\"" + "," 
	+ "\"wConfTempID\":" + "\"" + parent.getCurConfTempID() + "\"" + ","
	+ "\"achConfName\":" + "\"" + strConfName + "\"" + ","
	+ "\"achConfNum\":" + "\"" + strConfNum + "\"" + "}";
	sendNty(send_data);
};

function CheckConftempRepeatRes(data)
{
	//0: noRepeat; 1: Repeat; 2: fail
	if( "0" == data.wNameRet && "0" == data.wNumRet ){
		sendConfTemplateInfo();
	}else if( "2" == data.wNameRet && "2" == data.wNumRet ){
		top.showMessageBox("找不到当前编辑的模板信息");
	}else{
		if( "1" == data.wNameRet ){
			top.showMessageBox("模板名称重复");
		}else if( "1" == data.wNumRet ){
			top.showMessageBox("模板号码重复");
		}
	}
};