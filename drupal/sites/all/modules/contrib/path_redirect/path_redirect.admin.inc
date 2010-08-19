<?php
// $Id: path_redirect.admin.inc,v 1.1.2.84 2010/08/06 14:27:23 davereid Exp $

/**
 * @file
 * Administrative page callbacks for the path_redirect module.
 */

function path_redirect_list_redirects($query = array(), $conditions = array(), $tableselect = FALSE) {
  // Initialize the query array.
  $query += array(
    'conditions' => array(),
    'args' => array(),
    'limit' => 0,
  );

  // Check if this will be a tableselect element.
  $tableselect &= user_access('administer redirects') && module_exists('elements');

  // Set up the header.
  $header = array(
    'source' => array('data' => t('From'), 'field' => 'source', 'sort' => 'asc'),
    'redirect' => array('data' => t('To'), 'field' => 'redirect'),
    'type' => array('data' => t('Type'), 'field' => 'type'),
    'language' => array('data' => t('Language'), 'field' => 'language'),
    'last_used' => array('data' => t('Last used'), 'field' => 'last_used'),
    'operations' => array('data' => t('Operations')),
  );

  // Do not include the language column if locale is disabled.
  if (!module_exists('locale')) {
    unset($header['language']);
  }

  // Remove any columns that are present in conditions.
  _path_redirect_build_conditions($query, NULL, $conditions);
  foreach ($conditions as $field => $value) {
    unset($header[$field]);
  }

  // Build the SQL query.
  $sql = 'SELECT * FROM {path_redirect}';
  if ($query['conditions']) {
    $sql .= ' WHERE (' . implode(') AND (', $query['conditions']). ')';
  }
  $sql .= tablesort_sql($header);
  if ($query['limit']) {
    $query = pager_query($sql, $query['limit'], 0, NULL, $query['args']);
  }
  else {
    $query = db_query($sql, $query['args']);
  }

  // Load the redirects. We cannot use path_redirect_load_multiple() since
  // we want to preserve the sorting order.
  $redirects = array();
  while ($redirect = db_fetch_array($query)) {
    $redirects[$redirect['rid']] = $redirect;
  }
  $redirects = array_map('path_redirect_post_load_redirect', $redirects);

  $destination = drupal_get_destination();
  $rows = array();
  $weight = 0;
  foreach ($redirects as $rid => $redirect) {
    $row = array();
    if (isset($header['source'])) {
      $source_url = path_redirect_build_url($redirect['source'], $redirect['source_query']);
      $row['source'] = l($source_url, $redirect['source'], array('query' => $redirect['source_query'], 'alias' => TRUE));
    }
    if (isset($header['redirect'])) {
      $redirect_url = path_redirect_build_url($redirect['redirect'], $redirect['query'], $redirect['fragment'], TRUE);
      $row['redirect'] = l($redirect_url, $redirect['redirect'], array('query' => $redirect['query'], 'fragment' => $redirect['fragment']));
    }
    if (isset($header['type'])) {
      $row['type'] = $redirect['type'];
    }
    if (isset($header['language'])) {
      $row['language'] = module_invoke('locale', 'language_name', $redirect['language']);
    }
    if (isset($header['last_used'])) {
      $row['last_used'] = format_date($redirect['last_used'], 'short');
    }
    if (isset($header['operations'])) {
      $operations = array();
      $operations['edit'] = array(
        'title' => t('Edit'),
        'href' => 'admin/build/path-redirect/edit/' . $rid,
        'query' => $destination,
      );
      $operations['delete'] = array(
        'title' => t('Delete'),
        'href' => 'admin/build/path-redirect/delete/' . $rid,
        'query' => $destination,
      );
      $row['operations'] = theme('links', $operations, array('class' => 'links inline nowrap'));
    }
    $rows[(string) $rid] = $row;
  }

  if ($tableselect) {
    return array(
      '#type' => 'tableselect',
      '#header' => $header,
      '#options' => $rows,
      '#empty' => t('No URL redirects available.'),
    );
  }
  else {
    if (empty($rows)) {
      $rows[] = array(array(
        'data' => t('No URL redirects available.'),
        'colspan' => count($header),
        'class' => 'empty',
      ));
    }
    return array(
      '#type' => 'markup',
      '#value' => theme('table', $header, $rows),
    );
  }
}

/**
 * Render a list of redirects for the main admin page.
 */
function path_redirect_admin_redirects(&$form_state) {
  if (isset($form_state['values']['operation']) && empty($form_state['values']['confirm'])) {
    return path_redirect_admin_redirects_update_confirm($form_state, $form_state['values']['operation'], array_filter($form_state['values']['rids']));
  }

  // Get filter key.
  $keys = func_get_args();
  array_shift($keys); // Offset the $form_state parameter.
  $keys = implode('/', $keys);

  // Add the local actions and filter form.
  $form['actions'] = array(
    '#type' => 'markup',
    '#value' => path_redirect_local_actions(),
  );
  $form['filter'] = path_redirect_filter_form($keys);

  // Build the 'Update options' form.
  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Update options'),
    '#prefix' => '<div class="container-inline">',
    '#suffix' => '</div>',
    '#access' => user_access('administer redirects') && module_exists('elements'),
  );
  $options = array();
  foreach (module_invoke_all('path_redirect_operations') as $key => $operation) {
    $options[$key] = $operation['action'];
  }
  $form['options']['operation'] = array(
    '#type' => 'select',
    '#options' => $options,
    '#default_value' => 'delete',
  );
  $form['options']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
    '#validate' => array('path_redirect_admin_redirects_update_validate'),
    '#submit' => array('path_redirect_admin_redirects_update_submit'),
  );

  // Apply the filter conditions.
  $query = array('conditions' => array(), 'args' => array(), 'limit' => 50);
  path_redirect_filter_query($query, $keys);

  $form['rids'] = path_redirect_list_redirects($query, array(), TRUE);
  $form['pager'] = array(
    '#type' => 'markup',
    '#value' => theme('pager', NULL, 50, 0),
  );
  return $form;
}

function path_redirect_filter_query(&$query, $keys = '') {
  if ($keys) {
    // Replace wildcards with MySQL/PostgreSQL wildcards.
    $wildcard = preg_replace('!\*+!', '%', $keys);
    $query['conditions'][] = "(source LIKE '%%%s%%' OR redirect LIKE '%%%s%%' OR query LIKE '%%%s%%' OR fragment LIKE '%%%s%%')";
    $query['args'] = array_merge($query['args'], array($wildcard, $wildcard, $wildcard, $wildcard));
  }
}

/**
 * Return a form to filter URL redirects.
 *
 * @ingroup forms
 * @see path_redirect_filter_form_submit()
 */
function path_redirect_filter_form($keys = '') {
  $form['#attributes'] = array('class' => 'search-form');
  $form['basic'] = array(
    '#type' => 'fieldset',
    '#title' => t('Filter redirects'),
  );
  $form['basic']['inline'] = array(
    '#prefix' => '<div class="container-inline">',
    '#suffix' => '</div>',
  );
  $form['basic']['inline']['filter'] = array(
    '#type' => 'textfield',
    '#title' => '',
    '#default_value' => $keys,
    '#maxlength' => 128,
    '#size' => 25,
  );
  $form['basic']['inline']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Filter'),
    '#submit' => array('path_redirect_filter_form_submit'),
  );
  if ($keys) {
    $form['basic']['inline']['reset'] = array(
      '#type' => 'submit',
      '#value' => t('Reset'),
      '#submit' => array('path_redirect_filter_form_reset'),
    );
  }
  return $form;
}

/**
 * Process filter form submission when the Filter button is pressed.
 */
function path_redirect_filter_form_submit($form, &$form_state) {
  $form_state['redirect'] = 'admin/build/path-redirect/list/'. trim($form_state['values']['filter']);
}

/**
 * Process filter form submission when the Reset button is pressed.
 */
function path_redirect_filter_form_reset($form, &$form_state) {
  $form_state['redirect'] = 'admin/build/path-redirect';
}

/**
 * Validate node_admin_nodes form submissions.
 *
 * Check if any nodes have been selected to perform the chosen
 * 'Update option' on.
 */
function path_redirect_admin_redirects_update_validate($form, &$form_state) {
  // Error if there are no items to select.
  if (!is_array($form_state['values']['rids']) || !count(array_filter($form_state['values']['rids']))) {
    form_set_error('', t('No redirects selected.'));
  }
}

/**
 * Process path_redirect_admin_redirects form submissions.
 *
 * Execute the chosen 'Update option' on the selected redirects.
 */
function path_redirect_admin_redirects_update_submit($form, &$form_state) {
  $operations = module_invoke_all('path_redirect_operations');
  $operation = $operations[$form_state['values']['operation']];

  // Filter out unchecked redirects
  $rids = array_filter($form_state['values']['rids']);

  if (!empty($operation['confirm']) && empty($form_state['values']['confirm'])) {
    // We need to rebuild the form to go to a second step. For example, to
    // show the confirmation form for the deletion of redirects.
    $form_state['rebuild'] = TRUE;
  }
  else {
    $function = $operation['callback'];

    // Add in callback arguments if present.
    if (isset($operation['callback arguments'])) {
      $args = array_merge(array($rids), $operation['callback arguments']);
    }
    else {
      $args = array($rids);
    }
    call_user_func_array($function, $args);
    path_redirect_clear_cache();

    $count = count($form_state['values']['rids']);
    watchdog('path_redirect', '@action @count redirects.', array('@action' => $operation['action_past'], '@count' => $count));
    drupal_set_message(format_plural(count($rids), '@action @count redirect.', '@action @count redirects.', array('@action' => $operation['action_past'], '@count' => $count)));
    //$form_state['redirect'] = 'admin/config/search/path-redirect';
  }
}

function path_redirect_admin_redirects_update_confirm(&$form_state, $operation, $rids) {
  $operations = module_invoke_all('path_redirect_operations');
  $operation = $operations[$form_state['values']['operation']];

  $form['rids'] = array('#prefix' => '<ul>', '#suffix' => '</ul>', '#tree' => TRUE);
  $redirects = path_redirect_load_multiple($rids);
  foreach ($rids as $rid) {
    $redirect = $redirects[$rid];
    $form['rids'][$rid] = array(
      '#type' => 'hidden',
      '#value' => $rid,
      '#prefix' => '<li>',
      '#suffix' => path_redirect_build_url($redirect['source'], $redirect['source_query']) . "</li>\n",
    );
  }
  $form['operation'] = array('#type' => 'hidden', '#value' => $form_state['values']['operation']);
  $form['#submit'][] = 'path_redirect_admin_redirects_update_submit';
  $confirm_question = format_plural(count($rids), 'Are you sure you want to @action this redirect?', 'Are you sure you want to @action these redirects?', array('@action' => drupal_strtolower($operation['action'])));

  return confirm_form(
    $form,
    $confirm_question,
    'admin/config/search/path-redirect', // @todo This does not redirect back to filtered page.
    t('This action cannot be undone.'),
    $operation['action'],
    t('Cancel')
  );
}

function path_redirect_edit_form(&$form_state, $redirect = array()) {
  // Merge default values.
  $redirect += array(
    'rid' => NULL,
    'source' => isset($_GET['source']) ? urldecode($_GET['source']) : '',
    'source_query' => isset($_GET['source_query']) ? path_redirect_get_query_array($_GET['source_query']) : array(),
    'redirect' => isset($_GET['redirect']) ? urldecode($_GET['redirect']) : '',
    'query' => array(),
    'fragment' => '',
    'language' => isset($_GET['language']) ? urldecode($_GET['language']) : '',
    'type' => variable_get('path_redirect_default_status', 301),
  );

  $form['rid'] = array(
    '#type' => 'value',
    '#value' => $redirect['rid'],
  );

  $form['source'] = array(
    '#type' => 'textfield',
    '#title' => t('From'),
    '#description' => t("Enter an internal Drupal path or path alias to redirect (e.g. %example1 or %example2). Fragment anchors (e.g. %anchor) are <strong>not</strong> allowed.", array('%example1' => 'node/123', '%example2' => 'taxonomy/term/123', '%anchor' => '#anchor')),
    '#size' => 42,
    '#maxlength' => 255,
    '#default_value' => path_redirect_build_url($redirect['source'], $redirect['source_query']),
    '#required' => TRUE,
    '#field_prefix' => url('', array('absolute' => TRUE)) . (variable_get('clean_url', 0) ? '' : '?q='),
    '#autocomplete_path' => db_table_exists('watchdog') ? 'js/path_redirect/autocomplete_404' : '',
    '#element_validate' => array('path_redirect_validate_source_field'),
  );
  $form['redirect'] = array(
    '#type' => 'textfield',
    '#title' => t('To'),
    '#maxlength' => 560,
    '#default_value' => path_redirect_build_url($redirect['redirect'], $redirect['query'], $redirect['fragment'], TRUE),
    '#required' => TRUE,
    '#description' => t('Enter an internal Drupal path, path alias, or complete external URL (like http://example.com/) to redirect to. Use %front to redirect to the front page.', array('%front' => '<front>')),
    '#element_validate' => array('path_redirect_validate_redirect_field'),
  );
  // This will be a hidden value unless locale module is enabled.
  $form['language'] = array(
    '#type' => 'value',
    '#value' => $redirect['language'],
    '#process' => array(),
  );

  $form['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['advanced']['type'] = array(
    '#type' => 'select',
    '#title' => t('Redirect status'),
    '#description' => t('You can find more information about HTTP redirect status codes at <a href="@status-codes">@status-codes</a>.', array('@status-codes' => 'http://en.wikipedia.org/wiki/List_of_HTTP_status_codes#3xx_Redirection')),
    '#default_value' => $redirect['type'],
    '#options' => path_redirect_status_code_options(),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  $form['cancel'] = array(
    '#value' => l(t('Cancel'), isset($_REQUEST['destination']) ? $_REQUEST['destination'] : 'admin/build/path-redirect'),
  );

  return $form;
}

/**
 * Implement hook_form_FORM_ID_alter().
 */
function locale_form_path_redirect_edit_form_alter(&$form, &$form_state) {
  $form['language'] = array(
    '#type' => 'select',
    '#title' => t('Language'),
    '#options' => array('' => t('All languages')) + locale_language_list('name'),
    '#default_value' => $form['language']['#value'],
    '#weight' => -10,
    '#description' => t('A redirect set for a specific language will always be used when requesting this page in that language, and takes precedence over redirects set for <em>All languages</em>.'),
  );
}

/**
 * Validate a redirect's source path (from) field.
 */
function path_redirect_validate_source_field($element, &$form_state) {
  // Check that the path contains no URL fragment.
  if (strpos($element['#value'], '#') !== FALSE) {
    form_error($element, t('The source path cannot contain an URL fragment anchor.'));
  }

  //if (!valid_url($element['#value'])) {
  //  //Make sure "from" has the form of a local Drupal path
  //  form_serror($element, t('The source path does not appear valid. This must be a local Drupal path.'));
  //}

  // @todo Split into source and source_query here.

  // A redirect's 'from' cannot match any values from url_alias, it will cause an infinite loop.
  if ($pid = db_result(db_query("SELECT pid FROM {url_alias} WHERE dst = '%s'", $element['#value']))) {
    form_error($element, t('You cannot add an existing alias as a redirect as it will not work. You must <a href="@alias-delete">delete the alias</a> first.', array('@alias-delete' => url('admin/build/path/delete/' . $pid, array('query' => drupal_get_destination())))));
  }

  // Cannot create redirects for valid paths.
  $menu_item = menu_get_item($element['#value']);
  if ($menu_item && $menu_item['page_callback'] != 'path_redirect_goto' && $element['#value'] == $menu_item['path']) {
    form_error($element, t('The source path %path is a currently valid path. You cannot override existing paths. You can however, create URL aliases for them.', array('%path' => $element['#value'])));
  }

  return $element;
}

/**
 * Validate a redirect's redirect path (to) field.
 */
function path_redirect_validate_redirect_field($element, &$form_state) {
  // Split this field into path, query, and fragment.
  $parsed = parse_url($element['#value']) + array('query' => '', 'fragment' => '', 'path' => '');
  $form_state['values']['query'] = $parsed['query'];
  $form_state['values']['fragment'] = $parsed['fragment'];
  $form_state['values']['redirect'] = (isset($parsed['scheme']) ? $parsed['scheme'] . '://'. $parsed['host'] : '') . $parsed['path'];
  return $element;
}

function path_redirect_edit_form_validate($form, &$form_state) {
  $redirect = &$form_state['values'];

  if ($existing = path_redirect_load_by_source($redirect['source'], $redirect['language'])) {
    if ($redirect['rid'] != $existing['rid']) {
      // The "from" path should not conflict with another redirect
      form_set_error('source', t('The source path %source is already being redirected. Do you want to <a href="@edit-page">edit the existing redirect</a>?', array('%source' => $redirect['source'], '@edit-page' => url('admin/build/path-redirect/edit/'. $existing['rid']))));
    }
  }

  if (!valid_url($redirect['redirect']) && !valid_url($redirect['redirect'], TRUE) && $redirect['redirect'] != '<front>') {
    //form_set_error('redirect', t('The redirect <strong>to</strong> path does not appear valid.'));
  }

  // check that there there are no redirect loops
  if (url($redirect['source']) == url($redirect['redirect'])) {
    form_set_error('redirect', t('You are attempting to redirect the page to itself. This will result in an infinite loop.'));
  }
}

function path_redirect_edit_form_submit($form, &$form_state) {
  path_redirect_save($form_state['values']);
  drupal_set_message(t('The redirect has been saved.'));
  $form_state['redirect'] = 'admin/build/path-redirect';
}

function path_redirect_delete_form($form_state, $redirect) {
  $form['redirect'] = array(
    '#type' => 'value',
    '#value' => $redirect,
  );

  return confirm_form(
    $form,
    t('Are you sure you want to delete the redirect from %source to %redirect?', array('%source' => $redirect['source'], '%redirect' => $redirect['redirect'])),
    isset($_REQUEST['destination']) ? $_REQUEST['destination'] : 'admin/build/path-redirect'
  );
}

function path_redirect_delete_form_submit($form, &$form_state) {
  path_redirect_delete($form_state['values']['redirect']['rid']);
  drupal_set_message(t('The redirect has been deleted.'));
  $form_state['redirect'] = 'admin/build/path-redirect';
}

/**
 * Form builder; administrative settings for the module.
 *
 * @see system_settings_form()
 */
function path_redirect_settings_form() {
  $form['path_redirect_redirect_warning'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display a warning message to users when they are redirected.'),
    '#default_value' => variable_get('path_redirect_redirect_warning', 0),
  );
  $form['path_redirect_allow_bypass'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow users to bypass redirects by adding %code to the URL.', array('%code' => variable_get('clean_url', 0) ? '?redirect=no' : '&redirect=no')),
    '#default_value' => variable_get('path_redirect_allow_bypass', 0),
  );
  $form['path_redirect_auto_redirect'] = array(
    '#type' => 'checkbox',
    '#title' => t('Automatically create redirects when URL aliases are changed.'),
    '#default_value' => variable_get('path_redirect_auto_redirect', 1),
    '#access' => module_exists('path'),
  );
  $form['path_redirect_purge_inactive'] = array(
    '#type' => 'select',
    '#title' => t('Discard redirects that have not been accessed for'),
    '#default_value' => variable_get('path_redirect_purge_inactive', 0),
    '#options' => array(0 => t('Never (do not discard)')) + drupal_map_assoc(array(604800, 1209600, 2419200, 4838400, 7257600, 9676800, 31536000), 'format_interval'),
  );
  $form['path_redirect_default_status'] = array(
    '#type' => 'select',
    '#title' => t('Default redirect status'),
    '#description' => t('You can find more information about HTTP redirect status codes at <a href="@status-codes">@status-codes</a>.', array('@status-codes' => 'http://en.wikipedia.org/wiki/List_of_HTTP_status_codes#3xx_Redirection')),
    '#default_value' => variable_get('path_redirect_default_status', 301),
    '#options' => path_redirect_status_code_options(),
  );

  return system_settings_form($form);
}

function path_redirect_status_code_options() {
  return array(
    300 => t('300 Multiple Choices'),
    301 => t('301 Moved Permanently'),
    302 => t('302 Found'),
    303 => t('303 See Other'),
    304 => t('304 Not Modified'),
    305 => t('305 Use Proxy'),
    307 => t('307 Temporary Redirect'),
  );
}

/**
 * Autocompletion callback for the add/edit redirect form. Returns a list of
 * current 404s on the site.
 */
function path_redirect_js_autocomplete_404() {
  $args = func_get_args();
  $string = drupal_strtolower(implode('/', $args));
  $matches = array();

  // Get a list of 404s, sorted by the number of times each 404 was processed.
  $paths = db_query("SELECT message, COUNT(message) AS count FROM {watchdog} WHERE type = 'page not found' AND LOWER(message) LIKE '%%%s%%' GROUP BY message ORDER BY count DESC", drupal_strtolower($string));
  while ($path = db_result($paths)) {
    // If the 404 is now a valid path or already has a redirect, discard it.
    if (!menu_get_item($path) && !path_redirect_load_by_source($path)) {
      $matches[$path] = check_plain($path);
    }
  }

  // Limit the output to 10 results and return the JSON.
  $matches = array_slice($matches, 0, 10);
  drupal_json($matches);
}
