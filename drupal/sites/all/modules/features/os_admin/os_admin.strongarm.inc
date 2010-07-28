<?php

/**
 * Implementation of hook_strongarm().
 */
function os_admin_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'admin_theme';
  $strongarm->value = 'rubik';

  $export['admin_theme'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'admin_toolbar';
  $strongarm->value = array(
    'layout' => 'horizontal',
    'position' => 'sw',
    'blocks' => array(
      'admin-create' => -1,
      'admin-theme' => 1,
      'admin-account' => -1,
      'admin-menu' => 1,
    ),
  );

  $export['admin_toolbar'] = $strongarm;
  return $export;
}
