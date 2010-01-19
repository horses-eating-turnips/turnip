<?php
// $Id: path_redirect.admin.inc 900 2010-01-18 23:01:52Z jhedstrom $

/**
 * @file
 * Administrative page callbacks for the path_redirect module.
 */

/**
 * Render a list of redirects for the main admin page.
 */
function path_redirect_list_redirects() {
  $multilanguage = module_exists('locale');
  $languages = language_list();

  $header = array(
    array('data' => t('From'), 'field' => 'path', 'sort' => 'asc'),
    array('data' => t('To'), 'field' => 'redirect'),
    array('data' => t('Type'), 'field' => 'type'),
    array('data' => t('Operations'), 'colspan' => '2'),
  );
  if ($multilanguage) {
    array_splice($header, 3, 0, array(array('data' => t('Language'), 'field' => 'language')));
  }
  $rows = array();
  $limit = 50;

  $redirects = pager_query('SELECT rid, path, redirect, query, fragment, language, type FROM {path_redirect}'. tablesort_sql($header), $limit);
  while ($redirect = db_fetch_object($redirects)) {
    $redirect->redirect_url = url($redirect->redirect, array('query' => $redirect->query, 'fragment' => $redirect->fragment, 'absolute' => TRUE, 'alias' => TRUE));
    $redirect->path_url = $redirect->path;
    $redirect->path = parse_url($redirect->path);
    $row = array(
      'data' => array(
        l($redirect->path_url, $redirect->path['path'], $redirect->path),
        l($redirect->redirect_url, $redirect->redirect_url, array('external' => TRUE)),
        $redirect->type,
        l(t('Edit'), 'admin/build/path-redirect/edit/'. $redirect->rid),
        l(t('Delete'), 'admin/build/path-redirect/delete/'. $redirect->rid),
      ),
    );
    if ($multilanguage) {
      array_splice($row['data'], 3, 0, module_invoke('locale', 'language_name', $redirect->language));
    }
    $rows[] = $row;
  }

  if (empty($rows)) {
    $rows[] = array(array('data' => t('No redirects available.'), 'colspan' => $multilanguage ? 6 : 5));
  }

  $output = theme('table', $header, $rows, array('class' => 'path-redirects'));
  $output .= theme('pager', NULL, $limit);

  return $output;
}

function path_redirect_edit_form(&$form_state, $redirect = array()) {
  // Merge default values.
  $redirect += array(
    'rid' => NULL,
    'path' => isset($_GET['src']) ? urldecode($_GET['src']) : '',
    'redirect' => isset($_GET['dst']) ? urldecode($_GET['dst']) : '',
    'query' => NULL,
    'fragment' => NULL,
    'language' => isset($_GET['language']) ? urldecode($_GET['language']) : NULL,
    'type' => path_redirect_var('default_status'),
  );

  $form['rid'] = array(
    '#type' => 'value',
    '#value' => $redirect['rid'],
  );

  $form['path'] = array(
    '#type' => 'textfield',
    '#title' => t('From'),
    '#description' => t("Enter an interal Drupal path or path alias to redirect (e.g. %example1 or %example2). Fragment anchors (e.g. %anchor) are <strong>not</strong> allowed.", array('%example1' => 'node/123', '%example2' => 'taxonomy/term/123', '%anchor' => '#anchor')),
    '#size' => 42,
    '#maxlength' => 255,
    '#default_value' => $redirect['path'],
    '#required' => TRUE,
    '#field_prefix' => url('', array('absolute' => TRUE)) . (variable_get('clean_url', 0) ? '' : '?q='),
    '#autocomplete_path' => db_table_exists('watchdog') ? 'js/path_redirect/autocomplete_404' : '',
  );

  $form['redirect'] = array(
    '#type' => 'item',
    '#prefix' => '<div class="container-inline">',
    '#suffix' => '</div>',
    '#title' => t('To'),
    '#description' => '<div style="display:block">'. t('Enter an interal Drupal path, path alias, or complete external URL (like http://example.com/) to redirect to. Use %front to redirect to the front page. Enter (optional) queries after "?" and (optional) anchor after "#". Most redirects will not contain queries or fragment anchors.', array('%front' => '<front>')) .'</div>',
  );

  $form['redirect']['redirect'] = array(
    '#type' => 'textfield',
    '#size' => 30,
    '#maxlength' => 255,
    '#default_value' => $redirect['redirect'],
    //'#required' => TRUE,
  );

  $form['redirect'][] = array(
    '#value' => '?',
  );

  $form['redirect']['query'] = array(
    '#type' => 'textfield',
    '#size' => 12,
    '#maxlength' => 255,
    '#default_value' => $redirect['query'],
  );

  $form['redirect'][] = array(
    '#value' => '#',
  );

  $form['redirect']['fragment'] = array(
    '#type' => 'textfield',
    '#size' => 12,
    '#maxlength' => 50,
    '#default_value' => $redirect['fragment'],
  );

  $form[] = array(
    '#value' => "<p> </p>", // little bit of extra space
  );

  $languages = module_exists('locale') ? locale_language_list('name') : array();
  $form['language'] = array(
    '#type' => 'select',
    '#title' => t('Language'),
    '#options' => array('' => t('Language neutral')) + $languages,
    '#default_value' => $redirect['language'],
    '#description' => t('A redirect set for a specific language will always be used when requesting this page in that language, and takes precedence over redirects set for <em>All languages</em>.'),
    '#access' => $languages,
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
    '#value' => l(t('Cancel'),
    'admin/build/path-redirect'),
  );

  return $form;
}

function path_redirect_edit_form_validate($form, &$form_state) {
  path_redirect_validate_redirect($form_state['values']);
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
    t('Are you sure you want to delete the redirect from %path to %redirect?', array('%path' => $redirect['path'], '%redirect' => $redirect['redirect'])),
    isset($_GET['destination']) ? $_GET['destination'] : 'admin/build/path-redirect'
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
    '#default_value' => path_redirect_var('redirect_warning'),
  );
  $form['path_redirect_allow_bypass'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow users to bypass redirects by adding %code to the URL.', array('%code' => variable_get('clean_url', 0) ? '?redirect=no' : '&redirect=no')),
    '#default_value' => path_redirect_var('allow_bypass'),
  );
  $form['path_redirect_auto_redirect'] = array(
    '#type' => 'checkbox',
    '#title' => t('Automatically create redirects when URL aliases are changed.'),
    '#default_value' => path_redirect_var('auto_redirect'),
    '#access' => module_exists('path'),
  );
  $form['path_redirect_purge_inactive'] = array(
    '#type' => 'select',
    '#title' => t('Discard redirects that have not been accessed for'),
    '#default_value' => path_redirect_var('purge_inactive'),
    '#options' => array(0 => t('Never (do not discard)')) + drupal_map_assoc(array(604800, 1209600, 2419200, 4838400, 7257600, 9676800, 31536000), 'format_interval'),
  );
  $form['path_redirect_default_status'] = array(
    '#type' => 'select',
    '#title' => t('Default redirect status'),
    '#description' => t('You can find more information about HTTP redirect status codes at <a href="@status-codes">@status-codes</a>.', array('@status-codes' => 'http://en.wikipedia.org/wiki/List_of_HTTP_status_codes#3xx_Redirection')),
    '#default_value' => path_redirect_var('default_status'),
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
  $string = implode('/', $args);
  $matches = array();

  // Get a list of 404s, sorted by the number of times each 404 was processed.
  $paths = db_query("SELECT message, COUNT(message) AS count FROM {watchdog} WHERE type = 'page not found' AND LOWER(message) LIKE '%%%s%%' GROUP BY message ORDER BY count DESC", drupal_strtolower($string));
  while ($path = db_result($paths)) {
    // If the 404 is now a valid path or already has a redirect, discard it.
    if (!menu_get_item($path) && !path_redirect_load_by_path($path, FALSE)) {
      $matches[$path] = check_plain($path);
    }
  }

  // Limit the output to 10 results and return the JSON.
  $matches = array_slice($matches, 0, 10);
  drupal_json($matches);
}

/**
 * Form builder; an import form for redirects.
 *
 * @see path_redirect_import_form_submit()
 */
function path_redirect_import_form() {
  $form['file'] = array(
    '#type' => 'file',
    '#title' => t('Upload import file'),
    '#size' => 50,
  );
  $form['type'] = array(
    '#type' => 'radios',
    '#title' => t('File format'),
    '#options' => array(
      'auto' => t('Auto detect'),
      'csv' => t('CSV (Tab-delimited)'),
      'xml' => t('XML'),
    ),
    '#default_value' => 'auto',
    '#process' => array('expand_radios', '_path_redirect_process_import_export_options'),
  );
  $form['mode'] = array(
    '#type' => 'radios',
    '#title' => t('Mode'),
    '#description' => t('What action should be taken when there are duplicate redirects?'),
    '#options' => array(
      'overwrite' => t('Redirects in the uploaded file replace existing ones, new ones are added.'),
      'keep' => t('Existing redirects are kept, only new redirects are added.')
    ),
    '#default_value' => 'keep',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import'),
  );
  $form['#attributes']['enctype'] = 'multipart/form-data';

  return $form;
}

/**
 * Handles redirect import.
 *
 * @see path_redirect_import_form()
 * @see path_redirect_import_csv()
 * @see path_redirect_import_xml()
 */
function path_redirect_import_form_submit($form, $form_state) {
  if ($file = file_save_upload('file')) {
    $type = $form_state['values']['type'];

    if ($type == 'auto') {
      if ($file->filemime == 'text/csv' || substr($file->filename, -4) == '.csv') {
        $type = 'csv';
      }
      elseif (strpos($file->filemime, 'xml') !== FALSE || substr($file->filename, -4) == '.xml') {
        $type = 'xml';
      }
      else {
        drupal_set_message(t('Could not determine the correct file type. Please select the file format manually and check the import file.'), 'error');
        return;
      }
    }

    $function = 'path_redirect_import_'. $type;
    if ($text = @file_get_contents($file->filepath)) {
      $function($text);
    }
    else {
      drupal_set_message(t('Could not import file.'), 'error');
    }
  }
  else {
    drupal_set_message(t('Import file not found.'), 'error');
  }
}

/**
 * Imports redirects from a CSV file.
 *
 * @see path_redirect_import_form_submit()
 */
function path_redirect_import_csv($file) {
}

/**
 * Imports redirects from an XML file.
 *
 * @see path_redirect_import_form_submit()
 */
function path_redirect_import_xml($file) {
  $imports = simplexml_load_string($file);
}

/**
 * Form builder;
 */
function path_redirect_export_form() {
  if (!db_result(db_query("SELECT COUNT(*) FROM {path_redirect}"))) {
    drupal_set_message(t('No redirects available.'));
    return;
  }

  $form['type'] = array(
    '#type' => 'radios',
    '#title' => t('Export format'),
    '#options' => array(
      'csv' => t('CSV (Tab-delimited)'),
      'xml' => t('XML'),
    ),
    '#default_value' => 'csv',
    '#process' => array('expand_radios', '_path_redirect_process_import_export_options'),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Export'),
  );

  return $form;
}

/**
 * Handles redirect exporting.
 *
 * @see path_redirect_export_form()
 * @see path_redirect_export_csv()
 * @see path_redirect_export_xml()
 */
function path_redirect_export_form_submit($form, $form_state) {
  $type = $form_state['values']['type'];
  $function = 'path_redirect_export_'. $type;

  $filename = variable_get('site_name', 'Drupal') .' redirects '. format_date(time(), 'custom', 'Y m d');
  $filename = preg_replace(array('/^\W+|\W+$/', '/\W+/'), array('', '-'), drupal_strtolower($filename));
  $filename .= '.'. $type;
  drupal_set_header('Content-Disposition: attachment; filename='. $filename);

  echo $function();
  drupal_page_footer();
  exit();
}

/**
 * Exports redirects to a CSV format.
 *
 * @see path_redirect_export_form_submit()
 */
function path_redirect_export_csv() {
  drupal_set_header('Content-Type: text/csv; charset=utf-8');
  $fields = array('path', 'redirect', 'query', 'fragment', 'language', 'type', 'last_used');
  $redirects = db_query("SELECT ". implode(', ', $fields) ." FROM {path_redirect}");
  $export = implode("\t", $fields) . PHP_EOL;
  while ($redirect = db_fetch_array($redirects)) {
    $export .= implode("\t", $redirect) . PHP_EOL;
  }
  return $export;
}

/**
 * Exports redirects to a XML format.
 *
 * @see path_redirect_export_form_submit()
 */
function path_redirect_export_xml() {
  drupal_set_header('Content-Type: text/xml; charset=utf-8');
  //$export = simplexml_load_string();
  $export = new SimpleXMLElement("<?xml version=\"1.0\" encoding=\"utf-8\"?><redirects />");
  $redirects = db_query("SELECT path, redirect, query, fragment, language, type, last_used FROM {path_redirect}");
  while ($redirect = db_fetch_object($redirects)) {
    $export_item = $export->addChild('redirect');
    foreach ($redirect as $key => $value) {
      if ($value != '' && $value !== NULL) {
        $export_item->addAttribute($key, $value);
      }
    }
  }
  return $export->asXML();
}

/**
 * Disables the XML import/export options
 *
 * @todo Remove in Drupal 7.
 */
function _path_redirect_process_import_export_options($element) {
  if (!extension_loaded('simplexml')) {
    $element['xml']['#disabled'] = TRUE;
    $element['xml']['#description'] = t('This option requires PHP 5.1.');
  }
  return $element;
}
