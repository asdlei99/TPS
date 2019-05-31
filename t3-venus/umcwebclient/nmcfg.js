/**
 * @author xuhuaxiu
 */
var g_umcwebMaxCommunityLength = 31;
var g_curoperNMCfg = "";
$(document).ready(function(){
	$("input:text").each(function(){
		$(this).attr("disabled","disabled");
	});
	
	$("#switchStartServer1").unbind("click").click(function(){
		var self=$(this);
		if( self.attr("class") == "switchbtnOff" )
		{
			self.removeClass("switchbtnOff").addClass("switchbtnOpen");
		}
		else if( self.attr("class") == "switchbtnOpen" )
		{
			self.removeClass("switchbtnOpen").addClass("switchbtnOff");
		}
	});
	
	$("#switchStartServer2").unbind("click").click(function(){
		var self=$(this);
		if( self.attr("class") == "switchbtnOff" )
		{
			self.removeClass("switchbtnOff").addClass("switchbtnOpen");
		}
		else if( self.attr("class") == "switchbtnOpen" )
		{
			self.removeClass("switchbtnOpen").addClass("switchbtnOff");
		}
	});
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
			saveNMCfgInfo();
			$("input:text").each(function(){
				$(this).attr("disabled","disabled");
			});
			break;
		}
		case "cancel":
		{
			var send_data = "{\"event\":\"ev_umcweb_NMServer_nty_req\"}"
			$.post(url,send_data,function(data,ts){
				setNMCfgInfo(data);
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
	g_curoperNMCfg = strcuroper;
}

function getCurOper()
{
	return g_curoperNMCfg;
}

function checkIP(sIPAddress)
{
	var exp=/^([1-9]|\d[1-9]\d[0-9]|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$/;
	var reg = sIPAddress.match(exp);
	if(reg==null)
	{
		return false;
	}
	return true;
}

function checkNMCfg()
{
	var strNMServerIP1 = $(".textServerIp1").val();
	var strNMGetSetPort1 = $(".textGetSetPort1").val();
	var strNMTrapPort1 = $(".textTrapPort1").val();
	var strNMReadCommunity1 = $(".textReadCommunity1").val();
	var strNMWriteCommunity1 = $(".textWriteCommunity1").val();
	
	var strNMServerIP2 = $(".textServerIp2").val();
	var strNMGetSetPort2 = $(".textGetSetPort2").val();
	var strNMTrapPort2 = $(".textTrapPort2").val();
	var strNMReadCommunity2 = $(".textReadCommunity2").val();
	var strNMWriteCommunity2 = $(".textWriteCommunity2").val();

	if( strNMServerIP1 != "" && strNMServerIP2 != "" )
	{
		if( strNMServerIP1 == strNMServerIP2 )
		{
			parent.parent.messageBox.show("网管服务器地址不能相同");
			return false;
		}
	}
	
	//网管服务器1
	if( !( strNMServerIP1=="" && strNMGetSetPort1=="" && strNMTrapPort1=="" && strNMReadCommunity1=="" && strNMWriteCommunity1=="" ) )
	{
		if( strNMServerIP1 == "" )
		{
			parent.parent.messageBox.show("网管服务器地址不能为空");
			$(".textServerIp1").focus();
			return false;
		}
		
		if( !checkIP(strNMServerIP1) )
		{
			parent.parent.messageBox.show("网管服务器地址无效");
			$(".textServerIp1").focus();
			return false;
		}
		
		if( strNMReadCommunity1.length > g_umcwebMaxCommunityLength )
		{
			parent.parent.messageBox.show("读共同体名超过最大长度：" + g_umcwebMaxCommunityLength);
			$(".textReadCommunity1").focus();
			return false;
		}
		
		if( strNMWriteCommunity1.length > g_umcwebMaxCommunityLength )
		{
			parent.parent.messageBox.show("写共同体名超过最大长度：" + g_umcwebMaxCommunityLength);
			$(".textWriteCommunity1").focus();
			return false;
		}
		
		if( strNMGetSetPort1 == "" )
		{
			parent.parent.messageBox.show("读写端口不能为空");
			$(".divGetSetPort1").focus();
			return false;
		}
		
		if( parseFloat(strNMGetSetPort1) > 9999 || parseFloat(strNMGetSetPort1) < 1 )
		{
			parent.parent.messageBox.show("读写端口越界，请在1-9999之间");
			$(".divGetSetPort1").focus();
			return false;
		}
		
		if( strNMTrapPort1 == "" )
		{
			parent.parent.messageBox.show("发警告端口不能为空");
			$(".textTrapPort1").focus();
			return false;
		}
		
		if( parseFloat(strNMTrapPort1) > 9999 || parseFloat(strNMTrapPort1) < 1 )
		{
			parent.parent.messageBox.show("发警告端口越界，请在1-9999之间");
			$(".textTrapPort1").focus();
			return false;
		}
	}
	
	//网管服务器2
	if( !( strNMServerIP2=="" && strNMGetSetPort2=="" && strNMTrapPort2=="" && strNMReadCommunity2=="" && strNMWriteCommunity2=="" ) )
	{
		if( strNMServerIP2 == "" )
		{
			parent.parent.messageBox.show("网管服务器地址不能为空");
			$(".textServerIp2").focus();
			return false;
		}
		
		if( !checkIP(strNMServerIP2) )
		{
			parent.parent.messageBox.show("网管服务器地址无效");
			$(".textServerIp2").focus();
			return false;
		}
		
		if( strNMReadCommunity2.length > g_umcwebMaxCommunityLength )
		{
			parent.parent.messageBox.show("读共同体名超过最大长度：" + g_umcwebMaxCommunityLength);
			$(".textReadCommunity2").focus();
			return false;
		}
		
		if( strNMWriteCommunity2.length > g_umcwebMaxCommunityLength )
		{
			parent.parent.messageBox.show("写共同体名超过最大长度：" + g_umcwebMaxCommunityLength);
			$(".textWriteCommunity2").focus();
			return false;
		}
		
		if( strNMGetSetPort2 == "" )
		{
			parent.parent.messageBox.show("读写端口不能为空");
			$(".divGetSetPort2").focus();
			return false;
		}
		
		if( parseFloat(strNMGetSetPort2) > 9999 || parseFloat(strNMGetSetPort2) < 1 )
		{
			parent.parent.messageBox.show("读写端口越界，请在1-9999之间");
			$(".divGetSetPort2").focus();
			return false;
		}
		
		if( strNMTrapPort2 == "" )
		{
			parent.parent.messageBox.show("发警告端口不能为空");
			$(".textTrapPort2").focus();
			return false;
		}
		
		if( parseFloat(strNMTrapPort2) > 9999 || parseFloat(strNMTrapPort2) < 1 )
		{
			parent.parent.messageBox.show("发警告端口越界，请在1-9999之间");
			$(".textTrapPort2").focus();
			return false;
		}
	}
	
	return true;
}

function saveNMCfgInfo()
{
	if( !checkNMCfg() )
	{
		return;
	}
	
	var strIsServerOn1 = "";
	if( $("#switchStartServer1").attr("class") == "switchbtnOff" )
	{
		strIsServerOn1 = "0";
	}
	else if( $("#switchStartServer1").attr("class") == "switchbtnOpen" )
	{
		strIsServerOn1 = "1";
	}
	var strNMServerIP1 = $(".textServerIp1").val();
	var strNMGetSetPort1 = $(".textGetSetPort1").val();
	var strNMTrapPort1 = $(".textTrapPort1").val();
	var strNMReadCommunity1 = $(".textReadCommunity1").val();
	var strNMWriteCommunity1 = $(".textWriteCommunity1").val();
	var strNMServerNO1 = "0";
	
	var strIsServerOn2 = "";
	if( $("#switchStartServer2").attr("class") == "switchbtnOff" )
	{
		strIsServerOn2 = "0";
	}
	else if( $("#switchStartServer2").attr("class") == "switchbtnOpen" )
	{
		strIsServerOn2 = "1";
	}
	var strNMServerIP2 = $(".textServerIp2").val();
	var strNMGetSetPort2 = $(".textGetSetPort2").val();
	var strNMTrapPort2 = $(".textTrapPort2").val();
	var strNMReadCommunity2 = $(".textReadCommunity2").val();
	var strNMWriteCommunity2 = $(".textWriteCommunity2").val();
	var strNMServerNO2 = "1";
	
	var send_data = "{\"event\":\"ev_umcweb_NMServer_req\"" + "," 
	+ "\"IsServerOn1\":" + "\"" + strIsServerOn1 + "\"" + "," 
	+ "\"NMServerIP1\":" + "\"" + strNMServerIP1 + "\"" + "," 
	+ "\"NMGetSetPort1\":" + "\"" + strNMGetSetPort1 + "\"" + ","
	+ "\"NMTrapPort1\":" + "\"" + strNMTrapPort1 + "\"" + ","
	+ "\"NMReadCommunity1\":" + "\"" + strNMReadCommunity1 + "\"" + ","
	+ "\"NMWriteCommunity1\":" + "\"" + strNMWriteCommunity1 + "\"" + ","
	+ "\"NMServerNO1\":" + "\"" + strNMServerNO1 + "\"" + ","
	+ "\"IsServerOn2\":" + "\"" + strIsServerOn2 + "\"" + ","
	+ "\"NMServerIP2\":" + "\"" + strNMServerIP2 + "\"" + ","
	+ "\"NMGetSetPort2\":" + "\"" + strNMGetSetPort2 + "\"" + ","
	+ "\"NMTrapPort2\":" + "\"" + strNMTrapPort2 + "\"" + ","
	+ "\"NMReadCommunity2\":" + "\"" + strNMReadCommunity2 + "\"" + ","
	+ "\"NMWriteCommunity2\":" + "\"" + strNMWriteCommunity2 + "\"" + ","
	+ "\"NMServerNO2\":" + "\"" + strNMServerNO2 + "\"" + "}";

	$.post(url,send_data,function(data,ts){
		setNMCfgInfo(data);
	},'json');
}

function setNMCfgInfo(data)
{
	if( !( data.NMServerIP1=="0.0.0.0" && data.NMGetSetPort1=="0" && data.NMTrapPort1=="0" && data.NMReadCommunity1=="" && data.NMWriteCommunity1=="" ) )
	{
		if( "0" == data.IsServerOn1 )
		{
			$("#switchStartServer1").removeClass("switchbtnOpen").addClass("switchbtnOff");
		}
		else
		{
			$("#switchStartServer1").removeClass("switchbtnOff").addClass("switchbtnOpen");
		}
		$(".textServerIp1").val(data.NMServerIP1);
		$(".textGetSetPort1").val(data.NMGetSetPort1);
		$(".textTrapPort1").val(data.NMTrapPort1);
		$(".textReadCommunity1").val(data.NMReadCommunity1);
		$(".textWriteCommunity1").val(data.NMWriteCommunity1);	
	}

	if( !( data.NMServerIP2=="0.0.0.0" && data.NMGetSetPort2=="0" && data.NMTrapPort2=="0" && data.NMReadCommunity2=="" && data.NMWriteCommunity2=="" ) )
	{
		if( "0" == data.IsServerOn2 )
		{
			$("#switchStartServer2").removeClass("switchbtnOpen").addClass("switchbtnOff");
		}
		else
		{
			$("#switchStartServer2").removeClass("switchbtnOff").addClass("switchbtnOpen");
		}
		$(".textServerIp2").val(data.NMServerIP2);
		$(".textGetSetPort2").val(data.NMGetSetPort2);
		$(".textTrapPort2").val(data.NMTrapPort2);
		$(".textReadCommunity2").val(data.NMReadCommunity2);
		$(".textWriteCommunity2").val(data.NMWriteCommunity2);
	}
}
