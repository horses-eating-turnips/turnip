; Base image module set
core = "7.x"
api = 2

projects[image_resize_filter][subdir] = "contrib"
projects[image_resize_filter][version] = "1.13"

projects[insert][subdir] = "contrib"
projects[insert][version] = "1.1"

projects[media][subdir] = "contrib"
projects[media][version] = "1.0-rc2"

libraries[plupload][download][type] = "get"
libraries[plupload][download][url] = "http://cloud.github.com/downloads/moxiecode/plupload/plupload_1_4_3_2.zip"
libraries[plupload][download][destination] = "libraries"
libraries[plupload][download][directory_name] = "plupload"
