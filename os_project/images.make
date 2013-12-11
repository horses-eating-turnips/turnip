; Base image module set
core = "7.x"
api = 2

projects[caption_filter][download][branch] = "7.x-1.x"
projects[caption_filter][download][revision] = "b8097ee"

projects[image_resize_filter][version] = "1.13"
; Images not resizing if path has query string: https://drupal.org/node/1929710
projects[image_resize_filter][patch][] = https://drupal.org/files/image_resize_filter-remove-query-string-1929710-8.patch

projects[plupload][version] = "1.4"

libraries[plupload][download][type] = "get"
libraries[plupload][download][url] = "http://plupload.com/downloads/plupload_1_5_7.zip"

; Scald.
projects[scald][download][branch] = "7.x-1.x"
projects[scald][download][revision] = "a01013f"

projects[scald_file][version] = "1.0-beta3"
projects[scald_gallery][version] = "2.1"

libraries[galleria][download][type] = "get"
libraries[galleria][download][url] = "http://galleria.io/static/galleria-1.3.3.zip"

; Optional: Super neat JS-only PDF viewer support.
projects[scald_pdf][version] = "1.2"
projects[pdf][version] = "1.4"

libraries[pdf.js][download][type] = "git"
libraries[pdf.js][download][url] = "https://github.com/mozilla/pdf.js.git"
libraries[pdf.js][download][branch] = "master"
; No reason for this specific commit beyond it was the latest.
libraries[pdf.js][download][revision] = "d627741"
