<?php
// $Id: strongarm.admin.inc 891 2009-12-01 19:18:51Z jhedstrom $

/**
 * Main admin page menu callback.
 */
function strongarm_admin_page() {
  $output = '';
  $output .= drupal_get_form('strongarm_admin_settings_form');
  if (variable_get('strongarm_mode', STRONGARM_MODE_STRONG) == STRONGARM_MODE_WEAK) {
    $output .= drupal_get_form('strongarm_admin_form');
  }
  return $output;
}

/**
 * Get a map of variable to culprit (implementers of hook_strongarm()).
 */
function strongarm_get_culprits() {
  $culprits = array();
  foreach (module_implements('strongarm') as $module) {
    $module_conf = module_invoke($module, 'strongarm');
    foreach ($module_conf as $name => $value) {
      $culprits[$name] = $module;
    }
  }
  return $culprits;
}

/**
 * Settings form.
 */
function strongarm_admin_settings_form() {
  $form = array();
  $form['strongarm_mode'] = array(
    '#title' => t('Strongarm mode'),
    '#description' => t('Choose the strength of strongarm\'s restrictive behavior.'),
    '#type' => 'radios',
    '#options' => array(
      STRONGARM_MODE_STRONG => t('Force variables values'),
      STRONGARM_MODE_WEAK => t('Allow variable overrides'),
    ),
    '#default_value' => variable_get('strongarm_mode', STRONGARM_MODE_STRONG),
  );
  $form['strongarm_show_messages'] = array(
    '#title' => t('Show messages'),
    '#description' => t('Show helper messages to site administrators when variables have been strongarmed or overridden.'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('strongarm_show_messages', TRUE),
  );
  return system_settings_form($form);
}

/**
 * Variable management strongarm form.
 */
function strongarm_admin_form() {
  $form = array();

  $var_conf = strongarm_get_conf();
  $culprits = strongarm_get_culprits();

  $overridden = array();
  $result = db_query("SELECT * FROM {variable} ORDER BY name ASC");
  while ($row = db_fetch_object($result)) {
    $value = unserialize($row->value);
    if (isset($var_conf[$row->name]) && $var_conf[$row->name] != $value) {
      $overridden[$row->name] = $value;
    }
  }

  if (!empty($overridden)) {
    $form = array('#theme' => 'strongarm_admin_form',);
    foreach ($overridden as $name => $value) {
      $form['revert']['#tree'] = TRUE;
      $form['revert'][$name] = array('#type' => 'checkbox');
      $form['name'][$name] = array(
        '#type' => 'markup',
        '#value' => $name,
      );
      $form['current_value'][$name] = array(
        '#type' => 'markup',
        '#value' => check_plain(_strongarm_readable($overridden[$name])),
      );
      $form['default_value'][$name] = array(
        '#type' => 'markup',
        '#value' => check_plain(_strongarm_readable($var_conf[$name])),
      );
      $form['culprit'][$name] = array(
        '#type' => 'markup',
        '#value' => $culprits[$name],
      );
    }
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Revert'),
      '#submit' => array('strongarm_admin_revert_submit'),
    );
  }
  return $form;
}

/**
 * Revert form submit handler.
 */
function strongarm_admin_revert_submit(&$form, &$form_state) {
  if (!empty($form_state['values']['revert'])) {
    foreach ($form_state['values']['revert'] as $name => $revert) {
      if ($revert) {
        variable_del($name);
      }
    }
    // Re-set strongarm and variable caches
    strongarm_flush_caches();
    $var_conf = strongarm_get_conf();
    strongarm_set_conf($var_conf);
  }
}

/**
 * Recursive function that hunts down form elements that are likely to
 * be related to strongarm'd variables and locks them down.
 */
function _strongarm_lockdown(&$form, $pattern = '', $position = STRONGARM_PATTERN_PREFIX) {
  $var_conf = strongarm_get_conf();

  foreach (element_children($form) as $elem) {
    $children = element_children($form[$elem]);
    $key = $elem;

    $match = FALSE;
    if (isset($var_conf[$key])) {
      $match = TRUE;
    }
    else if (!empty($pattern)) {
      $key = ($position == STRONGARM_PATTERN_PREFIX) ? "{$pattern}_{$key}" : "{$key}_{$pattern}";
      if (isset($var_conf[$key])) {
        $match = TRUE;
      }
    }

    if ($match) {
      // If the default form value matches the strongarm value,
      // it is highly likely we have a match. Disable the field.
      if (isset($form[$elem]['#default_value']) && $var_conf[$key] == $form[$elem]['#default_value']) {
        $form[$elem]['#disabled'] = TRUE;
        $form[$elem]['#value'] = $form[$elem]['#default_value'];
      }
      if (!isset($form[$elem]['#attributes']['class'])) {
        $form[$elem]['#attributes']['class'] = "strongarm";
      }
      else {
        $form[$elem]['#attributes']['class'] .= " strongarm";
      }

      $altered = TRUE;
    }

    // If this is a tree'd element, recurse
    if (!empty($form[$elem]['#tree']) || !empty($children)) {
      $altered = _strongarm_lockdown($form[$elem], $pattern, $position) || $altered;
    }
  }
  return $altered;
}

/**
 * Display variables in a nicer way.
 */
function _strongarm_readable($var) {
  if (is_string($var) || is_bool($var) || is_numeric($var)) {
    return $var;
  }
  else if (is_array($var)) {
    $test = $detected = array();
    $test['keys'] = array_keys($var);
    $test['values'] = array_values($var);

    foreach ($test as $type => $values) {
      $numeric = TRUE;
      $sequential = 0;
      $boolean = TRUE;
      foreach ($values as $v) {
        $numeric = is_numeric($v) && $numeric;
        $sequential = is_numeric($v) && ($sequential == $v) && $sequential !== FALSE ? $sequential + 1 : FALSE;
        $boolean = $boolean && ($v === 0 || $v === 1 || $v === '1' || $v === '0' || $v === TRUE || $v === FALSE);
      }
      $detected[$type]['numeric'] = $numeric;
      $detected[$type]['sequential'] = $sequential !== FALSE;
      $detected[$type]['boolean'] = $boolean;
    }

    // List of things
    if (!empty($var) && $detected['keys']['numeric'] && $detected['keys']['sequential']) {
      return implode(', ', $var);
    }
    return '-';
  }
}

/**
 * Theme function for the strongarm admin form.
 */
function theme_strongarm_admin_form($form) {
  $output = '';
  $overridden = element_children($form['revert']);
  if (!empty($overridden)) {
    drupal_add_js('misc/tableselect.js');
    $rows = $headers = array();

    $output .= "<h3>". t('Manage overridden variables') ."</h3>";

    // Add checkboxes to the header and the rows.
    $headers[] = theme('table_select_header_cell');
    $headers[] = t('Variable');
    $headers[] = t('Current value');
    $headers[] = t('Module value');
    $headers[] = t('Module');

    foreach ($overridden as $name) {
      $row = array();
      $row[] = drupal_render($form['revert'][$name]);
      $row[] = drupal_render($form['name'][$name]);
      $row[] = drupal_render($form['current_value'][$name]);
      $row[] = drupal_render($form['default_value'][$name]);
      $row[] = drupal_render($form['culprit'][$name]);
      $rows[] = $row;
    }
    $output .= theme('table', $headers, $rows);
    $output .= drupal_render($form);
  }
  return $output;
}
