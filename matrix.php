<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('matrix')) {
	dl('matrix.' . PHP_SHLIB_SUFFIX);
}
use Ml\Matrix;

$matrix = new Matrix();
$matrixData = [
	[1, 2, 3],
	[3, 4, 5]
];

$_matrix = $matrix->createMatrix($matrixData);
var_dump($matrix->getMatrixRow(1));
?>
