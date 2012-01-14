<?php


function jqm_process_page(&$variables) {
  // make sure we have the library installed
  if (module_exists('jquerymobile')) {
    jquerymobile_add();
  }
  else {
    drupal_set_message('jQuery Mobile is not installed. This theme will not function as expected without it. <a href="http://drupal.org/projects/jquerymobile" target="_blank">Download the jQuery Mobile module.</a>', 'error');
  }
  // set defaults for the main page if they haven't been set elsewhere
  if (!isset($variables['jqm_page_id'])) {
    $variables['jqm_page_id'] = 'main-page' . str_replace('/', '-', request_uri());
  }
  if (!isset($variables['page_data_theme'])) {
    $variables['page_data_theme'] = theme_get_setting('jqm_page_data_theme');
  }

  if (!isset($variables['jqm_content_data_theme'])) {
    $variables['jqm_content_data_theme'] = theme_get_setting('jqm_content_data_theme');
  }
}

/**
 * Implements theme_menu_tree().
 * @todo for now, making all menus listviews; this will not be tenable forever
 */
function jqm_menu_tree($variables) {
  return '<ul class="menu clearfix" data-role="listview" data-inset="true" data-theme="' . theme_get_setting('jqm_listview_data_theme') . '">' . $variables['tree'] . '</ul>';
}

/**
 * theme override; adds ability to set jqm data-theme on select elements
 */
function jqm_select($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id', 'name', 'size'));
  _form_set_class($element, array('form-select'));
  
  // add data-theme
  $element['#attributes']['data-theme'] = isset($element['#attributes']['data-theme']) ? $element['#attributes']['data-theme'] : theme_get_setting('jqm_select_data_theme');

  return '<select' . drupal_attributes($element['#attributes']) . '>' . form_select_options($element) . '</select>';
}

/**
 * theme override: adds ability to set jqm data-theme on checkbox elements
 */
function jqm_checkbox($variables) {
  $element = $variables['element'];
  $t = get_t();
  $element['#attributes']['type'] = 'checkbox';
  element_set_attributes($element, array('id', 'name', '#return_value' => 'value'));

  // Unchecked checkbox has #value of integer 0.
  if (!empty($element['#checked'])) {
    $element['#attributes']['checked'] = 'checked';
  }
  _form_set_class($element, array('form-checkbox'));
  
  // add data-theme
  $element['#attributes']['data-theme'] = isset($element['#attributes']['data-theme']) ? $element['#attributes']['data-theme'] : theme_get_setting('jqm_checkbox_data_theme');
  

  return '<input' . drupal_attributes($element['#attributes']) . ' />';
}

/**
 * theme override: adds ability to set jqm data-theme on radio elements
 */
function jqm_radio($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'radio';
  element_set_attributes($element, array('id', 'name', '#return_value' => 'value'));

  if (isset($element['#return_value']) && $element['#value'] !== FALSE && $element['#value'] == $element['#return_value']) {
    $element['#attributes']['checked'] = 'checked';
  }
  _form_set_class($element, array('form-radio'));
  
  // add data-theme
  $element['#attributes']['data-theme'] = isset($element['#attributes']['data-theme']) ? $element['#attributes']['data-theme'] : theme_get_setting('jqm_radio_data_theme');

  return '<input' . drupal_attributes($element['#attributes']) . ' />';
}


/**
 * theme override: adds ability to set jqm data-theme
 */
function jqm_radios($variables) {
  $element = $variables['element'];
  $attributes = array();
  if (isset($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  $attributes['class'] = 'form-radios';
  if (!empty($element['#attributes']['class'])) {
    $attributes['class'] .= ' ' . implode(' ', $element['#attributes']['class']);
  }  
  
    // add data-theme
    $attributes['data-theme'] = isset($element['#attributes']['data-theme']) ? $element['#attributes']['data-theme'] : theme_get_setting('jqm_radio_data_theme');
    
    // group radios
    $attributes['data-role'] = 'controlgroup';
  
  return '<div' . drupal_attributes($attributes) . '>' . (!empty($element['#children']) ? $element['#children'] : '') . '</div>';
}

/**
 * theme override; remove the wrapper and don't place the textarea js
 */
function jqm_textarea($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id', 'name', 'cols', 'rows'));
  _form_set_class($element, array('form-textarea'));


  $output = '<textarea' . drupal_attributes($element['#attributes']) . '>' . check_plain($element['#value']) . '</textarea>';
  return $output;
}

/**
 * theme override: rework the vertical tab group as a jQM accordion group
 */
function jqm_vertical_tabs($variables) {
  $element = $variables['element'];
  $output = '<h2 class="element-invisible">' . t('Vertical Tabs') . '</h2>';
  $output .= '<div class="jqm-collapsible-set" data-role="collapsible-set">' . $element['#children'] . '</div>';
  return $output;
}



/**
 * Theme override: if the fieldset is collapsible, modify the output to make it a jqm collapsible region
 *
 * Returns HTML for a fieldset form element and its children.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #attributes, #children, #collapsed, #collapsible,
 *     #description, #id, #title, #value.
 *
 * @ingroup themeable
 */
function jqm_fieldset($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id'));
  _form_set_class($element, array('form-wrapper'));

  $output = '';
  if ($element['#collapsible']) {
    $element['#attributes']['data-role'] = 'collapsible';
    if ($element['#collapsed']) {
      $element['#attributes']['data-collapsed'] = 'true';
    }
    $output .= '<div' . drupal_attributes($element['#attributes']) . '>';
    if (!empty($element['#title'])) {
      $output .= '<h3>' . $element['#title'] . '</h3>';
    }
  }
  else {
    $output .= '<fieldset' . drupal_attributes($element['#attributes']) . '>';
    if (!empty($element['#title'])) {
      // Always wrap fieldset legends in a SPAN for CSS positioning.
      $output .= '<legend><span class="fieldset-legend">' . $element['#title'] . '</span></legend>';
    }
  }
  $output .= '<div class="fieldset-wrapper">';
  if (!empty($element['#description'])) {
    $output .= '<div class="fieldset-description">' . $element['#description'] . '</div>';
  }
  $output .= $element['#children'];
  if (isset($element['#value'])) {
    $output .= $element['#value'];
  }
  $output .= '</div>';
  if ($element['#collapsible']) {
    $output .= "</div>\n";
  }
  else {
    $output .= "</fieldset>\n";
  }
  return $output;
}


/* retheme local task output
 * these provide 'tabs' at the top navbar
 * this is borrowed wholesale from JAM by Eric Duran @ericduran
 */

function jqm_menu_local_task($variables) {
  $link = $variables['element']['#link'];
  $link_text = $link['title'];

  if (!empty($variables['element']['#active'])) {
    // If the link does not contain HTML already, check_plain() it now.
    // After we set 'html'=TRUE the link will not be sanitized by l().
    if (empty($link['localized_options']['html'])) {
      $link['title'] = check_plain($link['title']);
    }
    $active = '';
    $link['localized_options']['html'] = TRUE;
    $link_text = t('!local-task-title!active', array('!local-task-title' => $link['title'], '!active' => $active));
  }
  if (!empty($variables['element']['#active'])) {
    $link['localized_options']['attributes']['class'][] = 'ui-btn-active';
    $link = l($link_text, $link['href'], $link['localized_options']);
  }
  else {
    $link = l($link_text, $link['href'], $link['localized_options']);
  }

  return '<li>' . $link . "</li>\n";
}

function jqm_menu_local_tasks(&$variables) {
  $output = '';

  if (!empty($variables['primary'])) {
    $variables['primary']['#prefix'] = '<ul>';
    $variables['primary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['primary']);
  }
  if (!empty($variables['secondary'])) {
    $variables['secondary']['#prefix'] = '<ul>';
    $variables['secondary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['secondary']);
  }

  return $output;
}

/**
 * Returns HTML for a single local action link.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: A render element containing:
 *     - #link: A menu link array with 'title', 'href', and 'localized_options'
 *       keys.
 *
 * @ingroup themeable
 */
function jqm_menu_local_action($variables) {
  $link = $variables['element']['#link'];

  if (isset($link['localized_options'])) {
    $link['localized_options']['attributes'] = array('data-rel' => 'dialog', "data-transition" => "pop");
    $options = $link['localized_options'];
  }
  else {
    $options = array('attributes' => array('data-rel' => 'dialog', "data-transition" => "pop"));
  }

  $output = '<li>';
  if (isset($link['href'])) {
    $output .= l($link['title'], $link['href'], $options);
  }
  elseif (!empty($link['localized_options']['html'])) {
    $output .= $link['title'];
  }
  else {
    $output .= check_plain($link['title']);
  }
  $output .= "</li>\n";

  return $output;
}