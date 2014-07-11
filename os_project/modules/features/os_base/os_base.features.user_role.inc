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

  // Exported role: content editor.
  $roles['content editor'] = array(
    'name' => 'content editor',
    'weight' => 3,
  );

  // Exported role: developer.
  $roles['developer'] = array(
    'name' => 'developer',
    'weight' => 4,
  );

  return $roles;
}
