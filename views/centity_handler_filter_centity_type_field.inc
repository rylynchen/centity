<?php

/**
 * Filter by consult apply type.
 *
 * @ingroup views_filter_handlers
 */
class centity_handler_filter_centity_type_field extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Centity types');
      $types = centity_get_types();
      $options = array();
      foreach ($types as $type => $info) {
        $options[$type] = t($info->label);
      }
      asort($options);
      $this->value_options = $options;
    }
  }
}
