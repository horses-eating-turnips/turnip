<?php

// $Id: template.php 897 2009-12-31 20:46:29Z jhedstrom $

/**
 * @file
 * OpenSourcery base theme template.php.
 */


/**
 * Implementation of preprocess_page().
 */
function os_base_preprocess_page(&$vars) {
  // Set head tag, based on front page or not.
  $vars['head_tag'] = drupal_is_front_page() ? 'h1' : 'div';
  $vars['title_tag'] = drupal_is_front_page() ? 'h2' : 'h1';
}