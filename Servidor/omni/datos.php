<html>
<body>

<?php 
$fichero = 'datos.html';
if ($_GET["A0"]){
	$dato=$_GET["A0"];
	$contenido = "[A0] = $dato\n";
}
if ($_GET["A1"]){
	$dato=$_GET["A1"];
	$contenido = $contenido . "[A1] = $dato\n";
}
if ($_GET["A2"]){
	$dato=$_GET["A2"];
	$contenido = $contenido . "[A2] = $dato\n";
}
file_put_contents($fichero, $contenido);
echo "$contenido";


?>

</body>
</html> 
