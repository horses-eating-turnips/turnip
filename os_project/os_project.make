; This is the actual project make file that should be edited for a
; given project. This text should be replaced with a brief description
; of the project.
api = 2

; Set contrib directory.
defaults[projects][subdir] = "contrib"

core = "7.x"
projects[drupal][type] = "core"
projects[drupal][version] = "7.22"
; Make taxonomy permissions use vocabulary machine name instead of vid
projects[drupal][patch][] = "http://drupal.org/files/995156-31_portable_taxonomy_permissions-D7-15.patch"
; Ensure plain text fields evaluate line breaks.
projects[drupal][patch][] = "http://drupal.org/files/text-plain-1152216-24.patch"

; Base installation profile
includes[base] = "base.make"

; Image handling. Comment this out if you don't need any image handling.
includes[images] = "images.make"

; Uncomment this to enable demo content. Do not use on production.
;includes[demo] = "demo.make"

; Uncomment to use Panels.
;includes[panels] = "panels.make"

; Uncomment to use Solr Search.
; includes[solr] = "solr.make"

; OpenSourcery base feature.
projects[os_base][subdir] = "stock"
projects[os_base][type] = "module"
projects[os_base][download][type] = "git"
projects[os_base][download][url] = "git://github.com/opensourcery/os_base.git"
projects[os_base][download][branch] = "7.x-1.x"
projects[os_base][download][tag] = "7.x-1.0"

; Follow
projects[follow][version] = "2.0-alpha1"

; Google analytics
projects[google_analytics][version] = "1.3"

; Menu Block
projects[menu_block][version] = "2.3"

; Mollom
projects[mollom][version] = "2.6"

; Libraries.
projects[libraries][version] = "2.1"

; Libraries

; Profiler
libraries[profiler][download][type] = "get"
libraries[profiler][download][url] = "http://ftp.drupal.org/files/projects/profiler-7.x-2.0-beta1.tar.gz"
; http://drupal.org/node/1165672#comment-4696748: Don't disable blocks
libraries[profiler][patch][] = "http://drupal.org/files/issues/0001-Issue-1165672-don-t-disable-blocks.patch"
; http://drupal.org/node/1853290#comment-6787544: Add support for term parents.
libraries[profiler][patch][] = "http://drupal.org/files/1853290-support-term-parent-2.patch"
; http://drupal.org/node/1921880#comment-7086568: Add support for heirarchical menus on node creation.
libraries[profiler][patch][] = "http://drupal.org/files/profiler_heirarchical_node_menu-1921880-1.patch"
; http://drupal.org/node/1955904#comment-7233174: Add support for block creation.
libraries[profiler][patch][] = "http://drupal.org/files/add_block_support-1955904.patch"

; swfobject, JS library for embedding Flash content
;libraries[swfobject][download][type] = "get"
;libraries[swfobject][download][url] = "http://swfobject.googlecode.com/files/swfobject_2_2.zip"
;libraries[swfobject][destination] = "libraries"
;libraries[swfobject][directory_name] = "swfobject"

; Project-specific modules, and overrides.

