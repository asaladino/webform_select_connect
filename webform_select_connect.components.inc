<?php

/**
 * Implements _webform_defaults_component().
 * Specify the default properties of a component.
 *
 * @return array defining the default structure of a component.
 */
function _webform_defaults_select_connect() {
  return [
    'name'      => '',
    'form_key'  => NULL,
    'required'  => 0,
    'mandatory' => 0,
    'pid'       => 0,
    'weight'    => 0,
    'extra'     => [
      'description'   => '',
      'origin_select' => 'form_key',
      'dest_select'   => 'form_key',
      'value_prefix'  => 'tid_',
      'url'           => '/uri-to-your-view-or-rest-endpoint/',
      'nodes_name'    => 'nodes',
      'node_name'     => 'node',
      'node_value'    => 'nid',
      'node_title'    => 'title',
      'select_test'   => '',
    ],
  ];
}

/**
 * Implements _webform_theme_component().
 * This allows each Webform component to add information into hook_theme().
 * If you specify a file to include, you must define the path to the module
 * that this file belongs to.
 *
 * @return array of theme information about the select connect field.
 */
function _webform_theme_select_connect() {
  return ['webform_display_select_connect_field' => ['render element' => 'element']];
}

/**
 * Generate the form for editing a component.
 * Create a set of form elements to be displayed on the form for editing this
 * component. Use care naming the form items, as this correlates directly to
 * the database schema. The component "Name" and "Description" fields are added
 * to every component type and are not necessary to specify here (although they
 * may be overridden if desired).
 *
 * @param $component A Webform component array.
 *
 * @return array An array of form items to be displayed on the edit component
 *   page
 */
function _webform_edit_select_connect($component) {
  $form                           = [];
  $form['extra']['description']   = [
    '#type'          => 'textarea',
    '#title'         => t('Description'),
    '#default_value' => $component['extra']['description'],
    '#description'   => t('Describe the connection.'),
    '#required'      => FALSE,
  ];
  $form['extra']['origin_select'] = [
    '#type'          => 'textfield',
    '#title'         => t('Origin Select Field Form Key'),
    '#default_value' => $component['extra']['origin_select'],
    '#description'   => t('Enter the form key of the originating select field.'),
    '#required'      => TRUE,
  ];
  $form['extra']['dest_select']   = [
    '#type'          => 'textfield',
    '#title'         => t('Destination Select Field Form Key'),
    '#default_value' => $component['extra']['dest_select'],
    '#description'   => t('Enter the form key of the destination field. <strong><em>To avoid validation errors, this should be a text input field.</em></strong>'),
    '#required'      => TRUE,
  ];
  $form['extra']['value_prefix']  = [
    '#type'          => 'textfield',
    '#title'         => t('Value Prefix'),
    '#default_value' => $component['extra']['value_prefix'],
    '#description'   => t('Some values in the originating select field have extra info that might need to be removed.'),
    '#required'      => FALSE,
  ];
  $form['extra']['url']           = [
    '#type'          => 'textfield',
    '#title'         => t('URL'),
    '#default_value' => $component['extra']['url'],
    '#description'   => t('URL of the json view. The last param should accept the id from the originator. ex: /programs-by-degree/'),
    '#required'      => TRUE,
  ];
  $form['extra']['nodes_name']    = [
    '#type'          => 'textfield',
    '#title'         => t('Nodes Name'),
    '#default_value' => $component['extra']['nodes_name'],
    '#description'   => t('Name of the json key containing the array of values returned from the URL.'),
    '#required'      => TRUE,
  ];
  $form['extra']['node_name']     = [
    '#type'          => 'textfield',
    '#title'         => t('Node name'),
    '#default_value' => $component['extra']['node_name'],
    '#description'   => t('Name of the json key containing the object value and title.'),
    '#required'      => TRUE,
  ];
  $form['extra']['node_value']    = [
    '#type'          => 'textfield',
    '#title'         => t('Node Value'),
    '#default_value' => $component['extra']['node_value'],
    '#description'   => t('Name of the json key of the object\'s value.'),
    '#required'      => TRUE,
  ];
  $form['extra']['node_title']    = [
    '#type'          => 'textfield',
    '#title'         => t('Node Title'),
    '#default_value' => $component['extra']['node_title'],
    '#description'   => 'Name of the json key of the object\'s title. This is displayed in the list.',
    '#required'      => TRUE,
  ];
  $form['extra']['select_test']   = [
    '#type'          => 'textfield',
    '#prefix'        => webform_select_connect_get_view('verify', $form),
    '#title'         => FALSE,
    '#default_value' => $component['extra']['select_test'],
    '#required'      => FALSE,
  ];
  return $form;
}


/**
 * Render a Webform component to be part of a form.
 *
 * @param $component
 *   A Webform component array.
 * @param $value
 *   If editing an existing submission or resuming a draft, this will contain
 *   an array of values to be shown instead of the default in the component
 *   configuration. This value will always be an array, keyed numerically for
 *   each value saved in this field.
 * @param $filter
 *   Whether or not to filter the contents of descriptions and values when
 *   rendering the component. Values need to be unfiltered to be editable by
 *   Form Builder.
 *
 * @see _webform_client_form_add_component()
 * @return array
 */
function _webform_render_select_connect(
  $component,
  /** @noinspection PhpUnusedParameterInspection */
  $value = NULL,
  /** @noinspection PhpUnusedParameterInspection */
  $filter = TRUE
) {
  drupal_add_js(drupal_get_path('module', 'webform_select_connect') . '/js/select_connect.js', ['preprocess' => FALSE]);
  $element = [
    '#type'           => 'markup',
    '#weight'         => $component['weight'],
    '#markup'         => webform_select_connect_get_view('form', $component),
    '#theme_wrappers' => ['webform_element'],
  ];
  return $element;
}

/**
 * Alters the webform select connect element during the preview in the editor
 * to display information about the select connect.
 *
 * @param $form_element array to modify
 *
 * @return array modified form element.
 */
function _form_builder_webform_form_builder_preview_alter_select_connect($form_element) {
  $form_element['#children'] .= webform_select_connect_get_view('info', $form_element);
  return $form_element;
}

/**
 * The first hook provides the name and position of the field in the Form
 * Builder palette, as well as a default element to display when the field is
 * pulled out of the palette. The second hook maps the component properties and
 * options to FormAPI properties that Form Builder can manipulate. Form Builder
 * then will manage pulling the form out of the normal Webform configuration
 * form, loading configuration, and saving it. There are plenty of examples in
 * the form_builder_webform.components.inc file that other modules (such as
 * Webform Phone Number) can use as templates. I'm moving this request over to
 * that module's queue, and changing to a feature request.
 * Implements _form_builder_webform_form_builder_types_component().
 *
 * @return array fields.
 */
function _form_builder_webform_form_builder_types_select_connect() {
  drupal_add_css(drupal_get_path('module', 'webform_select_connect') . '/css/webform_select_connect.css', ['preprocess' => FALSE]);
  $fields                                                = [];
  $fields['select_connect']                              = [
    'title'      => t('Select Connect'),
    'properties' => [
      'origin_select',
      'dest_select',
      'value_prefix',
      'url',
      'nodes_name',
      'node_name',
      'node_value',
      'node_title',
      'select_test',
    ],
    'weight'     => -17,
  ];
  $defaults                                              = _webform_defaults_select_connect();
  $fields['select_connect']['default']['#title']         = t('New Select Connect Field');
  $fields['select_connect']['default']['#origin_select'] = $defaults['extra']['origin_select'];
  $fields['select_connect']['default']['#dest_select']   = $defaults['extra']['dest_select'];
  $fields['select_connect']['default']['#value_prefix']  = $defaults['extra']['value_prefix'];
  $fields['select_connect']['default']['#url']           = $defaults['extra']['url'];
  $fields['select_connect']['default']['#nodes_name']    = $defaults['extra']['nodes_name'];
  $fields['select_connect']['default']['#node_name']     = $defaults['extra']['node_name'];
  $fields['select_connect']['default']['#node_value']    = $defaults['extra']['node_value'];
  $fields['select_connect']['default']['#node_title']    = $defaults['extra']['node_title'];
  $fields['select_connect']['default']['#select_test']   = $defaults['extra']['select_test'];
  return $fields;
}

/**
 * Implements _form_builder_webform_form_builder_map_component().
 *
 * Example of how drupal is awesome. This function is needed and the form
 * editor won't display but there is zero documentation on what this does.
 *
 * @return array fields.
 */
function _form_builder_webform_form_builder_map_select_connect() {
  return [
    'form_builder_type' => 'select_connect',
    'properties'        => [
      'origin_select' => [
        'form_parents'    => [
          'extra',
          'origin_select',
        ],
        'storage_parents' => [
          'extra',
          'origin_select',
        ],
      ],
      'dest_select'   => [
        'form_parents'    => [
          'extra',
          'dest_select',
        ],
        'storage_parents' => [
          'extra',
          'dest_select',
        ],
      ],
      'value_prefix'  => [
        'form_parents'    => [
          'extra',
          'value_prefix',
        ],
        'storage_parents' => [
          'extra',
          'value_prefix',
        ],
      ],
      'url'           => [
        'form_parents'    => [
          'extra',
          'url',
        ],
        'storage_parents' => [
          'extra',
          'url',
        ],
      ],
      'nodes_name'    => [
        'form_parents'    => [
          'extra',
          'nodes_name',
        ],
        'storage_parents' => [
          'extra',
          'nodes_name',
        ],
      ],
      'node_name'     => [
        'form_parents'    => [
          'extra',
          'node_name',
        ],
        'storage_parents' => [
          'extra',
          'node_name',
        ],
      ],
      'node_value'    => [
        'form_parents'    => [
          'extra',
          'node_value',
        ],
        'storage_parents' => [
          'extra',
          'node_value',
        ],
      ],
      'node_title'    => [
        'form_parents'    => [
          'extra',
          'node_title',
        ],
        'storage_parents' => [
          'extra',
          'node_title',
        ],
      ],
      'select_test'   => [
        'form_parents'    => [
          'extra',
          'select_test',
        ],
        'storage_parents' => [
          'extra',
          'select_test',
        ],
      ],
    ],
  ];
}

/**
 * Gets the specified view.
 *
 * @param $view string to get.
 * @param $params array passed to view.
 *
 * @return string the output of the view.
 */
function webform_select_connect_get_view(
  $view, /** @noinspection PhpUnusedParameterInspection */
  &$params
) {
  ob_start();
  /** @noinspection PhpIncludeInspection */
  include drupal_get_path('module', 'webform_select_connect') . '/views/' . $view . '.php';
  return ob_get_clean();
}
