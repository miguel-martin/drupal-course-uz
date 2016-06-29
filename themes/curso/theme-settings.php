<?php


// Este archivo se tiene que llamar asi por convención de nombres.
// Aqui definimos los settings de nuestro theme

/**
 * Implements hook_form_system_theme_settings_alter
 * Con esto podremos alterar los settings del theme
 * que se ven en http://localhost/admin/appearance/settings/curso
 */
function curso_form_system_theme_settings_alter(&$form, $form_state){
    //dsm($form);

    // Vamos a crear un nuevo fieldset con nuestras opciones
    $form['curso_config'] = array(
    	'#type' => 'fieldset',
    	'#title' => 'Configuracion avanzada del tema',
    	'#weight' => -10 // para que salga arriba
    );


    $form['curso_config']['cursofixed'] = array( // defino la variable cursofixed
    	'#type' => 'select',
    	'#title' => 'Contenedor de tamaño fijo',
    	'#options' => array(
    		0 => 'No',
    		1 => 'Si'
    	),
    	'#default_value' => theme_get_setting('cursofixed')  // asi ya me coge el valor guardado, en vez de hacer un variable_get.
    );
}
