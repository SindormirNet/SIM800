<html>
<body>

<form action="" method="get">
<input type="submit" name="accion" value="Encender">
<input type="submit" name="accion" value="Apagar">
</form>

<?php 
if ($_GET["accion"]){
	$fichero = 'omni.html';
	
	if ($_GET["accion"] == "Encender"){
		echo "ENCENCIENDO";
		$contenido = "[OMNI] ENCENDER\n";
	}
	else{
		echo "APAGANDO";
		$contenido = "[OMNI] APAGAR\n";
	}
	file_put_contents($fichero, $contenido);

}
?>

</body>
</html> 
