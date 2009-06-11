/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2009 - DIGITEO - Antoine ELIAS
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 * Please note that piece of code will be rewrited for the Scilab 6 family
 * However, the API (profile of the functions in the header files) will be 
 * still available and supported in Scilab 6.
 */

#include "common_api.h"
#include "internal_common_api.h"
#include "sparse_api.h"

#include "MALLOC.h"
#include "CallScilab.h"
#include "stack-c.h"

//internal sparse functions
static int getCommonSparseMatrix(int* _piAddress, int _iComplex, int* _piRows, int* _piCols, int* _piNbItem, int** _piNbItemRow, int** _piColPos, double** _pdblReal, double** _pdblImg);
static int allocCommonSparseMatrix(int _iVar, int _iComplex, int _iRows, int _iCols, int _iNbItem, int** _piNbItemRow, int** _piColPos, double** _pdblReal, double** _pdblImg, int** _piAddress);
static int fillCommonSparseMatrix(int *_piAddress, int _iComplex, int _iRows, int _iCols, int _iNbItem, int** _piNbItemRow, int** _piColPos, double** _pdblReal, double** _pdblImg, int* _piTotalSize);
static int createCommonSparseMatrix(int _iVar, int _iComplex, int _iRows, int _iCols, int _iNbItem, int* _piNbItemRow, int* _piColPos, double* _pdblReal, double* _pdblImg, int** _piAddress);
static int createCommonNamedSparseMatrix(char* _pstName, int _iNameLen, int _iComplex, int _iRows, int _iCols, int _iNbItem, int* _piNbItemRow, int* _piColPos, double* _pdblReal, double* _pdblImg);
static int readCommonNamedSparseMatrix(char* _pstName, int _iNameLen, int _iComplex, int* _piRows, int* _piCols, int* _piNbItem, int* _piNbItemRow, int* _piColPos, double* _pdblReal, double* _pdblImg);

int getSparseMatrix(int* _piAddress, int* _piRows, int* _piCols, int* _piNbItem, int** _piNbItemRow, int** _piColPos, double** _pdblReal)
{
	return getCommonSparseMatrix(_piAddress, 0, _piRows, _piCols, _piNbItem, _piNbItemRow, _piColPos, _pdblReal, NULL);
}

int getComplexSparseMatrix(int* _piAddress, int* _piRows, int* _piCols, int* _piNbItem, int** _piNbItemRow, int** _piColPos, double** _pdblReal, double** _pdblImg)
{
	return getCommonSparseMatrix(_piAddress, 1, _piRows, _piCols, _piNbItem, _piNbItemRow, _piColPos, _pdblReal, _pdblImg);
}

static int getCommonSparseMatrix(int* _piAddress, int _iComplex, int* _piRows, int* _piCols, int* _piNbItem, int** _piNbItemRow, int** _piColPos, double** _pdblReal, double** _pdblImg)
{
	int i							= 0;
	int iPos					= 0;

	if(	_piAddress == NULL || 
			getVarType(_piAddress) != sci_sparse || 
			isVarComplex(_piAddress) != _iComplex)
	{
		return 1;
	}

	getVarDimension(_piAddress, _piRows, _piCols);

	*_piNbItem = _piAddress[4];

	if(_piNbItemRow == NULL)
	{
		return 0;
	}
	*_piNbItemRow = _piAddress + 5;//4 for header + 1 for NbItem

	if(_piColPos == NULL)
	{
		return 0;
	}
	*_piColPos = *_piNbItemRow + *_piRows;

	if(_pdblReal == NULL)
	{
		return 0;
	}

	iPos = (*_piNbItem + *_piRows) % 2 == 1 ? 0 : 1;
	*_pdblReal = (double*)(*_piColPos + *_piNbItem + iPos);
	if(_iComplex == 1 && _pdblImg != NULL)
	{
		*_pdblImg = *_pdblReal + *_piNbItem;
	}
	return 0;
}

int allocSparseMatrix(int _iVar, int _iRows, int _iCols, int _iNbItem, int** _piNbItemRow, int** _piColPos, double** _pdblReal, int** _piAddress)
{
	return allocCommonSparseMatrix(_iVar, 0, _iRows, _iCols, _iNbItem, _piNbItemRow, _piColPos, _pdblReal, NULL, _piAddress);
}

int allocComplexSparseMatrix(int _iVar, int _iRows, int _iCols, int _iNbItem, int** _piNbItemRow, int** _piColPos, double** _pdblReal, double** _pdblImg, int** _piAddress)
{
	return allocCommonSparseMatrix(_iVar, 1, _iRows, _iCols, _iNbItem, _piNbItemRow, _piColPos, _pdblReal, _pdblImg, _piAddress);
}

static int allocCommonSparseMatrix(int _iVar, int _iComplex, int _iRows, int _iCols, int _iNbItem, int** _piNbItemRow, int** _piColPos, double** _pdblReal, double** _pdblImg, int** _piAddress)
{
	int iNewPos			= Top - Rhs + _iVar;
	int iAddr				= *Lstk(iNewPos);
	int *piAddr			= NULL;
	int	iTotalSize	= 0;
	int iOffset			= 0;

	getNewVarAddressFromNumber(iNewPos, _piAddress);
	fillCommonSparseMatrix(*_piAddress, _iComplex, _iRows, _iCols, _iNbItem, _piNbItemRow, _piColPos, _pdblReal, _pdblImg, &iTotalSize);

	iOffset	= 5;//4 for header + 1 for NbItem
	iOffset		+= _iRows + _iNbItem + !((_iRows + _iNbItem) % 2);

	updateInterSCI(_iVar, '$', iAddr, sadr(iadr(iAddr) + iOffset));
	updateLstk(iNewPos, sadr(iadr(iAddr) + iOffset), iTotalSize);
	return 0;
}

static int fillCommonSparseMatrix(int *_piAddress, int _iComplex, int _iRows, int _iCols, int _iNbItem, int** _piNbItemRow, int** _piColPos, double** _pdblReal, double** _pdblImg, int* _piTotalSize)
{
	if(_piAddress == NULL)
	{
		return 1;
	}

	_piAddress[0]		= sci_sparse;
	_piAddress[1]		= Min(_iRows, _iRows * _iCols);
	_piAddress[2]		= Min(_iCols, _iRows * _iCols);
	_piAddress[3]		= _iComplex;

	_piAddress[4]		= _iNbItem;

	*_piNbItemRow	= _piAddress + 5;//4 for header + 1 for NbItem
	*_piColPos		= *_piNbItemRow + _iRows;
	*_pdblReal		= (double*)(*_piColPos + _iNbItem + !((_iRows + _iNbItem) % 2));

	if(_iComplex == 1)
	{
		*_pdblImg			= *_pdblReal + _iNbItem;
	}

	*_piTotalSize	= _iNbItem * (_iComplex + 1);
	return 0;
}

int createSparseMatrix(int _iVar, int _iRows, int _iCols, int _iNbItem, int* _piNbItemRow, int* _piColPos, double* _pdblReal, int** _piAddress)
{
	return createCommonSparseMatrix(_iVar, 0, _iRows, _iCols, _iNbItem, _piNbItemRow, _piColPos, _pdblReal, NULL, _piAddress);
}

int createComplexSparseMatrix(int _iVar, int _iRows, int _iCols, int _iNbItem, int* _piNbItemRow, int* _piColPos, double* _pdblReal, double* _pdblImg, int** _piAddress)
{
	return createCommonSparseMatrix(_iVar, 1, _iRows, _iCols, _iNbItem, _piNbItemRow, _piColPos, _pdblReal, _pdblImg, _piAddress);
}

static int createCommonSparseMatrix(int _iVar, int _iComplex, int _iRows, int _iCols, int _iNbItem, int* _piNbItemRow, int* _piColPos, double* _pdblReal, double* _pdblImg, int** _piAddress)
{
	int* piNbItemRow	= NULL;
	int* piColPos			= NULL;
	int* piAddr				= NULL;
	double* pdblReal	= NULL;
	double* pdblImg		= NULL;

	int iRet = allocCommonSparseMatrix(_iVar, _iComplex, _iRows, _iCols, _iNbItem, &piNbItemRow, &piColPos, &pdblReal, &pdblImg, &piAddr);
	if(iRet)
	{
		return 1;
	}

	memcpy(piNbItemRow, _piNbItemRow, _iRows * sizeof(int));
	memcpy(piColPos, _piColPos, _iNbItem * sizeof(int));
	memcpy(pdblReal, _pdblReal, _iNbItem  * sizeof(double));
	if(_iComplex)
	{
		memcpy(pdblImg, _pdblImg, _iNbItem  * sizeof(double));
	}
	return 0;
}

int createNamedSparseMatrix(char* _pstName, int _iNameLen, int _iRows, int _iCols, int _iNbItem, int* _piNbItemRow, int* _piColPos, double* _pdblReal)
{
	return createCommonNamedSparseMatrix(_pstName, _iNameLen, 0, _iRows, _iCols, _iNbItem, _piNbItemRow, _piColPos, _pdblReal, NULL);
}

int createNamedComplexSparseMatrix(char* _pstName, int _iNameLen, int _iRows, int _iCols, int _iNbItem, int* _piNbItemRow, int* _piColPos, double* _pdblReal, double* _pdblImg)
{
	return createCommonNamedSparseMatrix(_pstName, _iNameLen, 1, _iRows, _iCols, _iNbItem, _piNbItemRow, _piColPos, _pdblReal, _pdblImg);
}

static int createCommonNamedSparseMatrix(char* _pstName, int _iNameLen, int _iComplex, int _iRows, int _iCols, int _iNbItem, int* _piNbItemRow, int* _piColPos, double* _pdblReal, double* _pdblImg)
{
	int iVarID[nsiz];
  int iSaveRhs			= Rhs;
	int iSaveTop			= Top;
	int iRet					= 0;
	int iTotalSize		= 0;
	int iPos					= 0;

	int* piAddr				= NULL;
	int* piNbItemRow	= NULL;
	int* piColPos			= NULL;
	double* pdblReal	= NULL;
	double* pdblImg		= NULL;


  C2F(str2name)(_pstName, iVarID, _iNameLen);
  Top = Top + Nbvars + 1;

	iRet = getNewVarAddressFromNumber(Top, &piAddr);

	fillCommonSparseMatrix(piAddr, _iComplex, _iRows, _iCols, _iNbItem, &piNbItemRow, &piColPos, &pdblReal, &pdblImg, &iTotalSize);

	memcpy(piNbItemRow, _piNbItemRow, _iRows * sizeof(int));
	memcpy(piColPos, _piColPos, _iNbItem * sizeof(int));
	memcpy(pdblReal, _pdblReal, _iNbItem  * sizeof(double));
	if(_iComplex)
	{
		memcpy(pdblImg, _pdblImg, _iNbItem  * sizeof(double));
	}

	iPos	= 5;//4 for header + 1 for NbItem
	iPos += _iRows + _iNbItem;

	//update "variable index"
	updateLstk(Top, *Lstk(Top) + iPos, iTotalSize);

	Rhs = 0;
	//Add name in stack reference list
	createNamedVariable(iVarID);

	Top = iSaveTop;
  Rhs = iSaveRhs;

	return 0;

}

int readNamedSparseMatrix(char* _pstName, int _iNameLen, int* _piRows, int* _piCols, int* _piNbItem, int* _piNbItemRow, int* _piColPos, double* _pdblReal)
{
	return readCommonNamedSparseMatrix(_pstName, _iNameLen, 0, _piRows, _piCols, _piNbItem, _piNbItemRow, _piColPos, _pdblReal, NULL);
}

int readNamedComplexSparseMatrix(char* _pstName, int _iNameLen, int* _piRows, int* _piCols, int* _piNbItem, int* _piNbItemRow, int* _piColPos, double* _pdblReal, double* _pdblImg)
{
	return readCommonNamedSparseMatrix(_pstName, _iNameLen, 1, _piRows, _piCols, _piNbItem, _piNbItemRow, _piColPos, _pdblReal, _pdblImg);
}

static int readCommonNamedSparseMatrix(char* _pstName, int _iNameLen, int _iComplex, int* _piRows, int* _piCols, int* _piNbItem, int* _piNbItemRow, int* _piColPos, double* _pdblReal, double* _pdblImg)
{
	int iVarID[nsiz];
	int* piAddr				= NULL;
	int* piNbItemRow	= 0;
	int* piColPos			= 0;

	double* pdblReal	= NULL;
	double* pdblImg		= NULL;

	//get variable id from name
	C2F(str2name)(_pstName, iVarID, _iNameLen);

	//define scope of search
  Fin = -1;
	//search variable 
  C2F(stackg)(iVarID);

	if (Err > 0 || Fin == 0)
	{
		return 1;
	}

	//No idea :(
  if ( *Infstk(Fin) == 2)
		Fin = *istk(iadr(*Lstk(Fin )) + 1 + 1);

	//get variable address
	//WARNING check in VarType can be negative
	getNewVarAddressFromNumber(Fin, &piAddr);
	
	if(_iComplex == 1)
	{
		getComplexSparseMatrix(piAddr, _piRows, _piCols, _piNbItem, &piNbItemRow, &piColPos, &pdblReal, &pdblImg);
	}
	else
	{
		getSparseMatrix(piAddr, _piRows, _piCols, _piNbItem, &piNbItemRow, &piColPos, &pdblReal);
	}

	if(_piNbItemRow == NULL)
	{
		return 0;
	}

	memcpy(_piNbItemRow, piNbItemRow, *_piRows * sizeof(int));

	if(_piColPos == NULL)
	{
		return 0;
	}
	memcpy(_piColPos, piColPos, *_piNbItem * sizeof(int));


	if(_pdblReal == NULL)
	{
		return 0;
	}
	memcpy(_pdblReal, pdblReal, *_piNbItem  * sizeof(double));

	if(_iComplex && _pdblImg)
	{
		memcpy(_pdblImg, pdblImg, *_piNbItem  * sizeof(double));
	}

	return 0;
}
/*--------------------------------------------------------------------------*/

