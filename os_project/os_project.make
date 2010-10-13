; This is the actual project make file that should be edited for a
; given project. This text should be replaced with a brief description
; of the project.

includes[core] = "../opensourcery_install/opensourcery_base.make"

; Core image handling make file.
; includes[image] = "../opensourcery_install/opensourcery_image.make"

; OpenSourcery base feature.
projects[os_base][subdir] = "stock"
projects[os_base][type] = "module"
projects[os_base][download][type] = "git"
projects[os_base][download][url] = "git://github.com/opensourcery/os_base.git"
projects[os_base][download][branch] = "DRUPAL-7"

; Contextual admin (required by base feature).
;projects[context_admin][subdir] = "contrib"
;projects[context_admin][version] = "1.0-beta11"

; Views
;projects[views][subdir] = "contrib"
;projects[views][version] = "3.x-dev"

; Semantic Views
; projects[semanticviews][subdir] = "contrib"
; projects[semanticviews][version] = "1.1"
;; http://drupal.org/node/832048#comment-3441744
;projects[semanticviews][patch][] = "http://drupal.org/files/issues/semanticviews.832048.patch"

; Mollom
;projects[mollom][subdir] = "contrib"
;projects[mollom][version] = "1.0-alpha2"

; Google analytics
;projects[google_analytics][subdir] = "contrib"
;projects[google_analytics][version] = "1.x-dev"

; Project-specific modules, and overrides.


; Base theme: Create and specify a tag at the *end* of the project.
projects[doune][subdir] = "stock"
projects[doune][type] = theme
projects[doune][download][type] = "git"
projects[doune][download][url] = "git://github.com/opensourcery/doune.git"
projects[doune][download][branch] = "DRUPAL-7--1"

