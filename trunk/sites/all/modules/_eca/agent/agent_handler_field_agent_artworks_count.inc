<?php
// $Id: views_handler_field_term_node_tid.inc,v 1.3 2009/04/07 22:02:40 merlinofchaos Exp $

/**
 * Field handler for terms.
 */
class agent_handler_field_agent_artworks_count extends views_handler_field_numeric {
//class views_handler_field_agent_artworks_count extends views_handler_field_prerender_list {
 function construct() {
    parent::construct();
    $this->additional_fields['agent_id'] = array('table' => 'agent', 'field' => 'agent_id');
  }

  function query() {
    $this->add_additional_fields();
    //$this->field_alias = $this->aliases['agent_id'];
    $this->field_alias = "num_artworks";
  }

  function pre_render($values) {
    
    //print_r($this->field_alias);
    
    $agent_ids = array();
    $ids = array();
    
    //taken from views_handler_field_node_new_comments.inc
    
    //put all agent_ids into $agent_ids
    foreach ($values as $id => $result) {
      $agent_ids[] = $result->{$this->aliases['agent_id']};
      //save the row in $values where this agent_id occures
      $ids[$result->{$this->aliases['agent_id']}] = $id;
      
      //$values[$id]->{$this->field_alias} = 0;
       // Create a reference so we can find this record in the values again.
      /*if (empty($ids[$result->{$this->aliases['agent_id']}])) {
        $ids[$result->{$this->aliases['agent_id']}] = array();
      }
      $ids[$result->{$this->aliases['agent_id']}][] = $id;*/
    }  
    //$i = 0;
    if ($agent_ids) {
      db_set_active('compart');
      $result = db_query("SELECT creating.agent_id as agent_id, COUNT(artwork.artwork_id) as num_artworks FROM {artwork} INNER JOIN {creating} ON creating.artwork_id = artwork.artwork_id WHERE creating.agent_id IN (" . implode(', ', $agent_ids) . ") GROUP BY creating.agent_id");
      while ($agent = db_fetch_object($result)) {
        //foreach ($ids[$agent->agent_id] as $id) {
          //$values[$agent->agent_id]->{$this->field_alias} = $agent->num_artworks;
        //}
         //foreach ($agent_ids[$agent->agent_id] as $id) {
           //save the num artworks in the row, where the current agent_id is.
           $values[$ids[$agent->agent_id]]->num_artworks = $agent->num_artworks;
          // $i++; 
         // }
        
        //$this->items[$agent->agent_id][$agent->artwork_id] .= $agent->$cnt;
        //$values->{$agent->agent_id} = $agent->$cnt;    
        //$values->{$this->aliases['agent_id']} = $agent->$cnt;       
       
      }
      db_set_active('default');
    }
    //return $value;
  }
}

