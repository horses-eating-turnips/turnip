<?php
// $Id: path_redirect_generate.drush.inc,v 1.1.2.2 2009/12/02 10:54:25 davereid Exp $

/**
 * @file
 * Generate redirects via drush framework.
 */

/**
 * Implementation of hook_drush_help().
 */
function path_redirect_generate_drush_help($section) {
  switch ($section) {
    case 'drush:generate redirects':
      return dt('Generate URL redirects.');
  }
}

/**
 * Implementation of hook_drush_command().
 */
function path_redirect_generate_drush_command() {
  $items['generate redirects'] = array(
    'callback' => 'drush_generate_redirects',
    'description' => 'Creates URL redirects.',
    'arguments' => array(
      'num_redirects' => 'Number of redirects to generate.',
    ),
    'options' => array(
      'kill' => 'Delete all redirects before generating new ones.',
    ),
  );
  return $items;
}

/**
 * Command callback. Generate a number of redirects.
 */
function drush_generate_redirects($num_redirects = NULL) {
  require_once drupal_get_path('module', 'devel_generate') . '/devel_generate.drush.inc';
  if (drush_generate_is_number($num_redirects) == FALSE) {
    drush_set_error('DEVEL_GENERATE_INVALID_NUMBER', dt('Invalid number of redirects.'));
  }
  drush_generate_include_devel();
  drush_op('path_redirect_generate_redirects', $num_redirects, drush_get_option('kill'));
  drush_log(dt('Generated @number redirects.', array('@number' => $num_redirects)), 'ok');
}
