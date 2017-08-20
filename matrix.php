<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('matrix')) {
	dl('matrix.' . PHP_SHLIB_SUFFIX);
}
use Ml\Matrix;

$matrix = new Matrix();
$matrixData = [
	[1, 2, 3],
	[7, 8, 9],
];

$_matrix = $matrix->createMatrix($matrixData);
var_dump($matrix->getMatrixRow(1));
var_dump($matrix->getMatrixCol(2));
?>
