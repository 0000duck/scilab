/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2009 - INRIA - Antoine ELIAS
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 */

#ifndef __SAPRSE_API__
#define __SAPRSE_API__

/*****************************/
/*   sparse matrix functions */
/*****************************/

/**
 * Get sparse variable data
 * @param[in] _piAddress variable address
 * @param[out] _piRows return number of row 
 * @param[out] _piCols return number of column
 * @param[in] _iNbItem Number of item
 * @param[out] _piNbItemRow return array of number of item for each row
 * @param[out] _piColPos return array of item column position ( 1 indexed )
 * @param[out] _pdblReal return pointer on real data
 * @return if the operation successed (0) or not ( !0 )
 */
int getSparseMatrix(int* _piAddress, int* _piRows, int* _piCols, int* _piNbItem, int** _piNbItemRow, int** _piColPos, double** _pdblReal);

/**
 * Get sparse variable data
 * @param[in] _piAddress variable address
 * @param[out] _piRows return number of row 
 * @param[out] _piCols return number of column
 * @param[in] _iNbItem Number of item
 * @param[out] _piNbItemRow return array of number of item for each row
 * @param[out] _piColPos return array of item column position ( 1 indexed )
 * @param[out] _pdblReal return pointer on real data
 * @param[out] _pdblImg return pointer on img data
 * @return if the operation successed (0) or not ( !0 )
 */
int getComplexSparseMatrix(int* _piAddress, int* _piRows, int* _piCols, int* _piNbItem, int** _piNbItemRow, int** _piColPos, double** _pdblReal, double** _pdblImg);

/**
 * alloc sparse variable data
 * @param[in] _iVar variable number
 * @param[in] _iRows Number of row
 * @param[in] _iCols Number of column
 * @param[in] _iNbItem Number of item
 * @param[out] _piNbItemRow return array of number of item for each row
 * @param[out] _piColPos return array of item column position ( 1 indexed )
 * @param[out] _pdblReal return pointer on data
 * @param[out] _piAddress return pointer on new variable
 * @return if the operation successed (0) or not ( !0 )
 */
int allocSparseMatrix(int _iVar, int _iRows, int _iCols, int _iNbItem, int** _piNbItemRow, int** _piColPos, double** _pdblReal, int** _piAddress);

/**
 * alloc sparse variable data
 * @param[in] _iVar variable number
 * @param[in] _iRows Number of row
 * @param[in] _iCols Number of column
 * @param[in] _iNbItem Number of item
 * @param[out] _piNbItemRow return array of number of item for each row
 * @param[out] _piColPos return array of item column position ( 1 indexed )
 * @param[out] _pdblReal return pointer on data
 * @param[out] _pdblImg return pointer on img data
 * @param[out] _piAddress return pointer on new variable
 * @return if the operation successed (0) or not ( !0 )
 */
int allocComplexSparseMatrix(int _iVar, int _iRows, int _iCols, int _iNbItem, int** _piNbItemRow, int** _piColPos, double** _pdblReal, double** _pdblImg, int** _piAddress);

/**
 * Create sparse variable
 * @param[in] _iVar variable number
 * @param[in] _iRows Number of row
 * @param[in] _iCols Number of column
 * @param[in] _iNbItem Number of item
 * @param[in] _piNbItemRow array of number of item for each row
 * @param[in] _piColPos array of item column position ( 1 indexed )
 * @param[in] _pdblReal pointer on data
 * @param[out] _piAddress return pointer on new variable
 * @return if the operation successed (0) or not ( !0 )
 */
int createSparseMatrix(int _iVar, int _iRows, int _iCols, int _iNbItem, int* _piNbItemRow, int* _piColPos, double* _pdblReal, int** _piAddress);

/**
 * Create sparse variable
 * @param[in] _iVar variable number
 * @param[in] _iRows Number of row
 * @param[in] _iCols Number of column
 * @param[in] _iNbItem Number of item
 * @param[in] _piNbItemRow array of number of item for each row
 * @param[in] _piColPos array of item column position ( 1 indexed )
 * @param[in] _pdblReal pointer on real data
 * @param[out] _pdblImg pointer on img data
 * @param[out] _piAddress return pointer on new variable
 * @return if the operation successed (0) or not ( !0 )
 */
int createComplexSparseMatrix(int _iVar, int _iRows, int _iCols, int _iNbItem, int* _piNbItemRow, int* _piColPos, double* _pdblReal, double* _pdblImg, int** _piAddress);

/**
 * Create named sparse variable
 * @param[in] _pstName variable name
 * @param[in] _iNamelen variable name length
 * @param[in] _iRows Number of row
 * @param[in] _iCols Number of column
 * @param[in] _iNbItem Number of item
 * @param[in] _piNbItemRow array of number of item for each row
 * @param[in] _piColPos array of item column position ( 1 indexed )
 * @param[in] _pdblReal pointer on data
 * @param[out] _piAddress return pointer on new variable
 * @return if the operation successed (0) or not ( !0 )
 */
int createNamedSparseMatrix(char* _pstName, int _iNameLen, int _iRows, int _iCols, int _iNbItem, int* _piNbItemRow, int* _piColPos, double* _pdblReal);

/**
 * Create named sparse variable
 * @param[in] _pstName variable name
 * @param[in] _iNamelen variable name length
 * @param[in] _iRows Number of row
 * @param[in] _iCols Number of column
 * @param[in] _iNbItem Number of item
 * @param[in] _piNbItemRow array of number of item for each row
 * @param[in] _piColPos array of item column position ( 1 indexed )
 * @param[in] _pdblReal pointer on real data
 * @param[out] _pdblImg pointer on img data
 * @param[out] _piAddress return pointer on new variable
 * @return if the operation successed (0) or not ( !0 )
 */
int createNamedComplexSparseMatrix(char* _pstName, int _iNameLen, int _iRows, int _iCols, int _iNbItem, int* _piNbItemRow, int* _piColPos, double* _pdblReal, double* _pdblImg);

/**
 * Read named sparse variable
 * @param[in] _pstName variable name
 * @param[in] _iNamelen variable name length
 * @param[out] _piRows return number of row 
 * @param[out] _piCols return number of column
 * @param[out] _piNbItem return number of item
 * @param[out] _piNbItemRow return array of number of item for each row
 * @param[out] _piColPos return array of item column position ( 1 indexed )
 * @param[out] _pdblReal pointer on data
 * @param[out] _piAddress return pointer on new variable
 * @return if the operation successed (0) or not ( !0 )
 */
int readNamedSparseMatrix(char* _pstName, int _iNameLen, int* _piRows, int* _piCols, int* _piNbItem, int* _piNbItemRow, int* _piColPos, double* _pdblReal);

/**
 * Read named sparse variable
 * @param[in] _pstName variable name
 * @param[in] _iNamelen variable name length
 * @param[out] _piRows return number of row 
 * @param[out] _piCols return number of column
 * @param[out] _piNbItem return number of item
 * @param[out] _piNbItemRow return array of number of item for each row
 * @param[out] _piColPos return array of item column position ( 1 indexed )
 * @param[out] _pdblReal pointer on real data
 * @param[out] _pdblImg pointer on img data
 * @param[out] _piAddress return pointer on new variable
 * @return if the operation successed (0) or not ( !0 )
 */
int readNamedComplexSparseMatrix(char* _pstName, int _iNameLen, int* _piRows, int* _piCols, int* _piNbItem, int* _piNbItemRow, int* _piColPos, double* _pdblReal, double* _pdblImg);

#endif /* __SAPRSE_API__ */