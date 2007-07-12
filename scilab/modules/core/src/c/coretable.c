/*-----------------------------------------------------------------------------------*/
/* INRIA */
/* @TODO : rewrite all this crap ... this should not be released */
/*-----------------------------------------------------------------------------------*/
#include <string.h>
#include "FTables.h"


/***********************************
* Search Table for interf
***********************************/

#define ARGS_interf void *,void *,void *,void *,void *,void *,void *,void *,void *,void *,void *,void *,void *,void *,void *,void *,void *,void *,void *,void *,void *,void *,void *,void *,void *,void *,void *,void *,void *,void *
typedef integer * (*interff)(ARGS_interf);


#define ARGS_interf1 char *,long int
typedef integer * (*interff1)(ARGS_interf1);

/**************** interf ***************/
extern void C2F(icse0)(ARGS_interf);
extern void C2F(icse)(ARGS_interf);
extern void C2F(icscof)(ARGS_interf);
void C2F(interf)(ARGS_interf);
void C2F(interf1)(ARGS_interf1);
void C2F(setinterf)(char *name, int *rep);

FTAB FTab_interf[] =
{
	{"icscof", (voidf)  C2F(icscof)},
	{"icse", (voidf)  C2F(icse)},
	{"icse0", (voidf)  C2F(icse0)},
	{(char *) 0, (voidf) 0}
};


/***********************************
* Search Table for interf 
**********************************/

/** the current function fixed by setinterf **/

static interff interffonc ;

/** function call **/

void C2F(interf)(void * x1, void * x2, void * x3, void * x4, void * x5, void * x6, void * x7, void * x8, void * x9, void * x10, void * x11, void * x12, void * x13, void * x14, void * x15, void * x16, void * x17, void * x18, void * x19, void * x20, void * x21, void * x22, void * x23, void * x24, void * x25, void * x26, void * x27, void * x28, void * x29, void * x30)
{
	(*interffonc)(x1 ,x2 ,x3 ,x4 ,x5 ,x6 ,x7 ,x8 ,x9 ,x10,
		x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,
		x21,x22,x23,x24,x25,x26,x27,x28,x29,x30);
}


void C2F(interf1)(char *name, long int size)
{
	((interff1) *interffonc)(name,strlen(name));
}

/** fixes the function associated to name **/

void C2F(setinterf)(char *name, int *rep)
{
	interffonc = (interff) SetFunction(name,rep,FTab_interf);
}

/** function call **/
