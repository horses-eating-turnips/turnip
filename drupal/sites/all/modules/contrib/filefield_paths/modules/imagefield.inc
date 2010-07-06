<?php
// $Id: imagefield.inc,v 1.1.2.2 2010/01/11 06:07:16 deciphered Exp $
/**
 * @file
 * Provides ImageField module specific functions for FileField Paths.
 */

/**
 * Implements hook_filefield_paths_process_file().
 */
function imagefield_filefield_paths_process_file($new, $file, $settings, $node, $update) {
  if ($new) {
    // Delete ImageField thumbnail.
    if (isset($file['widget']) && $file['widget'] == 'imagefield' && file_exists($thumbnail_source = imagefield_file_admin_thumb_path(array('filepath' => $file['filepath']['old'])))) {
      file_delete($thumbnail_source);
    }
  }
}

/**
 * Implements hook_filefield_paths_cleanup().
 */
function imagefield_filefield_paths_cleanup(&$ffp, $paths, $name) {
  // Check for ImageFields.
  $imagefield = FALSE;
  foreach ($ffp['#files'] as $file) {
    if ($file['name'] == $name) {
      if (isset($file['widget']) && $file['widget'] == 'imagefield') {
        $imagefield = TRUE;
      }
      break;
    }
  }
  // Cleanup ImageFields temporary thumbnail paths.
  if ($imagefield) {
    array_unshift($paths, 'imagefield_thumbs');
    filefield_paths_cleanup_temp($paths);
  }
}
