<?php
// $Id: views_handler_field_term_node_tid.inc,v 1.3 2009/04/07 22:02:40 merlinofchaos Exp $

/**
 * Field handler for terms.
 */
class artwork_handler_field_artwork_agents extends views_handler_field_prerender_list {
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
      $result = db_query("SELECT compartDB.creating.artwork_id, compartDB.agent.first_name, compartDB.agent.last_name, agent.nid FROM {compartDB.agent} INNER JOIN {compartDB.creating} ON compartDB.creating.agent_id = compartDB.agent.agent_id LEFT JOIN {agent} ON compartDB.creating.agent_id = agent.agent_id WHERE compartDB.creating.artwork_id IN (" . implode(', ', $artwork_ids) . ")");
      while ($agent = db_fetch_object($result)) {
        $this->items[$agent->artwork_id][$agent->nid] .= l($agent->first_name . ' ' . $agent->last_name, 'node/'.$agent->nid);          
      }
      //print_r($this->items);
    }
  }
}

