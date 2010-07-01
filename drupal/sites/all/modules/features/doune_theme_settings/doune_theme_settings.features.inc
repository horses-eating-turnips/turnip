<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function doune_theme_settings_ctools_plugin_api() {
  module_load_include('inc', 'doune_theme_settings', 'doune_theme_settings.defaults');
  $args = func_get_args();
  return call_user_func_array('_doune_theme_settings_ctools_plugin_api', $args);
}

/**
 * Implementation of hook_strongarm().
 */
function doune_theme_settings_strongarm() {
  module_load_include('inc', 'doune_theme_settings', 'doune_theme_settings.defaults');
  $args = func_get_args();
  return call_user_func_array('_doune_theme_settings_strongarm', $args);
}
