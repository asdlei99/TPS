/**
 * @author shicheng
 */
var arrMessage = new Array();
var MAX_MESSAGE_LEN = 6;

$(document).ready(function(){
	$(".a_ntymessagebox_close").click(function(){
		$(".div_popupdialogbg").css("visibility","hidden");
		$(".div_ntymessagebox").css("visibility","hidden");
	});
	
	$(".button_ntymessagebox_clear").click(function(){
		arrMessage = [];
		$('.div_ntymessagebox_list_item_content').text("");
		$('.div_ntymessagebox_list_item_data').text("");
		$(".div_ntymessagebox_list_item").css("visibility","hidden");
	});
});

function showNtyMessageBox()
{
	$(".div_popupdialogbg").css("visibility","visible");
	$(".div_ntymessagebox").css("visibility","visible");
};

function addNtyMessageBox(strMessage)
{
	if ( arrMessage.length == MAX_MESSAGE_LEN )
	{
		arrMessage.shift();
	}
	
	var strData = getNowFormatDate();
	
	arrMessage.push([strMessage,strData]);
	
	$(".div_ntymessagebox_list_item").each(function(index,element){
		switch(index){
			case 0:
			{
				$(this).children('div.div_ntymessagebox_list_item_content').text(arrMessage[arrMessage.length-1][0]);
				$(this).children('div.div_ntymessagebox_list_item_data').text(arrMessage[arrMessage.length-1][1]);
				break;
			}
			case 1:
			{
				if(arrMessage.length >= 2){
					$(this).children('div.div_ntymessagebox_list_item_content').text(arrMessage[arrMessage.length-2][0]);
					$(this).children('div.div_ntymessagebox_list_item_data').text(arrMessage[arrMessage.length-2][1]);
				}
				
				break;
			}
			case 2:
			{
				if(arrMessage.length >= 3){
					$(this).children('div.div_ntymessagebox_list_item_content').text(arrMessage[arrMessage.length-3][0]);
					$(this).children('div.div_ntymessagebox_list_item_data').text(arrMessage[arrMessage.length-3][1]);
				}
				
				break;
			}
			case 3:
			{
				if(arrMessage.length >= 4){
					$(this).children('div.div_ntymessagebox_list_item_content').text(arrMessage[arrMessage.length-4][0]);
					$(this).children('div.div_ntymessagebox_list_item_data').text(arrMessage[arrMessage.length-4][1]);
				}
				
				break;
			}
			case 4:
			{
				if(arrMessage.length >= 5){
					$(this).children('div.div_ntymessagebox_list_item_content').text(arrMessage[arrMessage.length-5][0]);
					$(this).children('div.div_ntymessagebox_list_item_data').text(arrMessage[arrMessage.length-5][1]);
				}
				
				break;
			}
			case 5:
			{
				if(arrMessage.length >= 6){
					$(this).children('div.div_ntymessagebox_list_item_content').text(arrMessage[arrMessage.length-6][0]);
					$(this).children('div.div_ntymessagebox_list_item_data').text(arrMessage[arrMessage.length-6][1]);
				}
				
				break;
			}
		}
	});
};