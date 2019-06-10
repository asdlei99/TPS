/**
 * @author xuhuaxiu
 */
function showMessageBox(strContent)
{
	top.$(".div_popupdialogbg").css("visibility","visible");
	top.$(".div_messagebox").css("visibility","visible");

	$(".div_messagebox .div_messagebox_content").text(strContent);
};

function onMessageBoxOKClick(obj)
{
	var strContent = $(".div_messagebox .div_messagebox_content").text();

	if( strContent.indexOf("网络配置成功") != -1 ){
		window.location.href = "index.html";
	}
	else if( strContent.indexOf("退出至登录界面") != -1 ){
		window.location.href = "index.html";
	}
	
	OnPopupBtnOkClick(obj);
};