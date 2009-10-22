<?php
// $Id: views_handler_field_term_node_tid.inc,v 1.3 2009/04/07 22:02:40 merlinofchaos Exp $

/**
 * Field handler for terms.
 */
class agent_handler_field_agent_artworks extends views_handler_field_prerender_list {
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

    if ($agent_ids) {
      db_set_active('compart');
      $result = db_query("SELECT creating.agent_id, artwork.title FROM {artwork} INNER JOIN {creating} ON creating.artwork_id = artwork.artwork_id WHERE creating.agent_id IN (" . implode(', ', $agent_ids) . ")");
      while ($artwork = db_fetch_object($result)) {
        if(!empty($this->items[$artwork->agent_id][$artwork->artwork_id]))
          $this->items[$artwork->agent_id][$artwork->artwork_id] .= ', '; 
                  
        $this->items[$artwork->agent_id][$artwork->artwork_id] .= $artwork->title;          
      }
      db_set_active('default');
    }
  }
}

