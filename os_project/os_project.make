; This is the actual project make file that should be edited for a
; given project. This text should be replaced with a brief description
; of the project.
api = 2

; Set contrib directory.
defaults[projects][subdir] = "contrib"

; Drupal core.
core = "7.x"
projects[drupal][type] = "core"
projects[drupal][version] = "7.28"
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

; Theme and theme-related modules.
includes[theme] = "theme.make"

; Project-specific modules, and overrides.

; Superfish
projects[superfish][download][branch] = "7.x-1.x"
projects[superfish][download][revision] = "c799462"

; Follow
projects[follow][version] = "2.0-alpha1"

; Mollom
projects[mollom][version] = "2.10"


;; Libraries.
projects[libraries][version] = "2.2"

; Libraries
libraries[superfish][download][type] = "git"
libraries[superfish][download][branch] = "master"
libraries[superfish][download][revision] = "2670a36"
libraries[superfish][download][url] = "https://github.com/mehrpadin/Superfish-for-Drupal.git"
libraries[superfish][destination] = "libraries"
libraries[superfish][directory_name] = "superfish"

; Profiler
libraries[profiler][download][type] = "git"
libraries[profiler][download][branch] = "7.x-2.x"
libraries[profiler][download][revision] = "2ed2140"
; https://drupal.org/comment/7878427#comment-787842 Add support for FPP.
libraries[profiler][patch][] = "https://drupal.org/files/fieldable-panels-panes-support-2093337-01.patch"
