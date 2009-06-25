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
*/

extern "C"
{
#include <hdf5.h>
#include <string.h>
#include "gw_fileio.h"
#include "stack-c.h"
#include "MALLOC.h"
#include "Scierror.h"
#include "localization.h"
#include "sciprint.h"
#include "api_variable.h"
#include "../../call_scilab/includes/CallScilab.h"
#include "h5_fileManagement.h"
#include "h5_readDataFromFile.h"
#include "intmacr2tree.h"
#include "stack-def.h"
}


//#define PRINT_DEBUG
int iTab = 0;


void print_tree(char* _pstMsg);

bool	import_data(int _iDatasetId, int _iItemPos, int* _piAddress, char* _pstVarname);
bool import_double(int _iDatasetId, int _iItemPos, int* _piAddress, char* _pstVarname);
bool import_string(int _iDatasetId, int _iItemPos, int* _piAddress, char* _pstVarname);
bool import_boolean(int _iDatasetId, int _iItemPos, int* _piAddress, char* _pstVarname);
bool import_poly(int _iDatasetId, int _iItemPos, int* _piAddress, char* _pstVarname);
bool import_list(int _iDatasetId, int _iVarType, int _iItemPos, int* _piAddress, char* _pstVarname);

int sci_import_from_hdf5(char *fname,unsigned long fname_len)
{
	CheckRhs(1,2);
	CheckLhs(1,1);
	int iRows						= 0;
	int iCols						= 0;
	int iLen						= 0;
	int* piAddr					= NULL;
	char *pstVarName		= NULL;

	/*debug only*/
	int* piAddr2				= NULL;
	if(Rhs > 1)
	{
		getVarAddressFromPosition(2, &piAddr2);
	}
	int* piAddrOut				= NULL;
	getVarAddressFromPosition(Rhs + 1, &piAddrOut);

	/* debug end */
	getVarAddressFromPosition(1, &piAddr);

	if(getVarType(piAddr) != sci_strings)
	{
		Scierror(999,_("%s: Wrong type for input argument #%d: A string.\n"),fname, 2);
		return 0;
	}

	getVarDimension(piAddr, &iRows, &iCols);
	if(iRows != 1 || iCols != 1)
	{
		Scierror(999,_("%s: Wrong size for input argument #%d: A string expected.\n"),fname,2);
	}

	getMatrixOfString(piAddr, &iRows, &iCols, &iLen, NULL);
	pstVarName = (char*)MALLOC((iLen + 1) * sizeof(char));
	getMatrixOfString(piAddr, &iRows, &iCols, &iLen, &pstVarName);

	//open hdf5 file
	int iFile = openHDF5File(pstVarName);

	int iNbItem = 0;
	iNbItem = getVariableNames(iFile, NULL);
	char** pstVarNameList = (char**)malloc(sizeof(char*) * iNbItem);
	iNbItem = getVariableNames(iFile, pstVarNameList);

	bool bImport = false;
	for(int i = 0 ; i < iNbItem ; i++)
	{
		int iDataSetId = getDataSetIdFromName(iFile, pstVarNameList[i]);
		if(iDataSetId == 0)
		{
			return 0;
		}

		bImport = import_data(iDataSetId, 0, NULL, pstVarNameList[i]);
		if(bImport == false)
		{
			break;
		}
	}
	//import all data

	//close the file
	closeHDF5File(iFile);

	FREE(pstVarName);

	int *piReturn = NULL;
	allocMatrixOfBoolean(Rhs + 1, 1, 1, &piReturn);
	if(bImport == true)
	{
		piReturn[0] = 1;
	}
	else
	{
		piReturn[0] = 0;
	}

	LhsVar(1) = Rhs + 1;
	PutLhsVar();

	return 0;
}

bool import_data(int _iDatasetId, int _iItemPos, int* _piAddress, char* _pstVarname)
{
	bool bRet = false;
	//get var type
	int iVarType = getScilabTypeFromDataSet(_iDatasetId);
	switch(iVarType)
	{
	case sci_matrix :
		{
			bRet = import_double(_iDatasetId, _iItemPos, _piAddress, _pstVarname);
			break;
		}
	case sci_strings :
		{
			bRet = import_string(_iDatasetId, _iItemPos, _piAddress, _pstVarname);
			break;
		}
	case sci_list :
	case sci_tlist :
	case sci_mlist :
		{
			bRet = import_list(_iDatasetId, iVarType, _iItemPos, _piAddress, _pstVarname);
			break;
		}
	case sci_boolean :
		{
			bRet = import_boolean(_iDatasetId, _iItemPos, _piAddress, _pstVarname);
			break;
		}
	case sci_poly :
		{
			bRet = import_poly(_iDatasetId, _iItemPos, _piAddress, _pstVarname);
			break;
		}
	default : 
		{
			char pstMsg[512];
			sprintf(pstMsg, "Unknow type : %d", iVarType);
			print_tree(pstMsg);
		}
	}
	return bRet;
}

bool import_double(int _iDatasetId, int _iItemPos, int* _piAddress, char* _pstVarname)
{
	int iRet						= 0;
	double *pdblReal		= NULL;
	double *pdblImg			= NULL;
	int	iRows						= 0;
	int iCols						= 0;
	int iComplex				= 0;

	iRet				= getDataSetDims(_iDatasetId, &iRows, &iCols);
	iComplex		= isComplexData(_iDatasetId);
	if(iRet)
	{
		return false;
	}

	if(iRows * iCols != 0)
	{
		if(iComplex)
		{
			pdblReal	= (double *) malloc(iRows * iCols * sizeof(double));
			pdblImg		= (double *) malloc(iRows * iCols * sizeof(double));
			iRet			= readDoubleComplexMatrix(_iDatasetId, iRows, iCols, pdblReal, pdblImg);
		}
		else
		{
			pdblReal	= (double *) malloc(iRows * iCols * sizeof(double));
			iRet			= readDoubleMatrix(_iDatasetId, iRows, iCols, pdblReal);
		}
		if(iRet)
		{
			return false;
		}
	}

	if(_piAddress == NULL)
	{
		if(iComplex)
		{
			iRet			= createNamedComplexMatrixOfDouble(_pstVarname, strlen(_pstVarname), iRows, iCols, pdblReal, pdblImg);
		}
		else
		{
			iRet			= createNamedMatrixOfDouble(_pstVarname, strlen(_pstVarname), iRows, iCols, pdblReal);
		}
	}
	else //if not null this variable is in a list
	{
		if(iComplex)
		{
			iRet			= createComplexMatrixOfDoubleInNamedList(_pstVarname, strlen(_pstVarname), _piAddress, _iItemPos, iRows, iCols, pdblReal, pdblImg);
		}
		else
		{
			iRet			= createMatrixOfDoubleInNamedList(_pstVarname, strlen(_pstVarname), _piAddress, _iItemPos, iRows, iCols, pdblReal);
		}
	}

	char pstMsg[512];
	sprintf(pstMsg, "double (%d x %d)", iRows, iCols);
	print_tree(pstMsg);

	if(pdblReal)
	{
		free(pdblReal);
	}

	if(pdblImg)
	{
		free(pdblImg);
	}

	if(iRet)
	{
		return false;
	}

	return true;
}

bool import_string(int _iDatasetId, int _iItemPos, int* _piAddress, char* _pstVarname)
{
	int iRet						= 0;
	int i								= 0;
	int	iRows						= 0;
	int iCols						= 0;
	char **pstData			= NULL;

	iRet = getDataSetDims(_iDatasetId, &iRows, &iCols);
	if(iRet)
	{
		return false;
	}

	pstData = (char **) malloc(iRows * iCols * sizeof(char*));
	iRet = readStringMatrix(_iDatasetId, iRows, iCols, pstData);
	if(iRet)
	{
		return false;
	}

	if(_piAddress == NULL)
	{
		iRet = createNamedMatrixOfString(_pstVarname, strlen(_pstVarname), iRows, iCols, pstData);
	}
	else //if not null this variable is in a list
	{
		iRet = createMatrixOfStringInNamedList(_pstVarname, strlen(_pstVarname), _piAddress, _iItemPos, iRows, iCols, pstData);
	}

	char pstMsg[512];
	sprintf(pstMsg, "string (%d x %d)", iRows, iCols);
	print_tree(pstMsg);

	for(i = 0 ; i < iRows * iCols ; i++)
	{
		free(pstData[i]);
	}
	free(pstData);

	if(iRet)
	{
		return false;
	}

	return true;
}

bool import_boolean(int _iDatasetId, int _iItemPos, int* _piAddress, char* _pstVarname)
{
	int iRet						= 0;
	int* piData					= NULL;
	int	iRows						= 0;
	int iCols						= 0;

	iRet				= getDataSetDims(_iDatasetId, &iRows, &iCols);
	if(iRet)
	{
		return false;
	}

	if(iRows * iCols != 0)
	{
		piData		= (int *) malloc(iRows * iCols * sizeof(int));
		iRet			= readBooleanMatrix(_iDatasetId, iRows, iCols, piData);
		if(iRet)
		{
			return false;
		}
	}

	if(_piAddress == NULL)
	{
		iRet			= createNamedMatrixOfBoolean(_pstVarname, strlen(_pstVarname), iRows, iCols, piData);
	}
	else //if not null this variable is in a list
	{
		iRet			= createMatrixOfBooleanInNamedList(_pstVarname, strlen(_pstVarname), _piAddress, _iItemPos, iRows, iCols, piData);
	}

	char pstMsg[512];
	sprintf(pstMsg, "boolean (%d x %d)", iRows, iCols);
	print_tree(pstMsg);

	if(piData)
	{
		free(piData);
	}

	if(iRet)
	{
		return false;
	}

	return true;
}

bool import_poly(int _iDatasetId, int _iItemPos, int* _piAddress, char* _pstVarname)
{
	int iRet						= 0;
	int i								= 0;
	int	iRows						= 0;
	int iCols						= 0;
	int iComplex				= 0;
	char pstVarName[64]	= {0};
	double **pdblReal		= NULL;
	double **pdblImg		= NULL;
	int *piNbCoef				= NULL;


	iRet				= getDataSetDims(_iDatasetId, &iRows, &iCols);
	if(iRet)
	{
		return false;
	}

	iComplex		= isComplexData(_iDatasetId);


	if(iComplex)
	{
		piNbCoef		= (int*)malloc(iRows * iCols * sizeof(int));
		pdblReal		= (double**)malloc(iRows * iCols * sizeof(double*));
		pdblImg			= (double**)malloc(iRows * iCols * sizeof(double*));
		iRet				= readPolyComplexMatrix(_iDatasetId, pstVarName, iRows, iCols, piNbCoef, pdblReal, pdblImg);
	}
	else
	{
		piNbCoef		= (int*)malloc(iRows * iCols * sizeof(int));
		pdblReal		= (double**)malloc(iRows * iCols * sizeof(double*));
		iRet				= readPolyMatrix(_iDatasetId, pstVarName, iRows, iCols, piNbCoef, pdblReal);
	}

	if(iRet)
	{
		return false;
	}

	if(_piAddress == NULL)
	{
		if(iComplex)
		{
			iRet			=	createNamedComplexMatrixOfPoly(_pstVarname, strlen(_pstVarname), pstVarName, iRows, iCols, piNbCoef, pdblReal, pdblImg);
		}
		else
		{
			iRet			=	createNamedMatrixOfPoly(_pstVarname, strlen(_pstVarname), pstVarName, iRows, iCols, piNbCoef, pdblReal);
		}
	}
	else //if not null this variable is in a list
	{
		if(iComplex)
		{
			iRet			= createMatrixOfPolyInNamedList(_pstVarname, strlen(_pstVarname), _piAddress, _iItemPos, pstVarName, iRows, iCols, piNbCoef, pdblReal);
		}
		else
		{
			iRet			= createComplexMatrixOfPolyInNamedList(_pstVarname, strlen(_pstVarname), _piAddress, _iItemPos, pstVarName, iRows, iCols, piNbCoef, pdblReal, pdblImg);
		}
	}

	char pstMsg[512];
	sprintf(pstMsg, "string (%d x %d)", iRows, iCols);
	print_tree(pstMsg);

	for(i = 0 ; i < iRows * iCols ; i++)
	{
		free(pdblReal[i]);
	}
	free(pdblReal);
	free(piNbCoef);

	if(iRet)
	{
		return false;
	}

	return true;
}

bool import_list(int _iDatasetId, int _iVarType, int _iItemPos, int* _piAddress, char* _pstVarname)
{
	int iRet								= 0;
	int i										= 0;
	int	iRows								= 0;
	int iCols								= 0;
	int* piListAddr					= NULL;
	hobj_ref_t* piItemRef		= NULL;

	iRet				= getDataSetDims(_iDatasetId, &iRows, &iCols);
	if(iRet)
	{
		return false;
	}


	if(iRows * iCols == 0)
	{//special case for empty list
		iRows = 0;
		iCols = 0;
	}
	else
	{
		iRet			= getListItemReferences(_iDatasetId, &piItemRef);
		if(iRet)
		{
			return false;
		}
	}

	char pstMsg[512];
	sprintf(pstMsg, "list (%d x %d)", iRows, iCols);
	print_tree(pstMsg);

	if(_piAddress == 0)
	{
		switch(_iVarType)
		{
		case sci_list :
			iRet		= createNamedList(_pstVarname, strlen(_pstVarname), iRows * iCols, &piListAddr);
			break;
		case sci_tlist :
			iRet		= createNamedTList(_pstVarname, strlen(_pstVarname), iRows * iCols, &piListAddr);
			break;
		case sci_mlist :
			iRet		= createNamedMList(_pstVarname, strlen(_pstVarname), iRows * iCols, &piListAddr);
			break;
		default :
			return false;
		}
	}
	else //if not null this variable is in a list
	{
		switch(_iVarType)
		{
		case sci_list :
			iRet		= createListInNamedList(_pstVarname, strlen(_pstVarname), _piAddress, _iItemPos, iRows * iCols, &piListAddr);
			break;
		case sci_tlist :
			iRet		= createTListInNamedList(_pstVarname, strlen(_pstVarname), _piAddress, _iItemPos, iRows * iCols, &piListAddr);
			break;
		case sci_mlist :
			iRet		= createMListInNamedList(_pstVarname, strlen(_pstVarname), _piAddress, _iItemPos, iRows * iCols, &piListAddr);
			break;
		default :
			return false;
		}
	}

	if(iRet)
	{
		return false;
	}

	iTab++;
	for(i = 0 ; i < iRows * iCols ; i++)
	{
		int iItemDataset = 0;
		iRet			= getListItemDataset(_iDatasetId, piItemRef, i, &iItemDataset);
		if(iRet || iItemDataset == 0)
		{
			return false;
		}

		bool bRet = import_data(iItemDataset, i + 1, piListAddr, _pstVarname);
		if(bRet == false)
		{
			return false;
		}
	}
	iTab--;

	iRet				= deleteListItemReferences(_iDatasetId, piItemRef);
	if(iRet)
	{
		return false;
	}

	return true;
}

void print_tree(char* _pstMsg)
{
#ifdef PRINT_DEBUG
	for(int i = 0 ; i < iTab ; i++)
	{
		printf("\t");
	}
	printf("%s\n", _pstMsg);
#endif
}
/*--------------------------------------------------------------------------*/
