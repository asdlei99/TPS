/**
 * @author shicheng
 */
$(document).ready(function(){
	var time=7*24;
	addCookie("bLogin", "false", time);
	
	if( getCookie("loginRemember") > 0 ){
		//表示checkbox被选中
		setLoginInfo(getCookie("loginName"), getCookie("loginPwd"));
		document.getElementById("rememberpwd").checked = true;
    }
    
    
    $(".formlogin").submit( function() {
        loginPost();
     
        return false;//不刷新界面
    });
});

function loginPost()
{
    var usr = $("input[name='usrname']").val();
    var pwd = $("input[name='pwd']").val();
    
    if(!usr)
    {
    	$(".tip").css("visibility","visible");
    	$(".tip").text("登录失败：用户名不能为空");
    	return;
    }
    
    if(!pwd)
    {
    	$(".tip").css("visibility","visible");
    	$(".tip").text("登录失败：登录密码不为空");
    	return;
    }
    
    var send_data='{"event":"ev_umcweb_login_req","usr":' + '"' + usr + '"' + ',' + '"pwd":' + '"' + pwd + '"' + '}';
    
    $.post(url,send_data,function(data,ts){
	  	switch(data.EmTpLoginUmsRet)
	  	{
	  	case "0":
	  		{
	  			//登陆成功
	  			var time=7*24;
	            addCookie("loginName", $("input[name='usrname']").val(), time);
	            addCookie("loginPwd", $("input[name='pwd']").val(), time);
	            addCookie("loginRemember", $("input[name='rememberpwd']:checked").length, time);
	            addCookie("bLogin", "true", time);
	            
	            window.location.href = "mainframe.html" ;
	          
	  			break;
	  		}
	  	case "1":
	  		{
	  			$(".tip").text("登录失败：用户名或用户名错误");
	  			break;
	  		}
	  	case "2":
	  		{
	  			$(".tip").text("登录失败：用户名或用户名错误");
	  			break;
	  		}
	  	}
    },'json');
};

function setLoginInfo(loginName, loginPwd)
{
    $("#usrname").attr("value", loginName);
    $("#pwd").attr("value", loginPwd);
};