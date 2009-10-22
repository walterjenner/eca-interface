<?php 
//FOR NEW ROW STYLES, display types, style types, argument default handlers and argument validators

function artwork_views_data(){
  $data = array();
  $data['artwork']['table']['group'] = t('Artwork');
  $data['compartdb_creating']['table']['group'] = t('Creating CA');
  $data['compartdb_agent']['table']['group'] = t('Agent CA');
  $data['compartdb_artwork']['table']['group'] = t('Artwork CA');
   
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
  
  /*
  $data['agent']['table']['group'] = t('Creating table');
  $data['agent']['table']['title'] = t('Creating table');
  $data['agent']['table']['help'] = t('The Creating table in the compart DB');
  
  //connect agent with node
  $data['agent']['table']['join']['node'] = array(
    'left_field' => 'nid',
    'field' => 'nid',
  );*/
  
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
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
  );
  /*$data['artwork']['creation_year'] = array(
    'title' => t('creation_year'),
    'help' => t('A string describing the creation year'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
  );*/
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
   /* I AM NOT USING THIS APPROACH ANYMORE, as explain in the field handler file     
    $data['compartdb_agent']['last_name'] = array(
     'title' => t('Artist'),
     'help' => t('Artist'),
     'field' => array(
       'handler' => 'artwork_handler_field_agent_list',
       'click sortable' => TRUE,
     ),
     'argument' => array(
      'handler' => 'eca_main_handler_argument_agent_id',
      'empty field name' => t('No Agent'),
      'numeric' => TRUE,
    ),
   );*/
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
  
  /*
  $data['agent']['agent_id'] = array(
    'title' => t('Artwork ID'),
    'help' => t('Artwork ID'), 
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
  ); */
  
  //$data['compartdb_creating']['table']['group'] = t('Creating table');
  //$data['compartdb_creating']['table']['title'] = t('Creating table');
  //$data['compartdb_creating']['table']['help'] = t('The Creating table in the compart DB');
  
  //connect node via artwork table with creating table
  /* REMOVE THIS CONNECTIONS FOR TESTING
  $data['compartdb_creating']['table']['join']['agent'] = array(
    'left_field' => 'agent_id',
    'field' => 'agent_id',
  );
  
  $data['compartdb_creating']['agent_id'] = array(    
    'title' => t('agent id'),
    'help' => t('agent id'), 
    'field' => array(
      'title' => 'Artists who created this artwork',
      'help' => 'Artists who created this artwork',
      'handler' => 'artwork_handler_field_artwork_agents',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_many_to_one',
      'empty field name' => t('No agent'),
      'numeric' => TRUE,
    ),
  );*/
  
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
        'artwork_handler_field_agent_list' => array(
          'parent' => 'views_handler_field_prerender_list' ),
        'eca_main_handler_argument_agent_id' => array(
          'parent' => 'views_handler_argument_many_to_one', 
          'path' => drupal_get_path('module', 'eca_main') )
    ),
  );
}