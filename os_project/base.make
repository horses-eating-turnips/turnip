; OpenSourcery base make file
core = "7.x"
api = 2

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;; CONTRIB ;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;; (alphabetical order) ;;;;;;;;;;;;;;;
projects[breakpoints][version] = "1.1"

projects[context_admin][version] = "1.2"

projects[ctools][version] = "1.4"
; http://drupal.org/node/1120028#comment-5792282
projects[ctools][patch][] = "http://drupal.org/files/page-manager-admin-paths-1120028-08.patch"
; https://drupal.org/node/1417630#comment-6810906
projects[ctools][patch][] = "https://drupal.org/files/ctools-views-content-custom-url-1417630-06.patch"

projects[entity][version] = "1.5"

projects[entitycache][version] = "1.2"

projects[entityreference][version] = "1.1"

projects[elements][version] = "1.4"

projects[features][version] = "2.0"
; PDO exception if permissions are set in same feature as module creating them. http://drupal.org/node/1063204#comment-6350488
projects[features][patch][] = "http://drupal.org/files/features_static_caches-1063204-32.patch"
; Auto-add permissions to new node types https://www.drupal.org/node/2301315#comment-8958383
projects[features][patch][] = "http://www.drupal.org/files/issues/features_auto_export_node_type_permissions-2301315-1.patch"

; Later dev commit fixes array/boolean mismatch.
; @see https://drupal.org/node/1915318
projects[features_override][download][branch] = "7.x-2.x"
projects[features_override][download][revision] = "ed1df0e"
; A patch to fix coding standards issues with produced features override code
; Original issue see: http://drupal.org/node/1974336
projects[features_override][patch][] = "http://drupal.org/files/export_breaks_coding_standards_0.patch"

projects[fences][version] = "1.0"

projects[field_formatter_settings][version] = "1.1"

; FooTable (responsive tables).
projects[footable][download][branch] = "7.x-1.x"
projects[footable][download][revision] = "0878571"
; Support later FooTable library: https://drupal.org/node/2212881#comment-8734427
projects[footable][patch][] = "https://drupal.org/files/issues/footable-v2-2212881-01.patch"

projects[google_analytics][version] = "1.4"

projects[html5_tools][download][branch] = "7.x-1.x"
projects[html5_tools][download][revision] = "11e0c28"

projects[jquery_update][download][branch] = "7.x-2.x"
projects[jquery_update][download][revision] = "469fac0"

projects[link][version] = "1.2"

projects[linkchecker][version] = "1.2"

projects[linked_field][version] = "1.9"

projects[menu_block][version] = "2.4"

projects[menu_position][version] = "1.1"

projects[navbar][version] = 1.4

projects[redirect][version] = "1.0-rc1"

projects[pathauto][version] = "1.2"

projects[references_dialog][version] = "1.0-alpha4"
; References_dialog patch for FPP.  https://drupal.org/comment/8200307#comment-8200307
projects[references_dialog][patch][] = "https://drupal.org/files/issues/references_dialog_fieldable_panels_pane_support-2140535-3.patch"
; Entity Reference incorrectly calls entity_access() https://drupal.org/comment/7893609#comment-7893609
projects[references_dialog][patch][] = "https://drupal.org/files/references_dialog-wrong-call-to-entity_access-1780626-6.patch"

projects[strongarm][version] = "2.0"

projects[token][version] = "1.5"

projects[views][version] = "3.8"

projects[wysiwyg][download][branch] = "7.x-2.x"
projects[wysiwyg][download][revision] = "ee64524"
; Select theme css patch: https://drupal.org/node/1309040#comment-8008765
projects[wysiwyg][patch][] = "https://drupal.org/files/wysiwyg-1309040-32-select-theme-styles.patch"
; Support CKEditor 4.x's Advanced Content Filter setting to avoid destroying Media embeds.
; https://drupal.org/node/1956778
projects[wysiwyg][patch][] = "https://drupal.org/files/wysiwyg-ckeditor-acf-1956778-37.patch"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;; DEVELOPMENT MODULES ;;;;;;;;;;;;;
;;;;;;;; (may be disabled for production) ;;;;;;;;
projects[admin_menu][subdir] = "development"
projects[admin_menu][version] = "3.0-rc4"

projects[devel][subdir] = "development"
projects[devel][version] = "1.5"

projects[environment_indicator][subdir] = "development"
projects[environment_indicator][version] = "2.2"

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

projects[search_krumo][subdir] = "development"
projects[search_krumo][version] = "1.5"

projects[stage_file_proxy][subdir] = "development"
projects[stage_file_proxy][version] = "1.5"

projects[styleguide][subdir] = "development"
projects[styleguide][version] = "1.1"
projects[styleguide][patch][] = "https://drupal.org/files/issues/1004246-9-styleguide-maintenance-page.patch"

projects[diff][subdir] = "development"
projects[diff][version] = "3.2"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;; LIBRARIES ;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
libraries[backbone][download][type] = "get"
libraries[backbone][download][url] = "https://github.com/jashkenas/backbone/archive/1.0.0.tar.gz"

libraries[ckeditor][download][type] = "get"
libraries[ckeditor][download][url] = "http://download.cksource.com/CKEditor/CKEditor/CKEditor%204.3.2/ckeditor_4.3.2_full.zip"

libraries[underscore][download][type] = "get"
libraries[underscore][download][url] = "https://github.com/jashkenas/underscore/archive/1.5.2.zip"

libraries[footable][directory_name] = "FooTable"
libraries[footable][download][tag] = "V2.0.1.4"
libraries[footable][download][type] = "git"
libraries[footable][download][url] = "https://github.com/bradvin/FooTable.git"
