<?php
/**
 * @file
 * Rename and replace all instances of 'os_project' with 'PROJECTNAME'.
 */

/**
 * Set us as the default install profile, remove defaults and OpenSourcery.
 */
function system_form_install_select_profile_form_alter(&$form, $form_state) {
  unset($form['profile']['Minimal'], $form['profile']['Standard'], $form['profile']['OpenSourcery']);
  foreach($form['profile'] as $key => $element) {
    $form['profile'][$key]['#value'] = 'os_project';
  }
}

/**
 * Implementation of hook_form_FORM_ID_alter().
 *
 * Set defaults on "Configure site" form during installation.
 */
function os_project_form_install_configure_form_alter(&$form, $form_state) {
  $server_name = $_SERVER['SERVER_NAME'];

  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value']    = $server_name;

  // Other defaults, useful for speeding up development installs
  $form['site_information']['site_mail']['#default_value']    = 'webmaster@'. $server_name;
  $form['admin_account']['account']['name']['#default_value'] = 'admin';
  $form['admin_account']['account']['mail']['#default_value'] = 'webmaster@'. $server_name;

  // Don't enable update module
  $form['update_notifications']['update_status_module']['#default_value'] = array();
}
