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

#include "MALLOC.h"
#include "stack-c.h"
#include "CallScilab.h"

#include "api_common.h"
#include "api_internal_common.h"
#include "api_internal_double.h"
#include "api_internal_string.h"
#include "api_internal_boolean.h"
#include "api_internal_poly.h"
#include "api_list.h"
#include "api_string.h"
#include "api_boolean.h"


//internal functions
static int createCommonList(int _iVar, int _iListType, int _iNbItem, int** _piAddress);
static int createCommonListInList(int _iVar, int* _piParent, int _iItemPos, int _iListType, int _iNbItem, int** _piAddress, int iNamed);
static int createCommonNamedList(char* _pstName, int _iNameLen, int _iListType, int _iNbItem, int** _piAddress);
static int createCommonListInNamedList(char* _pstName, int _iNameLen, int* _piParent, int _iItemPos, int _iListType, int _iNbItem, int** _piAddress);
static int getCommonListInList(int _iVar, int* _piParent, int _iItemPos, int _iListType, int** _piAddress);
static int getCommomListInNamedList(char* _pstName, int _iNameLen, int* _piParent, int _iItemPos, int _iListType, int** _piAddress);
static int readCommonNamedList(char* _pstName, int _iNameLen, int _iListType, int* _piNbItem, int** _piAddress);
static int fillCommonList(int* _piAddress, int _iListType, int _iNbItem);
static int isKindOfList(int* _piNode);
static int getParentList(int* _piStart, int* _piToFind, int* _piDepth, int** _piParent);
static void closeList(int _iVar, int *_piEnd);
static void updateListOffset(int _iVar, int *_piCurrentNode, int _iItemPos, int *_piEnd);
static void updateNamedListOffset(int _iVar, int *_piCurrentNode, int _iItemPos, int *_piEnd);
static void updateCommunListOffset(int _iVar, int *_piCurrentNode, int _iItemPos, int *_piEnd);

static int allocCommonMatrixOfDoubleInList(int _iVar, int* _piParent, int _iItemPos, int _iComplex, int _iRows, int _iCols, double **_pdblReal, double **_pdblImg);
static int getCommonMatrixOfDoubleInList(int _iVar, int* _piParent, int _iItemPos, int _iComplex, int* _piRows, int* _piCols, double** _pdblReal, double** _pdblImg);
static int createCommonMatrixOfDoubleInList(int _iVar, int* _piParent, int _iItemPos, int _iComplex, int _iRows, int _iCols, double* _pdblReal, double* _pdblImg);
static int fillCommonMatrixOfDoubleInList(int _iVar, int* _piParent, int _iItemPos, int _iComplex, int _iRows, int _iCols, double** _pdblReal, double** _pdblImg);
static int createCommomMatrixOfDoubleInNamedList(char* _pstName, int _iNameLen, int* _piParent, int _iItemPos, int _iComplex, int _iRows, int _iCols, double* _pdblReal, double* _pdblImg);
static int readCommonMatrixOfDoubleInNamedList(char* _pstName, int _iNameLen, int* _piParent, int _iItemPos, int _iComplex, int* _piRows, int* _piCols, double* _pdblReal, double* _pdblImg);
static int allocCommonItemInList(int* _piParent, int _iItemPos, int** _piChildAddr);
static int fillMatrixOfBoolInList(int _iVar, int* _piParent, int _iItemPos, int _iRows, int _iCols, int** _piBool);
static int getCommonxMatrixOfPolyInList(int _iVar, int* _piParent, int _iItemPos, int _iComplex, int* _piRows, int* _piCols, int* _piNbCoef, double** _pdblReal, double** _pdblImg);
static int createCommonMatrixOfPolyInList(int _iVar, int* _piParent, int _iItemPos, char* _pstVarName, int _iComplex, int _iRows, int _iCols, int* _piNbCoef, double** _pdblReal, double** _pdblImg);
static int fillCommonMatrixOfPolyInList(int _iVar, int* _piParent, int _iItemPos, char* _pstVarName, int _iComplex, int _iRows, int _iCols, int* _piNbCoef, double** _pdblReal, double** _pdblImg, int* _piTotalLen);
static int fillCommonMatrixOfStringInList(int _iVar, int* _piParent, int _iItemPos, int _iRows, int _iCols, char** _pstStrings, int* _piTotalLen);

int getListItemNumber(int* _piAddress, int* _piNbItem)
{
	switch(getVarType(_piAddress))
	{
	case sci_list :
	case sci_mlist :
	case sci_tlist :
		*_piNbItem = _piAddress[1];
		break;
	default :
		*_piNbItem = -1;
		return 1;
	}
	return 0;
}

int getListItemAddress(int* _piAddress, int _iItemNum, int** _piItemAddress)
{
	int iRet						= 0;
	int iItem						= 0;
	int* piOffset				= NULL;
	int* piItemAddress	= NULL;

	//get item count
	iRet = getListItemNumber(_piAddress, &iItem);
	if(iRet)
	{
		return 1;
	}

	//get offset of item array
	piOffset				=	 _piAddress + 2;
	piItemAddress	= piOffset + iItem  + 1 + !(iItem % 2);
	*_piItemAddress	= piItemAddress + (piOffset[_iItemNum - 1] - 1) * (sizeof(double) / sizeof(int));
	return 0;
}

int createList(int _iVar, int _iNbItem, int** _piAddress)
{
	return createCommonList(_iVar, sci_list, _iNbItem, _piAddress);
}

int createMList(int _iVar, int _iNbItem, int** _piAddress)
{
	return createCommonList(_iVar, sci_mlist, _iNbItem, _piAddress);
}

int createTList(int _iVar, int _iNbItem, int** _piAddress)
{
	return createCommonList(_iVar, sci_tlist, _iNbItem, _piAddress);
}

int createNamedList(char* _pstName, int _iNameLen, int _iNbItem, int** _piAddress)
{
	return createCommonNamedList(_pstName, _iNameLen, sci_list, _iNbItem, _piAddress);
}

int createNamedTList(char* _pstName, int _iNameLen, int _iNbItem, int** _piAddress)
{
	return createCommonNamedList(_pstName, _iNameLen, sci_tlist, _iNbItem, _piAddress);
}

int createNamedMList(char* _pstName, int _iNameLen, int _iNbItem, int** _piAddress)
{
	return createCommonNamedList(_pstName, _iNameLen, sci_mlist, _iNbItem, _piAddress);
}

static int createCommonNamedList(char* _pstName, int _iNameLen, int _iListType, int _iNbItem, int** _piAddress)
{
	int iVarID[nsiz];
  int iSaveRhs			= Rhs;
	int iSaveTop			= Top;
	int iRet					= 0;
	int *piAddr				= NULL;
	int* piEnd				= NULL;

  C2F(str2name)(_pstName, iVarID, _iNameLen);
  Top = Top + Nbvars + 1;

	iRet = getNewVarAddressFromPosition(Top, &piAddr);
	fillCommonList(piAddr, _iListType, _iNbItem);

	piEnd = piAddr + 3 + _iNbItem + !(_iNbItem % 2);
	closeList(Top, piEnd);


	Rhs = 0;
	
	if(_iNbItem == 0)
	{//Add name in stack reference list
		createNamedVariable(iVarID);
	}

	Top						= iSaveTop;
  Rhs						= iSaveRhs;

	*_piAddress = piAddr;
	return 0;
}

static int createCommonList(int _iVar, int _iListType, int _iNbItem, int** _piAddress)
{
	int *piAddr			= NULL;
	int iNewPos			= Top - Rhs + _iVar;
	int iAddr				= *Lstk(iNewPos);

	int iRet = getNewVarAddressFromPosition(iNewPos, &piAddr);
	if(iRet)
	{
		return 1;
	}

	iRet = fillCommonList(piAddr, _iListType, _iNbItem);
	if(iRet)
	{
		return 1;
	}

	*_piAddress	= piAddr;
	updateInterSCI(_iVar, '$', iAddr, sadr(iadr(iAddr) + 2 + _iNbItem + 1 + !(_iNbItem % 2)));
	closeList(iNewPos, piAddr + 2 + _iNbItem + 1 + !(_iNbItem % 2));

	return 0;
}

int fillCommonList(int* _piAddress, int _iListType, int _iNbItem)
{
	int i					= 0;
	int* piOffset = NULL;

	_piAddress[0]	= _iListType;
	_piAddress[1] = _iNbItem;

	piOffset		= _piAddress + 2;
	piOffset[0]	= 1; //always

	for(i = 0 ; i < _iNbItem; i++)
	{//initialize item offset
		piOffset[i + 1] = -1;
	}
	return 0;
}

int readNamedList(char* _pstName, int _iNameLen, int* _piNbItem, int** _piAddress)
{
	return readCommonNamedList(_pstName, _iNameLen, sci_list, _piNbItem, _piAddress);
}

int readNamedTList(char* _pstName, int _iNameLen, int* _piNbItem, int** _piAddress)
{
	return readCommonNamedList(_pstName, _iNameLen, sci_tlist, _piNbItem, _piAddress);
}

int readNamedMList(char* _pstName, int _iNameLen, int* _piNbItem, int** _piAddress)
{
	return readCommonNamedList(_pstName, _iNameLen, sci_mlist, _piNbItem, _piAddress);
}

static int readCommonNamedList(char* _pstName, int _iNameLen, int _iListType, int* _piNbItem, int** _piAddress)
{
	int* piAddr		= NULL;
	int iNbItem		= 0;
	int iRet			= 0;

	iRet = getVarAddressFromName(_pstName, _iNameLen, &piAddr);
	if(iRet)
	{
		return 1;
	}

	if(piAddr[0] != _iListType)
	{
		return 1;
	}

	iRet = getListItemNumber(piAddr, &iNbItem);
	if(iRet)
	{
		return 1;
	}

	*_piNbItem = iNbItem;
	*_piAddress = piAddr;

	return 0;
}

int getListInList(int _iVar, int* _piParent, int _iItemPos, int** _piAddress)
{
	return getCommonListInList(_iVar, _piParent, _iItemPos, sci_list, _piAddress);
}

int getTListInList(int _iVar, int* _piParent, int _iItemPos, int** _piAddress)
{
	return getCommonListInList(_iVar, _piParent, _iItemPos, sci_tlist, _piAddress);
}

int getMListInList(int _iVar, int* _piParent, int _iItemPos, int** _piAddress)
{
	return getCommonListInList(_iVar, _piParent, _iItemPos, sci_mlist, _piAddress);
}

int getCommonListInList(int _iVar, int* _piParent, int _iItemPos, int _iListType, int** _piAddress)
{
	int iRet			= 0;

	iRet = getListItemAddress(_piParent, _iItemPos, _piAddress);
	if(iRet)
	{
		return 1;
	}

	if((*_piAddress)[0] != _iListType)
	{
		return 1;
	}
	return 0;
}

int getListInNamedList(char* _pstName, int _iNameLen, int* _piParent, int _iItemPos, int** _piAddress)
{
	return getCommomListInNamedList(_pstName, _iNameLen, _piParent, _iItemPos, sci_list, _piAddress);
}

int getTListInNamedList(char* _pstName, int _iNameLen, int* _piParent, int _iItemPos, int** _piAddress)
{
	return getCommomListInNamedList(_pstName, _iNameLen, _piParent, _iItemPos, sci_tlist, _piAddress);
}

int getMListInNamedList(char* _pstName, int _iNameLen, int* _piParent, int _iItemPos, int** _piAddress)
{
	return getCommomListInNamedList(_pstName, _iNameLen, _piParent, _iItemPos, sci_mlist, _piAddress);
}

int getCommomListInNamedList(char* _pstName, int _iNameLen, int* _piParent, int _iItemPos, int _iListType, int** _piAddress)
{
	int* piAddr		= NULL;

	getListItemAddress(_piParent, _iItemPos, &piAddr);

	if(piAddr[0] != _iListType)
	{
		return 1;
	}

	*_piAddress = piAddr;
	return 0;
}

/*********************
 * Double functions *
 *********************/

int getMatrixOfDoubleInList(int _iVar, int* _piParent, int _iItemPos, int* _piRows, int* _piCols, double** _pdblReal)
{
	return getCommonMatrixOfDoubleInList(_iVar, _piParent,_iItemPos, 0, _piRows, _piCols, _pdblReal, NULL);
}

int getComplexMatrixOfDoubleInList(int _iVar, int* _piParent, int _iItemPos, int* _piRows, int* _piCols, double** _pdblReal, double** _pdblImg)
{
	return getCommonMatrixOfDoubleInList(_iVar, _piParent,_iItemPos, 1, _piRows, _piCols, _pdblReal, _pdblImg);
}

static int getCommonMatrixOfDoubleInList(int _iVar, int* _piParent, int _iItemPos, int _iComplex, int* _piRows, int* _piCols, double** _pdblReal, double** _pdblImg)
{
	int iRet			= 0;
	int* piAddr		= NULL;

	iRet = getListItemAddress(_piParent, _iItemPos, &piAddr);
	if(iRet)
	{
		return 1;
	}

	iRet = getCommonMatrixOfDouble(piAddr, _iComplex, _piRows, _piCols, _pdblReal, _pdblImg);
	if(iRet)
	{
		return 1;
	}
	return 0;
}

int allocMatrixOfDoubleInList(int _iVar, int* _piParent, int _iItemPos, int _iRows, int _iCols, double** _pdblReal)
{
	return allocCommonMatrixOfDoubleInList(_iVar, _piParent, _iItemPos, 0, _iRows, _iCols, _pdblReal, NULL);
}

int allocComplexMatrixOfDoubleInList(int _iVar, int* _piParent, int _iItemPos, int _iRows, int _iCols, double** _pdblReal, double** _pdblImg)
{
	return allocCommonMatrixOfDoubleInList(_iVar, _piParent, _iItemPos, 1, _iRows, _iCols, _pdblReal, _pdblImg);
}

static int allocCommonMatrixOfDoubleInList(int _iVar, int* _piParent, int _iItemPos, int _iComplex, int _iRows, int _iCols, double** _pdblReal, double** _pdblImg)
{
	int iNewPos				= Top - Rhs + _iVar;
	int* piEnd				= NULL;

	fillCommonMatrixOfDoubleInList(_iVar, _piParent, _iItemPos, _iComplex, _iRows, _iCols, _pdblReal, _pdblImg);

	piEnd = (int*) (*_pdblReal + _iRows * _iCols * (_iComplex + 1));
	closeList(iNewPos, piEnd);

	if(_iItemPos == _piParent[1])
	{
		updateListOffset(_iVar, _piParent, _iItemPos, piEnd);
	}

	return 0;
}

static int fillCommonMatrixOfDoubleInList(int _iVar, int* _piParent, int _iItemPos, int _iComplex, int _iRows, int _iCols, double** _pdblReal, double** _pdblImg)
{
	int iRet					= 0;
	int iNbItem				= 0;
	int* piOffset			= NULL;
	int* piChildAddr	= NULL;

	//Does item can be added in the list
	getListItemNumber(_piParent, &iNbItem);
	if(iNbItem < _iItemPos)
	{
		return 1;
	}


	iRet = allocCommonItemInList(_piParent, _iItemPos, &piChildAddr);
	if(iRet)
	{
		return 1;
	}

	iRet = fillCommonMatrixOfDouble(piChildAddr, _iComplex, _iRows, _iCols, _pdblReal, _pdblImg);
	if(iRet)
	{
		return 1;
	}

	piOffset						= _piParent + 2;
	piOffset[_iItemPos] = piOffset[_iItemPos - 1] + _iRows * _iCols * (_iComplex + 1) + 2;

	return 0;
}


int	allocCommonItemInList(int* _piParent, int _iItemPos, int** _piChildAddr)
{
	int iRet			= 0;
	int* piOffset = NULL;

	//Does previous items was already inserted
	piOffset		= _piParent + 2;
	if(piOffset[_iItemPos - 1] == -1)
	{//Previous items wasn't inserted
		return 1;
	}

	iRet = getListItemAddress(_piParent, _iItemPos, _piChildAddr);
	if(iRet)
	{
		return 1;
	}
	return 0;
}

int createMatrixOfDoubleInList(int _iVar, int* _piParent, int _iItemPos, int _iRows, int _iCols, double* _pdblReal)
{
	return createCommonMatrixOfDoubleInList(_iVar, _piParent, _iItemPos, 0, _iRows, _iCols, _pdblReal, NULL);
}

int createComplexMatrixOfDoubleInList(int _iVar, int* _piParent, int _iItemPos, int _iRows, int _iCols, double* _pdblReal, double* _pdblImg)
{
	return createCommonMatrixOfDoubleInList(_iVar, _piParent, _iItemPos, 1, _iRows, _iCols, _pdblReal, _pdblImg);
}

int createCommonMatrixOfDoubleInList(int _iVar, int* _piParent, int _iItemPos, int _iComplex, int _iRows, int _iCols, double* _pdblReal, double* _pdblImg)
{
	double *pdblReal	= NULL;
	double *pdblImg		= NULL;

	int iRet = 0;

	iRet = allocCommonMatrixOfDoubleInList(_iVar, _piParent, _iItemPos, _iComplex, _iRows, _iCols, &pdblReal, &pdblImg);
	if(iRet)
	{
		return 1;
	}
	if(_pdblReal != NULL)
	{
		memcpy(pdblReal, _pdblReal, _iRows * _iCols * sizeof(double));
	}

	if(_iComplex && _pdblImg != NULL)
	{
		memcpy(pdblImg, _pdblImg, _iRows * _iCols * sizeof(double));
	}
	return 0;
}

int createMatrixOfDoubleInNamedList(char* _pstName, int _iNameLen, int* _piParent, int _iItemPos, int _iRows, int _iCols, double* _pdblReal)
{
	return createCommomMatrixOfDoubleInNamedList(_pstName, _iNameLen, _piParent, _iItemPos, 0, _iRows, _iCols, _pdblReal, NULL);
}

int createComplexMatrixOfDoubleInNamedList(char* _pstName, int _iNameLen, int* _piParent, int _iItemPos, int _iRows, int _iCols, double* _pdblReal, double* _pdblImg)
{
	return createCommomMatrixOfDoubleInNamedList(_pstName, _iNameLen, _piParent, _iItemPos, 1, _iRows, _iCols, _pdblReal, _pdblImg);
}

int createCommomMatrixOfDoubleInNamedList(char* _pstName, int _iNameLen, int* _piParent, int _iItemPos, int _iComplex, int _iRows, int _iCols, double* _pdblReal, double* _pdblImg)
{
	int iVarID[nsiz];
  int iSaveRhs			= Rhs;
	int iSaveTop			= Top;
	int iRet					= 0;
	int *piAddr				= NULL;
	double *pdblReal	= NULL;
	double *pdblImg		= NULL;
	int* piEnd				= NULL;
	int* piChildAddr	= NULL;

  C2F(str2name)(_pstName, iVarID, _iNameLen);
  Top = Top + Nbvars + 1;

	iRet = getNewVarAddressFromPosition(Top, &piAddr);
	if(iRet)
	{
		return 1;
	}

	iRet = fillCommonMatrixOfDoubleInList(Top, _piParent, _iItemPos, _iComplex, _iRows, _iCols, &pdblReal, &pdblImg);
	if(iRet)
	{
		return 1;
	}

	memcpy(pdblReal, _pdblReal, sizeof(double) * _iRows * _iCols);
	if(_iComplex)
	{
		memcpy(pdblImg, _pdblImg, sizeof(double) * _iRows * _iCols);
	}

	iRet = allocCommonItemInList(_piParent, _iItemPos, &piChildAddr);
	if(iRet)
	{
		return 1;
	}

	piEnd = piChildAddr + 4 + (_iRows * _iCols * 2);
	closeList(Top, piEnd);

	if(_iItemPos == _piParent[1])
	{
		updateNamedListOffset(Top, _piParent, _iItemPos, piEnd);
		createNamedVariable(iVarID);
	}

	Top = iSaveTop;
  Rhs = iSaveRhs;

	return 0;
}

int createListInList(int _iVar, int* _piParent, int _iItemPos, int _iNbItem, int** _piAddress)
{
	return createCommonListInList(_iVar, _piParent, _iItemPos, sci_list, _iNbItem, _piAddress, 0);
}

int createTListInList(int _iVar, int* _piParent, int _iItemPos, int _iNbItem, int** _piAddress)
{
	return createCommonListInList(_iVar, _piParent, _iItemPos, sci_tlist, _iNbItem, _piAddress, 0);
}

int createMListInList(int _iVar, int* _piParent, int _iItemPos, int _iNbItem, int** _piAddress)
{
	return createCommonListInList(_iVar, _piParent, _iItemPos, sci_mlist, _iNbItem, _piAddress, 0);
}

static int createCommonListInList(int _iVar, int* _piParent, int _iItemPos, int _iListType, int _iNbItem, int** _piAddress, int iNamed)
{
	int iRet					= 0;
	int iNewPos				= Top - Rhs + _iVar;
	int iNbItem				= 0;
	int* piChildAddr	= NULL;

	//Does item can be added in the list
	getListItemNumber(_piParent, &iNbItem);
	if(iNbItem < _iItemPos)
	{
		return 1;
	}

	iRet = allocCommonItemInList(_piParent, _iItemPos, &piChildAddr);
	if(iRet)
	{
		return 1;
	}

	iRet = fillCommonList(piChildAddr, _iListType, _iNbItem);
	if(iRet)
	{
		return 1;
	}

	*_piAddress = piChildAddr;
		if(iNamed)
		{
			closeList(_iVar, piChildAddr + 2 + _iNbItem + 1 + !(_iNbItem % 2));
		}
		else
		{
			closeList(iNewPos, piChildAddr + 2 + _iNbItem + 1 + !(_iNbItem % 2));
		}

	if(_iNbItem == 0)
	{//for empty list
		int *piOffset				= _piParent + 2;
		int* piEnd					= piChildAddr + 4;

		piOffset[_iItemPos] = piOffset[_iItemPos - 1] + 2;
		if(iNamed)
		{
			updateNamedListOffset(_iVar, _piParent, _iItemPos, piEnd);
		}
		else
		{
			updateListOffset(_iVar, _piParent, _iItemPos, piEnd);
		}
	}

	return 0;
}

int createListInNamedList(char* _pstName, int _iNameLen, int* _piParent, int _iItemPos, int _iNbItem, int** _piAddress)
{
	return createCommonListInNamedList(_pstName, _iNameLen, _piParent, _iItemPos, sci_list, _iNbItem, _piAddress);
}

int createTListInNamedList(char* _pstName, int _iNameLen, int* _piParent, int _iItemPos, int _iNbItem, int** _piAddress)
{
	return createCommonListInNamedList(_pstName, _iNameLen, _piParent, _iItemPos, sci_tlist, _iNbItem, _piAddress);
}

int createMListInNamedList(char* _pstName, int _iNameLen, int* _piParent, int _iItemPos, int _iNbItem, int** _piAddress)
{
	return createCommonListInNamedList(_pstName, _iNameLen, _piParent, _iItemPos, sci_mlist, _iNbItem, _piAddress);
}

int createCommonListInNamedList(char* _pstName, int _iNameLen, int* _piParent, int _iItemPos, int _iListType, int _iNbItem, int** _piAddress)
{
	int iVarID[nsiz];
	int iRet = 0;
	int iSaveTop = Top;

  C2F(str2name)(_pstName, iVarID, _iNameLen);
	Top = Top + Nbvars + 1;

	iRet = createCommonListInList(Top, _piParent, _iItemPos, _iListType, _iNbItem, _piAddress, 1);

	if(_iNbItem == 0 && _iItemPos == _piParent[1])
	{
		int* piEnd = *_piAddress + 4;
		updateNamedListOffset(Top, _piParent, _iItemPos, piEnd);
		createNamedVariable(iVarID);
	}

	Top = iSaveTop;
	return iRet;
}


int readMatrixOfDoubleInNamedList(char* _pstName, int _iNameLen, int* _piParent, int _iItemPos, int* _piRows, int* _piCols, double* _pdblReal)
{
	return readCommonMatrixOfDoubleInNamedList(_pstName, _iNameLen, _piParent, _iItemPos, 0, _piRows, _piCols, _pdblReal, NULL);
}

int readComplexMatrixOfDoubleInNamedList(char* _pstName, int _iNameLen, int* _piParent, int _iItemPos, int* _piRows, int* _piCols, double* _pdblReal, double* _pdblImg)
{
	return readCommonMatrixOfDoubleInNamedList(_pstName, _iNameLen, _piParent, _iItemPos, 1, _piRows, _piCols, _pdblReal, _pdblImg);
}

static int readCommonMatrixOfDoubleInNamedList(char* _pstName, int _iNameLen, int* _piParent, int _iItemPos, int _iComplex, int* _piRows, int* _piCols, double* _pdblReal, double* _pdblImg)
{
	int iRet					= 0;
	int* piAddr				= NULL;
	double* pdblReal	= NULL;
	double* pdblImg		= NULL;

	iRet = getListItemAddress(_piParent, _iItemPos, &piAddr);
	if(iRet)
	{
		return 1;
	}

	iRet = getCommonMatrixOfDouble(piAddr, _iComplex, _piRows, _piCols, &pdblReal, &pdblImg);
	if(iRet)
	{
		return 1;
	}

	if(_pdblReal == NULL || (_iComplex && _pdblImg == NULL))
	{
		return 0;
	}

	memcpy(_pdblReal, pdblReal, sizeof(double) * *_piRows * *_piCols);
	if(_iComplex)
	{
		memcpy(_pdblImg, pdblImg, sizeof(double) * *_piRows * *_piCols);
	}
	return 0;
}


/*********************
 * Strings functions *
 *********************/

int getMatrixOfStringInList(int _iVar, int* _piParent, int _iItemPos, int* _piRows, int* _piCols, int* _piLength, char** _pstStrings)
{
	int iRet			= 0;
	int* piAddr		= NULL;

	iRet = getListItemAddress(_piParent, _iItemPos, &piAddr);
	if(iRet)
	{
		return 1;
	}

	iRet = getMatrixOfString(piAddr, _piRows, _piCols, _piLength, _pstStrings);
	if(iRet)
	{
		return 1;
	}
	return 0;
}


int createMatrixOfStringInList(int _iVar, int* _piParent, int _iItemPos, int _iRows, int _iCols, char** _pstStrings)
{
	int iRet					= 0;
	int iNbItem				= 0;
	int iTotalLen			= 0;
	int iNewPos				= Top - Rhs + _iVar;

	int* piItemAddr		= NULL;
	int* piEnd				= NULL;

	iRet = getListItemAddress(_piParent, _iItemPos, &piItemAddr);
	if(iRet)
	{
		return 1;
	}

	iRet = fillCommonMatrixOfStringInList(_iVar, _piParent, _iItemPos, _iRows, _iCols, _pstStrings, &iTotalLen);
	if(iRet)
	{
		return 1;
	}

	piEnd = piItemAddr + iTotalLen + 5 + _iRows * _iCols + !((iTotalLen + _iRows * _iCols) % 2);
	closeList(iNewPos, piEnd);

	if(_iItemPos == iNbItem)
	{
		updateListOffset(_iVar, _piParent, _iItemPos, piEnd);
	}

	return 0;
}

int fillCommonMatrixOfStringInList(int _iVar, int* _piParent, int _iItemPos, int _iRows, int _iCols, char** _pstStrings, int* _piTotalLen)
{
	int iRet				= 0;
	int iNbItem			= 0;

	int* piAddr			= NULL;
	int* piOffset		= NULL;

	//Does item can be added in the list
	getListItemNumber(_piParent, &iNbItem);
	if(iNbItem < _iItemPos)
	{
		return 1;
	}

	iRet = allocCommonItemInList(_piParent, _iItemPos, &piAddr);
	if(iRet)
	{
		return 1;
	}

	iRet = fillMatrixOfString(piAddr, _iRows, _iCols, _pstStrings, _piTotalLen);
	if(iRet)
	{
		return 1;
	}

	piOffset						= _piParent + 2;
	piOffset[_iItemPos] = piOffset[_iItemPos - 1] + (*_piTotalLen + 5 + _iRows * _iCols + !((*_piTotalLen + _iRows * _iCols) %2)) / 2;

	return 0;
}

int createMatrixOfStringInNamedList(char* _pstName, int _iNameLen, int* _piParent, int _iItemPos, int _iRows, int _iCols, char** _pstStrings)
{
	int iVarID[nsiz];
	int iRet					= 0;
	int iTotalLen			= 0;
	int iSaveRhs			= Rhs;
	int iSaveTop			= Top;

	int* piItemAddr		= NULL;
	int* piEnd				= NULL;

  C2F(str2name)(_pstName, iVarID, _iNameLen);
	Top = Top + Nbvars + 1;

	iRet = getListItemAddress(_piParent, _iItemPos, &piItemAddr);
	if(iRet)
	{
		return 1;
	}

	iRet = fillCommonMatrixOfStringInList(Top, _piParent, _iItemPos, _iRows, _iCols, _pstStrings, &iTotalLen);
	if(iRet)
	{
		return 1;
	}

	piEnd = piItemAddr + (iTotalLen + 5 + _iRows * _iCols + !((_iRows * _iCols) %2));
	closeList(Top, piEnd);

	if(_iItemPos == _piParent[1])
	{
		updateNamedListOffset(Top, _piParent, _iItemPos, piEnd);
		createNamedVariable(iVarID);
	}

	Top = iSaveTop;
  Rhs = iSaveRhs;


	return 0;
}

int readMatrixOfStringInNamedList(char* _pstName, int _iNameLen, int* _piParent, int _iItemPos, int* _piRows, int* _piCols, int* _piLength, char** _pstStrings)
{
	return 0;
}

/*********************
 * boolean functions *
 *********************/

int getMatrixOfBooleanInList(int _iVar, int* _piParent, int _iItemPos, int* _piRows, int* _piCols, int** _piBool)
{
	int iRet			= 0;
	int* piAddr		= NULL;

	iRet = getListItemAddress(_piParent, _iItemPos, &piAddr);
	if(iRet)
	{
		return 1;
	}

	iRet = getMatrixOfBoolean(piAddr, _piRows, _piCols, _piBool);
	if(iRet)
	{
		return 1;
	}
	return 0;
}

int createMatrixOfBooleanInList(int _iVar, int* _piParent, int _iItemPos, int _iRows, int _iCols, int* _piBool)
{
	int *piBool			= NULL;

	int iRet = 0;

	iRet = allocMatrixOfBooleanInList(_iVar, _piParent, _iItemPos, _iRows, _iCols, &piBool);
	if(iRet)
	{
		return 1;
	}
	if(_piBool != NULL)
	{
		memcpy(piBool, _piBool, _iRows * _iCols * sizeof(int));
	}
	return 0;
}

int allocMatrixOfBooleanInList(int _iVar, int* _piParent, int _iItemPos, int _iRows, int _iCols, int** _piBool)
{
	int iNewPos				= Top - Rhs + _iVar;
	int* piEnd				= NULL;

	fillMatrixOfBoolInList(_iVar, _piParent, _iItemPos, _iRows, _iCols, _piBool);

	piEnd = *_piBool + _iRows * _iCols + !((_iRows * _iCols) % 2);
	closeList(iNewPos, piEnd);

	if(_iItemPos == _piParent[1])
	{
		updateListOffset(_iVar, _piParent, _iItemPos, piEnd);
	}
	return 0;
}

static int fillMatrixOfBoolInList(int _iVar, int* _piParent, int _iItemPos, int _iRows, int _iCols, int** _piBool)
{
	int iRet					= 0;
	int iNbItem				= 0;
	int* piOffset			= NULL;
	int* piChildAddr	= NULL;

	//Does item can be added in the list
	getListItemNumber(_piParent, &iNbItem);
	if(iNbItem < _iItemPos)
	{
		return 1;
	}


	iRet = allocCommonItemInList(_piParent, _iItemPos, &piChildAddr);
	if(iRet)
	{
		return 1;
	}

	iRet = fillMatrixOfBoolean(piChildAddr, _iRows, _iCols, _piBool);
	if(iRet)
	{
		return 1;
	}

	piOffset						= _piParent + 2;
	piOffset[_iItemPos] = piOffset[_iItemPos - 1] + ((3 + _iRows * _iCols + !((_iRows * _iCols) % 2)) / 2);

	return 0;
}

int createMatrixOfBooleanInNamedList(char* _pstName, int _iNameLen, int* _piParent, int _iItemPos, int _iRows, int _iCols, int* _piBool)
{
	int iVarID[nsiz];
  int iSaveRhs			= Rhs;
	int iSaveTop			= Top;
	int iRet					= 0;
	int *piAddr				= NULL;
	int* piBool				= NULL;
	int* piEnd				= NULL;
	int* piChildAddr	= NULL;

  C2F(str2name)(_pstName, iVarID, _iNameLen);
  Top = Top + Nbvars + 1;

	iRet = getNewVarAddressFromPosition(Top, &piAddr);
	if(iRet)
	{
		return 1;
	}

	iRet = fillMatrixOfBoolInList(Top, _piParent, _iItemPos, _iRows, _iCols, &piBool);
	if(iRet)
	{
		return 1;
	}

	memcpy(piBool, _piBool, sizeof(int) * _iRows * _iCols);

	iRet = allocCommonItemInList(_piParent, _iItemPos, &piChildAddr);
	if(iRet)
	{
		return 1;
	}

	piEnd = piChildAddr + 4 + (_iRows * _iCols) + ((_iRows * _iCols) % 2);
	closeList(Top, piEnd);

	if(_iItemPos == _piParent[1])
	{
		updateNamedListOffset(Top, _piParent, _iItemPos, piEnd);
		createNamedVariable(iVarID);
	}

	Top = iSaveTop;
  Rhs = iSaveRhs;

	return 0;
}

/*************************
 * polynomials functions *
 *************************/

int getMatrixOfPolyInList(int _iVar, int* _piParent, int _iItemPos, int* _piRows, int* _piCols, int* _piNbCoef, double** _pdblReal)
{
	return getCommonxMatrixOfPolyInList(_iVar, _piParent, _iItemPos, 0, _piRows, _piCols, _piNbCoef, _pdblReal, NULL);
}

int getComplexMatrixOfPolyInList(int _iVar, int* _piParent, int _iItemPos, int* _piRows, int* _piCols, int* _piNbCoef, double** _pdblReal, double** _pdblImg)
{
	return getCommonxMatrixOfPolyInList(_iVar, _piParent, _iItemPos, 1, _piRows, _piCols, _piNbCoef, _pdblReal, _pdblImg);
}

int getCommonxMatrixOfPolyInList(int _iVar, int* _piParent, int _iItemPos, int _iComplex, int* _piRows, int* _piCols, int* _piNbCoef, double** _pdblReal, double** _pdblImg)
{
	int iRet			= 0;
	int* piAddr		= NULL;

	iRet = getListItemAddress(_piParent, _iItemPos, &piAddr);
	if(iRet)
	{
		return 1;
	}

	iRet = getCommonMatrixOfPoly(piAddr, _iComplex, _piRows, _piCols, _piNbCoef, _pdblReal, _pdblImg);
	if(iRet)
	{
		return 1;
	}
	return 0;
}

int createMatrixOfPolyInList(int _iVar, int* _piParent, int _iItemPos, char* _pstVarName, int _iRows, int _iCols, int* _piNbCoef, double** _pdblReal)
{
	return createCommonMatrixOfPolyInList(_iVar, _piParent, _iItemPos, _pstVarName, 0, _iRows, _iCols, _piNbCoef, _pdblReal, NULL);
}

int createComplexMatrixOfPolyInList(int _iVar, int* _piParent, int _iItemPos, char* _pstVarName, int _iRows, int _iCols, int* _piNbCoef, double** _pdblReal, double** _pdblImg)
{
	return createCommonMatrixOfPolyInList(_iVar, _piParent, _iItemPos, _pstVarName, 1, _iRows, _iCols, _piNbCoef, _pdblReal, _pdblImg);
}

int createCommonMatrixOfPolyInList(int _iVar, int* _piParent, int _iItemPos, char* _pstVarName, int _iComplex, int _iRows, int _iCols, int* _piNbCoef, double** _pdblReal, double** _pdblImg)
{
	int iRet						= 0;
	int* piItemAddr			= NULL;
	int *piEnd					= NULL;
	int iItemLen				= 0;
	int iTotalLen				= 0;

	iRet = getListItemAddress(_piParent, _iItemPos, &piItemAddr);
	if(iRet)
	{
		return 1;
	}

	iRet = fillCommonMatrixOfPolyInList(_iVar, _piParent, _iItemPos, _pstVarName, _iComplex, _iRows, _iCols, _piNbCoef, _pdblReal, _pdblImg, &iTotalLen);
	if(iRet)
	{
		return 1;
	}

	iItemLen						= 9 + _iRows * _iCols + (9 + _iRows * _iCols)%2;
	iItemLen						+= iTotalLen;
	piEnd								=	piItemAddr + iItemLen;
	if(_iItemPos == _piParent[1])
	{
		updateListOffset(_iVar, _piParent, _iItemPos, piEnd);
	}

	closeList(_iVar, piEnd);

	return 0;
}

static int fillCommonMatrixOfPolyInList(int _iVar, int* _piParent, int _iItemPos, char* _pstVarName, int _iComplex, int _iRows, int _iCols, int* _piNbCoef, double** _pdblReal, double** _pdblImg, int* _piTotalLen)
{
	int iRet					= 0;
	int iNbItem				= 0;
	int iTotalLen			= 0;
	int* piOffset			= NULL;
	int* piChildAddr	= NULL;

	int iItemLen			= 0;

	//Does item can be added in the list
	getListItemNumber(_piParent, &iNbItem);
	if(iNbItem < _iItemPos)
	{
		return 1;
	}

	iRet = allocCommonItemInList(_piParent, _iItemPos, &piChildAddr);
	if(iRet)
	{
		return 1;
	}

	iRet = fillCommonMatrixOfPoly(piChildAddr, _pstVarName, _iComplex, _iRows, _iCols, _piNbCoef, _pdblReal, _pdblImg, &iTotalLen);
	if(iRet)
	{
		return 1;
	}

	piOffset						= _piParent + 2;

	iItemLen						= 9 + _iRows * _iCols + (9 + _iRows * _iCols)%2;
	iItemLen						+= iTotalLen;
	piOffset[_iItemPos] = piOffset[_iItemPos - 1] + ((iItemLen + 1) / 2);

	*_piTotalLen = iTotalLen;
	return 0;
}


int createMatrixOfPolyInNamedList(char* _pstName, int _iNameLen, int* _piParent, int _iItemPos, char* _pstVarName, int _iRows, int _iCols, int* _piNbCoef, double** _pdblReal)
{
	return createCommonMatrixOfPolyInNamedList(_pstName, _iNameLen, _piParent, _iItemPos, _pstVarName, 0, _iRows, _iCols, _piNbCoef, _pdblReal, NULL);
}

int createComplexMatrixOfPolyInNamedList(char* _pstName, int _iNameLen, int* _piParent, int _iItemPos, char* _pstVarName, int _iRows, int _iCols, int* _piNbCoef, double** _pdblReal, double** _pdblImg)
{
	return createCommonMatrixOfPolyInNamedList(_pstName, _iNameLen, _piParent, _iItemPos, _pstVarName, 1, _iRows, _iCols, _piNbCoef, _pdblReal, _pdblImg);
}

int createCommonMatrixOfPolyInNamedList(char* _pstName, int _iNameLen, int* _piParent, int _iItemPos, char* _pstVarName, int _iComplex, int _iRows, int _iCols, int* _piNbCoef, double** _pdblReal, double** _pdblImg)
{
	int iVarID[nsiz];
  int iSaveRhs			= Rhs;
	int iSaveTop			= Top;
	int iRet					= 0;
	int *piAddr				= NULL;
	int* piEnd				= NULL;
	int* piChildAddr	= NULL;
	int iTotalLen			= 0;
	int iItemLen			= 0;

  C2F(str2name)(_pstName, iVarID, _iNameLen);
  Top = Top + Nbvars + 1;

	iRet = getNewVarAddressFromPosition(Top, &piAddr);
	if(iRet)
	{
		return 1;
	}

	iRet = fillCommonMatrixOfPolyInList(Top, _piParent, _iItemPos, _pstVarName, _iComplex, _iRows, _iCols, _piNbCoef, _pdblReal, _pdblImg, &iTotalLen);
	if(iRet)
	{
		return 1;
	}

	iItemLen						= 9 + _iRows * _iCols + (9 + _iRows * _iCols)%2;
	iItemLen						+= iTotalLen;

	getListItemAddress(_piParent, _iItemPos, &piChildAddr);
	piEnd								=	piChildAddr + iItemLen;
	closeList(Top, piEnd);

	if(_iItemPos == _piParent[1])
	{
		updateNamedListOffset(Top, _piParent, _iItemPos, piEnd);
		createNamedVariable(iVarID);
	}


	Top = iSaveTop;
  Rhs = iSaveRhs;

	return 0;
}

int readMatrixOfPolyInNamedList(char* _pstName, int _iNameLen, int _piParent, int _iItemPos, int* _piRows, int* _piCols, int* _piNbCoef, double** _pdblReal)
{
	return readCommonMatrixOfPolyInNamedList(_pstName, _iNameLen, _piParent, _iItemPos, 0, _piRows, _piCols, _piNbCoef, _pdblReal, NULL);
}

int readComplexMatrixOfPolyInNamedList(char* _pstName, int _iNameLen, int _piParent, int _iItemPos, int* _piRows, int* _piCols, int* _piNbCoef, double** _pdblReal, double** _pdblImg)
{
	return readCommonMatrixOfPolyInNamedList(_pstName, _iNameLen, _piParent, _iItemPos, 1, _piRows, _piCols, _piNbCoef, _pdblReal, _pdblImg);
}

int readCommonMatrixOfPolyInNamedList(char* _pstName, int _iNameLen, int _piParent, int _iItemPos, int _iComplex, int* _piRows, int* _piCols, int* _piNbCoef, double** _pdblReal, double** _pdblImg)
{
//TODO !!!!!
}

int allocMatrixOfInteger8InList(int _iVar, int* _piParent, int _iItemPos, int _iRows, int _iCols, char* _pcData)
{
}

int allocMatrixOfInteger16InList(int _iVar, int* _piParent, int _iItemPos, int _iRows, int _iCols, short* _psData)
{
}

int allocMatrixOfInteger32InList(int _iVar, int* _piParent, int _iItemPos, int _iRows, int _iCols, int* _piData)
{
}

int createMatrixOfInteger8InList(int _iVar, int* _piParent, int _iItemPos, int _iRows, int _iCols, char* _pcData)
{
}

int createMatrixOfInteger16InList(int _iVar, int* _piParent, int _iItemPos, int _iRows, int _iCols, short* _psData)
{
}

int createMatrixOfInteger32InList(int _iVar, int* _piParent, int _iItemPos, int _iRows, int _iCols, int* _piData)
{
}


int createMatrixOfInteger8InNamedList(char* _pstName, int _iNameLen, int* _piParent, int _iItemPos, int _iRows, int _iCols, char* _pcData)
{

}

int createMatrixOfInteger16InNamedList(char* _pstName, int _iNameLen, int* _piParent, int _iItemPos, int _iRows, int _iCols, short* _psData)
{

}

int createMatrixOfInteger32InNamedList(char* _pstName, int _iNameLen, int* _piParent, int _iItemPos, int _iRows, int _iCols, int* _piData)
{
}



static void updateNamedListOffset(int _iVar, int *_piCurrentNode, int _iItemPos, int *_piEnd)
{
	updateCommunListOffset(_iVar, _piCurrentNode, _iItemPos, _piEnd);
}

static void updateListOffset(int _iVar, int *_piCurrentNode, int _iItemPos, int *_piEnd)
{
	int iNewPos				= Top - Rhs + _iVar;
	updateCommunListOffset(iNewPos, _piCurrentNode, _iItemPos, _piEnd);
}

//internal tool functions
static void updateCommunListOffset(int _iVar, int *_piCurrentNode, int _iItemPos, int *_piEnd)
{
	//find list depth and update list offset for last item
	int i							= 0;
	int *piRoot				= istk(iadr(*Lstk(_iVar)));
	int iDepth				= 1; //we are already in a list
	int iMaxDepth			= 0; //we are already in a list
	int **piParent			= NULL;

	getParentList(piRoot, _piCurrentNode, &iDepth, NULL);
	piParent = (int**)MALLOC(sizeof(int*) * iDepth);
	iMaxDepth = iDepth;
	iDepth = 1;
	piParent[0] = piRoot;
	getParentList(piRoot, _piCurrentNode, &iDepth, piParent);
	for(i = iMaxDepth - 2 ; i >= 0 ; i--)
	{
		int j					=	0;
		int iItem			= piParent[i][1];
		int *piOffset = piParent[i] + 2;
		int *piData		= piOffset + iItem + 1 + !(iItem % 2);

		//for all nodes
		for(j = 0 ; j < iItem ; j++)
		{
			int* piItem = piData + ((piOffset[j] - 1) * 2);

			if(piItem == piParent[i + 1])
			{
				int iOffset = 0;
				iOffset		= piOffset[j] + (int)((_piEnd - piItem + 1) / 2);
				piOffset[j + 1] = iOffset;
			}
			//else
			//{
			//	break;
			//	//if this item is not the last of the parent list
			//	//we don't need to continue to check the uppers levels
			//}
		}
	}

	FREE(piParent);
}

static void closeList(int _iVar, int *_piEnd)
{
	//Get Root address;
	int *piRoot				= istk(iadr(*Lstk(_iVar)));
	int iAddr					= *Lstk(_iVar);

	int iOffsetData		=	2 + piRoot[1] + 1 + !(piRoot[1] % 2);
	int iScale				= (int)(_piEnd - (piRoot + iOffsetData));
	int iDoubleSclale = (iScale + 1)/ 2;

	updateLstk(_iVar, sadr(iadr(iAddr) + iOffsetData), iDoubleSclale);
}

static int getParentList(int* _piStart, int* _piToFind, int* _piDepth, int** _piParent)
{
	if(isKindOfList(_piStart))
	{
		int iItem	= _piStart[1];
		int iIndex	= 0;
		*_piDepth += 1;
		for(iIndex = 0 ; iIndex < iItem ; iIndex++)
		{
			int *piChild = NULL;
			int iRet = 0;
			getListItemAddress(_piStart, iIndex + 1, &piChild);
			if(piChild == _piToFind)
			{
				if(_piParent != NULL)
				{
					_piParent[*_piDepth - 1] = piChild;
					*_piDepth -= 1;
				}
				return 1;
			}

			iRet = getParentList(piChild, _piToFind, _piDepth, _piParent);
			if(iRet != 0)
			{//find a child
				if(_piParent != NULL)
				{
					_piParent[*_piDepth - 1] = piChild;
					*_piDepth -= 1;
				}
				return 1;
			}

		}
		*_piDepth -= 1;
	}
	return 0;
}

static int isKindOfList(int* _piNode)
{
	if(_piNode[0] == sci_list || _piNode[0] == sci_tlist || _piNode[0] == sci_mlist)
		return 1;
	else
		return 0;
}
/*--------------------------------------------------------------------------*/
