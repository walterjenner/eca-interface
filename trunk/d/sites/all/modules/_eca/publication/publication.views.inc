<?php 
function publication_views_data(){
  $data = array();
  
  //PUBLICATIONS
  //BASE TABLE
  $data['compartdb_publication']['table']['base'] = array(
    'field' => 'publication_id', // the exhibit module function render() needs this var to be set!!!
    'publication_id' => 'Primary key',
    'title' => t('Publication'),
    'help' => t('A publication in the compart DB'),
    'weight' => -10,
  );
  
  //tables
  $data['compartdb_publication']['table']['group'] = t('Publication');
  $data['compartdb_authorship']['table']['group'] = t('Authorship table');
  $data['compartdb_publication_type']['table']['group'] = t('Publication Type');  
  $data['publication']['table']['group'] = t('Publication Mapping');
  
  //connections
  $data['publication']['table']['join']['compartdb_publication'] = array(    
    'left_field' => 'publication_id',
    'field' => 'publication_id',
  );
  $data['compartdb_authorship']['table']['join']['compartdb_publication'] = array(    
    'left_field' => 'publication_id',
    'field' => 'publication_id',
  );
  $data['compartdb_publication_type']['table']['join']['compartdb_publication'] = array(    
    'left_field' => 'publication_type_id',
    'field' => 'publication_type_id',
  );
  $data['node']['table']['join']['publication'] = array(    
    'left_field' => 'nid',
    'field' => 'nid',
  );  
  
  //fields
  $data['compartdb_publication']['publication_id'] = array(
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
  $data['compartdb_publication']['title'] = array(
    'title' => t('Title'),
    'help' => t('The Title of the Publication'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    )
  );  
  $data['compartdb_publication']['description'] = array(
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
  $data['compartdb_publication']['year'] = array(
    'title' => t('Year'),
    'help' => t('Year of publication'), 
    'field' => array(
      'handler' => 'eca_main_handler_field_year',
      'click sortable' => TRUE,
      'numeric' => TRUE
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    )
  );
  $data['compartdb_publication_type']['name'] = array(
    'title' => t('name'),
    'help' => t('Publication Type Name'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
  ); 
  $data['publication']['publication_id'] = array(
    'title' => t('Publication ID'),
    'help' => t('Publication ID'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );    
  $data['publication']['nid'] = array(
    'title' => t('Publication Node'),
    'help' => t('The Node of the Publication'),
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
  $data['compartdb_authorship']['agent_id'] = array(
    'title' => t('Authorship Agent'),
    'help' => t('Authorship Agent'),
    'field' => array(
      'handler' => 'publication_handler_field_author_list',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    /*'relationship' => array( //weil es eine relationship zu mehreren ist, wirds kompliziert. den link zum agenten machen ich sowieso im field handler
      'base' => 'compartdb_agent',
      'base_field' => 'agent_id'
    ),*/
    'argument' => array(
      'handler' => 'eca_main_handler_argument_agent_id',
      'empty field name' => t('No agent'),
      'numeric' => TRUE,
    ),
  );  
  
  
 return $data;
}

/**
 * Implementation of hook_views_handlers() to register all of the basic handlers
 * views uses.
 */
function publication_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'publication') . '',
    ),
    'handlers' => array(
        'publication_handler_field_author_list' => array(
          'parent' => 'views_handler_field_prerender_list', ),
        'eca_main_handler_argument_agent_id' => array(
          'parent' => 'views_handler_argument_many_to_one', 
          'path' => drupal_get_path('module', 'eca_main') ),
        'eca_main_handler_field_year' => array(
          'parent' => 'views_handler_field_numeric', 
          'path' => drupal_get_path('module', 'eca_main') ),
    ),
  );
}