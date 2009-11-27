<?php
// $Id$
/**
 * Allow agent ID(s) as argument
 */
class eca_main_handler_argument_agent_id extends views_handler_argument_many_to_one {
  function title_query() {
    $titles = array();
    $placeholders = implode(', ', array_fill(0, sizeof($this->value), '%d'));

    db_set_active('compart');
    $result = db_query("SELECT first_name, last_name FROM {agent} WHERE agent_id IN ($placeholders)", $this->value);
    while ($term = db_fetch_object($result)) {
      $titles[] = check_plain($term->first_name . ' ' . $term->last_name);
    }
    db_set_active('default');
    return $titles;
  }
}