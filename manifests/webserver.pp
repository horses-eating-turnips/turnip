exec { "apt-get update":
    command => "/usr/bin/apt-get update",
}

Package {
    require => Exec["apt-get update"],
}

package { "php5": }
package { "php5-cli": }
package { "php-apc": }
package { "php5-mysql": }
package { "php5-gd": }
package { "php-pear": }
package { "mysql-server": }
# Required for drush make
package { "zip": }
package { "git": }

# Solr and Tomcat. Un-comment to use:
#class { 'solr::tomcat6': }

# Varnish. Un-comment to use:
#class { 'varnish':
#  varnish_storage_size => '1G',
#  varnish_storage => 'malloc'
#}

class { "apache2":
  vhost_dir => '/vagrant/drupal'
}

class { "drupal":
  db_user => 'drupal',
  db_name => 'drupal'
}

service { "mysql":
    ensure => "running",
    enable => "true",
    require => Package["mysql-server"],
}

exec { "mysql password":
    unless => "/usr/bin/mysql -uroot -ppassword",
    command => "/usr/bin/mysqladmin -u root password password",
    notify => Service["mysql"],
    require => Package["mysql-server"],
}

exec { "create-drupal-db":
    unless => "/usr/bin/mysql -udrupal drupal",
    command => "/usr/bin/mysql -uroot -ppassword -e \"create database drupal; grant all on drupal.* to drupal@localhost;\"",
    require => Exec["mysql password"],
}

exec { "install-drush":
    unless => "/usr/bin/which drush",
    command => "/usr/bin/pear channel-discover pear.drush.org; /usr/bin/pear upgrade-all; /usr/bin/pear install drush/drush; /usr/bin/drush -h",
    require => Package["php-pear"],
}
