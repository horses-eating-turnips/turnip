<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function os_admin_user_default_permissions() {
  $permissions = array();

  // Exported permission: use admin toolbar
  $permissions['use admin toolbar'] = array(
    'name' => 'use admin toolbar',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  return $permissions;
}
