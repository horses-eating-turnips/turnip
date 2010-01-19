<?php
// $Id: securepages.admin.inc 5 2009-06-10 01:11:31Z jhedstrom $

/**
 * @file
 * Provide all the administration pages
 */
 
 /**
  * Implementation of hook_settings().
  */
 function securepages_settings() {
   $form = array();

   $form['securepages_enable'] = array(
     '#type' => 'radios',
     '#title' => t('Enable Secure Pages'),
     '#default_value' => variable_get('securepages_enable', 0),
     '#options' => array(t('Disabled'), t('Enabled')),
     '#disabled' => !securepages_test(),
     '#description' => t('To start using secure pages this setting must be enabled. This setting will only be able to changed when the web server has been configured for SSL.<br />If this test has failed then go <a href="!url">here</a>', array('!url' => preg_replace(';^http://;i', 'https://', url($_GET['q'], array('absolute' => TRUE))))),
   );
   $form['securepages_switch'] = array(
     '#type' => 'checkbox',
     '#title' => t('Switch back to http pages when there are no matches'),
     '#return_value' => TRUE,
     '#default_value' => variable_get('securepages_switch', FALSE),
   );

   $form['securepages_basepath'] = array(
     '#type' => 'textfield',
     '#title' => t('Non-secure Base URL'),
     '#default_value' => variable_get('securepages_basepath', ''),
   );

   $form['securepages_basepath_ssl'] = array(
     '#type' => 'textfield',
     '#title' => t('Secure Base URL'),
     '#default_value' => variable_get('securepages_basepath_ssl', ''),
   );

   $form['securepages_secure'] = array(
     '#type' => 'radios',
     '#title' => t('Pages which will be be secure'),
     '#default_value' => variable_get('securepages_secure', 1),
     '#options' => array(t('Make secure every page except the listed pages.'), t('Make secure only the listed pages.')),
   );
   $form['securepages_pages'] = array(
     '#type' => 'textarea',
     '#title' => t('Pages'),
     '#default_value' => variable_get('securepages_pages', "node/add*\nnode/*/edit\nuser/*\nadmin*"),
     '#cols' => 40,
     '#rows' => 5,
     '#description' => t("Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are '<em>blog</em>' for the blog page and '<em>blog/*</em>' for every personal blog. '<em>&lt;front&gt;</em>' is the front page."),
   );
   $form['securepages_ignore'] = array(
     '#type' => 'textarea',
     '#title' => t('Ignore pages'),
     '#default_value' => variable_get('securepages_ignore', "*/autocomplete/*\n*/ajax/*"),
     '#cols' => 40,
     '#rows' => 5,
     '#description' => t("The pages listed here will be ignored and be either returned in http or https. Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are '<em>blog</em>' for the blog page and '<em>blog/*</em>' for every personal blog. '<em>&lt;front&gt;</em>' is the front page."),
   );
   return system_settings_form($form);
 }
 
 