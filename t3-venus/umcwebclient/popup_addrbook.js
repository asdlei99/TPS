/**
 * @author shicheng
 */
var scroll_popup_addrbook_copy = null;
var scroll_popup_addrbook_globle = null;
var scroll_popup_addrbook_globle_checked = null;
var arrPopupAddrbookCurGroupID = new Array;
arrPopupAddrbookCurGroupID[0] = 1;		//当前进入的组

$(document).ready(function(){
	//复制、移动道祖
	$(".button_addrbook_copy_box_ok").click(function(){		
		if($(".div_addrbook_copy_box_title").text().indexOf("复制") != -1)
		{
			window.frames["addrbook"].$(".div_list_content .div_list_item").each(function(index,element){
				if($(this).children("input:checked").length)
				{
					var id = $(this).children(".div_list_item_no").text();
					
					addIG(id,arrPopupAddrbookCurGroupID[arrPopupAddrbookCurGroupID.length-1]);
				}
			});
		}
		else
		{
			window.frames["addrbook"].$(".div_list_content .div_list_item").each(function(index,element){
				if($(this).children("input:checked").length)
				{
					var id = $(this).children(".div_list_item_no").text();
					
					delIG(id,getCurGroupID());
					addIG(id,arrPopupAddrbookCurGroupID[arrPopupAddrbookCurGroupID.length-1]);
				}
			});
		}
		
		
		OnPopupBtnOkClick(this);
	});
	
	$(".btn_addrbook_copy_box_back").click(function(){
		
		arrPopupAddrbookCurGroupID.pop();
		
		strTemp = $(".div_addrbook_copy_box_level").text();
		strTemp = strTemp.substring(0,strTemp.lastIndexOf(" > "));
		$(".div_addrbook_copy_box_level").text(strTemp);
		
		getAddrbookGroupInfo(arrPopupAddrbookCurGroupID[arrPopupAddrbookCurGroupID.length-1]);
		
		if(arrPopupAddrbookCurGroupID.length == 1)
		{
			$(".btn_addrbook_copy_box_back")[0].setAttribute("disabled","disabled");
			$(".btn_addrbook_copy_box_back")[0].setAttribute("disabled","disabled");
		}
	});
	
	clearPopupAddrbookCopyItem();
	
	scroll_popup_addrbook_copy = new customBar($(".div_addrbook_copy_box_slider").get(0), $(".div_addrbook_copy_box_pannel").get(0), $(".div_addrbook_copy_box_drag").get(0));

	
	//新建会场
	$(".button_addmeetingroom_box_ok").click(function(){
		var strName = $(".text_addmeetingroom_box_name").val();
		var strNumber = $(".text_addmeetingroom_box_number").val();
		var strIp = $(".text_addmeetingroom_box_ip").val();
		
		if(!checkItem(strName,strNumber,strIp))
		{
			return true;
		}

		if($(".div_addmeetingroom_box_title").text().indexOf("新建") != -1)
		{
			addItem(strName,strNumber,strIp);
		}
		else
		{
			modItem(strName,strNumber,strIp);
		}
		
		OnPopupBtnOkClick(this);
	});
	
	//新建组
	$(".button_addgroup_box_ok").click(function(){
		var strName = $(".text_addgroup_box_name").val();
		
		if(!checkGroup(strName))
		{
			return true;
		}

		if($(".div_addgroup_box_title").text().indexOf("新建") != -1)
		{
			addGroup(strName);
		}
		else
		{
			modGroup(strName);
		}
		
		OnPopupBtnOkClick(this);
	});
	
	$(".div_globlegroup_box .img_search").click(function(){
		getAddrbookGlobleInfo();
	});
	
	$(".div_addrbook_copy_box .img_search").click(function(){
		getAddrbookGroupInfo(getCurGroupID());
	});
	
	//全局地址簿
	scroll_popup_addrbook_globle = new customBar($(".div_list_meettingroom_bechecked .slider").get(0), $(".div_list_meettingroom_bechecked .pannel").get(0), $(".div_list_meettingroom_bechecked .drag").get(0));
	scroll_popup_addrbook_globle_checked = new customBar($(".div_list_meettingroom_checked .slider").get(0), $(".div_list_meettingroom_checked .pannel").get(0), $(".div_list_meettingroom_checked .drag").get(0));
});

function onAddrbookCopyItemClick(obj)
{
	arrPopupAddrbookCurGroupID.push(parseInt($(obj).children(".div_addrbook_copy_box_list_item_no").text()));
	
	strTemp = $(".div_addrbook_copy_box_level").text();
	strTemp = strTemp + " > " + $(obj).children(".div_addrbook_copy_box_list_item_name").text();
	$(".div_addrbook_copy_box_level").text(strTemp);
	
	getAddrbookGroupInfo(arrPopupAddrbookCurGroupID[arrPopupAddrbookCurGroupID.length-1]);
	
	$(".btn_addrbook_copy_box_back")[0].removeAttribute("disabled");
};

function clearPopupAddrbookCopyItem()
{
	$(".div_addrbook_copy_box_list_item").remove(); 
};

function onShowAddrbookGloble()
{
	clearListItem_MeettingroomBechecked();
	clearListItem_MeettingroomChecked();
	$(".text_search").val("搜索");
};

function setPopupAddrbookGlobleInfo(data)
{
	clearListItem_MeettingroomBechecked();
	
	var arrItem=new Array();
				
	for (var i=0; i < data.count; i++) {
		arrItem.push(data.items[i]);
	};
	
	for (var i=0; i < arrItem.length; i++) {
		var strOnline = "在线";
		var strType;
		if(arrItem[i].type=="1" || arrItem[i].type=="2")
		{
			strType="sip";
		}
		else
		{
			strType="gk";
		}
		var strName = arrItem[i].name;
		var strNumber = arrItem[i].number;
		var strIp = arrItem[i].ip;

		addListItem_MeettingroomBechecked(i,strOnline,strType,strName,strNumber,strIp);
	};
	
	scroll_popup_addrbook_globle.init();
};

function setPopupAddrbookCopyInfo(data)
{
	clearPopupAddrbookCopyItem();
	
	var arrGroup=new Array();
				
	for (var i=0; i < data.count; i++) {
		arrGroup.push(data.items[i]);
	};
	
	for (var i=0; i < arrGroup.length; i++) {
		var divListItem = document.createElement("div");
		divListItem.className="div_addrbook_copy_box_list_item";
		divListItem.setAttribute("onmouseenter","onItemMouseenter(this)");
		divListItem.setAttribute("onmouseleave","onItemMouseleave(this)");
		divListItem.setAttribute("onclick","onAddrbookCopyItemClick(this)");
	
		var divListItemNo = document.createElement("div");
		divListItemNo.className="div_addrbook_copy_box_list_item_no";
		
		var divListItemName = document.createElement("div");
		divListItemName.className="div_addrbook_copy_box_list_item_name";
	
		
		divListItem.appendChild(divListItemNo);
		divListItem.appendChild(divListItemName);
	
		var divListContent = $(".div_addrbook_copy_box_list_content").get(0);
	
		divListContent.appendChild(divListItem);
		
		$(divListItemNo).text(arrGroup[i].id);
		$(divListItemName).text(arrGroup[i].name);
	};
	
	scroll_popup_addrbook_copy.init();
};

function checkItem(strName,strNumber,strIp)
{
	if( strName == "" && strNumber == "" && strIp == "" )
	{
		alert("会场名称、ip、号码不能全为空！");
		return false;
	}
	
	return true;
};

function checkGroup(strName)
{
	if( strName == "" )
	{
		alert("组名称不能为空！");
		return false;
	}
	
	return true;
};

function addItem(strName,strNumber,strIp)
{
	var send_data='{"event":"ev_umcweb_addrbook_item_add_req","name":' + '"' + strName + '"' + ',' + '"number":' + '"' + strNumber + '"' + ',' + '"ip":' + '"' + strIp + '"' + '}';
    
	$.post(url,send_data,function(data,ts){
  		switch(data.nIID)
  		{
  			case "号码已存在":
  			{
  				alert("号码已存在");
  				break;
  			}
  			case "名称已存在":
  			{
  				alert("名称已存在");
  				break;
  			}
  			case "ip已存在":
  			{
  				alert("ip已存在");
  				break;
  			}
  			default:
  			{
  				addIG(data.nIID, 1);
  				if(getCurGroupID() != 1)
  				{
  					addIG(data.nIID, getCurGroupID());
  				}
  				
  				break;
  			}
  		}
	},'json');
    	
	return true;
};

function modItem(strName,strNumber,strIp)
{
	var send_data='{"event":"ev_umcweb_addrbook_item_mod_req","id":' + '"' + getCurItemID() + '"' + ',' + '"name":' + '"' + strName + '"' + ',' + '"number":' + '"' + strNumber + '"' + ',' + '"ip":' + '"' + strIp + '"' + '}';
    
	$.post(url,send_data,function(data,ts){
  		switch(data.bRet)
  		{
  			case "0":
  			{
  				alert("修改条目失败");
  				break;
  			}
  			default:
  			{
  				getAddrbookInfo(getCurGroupID());
  				
  				break;
  			}
  		}
	},'json');
    	
	return true;
};

function addGroup(strName)
{
	var send_data='{"event":"ev_umcweb_addrbook_group_add_req","name":' + '"' + strName + '"' + '}';
    
	$.post(url,send_data,function(data,ts){
  		switch(data.nGID)
  		{
  			case "":
  			{
  				alert("添加组失败");
  				break;
  			}
  			default:
  			{
  				addGG(data.nGID);
  				break;
  			}
  		}
	},'json');
    	
	return true;
};

function modGroup(strName)
{
	var send_data='{"event":"ev_umcweb_addrbook_group_mod_req","id":' + '"' + getCurItemID() + '"' + ',' + '"name":' + '"' + strName + '"' + '}';

	$.post(url,send_data,function(data,ts){
  		switch(data.nGID)
  		{
  			case "0":
  			{
  				alert("修改组失败");
  				break;
  			}
  			default:
  			{
  				getAddrbookInfo(getCurGroupID());
  				break;
  			}
  		}
	},'json');
    	
	return true;
};

function addIG(nIID,nGID)
{
	var send_data='{"event":"ev_umcweb_addrbook_ig_add_req","iid":' + '"' + nIID + '"' + ',' + '"gid":' + '"' + nGID + '"' + '}';

	$.post(url,send_data,function(data,ts){
  		switch(data.bRet)
  		{
  			case "0":
  			{
  				alert("添加条目-组关系失败");
  				break;
  			}
  			default:
  			{
  				getAddrbookInfo(getCurGroupID());
  				break;
  			}
  		}
	},'json');
};

function delIG(nIID,nGID)
{
	var send_data='{"event":"ev_umcweb_addrbook_ig_del_req","iid":' + '"' + nIID + '"' + ',' + '"gid":' + '"' + nGID + '"' + '}';

	$.post(url,send_data,function(data,ts){
  		switch(data.bRet)
  		{
  			case "0":
  			{
  				alert("删除条目-组关系失败");
  				break;
  			}
  			default:
  			{
  				getAddrbookInfo(getCurGroupID());
  				break;
  			}
  		}
	},'json');
};

function addGG(nGID)
{
	var send_data='{"event":"ev_umcweb_addrbook_gg_add_req","id":' + '"' + nGID + '"' + ',' + '"pid":' + '"' + getCurGroupID() + '"' + '}';

	$.post(url,send_data,function(data,ts){
  		switch(data.bRet)
  		{
  			case "0":
  			{
  				alert("添加组-组关系失败");
  				break;
  			}
  			default:
  			{
  				getAddrbookInfo(getCurGroupID());
  				break;
  			}
  		}
	},'json');
};

function getCurGroupID()
{
	if(window.frames["addrbook"].arrCurGroupID.length > 0)
	{
		return window.frames["addrbook"].arrCurGroupID[window.frames["addrbook"].arrCurGroupID.length-1];
	}
	
	return 1;
};

function getCurItemID()
{
	return window.frames["addrbook"].nCurItemID;
};

function OnPopupBtnOkClick_Addrbook_import(obj)
{
	$(".div_list_meettingroom_checked .div_list_item").each(function(index,element){
		var strName = $(this).children(".div_list_item_name").text();
		var strNumber = $(this).children(".div_list_item_number").text();
		var strIp = $(this).children(".div_list_item_ip").text();

		addItem(strName,strNumber,strIp);
	});
		
		
	OnPopupBtnOkClick(obj);
};

function onBtnCheckOneClick()
{
	CheckOne("globlestate");
	
	scroll_popup_addrbook_globle_checked.init();
};

function onBtnCheckAllClick()
{
	CheckAll("globlestate");
	
	scroll_popup_addrbook_globle_checked.init();
};

function onBtnUncheckOneClick()
{
	UncheckOne("globlestate");
	
	scroll_popup_addrbook_globle_checked.init();
};

function onBtnUncheckAllClick()
{
	UncheckAll("globlestate");
	
	scroll_popup_addrbook_globle_checked.init();
};
