// $Id: README.txt,v 1.1.2.7 2009/07/09 22:50:46 deciphered Exp $

The FileField Paths module extends the default functionality of Drupals core
Upload module, the FileField module and many other File Upload modules by adding
the ability to use node tokens in destination paths and filenames.

In simple terms, FileField Paths allows you to automatically sort and rename
your uploaded files using token based replacement patterns to maintain a nice
clean filesystem.

FileField Paths was written and is maintained by Stuart Clark (deciphered).
- http://stuar.tc/lark


Features
--------------------------

* Configurable file paths now use node tokens instead of user tokens.
* Configurable filenames.
* Support for:
  * Drupal core Upload module.
  * FileField module.
  * ImageField module.
  * ImageField Crop module.
  * Image module.
  * Comment Upload module.
  * Audio module.
* File path and filename cleanup options:
  * Filter out words and punctuation by taking advantage of the Pathauto module.
  * Convert unicode characters into US-ASCII with the Transliteration module.
* Automatically updates unprocessed file paths in the node body on save.
* Retroactive updates - rename and/or move previously uploaded files (Use with
  caution)


Required Modules
--------------------------

* Token             - http://drupal.org/project/token


Recommended Modules
--------------------------

* ImageField Tokens - http://drupal.org/project/imagefield_tokens
* File Aliases      - http://drupal.org/project/file_aliases
* Pathauto          - http://drupal.org/project/pathauto
* Transliteration   - http://drupal.org/project/transliteration


Usage/Configuration
--------------------------

Once installed, FileField Paths needs to be configured for each file type you
wish to use.

* FileField/ImageField module

  Settings can be found on the fields configuration page in 'Page settings >
  FileField Path settings'.
  http://[www.yoursite.com/path/to/drupal]/admin/content/node-type/[node-type]/fields/[field-name] 


* Upload module

  Settings can be found on the content types configuration page in 'Workflow
  settings > Upload Path settings'.
  http://[www.yoursite.com/path/to/drupal]/admin/content/node-type/[node-type]


* Image module

  Settings can be found on the Images configuration page in 'Image file settings
  > Image Path settings'.
  http://[www.yoursite.com/path/to/drupal]/admin/settings/image


* Comment Upload module

  Settings can be found on the content types configuration page in 'Comment
  settings > Comment Upload Path settings'.
  http://[www.yoursite.com/path/to/drupal]/admin/content/node-type/[node-type]


* Audio module

  Settings can be found on the content types configuration page in 'Audio Path
  settings'.
  http://[www.yoursite.com/path/to/drupal]/admin/content/node-type/audio


Frequently Asked Questions
--------------------------

Q. Aren't tokens already supported in the FileField module?

A. Only User tokens are supported in the FileField module.

   Node tokens allow you to use the Node ID, Node Title, Node creation date and
   much more in your directory/filenames where User tokens are very limited.


Q. Why are my files uploaded to 'files/[nid]' instead of 'files/1'?

A. When you are creating or updating a node the full values for the Node tokens
   may not yet be known by Drupal, so the FileField Paths module will upload
   your files to a temporary path based on your filepath pattern ('files/[nid]')
   and then once you save the node and Drupal is provided with the Node tokens
   values the file will be moved to the appropriate location.


Q. Why is there a warning on the 'Retroactive updates' feature?

A. Retroactive updates will go through every single node of the particular
   content type and move and/or rename the files.

   While there have been no reports of errors caused by the feature, it is quite
   possible that the moving/renaming of these files could break links. It is
   strongly advised that you only use this functionality on your developmental
   servers so that you can make sure not to introduce any linking issues.

