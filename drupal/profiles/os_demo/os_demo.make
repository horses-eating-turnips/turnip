; This is the actual project make file that should be edited for a
; given project. This text should be replaced with a brief description
; of the project.
api = 2

includes[core] = "../opensourcery_install/opensourcery_base.make"

; Core image handling make file.
includes[image] = "../opensourcery_install/opensourcery_image.make"

; OpenSourcery base feature.
projects[os_base][subdir] = "features"
projects[os_base][type] = "module"
projects[os_base][download][type] = "git"
projects[os_base][download][url] = "git://github.com/opensourcery/os_base.git"

; OpenSourcery blog
projects[os_blog][subdir] = "features"
projects[os_blog][type] = "module"
projects[os_blog][download][type] = "git"
projects[os_blog][download][url] = "git://github.com/opensourcery/os_blog.git"

; OpenSourcery events
projects[os_event][subdir] = "features"
projects[os_event][type] = "module"
projects[os_event][download][type] = "git"
projects[os_event][download][url] = "git://github.com/opensourcery/os_event.git"

; OpenSourcery slideshow
projects[os_slideshow][subdir] = "features"
projects[os_slideshow][type] = "module"
projects[os_slideshow][download][type] = "git"
projects[os_slideshow][download][url] = "git://github.com/opensourcery/os_slideshow.git"

; CCK
projects[cck][subdir] = "contrib"
projects[cck][version] = "2.8"

; Context
projects[context][subdir] = "contrib"
projects[context][version] = "3.0"

; Views
projects[views][subdir] = "contrib"
projects[views][version] = "2.11"

; Semantic Views
 projects[semanticviews][subdir] = "contrib"
 projects[semanticviews][version] = "1.1"
; http://drupal.org/node/832048#comment-3441744
projects[semanticviews][patch][] = "http://drupal.org/files/issues/semanticviews.832048.patch"

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
projects[jquery_ui][subdir] = "contrib"
projects[jquery_ui][version] = "1.4"
libraries[jquery_ui][download][type] = "get"
libraries[jquery_ui][download][url] = "http://jquery-ui.googlecode.com/files/jquery.ui-1.6.zip"
libraries[jquery_ui][directory_name] = "jquery.ui"
libraries[jquery_ui][destination] = "modules/contrib/jquery_ui"

; Can be a normal release once 3.3 is released. This dev version fixes issue #895768
projects[webform][subdir] = "contrib"
projects[webform][type] = "module"
projects[webform][download][type] = "cvs"
projects[webform][download][module] = "contributions/modules/webform"
projects[webform][download][revision] = "DRUPAL-6--3:2010-08-30"

; Base theme: Create and specify a tag at the *end* of the project.
projects[doune][type] = theme
projects[doune][download][type] = "git"
projects[doune][download][url] = "git://github.com/opensourcery/doune.git"
;projects[doune][download][tag] = "6.x-0.1"

