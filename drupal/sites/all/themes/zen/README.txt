Full documentation on the Zen theme can be found in Drupal's Handbook:
  http://drupal.org/node/193318

Excellent documentation on Drupal theming can be found in the Theme Guide:
  http://drupal.org/theme-guide


Installation:

  1. Download Zen from http://drupal.org/project/zen

  2. Unpack the downloaded file, take the entire zen folder (which includes
     the README.txt file, a zen_classic folder, etc.) and place it in your
     Drupal installation under one of the following locations:
       sites/all/themes
         making it available to the default Drupal site and to all Drupal sites
         in a multi-site configuration
       sites/default/themes
         making it available to only the default Drupal site
       sites/example.com/themes
         making it available to only the example.com site if there is a
         sites/example.com/settings.php configuration file

  3. Log in as an administrator on your Drupal site and go to Administer > Site
     building > Themes (admin/build/themes) and make Zen or one of its
     sub-themes the default theme.

Build your own sub-theme:

  IMPORTANT: In Drupal 6, the theme system caches template files and which theme
  functions should be called. What that means is if you add a new theme or
  preprocess fuction to your template.php file or add a new template (.tpl.php)
  file to your sub-theme, you will need to rebuild the "theme registry."
  See http://drupal.org/node/173880#theme-registry

  The base Zen theme is designed to be easily extended by its sub-themes. You
  shouldn't modify any of the CSS or PHP files in the zen/ folder; but instead
  you should create a sub-theme of zen which is located in a folder outside of
  the root zen/ folder. The examples below assume zen and your sub-theme will be
  installed in sites/all/themes/.

    Why? To learn why you shouldn't modify any of the files in the zen/ folder,
    see http://drupal.org/node/245802

  1. Copy the STARTERKIT folder out of the zen/ folder and rename it to be your
     new sub-theme. IMPORTANT: Only lowercase letters and underscores should be
     used for the name of your sub-theme.

     For example, copy the sites/all/themes/zen/STARTERKIT folder and rename it
     as sites/all/themes/foo.

       Why? Each theme should reside in its own folder. Unlike in Drupal 5,
       sub-themes can (and should) reside in a folder separate from their base
       theme.

  2. In your new sub-theme folder, rename the STARTERKIT.info file to the name
     of your new sub-theme. Then edit the .info file by changing any occurrence
     of STARTERKIT with the name of your sub-theme and editing the name and
     description field.

     For example, rename the foo/STARTERKIT.info file to foo/foo.info. Edit the
     foo.info file and change "STARTERKIT.css" to "foo.css", change "name = Zen
     Themer's Starter Kit" to "name = Foo", and change "description = Read..."
     to "description = A Zen sub-theme".

       Why? The .info file describes the basic things about your theme: its
       name, description, features, template regions, CSS files, and javascript
       files. See the Drupal 6 Theme Guide for more info:
       http://drupal.org/node/171205

  3. If you want a liquid layout for your theme, copy the layout-liquid.css from
     the zen/zen folder and place it in your sub-theme's folder. If you want a
     fixed-width layout for your theme, copy the layout-fixed.css from the
     zen/zen folder and place it in your sub-theme's folder. Rename the layout
     stylesheet to "layout.css".

     For example, copy zen/zen/layout-fixed.css and rename it as foo/layout.css.
     Note that the .info file already has an entry for your layout.css file.

       Why? In Drupal 6 theming, if you want to modify a stylesheet included
       by the base theme or by a module, you should copy the stylsheet from the
       base theme or module's directory to your sub-theme's directory and then
       add the stylesheet to your .info file. See the Drupal 6 Theme Guide for
       more info: http://drupal.org/node/171209

  4. Copy the zen stylesheet from the zen folder and place it in your
     sub-theme's folder. Rename it to be the name of your sub-theme.

     For example, copy zen/zen/zen.css and rename it as foo/foo.css. Note that
     the .info file already has an entry for your foo.css file and that your
     .info file removes the base theme's zen.css file.

  5. Copy the print stylesheet from the zen folder and place it in your
     sub-theme's folder.

     For example, copy zen/zen/print.css to foo/print.css. Note that the .info
     file already has an entry for your print.css file.

  6. Copy the html-elements stylesheet from the zen folder and place it in your
     sub-theme's folder.

     For example, copy zen/zen/html-elements.css to foo/html-elements.css. Note
     that the .info file already has an entry for your html-elements.css file.

  7. Edit the template.php and theme-settings.php files in your sub-theme's
     folder; replace ALL occurances of "STARTERKIT" with the name of your
     sub-theme.

     For example, edit foo/template.php and foo/theme-settings.php and replace
     "STARTERKIT" with "foo".

  8. Log in as an administrator on your Drupal site and go to Administer > Site
     building > Themes (admin/build/themes) and enable your new sub-theme.

  Optional:

  9. MODIFYING ZEN CORE STYLESHEETS:
     If you decide you want to modify any of the other stylesheets in the zen
     folder, copy them to your sub-theme's folder before making any changes.
     Also, be sure the new stylesheet is included in your .info file and that
     you have rebuilt the theme registry.

     For example, copy zen/zen/wireframes.css to foo/wireframes.css. Then edit
     foo/foo.info and uncomment this line to activate it:
       ;stylesheets[all][]  = block-editing.css
     to:
       stylesheets[all][]   = block-editing.css

  10. MODIFYING ZEN CORE TEMPLATE FILES:
     If you decide you want to modify any of the .tpl.php template files in the
     zen folder, copy them to your sub-theme's folder before making any changes.
     And then rebuild the theme registry.

     For example, copy zen/zen/page.tpl.php to foo/page.tpl.php.

  11. THEMEING DRUPAL'S SEARCH FORM:
     Copy the search-theme-form.tpl.php template file from the modules/search/
     folder and place it in your sub-theme's folder. And then rebuild the theme
     registry.

     You can find a full list of Drupal templates that you can override on:
     http://drupal.org/node/190815

       Why? In Drupal 6 theming, if you want to modify a template included
       by a module, you should copy the template file from the module's
       directory to your sub-theme's directory and then rebuild the theme
       registry. See the Drupal 6 Theme Guide for more info:
       http://drupal.org/node/173880

  12. FURTHER EXTENSIONS OF YOUR SUB-THEME:
     Discover further ways to extend your sub-theme by reading Zen's
     documentation online at:
       http://drupal.org/node/193318
     and Drupal 6's Theme Guide online at:
       http://drupal.org/theme-guide
