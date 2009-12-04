/**
 * @author valderama
 */

function onArtworkShow( obj ){
  //$(obj).child("")tooltip();
  // console.log( "get child which is a link and add the tooltip" + obj );  
  
  $(obj).find(".artwork-tooltip").tooltip({ 
    bodyHandler: function() { 
        return $( $(obj).find("div.desc").html() ); 
    }, 
    showURL: false
  });
}

$(document).ready(function(){    
  
  var tabs;
  var carouselLength = 8;    
  
  //SERIES CAROUSEL
  var numArtworks = $('div#artwork-series-carousel > .carousel > ul').children().size(); 
  if( numArtworks > carouselLength ){
    $('div#artwork-series-carousel > .carousel').carousel({
      visible:carouselLength, circular: false, scroll:3, speed:1000
    });
    $('div#artwork-series-carousel > .carousel-prev').click(function() { $('div#artwork-series-carousel > .carousel').carousel('prev') });
    $('div#artwork-series-carousel > .carousel-next').click(function() { $('div#artwork-series-carousel > .carousel').carousel('next') });
  }
  else{
    $('div#artwork-series-carousel > .carousel-prev').hide();
    $('div#artwork-series-carousel > .carousel-next').hide();
  }
  
  //ARTWORKS CAROUSEL
  numArtworks = $('div#artworks-carousel > .carousel > ul').children().size(); 
  if( numArtworks > carouselLength ){
    $('div#artworks-carousel > .carousel').carousel({
      visible:carouselLength, circular: false, scroll:3, speed:1000
    });
    $('div#artworks-carousel > .carousel-prev').click(function() { $('div#artworks-carousel > .carousel').carousel('prev') });
    $('div#artworks-carousel > .carousel-next').click(function() { $('div#artworks-carousel > .carousel').carousel('next') });
  }
  else{
    $('div#artworks-carousel > .carousel-prev').hide();
    $('div#artworks-carousel > .carousel-next').hide();
  }
  
   //TOOLTIPS for carosel pictures
  $('.artwork-tooltip').tooltip( {showURL: false, showBody: ' - '} );
  
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
   
   //TOOLTIP
   $(".tooltip").tooltip({
     showURL: false,
     positionLeft: true
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
          modal: true, title: '', show: 'clip', close: removeDialog, width: 550
        });        
      }      
      
      //start the ajax request
      $.ajax({ type: 'POST', url: this.href, dataType: 'html', success: pageLoaded, data: 'js=1' });
      
      //add class to fake :visited state for this link - problem: reload
      //$(this).addClass("visited");
      
      //prevent 'normal' link behaviour
      return false;      
    });    
});
