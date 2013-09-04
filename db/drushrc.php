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
    'cache_entity_file',
    'cache_entity_message',
    'cache_entity_message_type',
    'cache_entity_message_type_category',
    'cache_entity_node',
    'cache_entity_og_membership',
    'cache_entity_og_membership_type',
    'cache_entity_profile2',
    'cache_entity_taxonomy_term',
    'cache_entity_taxonomy_vocabulary',
    'cache_entity_user',
    'cache_field',
    'cache_filter',
    'cache_form',
    'cache_image',
    'cache_libraries',
    'cache_media_xml',
    'cache_menu',
    'cache_page',
    'cache_path',
    'cache_rules',
    'cache_token',
    'cache_update',
    'cache_views',
    'cache_views_data',
    'history',
    'sessions',
    'watchdog'
  ),
);
