DESCRIPTION
===========

The admin module provides UI improvements to the standard Drupal admin
interface. It implements some of the ideas being explored for
usability improvements in Drupal 7.


INSTALLATION
============

1. Install & enable the module.

2. If you do not have an admin theme selected, admin will provide its
   admin theme as the default.

3. To make use of the admin header within your theme, you must add the
   following line to your theme's page.tpl.php file immediately
   following the <body> tag:

   <?php if (!empty($admin)) print $admin; ?>

4. Admin makes 2 different permissions available. In addition to using
   these permissions to enable/disable admin features for different
   roles, specific themes can specify their compatibility (see
   'Theme compatibility' below).

   'admin inline': Grant users access to inline contextual links for
     editing nodes, views, blocks, etc.

   'admin menu': Grant users access to the admin header/menu.


GRAPHICS
========

The icons used by the admin module were designed by Young Hahn and
AJ Ashton specifically for use with Drupal's admin interface.
The iconset is available for use under a dual GPL/BSD license,
meaning you may choose the license which is most appropriate for
your project.


THEME COMPATIBILITY
===================

A theme can specify its compatibility with different features
provided by the admin module in its .info file. If no compatibility
flag is set, admin assumes the theme is compatible with all of its
features.

To disable the admin menu when using your theme:

  admin[admin menu] = 0

To disable the admin inline links when using your theme:

  admin[admin inline] = 0


API & HOOKS
===========

There is a small API included in admin for adding inline links to
various objects. The hooks are parallel to hook_link() and
hook_link_alter(), except that they are used for admin inline links
only. The admin-edit, admin-delete, and admin-configure classes
are available for rendering links with icons (more to come).

- hook_admin_link($type, $object)

  Should return a $links array suitable for theming by theme_links().

- hook_admin_link_alter(&$links, $type, $object)

  A typical drupal_alter() hook that takes the links array, as well
  as object type and object as parameters.


CONTRIBUTORS
============
Young Hahn young@developmentseed.org
AJ Ashton aj@developmentseed.org
