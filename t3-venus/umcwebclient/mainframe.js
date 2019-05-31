/**
 * @author shicheng
 */
$(document).ready(function(){
	var bLogin = getCookie("bLogin");
	if(bLogin != "true")
	{
		//document.location.href="index.html";
	}
	
	new customBar(document.getElementById('slider'), document.getElementById('pannel'), document.getElementById('drag'));

	
	var loginName = getCookie("loginName");
	$(".username").text(loginName+"  |");
	
	showCurPage("usermng"); //设置默认显示界面
	var mainmenu = document.getElementsByName("amainmenu");
	$(".ausermng").click(function(){
		for( i = 0; i < mainmenu.length; i++ ){
			mainmenu[i].style.borderBottom = "0px";
		}
		this.style.borderBottom = "2px solid";
		showCurPage("usermng");
	});	
	
	$(".asysmng").click(function(){
		for( i = 0; i < mainmenu.length; i++ ){
			mainmenu[i].style.borderBottom = "0px";
		}
		this.style.borderBottom = "2px solid";
		showCurPage("sysmng");
	});
	
	$(".aconftemplate").click(function(){
		for( i = 0; i < mainmenu.length; i++ ){
			mainmenu[i].style.borderBottom = "0px";
		}
		this.style.borderBottom = "2px solid";
		showCurPage("conftemplate");
	});
	
	$(".aaddrbook").click(function(){
		for( i = 0; i < mainmenu.length; i++ ){
			mainmenu[i].style.borderBottom = "0px";
		}
		this.style.borderBottom = "2px solid";
		showCurPage("addrbook");
	});
	
	$(".aconfmng").click(function(){
		for( i = 0; i < mainmenu.length; i++ ){
			mainmenu[i].style.borderBottom = "0px";
		}
		this.style.borderBottom = "2px solid";
		showCurPage("confmng");
	});
	
	
	$(".alogoff").click(function(){
		showConfirmBox("确定要注销？");
	});	
	
	$(".antymessage").click(function(){
		showNtyMessageBox();
	});	
	

	$(window).on('beforeunload',function(){
		deleteCookieDelay("bLogin","true",2);
	});

	var nTimer = window.setInterval("onTimer()",30000);
	window.setTimeout("onTimerFirst()",3000);
});

function showCurPage(pageid)
{
	$("#usermng").css("width", "0px");
	$("#usermng").css("height", "0px");
	$("#sysmng").css("width", "0px");
	$("#sysmng").css("height", "0px");
	$("#conftemplate").css("width", "0px");
	$("#conftemplate").css("height", "0px");
	$("#addrbook").css("width", "0px");
	$("#addrbook").css("height", "0px");
	$("#confmng").css("width", "0px");
	$("#confmng").css("height", "0px");

	switch(pageid){
		case "usermng":{
			$("#usermng").css("width", "100%");
			$("#usermng").css("height", "100%");
			break;
		}
		case "sysmng":{
			$("#sysmng").css("width", "100%");
			$("#sysmng").css("height", "100%");
			break;
		}
		case "conftemplate":{
			$("#conftemplate").css("width", "100%");
			$("#conftemplate").css("height", "100%");
			break;
		}
		case "addrbook":{
			$("#addrbook").css("width", "100%");
			$("#addrbook").css("height", "100%");
			break;
		}
		case "confmng":{
			$("#confmng").css("width", "100%");
			$("#confmng").css("height", "100%");
			break;
		}
		default:{
			break;
		}
	}
};

function onTimerFirst()
{
//	var send_data="{\"event\":\"ev_dcweb_OSP_DISCONNECT_nty_req\"}";
//	sendNty(send_data);

	getUserInfo();
	getNetcfgInfo();
	getSysTimeInfo();
	//getNMServerInfo();
	getAddrbookInfo(1);

	if(window.frames["conftemplate"].document.readyState == "complete")
	{
		window.frames["conftemplate"].onShowWnd();
	}
	
	
	getConfListInfo();
	getConfbookListInfo();
};

function onTimer()
{
//	var send_data="{\"event\":\"ev_dcweb_OSP_DISCONNECT_nty_req\"}";
//	sendNty(send_data);
	
	//getUserInfo();
	//getNetcfgInfo();
	//getSysTimeInfo();
	//getNMServerInfo();
};

function sendNty(send_data)
{
    $.post(url,send_data,function(data,ts){
    	//返回通知消息
		switch(data.event){
			/*
			case "ev_dcweb_OSP_DISCONNECT_nty_rsp":{
				if(data.bLogin == "0"){
					showMessageBox("与服务器断开连接，即将退出至登录界面！");
				}
				
				break;
			}
			case "ev_dcweb_Mail_Nty_res":{
				var arrmailcfg = DC.getDCMailCfg().getMailCfg();
				if( !(arrmailcfg[0] == data.mailname && arrmailcfg[1] == data.mailusr && arrmailcfg[2] == data.mailpsw) ){
					DC.getDCMailCfg().setMailCfg(data.mailname,data.mailusr,data.mailpsw);
					window.frames["basiccfg"].frames["mailcfg"].setMailCfg();
				}
				
				break;
			}
			*/
			case "ev_umcweb_User_nty_res":{
				var arrUser=new Array();
				
				for (var i=0; i < data.count; i++) {
					arrUser.push(data.items[i].name);
				};
				
				window.frames["usermng"].updItem(arrUser);
								
				break;
			}
			case "ev_umcweb_IpCfg_nty_res":{
				window.frames["sysmng"].frames["netcfg"].setUmcServerInfo(data);
								
				break;
			}
			case "ev_umcweb_sipserver_nty_res":{
				window.frames["sysmng"].frames["netcfg"].setSipServerInfo(data);
								
				break;
			}
			case "ev_umcweb_GetSysTime_nty_res":{
				window.frames["sysmng"].frames["sysparam"].setSysparamInfo(data);	
				break;
			}
			case "ev_umcweb_NMServer_nty_res":{
				window.frames["sysmng"].frames["nmcfg"].setNMCfgInfo(data);	
				break;
			}
			case "ev_umcweb_addrbook_itemgroup_search_res":{
				window.frames["addrbook"].setAddrbookItemgroupInfo(data);
				break;
			}
			case "ev_umcweb_addrbook_group_get_res":{
				setPopupAddrbookCopyInfo(data);
				break;
			}
			case "ev_umcweb_addrbook_globle_get_res":{
				setPopupAddrbookGlobleInfo(data);
				break;
			}
			case "ev_umcweb_confmng_listconf_get_res":{
				window.frames["confmng"].frames["conflist"].setConfListInfo(data);
				break;
			}
			case "ev_umcweb_confmng_listconfbook_get_res":{
				window.frames["confmng"].frames["conflist"].setConfbookListInfo(data);
				break;
			}
			default:{
			    break;
			}
		}
    },'json');
};

function getUserInfo()
{
	send_data="{\"event\":\"ev_umcweb_User_nty_req\"}";
	sendNty(send_data);
};

function getNetcfgInfo()
{
	send_data="{\"event\":\"ev_umcweb_IpCfg_nty_req\"}";
	sendNty(send_data);
	
	send_data="{\"event\":\"ev_umcweb_sipserver_nty_req\"}";
	sendNty(send_data);
};

function getSysTimeInfo()
{
	send_data="{\"event\":\"ev_umcweb_GetSysTime_nty_req\"}";
	sendNty(send_data);
};
/*
function getNMServerInfo()
{
	send_data="{\"event\":\"ev_umcweb_NMServer_nty_req\"}";
	sendNty(send_data);
};
*/
function getAddrbookInfo(gid)
{
	if(window.frames["addrbook"].document.readyState == "complete")
	{
		var strSearch = window.frames["addrbook"].$(".text_search").val();
		if(strSearch == "搜索")
		{
			strSearch = "";
		}
		send_data="{\"event\":\"ev_umcweb_addrbook_itemgroup_search_req\",\"gid\":\""+gid+"\",\"search\":\""+strSearch+"\"}";
		sendNty(send_data);
	}
};

function getAddrbookGroupInfo(pid)
{
	var strSearch = $(".div_addrbook_copy_box .text_search").val();
	if(strSearch == "搜索")
	{
		strSearch = "";
	}
	send_data="{\"event\":\"ev_umcweb_addrbook_group_get_req\",\"pid\":\""+pid+"\",\"search\":\""+strSearch+"\"}";
	sendNty(send_data);
};

function getAddrbookGlobleInfo()
{
	var strSearch = $(".div_globlegroup_box .text_search").val();
	if(strSearch == "搜索")
	{
		strSearch = "";
	}
	send_data="{\"event\":\"ev_umcweb_addrbook_globle_get_req\",\"search\":\""+strSearch+"\"}";
	sendNty(send_data);
};

function getConfListInfo()
{
	send_data="{\"event\":\"ev_umcweb_confmng_listconf_get_req\"}";
	sendNty(send_data);
};

function getConfbookListInfo()
{
	send_data="{\"event\":\"ev_umcweb_confmng_listconfbook_get_req\"}";
	sendNty(send_data);
};
