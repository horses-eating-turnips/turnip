Donor Rally Drupal documentation and patches
--------------------------------------------

All files in this directory, unless otherwise noted, are patch files against various contrib modules, and in some rare cases, Drupal core.

All patches use the following naming convention:

MODULE_NAME.NID.patch

where NID denotes the drupal.org issue ID that the patch is being tracked in.

When updating any modules found in this directory it is important to first check the issue. If the issue has been sufficiently resolved, it is generally alright to proceed with the updgrade without re-applying the patch. If the issue is still active, the patch should be applied after upgrading the module.

In the case of the rare core patches, these are named using the convention above, but replacing the module name with CORE. A common use case here is to patch the .htaccess file, so the patch name would be CORE.htaccess.patch.
