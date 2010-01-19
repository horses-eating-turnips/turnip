<?php
// $Id: imagefield.inc,v 1.1 2009/10/21 06:23:43 quicksketch Exp $

/**
 * @file
 * Insert support for ImageField module.
 */

/**
 * Implementation of hook_insert_widgets().
 */
function imagefield_insert_widgets() {
  return array(
    'imagefield_widget' => array(
      'wrapper' => '.filefield-element',
      'fields' => array(
        'alt' => 'input[name$="[alt]"]',
        'title' => 'input[name$="[title]", textarea[name$="[title]"]',
        'description' => 'input[name$="[description]"], textarea[name$="[description]"]',
      ),
    ),
  );
}
