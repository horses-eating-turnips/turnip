<?php
// $Id: mollom.admin.inc 887 2009-09-24 15:51:14Z jhedstrom $

/**
 * @file
 * Administrative page callbacks for the mollom module.
 */

/**
 * Form builder; Administration settings form.
 *
 * @see system_settings_form()
 */
function mollom_admin_settings() {
  $keys = _mollom_access();

  if ($keys) {
    // Print a status message about the key:
    if (!$_POST) {
      // When a user visits the Mollom administration page, automatically
      // clear the server list.  This causes the client to fetch a fresh
      // server list from the server.
      variable_del('mollom_servers');

      // Verify the key:
      _mollom_verify_key();
    }

    $form['spam'] = array(
      '#type' => 'fieldset',
      '#title' => t('Spam protection settings'),
      '#description' =>
        '<p>'. t("Mollom can be used to block all types of spam received on your website's protected forms. Each form can be set to one of the following options:") .'</p>'.
        '<ul><li>'. t("<strong>Text analysis and CAPTCHA backup</strong>: Mollom analyzes the data submitted on the form and presents a CAPTCHA challenge if necessary. This option is strongly recommended, as it takes full advantage of the Mollom anti-spam service to categorize your posts into ham (not spam) and spam.") .'</li>'.
        '<li>'. t("<strong>CAPTCHA only</strong>: the form's data is not sent to Mollom for analysis, and a remotely-hosted CAPTCHA challenge is always presented. This option is useful when you wish to always display a CAPTCHA or want to send less data to the Mollom network. Note, however, that forms displayed with a CAPTCHA are never cached, so always displaying a CAPTCHA challenge may reduce performance.") .'</li>'.
        '<li>'. t('<strong>No protection</strong>: Mollom is not used with this form.') .'</li></ul>'.
        '<p>'. t("Data is processsed and stored as explained in our <a href=\"@mollom-privacy\">Web Service Privacy Policy</a>. It is your responsibility to provide any necessary notices and obtain the appropriate consent regarding Mollom's use of your data. For more information, see <a href=\"@mollom-works\">How Mollom Works</a> and the <a href=\"@mollom-faq\">Mollom FAQ</a>.", array('@mollom-privacy' => 'http://mollom.com/service-agreement-free-subscriptions', '@mollom-works' => 'http://mollom.com/how-mollom-works', '@mollom-faq' => 'http://mollom.com/faq')) .'</p>',
      '#collapsible' => TRUE,
    );

    $forms = _mollom_protectable_forms();
    foreach ($forms as $form_id => $details) {
      $mode = _mollom_get_mode($form_id);
      $name = 'mollom_'. $form_id;

      $options = array_slice(array(
        MOLLOM_MODE_DISABLED => t('No protection'),
        MOLLOM_MODE_CAPTCHA => t('CAPTCHA only'),
        MOLLOM_MODE_ANALYSIS => t('Text analysis and CAPTCHA backup'),
      ), 0, $details['mode'] + 1);

      $form['spam'][$name] = array(
        '#type' => 'select',
        '#title' => t('Protect @name', array('@name' => $details['name'])),
        '#options' => $options,
        '#default_value' => $mode,
      );
    }

    $form['server'] = array(
      '#type' => 'fieldset',
      '#title' => t('Server settings'),
      '#collapsible' => TRUE,
      '#collapsed' => $keys,
    );
    $form['server']['mollom_fallback'] = array(
      '#type' => 'radios',
      '#title' => t('Fallback strategy'),
      '#default_value' => variable_get('mollom_fallback', MOLLOM_FALLBACK_BLOCK), // we default to treating everything as inappropriate
      '#options' => array(
        MOLLOM_FALLBACK_BLOCK => t('Block all submissions of protected forms until the server problems are resolved'),
        MOLLOM_FALLBACK_ACCEPT => t('Leave all forms unprotected and accept all submissions'),
      ),
      '#description' => t('When the Mollom servers are down or otherwise unreachable, no text analysis is performed and no CAPTCHAs are generated. If this occurs, your Drupal site will use the configured fallback strategy, and will either accept all submissions without spam checking, or block all submissions until the server or connection problems are resolved. Subscribers to <a href="@pricing">Mollom Plus</a> receive access to <a href="@sla">Mollom\'s high-availability backend infrastructure</a>, not available to free users, reducing potential downtime.', array('@pricing' => 'http://mollom.com/pricing', '@sla' => 'http://mollom.com/standard-service-level-agreement')),
    );
  }

  $form['access-keys'] = array(
    '#type' => 'fieldset',
    '#title' => t('Mollom access keys'),
    '#description' => t('In order to use Mollom, you need both a public and private key. To obtain your keys, simply <a href="@mollom-register">create a user account on mollom.com</a>, <a href="@mollom-login">login to mollom.com</a>, and <a href="@mollom-manager-add">create a subscription</a> for your site.  Once you created a subscription, your private and public access keys will be available from the <a href="@mollom-manager">site manager on mollom.com</a>. Copy-paste them in the form below, and you are ready to go.', array('@mollom-register' => 'http://mollom.com/user/register', '@mollom-login' => 'http://mollom.com/user', '@mollom-manager-add' => 'http://mollom.com/site-manager/add', '@mollom-manager' => 'http://mollom.com/site-manager')),
    '#collapsible' => TRUE,
    '#collapsed' => $keys,
  );
  $form['access-keys']['mollom_public_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Public key'),
    '#default_value' => variable_get('mollom_public_key', ''),
    '#description' => t('The public key is used to uniquely identify you.'),
    '#required' => TRUE,
  );
  $form['access-keys']['mollom_private_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Private key'),
    '#default_value' => variable_get('mollom_private_key', ''),
    '#description' => t('The private key is used to prevent someone from hijacking your requests. Similar to a password, it should never be shared with anyone.'),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}

/**
 * This function contacts Mollom to verify the configured key pair.
 */
function _mollom_verify_key() {
  $status = mollom('mollom.verifyKey');

  if ($status === NETWORK_ERROR) {
    drupal_set_message(t('We tried to contact the Mollom servers but we encountered a network error. Please make sure that your web server can make outgoing HTTP requests.'), 'error');
  }
  elseif ($status === MOLLOM_ERROR) {
    drupal_set_message(t('We contacted the Mollom servers to verify your keys: your keys do not exist or are no longer valid. Please visit the <em>Manage sites</em> page on the Mollom website again: <a href="@mollom-user">@mollom-user</a>.', array('@mollom-user' => 'http://mollom.com/user')), 'error');
  }
  else {
    drupal_set_message(t('We contacted the Mollom servers to verify your keys: the Mollom services are operating correctly. We are now blocking spam.'));
  }
}

/**
 * Submit handler; mass-report and delete comments.
 */
function mollom_comment_admin_overview_submit($form, &$form_state) {
  // The operation has the following format: <operation>,
  // where '<operation>' can be 'unpublish' or 'delete'.
  list($id, $operation) = explode('-', $form_state['values']['operation']);

  if ($id == 'mollom') {
    foreach ($form_state['values']['comments'] as $cid => $value) {
      if ($value) {
        // First, send the proper information to the XML-RPC server:
        if ($data = mollom_get_data('comment-'. $cid)) {
          mollom('mollom.sendFeedback', array('session_id' => $data->session, 'feedback' => 'spam'));
        }

        // Second, perform the proper operation on the comments:
        if ($comment = _comment_load($cid)) {
          if ($operation == 'unpublish') {
            db_query("UPDATE {comments} SET status = %d WHERE cid = %d", COMMENT_NOT_PUBLISHED, $cid);
            _comment_update_node_statistics($comment->nid);
          }
          elseif ($operation == 'delete') {
            _comment_delete_thread($comment);
            _comment_update_node_statistics($comment->nid);
          }
        }
      }
    }

    // Clear the cache:
    cache_clear_all();

    if ($operation == 'delete') {
      drupal_set_message(t('The selected comments have been reported as inappropriate and are deleted.'));
    }
    else {
      drupal_set_message(t('The selected comments have been reported as inappropriate and are unpublished.'));
    }
  }
}

/**
 * Submit handler; mass-report and unpublish or delete nodes.
 */
function mollom_node_admin_overview_submit($form, &$form_state) {
  // The operation has the following format: <operation>,
  // where '<operation>' can be 'unpublish' or 'delete'.
  list($id, $operation) = explode('-', $form_state['values']['operation']);

  if ($id == 'mollom') {
    foreach ($form_state['values']['nodes'] as $nid => $value) {
      if ($value) {
        if ($data = mollom_get_data('node-'. $nid)) {
          mollom('mollom.sendFeedback', array('session_id' => $data->session, 'feedback' => 'spam'));
        }

        if ($node = node_load($nid)) {
          if ($operation == 'unpublish') {
            db_query("UPDATE {node} SET status = 0 WHERE nid = %d", $nid);
          }
          elseif ($operation == 'delete') {
            node_delete($nid);
          }
        }
      }
    }

    // Clear the cache:
    cache_clear_all();

    if ($operation == 'delete') {
      drupal_set_message(t('The selected posts have been reported as inappropriate and are deleted.'));
    }
    else {
      drupal_set_message(t('The selected posts have been reported as inappropriate and are unpublished.'));
    }
  }
}

/**
 * Display a reports page.
 */
function mollom_reports_page() {
  $form['statistics'] = array(
    '#type' => 'item',
    '#value' => '<embed src="http://mollom.com/statistics.swf?key='. check_plain(variable_get('mollom_public_key', '')) .'" quality="high" width="100%" height="430" name="Mollom" align="middle" play="true" loop="false" allowScriptAccess="sameDomain" type="application/x-shockwave-flash" pluginspage="http://www.adobe.com/go/getflashplayer"></embed>',
  );
  return drupal_render($form);
}
