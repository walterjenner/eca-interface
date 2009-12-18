<?php 
function institution_views_data(){
  $data = array();
  
  //INSTITUTIONS
  //BASE TABLE
  $data['compartdb_institution']['table']['base'] = array(
    'field' => 'institution_id', // the exhibit module function render() needs this var to be set!!!
    'publication_id' => 'Primary key',
    'title' => t('Institution'),
    'help' => t('Institutions in the compart DB'),
    'weight' => -10,
  );
  
  //tables
  $data['compartdb_institution']['table']['group'] = t('Institution');
  //$data['compartdb_authorship']['table']['group'] = t('Authorship table');
  $data['compartdb_institution_type']['table']['group'] = t('Institution Type');  
  $data['institution']['table']['group'] = t('Institution Mapping');
  
  //connections
  $data['institution']['table']['join']['compartdb_institution'] = array(    
    'left_field' => 'institution_id',
    'field' => 'institution_id',
  );
  $data['compartdb_institution_type']['table']['join']['compartdb_institution'] = array(    
    'left_field' => 'institution_type_id',
    'field' => 'institution_type_id',
  );
  $data['node']['table']['join']['institution'] = array(    
    'left_field' => 'nid',
    'field' => 'nid',
  );  
  
  //fields
  $data['compartdb_institution']['institution_id'] = array(
    'title' => t('Institution ID'),
    'help' => t('The ID of the Institution'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['compartdb_institution']['name'] = array(
    'title' => t('Name'),
    'help' => t('The Name of the Institution'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    )
  );  
  $data['compartdb_institution']['description'] = array(
    'title' => t('Description'),
    'help' => t('The Description of the Institution'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    )
  );  
  $data['compartdb_institution_type']['name'] = array(
    'title' => t('name'),
    'help' => t('Institution Type Name'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
  ); 
  $data['institution']['institution_id'] = array(
    'title' => t('Institution ID'),
    'help' => t('Institution ID'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );    
  $data['institution']['nid'] = array(
    'title' => t('Institution Node'),
    'help' => t('The Node of the Institution'),
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
  
 return $data;
}

/**
 * Implementation of hook_views_handlers() to register all of the basic handlers
 * views uses.
 */
function institution_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'institution') . '',
    ),
    'handlers' => array(
    ),
  );
}