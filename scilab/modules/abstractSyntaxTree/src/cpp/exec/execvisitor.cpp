/*
*  Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
*  Copyright (C) 2008-2008 - DIGITEO - Bruno JOFRET
*
*  This file must be used under the terms of the CeCILL.
*  This source file is licensed as described in the file COPYING, which
*  you should have received as part of this distribution.  The terms
*  are also available at
*  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
*
*/

#include "execvisitor.hxx"
#include "timer.hxx"
#include "localization.h"
#include "macro.hxx"

#include "class.hxx"
#include "ooutils.hxx"

#include "yaspio.hxx"

using std::string;

bool bConditionState(ast::ExecVisitor *exec);

void vTransposeRealMatrix(
			double *_pdblRealIn,
			int _iRowsIn,			int _iColsIn,
			double *_pdblRealOut);

void vTransposeComplexMatrix(
			double *_pdblRealIn,	double *_pdblImgIn,
			int _iRowsIn,			int _iColsIn,
			double *_pdblRealOut,	double *_pdblImgOut, bool _bConjugate);

namespace ast
{
	static int level = -1;

	static void DEBUG_START_NODE(void)
	{
		++level;
	}

	static void DEBUG_END_NODE(void)
	{
		--level;
	}

	static void DEBUG(string str)
	{
		for(int i = 0 ; i < level; ++i)
		{
			std::cerr << "  ";
		}
		if (level > 0)
		{
			std::cerr << "|_./ ";
		}
		std::cerr << str << std::endl;
	}

	void ExecVisitor::visit (const MatrixLineExp &e)
	{
	/*
		All processes are done in MatrixExp
	*/
	}

	void ExecVisitor::visit (const CellExp &e)
	{
		/*
			FIXME : container type
		*/
	}

	/** \name Visit Constant Expressions nodes.
	** \{ */
	void ExecVisitor::visit (const StringExp &e)
	{
		String *psz = new String(e.value_get().c_str());
		result_set(psz);
	}

	void ExecVisitor::visit (const CommentExp &e)
	{
		/*
		Nothing to do
		*/
	}

	void ExecVisitor::visit (const IntExp  &e)
	{
		/*
		Int does not exist, Int8 - 16 - 32 - 64 functions
		*/
	}

	void ExecVisitor::visit (const FloatExp  &e)
	{
		/*
		Float does not exist, float function
		*/
	}

	void ExecVisitor::visit (const DoubleExp  &e)
	{
		Double *pdbl = new Double(e.value_get());
		result_set(pdbl);
	}

	void ExecVisitor::visit (const BoolExp  &e)
	{
		Bool *pb = new Bool(e.value_get());
		result_set(pb);
	}

	void ExecVisitor::visit (const NilExp &e)
	{
		/*
		FIXME :
		*/
	}

	void ExecVisitor::visit (const SimpleVar &e)
	{
		InternalType *pI = symbol::Context::getInstance()->get(e.name_get());
		if(pI != NULL)
		{
			result_set(pI);
			if(pI != NULL && pI->getAsCallable() == false && e.is_verbose())
			{
			  std::ostringstream ostr;
			  ostr << e.name_get() << " = " << std::endl;
			  ostr << std::endl;
			  ostr << pI->toString(10,75) << std::endl;
			  YaspWrite((char *) ostr.str().c_str());
			}
		}
		else
		{
			char szError[bsiz];
#ifdef _MSC_VER
			sprintf_s(szError, bsiz, _("Undefined variable: %s\n"), e.name_get().name_get().c_str());
#else
			sprintf(szError, _("Undefined variable: %s\n"), e.name_get().name_get().c_str());
#endif
			throw string(szError);
			//Err, SimpleVar doesn't exist in Scilab scopes.
		}
	}

	void ExecVisitor::visit (const ColonVar &e)
	{
		int pRank[1] = {2};
		Double dblCoef(1,2);
		dblCoef.val_set(0, 0, 0);
		dblCoef.val_set(0, 1, 1);

		MatrixPoly *pVar	= new MatrixPoly("$", 1, 1, pRank);
		Poly *poPoly			= pVar->poly_get(0,0);
		poPoly->coef_set(&dblCoef);

		ImplicitList *pIL = new ImplicitList();
		pIL->start_set(1);
		pIL->step_set(1);
		pIL->end_set(pVar);
		result_set(pIL);
		/*
		: = 1:$
		*/
	}

	void ExecVisitor::visit (const DollarVar &e)
	{
		int pRank[1] = {2};
		Double dblCoef(1,2);
		dblCoef.val_set(0, 0, 0);
		dblCoef.val_set(0, 1, 1);

		MatrixPoly *pVar	= new MatrixPoly("$", 1, 1, pRank);
		Poly *poPoly			= pVar->poly_get(0,0);
		poPoly->coef_set(&dblCoef);
		result_set(pVar);
	}

	void ExecVisitor::visit (const ArrayListVar &e)
	{
		/*

		*/
	}

	void ExecVisitor::visit (const FieldExp &e)
	{
		/*
		a.b
		*/
		ExecVisitor *execL = new ast::ExecVisitor();
		e.head_get()->accept(*execL);
		types::InternalType *head = execL->result_get();
		const symbol::Symbol &tail = dynamic_cast<const SimpleVar*>(e.tail_get())->name_get();
		
		types::ObjectMatrix *obj = dynamic_cast<types::ObjectMatrix*>(head);
		if(obj != NULL)
		{
			types::InternalType *res = obj->get(tail.name_get());
			if(res != NULL)
			{
				result_set(res);
				if(e.is_verbose())
				{
					std::ostringstream ostr;
					ostr << obj->toString(10,75) << "." << tail.name_get() << " = " << std::endl;
					ostr << std::endl;
					ostr << res->toString(75,10) << std::endl;
					YaspWrite((char *) ostr.str().c_str());
				}
			}
		}
		
		delete execL;
	}

	void ExecVisitor::visit(const CallExp &e)
	{
		ExecVisitor *execFunc = new ast::ExecVisitor();
		std::list<Exp *>::const_iterator	i;

		e.name_get().accept(*execFunc);
		if(execFunc->result_get() != NULL && execFunc->result_get()->isCallable())
		{//function call
			Callable *pCall = execFunc->result_get()->getAsCallable();
			types::typed_list out;
			types::typed_list in;
			
			ExecVisitor **execVar	= new ast::ExecVisitor*[e.args_get().size()]();
			int j = 0;
			for (j = 0, i = e.args_get().begin (); i != e.args_get().end (); ++i,j++)
			{
				execVar[j] = new ast::ExecVisitor();
				(*i)->accept (*execVar[j]);
				in.push_back(execVar[j]->result_get());
			}
			
			Function::ReturnValue Ret = pCall->call(in, (int)expected_size_get(), out);
			
			if(Ret == Callable::OK)
			{
				if(expected_size_get() == 1 && out.size() == 0) //to manage ans
				{
					if((int)out.size() < expected_size_get())
					{
						std::ostringstream os;
						os << "bad lhs, expected : " << expected_size_get() << " returned : " << out.size() << std::endl;
						throw os.str();
					}
				}

				for(int i = 0 ; i < out.size() ; i++)
				{
					result_set(i, out[i]);
					out[i]->DecreaseRef();
				}
			}
			else if(Ret == Callable::Error)
			{
				std::ostringstream os;
				char szError[bsiz];
#ifdef _MSC_VER
				sprintf_s(szError, bsiz, _("Function call failed\n"));
#else
				sprintf(szError, _("Function call failed\n"));
#endif
				throw string(szError);
			}

			
			for (j = 0; j < e.args_get().size(); j++)
			{
				delete execVar[j];
			}
			delete[] execVar;
		}
		else if(execFunc->result_get() != NULL)
		{//a(xxx) with a variable, extraction

				InternalType *pResult = NULL;
				ExecVisitor* execMeArg = new ast::ExecVisitor();
				//Var = dynamic_cast<const SimpleVar*>(&CallVar->name_get());
				InternalType *pIT = execFunc->result_get();
				int iArgDim				= (int)e.args_get().size();
				bool bSeeAsVector	= iArgDim == 1;

				//Create list of indexes
				//std::vector<std::vector<int>> IndexList;

				int *piIndexSeq		= NULL;
				int *piMaxDim			= NULL;
				int *piDimSize		= new int[iArgDim];
				int iTotalCombi		= GetIndexList(e.args_get(), &piIndexSeq, &piMaxDim, pIT, piDimSize);

				if(pIT->getType() == InternalType::RealDouble)
				{
					Double *pDouble	= pIT->getAsDouble();
					Double *dResult;
					if(	iArgDim == 1 && piMaxDim[0] > pDouble->size_get() || //SeeAsVector
							iArgDim == 2 && (piMaxDim[0] > pDouble->rows_get() || piMaxDim[0] > pDouble->cols_get()) || //check dimension to extract
							iArgDim > 2) //more than 2 dimensions ?
					{
						std::ostringstream os;
						os << "inconsistent row/column dimensions";
						os << " (" << (*e.args_get().begin())->location_get().first_line << "," << (*e.args_get().begin())->location_get().first_column << ")" << std::endl;
						throw os.str();
					}


					int iRowOut = 0;
					int iColOut	= 0;
					if(iArgDim == 1)
					{
						if(pDouble->rows_get() == 1)
						{
							pResult = new Double(1, piDimSize[0], pDouble->isComplex());
							iRowOut = 1;
							iColOut = piDimSize[0];
						}
						else
						{
							pResult = new Double(piDimSize[0], 1, pDouble->isComplex());
							iRowOut = piDimSize[0];
							iColOut = 1;
						}
					}
					else
					{
						pResult = dResult = new Double(piDimSize[0], piDimSize[1], pDouble->isComplex());
						iRowOut = piDimSize[0];
						iColOut = piDimSize[1];
					}

					double *pRealIn		= pDouble->real_get();
					double *pImgIn		= pDouble->img_get();
					double *pRealOut	= dResult->real_get();
					double *pImgOut		= dResult->img_get();

					if(bSeeAsVector)
					{
						if(dResult->isComplex())
						{
							for(int i = 0 ; i < iTotalCombi ; i++)
							{
								pRealOut[i] = pRealIn[piIndexSeq[i] - 1];
								pImgOut[i]	= pImgIn[piIndexSeq[i] - 1];
							}
						}
						else
						{
							for(int i = 0 ; i < iTotalCombi ; i++)
							{
								pRealOut[i] = pRealIn[piIndexSeq[i] - 1];
							}
						}
					}
					else//matrix
					{
						int iRowIn = pDouble->rows_get();
						if(dResult->isComplex())
						{
							for(int i = 0 ; i < iTotalCombi ; i++)
							{
								int iCurIndex	= (i % iColOut) * iRowOut + (i / iColOut);
								pRealOut[iCurIndex] = pRealIn[(piIndexSeq[i * 2] - 1) + (piIndexSeq[i * 2 + 1] - 1) * iRowIn];
								pImgOut[iCurIndex] = pImgIn[(piIndexSeq[i * 2] - 1) + (piIndexSeq[i * 2 + 1] - 1) * iRowIn];
							}
						}
						else
						{
							for(int i = 0 ; i < iTotalCombi ; i++)
							{
								//convert vertical indexes to horizontal indexes
								int iCurIndex	= (i % iColOut) * iRowOut + (i / iColOut);
								pRealOut[iCurIndex] = pRealIn[(piIndexSeq[i * 2] - 1) + (piIndexSeq[i * 2 + 1] - 1) * iRowIn];
							}
						}
					}
				}
				else if(pIT->getType() == InternalType::RealObject)
				{
					ObjectMatrix *pObj = pIT->getAsObject();
					ObjectMatrix *oResult;
					if(iArgDim == 1 && piMaxDim[0] > pObj->size_get() || //SeeAsVector
							iArgDim == 2 && (piMaxDim[0] > pObj->rows_get() || piMaxDim[0] > pObj->cols_get()) || //check dimension to extract
							iArgDim > 2) //more than 2 dimensions ?
					{
						std::ostringstream os;
						os << "inconsistent row/column dimensions";
						os << " (" << (*e.args_get().begin())->location_get().first_line << "," << (*e.args_get().begin())->location_get().first_column << ")" << std::endl;
						string szErr(os.str());
						throw szErr;
					}


					int iRowOut = 0;
					int iColOut	= 0;
					if(iArgDim == 1)
					{
						pResult = oResult = new ObjectMatrix(piDimSize[0], 1);
						iRowOut = piDimSize[0];
						iColOut = 1;
					}
					else
					{
						// TODO
					}

					if(bSeeAsVector)
					{
						for(int i = 0 ; i < iTotalCombi ; i++)
						{
							oResult->elem_set(i, pObj->elem_get(piIndexSeq[i] - 1));
						}
					}
					else//matrix
					{
						// TODO
					}
				}
				delete[] piDimSize;
				result_set(pResult);
				if(e.is_verbose())
				{
				  std::ostringstream ostr;
				  ostr <<  pResult->toString(10,75) << std::endl;
				  YaspWrite((char *) ostr.str().c_str());
				}
		}
		else
		{//result == NULL ,variable doesn't exist :(
			std::ostringstream os;
			os << "variable must exist";
			os << " (" << e.location_get().first_line << "," << e.location_get().first_column << ")" << std::endl;
			throw os.str();
		}
		delete execFunc;
	}

	void ExecVisitor::visit (const IfExp  &e)
	{
		//Create local exec visitor
		ExecVisitor *execMeTest		= new ast::ExecVisitor();
		ExecVisitor *execMeAction = new ast::ExecVisitor();
		bool bTestStatus					= false;

		//condition
		e.test_get().accept(*execMeTest);

		bTestStatus = bConditionState(execMeTest);
		if(bTestStatus == true)
		{//condition == true
			if(e.is_breakable())
			{
				((Exp*)&e.then_get())->breakable_set();
			}
			e.then_get().accept(*execMeAction);
		}
		else
		{//condition == false
			if(e.is_breakable())
			{
				((Exp*)&e.else_get())->breakable_set();
			}
			e.else_get().accept(*execMeAction);
		}

		delete execMeAction;
		delete execMeTest;

		if(e.is_breakable() && ( ((Exp*)&e.else_get())->is_break() || ((Exp*)&e.then_get())->is_break() ))
		{
			((Exp*)&e)->break_set();
		}
	}

	void ExecVisitor::visit (const TryCatchExp  &e)
	{
	}

	void ExecVisitor::visit (const WhileExp  &e)
	{
			ExecVisitor *execMeTest		= new ast::ExecVisitor();
			bool bTestStatus					= false;

			//condition
			e.test_get().accept(*execMeTest);
			while(bConditionState(execMeTest))
			{
				delete execMeTest;

				ExecVisitor *execMeAction = new ast::ExecVisitor();
				e.body_get().accept(*execMeAction);
				delete execMeAction;

				execMeTest		= new ast::ExecVisitor();
				e.test_get().accept(*execMeTest);
			}
			delete execMeTest;
	}

	void ExecVisitor::visit (const ForExp  &e)
	{
		ExecVisitor *execVar = new ast::ExecVisitor();
		e.vardec_get().accept(*execVar);
		//allow break operation
		((Exp*)&e.body_get())->breakable_set();

		if(execVar->result_get()->getType() == InternalType::RealImplicitList)
		{
			ExecVisitor *execBody = new ast::ExecVisitor();
			ImplicitList* pVar = (ImplicitList*)execVar->result_get();
			for(int i = 0 ; i < pVar->size_get() ; i++)
			{
				double dblVal = pVar->extract_value(i);
				Double *pdbl = new Double(dblVal);
				symbol::Context::getInstance()->put(e.vardec_get().name_get(), *(GenericType*)pdbl);
				e.body_get().accept(*execBody);
				if(e.body_get().is_break())
				{
					break;
				}
			}
			delete execBody;
		}
		else
		{//Matrix i = [1,3,2,6] or other type
			ExecVisitor *execBody = new ast::ExecVisitor();
			Double* pVar = (Double*)execVar->result_get();
			for(int i = 0 ; i < pVar->size_get() ; i++)
			{
				double dblVal = pVar->real_get(0,i);
				Double *pdbl = new Double(dblVal);
				symbol::Context::getInstance()->put(e.vardec_get().name_get(), *(GenericType*)pdbl);
				e.body_get().accept(*execBody);
			}
			delete execBody;
		}
		delete execVar;
	}

	void ExecVisitor::visit (const BreakExp &e)
	{
		((BreakExp*)&e)->break_set();
	}

	void ExecVisitor::visit (const ReturnExp &e)
	{
		if(e.is_global())
		{//return 

		}
		else
		{//return(x)
			ExecVisitor execVar;
			e.exp_get().accept(execVar);
			
			for(int i = 0 ; i < execVar.result_size_get() ; i++)
			{
				result_set(i, execVar.result_get(i));
			}
		}
	}

	void ExecVisitor::visit (const SeqExp  &e)
	{
		std::list<Exp *>::const_iterator	i;

		for (i = e.exps_get().begin (); i != e.exps_get().end (); ++i)
		{
			ExecVisitor *execMe = new ast::ExecVisitor();
			if(e.is_breakable())
			{
				(*i)->breakable_set();
			}

			(*i)->accept (*execMe);

			if(execMe->result_get() != NULL)
			{
				if(execMe->result_get()->getAsCallable())
				{
					Callable *pCall = execMe->result_get()->getAsCallable();
					types::typed_list out;
					types::typed_list in;

					Function::ReturnValue Ret = pCall->call(in, (int)expected_size_get(), out);

					if(Ret == Callable::OK)
					{
						if(expected_size_get() == 1 && out.size() == 0) //to manage ans
						{
							if((int)out.size() < expected_size_get())
							{
								std::ostringstream os;
								os << "bad lhs, expected : " << expected_size_get() << " returned : " << out.size() << std::endl;
								throw os.str();
							}
						}

						for(int i = 0 ; i < out.size() ; i++)
						{
							out[i]->DecreaseRef();
							execMe->result_set(i, out[i]);
						}
					}
					else if(Ret == Callable::Error)
					{
						std::ostringstream os;
						char szError[bsiz];
	#ifdef _MSC_VER
						sprintf_s(szError, bsiz, _("Function call failed\n"));
	#else
						sprintf(szError, _("Function call failed\n"));
	#endif
						throw string(szError);
					}
				}

				if(execMe->result_get()->isDeletable())
				{
					symbol::Context::getInstance()->put(symbol::Symbol("ans"), *execMe->result_get());
					if((*i)->is_verbose())
					{
						std::ostringstream ostr;
						ostr << "ans = " << std::endl;
						ostr << std::endl;
						ostr << execMe->result_get()->toString(10,75) << std::endl;
						YaspWrite((char *)ostr.str().c_str());
					}
				}

			}

			delete execMe;
			if(((SeqExp*)&e)->is_breakable() && (*i)->is_break())
			{
				((SeqExp*)&e)->break_set();
				break;
			}
		}
	}

	void ExecVisitor::visit (const ArrayListExp  &e)
	{
		std::list<Exp *>::const_iterator it;
		int i = 0;
		for(it = e.exps_get().begin() ; it != e.exps_get().end() ; it++)
		{
			ExecVisitor *execArg = new ExecVisitor();
			(*it)->accept(*execArg);
			//execArg->result_get()->IncreaseRef();
			result_set(i, execArg->result_get());
			delete execArg;
			//result_get(i)->DecreaseRef();
			i++;
		}
	}

	void ExecVisitor::visit (const AssignListExp  &e)
	{
	}
	/** \} */

	/** \name Visit Single Operation nodes.
	** \{ */
	void ExecVisitor::visit (const NotExp &e)
	{
		/*
		@ or ~= !
		*/
		ExecVisitor* execMe = new ast::ExecVisitor();
		e.exp_get().accept(*execMe);

		if(execMe->result_get()->isDouble())
		{
			Double *pdbl	= execMe->result_get()->getAsDouble();
			Bool *pReturn	= new Bool(pdbl->rows_get(), pdbl->cols_get());
			double *pR		= pdbl->real_get();
			bool *pB			= pReturn->bool_get();
			for(int i = 0 ; i < pdbl->size_get() ; i++)
			{
				if(pR[i] == 0)
				{
					pB[i] = true;
				}
				else
				{
					pB[i] = false;
				}
			}
			result_set(pReturn);
		}
		else if(execMe->result_get()->isBool())
		{
			Bool *pb			= execMe->result_get()->getAsBool();
			Bool *pReturn	= new Bool(pb->rows_get(), pb->cols_get());
			bool *pR			= pb->bool_get();
			bool *pB			= pReturn->bool_get();

			for(int i = 0 ; i < pb->size_get() ; i++)
			{
				pB[i] = pR[i];
			}
			result_set(pReturn);
		}
		delete execMe;
	}

	void ExecVisitor::visit (const TransposeExp &e)
	{
		/*
		'
		*/
		ExecVisitor* execMe = new ast::ExecVisitor();
		e.exp_get().accept(*execMe);

		bool bConjug = e.conjugate_get() == TransposeExp::_Conjugate_;

		if(execMe->result_get()->isDouble())
		{
			Double *pdbl		= execMe->result_get()->getAsDouble();
			Double *pReturn	= NULL;

			if(pdbl->isComplex())
			{
				pReturn				= new Double(pdbl->cols_get(), pdbl->rows_get(), true);
				double *pInR	=	pdbl->real_get();
				double *pInI	=	pdbl->img_get();
				double *pOutR	=	pReturn->real_get();
				double *pOutI	=	pReturn->img_get();

				vTransposeComplexMatrix(pInR, pInI, pdbl->rows_get(), pdbl->cols_get(), pOutR, pOutI, bConjug);
			}
			else
			{
				pReturn				= new Double(pdbl->cols_get(), pdbl->rows_get(), false);
				double *pInR	=	pdbl->real_get();
				double *pOutR	=	pReturn->real_get();

				vTransposeRealMatrix(pInR, pdbl->rows_get(), pdbl->cols_get(), pOutR);
			}
			result_set(pReturn);
		}
		else
		{
		}



		delete execMe;
	}
	/** \} */

	/** \name Visit Declaration nodes.
	** \{ */
	/** \brief Visit Var declarations. */
	void ExecVisitor::visit (const VarDec  &e)
	{
		/*Create local exec visitor*/
		ExecVisitor* execMe = new ast::ExecVisitor();
		try
		{
			/*getting what to assign*/
			e.init_get().accept(*execMe);
			result_set(execMe->result_get());
			result_get()->IncreaseRef();
		}
		catch(string sz)
		{
			throw sz;
		}
		delete execMe;
	}

	void ExecVisitor::visit (const FunctionDec  &e)
	{
		/*
		function foo
		endfunction
		*/
		std::list<ast::Var *>::const_iterator	i;

		//get input parameters list
		std::list<symbol::Symbol> *pVarList = new std::list<symbol::Symbol>();
		ArrayListVar *pListVar = (ArrayListVar *)&e.args_get();
		for(i = pListVar->vars_get().begin() ; i != pListVar->vars_get().end() ; i++)
		{
			string sz = ((SimpleVar*)(*i))->name_get().name_get();
			pVarList->push_back(((SimpleVar*)(*i))->name_get());
		}

		//get output parameters list
		std::list<symbol::Symbol> *pRetList = new std::list<symbol::Symbol>();
		ArrayListVar *pListRet = (ArrayListVar *)&e.returns_get();
		for(i = pListRet->vars_get().begin() ; i != pListRet->vars_get().end() ; i++)
		{
			pRetList->push_back(((SimpleVar*)(*i))->name_get());
		}

		//types::Macro macro(VarList, RetList, (SeqExp&)e.body_get());
		types::Macro *pMacro = new types::Macro(e.name_get().name_get(), *pVarList, *pRetList, (SeqExp&)e.body_get(), "script");
		symbol::Context::getInstance()->AddMacro(pMacro);
	}
  
	void ExecVisitor::visit (const ClassDec &e)
	{
		types::Class *super = NULL;
		types::Class *kls = NULL;
		slots_t::const_iterator it;
		const slots_t &slots = e.slots_get();
		
		if(e.super_get() != NULL)
		{
			types::ObjectMatrix *super_mat = dynamic_cast<types::ObjectMatrix*>(symbol::Context::getInstance()->get(*e.super_get()));
			if(super_mat)
				super = dynamic_cast<types::Class*>(super_mat->object_ref_get());
		}
		
		kls = types::Class::create(e.name_get()->name_get(), super);
		for(it = slots.begin(); it != slots.end(); ++it)
		{
			SlotDec *sdec = *it;
			types::Slot::Visibility vis = types::Slot::PUBLIC;
			std::list<Var*>::iterator vars_it;
			std::list<Var*> vars = sdec->attributes_get().vars_get();
			bool class_slot = false;
			
			PropertyDec *pdec = dynamic_cast<PropertyDec*>(sdec);
			if(pdec != NULL)
			{
				Callable *setter = NULL;
				InternalType *def = NULL;
				if(pdec->default_get())
				{
					ExecVisitor execMe;
					pdec->default_get()->accept(execMe);
					def = execMe.result_get();
					def->IncreaseRef();
				}
				
				for(vars_it = vars.begin(); vars_it != vars.end(); ++vars_it)
				{
					std::string attr = dynamic_cast<SimpleVar*>(*vars_it)->name_get().name_get();
					if(attr == "public")
						vis = types::Slot::PUBLIC;
					else if(attr == "protected")
						vis = types::Slot::PROTECTED;
					else if(attr == "private")
						vis = types::Slot::PRIVATE;
					else if(attr == "ro")
						setter = ro_setter;
					else if(attr == "cls")
						class_slot = true;
				}
				
				if(class_slot)
				{
					kls->install_property(sdec->name_get().name_get(), vis, def, NULL, setter);
				}
				else
				{
					kls->install_instance_property(sdec->name_get().name_get(), vis, def, NULL, setter);
				}
				
				if(def)
				{
					def->DecreaseRef();
				}
			}
			else
			{
				MethodDec *mdec = dynamic_cast<MethodDec*>(sdec);
				bool getter = false;
				bool setter = false;
				
				std::list<symbol::Symbol> &in = *new std::list<symbol::Symbol>;
				std::list<symbol::Symbol> &out = *new std::list<symbol::Symbol>;
				std::list<Var*>::const_iterator it;
				
				for(it = mdec->args_get().vars_get().begin(); it != mdec->args_get().vars_get().end(); ++it)
				{
					in.push_back(dynamic_cast<const SimpleVar*>(*it)->name_get());
				}
				
				for(it = mdec->returns_get().vars_get().begin(); it != mdec->returns_get().vars_get().end(); ++it)
				{
					out.push_back(dynamic_cast<const SimpleVar*>(*it)->name_get());
				}
				
				Callable *code = new types::Macro(sdec->name_get().name_get() + "::" + e.name_get()->name_get(),
					in, out, (SeqExp&)mdec->body_get(), "script");
				
				for(vars_it = vars.begin(); vars_it != vars.end(); ++vars_it)
				{
					std::string attr = dynamic_cast<SimpleVar*>(*vars_it)->name_get().name_get();
					if(attr == "public")
						vis = types::Slot::PUBLIC;
					else if(attr == "protected")
						vis = types::Slot::PROTECTED;
					else if(attr == "private")
						vis = types::Slot::PRIVATE;
					else if(attr == "getter")
						getter = true;
					else if(attr == "setter")
						setter = true;
					else if(attr == "cls")
						class_slot = true;
				}
				
				if(getter || setter)
				{
					std::string slotName = sdec->name_get().name_get();
					Slot *mslot = NULL;
					
					if(class_slot)
					{
						if(kls->GetSlots().find(slotName) != kls->GetSlots().end())
						{
							mslot = &kls->GetSlots().find(slotName)->second;
						}
					}
					else
					{
						if(kls->GetInstanceSlots().find(slotName) != kls->GetInstanceSlots().end())
						{
							mslot = &kls->GetInstanceSlots().find(slotName)->second;
						}
					}
					
					PropertySlot *slot = dynamic_cast<PropertySlot*>(mslot);
					if(slot == NULL)
					{
						std::stringstream ss;
						ss << "Error: slot " << sdec->name_get().name_get() << " not found.";
						throw ss.str();
					}
					
					if(getter)
					{
						slot->getter = code;
					}
					else
					{
						slot->setter = code;
					}
				}
				else
				{
					if(class_slot)
					{
						kls->install_method(sdec->name_get().name_get(), vis, code);
					}
					else
					{
						kls->install_instance_method(sdec->name_get().name_get(), vis, code);
					}
				}
			}
		}
		
		ObjectMatrix *res = types::ObjectMatrix::create_standard_ref(kls);
		result_set(res);
		symbol::Context::getInstance()->put(symbol::Symbol(*e.name_get()), *res);
	}
  
	void ExecVisitor::visit (const PropertyDec &)
	{
	}
  
	void ExecVisitor::visit (const MethodDec &)
	{
	}
	/** \} */

	/** \name Visit Type dedicated Expressions related node.
	** \{ */
	void ExecVisitor::visit(const ListExp &e)
	{
		ExecVisitor*	execMeStart = new ast::ExecVisitor();
		ExecVisitor*	execMeStep	= new ast::ExecVisitor();
		ExecVisitor*	execMeEnd		= new ast::ExecVisitor();

		try
		{
			e.start_get().accept(*execMeStart);
			execMeStart->result_get()->IncreaseRef();
			GenericType* pITStart = (GenericType*)execMeStart->result_get();
			if(pITStart->rows_get() != 1 || pITStart->cols_get() != 1)
			{
				throw 1;
			}


			e.step_get().accept(*execMeStep);
			execMeStep->result_get()->IncreaseRef();
			GenericType* pITStep = (GenericType*)execMeStep->result_get();
			if(pITStep->rows_get() != 1 || pITStep->cols_get() != 1)
			{
				throw 2;
			}

			e.end_get().accept(*execMeEnd);
			execMeEnd->result_get()->IncreaseRef();
			GenericType* pITEnd = (GenericType*)execMeEnd->result_get();
			if(pITEnd->rows_get() != 1 || pITEnd->cols_get() != 1)
			{
				throw 3;
			}

			ImplicitList *pIL	= new ImplicitList(
				execMeStart->result_get(),
				execMeStep->result_get(),
				execMeEnd->result_get());

			result_set(pIL);
		}
		catch(int iPos)
		{
			char st[bsiz];
#ifdef _MSC_VER
			sprintf_s(st, bsiz, _("%s: Wrong type for argument %d: Scalar expected.\n"), ":", iPos);
#else
			sprintf(st, _("%s: Wrong type for argument %d: Scalar expected.\n"), "::", 1);
#endif
			throw string(st);
		}

		delete execMeStart;
		delete execMeStep;
		delete execMeEnd;
	}
	/** \} */

	int ExecVisitor::expected_size_get(void)
	{
		return _excepted_result;
	}

	int ExecVisitor::result_size_get(void)
	{
		return (int)_result.size();
	}

	void ExecVisitor::expected_size_set(int _iSize)
	{
		_excepted_result = _iSize;
	}

	InternalType* ExecVisitor::result_get(void)
	{
		return result_get(0);
	}

	types::InternalType* ExecVisitor::result_get(int _iPos)
	{
		if(_iPos >= _result.size())
		{
			return NULL;
		}
		return _result[_iPos];
	}

	void ExecVisitor::result_set(int _iPos, const types::InternalType *gtVal)
	{
		if(_iPos < _result.size())
		{
			if(_result[_iPos] != NULL && _result[_iPos]->isDeletable())
			{
				delete _result[_iPos];
			}
		}

		for(size_t i = _result.size() ; i <= _iPos ; i++)
		{
			_result.push_back(NULL);
		}
		_result[_iPos] = (InternalType *)gtVal;
	}

	void ExecVisitor::result_set(const InternalType *gtVal)
	{
		result_set(0, gtVal);
	}
}

using namespace ast;
//using ast::ExecVisitor;

bool bConditionState(ast::ExecVisitor *exec)
{
	if(((GenericType*)exec->result_get())->isDouble() && ((Double*)exec->result_get())->isComplex() == false)
	{
		Double *pR		= (Double*)exec->result_get();
		double *pReal	= pR->real_get();

		for(int i = 0 ; i < pR->size_get() ; i++)
		{
			if(pReal[i] == 0)
			{
				return false;
			}
		}
	}
	else if(((GenericType*)exec->result_get())->isBool())
	{
		Bool *pB		= (Bool*)exec->result_get();
		bool *pData		= pB->bool_get();

		for(int i = 0 ; i < pB->size_get() ; i++)
		{
			if(pData[i] == false)
			{
				return false;
				break;
			}
		}
	}
	else if(((GenericType*)exec->result_get())->isUInt())
	{
	}
	else if(((GenericType*)exec->result_get())->isInt())
	{
	}
	else
	{
		return false;
	}
	return true;
}

void vTransposeRealMatrix(double *_pdblRealIn, int _iRowsIn, int _iColsIn, double *_pdblRealOut)
{
	int iIndex = 0;
	for(iIndex = 0 ; iIndex < _iRowsIn * _iColsIn ; iIndex++)
	{
		int iNewCoord	= iIndex % _iRowsIn * _iColsIn + (iIndex / _iRowsIn);
		_pdblRealOut[iNewCoord]	= _pdblRealIn[iIndex];
	}
}

void vTransposeComplexMatrix(double *_pdblRealIn, double *_pdblImgIn, int _iRowsIn, int _iColsIn, double *_pdblRealOut, double *_pdblImgOut, bool _bConjugate)
{
	int iIndex = 0;

	if(_bConjugate == false)
	{
		for(iIndex = 0 ; iIndex < _iRowsIn * _iColsIn ; iIndex++)
		{
			int iNewCoord	= iIndex % _iRowsIn * _iColsIn + (iIndex / _iRowsIn);

			_pdblRealOut[iNewCoord]	= _pdblRealIn[iIndex];
			_pdblImgOut[iNewCoord]	= _pdblImgIn[iIndex];
		}
	}
	else
	{
		for(iIndex = 0 ; iIndex < _iRowsIn * _iColsIn ; iIndex++)
		{
			int iNewCoord	= iIndex % _iRowsIn * _iColsIn + (iIndex / _iRowsIn);

			_pdblRealOut[iNewCoord]	= _pdblRealIn[iIndex];
			//Conjugate
			_pdblImgOut[iNewCoord]	= -_pdblImgIn[iIndex];
		}
	}
}


int GetIndexList(std::list<ast::Exp *> _plstArg, int** _piIndexSeq, int** _piMaxDim, InternalType *_pRefVar, int *_iDimSize)
{
	//Create list of indexes
	//std::vector<std::vector<int>> IndexList;
	symbol::Context *pcontext = symbol::Context::getInstance();
	int iProductElem				= (int)_plstArg.size();
	int **piIndexList				= NULL;
	int iTotalCombi					= 1;
	ExecVisitor* execMeArg	= new ExecVisitor();

	int *piTabSize					= new int[iProductElem];
	(*_piMaxDim)						= new int[iProductElem];
	piIndexList							= new int*[iProductElem];


	int k = 0;
	std::list<Exp *>::const_iterator	i;
	for(i = _plstArg.begin() ; i != _plstArg.end() ; i++,k++)
	{
		(*i)->accept(*execMeArg);
		InternalType *pIn = NULL;
		Double *pDbl = NULL;
		bool bDeleteDbl = false;

		if(execMeArg->result_get()->getType() == InternalType::RealImplicitList)
		{//a:b:c
			int iMaxDim = 0;
			if(_pRefVar != NULL)
			{
				iMaxDim = GetVarMaxDim(_pRefVar, k, iProductElem);
			}

			Double dbl(iMaxDim); // $
			ImplicitList *pIL = execMeArg->result_get()->getAsImplicitList();
			if(pIL->computable() == false)
			{
				if(pIL->start_type_get() == InternalType::RealPoly)
				{
					MatrixPoly *poPoly	= pIL->start_poly_get();
					pIL->start_set(poPoly->evaluate(&dbl)->real_get(0,0));
				}
				if(pIL->step_type_get() == InternalType::RealPoly)
				{
					MatrixPoly *poPoly	= pIL->step_poly_get();
					pIL->step_set(poPoly->evaluate(&dbl)->real_get(0,0));
				}
				if(pIL->end_type_get() == InternalType::RealPoly)
				{
					MatrixPoly *poPoly	= pIL->end_poly_get();
					pIL->end_set(poPoly->evaluate(&dbl)->real_get(0,0));
				}
			}

			double *pDblData = NULL;
			pDbl = new Double(1, pIL->size_get(), &pDblData);
			pIL->extract_matrix(pDblData);
			bDeleteDbl = true;
		}
		else
		{
			pIn = execMeArg->result_get();

			if(pIn->getType() == InternalType::RealPoly)
			{//manage $
				MatrixPoly *pPoly = pIn->getAsPoly();

				if(_pRefVar != NULL)
				{
					int iMaxDim = GetVarMaxDim(_pRefVar, k, iProductElem);
					Double dbl(iMaxDim); // $
					pDbl = pPoly->evaluate(&dbl);
				}
				else
				{//houston we have a problem ...
					Double dbl(0);
					pDbl = pPoly->evaluate(&dbl);

				}
			}
			else if(pIn->getType() == InternalType::RealDouble)
			{
				pDbl	= pIn->getAsDouble();
			}
			else
			{//Heu ... ?
			}
		}

		double *pData = pDbl->real_get();

//					std::vector<int> SubList;
		piTabSize[k] = pDbl->size_get();
		piIndexList[k] = new int[piTabSize[k]];

		(*_piMaxDim)[k] = (int)(pData[0] + 0.5);
		int iSize = pDbl->size_get();
		if(_iDimSize != NULL)
		{
			_iDimSize[k] = iSize;
		}

		for(int j = 0 ; j < iSize ; j++)
		{
			if((int)(pData[j] + 0.5) > (*_piMaxDim)[k])
			{
				(*_piMaxDim)[k] = (int)(pData[j] + 0.5);
			}
			//SubList.push_back((int)pData[j]);
			piIndexList[k][j] = (int)(pData[j] + 0.5);

		}
		iTotalCombi *= iSize;
		//IndexList.push_back(SubList);

		if(bDeleteDbl == true)
		{
			delete pDbl;
		}
	}

	delete execMeArg;

	int iTabSize	= iTotalCombi * iProductElem;
	*_piIndexSeq	= new int[iTabSize];
	ExpandList(piIndexList, piTabSize, iProductElem, *_piIndexSeq);
	return iTotalCombi;
}

void ExpandList(int ** _piList, int *_piListSize, int _iListSizeSize, int *_piResultList)
{
	for(int i = _iListSizeSize - 1 ; i >= 0 ; i--)
	{
		int iPreOcc = 1;
		int iPostOcc = 1;
		for(int k = 0 ; k < i ; k++)
		{
			if(k != i)
			{
				iPreOcc *= _piListSize[k];
			}
		}

		for(int k = i + 1 ; k < _iListSizeSize ; k++)
		{
			if(k != i)
			{
				iPostOcc *= _piListSize[k];
			}
		}

		int iSize = _piListSize[i];
		for(int m = iSize - 1 ; m >= 0  ; m--)
		{
			for(int j1 = iPreOcc - 1 ; j1 >= 0 ; j1--)
			{
				for(int j2 = iPostOcc - 1 ; j2 >= 0 ; j2--)
				{
					//Bloc Offset				-> j1 * ( iPostOcc * iSize) * _iListSizeSize
					//Offset in Bloc		-> m * iPostOcc * _iListSizeSize
					//Offset in SubBloc -> j2 * _iListSizeSize + i
					int iPos = j1 * ( iPostOcc * iSize) * _iListSizeSize + m * iPostOcc * _iListSizeSize + j2 * _iListSizeSize + i;
					_piResultList[iPos] = _piList[i][m];
				}
			}
		}
	}
}

int GetVarMaxDim(InternalType *_pIT, int _iCurrentDim, int _iMaxDim)
{
	if(_pIT == NULL)
	{
		return 0;
	}
	if(_iCurrentDim == 0)
	{
		if(_iMaxDim != 1)
		{
			return ((GenericType*)_pIT)->rows_get();
		}
		else
		{
			return ((GenericType*)_pIT)->size_get();
		}
	}
	else if(_iCurrentDim == 1)
	{
		return ((GenericType*)_pIT)->cols_get();
	}
	else
	{//more than 2 dimansions ? :(
		return ((GenericType*)_pIT)->size_get();
	}
}
