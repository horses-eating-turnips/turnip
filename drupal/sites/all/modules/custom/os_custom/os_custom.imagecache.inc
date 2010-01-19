<?php

// $Id: os_custom.imagecache.inc 833 2009-06-16 22:51:45Z jhedstrom $

/**
 * @file
 * Default ImageCache presets for OpenSourcery customization module.
 */

/**
 * Define ImageCache default presets.
 */
function _os_custom_imagecache_default_presets() {
  $presets = array();
  $presets['medium-content'] = array(
    'presetname' => 'medium-content',
    'actions' => 
    array(
      array(
        'weight' => '0',
        'module' => 'imagecache',
        'action' => 'imagecache_scale',
        'data' => 
        array(
          'width' => '350',
          'height' => '',
          'upscale' => 0,
        ),
      ),
    ),
  );
  return $presets;
}