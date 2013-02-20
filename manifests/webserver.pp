exec { "apt-get update":
    command => "/usr/bin/apt-get update",
}

Package {
    require => Exec["apt-get update"],
}

package { "apache2": }
package { "apache2.2-common": }
package { "libapache2-mod-php5": }
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

service { "apache2":
    ensure => "running",
    enable => "true",
    require => Package["apache2"],
}

service { "mysql":
    ensure => "running",
    enable => "true",
    require => Package["mysql-server"],
}

file { "/etc/apache2/sites-available/default":
    notify => Service["apache2"],
    ensure => "present",
    source => "/vagrant/manifests/default",
    require => Package["apache2"],
}

exec { "mysql password":
    unless => "/usr/bin/mysql -uroot -ppassword",
    command => "/usr/bin/mysqladmin -u root password password",
    notify => Service["mysql"],
    require => Package["mysql-server"],
}

exec { "mod rewrite":
    notify => Service["apache2"],
    command => "/usr/sbin/a2enmod rewrite",
    require => Package["apache2"],
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
