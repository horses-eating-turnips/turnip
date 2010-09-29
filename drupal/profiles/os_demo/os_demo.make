; This is the actual project make file that should be edited for a
; given project. This text should be replaced with a brief description
; of the project.

includes[core] = "../opensourcery_install/opensourcery_base.make"

; Core image handling make file.
; includes[image] = "../opensourcery_install/opensourcery_image.make"

; OpenSourcery base feature.
projects[os_base][subdir] = "features"
projects[os_base][type] = "module"
projects[os_base][download][type] = "git"
projects[os_base][download][url] = "git://github.com/opensourcery/os_base.git"
projects[os_base][download][tag] = "DRUPAL-6--1-0-ALPHA1"

; Contextual admin (required by base feature).
projects[context_admin][subdir] = "contrib"
projects[context_admin][version] = "1.0-beta11"

; CCK
;projects[cck][subdir] = "contrib"
;projects[cck][version] = "2.8"

; Views
;projects[views][subdir] = "contrib"
;projects[views][version] = "2.11"

; Semantic Views
; projects[semanticviews][subdir] = "contrib"
; projects[semanticviews][version] = "1.1"
;; http://drupal.org/node/832048#comment-3441744
;projects[semanticviews][patch][] = "http://drupal.org/files/issues/semanticviews.832048.patch"

; SSL handling
;projects[securepages][subdir] = "contrib"
;projects[securepages][version] = "1.8"

; Mollom
;projects[mollom][subdir] = "contrib"
;projects[mollom][version] = "1.13"

; Google analytics
;projects[google_analytics][subdir] = "contrib"
;projects[google_analytics][version] = "2.2"

; jQuery UI
;projects[jquery_ui][subdir] = "contrib"
;projects[jquery_ui][version] = "1.4"
;libraries[jquery_ui][download][type] = "get"
;libraries[jquery_ui][download][url] = "http://jquery-ui.googlecode.com/files/jquery.ui-1.6.zip"
;libraries[jquery_ui][directory_name] = "jquery.ui"
;libraries[jquery_ui][destination] = "modules/contrib/jquery_ui"

; Project-specific modules, and overrides.


; Base theme: Create and specify a tag at the *end* of the project.
projects[doune][type] = theme
projects[doune][download][type] = "git"
projects[doune][download][url] = "git://github.com/opensourcery/doune.git"
;projects[doune][download][tag] = "6.x-0.1"

