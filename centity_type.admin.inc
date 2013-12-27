<?php

/**
 * UI controller.
 */
class CentityTypeUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
		$items[$this->path]['description'] = 'Manage centity entity types, including adding
		and removing fields and the display of fields.';
    return $items;
  }
}

/**
 * Generates the centity type editing form.
 */
function centity_type_form($form, &$form_state, $centity, $op = 'edit') {

  if ($op == 'clone') {
    $centity->label .= ' (cloned)';
    $centity->type = '';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $centity->label,
    '#description' => t('The human-readable name of this centity type.'),
    '#required' => TRUE,
    '#size' => 30,
  );
  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($centity->type) ? $centity->type : '',
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'centity_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this centity type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function centity_type_form_submit(&$form, &$form_state) {
  $centity = entity_ui_form_submit_build_entity($form, $form_state);
  $centity->save();
  $form_state['redirect'] = 'admin/structure/centity-types';
}

/**
 * Form API submit callback for the delete button.
 */
function centity_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/centity-types/manage/' . $form_state['centity']->type . '/delete';
}