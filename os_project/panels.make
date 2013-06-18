; Panels and related modules.
core = "7.x"
api = 2

; Uncomment fieldable_panels_panes once we have a custom module to create
; some panel pane entity bundles. See
; http://drupalcode.org/project/fieldable_panels_panes.git/blob/refs/heads/7.x-1.x:/README.txt
; Latest: 7.x-1.0 + 7 commits.
;projects[fieldable_panels_panes][revision] = "57000ec268603f43e2ea50817682b54659c33651"

projects[panelizer][version] = "3.1"

projects[panels][version] = "3.3"
; https://drupal.org/node/1632898#comment-6412840 - This was commited Nov 16, 2012 and should be removed when updating to 3.4
projects[panels][patch][] = "https://drupal.org/files/panels-n1632898-15.patch"

projects[panels_breadcrumbs][version] = "1.6"
