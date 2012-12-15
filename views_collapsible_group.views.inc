<?php

/**
 * @file
 * Contain all the code to alter views plugins.
 */

/**
 * Implements hook_views_plugins_alter().
 */
function views_collapsible_group_views_plugins_alter(&$plugins) {
  $path = drupal_get_path('module', 'views_collapsible_group');
  $plugins['style']['default']['handler'] = 'views_plugin_style_collapsible_group_defualt';
  $plugins['style']['default']['path'] = $path;
}
