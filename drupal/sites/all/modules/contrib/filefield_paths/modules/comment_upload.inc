<?php
// $Id: comment_upload.inc 843 2009-07-08 01:03:08Z jhedstrom $

/**
 * @file
 * Provides FileField Paths integration with the Comment Upload module.
 */

/**
 * Implementation of hook_filefield_paths_form_alter().
 */
function comment_upload_filefield_paths_form_alter(&$form, &$ffp) {
  if (isset($form['#id']) && $form['#id'] == 'node-type-form') {
    $ffp['comment_upload'] = array(
      'type' => $form['#node_type']->type,
      'form_path' => &$form['comment']['ffp_comment_upload'],
      'file_path_default' => ''
    );

    // Create path settings fieldset
    $ffp['comment_upload']['form_path'] = array(
      '#type' => 'fieldset',
      '#title' => t('Comment Upload Path settings'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#weight' => $form['comment']['comment_upload']['#weight'] + 1,
    );

    $ffp['comment_upload']['form_path']['file_path'] = array(
      '#type' => 'textfield',
      '#title' => t('File path'),
      '#description' => t('Optional subdirectory within the "%dir" directory where files will be stored. Do not include trailing slash.', array('%dir' => variable_get('file_directory_path', 'files'))),
      '#tree' => TRUE,
    );
  }
}

/**
 * Implementation of hook_filefield_paths_form_submit().
 */
function comment_upload_filefield_paths_form_submit(&$form_state, &$ffp) {
  if ($form_state['values']['form_id'] == 'node_type_form') {
    $ffp['comment_upload'] = array(
      'type' => $form_state['values']['type'],
    );
  }
}

/**
 * Implementation of hook_filefield_paths_get_fields().
 */
function comment_upload_filefield_paths_get_fields(&$node, &$ffp) {
  if (is_object($node) && $node->form_id == 'comment_form') {
    if (isset($node->files)) {
      foreach ($node->files as &$file) {
        $ffp['#files'][] = array(
          'field' => &$file,
          'module' => 'comment_upload',
          'name' => 'comment_upload',
          'new' => $file['new']
        );

        $ffp['#types']['comment_upload'] = TRUE;
      }
    }
  }
}

/**
 * Implementation of hook_filefield_paths_batch_update().
 */
function comment_upload_filefield_paths_batch_update($field_name, $type_name, &$objects) {
  if (empty($field_name)) {
    $result = db_query(
      "SELECT DISTINCT(cu.cid) FROM {comment_upload} cu LEFT JOIN {node} n
      ON cu.nid = n.nid WHERE n.type = '%s'", $type_name
    );

    // Build array of Comment IDs.
    while ($comment = db_fetch_object($result)) {
      $objects[] = $comment->cid;
    }
  }
}

/**
 * Implementation of hook_filefield_paths_update().
 */
function comment_upload_filefield_paths_update($oid, $field_name) {
  if (empty($field_name)) {
    $comment = _comment_load($oid);
    comment_invoke_comment($comment, 'view');

    // Flag files for update.
    if (isset($comment->files)) {
      foreach ($comment->files as &$file) {
        $file['new'] = TRUE;
      }
    }

    // Set Form ID.
    $comment->form_id = 'comment_form';

    // Process Comment.
    filefield_paths_comment((array) $comment, 'update');
  }
}

/**
 * Implementation of hook_comment().
 */
function filefield_paths_comment($a1, $op) {
  switch ($op) {
    case 'insert':
    case 'update':
      $update = new stdClass;
      $update->node = FALSE;
      $node = node_load($a1['nid']);

      $object = new stdClass();
      $object->form_id = $a1['form_id'];
      $object->type = $node->type;
      $object->files = $a1['files'];

      if (($ffp = filefield_paths_get_fields($object)) == FALSE) {
        break;
      }

      // Process files
      foreach ($ffp['#files'] as &$file) {
        module_invoke_all('filefield_paths_process_file', $file['new'], $file, $ffp['#settings'][$file['name']], $node, $update);
      }
      break;
  }
}
