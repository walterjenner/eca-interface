<?php
// $Id: views_handler_field_term_node_tid.inc,v 1.3 2009/04/07 22:02:40 merlinofchaos Exp $

/**
 * Field handler for terms.
 */
class artwork_handler_field_creator_list extends views_handler_field_prerender_list {
  function construct() {
    parent::construct();
    $this->additional_fields['artwork_id'] = array('table' => 'artwork', 'field' => 'artwork_id');
  }

  function query() {
    $this->add_additional_fields();
    $this->field_alias = $this->aliases['artwork_id'];
  }

  function pre_render($values) {
    $artwork_ids = array();
    $this->items = array();
//print_r($values);
    foreach ($values as $result) {
      $artwork_ids[] = $result->{$this->aliases['artwork_id']};
    }
    if ($artwork_ids) {
      $result = db_query("SELECT ca_c.artwork_id, ca_a.first_name, ca_a.last_name, a.nid 
                        FROM {compartDB.agent} ca_a
                        INNER JOIN {compartDB.creating}  ca_c
                          ON ca_c.agent_id = ca_a.agent_id 
                        LEFT JOIN {agent} a 
                          ON ca_c.agent_id = a.agent_id 
                        WHERE ca_c.artwork_id IN (" . implode(', ', $artwork_ids) . ")");
      while ($agent = db_fetch_object($result)) {
        $this->items[$agent->artwork_id][$agent->nid] .= l($agent->first_name . ' ' . $agent->last_name, 'node/'.$agent->nid);          
      }
      //print_r($this->items);
    }
  }
}

