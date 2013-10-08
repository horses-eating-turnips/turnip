core = 7.x

projects[title][download][branch] = "7.x-1.x"
projects[title][download][revision] = "2c11348"
; https://drupal.org/node/2098097#comment-7900137 - Fix translated titles not saving
projects[title][patch][] = "https://drupal.org/files/title-entity-sync-2098097-01.patch"

projects[entity_translation][download][branch] = "7.x-1.x"
projects[entity_translation][download][revision] = "7846c18"

projects[facetapi_i18n][version] = "1.0-beta2"
; https://drupal.org/node/2101713#comment-7920267
projects[facetapi_i18n][patch][] = "https://drupal.org/files/facetapi-i18n-field-2101713-01.patch"

projects[i18n][version] = "1.10"

projects[variable][version] = "2.3"
