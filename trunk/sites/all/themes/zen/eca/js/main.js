/**
 * @author valderama
 */

$(document).ready(function(){    
  
  var tabs;
  
    
  $.address.init(function(event) {   
      //TABS
      tabs = $('#tabs').tabs({
      // Content filter
      load: function(event, ui) {
          $(ui.panel).html($('#tabs div:first', ui.panel).html());
      },
      selected: $('#tabs ul:first a').index($('a[rel=address:' + event.value + ']'))
      });

     
     
      
  }).change(function(event) {     
      
      var selection = $('a[rel=address:' + event.value + ']');
      
      //alert("change " + $.address.value() + " | event.value: " + event.value + " | selection.attr('href'): " + selection.attr('href') + " | tabs: " +  tabs);
      tabs.tabs('select', selection.attr('href'));
      $.address.title($.address.title().split(' | ')[0] + ' | ' + selection.text());
  });
      
    
    //RESIZEABLE
    /*$(".resizable-sidebox").resizable({
			maxWidth: 240,
			minHeight: 150,
			minWidth: 240
		});*/
   
   //TOOLTIP
   $(".tooltip").tooltip({
     showURL: false,
     positionLeft: true
   });
   
   //EXPAND / COLLAPSE
    $(".expand-button").toggle( 
      function(){
        $(this).parent().height( $(this).parent().data("initialHeight") );
        $(this).css("background-position", "0px -60px");
        //$(this).parent().css({"background": "none"});
        this.blur();
      },
      function(){
        $(this).parent().height(170);
        $(this).css("background-position", "0 -30px");
         //$(this).parent().css({"background": "url(img/sidebox-fade.png) bottom x-repeat"});
        this.blur();
      }
    );
    
    $(".collapsible-sidebox").each(function(){
      //alert( "height:" + $(this).height() );
      if($(this).height() > 170){
        $(this).data("initialHeight",$(this).height());
        $(this).height(170);
        //alert($(this).data("initialHeight"));
        
      } 
      else {
        $(this).children(".expand-button").hide();
      }       
    });
    
    //DIALOG
    $('a.dialog-link').click( function(){
      
      //add loader element
      mouse_pos = $(this).offset();
      var loader = $('<div class="ajax-loader"></div>').prependTo('#page');
      loader.css({'left': mouse_pos.left + ($(this).width()/2) - (loader.width()/2), 'top': mouse_pos.top - (loader.height()/2) });
      loader.click ( function(){
        $(this).remove();
      });
      
      //callback when ajax request loaded
      var pageLoaded = function(data){
        var removeDialog = function(){
          $('#dialog-box').remove();
        }
        
        loader.remove();
        $('#page').prepend(data);          
        $('#dialog-box').dialog({
          modal: true, title: '', show: 'clip', close: removeDialog, width: 450
        });        
      }      
      
      //start the ajax request
      $.ajax({ type: 'POST', url: this.href, dataType: 'html', success: pageLoaded, data: 'js=1' });
      
      //prevent 'normal' link behaviour
      return false;      
    });    
});

function expand_block(){
  alert("do something!");
}
