<?php

class views_tooltip_handler_field_tooltip extends views_handler_field_custom {
  function option_definition() {
    $options = parent::option_definition();

    $options['tooltip_text'] = array('default' => '', 'translatable' => TRUE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['tooltip_text'] = array(
      '#type' => 'textarea',
      '#title' => t('Tooltip text'),
      '#description' => t('The text to display for the tooltip of this field. You may include HTML. You may enter data from this view as per the "Replacement patterns" below.'),
      '#default_value' => $this->options['tooltip_text'],
    );
  }

  function render_text($alter) {
    // First, render the content, passing it to upstream renderer.
    $content = parent::render_text($alter);

    // Then render the rest.
    $tokens = $this->get_render_tokens($alter);
    $theme_variables = array(
      'tooltip' => str_replace(array_keys($tokens), array_values($tokens), $this->options['tooltip_text']),
      'content' => $content,
    );
    return theme('views_tooltip', $theme_variables);
  }
}
