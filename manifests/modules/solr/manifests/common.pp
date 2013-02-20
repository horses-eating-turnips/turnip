class solr::common (
  $basedir      = '/var/lib/solr',
  $user         = 'root',
  $group        = 'root',
  $solr_version = '3.6.2',
  $solrconfig   = 'solr/solrconfig.xml.erb'
  ) {

  # Solr tarball.
  $solr_tarball = "http://apache.osuosl.org/lucene/solr/${solr_version}/apache-solr-${solr_version}.tgz"

  # Config directory.
  $solr_confdir = "$basedir/conf"

  # Data directory.
  $solr_datadir = "$basedir/data"
  
  file { $basedir:
    ensure => directory,
    owner => $user,
    group => $group,
    mode => 0755,
  }

  file { $solr_datadir:
    ensure => directory,
    owner => $user,
    group => $group,
    mode => 0755,
  }

  file { "${basedir}/solr-src":
    ensure => directory,
    owner => $user,
    group => $group,
    mode => 0755
  }

  package { "curl": }

  exec { 'solr-source':
    command => "curl -o ${basedir}/solr.tgz ${solr_tarball} && tar --strip-components=1 -xzf ${basedir}/solr.tgz -C ${basedir}/solr-src",
    require => [ File[$basedir], Package['curl'] ],
    refreshonly => true,
    path => '/usr/bin:/bin:/usr/sbin:/sbin'
  }

  file { $solr_confdir:
    ensure => directory,
    owner => $user,
    group => $group,
    mode => 0755,
    source => "${solr::common::basedir}/solr-src/example/solr/conf",
    recurse => true,
  }

  file { "$basedir/solr.xml":
    owner => $user,
    group => $group,
    mode => 0644,
    content => template('solr/solr.xml.erb'),
    require => File[$basedir],
  }

  # Obtain Solr conf from search api solr.
  file { "${solr_confdir}/schema.xml":
    owner => $user,
    group => $group,
    mode => 0644,
    content => template('solr/schema.xml.erb'),
    require => File[$solr_confdir],
  }

  file { "${solr_confdir}/solrconfig.xml":
    owner => $user,
    group => $group,
    mode => 0644,
    content => template('solr/solrconfig.xml.erb'),
    require => File[$solr_confdir],
  }

  file { "${solr_confdir}/solrcore.properties":
    owner => $user,
    group => $group,
    mode => 0644,
    content => template('solr/solrcore.properties.erb'),
    require => File[$solr_confdir],
  }

  file { "${solr_confdir}/protwords.txt":
    owner => $user,
    group => $group,
    mode => 0644,
    content => template('solr/protwords.txt.erb'),
    require => File[$solr_confdir],
  }

  file { "${solr_confdir}/solrconfig_extra.xml":
    owner => $user,
    group => $group,
    mode => 0644,
    content => template('solr/solrconfig_extra.xml.erb'),
    require => File[$solr_confdir],
  }

  file { "${solr_confdir}/schema_extra_fields.xml":
    owner => $user,
    group => $group,
    mode => 0644,
    content => template('solr/schema_extra_fields.xml.erb'),
    require => File[$solr_confdir],
  }

  file { "${solr_confdir}/schema_extra_types.xml":
    owner => $user,
    group => $group,
    mode => 0644,
    content => template('solr/schema_extra_types.xml.erb'),
    require => File[$solr_confdir],
  }
}
