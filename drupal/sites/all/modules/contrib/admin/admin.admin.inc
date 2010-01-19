<?php
// $Id: admin.admin.inc 881 2009-09-04 00:11:44Z jhedstrom $

/**
 * Implementation of hook_form_alter() for menu_edit_item.
 */
function admin_form_menu_edit_item_alter(&$form, &$form_state) {
  // If we are editing an item that is part of the admin menu, make
  // adjustments so we provide ways of editing the items' options array.
  if (!empty($form['menu']['original_item']['#value']['menu_name']) && $form['menu']['original_item']['#value']['menu_name'] == 'admin') {
    if (!empty($form['menu']['options']['#value']) && is_array($form['menu']['options']['#value'])) {
      foreach ($form['menu']['options']['#value'] as $k => $v) {
        $form['menu']['options'][$k] = array(
          '#type' => 'value',
          '#value' => $v,
        );
      }
    }
    unset($form['menu']['options']['#type']);
    unset($form['menu']['options']['#value']);
    $form['menu']['options']['#tree'] = TRUE;
    $form['menu']['options']['#weight'] = 1;

    $form['menu']['options']['admin']['#type'] = 'checkbox';
    $form['menu']['options']['admin']['#title'] = t('Display in admin menu');
    $form['menu']['options']['admin']['#description'] = t('If selected, this item will be displayed in the admin menu at the top of each page.');
    $form['menu']['options']['admin']['#default_value'] = $form['menu']['options']['admin']['#value'];
    unset($form['menu']['options']['admin']['#value']);
  }
}

/**
 * Implementation of hook_form_alter() for menu_overview_form.
 */
function admin_form_menu_overview_form_alter(&$form, &$form_state) {
  if ($form['#menu']['menu_name'] == 'admin') {
    foreach (element_children($form) as $key) {
      if (!empty($form[$key]['#item'])) {
        $form[$key]['admin'] = array(
          '#type' => 'checkbox',
          '#default_value' => !empty($form[$key]['#item']['options']['admin']),
        );
      }
    }
    $form['#theme'] = 'admin_menu_overview_form';
    $form['#submit'] = array('admin_menu_overview_form_submit');
  }
}

/**
 * Theme the menu overview form into a table.
 */
function theme_admin_menu_overview_form($form) {
  drupal_add_tabledrag('menu-overview', 'match', 'parent', 'menu-plid', 'menu-plid', 'menu-mlid', TRUE, MENU_MAX_DEPTH - 1);
  drupal_add_tabledrag('menu-overview', 'order', 'sibling', 'menu-weight');

  $header = array(
    t('Menu item'),
    array('data' => t('Admin'), 'class' => 'checkbox'),
    array('data' => t('Enabled'), 'class' => 'checkbox'),
    array('data' => t('Expanded'), 'class' => 'checkbox'),
    t('Weight'),
    array('data' => t('Operations'), 'colspan' => '3'),
  );

  $rows = array();
  foreach (element_children($form) as $mlid) {
    if (isset($form[$mlid]['hidden'])) {
      $element = &$form[$mlid];
      // Build a list of operations.
      $operations = array();
      foreach (element_children($element['operations']) as $op) {
        $operations[] = drupal_render($element['operations'][$op]);
      }
      while (count($operations) < 2) {
        $operations[] = '';
      }

      // Add special classes to be used for tabledrag.js.
      $element['plid']['#attributes']['class'] = 'menu-plid';
      $element['mlid']['#attributes']['class'] = 'menu-mlid';
      $element['weight']['#attributes']['class'] = 'menu-weight';

      // Change the parent field to a hidden. This allows any value but hides the field.
      $element['plid']['#type'] = 'hidden';

      $row = array();
      $row[] = theme('indentation', $element['#item']['depth'] - 1) . drupal_render($element['title']);
      $row[] = array('data' => drupal_render($element['admin']), 'class' => 'checkbox');
      $row[] = array('data' => drupal_render($element['hidden']), 'class' => 'checkbox');
      $row[] = array('data' => drupal_render($element['expanded']), 'class' => 'checkbox');
      $row[] = drupal_render($element['weight']) . drupal_render($element['plid']) . drupal_render($element['mlid']);
      $row = array_merge($row, $operations);

      $row = array_merge(array('data' => $row), $element['#attributes']);
      $row['class'] = !empty($row['class']) ? $row['class'] .' draggable' : 'draggable';
      $rows[] = $row;
    }
  }
  $output = '';
  if ($rows) {
    $output .= theme('table', $header, $rows, array('id' => 'menu-overview'));
  }
  $output .= drupal_render($form);
  return $output;
}

/**
 * Submit handler for the admin menu overview form.
 */
function admin_menu_overview_form_submit($form, &$form_state) {
  // When dealing with saving menu items, the order in which these items are
  // saved is critical. If a changed child item is saved before its parent,
  // the child item could be saved with an invalid path past its immediate
  // parent. To prevent this, save items in the form in the same order they
  // are sent by $_POST, ensuring parents are saved first, then their children.
  // See http://drupal.org/node/181126#comment-632270
  $order = array_flip(array_keys($form['#post'])); // Get the $_POST order.
  $form = array_merge($order, $form); // Update our original form with the new order.

  $updated_items = array();
  $fields = array('expanded', 'weight', 'plid');
  foreach (element_children($form) as $mlid) {
    if (isset($form[$mlid]['#item'])) {
      $element = $form[$mlid];
      // Update any fields that have changed in this menu item.
      foreach ($fields as $field) {
        if ($element[$field]['#value'] != $element[$field]['#default_value']) {
          $element['#item'][$field] = $element[$field]['#value'];
          $updated_items[$mlid] = $element['#item'];
        }
      }
      // Hidden is a special case, the value needs to be reversed.
      if ($element['hidden']['#value'] != $element['hidden']['#default_value']) {
        $element['#item']['hidden'] = !$element['hidden']['#value'];
        $updated_items[$mlid] = $element['#item'];
      }
      // Admin is also a special case -- we need to set its flag in the options array.
      if ($element['admin']['#value'] != $element['admin']['#default_value']) {
        $element['#item']['options']['admin'] = $element['admin']['#value'];
        $updated_items[$mlid] = $element['#item'];
      }
    }
  }

  // Save all our changed items to the database.
  foreach ($updated_items as $item) {
    $item['customized'] = 1;
    menu_link_save($item);
  }
}

/**
 * Implementation of hook_form_alter() for system_admin_theme_settings.
 */
function admin_form_system_admin_theme_settings_alter(&$form) {
  // Add in our admin theme ('slate') as an option
  $form['admin_theme']['#options']['slate'] = t('Slate (formerly \'Admin\')');
}

/**
 * Implementation of hook_form_alter() for node_filter_form.
 */
function admin_form_node_admin_content_alter(&$form) {
  // If the admin theme has been inited, do some additional work.
  global $theme;
  if ($theme == 'admin') {
    unset($form['admin']['options']['#type']);
    unset($form['admin']['options']['#prefix']);
    unset($form['admin']['options']['#suffix']);
    $form['admin']['options']['#theme'] = 'admin_manage_options';
  }
}

/**
 * Implementation of hook_form_alter() for admin_account_form.
 */
function admin_form_user_admin_account_alter(&$form) {
  // If the admin theme has been inited, do some additional work.
  global $theme;
  if ($theme == 'admin') {
    unset($form['options']['#type']);
    unset($form['options']['#prefix']);
    unset($form['options']['#suffix']);
    $form['options']['#theme'] = 'admin_manage_options';
  }
}
