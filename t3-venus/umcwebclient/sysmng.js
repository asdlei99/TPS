/**
 * @author xuhuaxiu
 */
var g_curPage = "netcfg";
$(document).ready(function(){
	$(".btnNetcfg").attr("disabled", "disabled");
	$(".btnSysparam").removeAttr("disabled");

	var sysmngmenu = document.getElementsByName("btnTap");
	$(".btnNetcfg").click(function(){
		for( i = 0; i < sysmngmenu.length; i++ ){
			sysmngmenu[i].disabled = false;
		}
		$(this).attr("disabled", "disabled");
		showCurPage("netcfg");
	});
	
	$(".btnSysparam").click(function(){
		for( i = 0; i < sysmngmenu.length; i++ ){
			sysmngmenu[i].disabled = false;
		}
		$(this).attr("disabled", "disabled");
		showCurPage("sysparam");
	});
	/*
	$(".anmcfg").click(function(){
		for( i = 0; i < sysmngmenu.length; i++ ){
			sysmngmenu[i].style.color = "#000000";
		}
		this.style.color = "green";
		showCurPage("nmcfg");
	});*/
	
	$(".btnedit").click(function(){
		notifyCurPage("edit");
		updateBtnState("edit");
	});
	
	$(".btncancel").click(function(){
		notifyCurPage("cancel");
		updateBtnState("cancel");
	});
	
	$(".btnsave").click(function(){
		notifyCurPage("save");
		updateBtnState("save");
	});
});

function showCurPage(pageid)
{
	$("#netcfg").css("width", "0px");
	$("#netcfg").css("height", "0px");
	$("#sysparam").css("width", "0px");
	$("#sysparam").css("height", "0px");
	//$("#nmcfg").css("width", "0px");
	//$("#nmcfg").css("height", "0px");

	switch(pageid){
		case "netcfg":{
			$("#netcfg").css("width", "100%");
			$("#netcfg").css("height", "100%");
			break;
		}
		case "sysparam":{
			$("#sysparam").css("width", "100%");
			$("#sysparam").css("height", "100%");
			break;
		}
		/*case "nmcfg":{
			$("#nmcfg").css("width", "100%");
			$("#nmcfg").css("height", "100%");
			break;
		}*/
		default:{
			break;
		}
	}
	g_curPage = pageid;
	
	var strCurPageOper = window.frames[g_curPage].getCurOper();
	updateBtnState(strCurPageOper);	
}

function updateBtnState(curoper)
{
	if( "edit" == curoper )
	{
		$(".btnedit").css("display", "none");
		$(".btnsave").css("display", "inline");
		$(".btncancel").css("display", "inline");
	}
	else
	{
		$(".btnedit").css("display", "inline");
		$(".btnsave").css("display", "none");
		$(".btncancel").css("display", "none");
	}
}

function notifyCurPage(curoper)
{	
	window.frames[g_curPage].updateUIState(curoper);
}
