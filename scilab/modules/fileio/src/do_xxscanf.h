/*-----------------------------------------------------------------------------------*/ 
/* INRIA */
/*-----------------------------------------------------------------------------------*/ 
#ifndef __DO_XXSCANF_H__
#define __DO_XXSCANF_H__

/*if maxscan is increased don't forget to change the (*xxscanf)(......) 
in do_xxscanf procedure */
#define MAXSCAN 100
#define MAX_STR 1024

typedef union 
{
	char * c;
	long unsigned int lui;
	short unsigned int sui;
	unsigned int ui;
	long int li;
	short int si;
	int i;
	double lf;
	float f;
} rec_entry;

typedef union 
{
	double d;
	char * s;
} entry;
typedef enum {SF_C,SF_S,SF_LUI,SF_SUI,SF_UI,SF_LI,SF_SI,SF_I,SF_LF,SF_F} sfdir;

int do_xxscanf (char *fname, FILE *fp, char *format, int *nargs, char *strv, int *retval, rec_entry *buf, sfdir *type);
#endif /* __DO_XXSCANF_H__ */

