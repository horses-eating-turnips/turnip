#!/bin/bash
#
# @@ Replace os_project with the actual project name, then remove this line @@
#
# Rebuild os_project in the drupal directory.
#
# To use this command you must have `drush make`, `cvs` and `git` installed.
#

PROFILE="os_project"

# Generate a complete Drupal build.
echo "Building PROJECT..."

# D7 has odd permissions on sites/default folder
chmod 777 drupal/sites/default
# remove old directories
rm -rf drupal
rm -rf $PROFILE/modules/contrib
rm -rf $PROFILE/modules/stock
rm -rf $PROFILE/themes/stock
rm -rf $PROFILE/libraries

# Build the drupal directory from the make file.
drush make $1 --yes --contrib-destination=profiles/$PROFILE $PROFILE/$PROFILE.make drupal

# Link settings.php and files into sites/default
cd drupal/sites/default || { echo "Aborting $0"; exit 1; }
ln -s ../../../shared/settings.php settings.php
ln -s ../../../shared/files files
cd -

# Clean-up the profile directory, and sym-link it into the drupal directory.
rsync -az drupal/profiles/$PROFILE/ $PROFILE/
rm -rf drupal/profiles/$PROFILE
cd drupal/profiles
ln -s ../../$PROFILE $PROFILE
cd -
