<?php
/**
 * @author Bruno Massa http://drupal.org/user/67164
 * @file
 * Use Open Flash Chart on your site.
 *
 * @note only hooks are here.
 */

/**
 * Implementation of hook_charts_info().
 *
 * Its a Charts module hook. It defines almost all aspects
 * of a chart provider, like its name, what types of charts
 * it can perform and what are the restrictions.
 */
function openflashchart_charts_info() {
  return array(
    'openflashchart' => array(
      'file'    => drupal_get_path('module', 'openflashchart') . '/openflashchart.inc',
      'name'    => t('Open Flash Chart'),
      'render'  => '_openflashchart_charts_render',
      'types'   => array('line2D', 'vbar2D', 'vbar3D', 'pie2D'),
    ),
  );
}
