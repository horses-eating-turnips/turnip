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
exit


# since profile is sym-linked, move modules and themes in there
mv drupal/profiles/opensourcery_install/modules/contrib drupal/profiles/$PROFILE/modules


mv drupal/sites/all/modules/contrib drupal/profiles/$PROFILE/modules/contrib
mv drupal/sites/all/modules/stock drupal/profiles/$PROFILE/modules/stock
mv drupal/sites/all/themes/stock drupal/profiles/$PROFILE/themes/stock
rm -rf drupal/sites/all/modules
rm -rf drupal/sites/all/themes

# settings and files
ln -s shared/settings.php drupal/sites/default/settings.php
ln -s shared/files drupal/sites/default/files