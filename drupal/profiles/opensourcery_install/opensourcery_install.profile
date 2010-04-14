<?php
// $Id: opensourcery_install.profile 880 2009-09-04 00:10:54Z jhedstrom $

/**
 * Return an array of the modules to be enabled when this profile is installed.
 *
 * @return array
 *   An array of modules to enable.
 */
function opensourcery_install_profile_modules() {
  $modules = array(
    // Drupal core modules.
    'help', 'menu', 'taxonomy', 'dblog', 'path',

    // Contributed modules.
    'admin_menu',
    'advanced_help',
    'better_formats',
    'pathauto',
    'path_redirect',
    'role_delegation',
    'strongarm',
    'token',
    'wysiwyg',

    // Custom modules.
    'os_custom',

    // Development modules.
    'devel',
  );

  return $modules;
}

/**
 * Return a description of the profile for the initial installation screen.
 *
 * @return
 *   An array with keys 'name' and 'description' describing this profile,
 *   and optional 'language' to override the language selection for
 *   language-specific profiles.
 */
function opensourcery_install_profile_details() {
  return array(
    'name' => 'OpenSourcery',
    'description' => st('Select this profile to enable a OpenSourcery base-install.'),
  );
}

/**
 * Return a list of tasks that this profile supports.
 *
 * @return
 *   A keyed array of tasks the profile will perform during
 *   the final stage. The keys of the array will be used internally,
 *   while the values will be displayed to the user in the installer
 *   task list.
 */
function opensourcery_install_profile_task_list() {
}

/**
 * Perform any final installation tasks for this profile.
 *
 * The installer goes through the profile-select -> locale-select
 * -> requirements -> database -> profile-install-batch
 * -> locale-initial-batch -> configure -> locale-remaining-batch
 * -> finished -> done tasks, in this order, if you don't implement
 * this function in your profile.
 *
 * If this function is implemented, you can have any number of
 * custom tasks to perform after 'configure', implementing a state
 * machine here to walk the user through those tasks. First time,
 * this function gets called with $task set to 'profile', and you
 * can advance to further tasks by setting $task to your tasks'
 * identifiers, used as array keys in the hook_profile_task_list()
 * above. You must avoid the reserved tasks listed in
 * install_reserved_tasks(). If you implement your custom tasks,
 * this function will get called in every HTTP request (for form
 * processing, printing your information screens and so on) until
 * you advance to the 'profile-finished' task, with which you
 * hand control back to the installer. Each custom page you
 * return needs to provide a way to continue, such as a form
 * submission or a link. You should also set custom page titles.
 *
 * You should define the list of custom tasks you implement by
 * returning an array of them in hook_profile_task_list(), as these
 * show up in the list of tasks on the installer user interface.
 *
 * Remember that the user will be able to reload the pages multiple
 * times, so you might want to use variable_set() and variable_get()
 * to remember your data and control further processing, if $task
 * is insufficient. Should a profile want to display a form here,
 * it can; the form should set '#redirect' to FALSE, and rely on
 * an action in the submit handler, such as variable_set(), to
 * detect submission and proceed to further tasks. See the configuration
 * form handling code in install_tasks() for an example.
 *
 * Important: Any temporary variables should be removed using
 * variable_del() before advancing to the 'profile-finished' phase.
 *
 * @param $task
 *   The current $task of the install system. When hook_profile_tasks()
 *   is first called, this is 'profile'.
 * @param $url
 *   Complete URL to be used for a link or form action on a custom page,
 *   if providing any, to allow the user to proceed with the installation.
 *
 * @return
 *   An optional HTML string to display to the user. Only used if you
 *   modify the $task, otherwise discarded.
 */
function opensourcery_install_profile_tasks(&$task, $url) {

  // Insert default user-defined node types into the database. For a complete
  // list of available node type attributes, refer to the node type API
  // documentation at: http://api.drupal.org/api/HEAD/function/hook_node_info.
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

  // Default page to not be promoted, and have comments disabled, and create new revisions.
  variable_set('node_options_page', array('status', 'revision'));
  variable_set('comment_page', COMMENT_NODE_DISABLED);

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
  // Pathauto defaults.
  _opensourcery_install_pathauto();
  // Core configuration and tweaks.
  _opensourcery_install_core();


  // Update the menu router information.
  menu_rebuild();
}

/**
 * Implementation of hook_form_alter().
 *
 * Allows the profile to alter the site-configuration form. This is
 * called through custom invocation, so $form_state is not populated.
 */
function opensourcery_install_form_alter(&$form, $form_state, $form_id) {
  if ($form_id == 'install_configure') {
    // Set default for site name field.
    $form['site_information']['site_name']['#default_value'] = $_SERVER['SERVER_NAME'];
  }
}

/**
 * Creates Site Editor and Web Admin roles.
 */
function _opensourcery_install_user_roles() {
  foreach (array('site editor', 'web admin') as $role) {
    if (!db_result(db_query("SELECT rid FROM {role} WHERE name = '%s'", array(':role_name' => $role)))) {
      db_query("INSERT INTO {role} (name) VALUES ('%s')", $role);
      drupal_set_message(t('The %role role has been added.', array('%role' => $role)));
      $dummy = array();
      better_formats_new_role($dummy, $dummy);
    }
  }
}

/**
 * Set site editor and web admin default input format to full HTML.
 */
function _opensourcery_install_better_formats() {
  $roles = array();
  foreach (user_roles() as $rid => $name) {
    if (in_array($name, array('site editor', 'web admin'))) {
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
  // Allow site editors and web admins to use HTML;
  db_query("UPDATE {filter_formats} SET roles = '%s' WHERE format = 2", array(':roles' => $roles));
}

/**
 * Set some sensible permissions.
 */
function _opensourcery_install_set_permissions() {
  $roles = user_roles();
  $admin_rid = array_search('web admin', $roles);
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
    'assign web admin role',
    'administer users',
    'access administration pages',
  );
  if (!db_result(db_query("SELECT rid FROM {permission} LEFT JOIN {role} USING (rid) WHERE name = '%s'", array(':role_name' => 'web admin')))) {
    db_query("INSERT INTO {permission} (rid, perm) VALUES (%d, '%s')", array(':rid' => $admin_rid, implode(', ', $admin_user_perms)));
    drupal_set_message(t("Set sensible defaults for %role role.", array('%role' => 'web admin')));
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

/**
 * Initial settings for pathauto and path redirect.
 */
function _opensourcery_install_pathauto() {
  /* Get rid of wonky content/foo pattern.
   * The rationale is that it's easier to bulk-update pathauto aliases
   * than it is to remove unwanted ones.
   * We leave this blank because there's no one-size-fits all pattern.
   */
  variable_set('pathauto_node_pattern', '');
  // Remove story pattern.  Even though we didn't create a story type,
  // pathauto will insert this default anyway.
  variable_del('pathauto_node_story_pattern');

  // Path redirect settings.
  $conf['path_redirect_allow_bypass'] = 0;
  $conf['path_redirect_auto_redirect'] = 1;
  $conf['path_redirect_default_status'] = '301';
  $conf['path_redirect_purge_inactive'] = '31536000'; // 1 year.
  $conf['path_redirect_redirect_warning'] = 0;
  foreach ($conf as $var => $val) {
    variable_set($var, $val);
  }
}

/**
 * Core customization.
 */
function _opensourcery_install_core() {
  // Change default anonymous to "Visitor".
  // @todo...present a form so it can easily be changed on install, set default
  // to "Visitor".
  variable_set('anonymous', 'Visitor');
  
  /* Increase the capacity of the Drupal watchdog.
   * The default of 1000 rows overflows too quickly, sometimes losing important
   * debug information.  100k rows is big, yet should still keep the watchdog
   * table under 10MB.
   */
  variable_set('dblog_row_limit', 100000);
  
  /* Set "Only site administrators can create new user accounts."
   * Drupal's default is open registration, which is easily overlooked.
   */
  variable_set("user_register", 0);
  
}
