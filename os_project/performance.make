; High-performance related modules
core = "7.x"
api = 2

projects[advagg][version] = "2.7"

projects[expire][version] = "2.0-rc3"

projects[memcache][version] = "1.2"

projects[purge][version] = "1.6"

; Varnish is an alternative to Purge, which selectively deletes only modified
; items from Varnish's cache.  See: https://www.drupal.org/node/1686298
;projects[varnish][version] = "1.0-beta2"