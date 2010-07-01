<?php

/**
 * Helper to implementation of hook_ctools_plugin_api().
 */
function _doune_theme_settings_ctools_plugin_api() {
  $args = func_get_args();
  $module = array_shift($args);
  $api = array_shift($args);
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Helper to implementation of hook_strongarm().
 */
function _doune_theme_settings_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'theme_doune_settings';
  $strongarm->value = array(
    'zen_block_editing' => 0,
    'zen_breadcrumb' => 'no',
    'zen_breadcrumb_separator' => ' › ',
    'zen_breadcrumb_home' => 1,
    'zen_breadcrumb_trailing' => 1,
    'zen_breadcrumb_title' => 0,
    'zen_rebuild_registry' => 0,
    'zen_wireframes' => 0,
    'toggle_logo' => 1,
    'toggle_name' => 1,
    'toggle_slogan' => 0,
    'toggle_mission' => 1,
    'toggle_node_user_picture' => 0,
    'toggle_comment_user_picture' => 0,
    'toggle_search' => 0,
    'toggle_favicon' => 1,
    'toggle_primary_links' => 1,
    'toggle_secondary_links' => 1,
    'default_logo' => 1,
    'logo_path' => '',
    'logo_upload' => '',
    'default_favicon' => 0,
    'favicon_path' => '',
    'favicon_upload' => '',
  );

  $export['theme_doune_settings'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'theme_settings';
  $strongarm->value = array(
    'toggle_logo' => 0,
    'toggle_name' => 1,
    'toggle_slogan' => 0,
    'toggle_mission' => 0,
    'toggle_node_user_picture' => 0,
    'toggle_comment_user_picture' => 0,
    'toggle_search' => 0,
    'toggle_favicon' => 0,
    'toggle_primary_links' => 1,
    'toggle_secondary_links' => 0,
    'toggle_node_info_group' => 0,
    'toggle_node_info_group_confirmation' => 1,
    'toggle_node_info_page' => 0,
    'toggle_node_info_priority_code' => 0,
    'toggle_node_info_profile' => 0,
    'toggle_node_info_shift' => 0,
    'toggle_node_info_signup' => 1,
    'default_logo' => 0,
    'logo_path' => '',
    'logo_upload' => '',
    'default_favicon' => 0,
    'favicon_path' => '',
    'favicon_upload' => '',
  );

  $export['theme_settings'] = $strongarm;
  return $export;
}
