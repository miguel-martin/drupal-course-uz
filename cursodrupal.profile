<?php

/**
 * Implements hook_form_FORM_ID_alter().
 */
function cursodrupal_form_install_configure_form_alter(&$form, $form_state) {
  $form['site_information']['site_name']['#default_value'] = variable_get('site_name', 'Unizar Curso');
  $form['server_settings']['site_default_country']['#default_value'] = 'ES';
  $form['server_settings']['date_default_timezone']['#default_value'] = 'Europe/Madrid';
  $form['update_notifications']['update_status_module']['#default_value'] = array(1);
}

/**
 * Implements hook_profile_details().
 */
function cursodrupal_profile_details() {
  return array(
    'language' => 'en',
  );
}
