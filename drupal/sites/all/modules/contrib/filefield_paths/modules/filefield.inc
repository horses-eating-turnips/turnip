<?php
// $Id: filefield.inc 843 2009-07-08 01:03:08Z jhedstrom $

/**
 * @file
 * Provides FileField Paths integration with the FileField module.
 */

/**
 * Implementation of hook_filefield_paths_form_alter().
 */
function filefield_filefield_paths_form_alter(&$form, &$ffp) {
  if (isset($form['basic']) && $form['basic']['type']['#value'] == 'filefield' && isset($form['widget']['path_settings'])) {
    $form['widget']['ffp_'. $form['field_name']['#value']] = $form['widget']['path_settings'];
    $form['widget']['path_settings']['#access'] = FALSE;

    $ffp[$form['field_name']['#value']] = array(
      'show' => TRUE,
      'type' => $form['type_name']['#value'],
      'form_path' => &$form['widget']['ffp_'. $form['field_name']['#value']],
      'file_path_default' => $form['widget']['path_settings']['file_path']['#default_value']
    );

    $form['widget']['ffp_'. $form['field_name']['#value']]['#title'] = t('FileField Path settings');

    unset($ffp[$form['field_name']['#value']]['form_path']['file_path']['#suffix']);
    $ffp[$form['field_name']['#value']]['form_path']['#attributes'] = array('id' => 'fieldset-path_settings');
  }
}

/**
 * Implementation of hook_filefield_paths_form_submit().
 */
function filefield_filefield_paths_form_submit(&$form_state, &$ffp) {
  if ($form_state['values']['form_id'] != 'node_type_form') {
    $ffp[$form_state['values']['field_name']] = array(
      'type' => $form_state['values']['type_name'],
    );

    $form_state['values']['file_path'] = $form_state['values']['ffp_'. $form_state['values']['field_name']]['file_path'];
  }
}

/**
 * Implementation of hook_filefield_paths_get_fields().
 */
function filefield_filefield_paths_get_fields(&$node, &$ffp) {
  if (is_object($node) && $node->form_id == $node->type .'_node_form') {
    $content_type = content_types($node->type);

    foreach ($content_type['fields'] as $field) {
      if ($field['type'] == 'filefield' && isset($node->$field['field_name']) && is_array($node->$field['field_name'])) {

        foreach ($node->$field['field_name'] as &$file) {
          $ffp['#files'][] = array(
            'field' => &$file,
            'module' => $field['module'],
            'name' => $field['field_name'],
            'widget' => $field['widget']['module'],
            'new' => (!empty($file['filepath']) && !empty($file['data']['process'])) ? TRUE : FALSE
          );
          unset($file['data']['process']);

          $ffp['#types'][$field['field_name']] = TRUE;
        }

      }
    }
  }
}

/**
 * Implementation of hook_filefield_paths_batch_update().
 */
function filefield_filefield_paths_batch_update($field_name, $type_name, &$objects) {
  if (!empty($field_name)) {
    $field = content_fields($field_name, $type_name);
    $db_info = content_database_info($field);

    $result = db_query(
      "SELECT c.nid FROM {%s} c LEFT JOIN {node} n ON c.nid = n.nid WHERE c.%s IS NOT NULL
      AND n.type = '%s'", $db_info['table'], $db_info['columns']['fid']['column'], $type_name
    );

    // Build array of Node IDs.
    while ($node = db_fetch_object($result)) {
      $objects[] = $node->nid;
    }
  }
}

/**
 * Implementation of hook_filefield_paths_update().
 */
function filefield_filefield_paths_update($oid, $field_name) {
  if (!empty($field_name)) {
    $node = node_load($oid);
    $content_type = content_types($node->type);

    // Flag files for update.
    if (isset($node->$field_name)) {
      foreach ($node->$field_name as &$file) {
        if (empty($file['filepath'])) {
          continue;
        }

        $file['data']['process'] = TRUE;
      }
    }

    // Set Form ID.
    $node->form_id = $node->type .'_node_form';

    // Process Node.
    filefield_paths_nodeapi($node, 'update', NULL, NULL);
  }
}
