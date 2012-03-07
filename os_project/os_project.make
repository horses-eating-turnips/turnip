; This is the actual project make file that should be edited for a
; given project. This text should be replaced with a brief description
; of the project.
api = 2

core = "7.x"
projects[drupal][type] = "core"
projects[drupal][version] = "7.12"
; Make taxonomy permissions use vocabulary machine name instead of vid
projects[drupal][patch][] = "http://drupal.org/files/issues/995156-5_portable_taxonomy_permissions.patch"

; Base installation profile
includes[base] = "base.make"

; Image handling. Comment this out if you don't need any image handling.
includes[images] = "images.make"

; OpenSourcery base feature.
projects[os_base][subdir] = "stock"
projects[os_base][type] = "module"
projects[os_base][download][type] = "git"
projects[os_base][download][url] = "git://github.com/opensourcery/os_base.git"
projects[os_base][download][branch] = "7.x-1.x"
; Tag new release at end of project
; projects[os_base][download][tag] = "7.x-1.0-alpha1"

; Views
projects[views][subdir] = "contrib"
projects[views][version] = "3.1"

; Mollom
;projects[mollom][subdir] = "contrib"
;projects[mollom][version] = "1.1"

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

; swfobject, JS library for embedding Flash content
;libraries[swfobject][download][type] = "get"
;libraries[swfobject][download][url] = "http://swfobject.googlecode.com/files/swfobject_2_2.zip"
;libraries[swfobject][destination] = "libraries"
;libraries[swfobject][directory_name] = "swfobject"

; Profiler
libraries[profiler][download][type] = "get"
libraries[profiler][download][url] = "http://ftp.drupal.org/files/projects/profiler-7.x-2.0-beta1.tar.gz"
; http://drupal.org/node/1165672#comment-4696748: Don't disable blocks
libraries[profiler][patch][] = "http://drupal.org/files/issues/0001-Issue-1165672-don-t-disable-blocks.patch"

; Project-specific modules, and overrides.
projects[bean][subdir] = "contrib"
projects[bean][version] = "1.0-rc1"

projects[beanslide][type] = "module"
projects[beanslide][subdir] = "contrib"
projects[beanslide][download][type] = "git"
projects[beanslide][download][branch] = "7.x-1.x"

libraries[jquery.vegas][download][type] = "get"
libraries[jquery.vegas][download][url] = "https://github.com/jaysalvat/vegas/zipball/v1.2"

projects[os_blog][subdir] = "stock"
projects[os_blog][type] = "module"
projects[os_blog][download][type] = "git"
projects[os_blog][download][url] = "git://github.com/opensourcery/os_blog.git"
projects[os_blog][download][branch] = "7.x-1.x"

projects[os_event][subdir] = "stock"
projects[os_event][type] = "module"
projects[os_event][download][type] = "git"
projects[os_event][download][url] = "git://github.com/opensourcery/os_event.git"
projects[os_event][download][branch] = "7.x-1.x"

projects[date][subdir] = "contrib"
projects[date][version] = "2.2"

projects[fullcalendar][subdir] = "contrib"
projects[fullcalendar][version] = "2.0-beta3"

projects[context][subdir] = "contrib"
projects[context][version] = "3.0-beta2"

projects[context_admin][subdir] = "contrib"
projects[context_admin][version] = "1.1"

projects[entity][subdir] = "contrib"
projects[entity][version] = "1.0-rc1"

projects[views_bulk_operations][subdir] = "contrib"
projects[views_bulk_operations][version] = "3.0-rc1"

libraries[fullcalendar][download][type] = "get"
libraries[fullcalendar][download][url] = "http://arshaw.com/fullcalendar/downloads/fullcalendar-1.5.1.zip"

; Omega base theme
projects[delta][subdir] = "contrib"
projects[delta][version] = "3.0-beta8"
projects[omega][version] = "3.0"

; Lovejoy theme for initial development.
projects[lovejoy][type] = "theme"
projects[lovejoy][download][type] = "git"
projects[lovejoy][download][url] = "git://github.com/opensourcery/lovejoy.git"
