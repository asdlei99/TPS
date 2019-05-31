/**
 * @author xuhuaxiu
 */
var g_curoperSysparam = "";
$(document).ready(function(){
	$(".btnSynLocaltime").unbind("click").click(function(){
		var date = new Date();
		var send_data = "{\"event\":\"ev_umcweb_SetSysTime_req\"" + "," 
		+ "\"nYear\":" + "\"" + date.getFullYear() + "\"" + "," 
		+ "\"nMonth\":" + "\"" + (date.getMonth()+1) + "\"" + "," 
		+ "\"nMDay\":" + "\"" + date.getDate() + "\"" + ","
		+ "\"nHour\":" + "\"" + date.getHours() + "\"" + ","
		+ "\"nMinute\":" + "\"" + date.getMinutes() + "\"" + ","
		+ "\"nSecond\":" + "\"" + date.getSeconds() + "\"" + "}";
	
	    $.post(url,send_data,function(data,ts){
		  	setSysparamInfo(data);
	    },'json');
	});

	//设置下拉框中显示的条目
	setSelectBoxItems();
	
	$(".selectSingleBoxHour").selectSingleBoxInit();
	$(".selectSingleBoxMinute").selectSingleBoxInit();
	$(".selectSingleBoxSecond").selectSingleBoxInit();
	
	ctrlButtonState(true);
});

function updateUIState(strcuroper)
{
	switch(strcuroper){
		case "edit":
		{
			ctrlButtonState(false);
			break;
		}
		case "save":
		{
			saveSysparamInfo();
			ctrlButtonState(true);
			break;
		}
		case "cancel":
		{
			var send_data = "{\"event\":\"ev_umcweb_GetSysTime_nty_req\"}";
		    $.post(url,send_data,function(data,ts){
				setSysparamInfo(data);
		    },'json');
			
			ctrlButtonState(true);
			break;
		}
		default:{
			break;
		}
	}
	g_curoperSysparam = strcuroper;
};

function ctrlButtonState(bDisabled)
{
	if( bDisabled ){
		$(".sysdate").attr("disabled","disabled");
		$(".selectSingleBox").webumcSelect("disabled", true);
	}else{
		$(".sysdate").removeAttr("disabled");
		$(".selectSingleBox").webumcSelect("disabled", false);
	}
};

function getCurOper()
{
	return g_curoperSysparam;
};

function setSelectBoxItems()
{
	var ulHour = $(".selectSingleBoxHour ul").get(0);
	var strHourIndex = "";
	for (var i=0; i < 24; i++) 
	{
		if( i < 10 ){
			strHourIndex = "0" + i;
		}
		else{
			strHourIndex = "" + i;
		}
		var liHour = document.createElement("li");		
		liHour.setAttribute("value", strHourIndex); 
		liHour.appendChild(document.createTextNode(strHourIndex));
		
		ulHour.appendChild(liHour); 
	};
	
	var ulMinute = $(".selectSingleBoxMinute ul").get(0);
	var strMinuteIndex = "";
	for (var i=0; i < 60; i++) 
	{
		if( i < 10 ){
			strMinuteIndex = "0" + i;
		}
		else{
			strMinuteIndex = "" + i;
		}
		var liMinute = document.createElement("li");		
		liMinute.setAttribute("value", strMinuteIndex); 
		liMinute.appendChild(document.createTextNode(strMinuteIndex));
		
		ulMinute.appendChild(liMinute); 
	};

	var ulSecond = $(".selectSingleBoxSecond ul").get(0);
	var strSecondIndex = "";
	for (var i=0; i < 60; i++) 
	{
		if( i < 10 ){
			strSecondIndex = "0" + i;
		}
		else{
			strSecondIndex = "" + i;
		}
		var liSecond = document.createElement("li");		
		liSecond.setAttribute("value", strSecondIndex); 
		liSecond.appendChild(document.createTextNode(strSecondIndex));
		
		ulSecond.appendChild(liSecond); 
	};
}

function saveSysparamInfo()
{
	var strDate = $(".sysdate").val(); //"2014-10-15";
	var strYear = strDate.substring(0, strDate.indexOf("-"));
	var strMonth = strDate.substring(strDate.indexOf("-")+1, strDate.lastIndexOf("-"));
	var strDay = strDate.substring(strDate.lastIndexOf("-")+1);

	var strHour = $(".textHour").html();
	var strMinute = $(".textMinute").html();
	var strSecond = $(".textSecond").html();

	var send_data = "{\"event\":\"ev_umcweb_SetSysTime_req\"" + "," 
	+ "\"nYear\":" + "\"" + strYear + "\"" + "," 
	+ "\"nMonth\":" + "\"" + strMonth + "\"" + "," 
	+ "\"nMDay\":" + "\"" + strDay + "\"" + ","
	+ "\"nHour\":" + "\"" + strHour + "\"" + ","
	+ "\"nMinute\":" + "\"" + strMinute + "\"" + ","
	+ "\"nSecond\":" + "\"" + strSecond + "\"" + "}";

    $.post(url,send_data,function(data,ts){
		setSysparamInfo(data);
    },'json');
}

function setSysparamInfo(data)
{
	$(".sysdate").val( data.nYear + "-" + data.nMonth + "-" + data.nMDay);
	
	$(".textHour").text(data.nHour);
	$(".textMinute").text(data.nMinute);
	$(".textSecond").text(data.nSecond);
}
