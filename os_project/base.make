; OpenSourcery base make file
core = "7.x"
api = 2

; Contrib modules
projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.0-rc1"
; http://drupal.org/node/1369082#comment-5453738
projects[ctools][patch][] = "http://drupal.org/files/ctools-1369082-02.patch"
; http://drupal.org/node/1120028#comment-5269384
projects[ctools][patch][] = "http://drupal.org/files/page-manager-admin-paths_3.patch"

projects[entitycache][subdir] = "contrib"
projects[entitycache][version] = "1.1"

projects[features][subdir] = "contrib"
projects[features][version] = "1.0-beta6"
; http://drupal.org/node/1265168#comment-5413624
projects[features][patch][] = "http://drupal.org/files/features-1265168-19-roles.patch"

projects[redirect][subdir] = "contrib"
projects[redirect][type] = "module"
projects[redirect][download][type] = "git"
; http://drupal.org/node/1174594
projects[redirect][download][revision] = "5de9fd440f1c5b8955b08ea3722a0ee09c6e051e"

projects[pathauto][subdir] = "contrib"
projects[pathauto][version] = "1.0"

projects[strongarm][subdir] = "contrib"
projects[strongarm][version] = "2.0-beta5"

projects[token][subdir] = "contrib"
projects[token][version] = "1.0-rc1"

projects[wysiwyg][subdir] = "contrib"
projects[wysiwyg][version] = "2.1"
; http://drupal.org/node/624018#comment-5098162
projects[wysiwyg][patch][] = "http://drupal.org/files/0001-feature.inc-from-624018-211.patch"

; Development modules
projects[admin_menu][type] = "module"
projects[admin_menu][subdir] = "development"
projects[admin_menu][version] = "3.0-rc1"
; Duplicate dropdown - http://drupal.org/node/1025846#comment-4111862
projects[admin_menu][patch][] = "http://drupal.org/files/issues/admin_menu.1025846-4.patch"

projects[devel][subdir] = "development"
projects[devel][version] = "1.2"

projects[coder][subdir] = "development"
projects[coder][version] = "1.0"

; Libraries
libraries[ckeditor][download][type] = "get"
libraries[ckeditor][download][url] = "http://download.cksource.com/CKEditor/CKEditor/CKEditor%203.6.2/ckeditor_3.6.2.tar.gz"
libraries[ckeditor][destination] = "libraries"
libraries[ckeditor][directory_name] = "ckeditor"

; Themes
projects[tao][version] = "3.0-beta4"
projects[rubik][version] = "4.0-beta7"
