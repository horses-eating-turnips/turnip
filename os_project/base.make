; OpenSourcery base make file
core = "7.x"
api = 2

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;; CONTRIB ;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;; (alphabetical order) ;;;;;;;;;;;;;;;
; ctools revision > 7.x-1.2
projects[ctools][revision] = "7cd8d95"
; http://drupal.org/node/1120028#comment-5792282
projects[ctools][patch][] = "http://drupal.org/files/page-manager-admin-paths-1120028-08.patch"

projects[entitycache][version] = "1.1"

projects[elements][version] = "1.2"

projects[features][version] = "1.0-rc3"
; http://drupal.org/node/1063204#comment-6217690
projects[features][patch][] = "http://drupal.org/files/features-static-caches-1063204-27.patch"

projects[fences][version] = "1.0"

projects[html5_tools][version] = "1.2"

projects[redirect][version] = "1.0-beta4"

projects[pathauto][version] = "1.2"

projects[strongarm][version] = "2.0"

projects[token][version] = "1.2"

projects[wysiwyg][revision] = "d17bf11"
; Select theme css patch: http://drupal.org/node/1309040#comment-6107956
projects[wysiwyg][patch][] = "http://drupal.org/files/1309040-22-select_theme_css.patch"
; Lazy-load editors: http://drupal.org/node/356480. Allows the WYSIWYG to work
; when editing custom content from within Panels.
projects[wysiwyg][patch][] = "http://drupal.org/files/lazy_wysiwyg-356480-150.patch"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;; DEVELOPMENT MODULES ;;;;;;;;;;;;;
;;;;;;;; (may be disabled for production) ;;;;;;;;
projects[admin_menu][type] = "module"
projects[admin_menu][subdir] = "development"
projects[admin_menu][version] = "3.0-rc3"

projects[devel][subdir] = "development"
projects[devel][version] = "1.3"

projects[environment_indicator][subdir] = "development"
projects[environment_indicator][version] = "1.1"

projects[os_devel][type] = "module"
projects[os_devel][subdir] = "development"
projects[os_devel][download][branch] = "7.x-1.x"
projects[os_devel][download][url] = "git://github.com/opensourcery/os_devel.git"

projects[stage_file_proxy][subdir] = "development"
projects[stage_file_proxy][version] = "1.0"

projects[styleguide][subdir] = "development"
projects[styleguide][version] = "1.0"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;; LIBRARIES ;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
libraries[tinymce][download][type] = "get"
libraries[tinymce][download][url] = "https://github.com/downloads/tinymce/tinymce/tinymce_3.4.8.zip"
libraries[tinymce][destination] = "libraries"
libraries[tinymce][directory_name] = "tinymce"
