
CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Installation
 * Running tests
 * Creating features and scenarios

INTRODUCTION
------------
Doobie is the home of Drupal.org Behavior Driven Development.

It's a collection of tests to verify the functionality of Drupal.org for pre-
deployment purposes. They are written in plain English as "Features" with
"Scenarios" beneath them, the outline how a piece of functionality is supposed
to work. Those English descriptions can then generate skeleton code for real
functionality testing.

For more background on Behat, see http://docs.behat.org

INSTALLATION
------------
Doobie requires a Linux-based system.

Helpful installation instructions are included on the project page:
http://drupal.org/project/doobie

When installation is complete, copy the default.behat.yml file to behat.yml and adjust the base url as needed.

RUNNING TESTS
-------------
To run tests, change into the doobie project directory and run:

bin/behat

This will cycle through all of the available features and scenarios and output
their results.

See http://docs.behat.org/guides/6.cli.html for other, fancier ways to run tests.

FEATURES AND SCENARIOS
----------------------
Human-readable features and scenarios are available in the features/ directory.
The actual code for each can be found in the 'bootstrap' directory within.

A tutorial on how to write features, scenarios, and tests can be found at http://docs.behat.org/guides/1.gherkin.html
