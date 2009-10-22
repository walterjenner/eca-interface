<?php 

//FOR NEW ROW STYLES, display types, style types, argument default handlers and argument validators
//function hook_views_handlers(){}
//function hook_views_plugins(){}

function agent_views_data(){
  $data = array();
  $data['agent']['table']['group'] = t('Agent');
  $data['compartdb_exhibits_in2']['table']['group'] = t('Exhibits_In CA');
    
  //connections
  //connect agent with node
  $data['agent']['table']['join']['node'] = array(
    'left_field' => 'nid',
    'field' => 'nid',
  );
  //seconds view on exhibits_in table, to define an alternating join with node
  $data['compartdb_exhibits_in2']['table']['join']['node'] = array(
    'left_table' => 'agent',
    'left_field' => 'agent_id',
    'field' => 'agent_id',
  );
  
  //fields
  $data['agent']['agent_id'] = array(
    'title' => t('Agent ID'),
    'help' => t('Agent ID'), 
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    )
  );  
  $data['agent']['roles'] = array(
    'title' => t('Roles of this agent'),
    'help' => t('Roles of this agent'), 
    'field' => array(
      'handler' => 'agent_handler_field_roles',
      'click sortable' => TRUE,
    ),
  );
  $data['compartdb_exhibits_in2']['exhibition_id'] = array(
     'title' => t('Exhibition ID'),
     'help' => t('Exhibition ID'),
     'field' => array(
       'handler' => 'exhibition_handler_field_agent_list',
       'click sortable' => TRUE,
     ),
     'argument' => array(
      'handler' => 'exhibition_handler_argument_exhibition_id',
      'name field' => 'last_name',
      'name table' => 'compartdb_agent',
      'empty field name' => t('No Agent'),
      'numeric' => TRUE,
    ),
   ); 
  
  
  //$data['compartdb_exhibits_in']['table']['group'] = t('Exhibits In'); 
  
  //link authorship with publication table
  /*$data['compartdb_exhibits_in']['table']['join']['node'] = array(    
    'left_table' => 'agent',
    'left_field' => 'agent_id',
    'field' => 'agent_id',
  );*/
  //link authorship with agent table
  //$data['authorship']['table']['join']['agent'] = array(    
  //  'left_field' => 'agent_id',
  //  'field' => 'agent_id',
  //);
  
  /*$data['compartdb_exhibits_in']['exhibition_id'] = array(
    'real_field' => 'exhibition_id',
    'title' => t('Exhibition ID'),
    'help' => t('Exhibition ID'),    
    'field' => array(
      'title' => t('Participated at exhibitions'),
      'help' => t('Display all exhibitions where this agent was part of.'),
      'handler' => 'agent_handler_field_exhibition_list',
    ),
    'argument' => array(
      'handler' => 'agent_handler_argument_exhibition_id',
      'name table' => 'node',
      'name field' => 'title',
      'empty field name' => t('No exhibition'),
      'numeric' => TRUE,
    ),
  );*/
 
  /* remove all connections for now
  $data['compartdb_creating']['table']['group'] = t('Creating');
  $data['compartdb_creating']['table']['title'] = t('Creating');
  $data['compartdb_creating']['table']['help'] = t('Creating: The Agent-Artwork Mapping table');
  
  //connect the creating table with the drupal agent table
  $data['compartdb_creating']['table']['join']['node'] = array(
    'left_table' => 'agent',
    'left_field' => 'agent_id',
    'field' => 'agent_id',
  );
  
  $data['compartdb_creating']['artwork_id'] = array(    
    'title' => t('artwork id'),
    'help' => t('artwork id'), 
    'field' => array(
      'title' => 'Artworks by Agent',
      'help' => 'The artworks this agent has created',
      'handler' => 'agent_handler_field_agent_artworks',
    ),
  );
  
  $data['compartdb_creating']['artwork_count'] = array(   
    'field' => array(
      'title' => 'Artwork Count',
      'help' => 'Number of Artworks by this Agent',
      'handler' => 'agent_handler_field_agent_artworks_count',
      'click sortable' => TRUE,
    ),
  );
  
  
  
  
  */
 /*
  //the drupal artwork table
  $data['artwork']['table']['group'] = t('Artwork');
  $data['artwork']['table']['title'] = t('Artwork');
  $data['artwork']['table']['help'] = t('The Drupal Artwork table');
  
  //connect the creating table with the drupal artwork table
  $data['compartdb_creating']['table']['join']['artwork'] = array(
    'left_field' => 'artwork_id',
    'field' => 'artwork_id',
  );
  
 $data['artwork']['nid'] = array(
    'title' => t('Agent ID'),
    'help' => t('Agent ID'), 
    'field' => array(
      'handler' => 'views_handler_field_node',
      'click sortable' => TRUE,
    ),
  ); */
  
  //print_r($data);
  return $data;
}

/**
 * Implementation of hook_views_handlers() to register all of the basic handlers
 * views uses.
 */
function agent_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'agent') . '',
    ),
    'handlers' => array(
        /*'agent_handler_field_agent_artworks' => array(
          'parent' => 'views_handler_field_prerender_list' ),
        'agent_handler_field_agent_artworks_count' => array(
          'parent' => 'views_handler_field_numeric' ),*/
        'agent_handler_field_roles' => array(
          'parent' => 'views_handler_field' ),
        /*'agent_handler_field_exhibition_list' => array(
          'parent' => 'views_handler_field_prerender_list', ),
        'agent_handler_argument_exhibition_id' => array(
          'parent' => 'views_handler_argument_many_to_one', ),*/
        'eca_main_handler_argument_agent_id' => array(
          'parent' => 'views_handler_argument_many_to_one', 
          'path' => drupal_get_path('module', 'eca_main') ),
        'exhibition_handler_argument_exhibition_id' => array(
          'parent' => 'views_handler_argument_many_to_one' , 
          'path' => drupal_get_path('module', 'exhibition') ),
    ),
  );
}
