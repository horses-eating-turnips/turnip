; Panels and related modules.
core = "7.x"
api = 2

projects[fieldable_panels_panes][version] = "1.5"

projects[panelizer][version] = "3.1"

projects[panels][version] = "3.3"
; https://drupal.org/node/1632898#comment-6412840 - This was commited Nov 16, 2012 and should be removed when updating to 3.4
projects[panels][patch][] = "https://drupal.org/files/panels-n1632898-15.patch"
; https://drupal.org/node/1613402#comment-6374724 - This was commited Feb 1, 2012 and should be removed when updating to 3.4
projects[panels][patch][] = "https://drupal.org/files/panels_ipe_fix_ajax_1613402-9.patch"
; Panels IPE Save Drops Context Specified in Page Manager https://drupal.org/node/1772834 - This was commited Sep 24, 2012 and should be removed when updating to 3.4
projects[panels][patch][] = "https://drupal.org/files/1772834-fix-lost-context-6.patch"

projects[panels_breadcrumbs][version] = "2.1"
