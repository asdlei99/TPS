function GetXmlHttpObject()
{
	var xmlHttp=null;
	try
	{
		// Firefox, Opera 8.0+, Safari
		xmlHttp=new XMLHttpRequest();
	}
	catch (e)
	{
		// Internet Explorer
		try
		{
			xmlHttp=new ActiveXObject("Msxml2.XMLHTTP");
		}
		catch (e)
		{
			xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");
		}
	}
	return xmlHttp;
}

function postMessage(ajaxFcgi, data, callBackFun)
{
	var url="http://172.16.48.18/cgi-bin/uewebservice.fcgi?";		
	ajaxFcgi.onreadystatechange=callBackFun;
	
	ajaxFcgi.open("post",url,true);
	
	ajaxFcgi.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
		
	ajaxFcgi.send(data);//参数可以通过此处发送，由于fileText内容可能会很大，所以用POST方法
	
	return ajaxFcgi;
	

	/*	
	$.post( 
				"/cgi-bin/uewebservice.fcgi",
				//$("#formlogin").serializeArray(),
				"{\"event\":\"ev_UMSLoginReq\",\"usr\":" + "\"" + usr + "\"" + "," + "\"psw\":" + "\"" + psw + "\"" + "}",
				
				function(data,status) { 
				    alert( "longinRsp data: " + data + "\nStatus: " + status); 
					var json=eval("("+data+")");
					if( json.ret == 1 )
					{
						//登陆成功，转到主界面
						window.location.href = "mainframe.html" ;
					}
					else
					{
						//data.tojson
						//alert( data + "\nStatus: " + status); 
						obj = eval( '(' + data + ')' );
						$.each(obj,function(index,elment) 
						{
							//alert( "login recievData: " + elment.name + ':' +  elment.value);
						});
					}
			  }		
		);
		*/

};