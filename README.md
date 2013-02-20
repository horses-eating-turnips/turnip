# Turnip

Turnip is OpenSourcery's Drupal starting kit.

[![Build Status](https://travis-ci.org/opensourcery/turnip.png?branch=7.x)](https://travis-ci.org/opensourcery/turnip)

![Turnip](https://upload.wikimedia.org/wikipedia/commons/thumb/a/a9/Turnip_J1.jpg/320px-Turnip_J1.jpg)

## Installation

1. Run `bin/make-install-profile` to instantiate an installation profile. For example
   ```
   bin/make-install-profile my_profile my_theme "Short name" "Long name"
   ```
1. Customize `my_profile/my_profile.make`
1. Run `bin/rebuild`
1. Custom modules or features should go in `my_project/modules/custom` or `my_project/modules/features`.

## Using Vagrant

For highly customized server requirements, or just to have a stable
and consistent environment to develop on, Turnip ships with a default
Vagrant configuration that will launch a Drupal site in a box.

1. Make sure [Vagrant](http://docs.vagrantup.com/v1/docs/getting-started/index.html) and [Virtualbox](https://www.virtualbox.org/) are installed.
1. Run `bin/install`
1. At this point, [http://localhost:8888](http://localhost:8888) should be serving Drupal.
1. Stop the server with `bin/stop`, and then restart with `bin/run`
1. Customize the server in `manifests/webserver.pp`. An Apache Solr example is included if that is required for search.
