
CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Installation
 * Running tests
 * Creating features and scenarios

INTRODUCTION
------------

For more background on Behat, see http://docs.behat.org

INSTALLATION
------------

1. You'll need [Composer](http://getcomposer.org).
1. From within this directory, run `composer install`
1. Copy `behat.local.yml.sample` to `behat.local.yml` and edit as needed
1. Configure `behat.yml` as needed

RUNNING TESTS
-------------

Run `bin/behat` to be sure your local setup is properly wired up.

To run the tests locally in the same way they are run in the TEST environment,
use the following command from within the `bdd` directory:

`$ bin/behat --format=progress --tags=~wip`

During development it is often handy to run a single feature test. For that, use

`$ bin/behat --format=progress --tags=~wip features/my.feature`

The behat doc page for the [behat command]
(http://docs.behat.org/guides/6.cli.html) is also quite useful.

Setting up tests on test server
-------------------------------

1. Copy `behat.local.yml.sample` to `testing.behat.yml` and edit accordingly.
