<?php

/**
 * Helper to implementation of hook_ctools_plugin_api().
 */
function _os_admin_ctools_plugin_api() {
  $args = func_get_args();
  $module = array_shift($args);
  $api = array_shift($args);
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Helper to implementation of hook_user_default_permissions().
 */
function _os_admin_user_default_permissions() {
  $permissions = array();

  // Exported permission: use admin toolbar
  $permissions[] = array(
    'name' => 'use admin toolbar',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  return $permissions;
}

/**
 * Helper to implementation of hook_strongarm().
 */
function _os_admin_strongarm() {
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
    'layout' => 'vertical',
    'position' => 'nw',
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
