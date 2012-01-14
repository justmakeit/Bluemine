<?php
// An example themes/garland/theme-settings.php file.

function jqm_form_system_theme_settings_alter(&$form, $form_state) {
  $jqm_options = array('a' => 'a', 'b' => 'b', 'c' => 'c', 'd' => 'd', 'e' => 'e');
  
  $jqm_elements = array(
    'page',
    'content',
    'listview',
    'radio', 
    'radios', 
    'select', 
    'checkbox',
  );
  
  $form['jqm_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('jQM settings'),
    '#description' => t('Modify the theme-wide settings for various page elements here.'),
  );
  
  foreach ($jqm_elements as $jqm_element) {
    $form['jqm_settings']['jqm_' . $jqm_element . '_data_theme'] = array(
      '#type' => 'select',
      '#options' => $jqm_options,
      '#title' => ucwords($jqm_element),
      '#default_value' => theme_get_setting('jqm_' . $jqm_element . '_data_theme', 'jqm'),
    );
  }
}
