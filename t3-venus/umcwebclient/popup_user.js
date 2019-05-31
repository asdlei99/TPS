/**
 * @author shicheng
 */
function OnPopupAdduserBtnOkClick(obj)
{
	var usr = $(".text_adduserbox_username").val();
	var pwd = $(".text_adduserbox_pwd").val();
	var confirmpwd = $(".text_adduserbox_confirmpwd").val();
	
	if( usr == "" || pwd == "" )
	{
		alert("请输入用户名或密码");
		return;
	}
	
	if( confirmpwd != pwd )
	{
		alert("两次密码输入不一致，请重新输入!");
		return;
	}
	
	var send_data='{"event":"ev_umcweb_AddUser_req","name":' + '"' + usr + '"' + ',' + '"pwd":' + '"' + pwd + '"' + '}';

	$.post(url,send_data,function(data,ts){
  		switch(data.emRet)
  		{
  			case "1":
  			{
  				break;
  			}
  			case "0":
  			{
  				alert("失败");
  				break;
  			}
  			default:
  			{
  				break;
  			}
  		}
	},'json');
	
	OnPopupBtnOkClick(obj);
};

function OnPopupEdituserBtnOkClick(obj)
{
	var usr = $(".text_edituserbox_username").val();
	var pwd = $(".text_edituserbox_pwd").val();
	var confirmpwd = $(".text_edituserbox_confirmpwd").val();
	
	if( pwd == "" )
	{
		alert("请输入密码");
		return;
	}
	
	if( confirmpwd != pwd )
	{
		alert("两次密码输入不一致，请重新输入!");
		return;
	}
	
	var send_data='{"event":"ev_umcweb_ChangePwd_req","name":' + '"' + usr + '"' + ',' + '"pwd":' + '"' + pwd + '"' + '}';

	$.post(url,send_data,function(data,ts){
  		switch(data.emRet)
  		{
  			case "1":
  			{
  				break;
  			}
  			case "0":
  			{
  				alert("修改失败");
  				break;
  			}
  			default:
  			{
  				break;
  			}
  		}
	},'json');
	
	OnPopupBtnOkClick(obj);
};
