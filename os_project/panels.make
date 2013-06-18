; Panels and related modules.
core = "7.x"
api = 2

projects[fieldable_panels_panes][version] = "1.4"

projects[panelizer][version] = "3.1"

projects[panels][version] = "3.3"
; https://drupal.org/node/1632898#comment-6412840 - This was commited Nov 16, 2012 and should be removed when updating to 3.4
projects[panels][patch][] = "https://drupal.org/files/panels-n1632898-15.patch"

projects[panels_breadcrumbs][version] = "2.0"
