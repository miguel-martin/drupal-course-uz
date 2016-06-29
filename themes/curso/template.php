<?php

// En este archivo haré toda la lógica del theme


/**
 * Implements hook_preprocess_html
 */
function curso_preprocess_html(&$variables){
 // dsm($variables); // asi miro lo que contiene ese vector de variables

 if (theme_get_setting('cursofixed')){ // si está activado el setting, añado esa clase al classes_array
 	$variables['classes_array'][] = 'contenedor-fijo';
 }



 //  dsm($variables);

}