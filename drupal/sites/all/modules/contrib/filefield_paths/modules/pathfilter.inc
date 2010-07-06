<?php
// $Id: pathfilter.inc,v 1.1.2.2 2010/01/11 06:07:16 deciphered Exp $
/**
 * @file
 * Provides FileField Paths integration with the Path Filter module.
 */

/**
 * Implements hook_filefield_paths_process_file().
 */
function pathfilter_filefield_paths_process_file($new, &$file, $settings, &$node, &$update) {
  if ($new && dirname($file['filepath']['new']) != dirname($file['filepath']['old']) || $file['filename']['new'] != $file['filename']['old']) {
    $file_directory_path = variable_get('file_downloads', FILE_DOWNLOADS_PUBLIC) == FILE_DOWNLOADS_PUBLIC ? file_directory_path() : 'system/files';

    // Regular expression to replace old file reference.
    $pattern = array(
      'regex' => 'files:([^"]*?)' . str_replace('/', '\/', str_replace(file_directory_path() . '/', '', $file['filepath']['old'])),
      'regex_enc' => 'files:([^"]*?)' . str_replace('/', '\/', str_replace(drupal_urlencode(file_directory_path()) . '/', '', drupal_urlencode($file['filepath']['old']))),
      'replace' => 'files:$1' . str_replace(file_directory_path() . '/', '', $file['filepath']['new']),
    );

    // Process regular expression.
    _filefield_paths_replace_pattern($pattern, $node, $update);
  }
}
