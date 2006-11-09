/*-----------------------------------------------------------------------------------*/ 
/* INRIA 2006 */
/* ALAN LAYEC initial revision  : 30/09/06 fftw3 toolbox*/
/* Allan CORNET scilab module */
/*-----------------------------------------------------------------------------------*/ 
#include "sci_fftw.h"
#include "fftw_utilities.h"
#include "callfftw.h"
#include "MALLOC.h"
/*-----------------------------------------------------------------------------------*/ 
extern FFTW_Plan_struct Sci_Plan;
/*-----------------------------------------------------------------------------------*/ 
/* fftw function.
*
* Scilab Calling sequence :
*   -->fftw(a,sign,dim,incr);
*
* Input : rhs(1) : a scilab double complex or real
*                  vector (row or column)/matrix
*
*         rhs(2) : a scilab double or integer
*                  scalar (-1 or 1) giving the sign
*                  in the exponential component
*
*         rhs(3) : a scilab double or integer
*                  vector (row or column) of dimension
*                  of the Fast Fourier Transform to perform
*
*         rhs(4) : a scilab double or integer
*                  scalar...
*
* Output : a scilab double complex or real
*          vector(row or column)/matrix that
*          gives the result of the transform.
*
*/
int sci_fftw __PARAMS((char *fname,unsigned long fname_len))
{
	/* declaration of variables to store scilab parameters address */
	static int lr1,li1,it1,m1, n1; /* Rhs(1) */

	static int lr2,li2,it2,m2,n2;   /* Rhs(2) */

	static int it3,m3,n3;           /* Rhs(3) */
	int mn3;

	static int it4,m4,n4;           /* Rhs(4) */
	int mn4;

	int *header;

	double         *ptr_d;
	char           *ptr_c;
	unsigned char  *ptr_uc;
	short          *ptr_s;
	unsigned short *ptr_us;
	int            *ptr_i;
	unsigned int   *ptr_ui;

	/* specific declaration for FFTW library variable */
	fftw_plan p;
	int rank;
	fftw_iodim *dims;
	int howmany_rank;
	fftw_iodim *howmany_dims;

	/* input/output address for transform variables */
	double *ri,*ii,*ro,*io;
	double *ptr;

	/* local counter variable */
	int i,j,k;

	/* local variable */
	int isn,vect;
	int *n,*nspn;
	double zero=0;

	/****************************************
	* Basic constraints on rhs parameters  *
	****************************************/

	/* check min/max lhs/rhs parameters of scilab funcion */
	CheckRhs(1,4);
	CheckLhs(1,1);

	/* 3 rhs not allowed */
	if (Rhs==3)
	{
		Scierror(39,"%s: "
			"Bad number of Rhs parameters\n",
			fname);

		return(0);
	}

	/* retrieve address of input variable to transform */
	GetRhsCVar(1, "d", &it1, &m1, &n1, &lr1, &li1);

	/* void input gives void output */
	if ((m1<1)|(n1<1))
	{
		LhsVar(1)=1;
		PutLhsVar();
		return(0);
	}

	/******************************************
	* Advanced constraints on rhs parameters *
	* Get value of rhs parameters            *
	******************************************/

	/*only one rhs parameter*/
	/*forward fft*/
	if (Rhs==1)
	{
		/* sign of the exp. component */
		isn=-1;
	}
	/* two or four rhs parameters case */
	else
	{
		/* Get dim/type of Rhs(2) */
		header = GetData(2);
		m2  = header[1];
		n2  = header[2];
		it2 = header[3];

		/* */
		CheckDims(2,m2,n2,1,1);

		/* look at for type of Rhs(2) */
		if (VarType(2)==8) /* int */
		{
			/* */
			switch (it2)
			{
			case I_CHAR   : ptr_c=IC_CHAR(&header[4]);
				isn=(int) ptr_c[0];
				break;
			case I_INT16  : ptr_s=IC_INT16(&header[4]);
				isn=(int) ptr_s[0];
				break;
			case I_INT32  : ptr_i=IC_INT32(&header[4]);
				isn=(int) ptr_i[0];
				break;
			case I_UCHAR  : ptr_uc=IC_UCHAR(&header[4]);
				isn=(int) ptr_uc[0];
				break;
			case I_UINT16 : ptr_us=IC_UINT16(&header[4]);
				isn=(int) ptr_us[0];
				break;
			case I_UINT32 : ptr_ui=IC_UINT32(&header[4]);
				isn=(int) ptr_ui[0];
				break;
			}
		}
		else if (VarType(2)==1)  /* double */
		{
			/* */
			ptr_d=(double *)(&header[4]);
			/* */
			isn=(int)ptr_d[0];
		}
		/* if is not int/double then error message */
		else
		{
			Scierror(53,"%s: "
				"Bad type for Rhs(2) parameter\n",
				fname);

			return(0);
		}

		/* check value of second rhs argument */
		if ((isn!=1)&&(isn!=-1))
		{
			Scierror(53,"%s: "
				"Bad value for Rhs(2) parameter\n",
				fname);

			return(0);
		}

		/* four rhs parameters */
		if (Rhs==4)
		{
			/* Get dim/type of Rhs(3) */
			header = GetData(3);
			m3  = header[1];
			n3  = header[2];
			it3 = header[3];

			/* look at for type of Rhs(3) */
			if ((VarType(3)!=8)&&(VarType(3)!=1))
			{
				Scierror(53,"%s: "
					"Bad type for Rhs(3) parameter\n",
					fname);

				return(0);
			}

			/* */
			mn3=m3*n3;

			/* check dims */
			if (m3*n3==0)
			{
				Scierror(999,"%s: "
					"Bad size for Rhs(3) parameter\n",
					fname);

				return(0);
			}

			/* Get dim/type of Rhs(4) */
			header = GetData(4);
			m4  = header[1];
			n4  = header[2];
			it4 = header[3];

			/* look at for type of Rhs(4) */
			if ((VarType(4)!=8)&&(VarType(4)!=1)) /* int */
			{
				Scierror(53,"%s: "
					"Bad type for Rhs(4) parameter\n",
					fname);

				return(0);
			}

			/* */
			mn4=m4*n4;

			/* check dims */
			if (m4*n4==0)
			{
				Scierror(999,"%s: "
					"Bad size for Rhs(4) parameter\n",
					fname);

				return(0);
			}

			/* cross variable size checking */
			if (mn4!=mn3)
			{
				Scierror(999,"%s: "
					"Size of Rhs(3) and Rhs(4) parameters "
					"must be the same\n",
					fname);
				return(0);
			}

			/* alloc n/nspn with MALLOC */
			if ((n=(int *)MALLOC(mn4*sizeof(int)))==NULL)
			{
				/* */
				Scierror(999,"%s: "
					"Allocation memory error\n",
					fname);
				return(0);
			}

			if ((nspn=(int *)MALLOC(mn4*sizeof(int)))==NULL)
			{
				/* */
				Scierror(999,"%s: "
					"Allocation memory error\n",
					fname);
				FREE(n);

				return(0);
			}

			/* n    <- Rhs(3) */
			/* nspn <- Rhs(4) */
			/* check values   */
			for (i=0;i<mn3;i++)
			{
				/* Rhs(3) */
				header = GetData(3);

				switch (VarType(3))
				{
					/* double */
				case 1 :
					{
						ptr_d=(double *)(&header[4]);
						n[i]=(int)ptr_d[i];
						break;
					}
					/* int */
				case 8 :
					{
						switch (it3)
						{
						case I_CHAR   : ptr_c=IC_CHAR(&header[4]);
							n[i]=(int) ptr_c[i];
							break;

						case I_INT16  : ptr_s=IC_INT16(&header[4]);
							n[i]=(int) ptr_s[i];
							break;

						case I_INT32  : ptr_i=IC_INT32(&header[4]);
							n[i]=(int) ptr_i[i];
							break;

						case I_UCHAR  : ptr_uc=IC_UCHAR(&header[4]);
							n[i]=(int) ptr_uc[i];
							break;

						case I_UINT16 : ptr_us=IC_UINT16(&header[4]);
							n[i]=(int) ptr_us[i];
							break;

						case I_UINT32 : ptr_ui=IC_UINT32(&header[4]);
							n[i]=(int) ptr_ui[i];
							break;
						}
						break;
					}
				}
				/* check value of n[i] */
				if (n[i]<=0)
				{
					Scierror(999,"%s: "
						"Bad value for Rhs(3) parameter : %d\n",
						fname,n[i]);
					FREE(n);FREE(nspn);
					return(0);
					break;
				}

				/* Rhs(4) */
				header = GetData(4);

				switch (VarType(4))
				{
					/* double */
				case 1 :
					{
						ptr_d=(double *)(&header[4]);
						nspn[i]=(int)ptr_d[i];
						break;
					}
					/* int */
				case 8 :
					{
						switch (it4)
						{
						case I_CHAR   : ptr_c=IC_CHAR(&header[4]);
							nspn[i]=(int) ptr_c[i];
							break;

						case I_INT16  : ptr_s=IC_INT16(&header[4]);
							nspn[i]=(int) ptr_s[i];
							break;

						case I_INT32  : ptr_i=IC_INT32(&header[4]);
							nspn[i]=(int) ptr_i[i];
							break;

						case I_UCHAR  : ptr_uc=IC_UCHAR(&header[4]);
							nspn[i]=(int) ptr_uc[i];
							break;

						case I_UINT16 : ptr_us=IC_UINT16(&header[4]);
							nspn[i]=(int) ptr_us[i];
							break;

						case I_UINT32 : ptr_ui=IC_UINT32(&header[4]);
							nspn[i]=(int) ptr_ui[i];
							break;
						}
						break;
					}
				}
				/* check value of nspn[i] */
				if (nspn[i]<=0)
				{
					Scierror(999,"%s: "
						"Bad value for Rhs(4) parameter : %d\n",
						fname,nspn[i]);
					FREE(n);FREE(nspn);
					return(0);
					break;
				}

			}
		}
	}

	/*********************************************
	* Set address of input/ouput array for fftw *
	*********************************************/

	/* complex data */
	if (it1==1)
	{
		/* set input array address */
		ri=stk(lr1);
		ii=stk(li1);
	}
	/* real data */
	else if (it1==0)
	{
		/* set input array address */
		CreateCVar(1, "d", (i=1,&i), &m1, &n1, &lr1,&li1);

		ri=stk(lr1);
		ii=stk(li1);

		/* set all elements of imaginary parts to 0 */

		C2F(dset)((i=m1*n1,&i), &zero, ii, (k=1,&k));
		//    for (i=0;i<m1*n1;i++) ii[i]=0;
	}

	/* set output array address */
	/* in place fft*/
	if (Sci_Plan.in)
	{
		ro=ri;
		io=ii;
	}
	/* out place fft*/
	else
	{
		/* */
		CreateCVar(2, "d", &it1, &m1, &n1, &lr2,&li2);

		/* */
		ro=stk(lr2);
		io=stk(li2);
	}

	/* reverse address of input/output array
	* if it is a backward fft 
	*/
	if (isn==1)
	{
		/* reverse input */
		ptr=ri;
		ri=ii;
		ii=ptr;

		/* reverse output */
		ptr=ro;
		ro=io;
		io=ptr;
	}

	/**********************************
	* Set parameters needed for fftw *
	**********************************/

	/* check if it is one column or row vector */
	vect=0;
	if ((m1==1)|(n1==1)) vect=1;

	/* vector transform */
	if ((vect)&&(Rhs<=2))
	{
		/* set parameters of fftw_plan_guru_split_dft */
		rank=1;
		if ((dims=(fftw_iodim *)MALLOC(sizeof(fftw_iodim)))==NULL)
		{
			/* */
			Scierror(999,"%s: "
				"Allocation memory error\n",
				fname);
			/* */
			return(0);
		}

		dims[0].n = m1*n1;
		dims[0].is = 1;
		dims[0].os = 1;

		howmany_rank=0;
		howmany_dims=NULL;
	}
	else
	{
		/* 2D fft */
		if (Rhs<=2)
		{
			/* set parameters of fftw_plan_guru_split_dft */
			rank=2;
			if ((dims=(fftw_iodim *)MALLOC(sizeof(fftw_iodim)*rank))==NULL)
			{
				/* */
				Scierror(999,"%s: "
					"Allocation memory error\n",
					fname);
				/* */
				return(0);
			}

			dims[0].n = m1;
			dims[0].is = 1;
			dims[0].os = 1;

			dims[1].n = n1;
			dims[1].is = m1;
			dims[1].os = m1;

			howmany_rank=0;
			howmany_dims=NULL;
		}
		/* multidimensional fft */
		else if (Rhs==4)
		{
			/* size 1x1 for Rhs(3)/Rhs(4) */
			if (mn3==1)
				/* **This is a special case**
				* all is made in the following block.
				* compatibility with scilab fft function.
				*/
			{
				/* set parameters of fftw_plan_guru_split_dft */
				rank=1;
				if ((dims=(fftw_iodim *)MALLOC(sizeof(fftw_iodim)*rank))==NULL)
				{
					/* */
					Scierror(999,"%s: "
						"Allocation memory error\n",
						fname);
					/* */
					return(0);
				}

				dims[0].n = n[0];
				dims[0].is = nspn[0];
				dims[0].os = nspn[0];

				howmany_rank=1;
				if ((howmany_dims=(fftw_iodim *)MALLOC(sizeof(fftw_iodim)*howmany_rank))==NULL)
				{
					/* */
					Scierror(999,"%s: "
						"Allocation memory error\n",
						fname);
					/* */
					return(0);
				}

				/* find number of transforms to compute */
				howmany_dims[0].n = 0;
				j = (n[0]-1)*nspn[0];
				while(j<((m1*n1)-(nspn[0]-1)))
				{
					howmany_dims[0].n++;
					j += nspn[0]*n[0];
				}
				if (j<=((m1*n1)-(nspn[0]-1)))
					k=j+nspn[0];
				else
					k=j-nspn[0]*n[0]+nspn[0];

				howmany_dims[0].is = n[0]*nspn[0];
				howmany_dims[0].os = n[0]*nspn[0];

				if ((p = GetFFTWPlan(rank, dims,
					howmany_rank, howmany_dims,
					ri, ii, ro, io,
					Sci_Plan.flags,isn)) == NULL)
				{
					/* */
					Scierror(999,"%s: "
						"Allocation memory error\n",
						fname);
					/* */
					FREE(dims);
					FREE(howmany_dims);

					/* */
					return(0);
				}
				else
				{
					if (isn==1) /* backward */
					{
						if (Sci_Plan.norm) /* normalized ffti */
						{
							/* */
							double ak;

							ak=1/((double)(n[0]));

							/* must find a BLAS/calelm function to do that */
							for(i=0;i<k;i++)
							{
								ri[i]=ri[i]*ak;
								ii[i]=ii[i]*ak;
							}
						}
					}

					/* */
					for(i=0;i<nspn[0];i++) call_fftw_execute_split_dft(p,&ri[i],&ii[i],&ro[i],&io[i]);

					/* */
					FREE(dims);
					FREE(howmany_dims);
					FREE(n);FREE(nspn);

					/* in place fft*/
					if (Sci_Plan.in) LhsVar(1) = 1;
					/* out place fft*/
					else LhsVar(1) = 2;

					PutLhsVar();

					/* */
					return(0);
				}
			}

			/* size mxn Rhs(3)/Rhs(4)  */
			else
			{
				/* set parameters of fftw_plan_guru_split_dft */
				rank=mn3;
				if ((dims=(fftw_iodim *)MALLOC(sizeof(fftw_iodim)*rank))==NULL)
				{
					/* */
					Scierror(999,"%s: "
						"Allocation memory error\n",
						fname);
					/* */
					return(0);
				}

				/* */
				for(j=0;j<rank;j++)
				{
					dims[j].n = n[j];
					dims[j].is = nspn[j];
					dims[j].os = nspn[j];
				}

				howmany_rank=0;
				howmany_dims=NULL;
			}

		}
	}

	/*****************
	* Get fftw plan *
	*****************/

	/* call GetFFTWPlan */
	if ((p = GetFFTWPlan(rank, dims,
		howmany_rank, howmany_dims,
		ri, ii, ro, io,
		Sci_Plan.flags,isn)) == NULL)
	{
		/* */
		Scierror(999,"%s: "
			"Allocation memory error\n",
			fname);
		/* */
		FREE(dims);
		if (howmany_dims!=NULL) FREE(howmany_dims);

		/* */
		return(0);
	}

	/* */
	FREE(dims);
	if (howmany_dims!=NULL) FREE(howmany_dims);

	/***************
	* Compute fft *
	***************/

	if (isn==1) /* backward */
	{
		if (Sci_Plan.norm) /* normalized ffti */
		{
			/* */
			double ak;

			if (Rhs==4)
			{
				ak=1;
				for(i=0;i<mn3;i++) ak=ak*1/((double)(n[i]));
				FREE(n);FREE(nspn);
			}
			else
			{
				ak=1/((double)(m1*n1));
			}

			/* must find a BLAS/calelm function to do that */
			for(i=0;i<m1*n1;i++)
			{
				ri[i]=ri[i]*ak;
				ii[i]=ii[i]*ak;
			}
		}
	}

	/* execute FFTW plan */
	call_fftw_execute_split_dft(p,ri,ii,ro,io);

	/***********************************
	* Return results in lhs parameter *
	***********************************/

	/* in place fft*/
	if (Sci_Plan.in) LhsVar(1) = 1;
	/* out place fft*/
	else LhsVar(1) = 2;

	PutLhsVar();
	/* */
	return(0);
}
/*-----------------------------------------------------------------------------------*/ 
