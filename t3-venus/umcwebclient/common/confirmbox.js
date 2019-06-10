/**
 * @author xuhuaxiu
 */
function showConfirmBox(strContent)
{
	top.$(".div_popupdialogbg").css("visibility","visible");
	top.$(".div_confirmbox").css("visibility","visible");

	$(".div_confirmbox .div_confirmbox_content").text(strContent);
};

function onConfirmBoxOKClick(obj)
{
	var strContent = $(".div_confirmbox .div_confirmbox_content").text();

	if( strContent.indexOf("注销") != -1 ){
		window.location.href = "index.html";
	}
	else if( strContent.indexOf("是否删除选择的用户条目") != -1 ){
		window.frames["usermng"].delItem();
	}
	else if( strContent.indexOf("是否删除所选模板信息") != -1 ){
		window.frames["conftemplate"].frames["conftemplateList"].delConftemplate();
	}
	else if( strContent.indexOf("是否删除选择的地址簿条目") != -1 ){
		window.frames["addrbook"].delItem();
	}
	else if( strContent.indexOf("请问你确定召开已选择的会议模板吗") != -1 ){
		window.frames["conftemplate"].frames["conftemplateList"].startConftemplate();
	}
	else if( strContent.indexOf("请问你确定召开当前会议模板吗") != -1 ){
		window.frames["conftemplate"].frames["conftemplateScan"].startConftemplate();
	}
	
	OnPopupBtnOkClick(obj);
};