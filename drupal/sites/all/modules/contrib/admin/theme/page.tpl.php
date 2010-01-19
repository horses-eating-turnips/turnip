<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">
  <head>
    <?php print $head ?>
    <?php print $styles ?>
    <!--[if lt IE 7]>
      <style type="text/css" media="screen">@import "<?php echo $base_path, $directory; ?>/ie6.css";</style>
    <![endif]-->
    <title><?php print $head_title ?></title>
  </head>
  <body class='admin <?php print $body_classes ?>'>

  <?php print $admin ?>

  <?php if ($help): ?>
    <div id='help' class='reverse limiter'>
      <div class='help-label'><?php print t('Help') ?></div>
      <div class='help-wrapper clear-block limiter'><?php print $help; ?></div>
    </div>
  <?php endif; ?>

  <div id='branding' class='clear-block reverse limiter'>
    <?php if ($site_name): ?><h1 class='site-name'><?php print l(truncate_utf8($site_name, 25, FALSE, TRUE), '<front>'); ?></h1><?php endif; ?>
    <?php if ($breadcrumb) print $breadcrumb; ?>
    <div class='right'>
      <?php if ($help): ?><?php print l(t('Need help?'), 'admin/help', array('attributes' => array('class' => 'help-toggle'))) ?><?php endif; ?>
      <?php if ($search_box): ?><div class="block block-theme"><?php print $search_box ?></div><?php endif; ?>
    </div>
  </div>

  <?php
    $primary_links = admin_navigation_primary();
    $secondary_links = admin_navigation_secondary();
    $primary_local_tasks = menu_primary_local_tasks();
    $secondary_local_tasks = menu_secondary_local_tasks();
  ?>

  <?php if ($title): ?>
    <div id='page-title' class='clear-block limiter reverse'>
      <?php if ($secondary_links): ?><?php print l(t('Expand'), $_GET['q'], array('attributes' => array('class' => 'subnav-toggle'))) ?><?php endif; ?>
      <h2 class='page-title'><?php print $title ?></h2>
      <?php if ($primary_local_tasks): ?><ul class='tabs primary'><?php print $primary_local_tasks ?></ul><?php endif; ?>
      <?php if (!empty($context_links)): ?><div class='tools'><?php print $context_links ?></div><?php endif; ?>
    </div>
  <?php endif; ?>

  <div id='page'>

    <?php if ($secondary_links): ?>
      <div id='secondary-links'><?php print theme('links', $secondary_links) ?></div>
    <?php endif; ?>

    <?php if ($secondary_local_tasks): ?><ul class='tabs secondary'><?php print $secondary_local_tasks ?></ul><?php endif; ?>

    <?php if ($primary_links): ?>
      <div id='primary-links' class='reverse clear-block'><?php print theme('links', $primary_links) ?></div>
    <?php endif; ?>

    <div id='content' class='clear-block'>
      <?php if ($show_messages && $messages): ?>
        <div id='console' class='clear-block'>
          <?php if ($show_messages && $messages): print $messages; endif; ?>
        </div>
      <?php endif; ?>
      <?php print $content ?>
    </div>

    <div id="footer">
      <?php print $feed_icons ?>
      <?php print $footer ?>
      <?php print $footer_message ?>
    </div>

  </div>

  <?php print $scripts ?>
  <?php print $closure ?>

  </body>
</html>
