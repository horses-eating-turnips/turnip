<?php
// $Id: maintenance-page.tpl.php 5 2009-06-10 01:11:31Z jhedstrom $

/**
 * @file maintenance-page.tpl.php
 *
 * Theme implementation to display a single Drupal page while off-line.
 *
 * All the available variables are mirrored in page.tpl.php. Some may be left
 * blank but they are provided for consistency.
 *
 *
 * @see template_preprocess()
 * @see template_preprocess_maintenance_page()
 */
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language; ?>" lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>">

<head>
  <title><?php print $head_title; ?></title>
  <?php print $head; ?>
  <?php print $styles; ?>
  <?php print $scripts; ?>
</head>
<body class="<?php print $body_classes; ?>">
  <div id="page">
    <div id="header">

      <div id="skip-nav"><a href="#content"><?php print t('Skip to Main Content'); ?></a></div>

      <div id="logo-title">

        <?php if (!empty($logo)): ?>
          <a href="<?php print $base_path; ?>" title="<?php print t('Home'); ?>" rel="home">
            <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" id="logo" />
          </a>
        <?php endif; ?>

        <div id="name-and-slogan">

        <?php if (!empty($site_name)): ?>
          <div id="site-name"><strong>
            <a href="<?php print $base_path; ?>" title="<?php print t('Home'); ?>" rel="home">
              <?php print $site_name; ?>
            </a>
          </strong></div>
        <?php endif; ?>

        <?php if (!empty($site_slogan)): ?>
          <div id="site-slogan">
            <?php print $site_slogan; ?>
          </div>
        <?php endif; ?>

        </div> <!-- /name-and-slogan -->

      </div> <!-- /logo-title -->

      <?php if (!empty($header)): ?>
        <div id="header-region">
          <?php print $header; ?>
        </div> <!-- /header-region -->
      <?php endif; ?>

    </div> <!-- /header -->

    <div id="container" class="clear-block">

      <?php if (!empty($left)): ?>
        <div id="sidebar-left" class="column sidebar">
          <?php print $left; ?>
        </div> <!-- /sidebar-left -->
      <?php endif; ?>

      <div id="main" class="column"><div id="squeeze" class="clear-block">
        <?php if (!empty($content_top)): ?>
          <div id="content-top"><?php print $content_top; ?></div>
        <?php endif; ?>
        <div id="content">
          <?php if (!empty($title)): ?>
            <h1 class="title"><?php print $title; ?></h1>
          <?php endif; ?>
          <?php print $messages; ?>
          <?php print $content; ?>
        </div> <!-- /content -->
        <?php if (!empty($content_bottom)): ?>
          <div id="content-bottom"><?php print $content_bottom; ?></div>
        <?php endif; ?>
      </div></div> <!-- /squeeze /main -->

      <?php if (!empty($right)): ?>
        <div id="sidebar-right" class="column sidebar">
          <?php print $right; ?>
        </div> <!-- /sidebar-right -->
      <?php endif; ?>

    </div> <!-- /container -->

    <?php if ($footer || $footer_message): ?>
      <div id="footer-wrapper"><div id="footer">

        <?php if ($footer_message): ?>
          <div id="footer-message"><?php print $footer_message; ?></div>
        <?php endif; ?>

        <?php print $footer; ?>

      </div></div> <!-- /#footer, /#footer-wrapper -->
    <?php endif; ?>

  </div> <!-- /page -->

  <?php if ($closure_region): ?>
    <div id="closure-blocks"><?php print $closure_region; ?></div>
  <?php endif; ?>

  <?php print $closure; ?>

</body>
</html>
