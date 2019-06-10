/**
 * @author Administrator
 */
var hscroll = null;
var scroll = null;
$(document).ready(function(){
	//添加滚动条
	hscroll = new customHBar($(".hslider").get(0), $(".hpannel").get(0), $(".hdrag").get(0));
	scroll = new customBar($(".slider").get(0), $(".pannel").get(0), $(".drag").get(0));
});


/**
 * @author shicheng
 */

function customHBar(oSlider, oPanel, oTrigger){ 
	this.wraper = oSlider.parentNode;
	this.slider = oSlider; 
	this.panel = oPanel;
	this.trigger = oTrigger;
	this.wWraper = this.wraper.clientWidth;
	this.wSlider = this.slider.offsetWidth;
	this.wPanel = this.panel.clientWidth;
	this.wTrigger = this.trigger.offsetWidth;
	this.k = (this.wSlider - this.wWraper)/(this.wPanel - this.wTrigger);
	this.dis = 0;
	this.flag = false;
	this.init();
};

customHBar.prototype = { 

	init: function(){
		this.wWraper = this.wraper.clientWidth;
		this.wSlider = this.slider.offsetWidth;
		this.k = (this.wSlider - this.wWraper)/(this.wPanel - this.wTrigger);
		this.dis = 0;
		this.flag = false;
	
		if(this.k <= 0)
		{
			this.panel.style.display = 'none';
			return;
		}
		else
		{
			this.panel.style.display = 'block';
		}

		this.slider.style.left = '0px';
		this.trigger.style.left = '0px';
		this.bind();
	},

	bind: function(){
		var that = this;
		this.trigger.onmousedown = function(e){
			that.down.call(that, e);
			return false;
		}

		this.trigger.onmousemove = document.onmousemove = function(e){
			that.move.call(that, e);
		}

		this.trigger.onmouseup = document.onmouseup = function(e){
			that.up.call(that, e);
		} 
	},

	down: function(e){
		var e = window.event || e,
		x1 = e.x || e.pageX,
		x2 = parseInt(this.trigger.style.left);
		this.dis = (x1 - x2);
		this.flag = true;
		this.move(e);
		
		var that = this;
		document.onmousemove = function(e){
			that.move.call(that, e);
		}
		
		document.body.onselectstart = function(){return false};
	},

	move: function(e){
		if(!this.flag) return;
		var e = window.event || e,
		x1 = e.x || e.pageX,
		dis = Math.min(Math.max(x1 - this.dis, 0), (this.wPanel - this.wTrigger));
		this.slider.style.left = -dis * this.k + 'px';
		this.trigger.style.left = dis + 'px';
	}, 

	up: function(){
		this.flag = false;
	}
};