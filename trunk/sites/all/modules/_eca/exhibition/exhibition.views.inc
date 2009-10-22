<?php 
function exhibition_views_data(){
  $data = array();
  
  $data['exhibition']['table']['group'] = t('Exhibition');
  $data['compartdb_exhibition']['table']['group'] = t('Exhibition CA');
  $data['compartdb_exhibition_type']['table']['group'] = t('Exhibition CA');
  $data['compartdb_exhibits_in']['table']['group'] = t('Exhibits_In CA');
  $data['compartdb_showing_artwork']['table']['group'] = t('Shown_At CA');
    
  //set up the join-chain
  $data['exhibition']['table']['join']['node'] = array(
    'left_field' => 'nid',
    'field' => 'nid',
  );  
  $data['compartdb_exhibition']['table']['join']['node'] = array(
    'left_table' => 'exhibition',
    'left_field' => 'exhibition_id',
    'field' => 'exhibition_id',
  );
  $data['compartdb_exhibition_type']['table']['join']['node'] = array(
    'left_table' => 'compartdb_exhibition',
    'left_field' => 'exhibition_type_id',
    'field' => 'exhibition_type_id',
  );
  $data['compartdb_exhibits_in']['table']['join']['node'] = array(
    'left_table' => 'exhibition',
    'left_field' => 'exhibition_id',
    'field' => 'exhibition_id',
  );
   $data['compartdb_showing_artwork']['table']['join']['node'] = array(
    'left_table' => 'artwork',
    'left_field' => 'artwork_id',
    'field' => 'artwork_id',
  );
  
  
  //fields
  $data['exhibition']['nid'] = array(
     'title' => t('The node id of the Exhibition'),
     'help' => t('The node id of the Exhibition.'),
   );   
   $data['exhibition']['exhibition_id'] = array(
     'title' => t('Exhibition ID'),
     'help' => t('Exhibition ID'),
     'field' => array(
       'handler' => 'views_handler_field_numeric',
       'click sortable' => TRUE,
     ),
   );   
   $data['compartdb_exhibition']['exhibition_type_id'] = array(
     'title' => t('Exhibition Type ID'),
     'help' => t('Exhibition Type ID'),
     'field' => array(
       'handler' => 'views_handler_field_numeric',
       'click sortable' => TRUE,
     ),
     'argument' => array(
      'handler' => 'views_handler_argument',
      'empty field name' => t('No type'),
      'numeric' => TRUE,
    ),
   );
   $data['compartdb_exhibition_type']['name'] = array(
     'title' => t('Exhibition Type Name'),
     'help' => t('Exhibition Type Name'),
     'field' => array(
       'handler' => 'views_handler_field',
       'click sortable' => TRUE,
     )
   );
   $data['compartdb_exhibits_in']['agent_id'] = array(
     'title' => t('Agent ID'),
     'help' => t('Agent ID'),
     'field' => array(
       'handler' => 'exhibition_handler_field_agent_list',
       'click sortable' => TRUE,
     ),
     'argument' => array(
      'handler' => 'eca_main_handler_argument_agent_id',
      'name field' => 'last_name',
      'name table' => 'compartdb_agent',
      'empty field name' => t('No Agent'),
      'numeric' => TRUE,
    ),
   );
   $data['compartdb_showing_artwork']['exhibition_id'] = array(
     'title' => t('Exhibition ID'),
     'help' => t('Exhibition ID'),
     'field' => array(
       'handler' => 'exhibition_handler_field_agent_list',
       'click sortable' => TRUE,
     ),
     'argument' => array(
      'handler' => 'exhibition_handler_argument_exhibition_id',
      'empty field name' => t('No Exhibition'),
      'numeric' => TRUE,
    ),
   );
  
  return $data;
}

/**
 * Implementation of hook_views_handlers() to register all of the basic handlers
 * views uses.
 */
function exhibition_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'exhibition') . '',
    ),
    'handlers' => array(
        'exhibition_handler_field_agent_list' => array(
          'parent' => 'views_handler_field_prerender_list', ),
        'eca_main_handler_argument_agent_id' => array(
          'parent' => 'views_handler_argument_many_to_one', 
          'path' => drupal_get_path('module', 'eca_main') ),
        'exhibition_handler_argument_exhibition_id' => array(
          'parent' => 'views_handler_argument_many_to_one' )
    ),
  );
}