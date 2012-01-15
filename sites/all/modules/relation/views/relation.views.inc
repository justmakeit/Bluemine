<?php

/**
 * @file
 * Views support.
 */

/**
 * Implements hook_views_data().
 */
function relation_views_data() {
  // Define the base group of this table.
  $data['relation']['table']['group']  = t('Relation');

  // Advertise this table as a possible base table
  $data['relation']['table']['base'] = array(
    'field' => 'rid',
    'title' => t('Relation'),
    'weight' => -10,
  );
  $data['relation']['table']['entity type'] = 'relation';
  $data['relation']['rid'] = array(
    'title' => t('Rid'),
    'help' => t('The relation ID.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['relation']['relation_type'] = array(
    'title' => t('Relation type'),
    'help' => t('The relation type.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_in_operator',
      'options callback' => 'relation_get_types_options',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['relation']['vid'] = array(
    'title' => t('Vid'),
    'help' => t('The relation revision ID.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['relation']['uid'] = array(
    'title' => t('Uid'),
    'help' => t('The relation uid.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'label' => 'relation author',
      'title' => t('Relation Author'),
      'base' => 'users',
      'base field' => 'uid',
    ),
  );

  $data['relation']['created'] = array(
    'title' => t('Create Date'),
    'help' => t('The date when the relation was created.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['relation']['changed'] = array(
    'title' => t('Change Date'),
    'help' => t('The date when the relation was last changed.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['relation']['arity'] = array(
    'title' => t('Number of rows'),
    'help' => t('The number of rows in this relation.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Define the base group of this table.
  $data['field_data_endpoints']['table']['group'] = t('Relation');
  $data['field_data_endpoints']['table']['join'] = array();

  // Find out which entity type has which base table.
  $entity_infos = entity_get_info();
  $entity_tables = array();
  foreach ($entity_infos as $entity_type => $entity_info) {
    if (isset($entity_info['base table'])) {
      $entity_tables[$entity_type] = $entity_info['base table'];
    }
  }
  $field = field_info_field('endpoints');
  $relation_data_table_name = _field_sql_storage_tablename($field);
  $entity_id_field_name = _field_sql_storage_columnname('endpoints', 'entity_id');
  $entity_type_field_name = _field_sql_storage_columnname('endpoints', 'entity_type');
  // Build the relations between the different tables.
  $types = relation_get_types();
  foreach ($types as $type => $relation_type) {
    $target_index = $relation_type->directional ? 'target_bundles' : 'source_bundles';
    foreach ($relation_type->source_bundles as $source_bundle) {
      $source_bundle = explode(':', $source_bundle, 2);
      $entity_type_left = $source_bundle[0];
      $relationship_field = $entity_infos[$entity_type_left]['entity keys']['id'];
      $base_table_left = $entity_tables[$entity_type_left];
      $t_arguments = array(
        '@left' => $entity_type_left,
        '@relation_type_label' => $relation_type->label,
      );
      foreach ($relation_type->$target_index as $target_bundle) {
        $target_bundle = explode(':', $target_bundle, 2);
        $entity_type_right = $target_bundle[0];
        $base_table_right = $entity_tables[$entity_type_right];
        $t_arguments['@right'] = $entity_type_right;
        // Define [join and] relationship from relation to endpoints.
        $data['relation']['relation_base_' . $type . '_right_endpoints'] = array(
          'title' => t('@relation_type_label -> endpoints[@relation_type_label]', $t_arguments),
          'help' => t('Relation table to endpoints table using "@relation_type_label" relation', $t_arguments),
          'relationship' => array(
            // relation_handler_relationship::options_form() relies on this check_plain().
            'label' => check_plain('Endpoints::' . $relation_type->label),
            'base' => 'field_data_endpoints',
            'base field' => 'entity_id',
            'real field' => 'rid',
            'handler' => 'relation_handler_relationship', // To choose the r_index option.
            'relation_type' => $type, // USE THIS as bundle
            'entity_type_right' => $entity_type_right, // Use this as endpoint_entity_type.
            'directional' => $relation_type->directional,
            'max_arity' => $relation_type->max_arity,
            'join_handler' => 'relation_handler_relation_endpoint_join', // To add the r_index condition to join.
          ),
        );
        if ($entity_type_right != 'relation') {
          // Define join and relationship from endpoints to entity.
          $data['field_data_endpoints']['table']['join'] += array(
            // Directly links to the $entity_type_right table.
            $entity_type_right => array(
              'left_field' => $entity_infos[$entity_type_right]['entity keys']['id'],
              'field' => 'endpoints_entity_id',
            ),
          );
        }
        $data['field_data_endpoints']['endpoints_base_' . $type . '_right_' . $entity_type_right] = array(
          'title' => t('endpoints[@relation_type_label] -> @right)', $t_arguments),
          'help' => t('Endpoints table to @right using "@relation_type_label" relation', $t_arguments),
          'relationship' => array(
            'label' => check_plain('Endpoints::' . $relation_type->label),
            'base' => $base_table_right,
            'base field' => $entity_infos[$entity_type_right]['entity keys']['id'],
            'relationship field' => 'endpoints_entity_id',
          ),
        );

        // Define [join and] relationship from endpoints to endpoints.
        $data['field_data_endpoints']['endpoints_base_' . $type . '_right_endpoints_' . $entity_type_right] = array(
          'title' => t('@left -> endpoints[@relation_type_label])', $t_arguments),
          'help' => t('@left to the sibling endpoints using the "@relation_type_label" relation', $t_arguments),
          'relationship' => array(
            // relation_handler_relationship::options_form() relies on this check_plain().
            'label' => check_plain('Endpoints::' . $relation_type->label),
            'base' => 'field_data_endpoints',
            'base field' => 'entity_id',
            'handler' => 'relation_handler_relationship',
            'relation_type' => $type, // USE THIS as bundle
            'entity_type_right' => $entity_type_right, // Use this as endpoint_entity_type.
            'directional' => $relation_type->directional,
            'join_handler' => 'relation_handler_endpoint_endpoint_join',
          ),
        );
      }
    }
  }
  return $data;
}
