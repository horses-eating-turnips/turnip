; Panels and related modules.
core = "7.x"
api = 2

projects[fieldable_panels_panes][version] = "1.5"
; Title should be displayed using view mode settings.
; https://drupal.org/comment/7876047#comment-7876047
projects[fieldable_panels_panes][patch][] = "https://drupal.org/files/fieldable_panels_panes-title_use_view_modes-2092477-2.patch"

projects[panelizer][version] = "3.1"
; Fix access logic error: https://drupal.org/node/2024831#comment-8496667
projects[panelizer][patch][] = "https://drupal.org/files/issues/panelizer-node-access-2024831-04_2.patch"
; Fix button that should not be displayed: https://drupal.org/node/2199859#comment-8496751
projects[panelizer][patch][] = "https://drupal.org/files/issues/panelizer-ipe-integration-fix-2199859-01.patch"

; Pull latest panels including many fixes since 3.3.
projects[panels][download][branch] = "7.x-3.x"
projects[panels][download][revision] = "2bb470e"
; PHP 5.4+ fix: https://drupal.org/comment/8262211#comment-8262211
projects[panels][patch][] = "https://drupal.org/files/issues/panels-array_diff_assoc-1762290-22.patch"

projects[panels_breadcrumbs][version] = "2.1"
