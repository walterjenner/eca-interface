<?php
// $Id: views_handler_field_term_node_tid.inc,v 1.3 2009/04/07 22:02:40 merlinofchaos Exp $

/**
 * Field handler for terms.
 */
class agent_handler_field_exhibition_list extends views_handler_field_prerender_list {
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
      $result = db_query("SELECT exhibits_in.agent_id as agent_id, exhibits_in.exhibition_id as exhibition_id, exhibition.name as name FROM {exhibition} INNER JOIN {exhibits_in} ON exhibits_in.exhibition_id = exhibition.exhibition_id WHERE exhibits_in.agent_id IN (" . implode(', ', $agent_ids) . ") ORDER BY exhibition.name");
      while ($exhibition = db_fetch_object($result)) {
        $this->items[$exhibition->agent_id][$exhibition->exhibition_id] = check_plain($exhibition->name);  
      }
      db_set_active('default');
    }
   
  }
}