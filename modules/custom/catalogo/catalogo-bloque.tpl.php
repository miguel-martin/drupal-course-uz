<div id="catalogo">
    
    <?php if($catalogo_desc_corta): ?>
       <p><?php print $catalogo_desc_corta; ?></p>
    <?php endif;?>

    <?php if($catalogo_oferta): ?>
       <p>Todo nuestro catálogo al 20%!</p>
    <?php endif;?>

    <?php if($enlace_pdf): ?>
       <?php print $enlace_pdf; ?>
    <?php endif;?>

</div>
