; This is the actual project make file that should be edited for a
; given project. This text should be replaced with a brief description
; of the project.
api = 2

; Set contrib directory.
defaults[projects][subdir] = "contrib"

; Drupal core.
core = "7.x"
projects[drupal][type] = "core"
projects[drupal][version] = "7.23"
; Ensure plain text fields evaluate line breaks.
projects[drupal][patch][] = "http://drupal.org/files/text-plain-1152216-24.patch"
; Resolve php notice thrown by the way PHP 5.4 handles array indexes vs 5.3. https://drupal.org/node/1824820#comment-6656728
projects[drupal][patch][] = "https://drupal.org/files/string-offset-cast-1824820-2.patch"

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

; Project-specific modules, and overrides.

; Follow
projects[follow][version] = "2.0-alpha1"

; Mollom
projects[mollom][version] = "2.7"

; Libraries.
projects[libraries][version] = "2.1"

; Libraries

; Profiler
libraries[profiler][download][type] = "git"
libraries[profiler][download][branch] = "7.x-2.x"
libraries[profiler][download][revision] = "4c131d2"
; http://drupal.org/node/1853290#comment-6787544: Add support for term parents.
libraries[profiler][patch][] = "http://drupal.org/files/1853290-support-term-parent-2.patch"
; http://drupal.org/node/1921880#comment-7086568: Add support for heirarchical menus on node creation.
libraries[profiler][patch][] = "http://drupal.org/files/profiler_heirarchical_node_menu-1921880-1.patch"

