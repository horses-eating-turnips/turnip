#!/bin/bash -l
if [ -z "$1" ]; then
  echo "Need one argument: name of gzipped SQL dump."
  exit 1
fi

# Must set this option, else script will not expand "drush" alias.
shopt -s expand_aliases

options="--root=../drupal --database=${2:-default}"
sqlconnect=`drush $options sql-connect`
if (echo "$sqlconnect" | grep "database" >/dev/null); then
  # New form (drush 4.x) returns a verbose connect command
  dbname=`echo -n $sqlconnect | sed -e 's/.*--database=\([^ ]*\) .*/\1/'`
else
  # Old form returns minimalist connect string with database name as last parameter
  dbname=`drush $options sql-connect | awk '{print $NF}'`
fi

echo "dropping database $dbname..."
drush $options sql-query "drop database $dbname; create database $dbname"

echo "loading from $1..."
if which pv >/dev/null; then
  # pv is installed; we can display a progress meter!
  uncompressed_size=`gzip -l $1 | awk 'NR==2 {print $2}'`
  gzip -d -c $1 | pv -i 0.5 -s $uncompressed_size | drush $options sql-cli
else
  gzip -d -c $1 | drush $options sql-cli
fi


# Uncomment these two lines if CiviCRM is used
# drush sql query "UPDATE civicrm_domain SET config_backend = NULL"
# rm sites/default/files/civicrm/upload/Config.IDS.ini
