/**
 * @author shicheng
 */
var nChecked = 0;
var scroll = null;
var arrCurGroupID = new Array;
arrCurGroupID[0] = 1;		//当前进入的组
var nCurItemID = 0;		//当前选中的条目、组
$(document).ready(function(){
	//添加滚动条
	scroll = new customBar($(".slider").get(0), $(".pannel").get(0), $(".drag").get(0));

	clearItem();
	
	/*新建*/
	$(".btn_add").click(function(){
		$(".div_dropdown_radio_add").css("display","block");
	});
	
	$(".div_dropdown_radio_add").mouseleave(function(){
		$(".div_dropdown_radio_add").css("display","none");
	});
	
	/*新建会场*/
	$(".add_meetingroom").click(function(){
		parent.$(".div_popupdialogbg").css("visibility","visible");
		parent.$(".div_addmeetingroom_box").css("visibility","visible");
		
		parent.$(".div_addmeetingroom_box_title").text("新建会场");
		
		parent.$(".text_addmeetingroom_box_name").val("");
		parent.$(".text_addmeetingroom_box_number").val("");
		parent.$(".text_addmeetingroom_box_ip").val("");
	});
	
	/*新建组*/
	$(".add_group").click(function(){
		parent.$(".div_popupdialogbg").css("visibility","visible");
		parent.$(".div_addgroup_box").css("visibility","visible");
		
		parent.$(".div_addgroup_box_title").text("新建组");
		
		parent.$(".text_addgroup_box_name").val("");
	});
	
	/*更多操作*/
	$(".btn_more").click(function(){
		$(".div_dropdown_radio_more").css("display","block");
	});
	
	$(".div_dropdown_radio_more").mouseleave(function(){
		$(".div_dropdown_radio_more").css("display","none");
	});
	
	$(".more_import").click(function(){
		top.$(".div_popupdialogbg").css("visibility","visible");
		top.$(".div_globlegroup_box").css("visibility","visible");
		
		top.onShowAddrbookGloble();
		top.getAddrbookGlobleInfo();
	});
	
	$(".more_refresh").click(function(){
		var send_data='{"event":"ev_umcweb_addrbook_globle_refresh_req"}';
		
		$.post(url,send_data,function(data,ts){
	  		switch(data.bRet)
	  		{
	  			case "0":
	  			{
	  				alert("刷新地址簿失败");
	  				break;
	  			}
	  			default:
	  			{
	  				break;
	  			}
	  		}
		},'json');
	});
	
	
	
	/*显示类型*/
	$(".div_showtype").click(function(){
		$(".div_dropdown_radio_showtype").css("display","block");
	});
	
	$(".div_dropdown_radio_showtype").mouseleave(function(){
		$(".div_dropdown_radio_showtype").css("display","none");
	});
	
	$(".showtype_online").click(function(){
		$(".font_content").text("显示在线");
	});
	
	$(".showtype_notonline").click(function(){
		$(".font_content").text("显示不在线");
	});
	
	$(".showtype_group").click(function(){
		$(".font_content").text("显示组");
	});
	
	$(".showtype_all").click(function(){
		$(".font_content").text("显示全部");
	});
	
	
	
	$(".btn_delete").click(function(){
		if( nChecked == 0 )
		{
			top.showMessageBox("请选择需要操作的条目！");
			return;
		}
		
		top.showConfirmBox("是否删除选择的地址簿条目？");
	});
	
	$(".btn_back").click(function(){
		$(".text_search").val("");
		
		arrCurGroupID.pop();
		
		strTemp = $(".div_level").text();
		strTemp = strTemp.substring(0,strTemp.lastIndexOf(" > "));
		$(".div_level").text(strTemp);
		
		top.getAddrbookInfo(arrCurGroupID[arrCurGroupID.length-1]);
		
		if(arrCurGroupID.length == 1)
		{
			$(".btn_back")[0].setAttribute("disabled","disabled");
			$(".btn_cut")[0].setAttribute("disabled","disabled");
		}
	});
	
	/*复制*/
	$(".btn_copy").click(function(){
		if( nChecked == 0 )
		{
			top.showMessageBox("请选择需要操作的条目！");
			return;
		}
		
		var bGroupChecked = false;
		
		$(".div_list_content .div_list_item").each(function(index,element){
			if($(this).children("input:checked").length)
			{
				if( $(this).children(".div_list_item_ip").text().indexOf("--") != -1 )
				{
					bGroupChecked = true;
				}
			}
		});
		
		if(bGroupChecked)
		{
			top.showMessageBox("组不能被复制或移动！");
			return;
		}
		
		parent.$(".div_popupdialogbg").css("visibility","visible");
		parent.$(".div_addrbook_copy_box").css("visibility","visible");
		
		parent.$(".div_addrbook_copy_box_title").text("复制到组");
		
		parent.$(".div_addrbook_copy_box_level").text("全部");
		parent.arrPopupAddrbookCurGroupID = [1];
		
		top.getAddrbookGroupInfo(1);
	});
	
	/*剪切*/
	$(".btn_cut").click(function(){
		if( nChecked == 0 )
		{
			top.showMessageBox("请选择需要操作的条目！");
			return;
		}
		
		var bGroupChecked = false;
		
		$(".div_list_content .div_list_item").each(function(index,element){
			if($(this).children("input:checked").length)
			{
				if( $(this).children(".div_list_item_ip").text().indexOf("--") != -1 )
				{
					bGroupChecked = true;
				}
			}
		});
		
		if(bGroupChecked)
		{
			top.showMessageBox("组不能被复制或移动！");
			return;
		}
		
		parent.$(".div_popupdialogbg").css("visibility","visible");
		parent.$(".div_addrbook_copy_box").css("visibility","visible");
		
		parent.$(".div_addrbook_copy_box_title").text("移动到组");
		
		parent.$(".div_addrbook_copy_box_level").text("全部");
		parent.arrPopupAddrbookCurGroupID = [1];
		
		top.getAddrbookGroupInfo(1);
	});
	
	$(".img_search").click(function(){
		top.getAddrbookInfo(arrCurGroupID[arrCurGroupID.length-1]);
	});
});

function clearItem()
{
	$(".div_list_item").remove(); 
	
	nChecked = 0;
	nCurItemID = 0;
	
	$(".div_choose_number").text("已选择（"+nChecked+"）");
	$(".div_list_head input").get(0).checked = false;
};

function delItem()
{
	$(".div_list_content .div_list_item").each(function(index,element){
		if($(this).children("input:checked").length)
		{
			var id = $(this).children(".div_list_item_no").text();
			var send_data;
			
			if( $(this).children(".div_list_item_ip").text().indexOf("--") == -1 )
			{
				send_data='{"event":"ev_umcweb_addrbook_item_del_req","id":' + '"' + id + '"' + '}';
			}
			else
			{
				send_data='{"event":"ev_umcweb_addrbook_group_del_req","id":' + '"' + id + '"' + '}';
			}
			
			$.post(url,send_data,function(data,ts){
		  		switch(data.emRet)
		  		{
		  			case "0":
		  			{
		  				alert("删除失败");
		  				break;
		  			}
		  			default:
		  			{
		  				top.getAddrbookInfo(arrCurGroupID[arrCurGroupID.length-1]);
		  				break;
		  			}
		  		}
	    	},'json');
		}
	});
};

function onAddrbookListItemClick(obj)
{
	onItemClick(obj);
	
	if($(obj).children(".div_list_item_ip").text().indexOf("--") != -1)
	{
		$(".text_search").val("");
		
		arrCurGroupID.push(parseInt($(obj).children(".div_list_item_no").text()));
		
		strTemp = $(".div_level").text();
		strTemp = strTemp + " > " + $(obj).children(".div_list_item_name").text();
		$(".div_level").text(strTemp);
		
		top.getAddrbookInfo(arrCurGroupID[arrCurGroupID.length-1]);
		
		$(".btn_back")[0].removeAttribute("disabled");
		$(".btn_cut")[0].removeAttribute("disabled");
	}
};

function onItemEditClick(obj)
{
	nCurItemID = parseInt($(obj).parents(".div_list_item").children(".div_list_item_no").text());
	
	parent.$(".div_popupdialogbg").css("visibility","visible");
	
	
	if( $(obj).parents(".div_list_item").children(".div_list_item_ip").text().indexOf("--") == -1 )
	{
		parent.$(".div_addmeetingroom_box").css("visibility","visible");
		parent.$(".div_addmeetingroom_box_title").text("编辑会场");
		
		var strName = $(obj).parents(".div_list_item").children(".div_list_item_name").text();
		var strNumber = $(obj).parents(".div_list_item").children(".div_list_item_number").text();
		var strIp = $(obj).parents(".div_list_item").children(".div_list_item_ip").text();
	
		
		parent.$(".text_addmeetingroom_box_name").val(strName);
		parent.$(".text_addmeetingroom_box_number").val(strNumber);
		parent.$(".text_addmeetingroom_box_ip").val(strIp);
	}
	else
	{
		parent.$(".div_addgroup_box").css("visibility","visible");
		parent.$(".div_addgroup_box_title").text("编辑组");
		
		var strName = $(obj).parents(".div_list_item").children(".div_list_item_name").text();
		
		parent.$(".text_addgroup_box_name").val(strName);
	}
	
	stopEvent();
};

function onItemDelClick(obj)
{
	var id = $(obj).parents(".div_list_item").children(".div_list_item_no").text();
	
	var send_data = '{"event":"ev_umcweb_addrbook_group_del_req","id":' + '"' + id + '"' + '}';
	
	$.post(url,send_data,function(data,ts){
  		switch(data.emRet)
  		{
  			case "0":
  			{
  				alert("删除失败");
  				break;
  			}
  			default:
  			{
  				top.getAddrbookInfo(arrCurGroupID[arrCurGroupID.length-1]);
  				break;
  			}
  		}
	},'json');
	
	stopEvent();
};

function setAddrbookItemgroupInfo(data)
{
	clearItem();
	
	var arrGroup=new Array();
				
	for (var i=0; i < data.groupcount; i++) {
		arrGroup.push(data.groupitems[i]);
	};
	
	for (var i=0; i < arrGroup.length; i++) {
		var divListItem = document.createElement("div");
		divListItem.className="div_list_item";
		divListItem.setAttribute("onmouseenter","onItemMouseenter(this)");
		divListItem.setAttribute("onmouseleave","onItemMouseleave(this)");
		divListItem.setAttribute("onclick","onAddrbookListItemClick(this)");
	
		var divListItemNo = document.createElement("div");
		divListItemNo.className="div_list_item_no";
		
		var checkboxItemNo = document.createElement("input");
		checkboxItemNo.type="checkbox";
		checkboxItemNo.setAttribute("style","visibility: hidden;");
		
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
		
		var divListItemHandle = document.createElement("div");
		divListItemHandle.className="div_list_item_handle";
		
		var aListItemHandle = document.createElement("a");
		aListItemHandle.href="javascript:void(0);"
		aListItemHandle.setAttribute("onclick","onItemEditClick(this)");
		$(aListItemHandle).text("编辑");
		
		var aListItemHandleDel = document.createElement("a");
		aListItemHandleDel.href="javascript:void(0);"
		aListItemHandleDel.setAttribute("onclick","onItemDelClick(this)");
		$(aListItemHandleDel).text("删除");
		aListItemHandleDel.className="aDelGroup";
	
		
		divListItem.appendChild(divListItemNo);
		divListItem.appendChild(checkboxItemNo);
		divListItem.appendChild(divListItemOnline);
		divListItem.appendChild(divListItemType);
		divListItem.appendChild(divListItemName);
		divListItem.appendChild(divListItemIp);
		divListItem.appendChild(divListItemNumber);
		divListItemHandle.appendChild(aListItemHandle);
		divListItemHandle.appendChild(aListItemHandleDel);
		divListItem.appendChild(divListItemHandle);
		
	
		var divListContent = $(".div_list_content").get(0);
	
		divListContent.appendChild(divListItem);
		
		$(divListItemNo).text(arrGroup[i].id);
		$(divListItemOnline).text("--");
		$(divListItemType).text("--");
		$(divListItemName).text(arrGroup[i].name);
		$(divListItemIp).text("--");
		$(divListItemNumber).text("--");
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
		divListItem.setAttribute("onclick","onAddrbookListItemClick(this)");
	
		var divListItemNo = document.createElement("div");
		divListItemNo.className="div_list_item_no";
		
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
		
		var divListItemHandle = document.createElement("div");
		divListItemHandle.className="div_list_item_handle";
		
		var aListItemHandle = document.createElement("a");
		aListItemHandle.href="javascript:void(0);"
		aListItemHandle.setAttribute("onclick","onItemEditClick(this)");
		$(aListItemHandle).text("编辑");
	
		
		divListItem.appendChild(divListItemNo);
		divListItem.appendChild(checkboxItemNo);
		divListItem.appendChild(divListItemOnline);
		divListItem.appendChild(divListItemType);
		divListItem.appendChild(divListItemName);
		divListItem.appendChild(divListItemIp);
		divListItem.appendChild(divListItemNumber);
		divListItemHandle.appendChild(aListItemHandle);
		divListItem.appendChild(divListItemHandle);
	
		var divListContent = $(".div_list_content").get(0);
	
		divListContent.appendChild(divListItem);
		
		$(divListItemNo).text(arrItem[i].id);
		
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
	scroll.init();
};
