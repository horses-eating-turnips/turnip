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
  $types = array(
    array(
      'type' => 'page',
      'name' => st('Page'),
      'module' => 'node',
      'description' => st("A <em>page</em> is a simple method for creating and displaying information that rarely changes, such as an \"About us\" section of a website. By default, a <em>page</em> entry does not allow visitor comments and is not featured on the site's initial home page."),
      'custom' => TRUE,
      'modified' => TRUE,
      'locked' => FALSE,
      'help' => '',
      'min_word_count' => '',
    ),
  );

  foreach ($types as $type) {
    $type = (object) _node_type_set_defaults($type);
    node_type_save($type);
  }

  // Don't display date and author information for page nodes by default.
  $theme_settings = variable_get('theme_settings', array());
  $theme_settings['toggle_node_info_page'] = FALSE;
  variable_set('theme_settings', $theme_settings);

  // Create roles.
  _opensourcery_install_user_roles();

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
 * Creates Site Editor and Administrator roles.
 */
function _opensourcery_install_user_roles() {
  foreach (array('site editor', 'administrator') as $role) {
    if (!db_result(db_query("SELECT rid FROM {role} WHERE name = '%s'", array(':role_name' => $role)))) {
      db_query("INSERT INTO {role} (name) VALUES ('%s')", $role);
      drupal_set_message(t('The %role role has been added.', array('%role' => $role)));
      $dummy = array();
      better_formats_new_role($dummy, $dummy);
    }
  }
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
    'create page content',
    'delete any page content',
    'edit any page content',
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
    'create page content',
    'delete own page content',
    'edit any page content',
    'revert revisions',
    'view revisions',
  );
  if (!db_result(db_query("SELECT rid FROM {permission} LEFT JOIN {role} USING (rid) WHERE name = '%s'", array(':role_name' => 'site editor')))) {
    db_query("INSERT INTO {permission} (rid, perm) VALUES (%d, '%s')", array(':rid' => $site_editor_rid, implode(', ', $site_editor_user_perms)));
    drupal_set_message(t("Set sensible defaults for %role role.", array('%role' => 'site editor')));
  }
}
