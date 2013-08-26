; Demo content make file
core = "7.x"
api = 2

projects[entity_dependency][subdir] = "development"
projects[entity_dependency][download][branch] = "7.x-1.x"
projects[entity_dependency][download][revision] = "7ca711a"
; Patch for entity-reference dependencies.
; http://drupal.org/node/1545278
projects[entity_dependency][patch][] = "http://drupal.org/files/entity-dependency-entityreference-1545278-2.patch"

projects[uuid][subdir] = "development"
projects[uuid][download][branch] = "7.x-1.x"
projects[uuid][download][revision] = "4bbf92d"
;; Patching for UUIDs not resolved/ignored properly on presave/insert.
;; https://drupal.org/node/1390708#comment-7525819
;; NOTE: This patch allows us to export field collections except if the FC
;; contains an entity refererence. Use discretion when deciding to use This
;; patch or not.
projects[uuid][patch][] = "https://drupal.org/files/1390708-10-uuid-field-insert.patch"

projects[deploy][subdir] = "development"
projects[deploy][version] = "2.0-alpha2"
