<?php
// $Id: 
/**
 * Author: Valderama
 * Render a field as a year. Tries to extract a 4 digit number, if there is non, empty is returned
 * NOTE: ignores all options from the numeric field, except hide empty and pre/suffix
 *
 * @ingroup views_field_handlers
 */
class eca_main_handler_field_year extends views_handler_field_numeric {
 
  function render($values) {
    $value = $values->{$this->field_alias};
    
    //take 4 digit number or nothing
    preg_match_all ("/(?<!\d)(\d{4})(?!\d)/", $value, $matches);
    $value = (count($matches))?$matches[0][0]:'';    

    // Check to see if hiding should happen before adding prefix and suffix.
    if ($this->options['hide_empty'] && empty($value) && ($value !== 0 || $this->options['empty_zero'])) {
      return '';
    }

    return check_plain($this->options['prefix'] . $value . $this->options['suffix']);
  }
}
