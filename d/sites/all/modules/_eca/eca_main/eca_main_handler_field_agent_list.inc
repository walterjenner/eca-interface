<?php
// $Id: views_handler_field_term_node_tid.inc,v 1.3 2009/04/07 22:02:40 merlinofchaos Exp $

/**
 * Field handler for terms.
 */
class eca_main_handler_field_agent_list extends views_handler_field_prerender_list {
 function construct() {
    parent::construct();
    $this->additional_fields['publication_id'] = array('table' => 'publication', 'field' => 'publication_id');
  }

  function query() {
    $this->add_additional_fields();
    $this->field_alias = $this->aliases['publication_id'];
  }

  function pre_render($values) {
    $publication_ids = array();
    $this->items = array();

    foreach ($values as $result) {
      $publication_ids[] = $result->{$this->aliases['publication_id']};
    }

    if ($publication_ids) {
      //db_set_active('compart');
      //$result = db_query("SELECT authorship.publication_id, authorship.agent_id, authorship.as_editor, agent.last_name, agent.first_name FROM {agent} INNER JOIN {authorship} ON authorship.agent_id = agent.agent_id WHERE authorship.publication_id IN (" . implode(', ', $publication_ids) . ") ORDER BY agent.last_name");
      $result = db_query("SELECT compartdb_authorship.publication_id, compartdb_authorship.agent_id, compartdb_authorship.as_editor, compartdb_agent.last_name, compartdb_agent.first_name, agent.nid FROM {compartdb_agent} INNER JOIN {compartdb_authorship} ON compartdb_authorship.agent_id = compartdb_agent.agent_id INNER JOIN {agent} ON agent.agent_id = compartdb_agent.agent_id WHERE compartdb_authorship.publication_id IN (" . implode(', ', $publication_ids) . ") ORDER BY compartdb_agent.last_name");
      while ($agent = db_fetch_object($result)) {
        if($agent->as_editor)
          $this->items[$agent->publication_id][$agent->agent_id] = l($agent->first_name . ' ' . $agent->last_name . ' (Ed.)', 'node/'.$agent->nid);    
        else        
          $this->items[$agent->publication_id][$agent->agent_id] = l($agent->first_name . ' ' . $agent->last_name, 'node/'.$agent->nid);    
          
      }
      db_set_active('default');
    }
  }
}

