<?php
// $Id: $

//include the file with the helper functions
require_once drupal_get_path('module', 'eca_main') . '/includes.inc';

/**
 * Field handler artwork thumbnail
 */
class artwork_handler_field_file_name extends views_handler_field {
 function construct() {
    parent::construct();
    $this->additional_fields['format'] = array('table' => 'compartdb_media_file', 'field' => 'format');
  } 

  function pre_render( $values ){
   //print_r($this->aliases);
   //print_r($values);
  }

  function render($values) {
    
    $media = new stdClass();
    $media->format = $values->compartdb_media_file_format;
    $media->file_name = $values->compartdb_media_file_file_name;
    
    if( eca_is_image($media) )
    {
      $path .= eca_get_media_path($media->format, 'thumbs');
 
      $path .= $values->compartdb_media_file_file_name;
      //$path .= '.' . $values->compartdb_media_file_format;
      $path .= '.jpg'; //as all thumbs are jpg?
      
      $output .= "<img src=\"$path\" alt=\"$media->file_name\" />";
      
      return $path;
    }
    else
      return '';
  }
}

