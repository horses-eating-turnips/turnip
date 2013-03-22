class drupal (
  $db_user = 'drupal',
  $db_name = 'drupal',
  $db_pass = '',
  $db_host = 'localhost',
  $db_driver = 'mysql',
  $db_port = '',
  $settings_path = '/vagrant/shared'
  ) {

  file { "${settings_path}/settings.local.php":
    content => template("drupal/drupal.settings.php.erb")
  }
}
