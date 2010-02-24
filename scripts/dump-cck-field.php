#!/usr/bin/env php
<?php
$argv = $GLOBALS['argv'];
if ($GLOBALS['argc'] < 3) {
  echo "Usage:\n";
  echo $argv[0] ." <field_name> <content_type_name>\n";
  exit(1);
}

chdir('../drupal');
require_once './includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);

module_load_include('inc', 'content', 'includes/content.crud');
module_load_include('inc', 'content', 'includes/content.admin');

var_export(content_fields($argv[1], $argv[2]));
echo ";\n";
