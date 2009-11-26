<?php 
//FOR NEW ROW STYLES, display types, style types, argument default handlers and argument validators

function artwork_views_data(){
  $data = array();
  $data['artwork']['table']['group'] = t('Artwork');
  $data['compartdb_creating']['table']['group'] = t('Creating CA');
  $data['compartdb_agent']['table']['group'] = t('Agent CA');
  $data['compartdb_artwork']['table']['group'] = t('Artwork CA');
  $data['compartdb_illustrated_by']['table']['group'] = t('Illustrated By CA');
  $data['compartdb_media_file']['table']['group'] = t('Media File CA');
   
  //connect drupal artwork table with node table
  $data['artwork']['table']['join']['node'] = array(
    'left_field' => 'nid',
    'field' => 'nid',
  );
  $data['compartdb_creating']['table']['join']['node'] = array(
    'left_table' => 'artwork',
    'left_field' => 'artwork_id',
    'field' => 'artwork_id',
  );
  $data['compartdb_artwork']['table']['join']['node'] = array(
    'left_table' => 'artwork',
    'left_field' => 'artwork_id',
    'field' => 'artwork_id',
  );   
  $data['compartdb_agent']['table']['join']['node'] = array(
    'left_table' => 'compartdb_creating',
    'left_field' => 'agent_id',
    'field' => 'agent_id',
  ); 
  $data['compartdb_illustrated_by']['table']['join']['node'] = array(
    'left_table' => 'artwork',
    'left_field' => 'artwork_id',
    'field' => 'row_id',
    /*'type' => 'inner', */ //to view just does nodes which have any media_file (might be a non-image)
    'extra' => array( 'table_id' => array(
                         'field' => 'table_id',
                         'operator' => '=',
                         'value' => '5',
                         'numeric' => true,
                       ),
                    ),
  );  
  $data['compartdb_media_file']['table']['join']['node'] = array(
    'left_table' => 'compartdb_illustrated_by',
    'left_field' => 'media_file_id',
    'field' => 'media_file_id',
  );  
  
  //fields
  $data['artwork']['artwork_id'] = array(
    'title' => t('Artwork ID'),
    'help' => t('Artwork ID'), 
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
  );
  $data['compartdb_artwork']['creation_year'] = array(
    'title' => t('creation_year'),
    'help' => t('A string describing the creation year'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
      'numeric' => TRUE
    ),
  );
  
  $data['compartdb_creating']['agent_id'] = array(
     'title' => t('Agent ID'),
     'help' => t('Agent ID'),
     'field' => array(
       'handler' => 'exhibition_handler_field_agent_list',
       'click sortable' => TRUE,
     ),
     'argument' => array(
      'handler' => 'eca_main_handler_argument_agent_id',
      'empty field name' => t('No Agent'),
      'numeric' => TRUE,
    ),
   );
   
   $data['compartdb_agent']['last_name'] = array(
     'title' => t('Artist'),
     'help' => t('Artist'),
     'field' => array(
       'handler' => 'artwork_handler_field_artwork_agents',
       'click sortable' => TRUE,
     ),
     'argument' => array(
      'handler' => 'eca_main_handler_argument_agent_id',
      'empty field name' => t('No Agent'),
      'numeric' => TRUE,
    ),
   );
  
  $data['compartdb_illustrated_by']['media_file_id'] = array(
    'title' => t('media_file_id'),
    'help' => t('media_file_id'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
  );  
  $data['compartdb_media_file']['file_name'] = array(
    'title' => t('file_name'),
    'help' => t('file_name'),
    'field' => array(
      'handler' => 'artwork_handler_field_file_name',
      'click sortable' => TRUE,
    ),
  );
  
  //print_r($data);
  return $data;
}

/**
 * Implementation of hook_views_handlers() to register all of the basic handlers
 * views uses.
 */
function artwork_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'artwork') . '',
    ),
    'handlers' => array(
        'artwork_handler_field_artwork_agents' => array(
          'parent' => 'views_handler_field_prerender_list' ),
        'artwork_handler_field_file_name' => array(
          'parent' => 'views_handler_field' ),
        'eca_main_handler_argument_agent_id' => array(
          'parent' => 'views_handler_argument_many_to_one', 
          'path' => drupal_get_path('module', 'eca_main') )
    ),
  );
}