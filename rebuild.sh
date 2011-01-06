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
core = "7.x"\n
projects[drupal][type] = "core"
projects[drupal][version] = "7.0"\n
EOF
)

# remove old directories
rm -rf drupal
rm -rf $PROFILE/modules/contrib
rm -rf $PROFILE/modules/stock
rm -rf $PROFILE/themes/stock
rm -rf $PROFILE/libraries

# Build the drupal directory from the make file.
echo -e "$MAKE" | drush make --yes --contrib-destination=profiles/$PROFILE - drupal

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

# Modules must be in the profile being installed, so move them over
# from opensourcery_install.
rsync -az drupal/profiles/opensourcery_install/modules/ drupal/profiles/$PROFILE/modules/
rsync -az drupal/profiles/opensourcery_install/libraries/ drupal/profiles/$PROFILE/libraries/
rsync -az drupal/profiles/opensourcery_install/themes/ drupal/profiles/$PROFILE/themes/
