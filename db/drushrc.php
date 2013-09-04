<?php

/**
 * @file
 * The drushrc file used by `db_dump.sh`.
 */

/**
 * Customize this associative array with your own tables. This is the list of
 * tables whose *data* is skipped by the 'sql-dump' and 'sql-sync' commands when
 * a structure-tables-key is provided. You may add new tables to the existing
 * array or add a new element.
 */
$options['structure-tables'] = array(
  'opensourcery' => array(
    'cache',
    'cache_block',
    'cache_bootstrap',
    'cache_field',
    'cache_filter',
    'cache_form',
    'cache_image',
    'cache_menu',
    'cache_page',
    'cache_path',
    'cache_token',
    'history',
    'sessions',
    'watchdog'
  ),
);
