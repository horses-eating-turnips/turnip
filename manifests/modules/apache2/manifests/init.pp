class apache2 (
  $vhost_dir = '/vagrant/drupal'
  ) {

  package { "apache2": }
  package { "apache2.2-common": }
  package { "libapache2-mod-php5": }

  service { "apache2":
    ensure => "running",
    enable => "true",
    require => Package["apache2"],
  }

  file { "/etc/apache2/sites-available/default":
    notify => Service["apache2"],
    ensure => "present",
    content => template("apache2/vhost.default.erb"),
    require => Package["apache2"],
  }

  exec { "mod rewrite":
    notify => Service["apache2"],
    command => "/usr/sbin/a2enmod rewrite",
    require => Package["apache2"],
  }
}
