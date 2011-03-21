; This is the actual project make file that should be edited for a
; given project. This text should be replaced with a brief description
; of the project.
api = 2

; Base installation profile
projects[opensourcery_install][type] = "profile"
projects[opensourcery_install][download][type] = "git"
projects[opensourcery_install][download][url] = "git@github.com:opensourcery/opensourcery_install.git"
projects[opensourcery_install][download][branch] = "DRUPAL-7"
;projects[opensourcery_install][download][tag] = "DRUPAL-7--1-0"

; OpenSourcery administration feature
projects[os_admin][subdir] = "stock"
projects[os_admin][type] = "module"
projects[os_admin][download][type] = "git"
projects[os_admin][download][url] = "git://github.com/opensourcery/os_admin.git"
projects[os_admin][download][branch] = "DRUPAL-7--1"
; Tag new release at end of project
; projects[os_admin][download][tag] = "DRUPAL-7--1-0-ALPHA2"

; OpenSourcery base feature.
projects[os_base][subdir] = "stock"
projects[os_base][type] = "module"
projects[os_base][download][type] = "git"
projects[os_base][download][url] = "git://github.com/opensourcery/os_base.git"
projects[os_base][download][branch] = "DRUPAL-7--1"
; Tag new release at end of project
; projects[os_base][download][tag] = "DRUPAL-7--1-0-ALPHA1"

; CCK
;projects[cck][subdir] = "contrib"
;projects[cck][version] = "2.8"

; Views
;projects[views][subdir] = "contrib"
;projects[views][version] = "3.0-alpha1"

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
;projects[google_analytics][version] = "1.0"

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
projects[doune][download][branch] = "DRUPAL-7--2"
; Tag new release at end of project
; projects[doune][download][tag] = "DRUPAL-7--2-0"

