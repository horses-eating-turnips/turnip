<?php
// $Id: audio.inc,v 1.1.2.4 2010/01/11 06:07:16 deciphered Exp $
/**
 * @file
 * Provides FileField Paths integration with the Audio module.
 */

/**
 * Implements hook_filefield_paths_form_alter().
 */
function audio_filefield_paths_form_alter(&$form, &$ffp) {
  if (isset($form['#id']) && $form['#id'] == 'node-type-form' && isset($form['#node_type']) && $form['#node_type']->module == 'audio') {
    $ffp['audio'] = array(
      'type' => $form['#node_type']->type,
      'form_path' => &$form['ffp_audio'],
      'file_path_default' => ''
    );

    // Create path settings fieldset
    $ffp['audio']['form_path'] = array(
      '#type' => 'fieldset',
      '#title' => t('Audio Path settings'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $ffp['audio']['form_path']['file_path'] = array(
      '#type' => 'textfield',
      '#title' => t('File path'),
      '#description' => t('Optional subdirectory within the "%dir" directory where files will be stored. Do not include trailing slash.', array('%dir' => variable_get('file_directory_path', 'files'))),
      '#tree' => TRUE,
    );

    $form['workflow']['#weight'] = $form['comment']['#weight'] = 1;
  }
}

/**
 * Implements hook_filefield_paths_form_submit().
 */
function audio_filefield_paths_form_submit(&$form_state, &$ffp) {
  if ($form_state['values']['form_id'] == 'node_type_form') {
    $ffp['audio'] = array(
      'type' => $form_state['values']['type'],
    );
  }
}

/**
 * Implements hook_filefield_paths_get_fields().
 */
function audio_filefield_paths_get_fields(&$node, &$ffp) {
  if (is_object($node) && isset($node->audio['file'])) {
    $node->audio['file'] = (array) $node->audio['file'];

    $ffp['#files'][] = array(
      'field' => &$node->audio['file'],
      'module' => 'audio',
      'name' => 'audio',
      'new' => isset($node->audio['file']->source),
    );

    $ffp['#types']['audio'] = TRUE;
  }
}

/**
 * Implements hook_filefield_paths_batch_update().
 */
function audio_filefield_paths_batch_update($field, $type, &$objects) {
  $result = db_query(
    "SELECT a.nid FROM {audio} a LEFT JOIN {node} n ON a.nid = n.nid WHERE n.type = '%s'", $type
  );

  // Build array of Node IDs.
  while ($node = db_fetch_object($result)) {
    $objects[] = $node->nid;
  }
}

/**
 * Implements hook_filefield_paths_update().
 */
function audio_filefield_paths_update($oid, $field) {
  $node = node_load($oid);

  // Flag files for update.
  $node->audio['file']->source = 'filefield_paths';

  // Set Form ID.
  $node->form_id = $node->type . '_node_form';

  // Process Node.
  filefield_paths_nodeapi($node, 'update', NULL, NULL);
}
