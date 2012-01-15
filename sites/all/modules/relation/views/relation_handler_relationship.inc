<?php

/**
 * @file
 * Views relationship support.
 */

class relation_handler_relationship extends views_handler_relationship {
  /**
   * Define r_index option.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['r_index'] = array('default' => -1);
    return $options;
  }

  /**
   * Let the user choose r_index.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $options = $this->options_form_summary_options();
    if ($this->definition['directional']) {
      $form['r_index'] = array(
        '#type' => 'select',
        '#options' => $options,
        '#title' => t('Position of the relationship base'),
        '#default_value' => $this->options['r_index'],
        // check_plain()'d in the definition.
        '#description' => t('Select whether the entity you are adding the relationship to is source or target of !relation_type_label relation.', array('!relation_type_label' => $this->definition['label'])),
      );
    }
  }

  /**
   * Return the main options, which are shown in the summary title.
   */
  function options_form_summary_options() {
    return $this->definition['directional'] ? array(
      -1 => t('Any'),
      0 => t('Source'),
      1 => t('Target'),
    ) : array();
  }
}

class relation_handler_endpoint_endpoint_join extends views_join {
  /**
   * Build the SQL for the join this object represents.
   *
   * This does an endpoint to endpoint join relative to a relation.
   */
  function build_join($select_query, $table, $view_query) {
    $entity_type_field_name = _field_sql_storage_columnname('endpoints', 'entity_type');
    $r_index_field_name = _field_sql_storage_columnname('endpoints', 'r_index');

    $entity_type_right = $this->definition['entity_type_right'];
    $relation_type = $this->definition['relation_type'];

    // Note: the Views naming convention on left versus right is opposite the
    // actual order in the join clause.

    // The aliased name of the existing endpoint table we are joining to.
    $l = $this->left_table;
    // The aliased name of the current endpoint table.
    $r = $table['alias'];

    // Self-join the endpoints table but grab a different endpoint (r_index).
    $conditions = "$r.entity_id = $l.entity_id AND $r.$r_index_field_name != $l.$r_index_field_name";
    if ($this->options['r_index'] > -1) {
      // Grab a specific index.
      $conditions .= " AND $l.$r_index_field_name = " . $this->options['r_index'];
    }
    // Restrict the join to the proper entity type and bundle.
    $conditions .= " AND $r.$entity_type_field_name = '$entity_type_right' AND $r.bundle = '$relation_type'";

    // Add a self-join.
    $select_query->addJoin($this->type, $table['table'], $table['alias'], $conditions);
  }
}

/**
 * Join handler which is used to join from relation table to the field_data_endpoints table.
 */
class relation_handler_relation_endpoint_join extends views_join {
  /**
   * Construct the views_join object.
   *
   * This does a relation to endpoint join.
   */
  function construct($table = NULL, $left_table = NULL, $left_field = NULL, $field = NULL, $extra = array(), $type = 'LEFT') {
    parent::construct($table, $left_table, $left_field, $field, $extra, $type);
    $r_index_field_name = _field_sql_storage_columnname('endpoints', 'r_index');
    if ($this->options['r_index'] > -1) {
      $this->extra = array(array('field' => $r_index_field_name, 'value' => $this->options['r_index']));
    }
  }
}
