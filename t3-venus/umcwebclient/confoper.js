/**
 * @author shicheng
 */

$(document).ready(function(){
	updBtnState();
	
	$(".btn_dual").click(function(){
		var confid = parent.parent.getCurConfID();
		var $items = getCheckedItems(parent.$(".div_list_meettingroom")[0]);
		var epid = $items[0].getAttribute("no");
		
		if( $(this).val() == "双流演示" )
		{
			var send_data='{"event":"ev_umcweb_epoper_startdual_req","confid":"'+confid+'","epid":"'+epid+'"}';
		}
		else
		{
			var send_data='{"event":"ev_umcweb_epoper_stopdual_req","confid":"'+confid+'","epid":"'+epid+'"}';
		}
		
		sendNty(send_data);
	});
	
	$(".btn_speaker").click(function(){
		var confid = parent.parent.getCurConfID();
		var $items = getCheckedItems(parent.$(".div_list_meettingroom")[0]);
		var epid = $items[0].getAttribute("no");
	
		var send_data='{"event":"ev_umcweb_epoper_applyspeaker_req","confid":"'+confid+'","epid":"'+epid+'"}';
	
		sendNty(send_data);
	});
	
	$(".btn_quiet").click(function(){
		var confid = parent.parent.getCurConfID();
		var $items = getCheckedItems(parent.$(".div_list_meettingroom")[0]);
		
		for( var i = 0; i < $items.length; i++ )
		{
			var epid = $items[i].getAttribute("no");
			
			var bQuiet;
			if( $(this).val() == "静音" )
			{
				if( $($items[i]).find(".font_quiet").text() == "静音" )
				{
					continue;
				}
				bQuiet = 1;
			}
			else
			{
				if( $($items[i]).find(".font_quiet").text() == "未静音" )
				{
					continue;
				}
				bQuiet = 0;
			}
			
			var send_data='{"event":"ev_umcweb_epoper_startdual_req","confid":"'+confid+'","epid":"'+epid+'","bquiet":"'+bQuiet+'"}';
		
			sendNty(send_data);
		}
	});
	
	$(".btn_mute").click(function(){
		var confid = parent.parent.getCurConfID();
		var $items = getCheckedItems(parent.$(".div_list_meettingroom")[0]);
		
		for( var i = 0; i < $items.length; i++ )
		{
			var epid = $items[i].getAttribute("no");
			
			var bMute;
			if( $(this).val() == "哑音" )
			{
				if( $($items[i]).find(".font_mute").text() == "哑音" )
				{
					continue;
				}
				bMute = 1;
			}
			else
			{
				if( $($items[i]).find(".font_mute").text() == "未哑音" )
				{
					continue;
				}
				bMute = 0;
			}
			
			var send_data='{"event":"ev_umcweb_epoper_mute_req","confid":"'+confid+'","epid":"'+epid+'","bmute":"'+bMute+'"}';
		
			sendNty(send_data);
		}
	});
	
	$(".btn_drop").click(function(){
		var confid = parent.parent.getCurConfID();
		var $items = getCheckedItems(parent.$(".div_list_meettingroom")[0]);
		
		for( var i = 0; i < $items.length; i++ )
		{
			if( $($items[i]).find(".div_list_item_online").text() == "不在线" )
			{
				continue;
			}
			
			var epid = $items[i].getAttribute("no");
			
			
			var send_data='{"event":"ev_umcweb_epoper_drop_req","confid":"'+confid+'","epid":"'+epid+'"}';
		
			sendNty(send_data);
		}
	});
	
	$(".btn_call").click(function(){
		var confid = parent.parent.getCurConfID();
		var $items = getCheckedItems(parent.$(".div_list_meettingroom")[0]);
		
		for( var i = 0; i < $items.length; i++ )
		{
			if( $($items[i]).find(".div_list_item_online").text() == "在线" )
			{
				continue;
			}
			
			var epid = $items[i].getAttribute("no");
			
			
			var send_data='{"event":"ev_umcweb_epoper_call_req","confid":"'+confid+'","epid":"'+epid+'"}';
		
			sendNty(send_data);
		}
	});
	
	//选看
	$(".btn_chooseview").click(function(){
		top.$(".div_popupdialogbg").css("visibility","visible");
		top.$(".div_popup_selview").css("visibility","visible");
		
		top.onShowWnd_popup_selview();
	});
	
	$(".btn_discuss").click(function(){
		parent.showCurPage("confctrldiscuss");
	});
	
	$(".btn_polling").click(function(){
		parent.showCurPage("confctrlpolling");
	});
});

function updBtnState()
{
	var nChecked = getCurChecked(parent.$(".div_list_meettingroom").find(".div_list_content")[0]);
	
	$(".div_oper_mt input").removeAttr("disabled");
	
	if( nChecked == 0 )
	{
		$(".div_oper_mt input").attr("disabled", "false");
	}
	else if( nChecked == 1 )
	{
		var $items = getCheckedItems(parent.$(".div_list_meettingroom")[0]);
		
		if( $($items[0]).find(".font_dual").text() == "双流" )
		{
			$(".btn_dual").val("停止双流演示");
		}
		else
		{
			$(".btn_dual").val("双流演示");
		}
		
		if( $($items[0]).find(".font_speaker").text() == "发言" )
		{
			$(".btn_speaker").attr("disabled", "false");
		}
		else
		{
			$(".btn_speaker").removeAttr("disabled");
		}
		
		if( $($items[0]).find(".font_selview").text() == "选看" )
		{
			$(".btn_unchooseview").removeAttr("disabled");
		}
		else
		{
			$(".btn_unchooseview").attr("disabled", "false");
		}
	}
	else
	{
		$(".btn_chooseview").attr("disabled", "false");
		$(".btn_unchooseview").attr("disabled", "false");
		$(".btn_dual").attr("disabled", "false");
		$(".btn_speaker").attr("disabled", "false");
	}
	
	if( nChecked > 0 )
	{
		var $items = getCheckedItems(parent.$(".div_list_meettingroom")[0]);
		
		var bQuiet = false;
		var bMute = false;
		var bCall = false;
		var bDrop = false;
		
		for( var i = 0; i < $items.length; i++ )
		{
			if( $($items[i]).find(".font_quiet").text() == "未静音" )
			{
				bQuiet = true;
			}
			
			if( $($items[i]).find(".font_mute").text() == "未哑音" )
			{
				bMute = true;
			}
			
			if( $($items[i]).find(".div_list_item_online").text() == "不在线" )
			{
				bCall = true;
			}
			
			if( $($items[i]).find(".div_list_item_online").text() == "在线" )
			{
				bDrop = true;
			}
		}
		
		if( bQuiet == true )
		{
			$(".btn_quiet").val("静音");
		}
		else
		{
			$(".btn_quiet").val("取消静音");
		}
		
		if( bMute == true )
		{
			$(".btn_mute").val("哑音");
		}
		else
		{
			$(".btn_mute").val("取消哑音");
		}
		
		if( bCall == true )
		{
			$(".btn_call").removeAttr("disabled");
		}
		else
		{
			$(".btn_call").attr("disabled", "false");
		}
		
		if( bDrop == true )
		{
			$(".btn_drop").removeAttr("disabled");
		}
		else
		{
			$(".btn_drop").attr("disabled", "false");
		}
	}
};

function sendNty(send_data)
{
    $.post(url,send_data,function(data,ts){
    	//返回通知消息
		switch(data.event){
			case "ev_umcweb_epoper_startdual_res":{
				if(data.emRet == "0")
				{
					parent.getMTList();
				}
				else
				{
					alert("开启双流失败");
				}
				
				break;
			}
			case "ev_umcweb_epoper_stopdual_res":{
				if(data.emRet == "0")
				{
					var confid = parent.parent.getCurConfID();
					var send_data='{"event":"ev_umcweb_list_meetingroom_get_req","confid":"'+confid+'"}';
					parent.sendNty(send_data);
				}
				else
				{
					alert("停止双流失败");
				}
				
				break;
			}
			case "ev_umcweb_epoper_applyspeaker_res":{
				if(data.emRet == "0")
				{
					var confid = parent.parent.getCurConfID();
					var send_data='{"event":"ev_umcweb_list_meetingroom_get_req","confid":"'+confid+'"}';
					parent.sendNty(send_data);
				}
				else
				{
					alert("指定发言人失败");
				}
				
				break;
			}
			case "ev_umcweb_epoper_quiet_res":{
				if(data.bRet == "1")
				{
					var confid = parent.parent.getCurConfID();
					var send_data='{"event":"ev_umcweb_list_meetingroom_get_req","confid":"'+confid+'"}';
					parent.sendNty(send_data);
				}
				else
				{
					alert("静音设置失败");
				}
				
				break;
			}
			case "ev_umcweb_epoper_mute_res":{
				if(data.bRet == "1")
				{
					var confid = parent.parent.getCurConfID();
					var send_data='{"event":"ev_umcweb_list_meetingroom_get_req","confid":"'+confid+'"}';
					parent.sendNty(send_data);
				}
				else
				{
					alert("哑音设置失败");
				}
				
				break;
			}
			case "ev_umcweb_epoper_drop_res":{
				if(data.emRet == "0")
				{
					var confid = parent.parent.getCurConfID();
					var send_data='{"event":"ev_umcweb_list_meetingroom_get_req","confid":"'+confid+'"}';
					parent.sendNty(send_data);
				}
				else
				{
					alert("会场挂断失败");
				}
				
				break;
			}
			case "ev_umcweb_epoper_call_res":{
				if(data.emRet == "0")
				{
					var confid = parent.parent.getCurConfID();
					var send_data='{"event":"ev_umcweb_list_meetingroom_get_req","confid":"'+confid+'"}';
					parent.sendNty(send_data);
				}
				else
				{
					alert("会场呼叫失败");
				}
				
				break;
			}
			default:{
			    break;
			}
		}
    },'json');
};
