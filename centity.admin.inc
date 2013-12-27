<?php

/**
 * UI controller.
 */
class CentityUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults. Main reason for doing this is that
   * parent class hook_menu() is optimized for entity type administration.
   */
  public function hook_menu() {
    
    $items = array();
    $id_count = count(explode('/', $this->path));
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%' . $this->entityType;

    $items[$this->path] = array(
      'title' => 'Centities',
      'description' => 'Add edit and update centity.',
      'page callback' => 'system_admin_menu_block_page',
      'access arguments' => array('access administration pages'),
      'file path' => drupal_get_path('module', 'system'),
      'file' => 'system.admin.inc',
    );
    
    // Change the overview menu type for the list of centities.
    $items[$this->path]['type'] = MENU_LOCAL_TASK;
    
    // Change the add page menu to multiple types of entities
    $items[$this->path . '/add'] = array(
      'title' => 'Add a centity',
      'description' => 'Add a new centity',
      'page callback'  => 'centity_add_page',
      'access callback'  => 'centity_access',
      'access arguments' => array('edit'),
      'type' => MENU_NORMAL_ITEM,
      'weight' => 20,
      'file' => 'centity.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module']),
    );
    
    // Add menu items to add each different type of entity.
    foreach (centity_get_types() as $type) {
      $items[$this->path.'/add/' . $type->type] = $items['centity/add/' . $type->type] = array(
        'title' => 'Add ' . $type->label,
        'page callback' => 'centity_form_wrapper',
        'page arguments' => array(centity_create(array('type' => $type->type))),
        'access callback' => 'centity_access',
        'access arguments' => array('edit', (object) array('type' => $type->type)),
        'file' => 'centity.admin.inc',
        'file path' => drupal_get_path('module', $this->entityInfo['module'])
      );
    }
    // view page
    $items[$this->path . '/' . $wildcard] = array(
      'title callback' => 'centity_page_title',
      'title arguments' => array($id_count),
      'page callback' => 'centity_page_view',
      'page arguments' => array($id_count),
      'access callback' => 'centity_access',
      'access arguments' => array('view', $id_count),
      'type' => MENU_CALLBACK,
    );
    $items['centity/' . $wildcard] = array(
      'title callback' => 'centity_page_title',
      'title arguments' => array(1),
      'page callback' => 'centity_page_view',
      'page arguments' => array(1),
      'access callback' => 'centity_access',
      'access arguments' => array('view', 1),
      'type' => MENU_CALLBACK,
    );
    // edit page
    $items[$this->path . '/' . $wildcard . '/edit'] = array(
      'title callback' => 'centity_page_title',
      'title arguments' => array($id_count),
      'page callback' => 'centity_form_wrapper',
      'page arguments' => array($id_count),
      'access callback' => 'centity_access',
      'access arguments' => array('edit', $id_count),
      'weight' => 0,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'file' => 'centity.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    ); 
    $items['centity/' . $wildcard . '/edit'] = array(
      'title callback' => 'centity_page_title',
      'title arguments' => array(1),
      'page callback' => 'centity_form_wrapper',
      'page arguments' => array(1),
      'access callback' => 'centity_access',
      'access arguments' => array('edit', 1),
      'weight' => 0,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'file' => 'centity.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );
    // delete page
    $items[$this->path . '/' . $wildcard . '/delete'] = array(
      'title' => 'Delete',
      'page callback' => 'centity_delete_form_wrapper',
      'page arguments' => array($id_count),
      'access callback' => 'centity_access',
      'access arguments' => array('edit', $id_count),
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_INLINE,
      'weight' => 10,
      'file' => 'centity.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    ); 
    $items['centity/' . $wildcard . '/delete'] = array(
      'title' => 'Delete',
      'page callback' => 'centity_delete_form_wrapper',
      'page arguments' => array(1),
      'access callback' => 'centity_access',
      'access arguments' => array('edit', 1),
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_INLINE,
      'weight' => 10,
      'file' => 'centity.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );
    return $items;
  }
  
  /**
   * Create the markup for the add Model Entities page within the class
   * so it can easily be extended/overriden.
   */ 
  public function addPage() {
    $item = menu_get_item();
    $content = system_admin_menu_block($item);

    if (count($content) == 1) {
      $item = array_shift($content);
      drupal_goto($item['href']);
    }    
        
    return theme('centity_add_list', array('content' => $content));
  }
  
}

/**
 * Form callback wrapper: create or edit a centity.
 *
 * @param $centity
 *   The centity object being edited by this form.
 *
 * @see centity_edit_form()
 */
function centity_form_wrapper($centity) {
  // Add the breadcrumb for the form's location.
  centity_set_breadcrumb();
  return drupal_get_form('centity_edit_form', $centity);
}

/**
 * Form callback wrapper: delete a centity.
 *
 * @param $centity
 *   The centity object being edited by this form.
 *
 * @see centity_edit_form()
 */
function centity_delete_form_wrapper($centity) {
  // Add the breadcrumb for the form's location.
  centity_set_breadcrumb();
  return drupal_get_form('centity_delete_form', $centity);
}

/**
 * Form callback: create or edit a centity.
 *
 * @param $centity
 *   The centity object to edit or for a create form an empty centity object
 *     with only a centity type defined.
 */
function centity_edit_form($form, &$form_state, $centity) {
  // Add the field related form elements.
  $form_state['centity'] = $centity;
  field_attach_form('centity', $centity, $form, $form_state);

  $form['actions'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('form-actions')),
    '#weight' => 400,
  );

  // We add the form's #submit array to this button along with the actual submit
  // handler to preserve any submit handlers added by a form callback_wrapper.
  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => $submit + array('centity_edit_form_submit'),
  );
  
  if (!empty($centity->cid)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#suffix' => l(t('Cancel'), 'admin/content/centity'),
      '#submit' => $submit + array('centity_form_submit_delete'),
    );
  }

  // We append the validate handler to #validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'][] = 'centity_edit_form_validate';
  return $form;
}

/**
 * Form API submit callback for the delete button.
 * 
 * @todo Remove hard-coded path
 */
function centity_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/content/centity/centity/' . $form_state['centity']->cid . '/delete';
}

/**
 * Form callback: confirmation form for deleting a centity.
 *
 * @param $centity
 *   The centity to delete
 *
 * @see confirm_form()
 */
function centity_delete_form($form, &$form_state, $centity) {
  $form_state['centity'] = $centity;

  $form['#submit'][] = 'centity_delete_form_submit';

  $form = confirm_form($form,
    t('Are you sure you want to delete centity %id?', array('%id' => $centity->cid)),
    'admin/content/centity/centity',
    '<p>' . t('This action cannot be undone.') . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );
  
  return $form;
}

/**
 * Submit callback for centity_delete_form
 */
function centity_delete_form_submit($form, &$form_state) {
  $centity = $form_state['centity'];

  centity_delete($centity);

  drupal_set_message(t('The centity %id has been deleted.', array('%id' => $centity->cid)));
  watchdog('centity', 'Deleted centity %id.', array('%id' => $centity->cid));

  $form_state['redirect'] = 'admin/content/centity';
}

/**
 * Page to add Model Entities.
 *
 * @todo Pass this through a proper theme function
 */
function centity_add_page() {
  $controller = entity_ui_controller('centity');
  return $controller->addPage();
}

/**
 * Displays the list of available centity types for centity creation.
 *
 * @ingroup themeable
 */
function theme_centity_add_list($variables) {
  $content = $variables['content'];
  $output = '';
  if ($content) {
    $output = '<dl class="centity-type-list">';
    foreach ($content as $item) {
      $output .= '<dt>' . l($item['title'], $item['href']) . '</dt>';
      $output .= '<dd>' . filter_xss_admin($item['description']) . '</dd>';
    }
    $output .= '</dl>';
  }
  else {
    if (user_access('administer centity types')) {
      $output = '<p>' . t('Model Entities cannot be added because you have not created any centity types yet. Go to the <a href="@create-centity-type">centity type creation page</a> to add a new centity type.', array('@create-centity-type' => url('admin/structure/centity-types/add'))) . '</p>';
    }
    else {
      $output = '<p>' . t('No centity types have been created yet for you to use.') . '</p>';
    }
  }

  return $output;
}

/**
 * Sets the breadcrumb for administrative centity pages.
 */
function centity_set_breadcrumb() {
  $breadcrumb = array(
    l(t('Home'), '<front>'),
    l(t('Administration'), 'admin'),
    l(t('Content'), 'admin/content'),
    l(t('Centity'), 'admin/content/centity'),
  );
  drupal_set_breadcrumb($breadcrumb);
}