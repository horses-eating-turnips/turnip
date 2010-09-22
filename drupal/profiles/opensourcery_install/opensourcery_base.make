; OpenSourcery base make file
core = "7.x"

; Contrib modules
projects[admin][subdir] = "contrib"
projects[admin][version] = "2.0-beta1"

projects[advanced_help][subdir] = "contrib"
projects[advanced_help][version] = "1.x-dev"

projects[ctools][subdir] = "contrib"
projects[ctools][type] = "module"
projects[ctools][download][type] = "git"
projects[ctools][download][url] = "git://github.com/sdboyer/ctools.git"

projects[features][subdir] = "contrib"
projects[features][version] = "1.0-alpha1"

projects[less][subdir] = "contrib"
projects[less][version] = "2.x-dev"

projects[path_redirect][subdir] = "contrib"
projects[path_redirect][version] = "1.x-dev"

projects[pathauto][subdir] = "contrib"
projects[pathauto][version] = "1.0-alpha2"

projects[role_delegation][subdir] = "contrib"
projects[role_delegation][version] = "1.x-dev"

projects[strongarm][subdir] = "contrib"
projects[strongarm][version] = "2.0-beta1"

projects[token][subdir] = "contrib"
projects[token][version] = "1.0-alpha2"

projects[wysiwyg][subdir] = "contrib"
projects[wysiwyg][version] = "2.x-dev"

; Development modules
projects[admin_menu][subdir] = "development"
projects[admin_menu][version] = "3.x-dev"

projects[devel][subdir] = "development"
projects[devel][version] = "1.0-beta2"

projects[coder][subdir] = "development"
projects[coder][version] = "1.0-beta4"

; Libraries

libraries[ckeditor][download][type] = "get"
libraries[ckeditor][download][url] = "http://download.cksource.com/CKEditor/CKEditor/CKEditor%203.4/ckeditor_3.4.tar.gz"
libraries[ckeditor][destination] = "libraries"
libraries[ckeditor][directory_name] = "ckeditor"

; Themes

projects[zen][version] = "3.x-dev"

projects[tao][type] = theme
projects[tao][download][type] = "git"
projects[tao][download][url] = "git://github.com/developmentseed/tao.git"
projects[tao][download][branch] = "drupal-7--3"

projects[rubik][type] = theme
projects[rubik][download][type] = "git"
projects[rubik][download][url] = "git://github.com/developmentseed/rubik.git"
projects[rubik][download][branch] = "drupal-7--3"
