<?php
// $Id: views_handler_field_term_node_tid.inc,v 1.3 2009/04/07 22:02:40 merlinofchaos Exp $

/**
 * NOTE: 
 * 
 * this field uses another technique to display a list of items, 
 * which does not need an extra request to the database.
 * however there are some problems: 
 *   1) i cannot link to the agent, as i do not have a nid
 *   2) the agents are display in the plain list, but not within the exhibit view (as this is rendered differently).
 *   
 * finally the extra db-request should not matter, because the view is cached anyway.
 * also this way is the standard way, how taxonomy terms are added as a field. * 
 */

/**
 * Field handler for adding all agent that where at a exhibition to the exhibition list.
 */
class artwork_handler_field_agent_list extends views_handler_field_prerender_list {
  
  function construct() {
    parent::construct();
    $this->additional_fields['first_name'] = array('table' => 'compartdb_agent', 'field' => 'first_name');
  }
  
  function pre_render($values) {    
    $last_i = 0;
    $last_nid = -1;
    
    //as i unset elements of the array, the count would change.
    $countValues = count($values);
    
    for($i = 0; $i < $countValues; $i++){
      $values[$i]->{$this->field_alias} = $values[$i]->compartdb_agent_first_name . " " .$values[$i]->{$this->field_alias}; //add first name 
      if($values[$i]->nid == $last_nid){             
        array_push( $values[$last_i]->{$this->field_alias}, $values[$i]->{$this->field_alias} );    
        unset($values[$i]->{$this->field_alias});        
        unset($values[$i]);
      } else {
        $temp = $values[$i]->{$this->field_alias};
        $values[$i]->{$this->field_alias} = array(0 =>$temp);
        
        $last_i = $i;
        $last_nid = $values[$i]->nid;
      }   
    }
  } 
   
  function render($values){
     if(is_array($values->{$this->field_alias}) && !empty($values->{$this->field_alias}[0]) ){
       if ($this->options['type'] == 'separator') {
         return implode(check_plain($this->options['separator']), $values->{$this->field_alias});
       }
       else {
         return theme('item_list', $values->{$this->field_alias}, NULL, $this->options['type']);
       }
     }       
     else if (!empty($this->options['empty'])) {
       return $this->options['empty'];
     }
  }
  
  function advanced_render($values){
    // dpm("in artwork handler advanced render");
     return $this->render($values);
  }
  
}

