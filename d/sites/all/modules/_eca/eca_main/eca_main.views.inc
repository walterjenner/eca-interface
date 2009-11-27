<?php 
//FOR NEW ROW STYLES, display types, style types, argument default handlers and argument validators

function eca_main_views_data(){
  $data = array();
  
  //BASE TABLE
  $data['publication']['table']['base'] = array(
    'field' => 'publication_id', // the exhibit module function render() needs this var to be set!!!
    'publication_id' => 'Primary key',
    'title' => t('Publication'),
    'help' => t('The unique ID of a publication in the compart DB'),
    'database' => 'compart',
    'weight' => -10,
  );
  
  //TABLES
  $data['publication']['table']['group'] = t('Publication');
  $data['publication_type']['table']['group'] = t('Publication Type');
  $data['authorship']['table']['group'] = t('Authorship table');
  
  //CONNECTIONS
  $data['publication_type']['table']['join']['publication'] = array(    
    'left_field' => 'publication_type_id',
    'field' => 'publication_type_id',
  );
  //link authorship with publication table
  $data['authorship']['table']['join']['publication'] = array(    
    'left_field' => 'publication_id',
    'field' => 'publication_id',
  );
  //link authorship with agent table
  $data['authorship']['table']['join']['agent'] = array(    
    'left_field' => 'agent_id',
    'field' => 'agent_id',
  );
  
  //FIELDS
  $data['publication']['publication_id'] = array(
    'title' => t('Publication ID'),
    'help' => t('The ID of the Publication'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );   
  $data['publication']['title'] = array(
    'title' => t('Title'),
    'help' => t('The Title of the Publication'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );  
  $data['publication']['description'] = array(
    'title' => t('Description'),
    'help' => t('The Description of the Publication'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    )
  );  
  $data['publication']['year'] = array(
    'title' => t('Year'),
    'help' => t('Year of publication'), // The help that appears on the UI,
    // Information for displaying the nid
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
      'numeric' => TRUE
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'name field' => 'title', 
      'numeric' => TRUE,
      'validate type' => 'nid',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    )
  );  
  $data['publication_type']['name'] = array(
    'title' => t('name'),
    'help' => t('Publication Type Name'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
  );  
  $data['authorship']['agent_id'] = array(
    'real_field' => 'agent_id',
    'title' => t('Agent ID'),
    'help' => t('Agent ID'),    
    'field' => array(
      'title' => t('Authors'),
      'help' => t('Display all agents who are authors of this publication.'),
      'handler' => 'eca_main_handler_field_agent_list',
      /*'skip base' => 'term_data',*/
    ),
    'argument' => array(
      'handler' => 'eca_main_handler_argument_agent_id',
      'empty field name' => t('No agent'),
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
function eca_main_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'eca_main') . '',
    ),
    'handlers' => array(
        'eca_main_handler_field_agent_list' => array(
          'parent' => 'views_handler_field_prerender_list', ),
        'eca_main_handler_argument_agent_id' => array(
          'parent' => 'views_handler_argument_many_to_one', )
    ),
  );
}