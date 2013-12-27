<?php

class centity_handler_centity_type_field extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['type_label'] = array(
      'table' => 'centity_type', 
      'field' => 'label'
    );
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['text'] = array('default' => '', 'translatable' => TRUE);
    return $options;
  }

  function query() {
    $this->ensure_my_table();
    $join = new views_join();
    $def = array(
      'table' => 'centity_type',
      'field' => 'type',
      'left_table' => $this->table_alias,
      'left_field' => 'type',
    );
    $join->definition = $def;
    $join->construct();
    $join->adjusted = TRUE;
    $this->table_alias = $this->query->add_table('centity_type', $this->relationship, $join);
    $this->add_additional_fields(); 
  }

  function render($values) {
    return $values->{$this->aliases['type_label']};
  }
}
