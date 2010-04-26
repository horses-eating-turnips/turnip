#!/bin/bash -l

shopt -s expand_aliases
# Must set this option, else script will not expand "drush" alias.

if [ -z "$1" ]; then
  # get drupal's site name, then make lowercase and change spaces to dashes
  output="`drush --root=../drupal php-eval "print variable_get('site_name', 'local')"`.sql.gz"
  output=`echo "$output" | sed -e 's/.*/\L&/' | sed -e 's/ /-/'`
else
  if [[ "$1" == "--release" ]]; then
    output="release-`date +%Y_%m_%d__%H_%M_%S`.sql.gz"
  else
    output="$1"
  fi
fi

drush --root=../drupal cc all
drush --root=../drupal --config=drushrc.php sql-dump --structure-tables-key=opensourcery | gzip > $output
