<?php
// $Id: image.inc 843 2009-07-08 01:03:08Z jhedstrom $

/**
 * @file
 * Provides FileField Paths integration with the Image module.
 */

/**
 * Implementation of hook_filefield_paths_form_alter().
 */
function image_filefield_paths_form_alter(&$form, &$ffp) {
  if ($form['#id'] == 'image-admin-settings') {
    $ffp['image'] = array(
      'type' => 'image',
      'form_path' => &$form['files']['ffp_image'],
      'file_path_default' => $form['files']['image_default_path']['#default_value']
    );

    // Create path settings fieldset
    $ffp['image']['form_path'] = array(
      '#type' => 'fieldset',
      '#title' => t('Image Path settings'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#weight' => 0,
    );

    $ffp['image']['form_path']['file_path'] = $form['files']['image_default_path'];
    $ffp['image']['form_path']['file_path']['#title'] = t('File path');
    $form['files']['image_default_path']['#access'] = FALSE;
  }
}

/**
 * Implementation of hook_filefield_paths_form_submit().
 */
function image_filefield_paths_form_submit(&$form_state, &$ffp) {
  $ffp['image'] = array(
    'type' => 'image',
  );
}

/**
 * Implementation of hook_filefield_paths_get_fields().
 */
function image_filefield_paths_get_fields(&$node, &$ffp) {
  if ($node->type == 'image') {
    $info = array();

    $result = db_query('SELECT * FROM {image} WHERE nid = %d', $node->nid);
    while ($data = db_fetch_object($result)) {
      $info[$data->image_size] = $data->fid;
    }

    foreach ($node->images as $name => &$file) {
      if (isset($info[$name])) {
        $file_info = pathinfo($file);
  
        $ffp['#files'][] = array(
          'field' => array(
            'filepath' => &$file,
            'filename' => $file_info['basename'],
            'fid' => $info[$name],
            'type' => $name
          ),
          'module' => 'image',
          'name' => 'image',
          'new' => $node->new_file
        );
  
        $ffp['#types']['image'] = TRUE;
      }
    }
  }
}

/**
 * Implementation of hook_filefield_paths_batch_update().
 */
function image_filefield_paths_batch_update($field_name, $type_name, &$objects) {
  if (empty($field_name) && empty($field_name)) {
    $result = db_query("SELECT nid FROM {node} WHERE type = '%s'", 'image');

    // Build array of Node IDs.
    while ($node = db_fetch_object($result)) {
      $objects[] = $node->nid;
    }
  }
}

/**
 * Implementation of hook_filefield_paths_update().
 */
function image_filefield_paths_update($oid, $field_name) {
  if (empty($field_name)) {
    $node = node_load($oid);

    // Flag files for update.
    $node->new_file = TRUE;

    // Process Node.
    filefield_paths_nodeapi($node, 'update', NULL, NULL);
  }
}
