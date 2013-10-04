; OpenSourcery base make file
core = "7.x"
api = 2

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;; CONTRIB ;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;; (alphabetical order) ;;;;;;;;;;;;;;;

projects[breakpoints][download][branch] = "7.x-1.x"
projects[breakpoints][download][revision] = "c4f3665"

;projects[ckeditor][version] = "1.13"

projects[ckeditor][download][branch] = "7.x-1.x"
projects[ckeditor][download][revision] = "57245a9"
; Media 2.x integration. https://drupal.org/node/1504696#comment-7766639
projects[ckeditor][patch][] = "https://drupal.org/files/ckeditor_1504696_58.patch"

projects[ctools][version] = "1.3"
; http://drupal.org/node/1120028#comment-5792282
projects[ctools][patch][] = "http://drupal.org/files/page-manager-admin-paths-1120028-08.patch"
; https://drupal.org/node/1417630#comment-6810906
projects[ctools][patch][] = "https://drupal.org/files/ctools-views-content-custom-url-1417630-06.patch"
; Adding a renderable-array block to a page gives errors in the admin UI.
; @todo remove with ctools upgrade to 1.4.
projects[ctools][patch][1925018] = "http://drupal.org/files/ctools-1925018-61.patch"

projects[edit][version] = "1.0-alpha11"

projects[entity][version] = "1.2"

projects[entitycache][version] = "1.1"

projects[elements][version] = "1.4"

projects[features][version] = "2.0-rc2"
; PDO exception if permissions are set in same feature as module creating them. http://drupal.org/node/1063204#comment-6350488
projects[features][patch][] = "http://drupal.org/files/features_static_caches-1063204-32.patch"
; Expanded or hidden menu links aren't seen as customized http://drupal.org/node/927576
projects[features][patch][] = "http://drupal.org/files/menu_links_customized-927576-8.patch"

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

projects[gridbuilder][version] = 1.0-alpha2

projects[html5_tools][version] = "1.2"

projects[jquery_update][version] = "2.3"

projects[json2][version] = "1.1"

projects[layout][version] = 1.0-alpha6

projects[libraries][download][branch] = "7.x-2.x"
projects[libraries][download][revision] = "037017e"

projects[linkchecker][version] = "1.1"

projects[navbar][version] = "1.0-alpha10"

projects[redirect][version] = "1.0-rc1"

projects[responsive_preview][version] = 1.0-beta1

projects[pathauto][version] = "1.2"

projects[picture][version] = 1.1

projects[simplified_menu_admin][version] = 1.0-beta2

projects[strongarm][version] = "2.0"

projects[token][version] = "1.5"

projects[views][version] = "3.7"

projects[wysiwyg][version] = "2.2"
; Select theme css patch: http://drupal.org/node/1309040#comment-6107956
projects[wysiwyg][patch][] = "http://drupal.org/files/1309040-22-select_theme_css.patch"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;; THEMES ;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

projects[responsive_bartik][download][revision] = 7c2db58a201fd572153545b24bfcc2703c2fac80
projects[responsive_bartik][download][branch] = 7.x-1.x

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

projects[os_devel][type] = "module"
projects[os_devel][subdir] = "development"
projects[os_devel][download][branch] = "7.x-1.x"
projects[os_devel][download][url] = "https://github.com/opensourcery/os_devel.git"

projects[stage_file_proxy][subdir] = "development"
projects[stage_file_proxy][version] = "1.4"

projects[styleguide][subdir] = "development"
projects[styleguide][version] = "1.1"

projects[diff][subdir] = "development"
projects[diff][version] = "3.2"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;; LIBRARIES ;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

libraries[backbone][download][type] = "get"
libraries[backbone][download][url] = "https://github.com/documentcloud/backbone/archive/1.0.0.zip"

libraries[ckeditor][download][type] = "get"
libraries[ckeditor][download][url] = "http://download.cksource.com/CKEditor/CKEditor/CKEditor%204.1.3/ckeditor_4.1.3_standard.zip"
;libraries[ckeditor][download][url] = http://download.cksource.com/CKEditor/CKEditor/CKEditor%204.0.1/ckeditor_4.0.1_standard.zip

libraries[footable][directory_name] = "FooTable"
libraries[footable][download][revision] = "228b101"
libraries[footable][download][type] = "git"
libraries[footable][download][url] = "https://github.com/bradvin/FooTable.git"

libraries[json2][download][type] = "get"
libraries[json2][download][url] = "https://raw.github.com/douglascrockford/JSON-js/master/json2.js"
libraries[json2][revision] = "fc535e9cc8fa78bbf45a85835c830e7f799a5084"

libraries[underscore][download][type] = "get"
libraries[underscore][download][url] = "https://github.com/documentcloud/underscore/archive/1.4.4.zip"
