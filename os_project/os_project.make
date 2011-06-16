; This is the actual project make file that should be edited for a
; given project. This text should be replaced with a brief description
; of the project.
api = 2

; Base installation profile
projects[opensourcery_install][type] = "profile"
projects[opensourcery_install][download][type] = "git"
projects[opensourcery_install][download][url] = "git@github.com:opensourcery/opensourcery_install.git"
projects[opensourcery_install][download][branch] = "7.x"
;projects[opensourcery_install][download][tag] = "7.x-1.0"

; OpenSourcery administration feature
projects[os_admin][subdir] = "stock"
projects[os_admin][type] = "module"
projects[os_admin][download][type] = "git"
projects[os_admin][download][url] = "git://github.com/opensourcery/os_admin.git"
projects[os_admin][download][branch] = "7.x-1.x"
; Tag new release at end of project
; projects[os_admin][download][tag] = "7.x-1.0-alpha1"

; OpenSourcery base feature.
projects[os_base][subdir] = "stock"
projects[os_base][type] = "module"
projects[os_base][download][type] = "git"
projects[os_base][download][url] = "git://github.com/opensourcery/os_base.git"
projects[os_base][download][branch] = "7.x-1.x"
; Tag new release at end of project
; projects[os_base][download][tag] = "7.x-1.0-alpha1"

; Views
;projects[views][subdir] = "contrib"
;projects[views][version] = "3.0-beta3"

; Mollom
;projects[mollom][subdir] = "contrib"
;projects[mollom][version] = "1.0"

; Google analytics
;projects[google_analytics][subdir] = "contrib"
;projects[google_analytics][version] = "1.2"

; Apache Solr Search
; TODO potentially switch from this module to search_api module.
;projects[apachesolr][subdir] = "contrib"
;projects[apachesolr][version] = "1.0-beta8"
;libraries[SolrPHPClient][download][type] = "svn"
;libraries[SolrPHPClient][download][url] = "http://solr-php-client.googlecode.com/svn/trunk/"
;libraries[SolrPHPClient][download][revision] = "22"
;libraries[SolrPHPClient][destination] = "modules/contrib/apachesolr/"
;libraries[SolrPHPClient][directory_name] = "SolrPhpClient"

; Project-specific modules, and overrides.

; Modules required by the Doune theme.
projects[elements][subdir] = "contrib"
projects[elements][version] = "1.2"

projects[html5_tools][subdir] = "contrib"
projects[html5_tools][type] = "module"
projects[html5_tools][download][type] = "git"
projects[html5_tools][download][revision] = "6fab84596aad3045126070f812b2dc3e6ce8803c"

; Base theme: Create and specify a tag at the *end* of the project.
projects[doune][type] = "theme"
projects[doune][download][type] = "git"
projects[doune][download][url] = "git://github.com/opensourcery/doune.git"
projects[doune][download][branch] = "7.x-2.x"
; Tag new release at end of project
; projects[doune][download][tag] = "7.x-2.0-alpha1"
