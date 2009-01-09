/*
*  Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
*  Copyright (C) 2007-2008 - INRIA - Bruno JOFRET
*  Copyright (C) 2008-2008 - DIGITEO - Antoine ELIAS
*
*  This file must be used under the terms of the CeCILL.
*  This source file is licensed as described in the file COPYING, which
*  you should have received as part of this distribution.  The terms
*  are also available at
*  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
*
*/

#ifndef SYMBOL_SCOPE_HH
# define SYMBOL_SCOPE_HH

#include <iostream>
#include <map>
#include "symbol.hxx"
#include "alltypes.hxx"
#include "export_symbol.h"

extern "C"
{
	#include "elem_common.h"
}

using namespace types;

namespace symbol
{

	//template< class Entry_T, class Key_T = Symbol >
	class EXTERN_SYMBOL Scope
	{
	public:
		/** Constructor & Destructor */
		/** \brief Construct a Scope */
		explicit Scope()
		{
			_scope = new std::map<Symbol, InternalType*>();
			_name = "";
		}
		/** \brief Construct a named Scope i.e Namespace */
		explicit Scope(std::string name)
		{
			_scope = new std::map<Symbol, InternalType*>();
			_name = name;
		}

		~Scope()
		{
			delete _scope;
		}

		bool isUsed(InternalType* pIT) const
		{
			std::map<Symbol, InternalType*>::const_iterator it_scope;
			for(it_scope = _scope->begin() ; it_scope != _scope->end() ; ++it_scope)
			{
				if((*it_scope).second == pIT)
					return true;
			}
			return false;
		}

		/** Associate value to key in the current scope. */
		InternalType*	put (Symbol key, InternalType &value)
		{
			InternalType *pOld = (*_scope)[key];
			if(pOld != NULL)
			{
				pOld->DecreaseRef();
				if(pOld->isRef() == false)
				{
					delete pOld;
				}
			}
/*
			if(value.isRef())
			{
				std::cout << "Need copy : " << key.name_get() << std::endl;
			}
*/
			(*_scope)[key] = &value;
			value.IncreaseRef();
			return NULL;
		}

		/** If key was associated to some Entry_T in the open scopes, return the
		** most recent insertion. Otherwise return the empty pointer. */
		InternalType*	get (Symbol key) const
		{
			std::map<Symbol, InternalType*>::const_iterator it_scope;

			it_scope = (*_scope).find(key);
			if (it_scope == (*_scope).end())
				return 0;
			return (*it_scope).second;
		}

		/** Return name of current scope, use for namespace. */
		std::string get_name() const
		{
			return _name;
		}

		/** Send the content of this table on ostr in a readable manner, the top
		** of the stack being displayed last. */
		void	print (std::ostream& ostr) const
		{
			std::map<Symbol, InternalType*>::const_iterator it_scope;

			for(it_scope = _scope->begin() ; it_scope != _scope->end() ; ++it_scope)
			{
				if (_name != "")
				{
					ostr << _name << "::";
				}
				ostr << (*it_scope).first << " : ";
				(*it_scope).second->whoAmI();
				if((*it_scope).second->isDouble())
				{
					Double *pdbl = (*it_scope).second->getAsDouble();
					ostr << pdbl->DimToString() << std::endl;
					ostr << pdbl->toString(10, 75);
					ostr << std::endl;
				}
				else if((*it_scope).second->isInt())
				{
					Int *pi = (*it_scope).second->getAsInt();
					ostr << "( " << pi->rows_get() << ", " << pi->cols_get() << " )" << std::endl;
					int iCols = pi->cols_get();
					int iRows = pi->rows_get();
					if(iRows == 1 && iCols == 1)
					{
						ostr << pi->real_get(0,0);
						if(pi->isComplex())
						{
							ostr << (pi->img_get(0,0) < 0 ? " " : " +") << pi->img_get(0,0) << "i";
						}

						ostr << std::endl;
					}
					else
					{
						ostr << "[ ";
						for(int r = 0 ; r < iRows ; r++)
						{
							for(int c = 0 ; c < iCols ; c++)
							{
								ostr << pi->real_get(r, c);
								if(pi->isComplex())
								{
									ostr << (pi->img_get(r, c) < 0 ? " " : " +") << pi->img_get(r, c) << "i";
								}

								if((c + 1) != iCols || (r + 1) != iRows)
								{
									ostr << " , ";
								}
							}
							ostr  << std::endl;
						}
						ostr << " ]" << std::endl;
					}
				}
				else if((*it_scope).second->isString())
				{
					String *psz = (*it_scope).second->getAsString();
					ostr << psz->DimToString() << std::endl;
					ostr << psz->toString(10, 75);
					ostr << std::endl;
				}
				else if((*it_scope).second->isBool())
				{
					Bool *pb = (*it_scope).second->getAsBool();
					ostr << "( " << pb->rows_get() << ", " << pb->cols_get() << " )" << std::endl;

					//string szOut = pb->toString(100);
					//ostr << szOut;

					for(int i = 0 ; i < pb->rows_get() ; i++)
					{
						for(int j = 0 ; j < pb->cols_get() ; j++)
						{
							ostr << pb->bool_get(i,j) == false ? "F " : "T ";
						}
						ostr << std::endl;
					}
				}
				else if((*it_scope).second->isFunction())
				{
					Function *pF = (*it_scope).second->getAsFunction();
					ostr << std::endl;
					ostr << "Module : " << pF->m_szModule << " Function : " << pF->m_szName << std::endl;
				}
				else if((*it_scope).second->isPoly())
				{
/*					MatrixPoly *pPoly = (*it_scope).second->getAsPoly();
					ostr << pPoly->DimToString() << std::endl;
					ostr << pPoly->toString(10, 75);
					ostr << std::endl;
*/
					MatrixPoly *pMP = (*it_scope).second->getAsPoly();
					ostr << "( " << pMP->rows_get() << ", " << pMP->cols_get() << " )" << std::endl;
					for(int i = 0 ; i < pMP->rows_get(); i++)
					{
						for(int j = 0 ; j < pMP->cols_get(); j++)
						{
							ostr << "| ";
							Poly *poPoly	= pMP->poly_get(i,j);
							Double *pdbl	= poPoly->coef_get();
							double *pR		= pdbl->real_get();
							double *pI		= pdbl->img_get();

							for(int k = poPoly->rank_get() - 1 ; k >= 0 ; k--)
							{
								if(k != poPoly->rank_get() - 1)
								{
									ostr << " + ";
								}

								ostr << "(";
								if(pR[k] != 0 || pI == NULL || pI[k] == 0)
								{
									if(isZero(pR[k]) == false)
									{
										ostr << pR[k];
									}
									else
									{
										ostr << 0;
									}
								}

 								if((pI != NULL && pI[k] != 0))
								{
									if(pR[k] != 0 && pI[k] > 0)
									{
										ostr << "+";
									}

									if(pI[k] == 1)
									{
										ostr << "i";
									}
									else if(pI[k] == -1)
									{
										ostr << "-i";
									}
									else
									{
										ostr << pI[k] << "i";
									}
								}
								ostr << ")";

								if(k != 0)
								{
									ostr << " * " << pMP->var_get();
									if(k != 1)
									{
										ostr << "^" << k;
									}
								}
							}
							ostr << " |";
						}
						ostr << std::endl;
					}
					ostr << std::endl << std::endl;
				}
			}
		}

	private:
		std::map<Symbol, InternalType*>* 	_scope;
		std::string				_name;
	};

	inline std::ostream& operator<< (std::ostream& ostr,
		const Scope &scope)
	{
		scope.print(ostr);
		return ostr;
	}
}


#endif /* ! SYMBOL_SCOPE_HH */

