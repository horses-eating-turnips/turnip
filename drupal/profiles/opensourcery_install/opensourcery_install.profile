<?php
// $Id: opensourcery_install.profile 880 2009-09-04 00:10:54Z jhedstrom $

/**
 * Implementation of hook_install().
 */
function opensourcery_install_install() {
  // Don't display date and author information for page nodes by default.
  $theme_settings = variable_get('theme_settings', array());
  $theme_settings['toggle_node_info_page'] = FALSE;
  variable_set('theme_settings', $theme_settings);

  // Initial permissions.
  // @TODO _opensourcery_install_set_permissions();

  // Since content_profile adds a value for this variable during
  // install, we must delete it here.
  variable_del('content_profile_profile');

  // Cleanup after pathauto.
  variable_del('pathauto_node_page_pattern');
  variable_del('pathauto_node_story_pattern');
}

/**
 * Set some sensible permissions.
 */
function _opensourcery_install_set_permissions() {
  $roles = user_roles();
  $admin_rid = array_search('administrator', $roles);
  $admin_user_perms = array(
    'access administration menu',
    'create url aliases',
    'administer menu',
    'administer nodes',
    'revert revisions',
    'view revisions',
    'assign site editor role',
    'assign administrator role',
    'administer users',
    'access administration pages',
  );
  if (!db_query("SELECT rid FROM {permission} LEFT JOIN {role} USING (rid) WHERE name = :role_name", array(':role_name' => 'administrator'))->fetchField()) {
    $fields = array(
      'rid' => $admin_rid,
      'perm' => implode(', ', $admin_user_perms),
    );
    db_insert('permission')
      ->fields($fields)
      ->execute();
    drupal_set_message(t("Set sensible defaults for %role role.", array('%role' => 'administrator')));
  }

  $site_editor_rid = array_search('site editor', $roles);
  $site_editor_user_perms = array(
    'create url aliases',
    'revert revisions',
    'view revisions',
  );
  if (!db_query("SELECT rid FROM {permission} LEFT JOIN {role} USING (rid) WHERE name = '%s'", array(':role_name' => 'site editor'))->fetchField()) {
    $fields = array(
      'rid' => $site_editor_rid,
      'perm' => $site_editor_user_perms,
    );
    db_insert('permission')
      ->fields($fields)
      ->execute();
    drupal_set_message(t("Set sensible defaults for %role role.", array('%role' => 'site editor')));
  }
}
