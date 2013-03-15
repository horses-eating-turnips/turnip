class varnish (
  $varnish_storage_size = '12G',
  $varnish_storage = 'malloc',
  $varnish_vcl = '/etc/varnish/default.vcl',
  $varnish_conf = '/etc/default/varnish',
  ) {

  package { 'varnish': }
  
  service { "varnish":
    ensure => "running",
    enable => "true",
    require =>  File[$varnish_vcl, $varnish_conf]
  }

  file { $varnish_vcl:
    notify => Service["varnish"],
    ensure => "present",
    content => template('varnish/default.vcl.erb'),
  }

  file { $varnish_conf:
    notify => Service["varnish"],
    ensure => "present",
    content => template('varnish/varnish.erb'),
  }
}
