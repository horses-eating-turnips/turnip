#!/usr/bin/env php
<?php
// $Id$

/**
 * @file
 * Rescue script that rebuilds the code registry in the event of Drupal not
 * being able to do a full bootstrap due to a corrupt/lost code registry.
 * One cause of a bad registry is modules being moved to a new location.
 *
 * Run from the root directory of the Drupal installation.
 */

/**
 * Root directory of Drupal installation.
 */
define('DRUPAL_ROOT', getcwd());

$_SERVER['HTTP_HOST']       = 'default';
$_SERVER['PHP_SELF']        = '/index.php';
$_SERVER['REMOTE_ADDR']     = '127.0.0.1';
$_SERVER['SERVER_SOFTWARE'] = NULL;
$_SERVER['REQUEST_METHOD']  = 'GET';
$_SERVER['QUERY_STRING']    = '';
$_SERVER['PHP_SELF']        = $_SERVER['REQUEST_URI'] = '/';
$_SERVER['HTTP_USER_AGENT'] = 'console';

require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
require_once DRUPAL_ROOT . '/includes/common.inc';
require_once DRUPAL_ROOT . '/modules/system/system.module';
drupal_bootstrap(DRUPAL_BOOTSTRAP_SESSION);

registry_rebuild();
