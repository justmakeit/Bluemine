/* this is most likely going to be in Drupal settings or else somehow inline eventually */
jQuery(document).bind("mobileinit", function(){
  $ = jQuery;
  $.extend(  $.mobile , {
   // ajaxEnabled: false
  });
});