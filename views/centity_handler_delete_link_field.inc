<?php

class centity_handler_delete_link_field extends centity_handler_link_field {
  function construct() {
    parent::construct();
    $this->additional_fields['type'] = 'type';
  }

  function render($values) {
    $type = $values->{$this->aliases['type']};
    
    //Creating a dummy model to check access against
    $dummy_centity = (object) array('type' => $type);
    if (!signup_access('edit', $dummy_centity)) {
      return;
    }
    
    $text = !empty($this->options['text']) ? $this->options['text'] : t('delete');
    $cid = $values->{$this->aliases['cid']};
    
    return l($text, 'admin/content/centity/' . $cid . '/delete');
  }
}
