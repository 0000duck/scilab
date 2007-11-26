/*--------------------------------------------------------------------------*/
/* INRIA 2006 */
/* Allan CORNET */
/*--------------------------------------------------------------------------*/
#include "gw_core.h"
#include "machine.h"
#include "stack-c.h"
#include "MALLOC.h"
#include "getmaxMALLOC.h"
#include "scimem.h"
#include "localization.h"
#include "stackinfo.h"
#include "Scierror.h"
/*--------------------------------------------------------------------------*/
extern integer C2F(adjuststacksize)();
/*--------------------------------------------------------------------------*/
#define MIN_STACKSIZE 180000
/*--------------------------------------------------------------------------*/
/**
* stacksize - set scilab stack size
* Calling Sequence
* stacksize(n)
* stacksize('max')
* stacksize('min')
* sz=stacksize()
* Parameters
* n : integer, the required stack size given in number of double precision words
* 'max' : try to allocate the maximum of memory
* 'max' : allocate the minimum of memory
* sz : 2-vector [total used]
*/
/*--------------------------------------------------------------------------*/
int C2F(sci_stacksize) _PARAMS((char *fname,unsigned long fname_len))
{
	static int l1,n1,m1;

	Rhs=Max(0,Rhs);
	CheckRhs(0,1);
	CheckLhs(0,1);

	if (Rhs == 0)
	{
		int *paramoutINT=NULL;
		int total=0;
		int used=0;
		paramoutINT=(int*)MALLOC(sizeof(int)*2);

		C2F(getstackinfo)(&total,&used);
		paramoutINT[0]=total;
		paramoutINT[1]=used;

		n1=1;m1=2;
		CreateVarFromPtr(Rhs+1,MATRIX_OF_INTEGER_DATATYPE, &n1, &m1, &paramoutINT);

		LhsVar(1) = Rhs+1;
		C2F(putlhsvar)();

		if (paramoutINT) {FREE(paramoutINT);paramoutINT=NULL;}
	}
	else
	{
		if ( GetType(1) == sci_matrix )
		{
			GetRhsVar(1,MATRIX_OF_DOUBLE_DATATYPE,&m1,&n1,&l1);

			if ( (m1 == 1) && (n1 == 1) )
			{
				unsigned long MEMSTACKSIZE = (unsigned long) *stk(l1);

				/* add 1 for alignment problems */
				if ( is_a_valid_size_for_scilab_stack(MEMSTACKSIZE + 1) )
				{
					if ( (MEMSTACKSIZE>=MIN_STACKSIZE) && ((unsigned long)MEMSTACKSIZE<=get_max_memory_for_scilab_stack()) )
					{
						int currentstacksize=0;
						int used=0;

						C2F(getstackinfo)(&currentstacksize,&used);

						if (MEMSTACKSIZE != currentstacksize)
						{
							integer ptr;
							C2F(scimem)( (int *)&MEMSTACKSIZE,&ptr);
							if (ptr) C2F(adjuststacksize)(&MEMSTACKSIZE,&ptr);
							else
							{
								Scierror(999,_("%s : can't alloc more memory.\nTry gstacksize('max').\n"),fname);
								return 0;
							}
						}
						else
						{
							/* same stacksize nothing to do */
						}

						LhsVar(1) = 0;
						C2F(putlhsvar)();
						return 0;
					}
					else
					{
						Scierror(1504,_("%s : Out of bounds value. Not in [%lu,%lu].\n"),fname,MIN_STACKSIZE,get_max_memory_for_scilab_stack()-1);
						return 0;
					}
				}
				else
				{
					Scierror(1504,_("%s : Out of bounds value. Not in [%lu,%lu].\n"),fname,MIN_STACKSIZE,get_max_memory_for_scilab_stack()-1);
					return 0;
				}
			}
			else
			{
				Scierror(204,_("%s : Argument 1: wrong type argument expecting a scalar or 'min' or 'max'.\n"),fname);
				return 0;
			}
		}
		else
		{
			if ( GetType(1) == sci_strings )
			{
				char *param=NULL;

				GetRhsVar(1,STRING_DATATYPE,&m1,&n1,&l1);
				param=cstk(l1);

				if ( strcmp("max",param) == 0 )
				{
					integer ptr=0;

					integer memstacktotal=0;
					integer memstackused=0;
					integer memgstacktotal=0;
					integer memgstackused=0;

					integer newmaxstack=0;

					unsigned long memmaxavailablebyscilab=get_max_memory_for_scilab_stack();
					unsigned long maxmemfree=(GetLargestFreeMemoryRegion())/sizeof(double);

					C2F(getstackinfo)(&memstacktotal,&memstackused);
					C2F(getgstackinfo)(&memgstacktotal,&memgstackused);

					newmaxstack = maxmemfree-memstackused-memgstackused;

					if ( newmaxstack > (integer)memmaxavailablebyscilab )
					{
						newmaxstack = memmaxavailablebyscilab;
					}
					if (newmaxstack < MIN_STACKSIZE)
					{
						newmaxstack = MIN_STACKSIZE;
					}

					C2F(scimem)(&newmaxstack,&ptr);
					if (ptr)
					{
						C2F(adjuststacksize)(&newmaxstack,&ptr);
					}

					LhsVar(1) = 0;
					C2F(putlhsvar)();
					return 0;
				}
				else if ( strcmp("min",param) == 0 )
				{
					integer ptr=0;
					integer memstacktotal=0;
					integer memstackused=0;
					integer newminstack=0;

					C2F(getstackinfo)(&memstacktotal,&memstackused);

					if (memstackused<MIN_STACKSIZE)
					{
						newminstack = MIN_STACKSIZE;
					}
					else
					{
						/* Add 3000 security for the stack */
						newminstack = memstackused+3000;
					}

					C2F(scimem)(&newminstack,&ptr);
					if (ptr)
					{
						C2F(adjuststacksize)(&newminstack,&ptr);
					}
					LhsVar(1) = 0;
					C2F(putlhsvar)();
					return 0;
				}
				else
				{
					Scierror(204,_("%s : Argument 1: wrong type argument expecting a scalar or 'min' or 'max'.\n"),fname);
					return 0;
				}
			}
			else
			{
				Scierror(204,_("%s : Argument 1: wrong type argument expecting a scalar or 'min' or 'max'.\n"),fname);
				return 0;
			}
		}
	}
	return 0;
}
/*--------------------------------------------------------------------------*/
