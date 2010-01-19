// $Id: README.txt 844 2009-07-08 01:04:33Z jhedstrom $

The ImageField Tokens module extends the default functionality of ImageField
module by adding the ability to use node tokens in the ALT and Title text.

ImageField Tokens was written and is maintained by Stuart Clark (deciphered).
- http://stuar.tc/lark


Features
--------------------------

* Configurable ALT and Title text now use node tokens instead of user tokens.
* Support for Imagefield Crop
* Support for Image FUpload.


Required Modules
--------------------------

* FileField Paths - http://drupal.org/project/filefield_paths
* ImageField      - http://drupal.org/project/imagefield


Frequently Asked Questions
--------------------------

Q. Aren't tokens already supported in the ImageField module?

A. Only User tokens are supported in the ImageField module.

   Node tokens allow you to use the Node ID, Node Title, Node creation date and
   much more in your ALT/Title text where User tokens are very limited.


Q. Is there going to be a Drupal 5 version?

A. Yes, I have already completed a Development build for Drupal 5, however it is
   dependent on a patch for ImageField 5.x-2.x-dev.

   The sooner it is reviewed/tested and committed the sooner the Drupal 5
   version of ImageField Tokens will be released, so if you have the know how,
   head over to the issue: http://drupal.org/node/406874
