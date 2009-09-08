/*
*  Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
*  Copyright (C) 2009-2009 - DIGITEO - Bruno JOFRET
* 
*  This file must be used under the terms of the CeCILL.
*  This source file is licensed as described in the file COPYING, which
*  you should have received as part of this distribution.  The terms
*  are also available at
*  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
* 
*/

#include "macro.hxx"
#include "context.hxx"
#include "execvisitor.hxx"
#include "localization.h"
#include "yaspio.hxx"

namespace types
{

	/*--------------*/
	/*	Contructor  */
	/*--------------*/
	Macro::Macro(std::string _stName, std::list<symbol::Symbol> &_inputArgs, std::list<symbol::Symbol> &_outputArgs, ast::SeqExp &_body, string _stModule):
		Callable(),
		m_stName(_stName),
		m_inputArgs(&_inputArgs),
		m_outputArgs(&_outputArgs),
		m_stModule(_stModule),
		m_body(&_body)
	{
	}

	Macro::~Macro()
	{
		delete m_body;
	}
	/*--------------*/
	/*	whoIAm		  */
	/*--------------*/
	void Macro::whoAmI()
	{
		std::cout << "types::Macro";
	}

	Macro* Macro::getAsMacro(void)
	{
		return this; 
	}

	InternalType::RealType Macro::getType(void)
	{ 
		return RealMacro; 
	}
	
	Callable::ReturnValue Macro::call(typed_list &in, int _iRetCount, typed_list &out)
	{
		ReturnValue RetVal = Callable::OK;
		//check excepted and input/output parameters numbers
		if(in.size() != m_inputArgs->size())
		{
			return Callable::Error;
		}

		std::list<symbol::Symbol>::const_iterator i;
		typed_list::const_iterator j;
		ast::ExecVisitor execFunc;

		//open a new scope
		symbol::Context *pContext = symbol::Context::getInstance();
		pContext->scope_begin();

		//assign value to variable in the new context
		for (i = m_inputArgs->begin(), j = in.begin(); j != in.end (); ++j,++i)
		{
			pContext->put(*i, **j);
		}

		try
		{
			m_body->accept(execFunc);

			for (i = m_outputArgs->begin(); i != m_outputArgs->end() && _iRetCount; ++i, --_iRetCount)
			{
				InternalType *pIT = pContext->get(*i);
				if(pIT != NULL)
				{
					out.push_back(pIT);
					//pIT->IncreaseRef();
				}
				else
				{
					char sz[bsiz];
#ifdef _MSC_VER
					sprintf_s(sz, bsiz, _("Undefined variable %s.\n"), (*i).name_get().c_str());
#else
					sprintf(sz, _("Undefined variable %s.\n"), (*i).name_get().c_str());
#endif
					YaspWrite(sz);
				}
			}
		}
		catch(string sz)
		{
		  YaspWrite((char *) sz.c_str());
		  YaspWrite("\n");
			RetVal = Callable::Error;
		}
		
		//close the current scope
		pContext->scope_end();

		return RetVal;
	}
}
