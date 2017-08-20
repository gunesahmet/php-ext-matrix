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
	[70, 80, 90],
];

$_matrix = $matrix->createMatrix($matrixData);
var_dump($matrix->getMatrixRow(0));
var_dump($matrix->getMatrixRow(1));
var_dump($matrix->getMatrixRow(2));
var_dump($matrix->getMatrixCol(0));
var_dump($matrix->getMatrixCol(1));
var_dump($matrix->getMatrixCol(2));
?>
