#!/bin/bash -l

shopt -s expand_aliases
# Must set this option, else script will not expand "drush" alias.

# @todo - maybe use drupal's site_name to name the output file?

output=`pwd`/local.sql.gz

cd ../drupal
drush cache-clear all
drush watchdog-delete all
drush sql-dump | gzip > $output
