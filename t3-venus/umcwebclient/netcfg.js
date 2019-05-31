/**
 * @author shicheng
 */

var g_curoperNetcfg = "";

$(document).ready(function(){
	
});

function updateUIState(strcuroper)
{
	switch(strcuroper){
		case "edit":
		{
			$("input:text").each(function(){
				$(this).removeAttr('disabled');
			});
			break;
		}
		case "save":
		{
			saveNetcfgInfo();
			$("input:text").each(function(){
				$(this).attr("disabled","disabled");
			});
			break;
		}
		case "cancel":
		{
			var send_data = "{\"event\":\"ev_umcweb_IpCfg_nty_req\"}";
		    $.post(url,send_data,function(data,ts){
				setUmcServerInfo(data);
		    },'json');
			
			$("input:text").each(function(){
				$(this).attr("disabled","disabled");
			});
			break;
		}
		default:{
			break;
		}
	}
	g_curoperNetcfg = strcuroper;
};

function getCurOper()
{
	return g_curoperNetcfg;
};

function saveNetcfgInfo()
{
	var strIp = $(".text_umcServer_ip").val();
	var strSubmask = $(".text_umcServer_submask").val();
	var strGateway = $(".text_umcServer_gateway").val();
	
	if( checkIP(strIp, "UMC服务器ip地址") && checkIP(strSubmask, "UMC服务器子网掩码") && checkIP(strGateway, "UMC服务器配置网关地址") ){
		var send_data="{\"event\":\"ev_umcweb_IpCfg_req\"" + "," + "\"ip\":" + "\"" + strIp + "\"" + 
		"," + "\"submask\":" + "\"" + strSubmask + "\"" + "," + "\"gateway\":"+ "\"" + strGateway + "\"" + "}";

		$.post(url,send_data,function(data,ts){
			setUmcServerInfo(data);
    	},'json');
    }
    
    var strSipIp = $(".text_sipServer_ip").val();
    
	if( checkIP(strSipIp, "注册服务器ip地址") ){
		var send_data="{\"event\":\"ev_umcweb_sipserver_req\"" + "," + "\"ip\":" + "\"" + strSipIp + "\"" + "}";

		$.post(url,send_data,function(data,ts){
			setSipServerInfo(data);
    	},'json');
    }
};

function setUmcServerInfo(data){
	$(".text_umcServer_ip").val(data.ip);
	$(".text_umcServer_submask").val(data.submask);
	$(".text_umcServer_gateway").val(data.gateway);
};

function setSipServerInfo(data){
	$(".text_sipServer_ip").val(data.ip);
};
