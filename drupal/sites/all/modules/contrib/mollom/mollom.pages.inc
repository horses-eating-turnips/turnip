<?php
// $Id: mollom.pages.inc 887 2009-09-24 15:51:14Z jhedstrom $

/**
 * @file
 * Various non-administration page callbacks for the mollom module.
 */

/**
 * AJAX callback to retrieve a CAPTCHA.
 *
 * @todo Add error handling.
 */
function mollom_captcha_js($type, $session_id) {
  $output = '';

  if ($type == 'audio') {
    $response = mollom('mollom.getAudioCaptcha', array('author_ip' => ip_address(), 'session_id' => $session_id));
    if ($response) {
      $output  = '<a href="http://mollom.com" id="mollom-captcha"><embed src="'. check_plain($response['url']) .'" autostart="true" width="120" height="30" /></a>';
      $output .= ' (<a href="#" id="mollom-image-captcha">'. t('use image CAPTCHA') .'</a>)';
    }
  }
  elseif ($type == 'image') {
    $response = mollom('mollom.getImageCaptcha', array('author_ip' => ip_address(), 'session_id' => $session_id));
    if ($response) {
      $output = '<a href="http://mollom.com" id="mollom-captcha"><img src="'. check_plain(url($response['url'])) .'" alt="Mollom CAPTCHA" /></a>';
      $output .= ' (<a href="#" id="mollom-audio-captcha">'. t('play audio CAPTCHA') .'</a>)';
    }
  }

  print $output;
  exit();
}

/**
 * Return a list of the possible feedback options for content.
 */
function _mollom_feedback_options() {
  return array(
    '#type' => 'radios',
    '#title' => t('Optionally report this to Mollom'),
    '#options' => array(
      'none' => t("Don't send feedback to Mollom"),
      'spam' => t('Report as spam or unsolicited advertising'),
      'profanity' => t('Report as obscene, violent or profane content'),
      'low-quality' => t('Report as low-quality content or writing'),
      'unwanted' => t('Report as unwanted, taunting or off-topic content'),
    ),
    '#default_value' => 'none',
    '#description' => t("Mollom is a web service that helps you moderate your site's content: see <a href=\"http://mollom.com\">http://mollom.com</a> for more information. By sending feedback to Mollom, you teach Mollom about the content you like and dislike, allowing Mollom to do a better job helping you moderate your site's content. If you want to report multiple posts at once, you can use Mollom's bulk operations on the content and comment administration pages."),
  );
}

/**
 * This function reports a comment as feedback and deletes it.
 */
function mollom_report_comment($form_state, $cid) {
  if ($comment = _comment_load($cid)) {
    $form['cid'] = array('#type' => 'value', '#value' => $cid);
    $form['feedback'] = _mollom_feedback_options();

    return confirm_form($form,
      t('Are you sure you want to delete the comment and report it?'),
      isset($_GET['destination']) ? $_GET['destination'] : 'node/'. $comment->nid,
      t('This action cannot be undone.'),
      t('Delete'), t('Cancel'));
  }
}

/**
 * This function deletes a comment and optionally sends feedback to Mollom.
 */
function mollom_report_comment_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    if ($comment = _comment_load($form_state['values']['cid'])) {
      // Load the Mollom session data:
      $data = mollom_get_data('comment-'. $comment->cid);

      // Provide feedback to Mollom if available:
      if (isset($data) && isset($data->session) && isset($form_state['values']['feedback']) && $form_state['values']['feedback'] != 'none') {
        mollom('mollom.sendFeedback', array('session_id' => $data->session, 'feedback' => $form_state['values']['feedback']));
      }

      // Delete a comment and its replies:
      module_load_include('inc', 'comment', 'comment.admin');
      _comment_delete_thread($comment);
      _comment_update_node_statistics($comment->nid);
      cache_clear_all();

      drupal_set_message(t('The comment has been deleted.'));
    }
  }
  $form_state['redirect'] = "node/$comment->nid";
}

/**
 * This function deletes a node and optionally sends feedback to Mollom.
 */
function mollom_report_node($form_state, $nid) {
  if ($node = node_load($nid)) {
    $form['nid'] = array('#type' => 'value', '#value' => $node->nid);
    $form['feedback'] = _mollom_feedback_options();

    return confirm_form($form,
      t('Are you sure you want to delete %title and report it?', array('%title' => $node->title)),
      isset($_GET['destination']) ? $_GET['destination'] : 'node/'. $node->nid,
      t('This action cannot be undone.'),
      t('Delete'), t('Cancel'));
  }
}

/**
 * This function deletes a node and optionally sends feedback to Mollom.
 */
function mollom_report_node_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    if ($node = node_load($form_state['values']['nid'])) {
      // Load the Mollom session data:
      $data = mollom_get_data('node-'. $node->nid);

      // Provide feedback to Mollom if available:
      if (isset($data) && isset($data->session) && isset($form_state['values']['feedback']) && $form_state['values']['feedback'] != 'none') {
        mollom('mollom.sendFeedback', array('session_id' => $data->session, 'feedback' => $form_state['values']['feedback']));
      }

      // Delete the node.  Calling this function will delete any comments,
      // clear the cache and print a status message.
      node_delete($node->nid);
    }
  }

  $form_state['redirect'] = '<front>';
}
