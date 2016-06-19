<?php

/**
 * Generates the profile type editing form.
 */
function codigo_postal_form($form, &$form_state, $codigo_postal, $op = 'edit', $entity_type = NULL) {

  //dsm($form_state);
  //dsm($op);



  $info = '<h1>Gestión de códigos postales</h1>';

  if ($op == 'edit') {
    $info .= '<h3>Editar código '.$codigo_postal->codigo.'</h3>';
  }
  elseif ($op == 'add'){
     $info .= '<h3>Añadir nuevo código.</h3>';
  }
  $form['informacion_codigos'] = array(
    '#markup' => $info,
    '#weight' => -1,
  );

  $form['codigo'] = array(
    '#title' => 'Código postal',
    '#type' => 'textfield',
    '#default_value' => isset($codigo_postal->codigo) ? $codigo_postal->codigo : '',
    '#description' => 'El código postal se compone de 5 dígitos o más.',
  );

  $form['name'] = array(
    '#title' => 'Localidad',
    '#type' => 'textfield',
    '#default_value' => isset($codigo_postal->name) ? $codigo_postal->name : '',
    '#description' => 'Introduzca la ubicación relacionada al código',
  );

  // creo el botón submit
  $form['config']["submit_button"] = array(
    '#type' => 'submit',
    '#value' => 'Guardar',
  );

  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function codigo_postal_form_submit(&$form, &$form_state) {
  $codigo_postal = entity_ui_form_submit_build_entity($form, $form_state);
  // Save and go back.
  $codigo_postal->save();
  drupal_set_message('Guardados cambios a código '.$codigo_postal->codigo);
  $form_state['redirect'] = 'admin/content/codigos';
}

/**
 * Implements hook_form_validate
 * Validacion del formulario, se ejecuta en cuanto haces submit.
 * FixMe.
 */
 function codigo_postal_form_validate($node, &$form_state){

  //dsm($form_state);

  // Ejemplo de comprobación
  if (strlen($form_state['values']['codigo'])>6){
    form_set_error('codigo','El código postal debe ser de long 6.');
  }

 }