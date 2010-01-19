<?php
// $Id: imagefield_crop.inc 843 2009-07-08 01:03:08Z jhedstrom $

/**
 * @file
 * Provides ImageField Crop module specific functions for FileField Paths.
 */

/**
 * Implementation of hook_filefield_paths_process_file().
 */
function imagefield_crop_filefield_paths_process_file($new, $file, $settings, $node, $update) {
  if ($new) {
    // Move ImageField Crop image.
    if (isset($file['widget']) && $file['widget'] == 'imagefield_crop' && file_exists($crop_source = imagefield_crop_file_admin_crop_display_path(array('filepath' => $file['filepath']['old'])))) {
      file_move($crop_source, imagefield_crop_file_admin_crop_display_path(array('filepath' => $file['filepath']['new'])));
    }
  }
}
