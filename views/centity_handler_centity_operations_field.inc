<?php

class centity_handler_centity_operations_field extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['cid'] = 'cid';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $cid = $this->get_value($values, 'cid');
    $links = array();
    $links[] = array(
      'title' => l(t('View'), 'admin/content/centity/'.$cid),
      'html' => TRUE,
    );
    $links[] = array(
      'title' => l(t('Edit'), 'admin/content/centity/'.$cid.'/edit'),
      'html' => TRUE,
    );
    $links[] = array(
      'title' => l(t('Delete'), 'admin/content/centity/'.$cid.'/delete'),
      'html' => TRUE,
    );
    if (!empty($links)) {
      return theme('links', array('links' => $links, 'attributes' => array('class' => array('links', 'inline', 'operations'))));
    }
  }
}
