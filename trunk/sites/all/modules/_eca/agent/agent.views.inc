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
  //set up the exhibit_in field to use it as an argument. (to get a list of agents per exhibition)
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
          'parent' => 'views_handler_field_prerender_list' ),
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
