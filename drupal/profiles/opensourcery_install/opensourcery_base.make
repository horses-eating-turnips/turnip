; OpenSourcery base make file
core = "6.x"

; Contrib modules
projects[admin][subdir] = "contrib"
projects[admin][version] = "2.0"

projects[advanced_help][subdir] = "contrib"
projects[advanced_help][version] = "1.2"

projects[better_formats][subdir] = "contrib"
projects[better_formats][version] = "1.2"

projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.7"

projects[features][subdir] = "contrib"
projects[features][version] = "1.0"

projects[less][subdir] = "contrib"
projects[less][version] = "2.1"

projects[path_redirect][subdir] = "contrib"
projects[path_redirect][version] = "1.0-beta7"

projects[pathauto][subdir] = "contrib"
projects[pathauto][version] = "1.4"

projects[role_delegation][subdir] = "contrib"
projects[role_delegation][version] = "1.3"

projects[strongarm][subdir] = "contrib"
projects[strongarm][version] = "2.0"

projects[token][subdir] = "contrib"
projects[token][version] = "1.14"

projects[wysiwyg][subdir] = "contrib"
projects[wysiwyg][version] = "2.1"

; Development modules
projects[admin_menu][subdir] = "development"
projects[admin_menu][version] = "1.6"

projects[devel][subdir] = "development"
projects[devel][version] = "1.22"

projects[coder][subdir] = "development"
projects[coder][version] = "2.0-beta1"

projects[simpletest][subdir] = "development"
projects[simpletest][version] = "2.10"

; Libraries

libraries[ckeditor][download][type] = "get"
libraries[ckeditor][download][url] = "http://download.cksource.com/CKEditor/CKEditor/CKEditor%203.4/ckeditor_3.4.tar.gz"
libraries[ckeditor][destination] = "libraries"
libraries[ckeditor][directory_name] = "ckeditor"
