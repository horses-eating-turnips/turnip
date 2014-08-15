; Base theme make file, including theme-related modules
core = "7.x"
api = 2

; Modules

; Blockify
projects[blockify][version] = "1.2"

; Chosen
projects[chosen][version] = "2.0-beta4"

; Magic
projects[magic][version] = "1.5"

; Modernizr
projects[modernizr][version] = "3.2"

; Bedrock
projects[bedrock][version] = "1.0-alpha3"

; Libraries

; Chosen
libraries[chosen][download][type] = "get"
libraries[chosen][download][url] = "https://github.com/harvesthq/chosen/releases/download/1.0.0/chosen_v1.0.0.zip"

; Modernizr
libraries[modernizr][download][type] = "get"
libraries[modernizr][download][url] = "http://modernizr.com/downloads/modernizr-latest.js"
libraries[modernizr][download][filename] = "modernizr.js"
libraries[modernizr][destination] = "libraries"
libraries[modernizr][directory_name] = "modernizr"

; Alphecca Sass Framework
libraries[alphecca][download][type] = "git"
libraries[alphecca][download][tag] = "0.1.0"
libraries[alphecca][download][url] = "https://github.com/opensourcery/alphecca.git"
libraries[alphecca][destination] = "themes/custom/THEME/vendor"
libraries[alphecca][download][directory_name] = "alphecca"

; Themes

; Aurora
projects[aurora][type] = "theme"
projects[aurora][version] = "3.2"
