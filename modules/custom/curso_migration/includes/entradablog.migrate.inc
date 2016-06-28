<?php

class CategoriasBlogMigration extends Migration{
	public function __construct($arguments){

		parent::__construct($arguments);

		// 1. DEFINIR EL ORIGEN
		$ruta = drupal_get_path('module','curso_migration'). '/data/categorias.csv';

		$columns = array(
      		0 => array('id', 'ID Categoria'),
      		1 => array('nombrecateg', 'Nombre Categoria'),
    	);
		$this->source = new MigrateSourceCSV($ruta, $columns, array('delimiter' => ';','track_changes' => TRUE, ));

    	// 2. DEFINIR DESTINO
    	$this->destination = new MigrateDestinationTerm('ejemplotaxonomia');

    	// 3. MAPPEO CLAVES
    	$this->map = new MigrateSQLMap(
    	  $this->machineName,
    	  array(
    	  	'id' => array( // mirando en el blog.csv veo que el campo clave es el id
    	  		'type' => 'int',	// es de tipo entero
    	  		'description' => 'Clave entera categoria',
    	  		'unsigned' => TRUE,
    	  		'not null' => TRUE,
    	  	)
    	  ),
    	  MigrateDestinationTerm::getKeySchema() 
    	  // me devuelve la clave que tienen los nodos. 
    	  // puedo ver el contenido en http://localhost/devel/php haciendo un dsm(MigrateDestinationNode::getKeySchema());
    	);


    	// 4. MAPPEO DE CAMPOS
    	$this->addFieldMapping('name', 'nombrecateg');

	}
}


class EntradasBlogMigration extends Migration {
	
	public function __construct($arguments){
		parent::__construct($arguments);

		// 1. DEFINIR ORIGEN defino dónde va a estar el origen
		$ruta = drupal_get_path('module','curso_migration'). '/data/blog.csv'; 
	
		//como el data/blog.csv ya tiene las columnas, no hace falta pasar este parámetro asi que lo paso vacío
    	$this->source = new MigrateSourceCSV($ruta, array(), array(
    		'header_rows' => 1, // la primera linea tiene las cabeceras.
    		'delimiter' => ';',
    		'embedded_newlines' => TRUE, //Set to TRUE if your input file has embedded newlines which throw the record count off. 
    		'track_changes' => TRUE,
    	));
	
	
    	// 2. DEFINIR DESTINO
    	// cursoblog = qué tipo de nodo es (nombre máquina se ve aqui http://localhost/admin/structure/types)
    	$this->destination = new MigrateDestinationNode('cursoblog'); 
	
	
    	// 3. MAPPEO CLAVES
    	$this->map = new MigrateSQLMap(
    	  $this->machineName,
    	  array(
    	  	'id' => array( // mirando en el blog.csv veo que el campo clave es el id
    	  		'type' => 'int',	// es de tipo entero
    	  		'description' => 'Clave entera del CSV',
    	  		'unsigned' => TRUE,
    	  		'not null' => TRUE,
    	  	)
    	  ),
    	  MigrateDestinationNode::getKeySchema() 
    	  // me devuelve la clave que tienen los nodos. 
    	  // puedo ver el contenido en http://localhost/devel/php haciendo un dsm(MigrateDestinationNode::getKeySchema());
    	);
	
	
    	// 4. MAPPEO DE CAMPOS
    	$this->addFieldMapping('title','titulo'); // mappear el title del node al titulo del blog.csv
    	$this->addFieldMapping('body','contenido'); // mappear el body del node al titulo del blog.csv
    	
    	// vamos a importar los tags...
    	
    	// hay que decirle que pueden venir varios valores.
    	$this->addFieldMapping('field_tags','tags')
    		->separator(','); // le digo que los tags en origen vienen separados por coma. 
    						  // Tb podría hacer un prepareRow y generar un array de los valores.

    	// hay que decirle que CREE el término si no existe
    	// los valores de estos campos podemos verlos en http://localhost/admin/content/migrate/groups/curso/entradasblog
    	$this->addFieldMapping('field_tags:create_term')->defaultValue(TRUE);


    	// Ahora tengo que mappear la categoria del blog.csv a las categorias
    	// Me vienen los ID's de las categorías pero esos ID's de origen no coinciden con los ID's de destino.
    	// Tengo que hacer la transformación para ver qué id tiene cada término al haberlo importado.
    	$this->addFieldMapping('field_tipos','categoria')->sourceMigration(array('categoriasblog'));
    	$this->addFieldMapping('field_tipos:source_type')->defaultValue('tid');	
    	$this->addFieldMapping('field_tipos:create_term')->defaultValue(TRUE);
    	$this->addFieldMapping('field_tipos:ignore_case')->defaultValue(TRUE);

    	// aqui haría el mappeo de la imagen si existe
    	$this->addFieldMapping('field_imagen','img');	// lo mappeo al campo 'img' porque ese campo lo creo "al vuelo" en prepareRow
    	$this->addFieldMapping('field_imagen:preserve_files')->defaultValue(FALSE);
    	// el path donde están las imgs
    	$pathimgs =  drupal_get_path('module', 'curso_migration').'/data/img/';
    	$this->addFieldMapping('field_imagen:source_dir')->defaultValue($pathimgs);

    }


    /**
     * Vamos a alterar los títulos de cada row.
     * Si devuelvo false en esta prepareRow, se saltaría la fila.
     * Aqui dentro puedo generar campos también...
     */
    public function prepareRow($row){
    	//dsm($row);
    	$row->titulo = 'Blog - '. $row->titulo;

    	// compruebo si existe la img asociada a dicho id.
    	// si existe, le creo la propiedad img (que es la que mappeo en la línea 108)
    	$pathposibleimg =  drupal_get_path('module', 'curso_migration').'/data/img/'.$row->id.'.jpg';
    	if (file_exists($pathposibleimg)){
    		$row->img=$row->id . '.jpg';
    	}
    }

	
}