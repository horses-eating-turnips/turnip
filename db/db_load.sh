#!/bin/bash -l

shopt -s expand_aliases
# Must set this option, else script will not expand "drush" alias.

cd ../drupal

dbname=`drush sql-connect | awk '{print $NF}'`

echo "dropping database $dbname..."
drush sql-query "drop database $dbname; create database $dbname"

echo "loading from $1..."
gzip -d -c ../db/$1 | drush sql-cli

# Uncomment these two lines if CiviCRM is used
# drush sql query "UPDATE civicrm_domain SET config_backend = NULL"
# rm sites/default/files/civicrm/upload/Config.IDS.ini
