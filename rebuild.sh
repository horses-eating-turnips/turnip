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

MAKE=$(cat $PROFILE/$PROFILE.make - <<EOF
api = "2"\n
core = "6.x"\n
projects[drupal][version] = "6.19"\n
EOF
)

# remove old directories
rm -rf drupal
rm -rf $PROFILE/modules/contrib
rm -rf $PROFILE/modules/stock
rm -rf $PROFILE/themes/stock
echo -e "$MAKE" | drush make --yes --contrib-destination=profiles/$PROFILE - drupal

# settings and files
cd drupal/sites/default
ln -s ../../../shared/settings.php settings.php
ln -s ../../../shared/files files
cd -ls 

# os_project directory
rsync -az drupal/profiles/$PROFILE/ $PROFILE/
rm -rf drupal/profiles/$PROFILE
cd drupal/profiles
ln -s ../../$PROFILE $PROFILE
cd -
