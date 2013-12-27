<?php

/**
 * Implements hook_views_data()
 */
function centity_views_data_alter(&$data) {
  $data['centity']['link_centity'] = array(
    'field' => array(
      'title' => t('Link'),
      'help' => t('Provide a link to the centity.'),
      'handler' => 'centity_handler_link_field',
    ),
  );
  $data['centity']['edit_centity'] = array(
    'field' => array(
      'title' => t('Edit Link'),
      'help' => t('Provide a link to the edit form for the centity.'),
      'handler' => 'centity_handler_edit_link_field',
    ),
  );
  $data['centity']['delete_centity'] = array(
    'field' => array(
      'title' => t('Delete Link'),
      'help' => t('Provide a link to delete the centity.'),
      'handler' => 'centity_handler_delete_link_field',
    ),
  );
  $data['centity']['operations'] = array(
    'field' => array(
      'title' => t('Operations links'),
      'help' => t('Display all operations available for this centity.'),
      'handler' => 'centity_handler_centity_operations_field',
    ),
  );
  // type
  $data['centity']['type']['field']['title'] = t('Type');
  $data['centity']['type']['field']['handler'] = 'centity_handler_centity_type_field';
  $data['centity']['type']['filter']['handler'] = 'centity_handler_filter_centity_type_field';
}

/**
 * Implements hook_views_default_views().
 */
function centity_views_default_views() {
  $view = new view();
  $view->name = 'centities';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'centity';
  $view->human_name = 'Centities';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Centitiy';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer centities';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: Centity: Centity ID */
  $handler->display->display_options['fields']['cid']['id'] = 'cid';
  $handler->display->display_options['fields']['cid']['table'] = 'centity';
  $handler->display->display_options['fields']['cid']['field'] = 'cid';
  /* Field: Centity: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'centity';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  /* Field: Centity: Operations links */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'centity';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  $handler->display->display_options['fields']['operations']['label'] = 'Operations';
  /* Sort criterion: Centity: Centity ID */
  $handler->display->display_options['sorts']['cid']['id'] = 'cid';
  $handler->display->display_options['sorts']['cid']['table'] = 'centity';
  $handler->display->display_options['sorts']['cid']['field'] = 'cid';
  $handler->display->display_options['sorts']['cid']['order'] = 'DESC';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/content/centity';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Centity';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['centities'] = array(
    t('Master'),
    t('Centitiy'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Centity ID'),
    t('Type'),
    t('Operations'),
    t('Page'),
  );

  $views[$view->name] = $view;
  return $views;
}