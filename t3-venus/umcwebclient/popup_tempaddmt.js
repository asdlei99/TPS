/**
 * @author shicheng
 */
$(document).ready(function(){
	$(".div_popup_tempaddmt .checkbox_mt").click(function(){
		$(".checkbox_mt")[0].checked = true;
		$(".checkbox_jk")[0].checked = false;
	});
	
	$(".div_popup_tempaddmt .checkbox_jk").click(function(){
		$(".checkbox_mt")[0].checked = false;
		$(".checkbox_jk")[0].checked = true;
	});
	
});

function onPopupTempaddmtOKClick(obj)
{
	var strType;
	if( $(".div_popup_tempaddmt .checkbox_mt:checked").length == 1 )
	{
		strType = "1";
	}
	else
	{
		strType = "2";
	}
	
	var strName = $(".div_popup_tempaddmt .text_name").val();
	var strNumber = $(".div_popup_tempaddmt .text_number").val();
	var strIp = $(".div_popup_tempaddmt .text_ip").val();
	
	if( CheckPopupTempaddmtData( strName, strNumber, strIp ) == false )
	{
		return;
	}
	
	window.frames["conftemplate"].frames["conftemplateEdit"].addConftempMeetListItem( 
		"meetlist", "", strName, strNumber, strIp, "", strType );
	
	OnPopupBtnCloseClick(obj);
};

function CheckPopupTempaddmtData(strName, strNumber, strIp)
{
	if( strName == "" && strNumber == "" && strIp == "" )
	{
		alert("会场名称、ip、号码不能全为空！");
		return false;
	}
	
	if( $(".div_popup_tempaddmt .checkbox_jk:checked").length > 0 )
	{
		if( strName == "" || strIp == "" )
		{
			alert("监控终端：会场名称、ip必须输入！");
			return false;
		}
	}
	
	return true;
};