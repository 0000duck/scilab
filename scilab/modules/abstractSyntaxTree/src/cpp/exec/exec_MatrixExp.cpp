/*
*  Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
*  Copyright (C) 2008-2008 - DIGITEO - Antoine ELIAS
*
*  This file must be used under the terms of the CeCILL.
*  This source file is licensed as described in the file COPYING, which
*  you should have received as part of this distribution.  The terms
*  are also available at
*  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
*
*/

#include "execvisitor.hxx"

using std::string;

InternalType* AddElementToVariable(InternalType* _poDest, InternalType* _poSource, int _iRows, int _iCols, int *_piRows, int *_piCols);


namespace ast
{
	/*
	[1,2;3,4] with/without special character $ and :
	*/
	void ExecVisitor::visit (const MatrixExp &e)
	{
		try
		{
//			int iRows = e.lines_get().size();
//			int iCols	= -1;
			int iRows = 0;
			int iCols	= -1;
			int iCurRow = -1;
			int iCurCol = 0;
			InternalType *poResult = NULL;

			std::list<MatrixLineExp *>::const_iterator	row;
			std::list<Exp *>::const_iterator	col;
			//store all element after evaluation

			list<list<InternalType*>> MatrixList;
			for (row = e.lines_get().begin() ; row != e.lines_get().end() ; ++row )
			{
				list<InternalType*> RowList;
				for (col = (*row)->columns_get().begin() ; col != (*row)->columns_get().end() ; ++col)
				{
					ExecVisitor* execMe = new ast::ExecVisitor();
					(*col)->accept (*execMe);
					if(execMe->result_get()->getType() == InternalType::RealImplicitList)
					{
						Double *pTemp = new Double(1, execMe->result_get()->getAsList()->size_get(), false);
						execMe->result_get()->getAsList()->extract_matrix(pTemp->real_get());
						delete execMe->result_get();
						execMe->result_set(pTemp);
					}

					iCurCol += ((GenericType*)execMe->result_get())->cols_get();
					if(iCurRow == -1)
					{
						iCurRow = ((GenericType*)execMe->result_get())->rows_get();
					}
					else if(iCurRow != ((GenericType*)execMe->result_get())->rows_get())
					{
						std::ostringstream os;
						os << "inconsistent row/column dimensions";
						os << " (" << (*row)->location_get().first_line << "," << (*row)->location_get().first_column << ")" << std::endl;
						string szErr(os.str());
						throw szErr;
					}

					RowList.push_back(execMe->result_get());
					delete execMe;
				}

				if(iCols == -1)
				{
					iCols = iCurCol;
				}
				else if(iCols != iCurCol)
				{
					std::ostringstream os;
					os << "inconsistent row/column dimensions";
					os << " (" << (*row)->location_get().first_line << "," << (*row)->location_get().first_column << ")" << std::endl;
					string szErr(os.str());
					throw szErr;
				}

				iRows += iCurRow;
				iCurCol = 0;
				iCurRow = -1;
				MatrixList.push_back(RowList);
			}

			list<list<InternalType*>>::const_iterator it_ML;
			list<InternalType*>::const_iterator it_RL;

			int iAddRow = 0;
			iCurRow			= 0;
			iCurCol			= 0;
			for(it_ML = MatrixList.begin() ; it_ML != MatrixList.end() ; it_ML++)
			{
				int iAddCol = 0;
				for(it_RL = (*it_ML).begin() ; it_RL != (*it_ML).end() ; it_RL++)
				{
					if(poResult == NULL)
					{
						poResult = AddElementToVariable(poResult, *it_RL, iRows, iCols, &iAddRow, &iAddCol);
						iCurCol += iAddCol;
					}
					else
					{
						poResult = AddElementToVariable(poResult, *it_RL, iCurRow, iCurCol, &iAddRow, &iAddCol);
						iCurCol += iAddCol;
					}
				}
				iCurRow += iAddRow;
				iCurCol = 0;
			}
			result_set(poResult);
			if(e.is_verbose())
			{
				std::cout << poResult->toString(10,75) << std::endl;
			}
/*
			for (row = e.lines_get().begin() ; row != e.lines_get().end() ; ++row )
			{
				std::list<Exp *>::const_iterator	col;

				//check if Cols size is always the same
				if(iCols != -1 && iCols != (*row)->columns_get().size())
				{
					std::ostringstream os;
					os << "inconsistent row/column dimensions";
					os << " (" << (*row)->location_get().first_line << "," << (*row)->location_get().first_column << ")" << std::endl;
					string szErr(os.str());
					throw szErr;
				}
				//store Cols size
				iCols = (*row)->columns_get().size();

				for (col = (*row)->columns_get().begin() ; col != (*row)->columns_get().end() ; ++col)
				{
					ExecVisitor* execMe = new ast::ExecVisitor();
					(*col)->accept (*execMe);

					if(poResult == NULL)
					{
						poResult = AddElementToVariable(poResult, execMe->result_get(), iRows, iCols);
					}
					else
					{
						poResult = AddElementToVariable(poResult, execMe->result_get(), iCurRow, iCurCol);
					}
					iCurCol++;
					delete execMe;
				}
				iCurCol = 0;
				iCurRow++;
			}
			result_set(poResult);
			if(e.is_verbose())
			{
				std::cout << poResult->toString(10,75);
			}
*/
		}
		catch(string sz)
		{
			throw sz;
		}
	}
}


/*
_iRows : Position if _poDest allready initialized else size of the matrix
_iCols : Position if _poDest allready initialized else size of the matrix
*/
InternalType* AddElementToVariable(InternalType* _poDest, InternalType* _poSource, int _iRows, int _iCols, int *_piRows, int *_piCols)
{
	InternalType *poResult	= NULL;
	InternalType::RealType TypeSource	= ((GenericType*)_poSource)->getType();
	InternalType::RealType TypeDest		=	InternalType::RealInternal;
	int iCurRow = _iRows;
	int iCurCol = _iCols;

	if(_poDest == NULL)
	{
		switch(TypeSource)
		{
		case GenericType::RealDouble :
			poResult = new Double(_iRows, _iCols, false);
			break;
		case GenericType::RealBool :
			poResult = new Bool(_iRows, _iCols);
			break;
		case GenericType::RealUInt :
			poResult = new UInt(_iRows, _iCols);
			break;
		case GenericType::RealInt :
			poResult = new Int(_iRows, _iCols);
			break;
		case GenericType::RealString :
			poResult = new String(_iRows, _iCols);
			break;
		case GenericType::RealPoly :
			{
				int* piRank = new int[_iRows * _iCols];
				for(int i = 0 ; i < _iRows * _iCols ; i++)
				{
					piRank[i] = 1;
				}
				poResult = new MatrixPoly(_poSource->getAsPoly()->var_get(), _iRows, _iCols, piRank);
				break;
			}
		case InternalType::RealImplicitList :
			poResult = new ImplicitList();
			break;
		}
		iCurCol		= 0;
		iCurRow		= 0;
		TypeDest	=	TypeSource;
	}
	else
	{
		TypeDest		= ((GenericType*)_poDest)->getType();
		poResult = _poDest;
	}


	if(TypeDest != TypeSource)
	{//check if source type is compatible with the old one
		switch(TypeDest)
		{
		case GenericType::RealDouble :
			if(TypeSource == GenericType::RealPoly)
			{
				Double *poDest = (Double*)_poDest;
				//Convert Dest to RealPoly
				int *piRank = new int[poDest->size_get()];
				for(int i = 0 ; i < poDest->size_get() ; i++)
				{
					piRank[i] = 1;
				}

				poResult = new MatrixPoly(((MatrixPoly*)_poSource)->var_get(), poDest->rows_get(), poDest->cols_get(),  piRank);

				double *pR = poDest->real_get();
				double *pI = poDest->img_get();
				for(int i = 0 ; i < poDest->size_get() ; i++)
				{
					Double *pdbl = NULL;
					if(poDest->isComplex())
					{
						pdbl = new Double(pR[i], pI[i]);
					}
					else
					{
						pdbl = new Double(pR[i]);
					}

					((MatrixPoly*)poResult)->poly_set(i, pdbl);
					delete pdbl;
				}

				((MatrixPoly*)poResult)->poly_set(iCurRow, iCurCol, ((MatrixPoly*)_poSource)->poly_get(0)->coef_get());
			}
			break;
		case GenericType::RealPoly :
			if(TypeSource == GenericType::RealDouble)
			{
				//Add Source like coef of the new element
				Poly* pPolyOut	= poResult->getAsPoly()->poly_get(iCurRow, iCurCol);

				pPolyOut->rank_set(1);
				pPolyOut->coef_set((Double*)_poSource);
			}
			break;
		default:
			break;
		}
		return poResult;
	}
	else
	{//Just add the new value in the current item
		switch(TypeDest)
		{
		case GenericType::RealDouble :
			if(poResult->getAsDouble()->isComplex() == false && _poSource->getAsDouble()->isComplex() == true)
			{
				poResult->getAsDouble()->complex_set(true);
			}

			if(_poSource->getAsDouble()->size_get() != 1)
			{
				poResult->getAsDouble()->insert(iCurRow, iCurCol, _poSource->getAsDouble());
				*_piRows = _poSource->getAsDouble()->rows_get();
				*_piCols = _poSource->getAsDouble()->cols_get();
			}
			else
			{
				poResult->getAsDouble()->val_set(iCurRow, iCurCol, _poSource->getAsDouble()->real_get(0,0), _poSource->getAsDouble()->img_get(0,0));
				*_piRows = 1;
				*_piCols = 1;
			}
			break;
		case GenericType::RealPoly :
			{
/*
				Double *pDbl = _poSource->getAsPoly()->poly_get(0)->coef_get();
				pDbl->toString(10,75;
				_poDest->getAsPoly()->poly_set(iCurRow, iCurCol, _poSource->getAsPoly()->poly_get(0)->coef_get());
*/

				Poly* pPolyIn		= _poSource->getAsPoly()->poly_get(0);
				if(_poSource->getAsPoly()->isComplex())
				{
					poResult->getAsPoly()->complex_set(true);
				}

				Poly* pPolyOut	= poResult->getAsPoly()->poly_get(iCurRow, iCurCol);

				pPolyOut->rank_set(pPolyIn->rank_get());
				pPolyOut->coef_set(pPolyIn->coef_get());
				*_piRows = 1;
				*_piCols = 1;

				break;
			}
		case GenericType::RealBool:
			poResult->getAsBool()->bool_set(iCurRow, iCurCol, _poSource->getAsBool()->bool_get(0,0));
			break;
		case GenericType::RealUInt:
			//((Double*)poResult)->val_set(iCurRow, iCurCol, ((Double*)_poSource)->real_get(0,0), ((Double*)_poSource)->img_get(0,0));
			break;
		case GenericType::RealInt :
			//((Double*)poResult)->val_set(iCurRow, iCurCol, ((Double*)_poSource)->real_get(0,0), ((Double*)_poSource)->img_get(0,0));
			break;
		case GenericType::RealString :
			poResult->getAsString()->string_set(iCurRow, iCurCol, _poSource->getAsString()->string_get(0,0));
			break;
		case GenericType::RealImplicitList :
			{
				if(_poSource->getAsList()->start_type_get() == InternalType::RealPoly)
				{
					poResult->getAsList()->start_set(_poSource->getAsList()->start_poly_get());
				}
				else
				{
					poResult->getAsList()->start_set(_poSource->getAsList()->start_get());
				}

				if(_poSource->getAsList()->step_type_get() == InternalType::RealPoly)
				{
					poResult->getAsList()->step_set(_poSource->getAsList()->step_poly_get());
				}
				else
				{
					poResult->getAsList()->step_set(_poSource->getAsList()->step_get());
				}

				if(_poSource->getAsList()->end_type_get() == InternalType::RealPoly)
				{
					poResult->getAsList()->end_set(_poSource->getAsList()->end_poly_get());
				}
				else
				{
					poResult->getAsList()->end_set(_poSource->getAsList()->end_get());
				}
				break;
			}
		default:
			break;
		}
		return poResult;
	}
	return NULL;
}

