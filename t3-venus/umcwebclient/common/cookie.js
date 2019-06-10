function addCookie(name,value,expiresHours)
{
	var cookieString=name+"="+escape(value);
	//判断是否设置过期时间 
	if(expiresHours>0)
	{
		var date=new Date();
		date.setTime(date.getTime()+expiresHours*3600*1000);
		cookieString=cookieString+"; expires="+date.toGMTString();
	}
	document.cookie=cookieString;
}
	
function deleteCookie(name)
{
	var date=new Date(); 
	date.setTime(date.getTime()-10000); 
	var cookieString=name+"=v; expires="+date.toGMTString();
	document.cookie=cookieString;
};

function getCookie(name)
{
	var strCookie=document.cookie; 
	var arrCookie=strCookie.split("; "); 
	for(var i=0;i<arrCookie.length;i++)
	{ 
		var arr=arrCookie[i].split("="); 
		if(arr[0]==name)
		{
			return arr[1]; 
		}
	} 
	return ""; 
};

function deleteCookieDelay(name,value,delayTime)
{
	var cookieString=name+"="+escape(value);
	var date=new Date(); 
	date.setTime(date.getTime()+delayTime*1000);
	cookieString=cookieString+"; expires="+date.toGMTString();
	document.cookie=cookieString;
};