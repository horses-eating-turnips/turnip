class solr::tomcat6 (
  $basedir = '/var/lib/solr',
  $user    = 'tomcat6',
  $group   = 'tomcat6',
  $solr_context_template = 'solr/solr-context.xml.erb',
  $tomcat_home = '/etc/tomcat6',
  ) {
  
  Class['Solr::Common'] -> Class['Solr::Tomcat6']

  package { "tomcat6": }

  service { "tomcat6":
    ensure => "running",
    enable => "true",
    require => Package["tomcat6"],
  }

  class { 'solr::common':
    basedir => $basedir,
    user => $user,
    group => $group,
  }

  file { "${solr::common::basedir}/solr.war":
    owner => $user,
    group => $group,
    mode => 0644,
    source => "${solr::common::basedir}/solr-src/dist/apache-solr-${solr::common::solr_version}.war",
    require => Exec['solr-source']
  }

  file { "${tomcat_home}/Catalina/localhost/solr.xml":
    owner => $user,
    group => $group,
    mode => 0644,
    content => template($solr_context_template),
    notify => Service['tomcat6'],
  }
}
