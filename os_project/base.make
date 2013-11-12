; OpenSourcery base make file
core = "7.x"
api = 2

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;; CONTRIB ;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;; (alphabetical order) ;;;;;;;;;;;;;;;
projects[ctools][version] = "1.3"
; http://drupal.org/node/1120028#comment-5792282
projects[ctools][patch][] = "http://drupal.org/files/page-manager-admin-paths-1120028-08.patch"
; https://drupal.org/node/1417630#comment-6810906
projects[ctools][patch][] = "https://drupal.org/files/ctools-views-content-custom-url-1417630-06.patch"

projects[entitycache][version] = "1.2"

projects[elements][version] = "1.4"

projects[features][version] = "2.0"
; PDO exception if permissions are set in same feature as module creating them. http://drupal.org/node/1063204#comment-6350488
projects[features][patch][] = "http://drupal.org/files/features_static_caches-1063204-32.patch"

; Later dev commit fixes array/boolean mismatch.
; @see https://drupal.org/node/1915318
projects[features_override][download][branch] = "7.x-2.x"
projects[features_override][download][revision] = "ed1df0e"
; A patch to fix coding standards issues with produced features override code
; Original issue see: http://drupal.org/node/1974336
projects[features_override][patch][] = "http://drupal.org/files/export_breaks_coding_standards_0.patch"

projects[fences][version] = "1.0"

; FooTable (responsive tables).
projects[footable][download][branch] = "7.x-1.x"
projects[footable][download][revision] = "a52b6dc"
; https://drupal.org/node/1924942#comment-7098614
projects[footable][patch][] = "https://drupal.org/files/footable-hook-requirements-install-1924942-02.patch"

projects[google_analytics][version] = "1.3"

projects[html5_tools][download][branch] = "7.x-1.x"
projects[html5_tools][download][revision] = "11e0c28"

projects[jquery_update][download][branch] = "7.x-2.x"
projects[jquery_update][download][revision] = "469fac0"

projects[linkchecker][version] = "1.1"

projects[menu_block][version] = "2.3"

projects[menu_position][version] = "1.1"

projects[redirect][version] = "1.0-rc1"

projects[pathauto][version] = "1.2"

projects[strongarm][version] = "2.0"

projects[token][version] = "1.5"

projects[views][version] = "3.7"

projects[wysiwyg][version] = "2.2"
; Select theme css patch: http://drupal.org/node/1309040#comment-6107956
projects[wysiwyg][patch][] = "http://drupal.org/files/1309040-22-select_theme_css.patch"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;; DEVELOPMENT MODULES ;;;;;;;;;;;;;
;;;;;;;; (may be disabled for production) ;;;;;;;;
projects[admin_menu][type] = "module"
projects[admin_menu][subdir] = "development"
projects[admin_menu][version] = "3.0-rc4"

projects[devel][subdir] = "development"
projects[devel][version] = "1.3"

projects[environment_indicator][subdir] = "development"
projects[environment_indicator][version] = "2.0"

projects[maillog][download][branch] = "7.x-1.x"
projects[maillog][download][revision] = "2591153"
projects[maillog][subdir] = "development"
; Behat step-definitions: https://drupal.org/node/1932698#comment-7131840
projects[maillog][patch][] = "https://drupal.org/files/behat-subcontext-1932698-1.patch"

projects[os_devel][type] = "module"
projects[os_devel][subdir] = "development"
projects[os_devel][download][branch] = "7.x-1.x"
projects[os_devel][download][url] = "https://github.com/opensourcery/os_devel.git"

projects[os_testing][type] = "module"
projects[os_testing][subdir] = "development"
projects[os_testing][download][tag] = "7.x-1.0"
projects[os_testing][download][url] = "https://github.com/opensourcery/os_testing.git"

projects[stage_file_proxy][subdir] = "development"
projects[stage_file_proxy][version] = "1.4"

projects[styleguide][subdir] = "development"
projects[styleguide][version] = "1.1"

projects[diff][subdir] = "development"
projects[diff][version] = "3.2"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;; LIBRARIES ;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
libraries[tinymce][download][type] = "get"
libraries[tinymce][download][url] = "https://github.com/downloads/tinymce/tinymce/tinymce_3.5.8.zip"
libraries[tinymce][destination] = "libraries"
libraries[tinymce][directory_name] = "tinymce"

libraries[footable][directory_name] = "FooTable"
libraries[footable][download][revision] = "228b101"
libraries[footable][download][type] = "git"
libraries[footable][download][url] = "https://github.com/bradvin/FooTable.git"
