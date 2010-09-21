<?php
// $Id: opensourcery_install.profile 880 2009-09-04 00:10:54Z jhedstrom $

if (!function_exists('profiler_v2')) {
  require 'libraries/profiler/profiler.inc';
}
profiler_v2('opensourcery_install');

/**
 * Implementation of hook_install().
 */
function opensourcery_install_install() {
  // Don't display date and author information for page nodes by default.
  $theme_settings = variable_get('theme_settings', array());
  $theme_settings['toggle_node_info_page'] = FALSE;
  variable_set('theme_settings', $theme_settings);

  // Assign sensible input filter defaults to roles.
  _opensourcery_install_better_formats();

  // Initial permissions.
  _opensourcery_install_set_permissions();

  // Since content_profile adds a value for this variable during
  // install, we must delete it here.
  variable_del('content_profile_profile');

  // Cleanup after pathauto.
  variable_del('pathauto_node_page_pattern');
  variable_del('pathauto_node_story_pattern');
}

/**
 * Set site editor and administrator default input format to full HTML.
 */
function _opensourcery_install_better_formats() {
  $roles = array();
  foreach (user_roles() as $rid => $name) {
    if (in_array($name, array('site editor', 'administrator'))) {
      $roles[] = $rid;
      // Float admin to top, site editor 2nd highest.
      $weight = -2 * $rid;
      db_query("UPDATE {better_formats_defaults} SET format = %d, weight = %d WHERE rid = %d AND type = '%s'", array(':format' => 2, ':weight' => $weight, ':rid' => $rid, ':type' => 'node'));
      db_query("UPDATE {better_formats_defaults} SET format = %d, weight = %d WHERE rid = %d AND type = '%s'", array(':format' => 2, ':weight' => $weight, ':rid' => $rid, ':type' => 'comment'));
    }
  }
  $current = db_result(db_query("SELECT roles FROM {filter_formats} WHERE format = 2"));
  if ($current) {
    $current = explode(',', $roles);
    $roles = array_merge($current, $roles);
  }
  $roles = ','. implode(',', $roles) .',';
  // Allow site editors and administrators to use HTML;
  db_query("UPDATE {filter_formats} SET roles = '%s' WHERE format = 2", array(':roles' => $roles));
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
  if (!db_result(db_query("SELECT rid FROM {permission} LEFT JOIN {role} USING (rid) WHERE name = '%s'", array(':role_name' => 'administrator')))) {
    db_query("INSERT INTO {permission} (rid, perm) VALUES (%d, '%s')", array(':rid' => $admin_rid, implode(', ', $admin_user_perms)));
    drupal_set_message(t("Set sensible defaults for %role role.", array('%role' => 'administrator')));
  }

  $site_editor_rid = array_search('site editor', $roles);
  $site_editor_user_perms = array(
    'create url aliases',
    'revert revisions',
    'view revisions',
  );
  if (!db_result(db_query("SELECT rid FROM {permission} LEFT JOIN {role} USING (rid) WHERE name = '%s'", array(':role_name' => 'site editor')))) {
    db_query("INSERT INTO {permission} (rid, perm) VALUES (%d, '%s')", array(':rid' => $site_editor_rid, implode(', ', $site_editor_user_perms)));
    drupal_set_message(t("Set sensible defaults for %role role.", array('%role' => 'site editor')));
  }
}
