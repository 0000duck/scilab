/*-----------------------------------------------------------------------------------*/
/* INRIA */
/*-----------------------------------------------------------------------------------*/
#include "machine.h"

typedef void (*voidf)();

typedef struct 
{
	char *name;
	voidf f;
} FTAB;

extern voidf SetFunction(char *name, int *rep, FTAB *table);
/***********************************
* corr ( dgetx dgety )
***********************************/

#define ARGS_dgetx double *,integer*,integer*
typedef void (*dgetxf)(ARGS_dgetx);

#define ARGS_dgety double *,integer*,integer*
typedef void (*dgetyf)(ARGS_dgety);


/**************** dgetx ***************/
extern void C2F(corexx)(ARGS_dgetx);
void C2F(dgetx)(ARGS_dgetx);
void C2F(setdgetx)(char *name, int *rep);

FTAB FTab_dgetx[] =
{
	{"corexx", (voidf)  C2F(corexx)},
	{(char *) 0, (voidf) 0}
};

/**************** dgety ***************/
extern void C2F(corexy)(ARGS_dgety);
void C2F(dgety)(ARGS_dgety);
void C2F(setdgety)(char *name, int *rep);

FTAB FTab_dgety[] =
{
	{"corexy", (voidf)  C2F(corexy)},
	{(char *) 0, (voidf) 0}
};

/***********************************
* Search Table for corr
*   corr uses two externals : dgetx and dgety 
***********************************/

/** the current function fixed by setdgetx **/


static dgetxf dgetxfonc ;

/** function call **/

void C2F(dgetx)(double *x, integer *incr, integer *istart)
{
	(*dgetxfonc)(x, incr, istart);
}

/** fixes the function associated to name **/

void C2F(setdgetx)(char *name, int *rep)
{
	dgetxfonc = (dgetxf) SetFunction(name,rep,FTab_dgetx);
}


/** the current function fixed by setdgety **/

static dgetyf dgetyfonc ;

void C2F(dgety)(double *y, integer *incr, integer *istart)
{
	(*dgetyfonc)(y, incr, istart);
}


/** fixes the function associated to name **/

void C2F(setdgety)(char *name, int *rep)
{
	dgetyfonc = (dgetyf) SetFunction(name,rep,FTab_dgety);
}

