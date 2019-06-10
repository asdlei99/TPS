/**
 * @author shicheng
 */

function customBar(oSlider, oPanel, oTrigger){ 
	this.parent = oSlider.parentNode;
	this.slider = oSlider; 
	this.panel = oPanel;
	this.trigger = oTrigger;
	this.h1 = this.parent.clientHeight;
	this.h2 = this.slider.offsetHeight;
	this.h3 = this.panel.clientHeight;
	this.h4 = this.trigger.offsetHeight;
	this.k = (this.h2 - this.h1)/(this.h3 - this.h4);
	this.dis = 0;
	this.flag = false;
	this.init();
};

customBar.prototype = { 

	init: function(){
		this.h1 = this.parent.clientHeight;
		this.h2 = this.slider.offsetHeight;
		this.h3 = this.panel.clientHeight;
		this.h4 = this.trigger.offsetHeight;

		this.k = (this.h2 - this.h1)/(this.h3 - this.h4);
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

		this.slider.style.top = '0px';
		this.trigger.style.top = '0px';
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

		//使用鼠标滚轮滚动
		this.slider.onmousewheel = document.onmousewheel = function(e){
			that.wheel.call(that, e);
		}
		
		var isFirefox=(navigator.userAgent.indexOf('Gecko')!==-1);
		if(isFirefox){   //仅firefox
			AttachEvent(this.slider,'DOMMouseScroll',that.wheel, that );
		}
	},

	down: function(e){
		var e = window.event || e,
		y1 = e.y || e.pageY,
		y2 = parseInt(this.trigger.style.top);
		this.dis = (y1 - y2);
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
		y1 = e.y || e.pageY,
		dis = Math.min(Math.max(y1 - this.dis, 0), (this.h3 - this.h4));
		this.slider.style.top = -dis * this.k + 'px';
		this.trigger.style.top = dis + 'px';
	}, 

	up: function(){
		this.flag = false;
	},
	
	wheel: function(e){
		var e = window.event || e;
		var step = 20;
		if(e.wheelDelta < 0 || e.detail > 0) {
			if(parseInt(this.trigger.style.top) < (this.h3 - this.h4))
			{
				this.trigger.style.top = (parseInt(this.trigger.style.top)+step) + 'px';
				this.slider.style.top = -parseInt(this.trigger.style.top) * this.k + 'px';
			}
		} else {
			if(parseInt(this.trigger.style.top) > 0)
			{
				this.trigger.style.top = (parseInt(this.trigger.style.top)-step) + 'px';
				this.slider.style.top = -parseInt(this.trigger.style.top) * this.k + 'px';
			}
		}
		
		if(e.preventDefault){
			e.preventDefault();
		}
		if(e.stopPropagation){
			e.stopPropagation();
		}
		e.cancelBubble=true;
		e.returnValue=false;
		
		return false;
	}
};