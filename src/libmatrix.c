#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

/* include global headers*/
#include "php_matrix.h"
#include "src/libmatrix.h"
zend_class_entry * matrix_ce;
ZEND_BEGIN_ARG_INFO(createMatrixArgInfo, 0)
    ZEND_ARG_INFO(0, matrixData)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(getMatrixRowArgInfo, 0)
ZEND_ARG_INFO(0, rowNum)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(getMatrixColArgInfo, 0)
ZEND_ARG_INFO(0, colNum)
ZEND_END_ARG_INFO()

PHP_METHOD(Matrix, createMatrix)
{
    zval *matrixData;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ARRAY(matrixData)
    ZEND_PARSE_PARAMETERS_END();
    zend_update_property(matrix_ce, getThis(), ZEND_STRL("matrix"), matrixData);
    RETURN_ZVAL(matrixData, 0, 0);
}

PHP_METHOD(Matrix, getMatrixRow)
{
    zend_long rowNum;
    zval *matrixData, *entry;
    zend_ulong h, hRow;
    zend_string *key, *hKey;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(rowNum)
    ZEND_PARSE_PARAMETERS_END();

    matrixData = zend_read_property(matrix_ce, getThis(), ZEND_STRL("matrix"), 0, matrixData);

    ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(matrixData), h, key, entry) {
       if (Z_TYPE_P(entry) == IS_ARRAY && rowNum == h) {
            RETURN_ZVAL(entry, 0, 0);   
       }
    } ZEND_HASH_FOREACH_END();
    RETURN_NULL();
}

PHP_METHOD(Matrix, getMatrixCol)
{
    zend_long colNum;
    zval *matrixData, *entry, *colData, arr;
    zend_ulong h, hCol, index = 0;
    zend_string *key, *hKey;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(colNum)
    ZEND_PARSE_PARAMETERS_END();

    matrixData = zend_read_property(matrix_ce, getThis(), ZEND_STRL("matrix"), 0, matrixData);
    array_init(&arr);
    ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(matrixData), h, key, entry) {
        if (Z_TYPE_P(entry) == IS_ARRAY) {
            ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(entry), hCol, hKey, colData) { 
                php_printf("index: %d , hcol: %d, value:%d\n", colNum, hCol, Z_LVAL_P(colData));
                if (colNum == hCol) {
                   
                    add_index_long(&arr, index, Z_LVAL_P(colData));
                    index++;
                }
                
            } ZEND_HASH_FOREACH_END();
        }
    } ZEND_HASH_FOREACH_END();
    RETURN_ZVAL(&arr, 0, 1);
}


static zend_function_entry matrix_methods[] = {
    PHP_ME(Matrix, createMatrix, createMatrixArgInfo, ZEND_ACC_PUBLIC)
    PHP_ME(Matrix, getMatrixRow, getMatrixRowArgInfo, ZEND_ACC_PUBLIC)
    PHP_ME(Matrix, getMatrixCol, getMatrixColArgInfo, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

PHP_MATRIX_STARTUP_FUNCTION(Matrix)
{
    zend_class_entry matrix_container_ce;
    INIT_CLASS_ENTRY(matrix_container_ce, "Ml\\Matrix", matrix_methods);
    matrix_ce = zend_register_internal_class(&matrix_container_ce TSRMLS_CC);
    zend_declare_property_null(matrix_ce, ZEND_STRL("matrix"), ZEND_ACC_PUBLIC);
    return SUCCESS;
}