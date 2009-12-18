<?php 

function agent_views_data(){
  $data = array();
  
  //BASE TABLE
  $data['compartdb_agent']['table']['base'] = array(
    'field' => 'agent_id', // the exhibit module function render() needs this var to be set!!!
    'agent_id' => 'Primary key',
    'title' => t('Agent'),
    'help' => t('An agent in the compart DB'),
    'weight' => -10,
  );
  
  $data['compartdb_agent']['table']['group'] = t('Agent');
  $data['agent']['table']['group'] = t('Agent Mapping');
  $data['compartdb_exhibits_in2']['table']['group'] = t('Exhibits_In CA');
  
  //conncections
  $data['agent']['table']['join']['compartdb_agent'] = array(    
    'left_field' => 'agent_id',
    'field' => 'agent_id',
  );
  $data['compartdb_exhibits_in2']['table']['join']['compartdb_agent'] = array(    
    'left_field' => 'agent_id',
    'field' => 'agent_id',
  );
  
  //fields
  $data['compartdb_agent']['first_name'] = array(
    'title' => t('First name'),
    'help' => t('First name'), 
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['compartdb_agent']['last_name'] = array(
    'title' => t('Last name'),
    'help' => t('Last name'), 
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['compartdb_agent']['description'] = array(
    'title' => t('Description'),
    'help' => t('Description'), 
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator_string',
    ),
  );
  $data['compartdb_agent']['title'] = array(
    'title' => t('Academic title'),
    'help' => t('Academic title'), 
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter',
    ),
  );
  $data['compartdb_agent']['pseudonym'] = array(
    'title' => t('Pseudonym'),
    'help' => t('Pseudonym'), 
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    )
  );
  $data['compartdb_agent']['gender'] = array(
    'title' => t('Gender'),
    'help' => t('Gender'), 
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
    ),
  );
  $data['compartdb_agent']['url'] = array(
    'title' => t('Web site'),
    'help' => t('Web site'), 
    'field' => array(
      'handler' => 'views_handler_field_url',
      'click sortable' => TRUE,
    )
  );
  $data['compartdb_agent']['email'] = array(
    'title' => t('Email Address'),
    'help' => t('Email Address'), 
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    )
  );
  $data['compartdb_agent']['birth_date'] = array(
    'title' => t('Birthdate'),
    'help' => t('Birthdate'), 
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
  $data['compartdb_agent']['death_date'] = array(
    'title' => t('Deathdate'),
    'help' => t('Deathdate'), 
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
  $data['compartdb_agent']['last_change'] = array(
    'title' => t('Timestamp of last Change'),
    'help' => t('Timestamp of last Change'), 
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
  $data['compartdb_agent']['permissions'] = array(
    'title' => t('Permissions'),
    'help' => t('Permissions'), 
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );  
  $data['agent']['agent_id'] = array(
    'title' => t('Agent ID'),
    'help' => t('Agent ID'), 
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    )
  );
  $data['agent']['nid'] = array(
    'title' => t('Agent Node'),
    'help' => t('The Agent Node'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'base' => 'node',
      'base_field' => 'nid'
    ),
  );  
  $data['compartdb_agent']['roles'] = array(
    'title' => t('Roles of this agent'),
    'help' => t('Roles of this agent'), 
    'field' => array(
      'handler' => 'agent_handler_field_roles',
      'click sortable' => TRUE,
    ),
  );
  $data['compartdb_illustrated_by']['table']['join']['compartdb_agent'] = array(
    'left_field' => 'agent_id',
    'field' => 'row_id',
    //'type' => 'inner', //to view just does nodes which have any media_file (might be a non-image)
    'extra' => array( 'table_id' => array(
                         'field' => 'table_id',
                         'operator' => '=',
                         'value' => '1',
                         'numeric' => true,
                       ),
                    ),
  );  
  $data['compartdb_media_file']['table']['join']['compartdb_agent'] = array(
    'left_table' => 'compartdb_illustrated_by',
    'left_field' => 'media_file_id',
    'field' => 'media_file_id',
  );
  
  //arguments
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
      'name field' => 'agent_id',
      'name table' => 'compartdb_agent',
      'empty field name' => t('No Agent'),
      'numeric' => TRUE,
    ),
   );  
  return $data;
}

function _agent_views_data(){
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
     'argument' => array(
      'handler' => 'exhibition_handler_argument_exhibition_id',
      'name field' => 'last_name',
      'name table' => 'compartdb_agent',
      'empty field name' => t('No Agent'),
      'numeric' => TRUE,
    ),
   );  
  
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
        'agent_handler_field_roles' => array(
          'parent' => 'views_handler_field_prerender_list' ),
        'exhibition_handler_argument_exhibition_id' => array(
          'parent' => 'views_handler_argument_many_to_one' , 
          'path' => drupal_get_path('module', 'exhibition') ),
    ),
  );
}
