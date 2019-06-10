$(function () {
    /*下拉框
    ********************/
    //selectSingleBoxInit($(".selectSingleBox"));
    
    //selectMultipleBoxInit($(".selectMultipleBox"));
});

(function ($) {
    /*下拉框
    ********************/
    $.fn.webumcSelect = function (attrName, value) {
        switch (attrName) {
            case "disabled":
            {
            	var $selectVal = $(this).find(".selectVal");
            	if( value ){
            		$selectVal.addClass("selectVal_disabled");
					$selectVal.find("input").addClass("input_text_disabled");
					$selectVal.find("span").addClass("span_select_img_disabled");
            	}else{
            		$selectVal.removeClass("selectVal_disabled");
					$selectVal.find("input").removeClass("input_text_disabled");
					$selectVal.find("span").removeClass("span_select_img_disabled");
            	}
                break;
            }
            default:
                break;
        }
    }
})(jQuery);

(function($){
	$.fn.extend({
		/*下拉菜单栏  - 单选
		********************/
		selectSingleBoxInit : function(){
			//添加滚动条
			var nObjScroll = this.find(".wraper_select .slider").length;
			if( nObjScroll == 1 ){
				var objScroll = new customBar( this.find(".wraper_select .slider").get(0), 
					this.find(".wraper_select .pannel").get(0), this.find(".wraper_select .drag").get(0));
			}

			//重置控件宽度
			var fwidth_select = parseFloat( this.css("width") );
			this.find(".selectVal").css("width", fwidth_select);
			this.find(".selectVal input").css("width", (fwidth_select - 18));
			this.find(".wraper_select").css("width", fwidth_select);
			this.find("ul").css( "width", fwidth_select );
	
			this.click(function () {
				var $selectVal = $(this).find(".selectVal");
				var $inputText = $(this).find(".selectVal input");
	            var $selectWraper = $(this).find(".wraper_select");
	            var $selectBoxUl = $(this).find("ul");

	            if ( !$selectVal.hasClass("selectVal_disabled") && $selectBoxUl.is(":hidden") ) {
	                $(this).css({ "z-index": "100" });
	                $selectWraper.css({ "display": "block" });
	                $selectBoxUl.slideDown("fast", function () {
	                	if( nObjScroll == 1 ){
	                		objScroll.init();
	                	}
	                });
	
	                var selectIndex = 0;
	                if ( !!$inputText.val() )
	                {
						var strFind = $inputText.val();
						var numReg = /(\d)/gi;
						var strResNum = strFind.replace( numReg, "" );
						if( "" == strResNum ){
							strFind = parseInt(strFind);
						}
	
	                	selectIndex = $selectBoxUl.find("li[value=" + strFind + "]").index();
	                }
	                $selectBoxUl.find("li").eq(selectIndex).addClass("selected_hover");
	            }
	        }).mouseover(function () {
	            var $selectVal = $(this).find(".selectVal");
				if ( !$selectVal.hasClass("selectVal_disabled") ) {
	                ctrlSelectValHoverState($selectVal, true);
	            }
	        }).mouseleave(function () {
				var $selectVal = $(this).find(".selectVal");
	            if ( !$selectVal.hasClass("selectVal_disabled") ) {
	                ctrlSelectValHoverState($selectVal, false);
	
	                if (!$(this).find("ul").is(":hidden")) {
	                    $(this).find("ul").slideUp("fast", function () {});
	                }
	                $(this).find(".wraper_select").css({ "display": "none" });
	                $(this).css({ "z-index": "1" });
	            }
	        });
	
	        this.find("li").mouseover(function () {
	            $(this).parent().find(".selected_hover").removeClass("selected_hover");
	            $(this).addClass("selected_hover");
	        }).mouseleave(function () {
	            $(this).removeClass("selected_hover");
	        }).click(function () {
	            var $ul = $(this).parent();
	
				//小于10的数字显示01、02...
				var strShow = $(this).attr("value");
				var numReg = /(\d)/gi;
				var strResNum = strShow.replace( numReg, "" );
				if( "" == strResNum && parseInt(strShow) < 10 && parseInt(strShow) != 0 ){
					strShow = "0" + strShow;
				}
	            $ul.parents(".selectSingleBox").find(".selectVal input").val( strShow );
	
	            $ul.slideUp("fast", function () {});
	            $ul.parents(".selectSingleBox").find(".wraper_select").css({ "display": "none" });
	            $ul.parents(".selectSingleBox").css({ "z-index": "1" });
	            
	            var $selectVal = $ul.parents(".selectSingleBox").find(".selectVal");
	            ctrlSelectValHoverState($selectVal, false);
	            return false;
	        });
		},
		
		/*下拉菜单栏  - 多选
		********************/
		selectMultipleBoxInit : function() {
			//添加滚动条
			var nObjScroll = this.find(".wraper_select .slider").length;
			if( nObjScroll == 1 ){
				var objScroll = new customBar( this.find(".wraper_select .slider").get(0), 
					this.find(".wraper_select .pannel").get(0), this.find(".wraper_select .drag").get(0));
			}

			//重置控件宽度
			var fwidth_select = parseFloat( this.css("width") );
			this.find(".selectVal").css("width", fwidth_select);
			this.find(".selectVal input").css("width", (fwidth_select - 18));
			this.find(".wraper_select").css("width", fwidth_select);
			this.find("ul").css( "width", fwidth_select );
	
			this.click(function () {
				var $selectVal = $(this).find(".selectVal");
				var $inputText = $(this).find(".selectVal input");
	            var $selectWraper = $(this).find(".wraper_select");
	            var $selectBoxUl = $(this).find("ul");
	
	            if ( !$selectVal.hasClass("selectVal_disabled") && $selectBoxUl.is(":hidden") ) {
	                $(this).css({ "z-index": "100" });
	                $selectWraper.css({ "display": "block" });
	                $selectBoxUl.slideDown("fast", function () {
	                	if( nObjScroll == 1 ){
	                		objScroll.init();
	                	}
	                });
	
	                if ( !!$inputText.val() )
	                {
						var strFind = $inputText.val();
						var arrFind = strFind.split("; ");
						var wFindLen = strFind.split("; ").length;
						var numReg = /(\d)/gi;
						for( var i = 0; i < wFindLen; i++ ){
							var strItem = arrFind[i];
							var strResNum = strItem.replace( numReg, "" );
							if( "" == strResNum ){
								strItem = parseInt(strItem);
							}
							
							var selectIndex = $selectBoxUl.find("li[value=" + strItem + "]").index();
							//$selectBoxUl.find("li").eq(selectIndex).addClass("selected_hover");
							$selectBoxUl.find("li").eq(selectIndex).find("input").get(0).checked = true;
						}
	                } 
	            }
	        }).mouseover(function () {
	            var $selectVal = $(this).find(".selectVal");
				if ( !$selectVal.hasClass("selectVal_disabled") ) {
	                ctrlSelectValHoverState($selectVal, true);
	            }
	        }).mouseleave(function () {
	           var $selectVal = $(this).find(".selectVal");
	            if ( !$selectVal.hasClass("selectVal_disabled") ) {
	                ctrlSelectValHoverState($selectVal, false);
	
	                if (!$(this).find("ul").is(":hidden")) {
	                    $(this).find("ul").slideUp("fast", function () {});
	                }
	                $(this).find(".wraper_select").css({ "display": "none" });
	                $(this).css({ "z-index": "1" });
	            }
	        });
	
	        this.find("li").mouseover(function () {
	            $(this).parent().find(".selected_hover").removeClass("selected_hover");
	            $(this).addClass("selected_hover");
	        }).mouseleave(function () {
	            $(this).removeClass("selected_hover");
	        }).click(function () {
	            var $ul = $(this).parent();
	
				if( $(this).find("input:checked").length > 0 ){
	            	$(this).find("input").get(0).checked = false;
	            }else{
	            	$(this).find("input").get(0).checked = true;
	            }
	            
	            var strSelectShow = "";
	            var arr$DomLiItem = $ul.find("li");
	            for( var i = 0; i < arr$DomLiItem.length; i++ ){
	            	var domLiItem = arr$DomLiItem[i];
	             	if( $(domLiItem).find("input:checked").length > 0 ){
	            		var strShow = $(domLiItem).attr("value");
						var numReg = /(\d)/gi;
						var strResNum = strShow.replace( numReg, "" );
						if( "" == strResNum && parseInt(strShow) < 10 && parseInt(strShow) != 0 ){
							strShow = "0" + strShow;
						}
				
						if( "" == strSelectShow ){
							strSelectShow = strShow;
						}else{
							strSelectShow = strSelectShow + "; " + strShow;
						}
	            	}
	            }
	            
	            $ul.parents(".selectMultipleBox").find(".selectVal input").val( strSelectShow );
	        });
		}

	})
})(jQuery);

function onSelectMultipleCheckboxClick(obj)
{
	$(obj).parent().click();
};

function ctrlSelectValHoverState($selectVal, bHover)
{
	if( bHover ){
		$selectVal.addClass("selectVal_hover");
        $selectVal.find("input").addClass("input_text_hover");
        $selectVal.find("span").addClass("span_select_img_hover");
	}else{
		$selectVal.removeClass("selectVal_hover");
		$selectVal.find("input").removeClass("input_text_hover");
		$selectVal.find("span").removeClass("span_select_img_hover");
	}
};