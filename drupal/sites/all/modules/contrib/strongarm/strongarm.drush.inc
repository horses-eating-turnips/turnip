<?php
// $Id: strongarm.drush.inc,v 1.1.2.2 2009/09/24 15:59:54 jmiccolis Exp $

/**
 * @file
 * Drush integration for Strongarm. Provides commands to export variables.
 */

/**
 * Implementation of hook_drush_help().
 */
function strongarm_drush_help($section) {
  switch ($section) {
    case 'drush:strongarm':
      return dt("Export Drupal variables. Without any arguments a list of all variables will be shown. If arguments are specified they'll be var_exported to stdout.");
  }
}

/**
 * Implementation of hook_drush_command().
 */
function strongarm_drush_command() {
  $items['strongarm'] = array(
    'callback' => 'strongarm_drush_export',
    'description' => 'Export variable(s).',
  );
  return $items;
}

// Callback for strongarm command.
function strongarm_drush_export() {
  $vars = func_get_args();
  if (empty($vars)) {
    // Pull all variables from DB.
    $result = db_query('SELECT name FROM variable');
    $variables = array();
    while ($variable = db_fetch_object($result)) {
      $variables[$variable->name] = $variable->name;
    }

    // Pull all variables defined in hook_strongarm(), merge them in.
    $strongarmed = drupal_map_assoc(array_keys(strongarm_get_conf(TRUE, TRUE)));
    $variables = $variables + $strongarmed;
    ksort($variables);

    // Output result, flag strongarmed variables.
    $rows = array(array('Strongarmed', 'Variable name'));
    foreach ($variables as $variable) {
      $flag = $strongarmed[$variable] ? '*' : '';
      $rows[] = array($flag, $variable);
    }
    drush_print_table($rows, TRUE);
  }
  else {
    $exports = array();
    foreach ($vars as $v) {
      // We use the very unlikely 'DRUSH_STRONGARM_NO_VALUE_HERE' as the 
      // default value which *should* be ok, right?
      $variable = variable_get($v, 'DRUSH_STRONGARM_NO_VALUE_HERE');
      if ($variable !== 'DRUSH_STRONGARM_NO_VALUE_HERE') {
        $exports[$v] = $variable;
      }
    }
    drush_print(var_export($exports));
  }
}
