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

  return $pages;

}
