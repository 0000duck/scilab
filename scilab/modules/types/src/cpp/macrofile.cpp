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

#include "macrofile.hxx"
#include "context.hxx"
#include "execvisitor.hxx"
#include "localization.h"
#include "yaspio.hxx"
#include "parser.hxx"
#include "configvariable.hxx"

using namespace ast;
namespace types
{

	/*--------------*/
	/*	Contructor  */
	/*--------------*/
	MacroFile::MacroFile(std::string _stName, string _stPath, string _stModule):
		Callable(),
		m_stName(_stName),
		m_stPath(_stPath),
		m_stModule(_stModule),
		m_pMacro(NULL)
	{
	}

	/*--------------*/
	/*	whoIAm		  */
	/*--------------*/
	void MacroFile::whoAmI()
	{
		std::cout << "types::MacroFile";
	}

	MacroFile* MacroFile::getAsMacroFile(void)
	{
		return this; 
	}

	InternalType::RealType MacroFile::getType(void)
	{ 
		return RealMacroFile; 
	}
	
	Callable::ReturnValue MacroFile::call(typed_list &in, int _iRetCount, typed_list &out)
	{
		ReturnValue RetVal = Callable::OK;

		//check excepted and input/output parameters numbers

		if(m_pMacro == NULL)
		{//load file, only for the first call
			Parser::getInstance()->parseFile(m_stPath, ConfigVariable::getInstance()->get("SCI"));
			//find FunctionDec
			FunctionDec* pFD = NULL;

			std::list<Exp *>::iterator j;
			std::list<Exp *>LExp = ((SeqExp*)Parser::getInstance()->getTree())->exps_get();

			for(j = LExp.begin() ; j != LExp.end() ; j++)
			{
				pFD = dynamic_cast<FunctionDec*>(*j);
				if(pFD) // &&	pFD->name_get().name_get() == m_stName
				{
					symbol::Context* pContext = symbol::Context::getInstance();
					if(pContext->get_fun(pFD->name_get())->isMacroFile())
					{
						MacroFile* pMacro = pContext->get_fun(pFD->name_get())->getAsMacroFile();
						if(pMacro->m_pMacro == NULL)
						{
							std::list<Var *>::const_iterator	i;

							//get input parameters list
							std::list<symbol::Symbol> *pVarList = new std::list<symbol::Symbol>();
							ArrayListVar *pListVar = (ArrayListVar *)&pFD->args_get();
							for(i = pListVar->vars_get().begin() ; i != pListVar->vars_get().end() ; i++)
							{
								string sz = ((SimpleVar*)(*i))->name_get().name_get();
								pVarList->push_back(((SimpleVar*)(*i))->name_get());
							}

							//get output parameters list
							std::list<symbol::Symbol> *pRetList = new std::list<symbol::Symbol>();
							ArrayListVar *pListRet = (ArrayListVar *)&pFD->returns_get();
							for(i = pListRet->vars_get().begin() ; i != pListRet->vars_get().end() ; i++)
							{
								pRetList->push_back(((SimpleVar*)(*i))->name_get());
							}

							//types::Macro macro(VarList, RetList, (SeqExp&)e.body_get());
							//types::Macro *pMacro = new types::Macro(m_stName, *pVarList, *pRetList, (SeqExp&)e.body_get());

							pMacro->m_pMacro = new Macro(m_stName, *pVarList, *pRetList, (SeqExp&)pFD->body_get(), m_stModule);
						}
					}
				}
			}
		}

		if(m_pMacro)
		{
			ReturnValue Val =  m_pMacro->call(in, _iRetCount, out);
			return Val;
		}
		else
		{
			return Callable::Error;
		}
	}
}
