<?php
/**
 * @file
 * os_base.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function os_base_user_default_roles() {
  $roles = array();

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 3,
  );

  // Exported role: site editor.
  $roles['site editor'] = array(
    'name' => 'site editor',
    'weight' => 4,
  );

  return $roles;
}
