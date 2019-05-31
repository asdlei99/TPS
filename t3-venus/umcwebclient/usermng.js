/**
 * @author shicheng
 */
var nChecked = 0;
var scroll = null;
$(document).ready(function(){
	//添加滚动条
	scroll = new customBar($(".slider").get(0), $(".pannel").get(0), $(".drag").get(0));

	clearItem();
	
	$(".btn_add").click(function(){
		top.$(".div_popupdialogbg").css("visibility","visible");
		top.$(".div_adduserbox").css("visibility","visible");
		
		top.$(".text_adduserbox_username").val("");
		top.$(".text_adduserbox_pwd").val("");
		top.$(".text_adduserbox_confirmpwd").val("");
	});
	
	$(".btn_delete").click(function(){
		if( nChecked == 0 )
		{
			top.showMessageBox("请选择需要删除的用户条目！");
			return;
		}
		
		top.showConfirmBox("是否删除选择的用户条目？");
	});
});

function clearItem()
{
	$(".div_list_item").remove(); 
};

function updItem(arrUser)
{
	clearItem();
	
	arrUser.sort();
	
	for (var i=0; i < arrUser.length; i++) {
		var divListItem = document.createElement("div");
		divListItem.className="div_list_item";
		divListItem.setAttribute("onmouseenter","onItemMouseenter(this)");
		divListItem.setAttribute("onmouseleave","onItemMouseleave(this)");
		divListItem.setAttribute("onclick","onItemClick(this)");
	
		var divListItemNo = document.createElement("div");
		divListItemNo.className="div_list_item_no";
		
		var checkboxItemNo = document.createElement("input");
		checkboxItemNo.type="checkbox";
		checkboxItemNo.setAttribute("onclick","onItemCheckboxClick(this)");
	
		var divListItemName = document.createElement("div");
		divListItemName.className="div_list_item_name";
		
		var divListItemHandle = document.createElement("div");
		divListItemHandle.className="div_list_item_handle";
		
		var aListItemHandle = document.createElement("a");
		aListItemHandle.href="javascript:void(0);"
		aListItemHandle.setAttribute("onclick","onBtnEditClick(this)");
		$(aListItemHandle).text("编辑");
	
		
		divListItem.appendChild(divListItemNo);
		divListItem.appendChild(checkboxItemNo);
		divListItem.appendChild(divListItemName);
		divListItemHandle.appendChild(aListItemHandle);
		divListItem.appendChild(divListItemHandle);
	
		var divListContent = $(".div_list_content").get(0);
	
		divListContent.appendChild(divListItem);
		
		$(divListItemNo).text(i+1);
		$(divListItemName).text(arrUser[i]);
	};
	
	//添加滚动条
	scroll.init();
};

function delItem()
{
	$(".div_list_content .div_list_item").each(function(index,element){
		if($(this).children("input:checked").length)
		{
			var usr = $(this).children(".div_list_item_name").text();
			
			var send_data='{"event":"ev_umcweb_DelUser_req","name":' + '"' + usr + '"' + '}';
			alert("删除"+usr);
			
			$.post(url,send_data,function(data,ts){
		  		switch(data.emRet)
		  		{
		  			case "1":
		  			{
		  				break;
		  			}
		  			case "0":
		  			{
		  				alert("删除用户失败");
		  				break;
		  			}
		  			default:
		  			{
		  				break;
		  			}
		  		}
	    	},'json');
		}
	});
};

function onBtnEditClick(obj)
{
	top.$(".div_popupdialogbg").css("visibility","visible");
	top.$(".div_edituserbox").css("visibility","visible");
	
	usr = $(obj).parents(".div_list_item").children(".div_list_item_name").text();
	
	top.$(".text_edituserbox_username").val(usr);
	top.$(".text_edituserbox_pwd").val("******");
	top.$(".text_edituserbox_confirmpwd").val("******");
};