# Turnip

Turnip is OpenSourcery's Drupal starting kit. Using a Drush Make
workflow, only custom modules, features and themes are committed to
the repository, which allows for teams to quickly get up to speed and
collaborate on the important parts of the project at hand. It includes
a starting framework for using Behat for behavior driven
development. Each site is built as an installation profile.

[![Build Status](https://travis-ci.org/opensourcery/turnip.png?branch=7.x)](https://travis-ci.org/opensourcery/turnip)

![Turnip](https://raw.github.com/opensourcery/turnip/7.x/turnip.png)

## Installation

1. Either copy all files into a new repository or clone this
   repository, keeping an upstream origin named `turnip`:

    ```bash
    git clone -o turnip git@github.com:opensourcery/turnip.git foo_project
    cd foo_project
    git checkout -b master
    ```

1. Initialize git (if files were copied), andmar add a remote:
   ```bash
   git remote add origin git@github:foo/bar.git
   ```
1. Run `bin/make-install-profile` to instantiate an installation profile. For example
   ```bash
   bin/make-install-profile my_profile my_theme "Short name" "Long name"
   ```
1. Customize `my_profile/my_profile.make`
1. Run `bin/rebuild`
1. Custom modules or features should go in `my_project/modules/custom`
   or `my_project/modules/features`.

## Drush Make

There are several bundled make files:

* `os_project.make` - This gets renamed to the installation profile's machine name
* `base.make` - common modules and libraries
* `images.make` - Media module and other image-related modules
* `panels.make` - Panels modules related dependencies

If using dev versions of modules, specific commit hashes are
preferable in the make files, rather than the more general dev branch.

## Installation profile

By building the site out as an installation profile, funcitonality can
easily be tracked in commit logs.

The [Profiler](http://drupal.org/project/profiler) library is used for
creating placeholder nodes, users and taxonomy terms, as well as
setting variables that don't make sense to commit to feature modules.

## Using Vagrant

For highly customized server requirements, or just to have a stable
and consistent environment to develop on, Turnip ships with a default
Vagrant configuration that will launch a Drupal site in a box.

1. Make sure [Vagrant](http://docs.vagrantup.com/v1/docs/getting-started/index.html) and [Virtualbox](https://www.virtualbox.org/) are installed.
1. Run `bin/install`
1. At this point, [http://localhost:8888](http://localhost:8888) should be serving Drupal.
1. Stop the server with `bin/stop`, and then restart with `bin/run`
1. Customize the server in `manifests/webserver.pp`. An Apache Solr example is included if that is required for search.
