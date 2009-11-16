<?php
// $Id: views_handler_field_term_node_tid.inc,v 1.3 2009/04/07 22:02:40 merlinofchaos Exp $

/**
 * Field handler for terms.
 */
class agent_handler_field_roles extends views_handler_field_prerender_list {
  function construct() {
    parent::construct();
    $this->additional_fields['agent_id'] = array('table' => 'agent', 'field' => 'agent_id');
  }

  function query() {
    $this->add_additional_fields();
    $this->field_alias = $this->aliases['agent_id'];
  }
  
  function pre_render($values) {
    $agent_ids = array();
    $this->items = array();
    
    foreach ($values as $result) {
      $agent_ids[] = $result->{$this->aliases['agent_id']};
    }
   // print_r($values);
    if ($agent_ids) {
      $result = db_query("SELECT ca_c.agent_id as agent_id, COUNT(ca_a.artwork_id) as num_artworks FROM {compartdb.artwork} as ca_a INNER JOIN {compartdb.creating} as ca_c ON ca_c.artwork_id = ca_a.artwork_id WHERE ca_c.agent_id IN (" . implode(', ', $agent_ids) . ") GROUP BY ca_c.agent_id");
      while ($agent = db_fetch_object($result)) {
        if($agent->num_artworks > 0)
          $this->items[$agent->agent_id]['artist'] = t('Artist');
      }
      $result2 = db_query("SELECT ca_a.agent_id as agent_id, COUNT(ca_p.publication_id) as num_publications FROM {compartdb.publication} as ca_p INNER JOIN {compartdb.authorship} as ca_a ON ca_a.publication_id = ca_p.publication_id WHERE ca_a.agent_id IN (" . implode(', ', $agent_ids) . ")  GROUP BY ca_a.agent_id");
      while ($agent2 = db_fetch_object($result2)) {
        if($agent2->num_publications > 0){         
          $this->items[$agent2->agent_id]['author'] = t('Author');
        }       
      }
      $result3 = db_query("SELECT ca_a.agent_id as agent_id, COUNT(ca_o.exhibition_id) as num_exhibitions FROM {compartdb.agent} as ca_a INNER JOIN {compartdb.organizing} as ca_o ON ca_a.agent_id = ca_o.agent_id WHERE ca_a.agent_id IN (" . implode(', ', $agent_ids) . ")  GROUP BY ca_a.agent_id");
      while ($agent3 = db_fetch_object($result3)) {
        if($agent3->num_exhibitions > 0){         
          $this->items[$agent3->agent_id]['Curator'] = t('Curator');
        }       
      }
      $result4 = db_query("SELECT ca_a.agent_id as agent_id, COUNT(ca_ao.artwork_id) as num_artworks FROM {compartdb.agent} as ca_a INNER JOIN {compartdb.artwork_ownership} as ca_ao ON ca_a.agent_id = ca_ao.agent_id WHERE ca_a.agent_id IN (" . implode(', ', $agent_ids) . ")  GROUP BY ca_a.agent_id");
      while ($agent4 = db_fetch_object($result4)) {
        if($agent4->num_artworks > 0){         
          $this->items[$agent4->agent_id]['Art Collectors'] = t('Art Collector');
        }       
      }
      $result5 = db_query("SELECT ca_a.agent_id as agent_id, COUNT(ca_co.collection_id) as num_artworks FROM {compartdb.agent} as ca_a INNER JOIN {compartdb.collection_ownership} as ca_co ON ca_a.agent_id = ca_co.agent_id WHERE ca_a.agent_id IN (" . implode(', ', $agent_ids) . ")  GROUP BY ca_a.agent_id");
      while ($agent5 = db_fetch_object($result5)) {
        if($agent5->num_artworks > 0){         
          $this->items[$agent5->agent_id]['Art Collectors'] = t('Art Collector');
        }       
      }            
     // print_r($this->items);
   }
    
  }
  
  
  function dep___pre_render($values) {
    $agent_ids = array();
    $ids = array();   
    
    //put all agent_ids into $agent_ids
    foreach ($values as $id => $result) {
      $agent_ids[] = $result->{$this->aliases['agent_id']};
      //save the row in $values where this agent_id occures
      $ids[$result->{$this->aliases['agent_id']}] = $id;
      
    }  
    //$i = 0;
    if ($agent_ids) {
      //db_set_active('compart');
      $result = db_query("SELECT compartdb_creating.agent_id as agent_id, COUNT(compartdb_artwork.artwork_id) as num_artworks FROM {compartdb_artwork} INNER JOIN {compartdb_creating} ON compartdb_creating.artwork_id = compartdb_artwork.artwork_id WHERE compartdb_creating.agent_id IN (" . implode(', ', $agent_ids) . ") GROUP BY compartdb_creating.agent_id");
      while ($agent = db_fetch_object($result)) {
        if($agent->num_artworks > 0)
          $values[$ids[$agent->agent_id]]->roles = t("Artist") . ""; 
      }
      $result2 = db_query("SELECT compartdb_authorship.agent_id as agent_id, COUNT(compartdb_publication.publication_id) as num_publications FROM {compartdb_publication} INNER JOIN {compartdb_authorship} ON compartdb_authorship.publication_id = compartdb_publication.publication_id WHERE compartdb_authorship.agent_id IN (" . implode(', ', $agent_ids) . ")  GROUP BY compartdb_authorship.agent_id");
      while ($agent2 = db_fetch_object($result2)) {
        if($agent2->num_publications > 0){
          if(!empty($values[$ids[$agent2->agent_id]]->roles))
            $values[$ids[$agent2->agent_id]]->roles .= t(",") . " ";
          
          $values[$ids[$agent2->agent_id]]->roles .= t("Author") . " ";
        }
       
      }
      //db_set_active('default');
    }
    //return $value;
  }
}

