<?php
/**
 * @file
 * os_base.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function os_base_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'sub_page';
  $page->task = 'page';
  $page->admin_title = 'Add a sub page';
  $page->admin_description = '';
  $page->path = 'node/%node/add-sub-page';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'node_type',
        'settings' => array(
          'type' => array(
            'page' => 'page',
          ),
        ),
        'context' => 'argument_nid_1',
      ),
      1 => array(
        'name' => 'perm',
        'settings' => array(
          'perm' => 'create page content',
        ),
        'context' => 'logged-in-user',
      ),
      2 => array(
        'name' => 'node_menu_depth',
        'settings' => array(
          'menu' => 'main-menu',
          'menu_depth' => 'p3',
        ),
        'context' => 'argument_nid_1',
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array(
    'type' => 'tab',
    'title' => 'Add Sub Page',
    'name' => 'navigation',
    'weight' => '10',
    'parent' => array(
      'type' => 'none',
      'title' => '',
      'name' => 'navigation',
      'weight' => '0',
    ),
  );
  $page->arguments = array(
    'node' => array(
      'id' => 1,
      'identifier' => 'Node: ID',
      'name' => 'nid',
      'settings' => array(),
    ),
  );
  $page->conf = array(
    'admin_paths' => TRUE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_sub_page_menu_context';
  $handler->task = 'page';
  $handler->subtask = 'sub_page';
  $handler->handler = 'menu_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Context Admin',
    'no_blocks' => FALSE,
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'context_admin_options' => 'node_create_menu',
    'context_admin_options_items' => 'page',
    'context_admin_sub_page' => 1,
    'submitted_context' => 'argument_nid_1',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_menu_depth',
          'settings' => array(
            'menu' => 'main-menu',
            'menu_depth' => 'p3',
          ),
          'context' => 'argument_nid_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'or',
    ),
  );
  $page->default_handlers[$handler->name] = $handler;
  $pages['sub_page'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'welcome_page';
  $page->task = 'page';
  $page->admin_title = 'Welcome page';
  $page->admin_description = '';
  $page->path = 'welcome';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_welcome_page_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'welcome_page';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'slate';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'column_left' => NULL,
      'column_right' => NULL,
      'main_content' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-1';
    $pane->panel = 'main_content';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => 'Welcome to turnip message',
      'title' => '',
      'body' => '<h2 style="box-sizing: border-box; margin-top: 1em; margin-bottom: 16px; line-height: 1.225; font-size: 1.75em; position: relative; padding-bottom: 0.3em; border-bottom-width: 1px; border-bottom-style: solid; border-bottom-color: rgb(238, 238, 238); color: rgb(51, 51, 51); font-family: \'Helvetica Neue\', Helvetica, \'Segoe UI\', Arial, freesans, sans-serif;">Welcome to Turnip by OpenSourcery</h2><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 16px; color: rgb(51, 51, 51); font-family: \'Helvetica Neue\', Helvetica, \'Segoe UI\', Arial, freesans, sans-serif; font-size: 16px; line-height: 25.600000381469727px;">Turnip is OpenSourcery\'s Drupal starting kit. Using a Drush Make workflow, only custom modules, features and themes are committed to the repository, which allows for teams to quickly get up to speed and collaborate on the important parts of the project at hand. It includes a starting framework for using Behat for behavior driven development. Each site is built as an installation profile.</p><h2 style="box-sizing: border-box; margin-top: 1em; margin-bottom: 16px; line-height: 1.225; font-size: 1.75em; position: relative; padding-bottom: 0.3em; border-bottom-width: 1px; border-bottom-style: solid; border-bottom-color: rgb(238, 238, 238); color: rgb(51, 51, 51); font-family: \'Helvetica Neue\', Helvetica, \'Segoe UI\', Arial, freesans, sans-serif;">Edit this page!</h2><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 16px; color: rgb(51, 51, 51); font-family: \'Helvetica Neue\', Helvetica, \'Segoe UI\', Arial, freesans, sans-serif; font-size: 16px; line-height: 25.600000381469727px;">To edit this page, click the contextual link on the upper-right side of the page (it looks like a little gear). Then edit \'Welcome to turnip message\'. Make the changes you want, click finish, then update &amp; save. Make it your own. &nbsp;This page is a panel, so add more content to it. &nbsp;Like a slideshow, or a login block.</p><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 16px; color: rgb(51, 51, 51); font-family: \'Helvetica Neue\', Helvetica, \'Segoe UI\', Arial, freesans, sans-serif; font-size: 16px; line-height: 25.600000381469727px;"><a href="https://camo.githubusercontent.com/019ec9cd644f5a076857c72b76a9685b436ef5d2/68747470733a2f2f7261772e6769746875622e636f6d2f6f70656e736f7572636572792f7475726e69702f372e782f7475726e69702e706e67" style="box-sizing: border-box; color: rgb(65, 131, 196); text-decoration: none; background-image: initial; background-attachment: initial; background-size: initial; background-origin: initial; background-clip: initial; background-position: initial; background-repeat: initial;" target="_blank"><img alt="Turnip" data-canonical-src="https://raw.github.com/opensourcery/turnip/7.x/turnip.png" src="https://camo.githubusercontent.com/019ec9cd644f5a076857c72b76a9685b436ef5d2/68747470733a2f2f7261772e6769746875622e636f6d2f6f70656e736f7572636572792f7475726e69702f372e782f7475726e69702e706e67" style="box-sizing: border-box; border: 0px; max-width: 100%;"></a></p><h2 style="box-sizing: border-box; margin-top: 1em; margin-bottom: 16px; line-height: 1.225; font-size: 1.75em; position: relative; padding-bottom: 0.3em; border-bottom-width: 1px; border-bottom-style: solid; border-bottom-color: rgb(238, 238, 238); color: rgb(51, 51, 51); font-family: \'Helvetica Neue\', Helvetica, \'Segoe UI\', Arial, freesans, sans-serif;">Drush Make</h2><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 16px; color: rgb(51, 51, 51); font-family: \'Helvetica Neue\', Helvetica, \'Segoe UI\', Arial, freesans, sans-serif; font-size: 16px; line-height: 25.600000381469727px;">There are several bundled make files:</p><ul class="task-list" style="box-sizing: border-box; padding: 0px 0px 0px 2em; margin-top: 0px; margin-bottom: 16px; color: rgb(51, 51, 51); font-family: \'Helvetica Neue\', Helvetica, \'Segoe UI\', Arial, freesans, sans-serif; font-size: 16px; line-height: 25.600000381469727px;"><li style="box-sizing: border-box;"><code style="box-sizing: border-box; font-family: Consolas, \'Liberation Mono\', Menlo, Courier, monospace; font-size: 14px; padding: 0.2em 0px; margin: 0px; border-top-left-radius: 3px; border-top-right-radius: 3px; border-bottom-right-radius: 3px; border-bottom-left-radius: 3px; background-color: rgba(0, 0, 0, 0.0392157);">my_profile.make</code>&nbsp;- This gets renamed to the installation profile\'s machine name and should contain modules than relate specifically to your project.</li><li style="box-sizing: border-box;"><code style="box-sizing: border-box; font-family: Consolas, \'Liberation Mono\', Menlo, Courier, monospace; font-size: 14px; padding: 0.2em 0px; margin: 0px; border-top-left-radius: 3px; border-top-right-radius: 3px; border-bottom-right-radius: 3px; border-bottom-left-radius: 3px; background-color: rgba(0, 0, 0, 0.0392157);">base.make</code>&nbsp;- common modules and libraries</li><li style="box-sizing: border-box;"><code style="box-sizing: border-box; font-family: Consolas, \'Liberation Mono\', Menlo, Courier, monospace; font-size: 14px; padding: 0.2em 0px; margin: 0px; border-top-left-radius: 3px; border-top-right-radius: 3px; border-bottom-right-radius: 3px; border-bottom-left-radius: 3px; background-color: rgba(0, 0, 0, 0.0392157);">images.make</code>&nbsp;- Media module and other image-related modules</li><li style="box-sizing: border-box;"><code style="box-sizing: border-box; font-family: Consolas, \'Liberation Mono\', Menlo, Courier, monospace; font-size: 14px; padding: 0.2em 0px; margin: 0px; border-top-left-radius: 3px; border-top-right-radius: 3px; border-bottom-right-radius: 3px; border-bottom-left-radius: 3px; background-color: rgba(0, 0, 0, 0.0392157);">panels.make</code>&nbsp;- Panels modules related dependencies</li><li style="box-sizing: border-box;"><code style="box-sizing: border-box; font-family: Consolas, \'Liberation Mono\', Menlo, Courier, monospace; font-size: 14px; padding: 0.2em 0px; margin: 0px; border-top-left-radius: 3px; border-top-right-radius: 3px; border-bottom-right-radius: 3px; border-bottom-left-radius: 3px; background-color: rgba(0, 0, 0, 0.0392157);">theme.make</code>&nbsp;- Dependencies for Arcturus/Aurora subthemes.</li></ul><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 16px; color: rgb(51, 51, 51); font-family: \'Helvetica Neue\', Helvetica, \'Segoe UI\', Arial, freesans, sans-serif; font-size: 16px; line-height: 25.600000381469727px;">If using dev versions of modules, specific commit hashes are preferable in the make files, rather than the more general dev branch.</p><h2 style="box-sizing: border-box; margin-top: 1em; margin-bottom: 16px; line-height: 1.225; font-size: 1.75em; position: relative; padding-bottom: 0.3em; border-bottom-width: 1px; border-bottom-style: solid; border-bottom-color: rgb(238, 238, 238); color: rgb(51, 51, 51); font-family: \'Helvetica Neue\', Helvetica, \'Segoe UI\', Arial, freesans, sans-serif;">Installation profile</h2><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 16px; color: rgb(51, 51, 51); font-family: \'Helvetica Neue\', Helvetica, \'Segoe UI\', Arial, freesans, sans-serif; font-size: 16px; line-height: 25.600000381469727px;">By building the site out as an installation profile, funcitonality can easily be tracked in commit logs.</p><p style="box-sizing: border-box; margin-top: 0px; margin-bottom: 16px; color: rgb(51, 51, 51); font-family: \'Helvetica Neue\', Helvetica, \'Segoe UI\', Arial, freesans, sans-serif; font-size: 16px; line-height: 25.600000381469727px;">The&nbsp;<a href="http://drupal.org/project/profiler" style="box-sizing: border-box; color: rgb(65, 131, 196); text-decoration: none; background-image: initial; background-attachment: initial; background-size: initial; background-origin: initial; background-clip: initial; background-position: initial; background-repeat: initial;">Profiler</a>&nbsp;library is used for creating placeholder nodes, users and taxonomy terms, as well as setting variables that don\'t make sense to commit to feature modules.</p><h3 style="box-sizing: border-box; margin-top: 1em; margin-bottom: 16px; line-height: 1.43; font-size: 1.5em; position: relative; color: rgb(51, 51, 51); font-family: \'Helvetica Neue\', Helvetica, \'Segoe UI\', Arial, freesans, sans-serif;">Adding contrib modules</h3><p style="box-sizing: border-box; margin-top: 0px; color: rgb(51, 51, 51); font-family: \'Helvetica Neue\', Helvetica, \'Segoe UI\', Arial, freesans, sans-serif; font-size: 16px; line-height: 25.600000381469727px; margin-bottom: 0px !important;">If you need to install a module that\'s&nbsp;<strong style="box-sizing: border-box;">not</strong>&nbsp;part of Turnip, add the module to the my_profile.make file (e.g.<code style="box-sizing: border-box; font-family: Consolas, \'Liberation Mono\', Menlo, Courier, monospace; font-size: 14px; padding: 0.2em 0px; margin: 0px; border-top-left-radius: 3px; border-top-right-radius: 3px; border-bottom-right-radius: 3px; border-bottom-left-radius: 3px; background-color: rgba(0, 0, 0, 0.0392157);">projects[bad_judgement][version] = 1.0-rc39</code>). For more information on drush make, please refer to&nbsp;<a href="http://www.slideshare.net/rupl/drush-make-install-drupal-like-a-pro" style="box-sizing: border-box; color: rgb(65, 131, 196); text-decoration: none; background-image: initial; background-attachment: initial; background-size: initial; background-origin: initial; background-clip: initial; background-position: initial; background-repeat: initial;">http://www.slideshare.net/rupl/drush-make-install-drupal-like-a-pro</a></p>',
      'format' => 'full_html',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content['new-1'] = $pane;
    $display->panels['main_content'][0] = 'new-1';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-1';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['welcome_page'] = $page;

  return $pages;

}
