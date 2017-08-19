/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2017 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: shinemotec@gmail.com                                         |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_MATRIX_H
#define PHP_MATRIX_H

extern zend_module_entry matrix_module_entry;
#define phpext_matrix_ptr &matrix_module_entry

#define PHP_MATRIX_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_MATRIX_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_MATRIX_API __attribute__ ((visibility("default")))
#else
#	define PHP_MATRIX_API
#endif

#define PHP_MATRIX_STARTUP(module)               ZEND_MODULE_STARTUP_N(php_matrix_##module)(INIT_FUNC_ARGS_PASSTHRU)
#define PHP_MATRIX_STARTUP_FUNCTION(module)      ZEND_MINIT_FUNCTION(php_matrix_##module)

#ifdef ZTS
#include "TSRM.h"
#endif

#define MATRIX_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(matrix, v)

#if defined(ZTS) && defined(COMPILE_DL_MATRIX)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif