; OpenSourcery base make file
core = "7.x"
api = 2

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;; CONTRIB ;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;; (alphabetical order) ;;;;;;;;;;;;;;;
projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.0"
; http://drupal.org/node/1120028#comment-5792282
projects[ctools][patch][] = "http://drupal.org/files/page-manager-admin-paths-1120028-08.patch"

projects[entitycache][subdir] = "contrib"
projects[entitycache][version] = "1.1"

projects[features][subdir] = "contrib"
projects[features][revision] = "a110769"
; http://drupal.org/node/1265168#comment-5413624
projects[features][patch][] = "http://drupal.org/files/features-1265168-19-roles.patch"

projects[redirect][subdir] = "contrib"
projects[redirect][version] = "1.0-beta4"

projects[pathauto][subdir] = "contrib"
projects[pathauto][version] = "1.0"

projects[strongarm][subdir] = "contrib"
projects[strongarm][version] = "2.0-rc1"

projects[token][subdir] = "contrib"
projects[token][version] = "1.0-rc1"

projects[wysiwyg][subdir] = "contrib"
projects[wysiwyg][version] = "2.1"
; http://drupal.org/node/624018#comment-5098162
projects[wysiwyg][patch][] = "http://drupal.org/files/0001-feature.inc-from-624018-211.patch"
; Select theme css patch: http://drupal.org/node/1309040#comment-5512318
projects[wysiwyg][patch[] = "http://drupal.org/files/1309040-7-select_theme_css.patch"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;; DEVELOPMENT MODULES ;;;;;;;;;;;;;
;;;;;;;; (may be disabled for production) ;;;;;;;;
projects[admin_menu][type] = "module"
projects[admin_menu][subdir] = "development"
projects[admin_menu][version] = "3.0-rc1"
; Duplicate dropdown - http://drupal.org/node/1025846#comment-4111862
projects[admin_menu][patch][] = "http://drupal.org/files/issues/admin_menu.1025846-4.patch"

projects[devel][subdir] = "development"
projects[devel][version] = "1.2"

projects[environment_indicator][subdir] = "development"
projects[environment_indicator][version] = "1.1"

projects[stage_file_proxy][subdir] = "development"
projects[stage_file_proxy][revision] = "0c619c7"

; Libraries
libraries[tinymce][download][type] = "get"
libraries[tinymce][download][url] = "https://github.com/downloads/tinymce/tinymce/tinymce_3.4.8.zip"
libraries[tinymce][destination] = "libraries"
libraries[tinymce][directory_name] = "tinymce"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;; THEME ;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
projects[tao][version] = "3.0-beta4"
projects[rubik][version] = "4.0-beta7"
