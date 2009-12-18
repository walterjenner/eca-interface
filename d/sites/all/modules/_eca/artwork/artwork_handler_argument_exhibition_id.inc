<?php
// $Id$
/**
 * Allow exhibitions ID(s) as argument, to show all allworks at a given exhibition
 */
class artwork_handler_argument_exhibition_id extends views_handler_argument_many_to_one {
  function title_query() {
    $titles = array();
    $placeholders = implode(', ', array_fill(0, sizeof($this->value), '%d'));

    db_set_active('compart');
    $result = db_query("SELECT name FROM {exhibition} WHERE exhibition_id IN ($placeholders)", $this->value);
    while ($term = db_fetch_object($result)) {
      $titles[] = check_plain($term->name);
    }
    db_set_active('default');
    return $titles;
  }
}