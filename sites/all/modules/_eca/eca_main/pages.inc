<?php

//include the file with the helper functions
require_once drupal_get_path('module', 'eca_main') . '/includes.inc';

/*
 * prints a publication
 */
function eca_main_publication( $id = 0 ){
  if( $id == 0 || !is_numeric($id))
    return drupal_not_found();
  
  $item = _load_publication($id);
  
  if(!$item)
    return drupal_not_found();
  
  $print_as_page = empty($_POST['js']);
  
  if( !$print_as_page )
    $output .= '<div id="dialog-box">';
    
  $output .= "<h3>Publication</h3>";
  foreach($item as $key => $field){
    if( $key == 'authors' )
      $output .= return_value( return_agents($field) , 'Author(s)' );
    else if( $key == 'media' ){
      $output .= 'Files:';
      foreach($field as $mediafile){
        $output .= $mediafile->file_name . '.' . $mediafile->format . ', ';
      }
    }
    else
      $output .= return_value( $field, $key);
  }  
  
  if( !$print_as_page )
    $output .= '</div>';
  
  //Check if it is a js call or not  
  if(empty($_POST['js'])){
    drupal_set_title($item->title);
    print theme('page', $output);
  }
  else{
    print $output;
  }
  exit();
}

function eca_main_collective( $id = 0 ){
  if( $id == 0 || !is_numeric($id) )
    return drupal_not_found();

  $item = _load_collective($id);
  
  if(!$item)
    return drupal_not_found();
  
  $print_as_page = empty($_POST['js']);
  
  if(!$print_as_page)
    $output .= '<div id="dialog-box">';
  
  foreach($item as $key => $field){
    if($key == 'agents')
      $output .= return_value( return_agents( $item['agents'] ), 'Members' );
    else
      $output .= return_value( $field, $key);
  } 
  
  if( !$print_as_page )
    $output .= '</div>';
  
  if(empty($_POST['js'])){
    drupal_set_title($item['name']);  
    print theme('page', $output);
  }
  else{
    print $output;
  }
  
  exit();
}

function eca_main_award( $id = 0 ){
  if( $id == 0 || !is_numeric($id) )
    return drupal_not_found();

  $item = _load_award($id);
  
  if(!$item)
    return drupal_not_found(); 
    
  $print_as_page = empty($_POST['js']);
  
  if( !$print_as_page )
    $output .= '<div id="dialog-box">';

  foreach($item as $key => $field){
    if($key == 'agents')
      $output .= return_value( return_agents( $item['agents'] ), 'Winners' );
    else
      $output .= return_value( $field, $key);
  }
  
  if( !$print_as_page )
    $output .= '</div>';
  
  //Check if it is a js call or not  
  if(empty($_POST['js'])){
    drupal_set_title($item['title']);
    print theme('page', $output);
  }
  else{
    print $output;
  }  
 
  exit();
}

function eca_main_institution( $id = 0 ){
  if( $id == 0 || !is_numeric($id) )
    return drupal_not_found();
  
  $item = _load_institution($id);
  
  if( !$item )
    return drupal_not_found();
  
  $print_as_page = empty($_POST['js']);
  
  if(!$print_as_page)
    $output .= '<div id="dialog-box">';
  
  foreach($item as $key => $field){
    if($key == 'happenings')
      $output .= return_value( return_happenings( $field ), "Happening(s)" ); 
    else if($key == 'exhibitions')
      $output .= return_value( return_happenings( $field ), "Exhibition(s) organized" );
    else if($key == 'artworks')
      $output .= return_value( return_artworks( $field ), "Artwork(s) owned" );  
    else if($key == 'collections')
      $output .= return_value( return_collections( $field ), "Collection(s) owned" );
    else if($key == 'citations')
      $output .= return_value( return_publications( $field ), "Cited in" );
    else
      $output .= return_value( $field, $key);
  }
  
  if(!$print_as_page)
    $output .= '</div>';
  
  if(empty($_POST['js'])){
    drupal_set_title($item->name);  
    print theme('page', $output);
  }
  else{
    print $output;
  }
  
  exit();
}

function eca_main_algorithm( $id = 0 ){
  if( $id == 0 || !is_numeric($id) )
   return drupal_not_found();

  $item = _load_algorithm($id);
  
  $output .= '<div id="dialog-box">';
  
  foreach($item as $key => $field){
    $output .= return_value( $field, $key);
  }
  
  $output .= '</div>';
  
  if(empty($_POST['js'])){
    drupal_set_title($item->ca_al_name);  
    print theme('page', $output);
  }
  else{
    print $output;
  }

  exit();
}

function eca_main_collection( $id = 0 ){
  if( $id == 0 || !is_numeric($id) )
    return drupal_not_found();
  
  $print_as_page = empty($_POST['js']);
  
  $item = _load_collection($id);
  
  //dpr($item);
  
  if(!$print_as_page)
    $output .= '<div id="dialog-box">';
  
  foreach($item as $key => $field){
    if($key == 'artworks')
      $output .= return_value( return_artworks( $field ), "Artwork(s)" );  
    else if($key == 'owners')
      $output .= return_value( return_owners( $field ), "Owner(s)" );
    else if($key == 'exhibitions')
      $output .= return_value( return_exhibitions( $field ), "Shown at(s)" );
    else
      $output .= return_value( $field, $key);
  }
  
  if(!$print_as_page)
    $output .= '</div>';
  
  if( $print_as_page ){
    drupal_set_title($item->name);  
    print theme('page', $output);
  }
  else{
    print $output;
  }
  
  exit();
}

function eca_main_agent( $id = 0 ){
  if( $id == 0 || !is_numeric($id) )
    return drupal_not_found();
  else{
     $agent = db_fetch_object(db_query("SELECT nid FROM agent WHERE agent_id = $id"));
     if(!$agent)
       return drupal_not_found();
     else
       return drupal_goto("node/$agent->nid");
  }
  exit();
}
function eca_main_exhibition( $id = 0 ){
  if( $id == 0 || !is_numeric($id) )
    return drupal_not_found();
  else{
     $node = db_fetch_object(db_query("SELECT nid FROM exhibition WHERE exhibition_id = $id"));
     if(!$node)
       return drupal_not_found();
     else
       return drupal_goto("node/$node->nid");
  }
  exit();
}

function eca_main_artwork( $id = 0 ){
  if( $id == 0 || !is_numeric($id) )
   return drupal_not_found();
  else{
     $node = db_fetch_object(db_query("SELECT nid FROM artwork WHERE artwork_id = $id"));
     if(!$node)
       return drupal_not_found();
     else
       return drupal_goto("node/$node->nid");
  }
  exit();
}

function _load_publication( $id ){
  
  if ($cached = cache_get("publication:$id", 'cache_eca')) {
    return $cached->data;
  }
  
  $select = "SELECT p.publication_id, p.title , p.booktitle, p.journal, p.volume, p.number, p.year, p.isbn, p.nr_pages, 
                    p.on_pages, p.edition, p.publisher, p.url, p.last_seen, p.format, p.duration, p.address, p.keywords, 
                    p.month, p.description,
                    pt.name AS type_name                   
             FROM compartdb.publication p  
             LEFT JOIN compartdb.publication_type pt 
             ON p.publication_type_id = pt.publication_type_id
             WHERE p.publication_id = $id";

  if( $item = db_fetch_object( db_query($select) ) ){
    //getAuthors
    $item->authors = array();
    $selectAuthors = "SELECT ca_a.first_name, ca_a.last_name, ca_as.agent_id, ca_as.as_editor
                      FROM compartdb.authorship ca_as
                      LEFT JOIN compartdb.agent ca_a
                      ON ca_as.agent_id = ca_a.agent_id
                      WHERE ca_as.publication_id = $id";
                      
    $resultAuthors = db_query( $selectAuthors );
    while( $author = db_fetch_object($resultAuthors) ){
      array_push( $item->authors, $author ); 
    }
    
    //getMedia
    $item->media = array();
    $item->media = eca_get_media( 30, $id );
  }
  
  //set cache,  minimum time 1 day
  cache_set("publication:$id", $item ,'cache_eca', time() + MIN_CACHE_LIFETIME);
  
  //dvm($item);
  return $item;
}

function _load_collective( $id ){
  
  if ($cached = cache_get("collective:$id", 'cache_eca')) {
    return $cached->data;
  }
  
  $collective = array();
  $collective['agents'] = array();
  
  $select = "SELECT c.name, c.description, a.last_name, a.first_name, aipa.agent_id
             FROM compartdb.collective c
             LEFT JOIN compartdb.agent_is_part_of aipa
             ON c.collective_id = aipa.collective_id
             LEFT JOIN compartdb.agent a
             ON a.agent_id = aipa.agent_id
             WHERE c.collective_id = $id";

  $res = db_query($select);
  while( $agent = db_fetch_object($res) ){
    $collective['name'] = $agent->name;
    $collective['description'] = $agent->description; 
    array_push($collective['agents'], $agent);
  }
  
  cache_set("collective:$id", $collective ,'cache_eca', time() + MIN_CACHE_LIFETIME);
  
  //print_r($collective);
  return $collective;
}

function _load_award( $id ){
  
  if ($cached = cache_get("award:$id", 'cache_eca')) {
    return $cached->data;
  }
  
  $award = array();
  $award['agents'] = array();
             
  $select = "SELECT aw.title, r.at_date, ag.last_name, ag.first_name, r.agent_id                
             FROM compartdb.award aw
             LEFT JOIN compartdb.receiving r
             ON aw.award_id = r.award_id
             LEFT JOIN compartdb.agent ag
             ON ag.agent_id = r.agent_id
             WHERE aw.award_id = $id";

  $res = db_query($select);
  while( $agent = db_fetch_object($res) ){
    $award['title'] = $agent->title;
    array_push($award['agents'], $agent);
  }
  
  cache_set("award:$id", $award ,'cache_eca', time() + MIN_CACHE_LIFETIME);
  
  //print_r($award);
  return $award;
}

function _load_institution( $id ){
  
  if ($cached = cache_get("institution:$id", 'cache_eca')) {
    return $cached->data;
  }
  
  $select = "SELECT i.name, i.url, i.email, i.description, it.name it_name, a.street, a.zip, a.pobox, a.additional, l.city, l.country            
             FROM compartdb.institution i
             LEFT JOIN compartdb.institution_type it
             ON i.institution_type_id = it.institution_type_id
             LEFT JOIN compartdb.address a
             ON i.address_id = a.address_id
             LEFT JOIN compartdb.location l 
             ON a.location_id = l.location_id
             WHERE i.institution_id = $id";
             
   $res = db_query($select);
   if( $institution = db_fetch_object($res) ){
      //getHappenings (which were shown there)
      $institution->happenings = array();
      $selectHappenings = "SELECT ca_e.name, ca_h.exhibition_id, ca_h.from_date, ca_h.to_date 
                            FROM compartdb.happening ca_h
                            LEFT JOIN compartdb.exhibition ca_e
                            ON ca_h.exhibition_id = ca_e.exhibition_id  
                            WHERE ca_h.institution_id = $id";
      $resultHappenings = db_query( $selectHappenings );
      while( $happening = db_fetch_object($resultHappenings) ){
        array_push( $institution->happenings, $happening );
      }
      
      //getExhibitions (that were organized there)
      $institution->exhibitions = array();
      $selectExhibitions = "SELECT ca_e.name, ca_o.exhibition_id 
                            FROM compartdb.organizing ca_o
                            LEFT JOIN compartdb.exhibition ca_e
                            ON ca_o.exhibition_id = ca_e.exhibition_id  
                            WHERE ca_o.institution_id = $id";
      $resultExhibitions = db_query( $selectExhibitions );
      while( $exhibition = db_fetch_object($resultExhibitions) ){
        array_push( $institution->exhibitions, $exhibition );
      }
      
      //getArtwork (that are owned by this i.)
      $institution->artworks = array();
      $selectArtworks = "SELECT ca_a.title, ca_o.artwork_id 
                            FROM compartdb.artwork_ownership ca_o
                            LEFT JOIN compartdb.artwork ca_a
                            ON ca_o.artwork_id = ca_a.artwork_id  
                            WHERE ca_o.institution_id = $id";
      $resultArtworks = db_query( $selectArtworks );
      while( $artwork = db_fetch_object($resultArtworks) ){
        array_push( $institution->artworks, $artwork );
      }
      
      //getCollections (that are owned by this i.)
      $institution->collections = array();
      $selectCollections = "SELECT ca_c.name, ca_o.collection_id 
                            FROM compartdb.collection_ownership ca_o
                            LEFT JOIN compartdb.collection ca_c
                            ON ca_o.collection_id = ca_c.collection_id  
                            WHERE ca_o.institution_id = $id";
      $resultCollections = db_query( $selectCollections );
      while( $collection = db_fetch_object($resultCollections) ){
        array_push( $institution->collections, $collection );
      }
      
      //getCitations (that are owned by this i.)
      $institution->citations = array();
      $selectCitations = "SELECT ca_p.title, ca_ic.publication_id 
                            FROM compartdb.institution_citation ca_ic
                            LEFT JOIN compartdb.publication ca_p
                            ON ca_ic.publication_id = ca_p.publication_id  
                            WHERE ca_ic.institution_id = $id";
      $resultCitations = db_query( $selectCitations );
      while( $citation = db_fetch_object($resultCitations) ){
        array_push( $institution->citations, $citation );
      }
      
      cache_set("institution:$id", $institution ,'cache_eca', time() + MIN_CACHE_LIFETIME);
      
      return $institution;
   }
   return;   
}

function _load_algorithm( $id ){
  
  if ($cached = cache_get("algorithm:$id", 'cache_eca')) {
    return $cached->data;
  }
  
  $select = "SELECT ca_al.name as ca_al_name, ca_al.description as ca_al_description, ca_al.code as ca_al_code, 
              ca_lang.name as ca_lang_name, ca_lang.description as ca_lang_description
              FROM compartdb.algorithm ca_al
              LEFT JOIN compartdb.language_type ca_lang
              ON ca_al.language_type_id = ca_lang.language_type_id
              WHERE ca_al.algorithm_id = $id";
   
   $item = db_fetch_object( db_query($select) );
   cache_set("algorithm:$id", $item ,'cache_eca', time() + MIN_CACHE_LIFETIME);
   
   return $item;
}

function _load_collection( $id ){
  
  if ($cached = cache_get("collection:$id", 'cache_eca')) {
    return $cached->data;
  }
  
  $select = "SELECT name, description FROM compartdb.collection WHERE collection_id = $id";
  
  $res = db_query($select);
  if( $collection = db_fetch_object($res) ){
    //ARTWORKS
    $collection->artworks = array();
    $selectArtworks = "SELECT ca_a.title, ca_a.artwork_id FROM compartdb.artwork_is_part_of ca_aipo LEFT JOIN compartdb.artwork ca_a ON  ca_aipo.artwork_id = ca_a.artwork_id WHERE ca_aipo.collection_id = $id";
    $resultArtworks = db_query( $selectArtworks );
    while($artwork = db_fetch_object($resultArtworks)){
      array_push($collection->artworks, $artwork);
    }
    
    //OWNERS
    $collection->owners = array('agents' => array(), 'institutions' => array());
    $selectOwners = "SELECT ca_co.agent_id, ca_co.institution_id FROM compartdb.collection_ownership ca_co WHERE ca_co.collection_id = $id";
    $resultOwners = db_query( $selectOwners );
    while($ownership = db_fetch_object($resultOwners)){
      if($ownership->agent_id != ''){
        if( $ownerAgent = db_fetch_object( db_query("SELECT n.title, n.nid FROM node n LEFT JOIN agent a ON n.nid = a.nid WHERE a.agent_id = $ownership->agent_id") ) ){
          array_push($collection->owners['agents'], $ownerAgent); 
        }
      }
      else if( $ownership->institution_id != '' ){
        if( $ownerInstitution = db_fetch_object( db_query("SELECT i.name, i.institution_id FROM compartdb.institution i WHERE i.institution_id = $ownership->institution_id") ) ){
          array_push($collection->owners['institutions'], $ownerInstitution); 
        }
      }
    }
    
    //SHOWN AT EXIBITIONS
    $collection->exhibitions = array();
    $selectExhibitions = "SELECT ca_e.name, ca_e.exhibition_id FROM compartdb.showing_collection ca_sc LEFT JOIN compartdb.exhibition ca_e ON ca_sc.exhibition_id = ca_e.exhibition_id WHERE ca_sc.collection_id = $id";
    $resultExhibitions = db_query( $selectExhibitions );
    while( $exhibition = db_fetch_object( $resultExhibitions ) ){
      array_push( $collection->exhibitions, $exhibition );  
    }
  }
  
   cache_set("collection:$id", $collection ,'cache_eca', time() + MIN_CACHE_LIFETIME);
  
  return $collection;
}
      
     
