<?php
// $Id: views_handler_field_term_node_tid.inc,v 1.3 2009/04/07 22:02:40 merlinofchaos Exp $

/**
 * Field handler for terms.
 */
class agent_handler_field_roles extends views_handler_field {
//class views_handler_field_agent_artworks_count extends views_handler_field_prerender_list {
 function construct() {
    parent::construct();
    $this->additional_fields['agent_id'] = array('table' => 'agent', 'field' => 'agent_id');
  }

  function query() {
    $this->add_additional_fields();
    //$this->field_alias = $this->aliases['agent_id'];
    $this->field_alias = "roles";
  }

  function pre_render($values) {
    
    //print_r($this->field_alias);    
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
      db_set_active('compart');
      $result = db_query("SELECT creating.agent_id as agent_id, COUNT(artwork.artwork_id) as num_artworks FROM {artwork} INNER JOIN {creating} ON creating.artwork_id = artwork.artwork_id WHERE creating.agent_id IN (" . implode(', ', $agent_ids) . ") GROUP BY creating.agent_id");
      while ($agent = db_fetch_object($result)) {
        if($agent->num_artworks > 0)
          $values[$ids[$agent->agent_id]]->roles = t("Artist") . " "; 
      }
      $result2 = db_query("SELECT authorship.agent_id as agent_id, COUNT(publication.publication_id) as num_publications FROM {publication} INNER JOIN {authorship} ON authorship.publication_id = publication.publication_id WHERE authorship.agent_id IN (" . implode(', ', $agent_ids) . ")  GROUP BY authorship.agent_id");
      while ($agent2 = db_fetch_object($result2)) {
        if($agent2->num_publications > 0){
          if(!empty($values[$ids[$agent2->agent_id]]->roles))
            $values[$ids[$agent2->agent_id]]->roles .= t("and") . " ";
          
          $values[$ids[$agent2->agent_id]]->roles .= t("Author") . " ";
        }
       
      }
      db_set_active('default');
    }
    //return $value;
  }
}

