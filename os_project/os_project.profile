<?php
// $Id$

/**
 * @file
 * Rename and replace all instances of 'os_project' with 'PROJECTNAME'.
 */

/**
 * Set us as the default install profile, remove defaults and OpenSourcery.
 */
function system_form_install_select_profile_form_alter(&$form, $form_state) {
  unset($form['profile']['Minimal'], $form['profile']['Standard'], $form['profile']['OpenSourcery']);
  foreach($form['profile'] as $key => $element) {
    $form['profile'][$key]['#value'] = 'os_project';
  }
}
