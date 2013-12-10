; Base image module set
core = "7.x"
api = 2

projects[caption_filter][download][branch] = "7.x-1.x"
projects[caption_filter][download][revision] = "6ab247f6c"
; https://drupal.org/node/1432092#comment-7541749
projects[caption_filter][patch][] = "https://drupal.org/files/tinymce-button--1432092--17.patch"

projects[file_entity][version] = "2.0-alpha3"

projects[image_resize_filter][version] = "1.13"
; Images not resizing if path has query string: https://drupal.org/node/1929710
projects[image_resize_filter][patch][] = https://drupal.org/files/image_resize_filter-remove-query-string-1929710-8.patch

projects[media][version] = "2.0-alpha3"
; http://drupal.org/node/1278180#comment-5085370
projects[media][patch][] = "http://drupal.org/files/media-embed-library-resize.patch"
; Image resize filter fails with media https://drupal.org/node/1411340
projects[media][patch][] = "https://drupal.org/files/media-resize_images_in_wysiwyg-1411340-71.patch"

; Required for multiple file uploads via plupload at `file/add`.
projects[multiform][version] = "1.0"

projects[plupload][version] = "1.3"
; http://drupal.org/node/1476830#comment-6026232
projects[plupload][patch][] = "http://drupal.org/files/media-upload-widget--1476830-2.patch"

libraries[plupload][download][type] = "get"
libraries[plupload][download][url] = "http://cloud.github.com/downloads/moxiecode/plupload/plupload_1_5_1_1.zip"
libraries[plupload][download][destination] = "libraries"
libraries[plupload][download][directory_name] = "plupload"
