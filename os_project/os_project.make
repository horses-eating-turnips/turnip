; This is the actual project make file that should be edited for a
; given project. This text should be replaced with a brief description
; of the project.
api = 2

; Base installation profile
projects[opensourcery_install][type] = "profile"
projects[opensourcery_install][download][type] = "git"
projects[opensourcery_install][download][url] = "git@github.com:opensourcery/opensourcery_install.git"
projects[opensourcery_install][download][branch] = "DRUPAL-6"
;projects[opensourcery_install][download][tag] = "DRUPAL-6--1.0"

; OpenSourcery administration feature
projects[os_admin][subdir] = "stock"
projects[os_admin][type] = "module"
projects[os_admin][download][type] = "git"
projects[os_admin][download][url] = "git://github.com/opensourcery/os_admin.git"
; Tag new release at end of project
; projects[os_admin][download][tag] = "DRUPAL-6--1-0-ALPHA2"

; OpenSourcery base feature.
projects[os_base][subdir] = "stock"
projects[os_base][type] = "module"
projects[os_base][download][type] = "git"
projects[os_base][download][url] = "git://github.com/opensourcery/os_base.git"
; Tag new release at end of project
; projects[os_base][download][tag] = "DRUPAL-6--1-0-ALPHA1"

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

; Apache Solr Search
;projects[apachesolr][subdir] = "contrib"
;projects[apachesolr][version] = "1.2"
;libraries[SolrPHPClient][download][type] = "svn"
;libraries[SolrPHPClient][download][url] = "http://solr-php-client.googlecode.com/svn/trunk/"
;libraries[SolrPHPClient][download][revision] = "22"
;libraries[SolrPHPClient][destination] = "modules/contrib/apachesolr/"
;libraries[SolrPHPClient][directory_name] = "SolrPhpClient"

; Project-specific modules, and overrides.


; Base theme: Create and specify a tag at the *end* of the project.
projects[doune][type] = "theme"
projects[doune][subdir] = "stock"
projects[doune][download][type] = "git"
projects[doune][download][url] = "git://github.com/opensourcery/doune.git"
;projects[doune][download][tag] = "6.x-0.1"

