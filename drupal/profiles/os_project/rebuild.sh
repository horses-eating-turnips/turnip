# To run this script, you'll need drush_make, git, and cvs installed.
#
# To build with working CVS repositories, add the --working-copy flag to the drush make command (and make sure you have CVSROOT set).
drush make --no-core --contrib-destination=. os_project.make
