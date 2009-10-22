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

    foreach ($values as $result) {
      $artwork_ids[] = $result->{$this->aliases['artwork_id']};
    }

    if ($artwork_ids) {
      //db_set_active('compart');
      $result = db_query("SELECT compartdb_creating.artwork_id, compartdb_agent.first_name, compartdb_agent.last_name, agent.nid FROM {compartdb_agent} INNER JOIN {compartdb_creating} ON compartdb_creating.agent_id = compartdb_agent.agent_id LEFT JOIN {agent} ON compartdb_creating.agent_id = agent.agent_id WHERE compartdb_creating.artwork_id IN (" . implode(', ', $artwork_ids) . ")");
      while ($agent = db_fetch_object($result)) {
        if(!empty( $this->items[$agent->artwork_id][$agent->agent_id] ))
          $this->items[$agent->artwork_id][$agent->agent_id] .= ', ';
          
        $this->items[$agent->artwork_id][$agent->agent_id] .= l($agent->first_name . ' ' . $agent->last_name, 'node/'.$agent->nid);          
      }
      //db_set_active('default');
    }
  }
}

