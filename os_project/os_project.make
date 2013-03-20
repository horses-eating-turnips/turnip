; This is the actual project make file that should be edited for a
; given project. This text should be replaced with a brief description
; of the project.
api = 2

; Set contrib directory.
defaults[projects][subdir] = "contrib"

core = "7.x"
projects[drupal][type] = "core"
projects[drupal][version] = "7.21"
; Make taxonomy permissions use vocabulary machine name instead of vid
projects[drupal][patch][] = "http://drupal.org/files/995156-31_portable_taxonomy_permissions-D7-15.patch"

; Base installation profile
includes[base] = "base.make"

; Image handling. Comment this out if you don't need any image handling.
includes[images] = "images.make"

; Uncomment this to enable demo content. Do not use on production.
;includes[demo] = "demo.make"

; Uncomment to use Panels.
;includes[panels] = "panels.make"

; OpenSourcery base feature.
projects[os_base][subdir] = "stock"
projects[os_base][type] = "module"
projects[os_base][download][type] = "git"
projects[os_base][download][url] = "git://github.com/opensourcery/os_base.git"
projects[os_base][download][branch] = "7.x-1.x"
; Tag new release at end of project
; projects[os_base][download][tag] = "7.x-1.0-alpha1"

; Apache Solr Search
; TODO potentially switch from this module to search_api module.
; SolrPHPClient is NOT required (all code is in the module).
; Be sure to use Solr 3.5 or higher. Also remember to copy the module's conf files.
; http://drupalcode.org/project/apachesolr.git/blob_plain/refs/heads/7.x-1.x:/README.txt
projects[apachesolr][version] = "1.0-rc3"

; Google analytics
projects[google_analytics][version] = "1.2"

; Menu Block
projects[menu_block][version] = "2.3"

; Mollom
projects[mollom][version] = "2.0"

; Libraries.
projects[libraries][version] = "2.0"

; Libraries

; Profiler
libraries[profiler][download][type] = "get"
libraries[profiler][download][url] = "http://ftp.drupal.org/files/projects/profiler-7.x-2.0-beta1.tar.gz"
; http://drupal.org/node/1165672#comment-4696748: Don't disable blocks
libraries[profiler][patch][] = "http://drupal.org/files/issues/0001-Issue-1165672-don-t-disable-blocks.patch"

; swfobject, JS library for embedding Flash content
;libraries[swfobject][download][type] = "get"
;libraries[swfobject][download][url] = "http://swfobject.googlecode.com/files/swfobject_2_2.zip"
;libraries[swfobject][destination] = "libraries"
;libraries[swfobject][directory_name] = "swfobject"

; Project-specific modules, and overrides.

