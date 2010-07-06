<?php
// $Id: image.inc,v 1.1.2.8 2010/01/11 06:07:16 deciphered Exp $
/**
 * @file
 * Provides FileField Paths integration with the Image module.
 */

/**
 * Implements hook_filefield_paths_form_alter().
 */
function image_filefield_paths_form_alter(&$form, &$ffp) {
  if (isset($form['#id']) && $form['#id'] == 'image-admin-settings') {
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
 * Implements hook_filefield_paths_form_submit().
 */
function image_filefield_paths_form_submit(&$form_state, &$ffp) {
  if (isset($form_state['values']['ffp_image'])) {
    $ffp['image'] = array(
      'type' => 'image',
    );
  }
}

/**
 * Implements hook_filefield_paths_get_fields().
 */
function image_filefield_paths_get_fields(&$node, &$ffp) {
  if ($node->type == 'image') {
    $info = $origname = array();

    $result = db_query('SELECT i.*, f.origname FROM {image} i JOIN {files} f ON i.fid = f.fid  WHERE i.nid = %d', $node->nid);
    while ($data = db_fetch_object($result)) {
      $info[$data->image_size] = $data->fid;
      $origname[$data->image_size] = $data->origname;
    }

    foreach ($node->images as $name => &$file) {
      if (isset($info[$name])) {
        $file_info = pathinfo($file);

        $ffp['#files'][] = array(
          'field' => array(
            'filepath' => &$file,
            'filename' => $file_info['basename'],
            'fid' => $info[$name],
            'type' => $name,
            'origname' => $origname[$name],
          ),
          'module' => 'image',
          'name' => 'image',
          'new' => $node->new_file || $node->rebuild_images,
        );

        $ffp['#types']['image'] = TRUE;
      }
    }
  }
}

/**
 * Implements hook_filefield_paths_batch_update().
 */
function image_filefield_paths_batch_update($field, $type, &$objects) {
  $result = db_query("SELECT nid FROM {node} WHERE type = '%s'", 'image');

  // Build array of Node IDs.
  while ($node = db_fetch_object($result)) {
    $objects[] = $node->nid;
  }
}

/**
 * Implements hook_filefield_paths_update().
 */
function image_filefield_paths_update($oid, $field) {
  $node = node_load($oid);

  if (isset($node->images)) {
    // Flag files for update.
    $node->new_file = TRUE;

    // Process Node.
    filefield_paths_nodeapi($node, 'update', NULL, NULL);
  }
}
