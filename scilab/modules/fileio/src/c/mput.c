/*--------------------------------------------------------------------------*/
/* Scilab */
/* INRIA 2007 */
/*--------------------------------------------------------------------------*/
#include <string.h>
#include "mput.h"
#include "filesmanagement.h"
#include "sciprint.h"
#include "islittleendian.h"
#include "../../../libs/libst/misc.h"
#include "machine.h"
#include "localization.h"
/*--------------------------------------------------------------------------*/
extern struct soundstream ftf; /* defined in mget.c */
extern int swap; /* defined in mget.c */
/*--------------------------------------------------------------------------*/
/*===============================================
* function to write data without type conversion
*===============================================*/
#define MPUT_CHAR_NC(Type) \
{\
	Type *val = (Type *) res ; \
	fwrite(val,sizeof(Type),n,fa); \
}
/*--------------------------------------------------------------------------*/
#define MPUT_NC(Type,Fswap) \
{ \
	Type *val = (Type *) res ; \
	Type vali; \
	for ( i=0; i< n; i++)  \
		   { \
		   vali = *val++; \
		   if ( swap) vali = Fswap(vali); \
		   fwrite(&vali,sizeof(Type),1,fa); \
		} \
}
/*--------------------------------------------------------------------------*/
#define MPUT_GEN_NC(Type,Fswap,cf) \
	switch ( cf )  \
	{ \
	case ' ': MPUT_NC(Type,Fswap); break; \
	case 'b': \
	swap = (islittleendian()==1) ? 1 : 0; \
	MPUT_NC(Type,Fswap); break; \
		case 'l': \
		swap = (islittleendian()==1) ? 0 : 1; \
		MPUT_NC(Type,Fswap); break; \
		default: \
		sciprint(_("%s: %s format not recognized.\n"),"mput",type); \
		*ierr=1;return; \
	}
/*--------------------------------------------------------------------------*/
void C2F(mputnc) (integer *fd, void * res, integer *n1, char *type, integer *ierr)
{  
	char c1,c2;
	int i,swap2,n;
	FILE *fa;
	n=*n1;
	*ierr=0;
	if ((fa = GetFileOpenedInScilab(*fd)) ==NULL) {
		sciprint(_("%s: No input file associated to logical unit %d.\n"),"mput",*fd);
		*ierr=3;
		return;
	}
	swap2 = GetSwapStatus(*fd);

	c1 = ( strlen(type) > 1) ? type[1] : ' '; 
	c2 = ( strlen(type) > 2) ? type[2] : ' '; 
	switch ( type[0] )
	{
	case 'i' : MPUT_GEN_NC(int,swapi,c1);       break;
	case 'l' : MPUT_GEN_NC(long,swapl,c1);      break;
	case 's' : MPUT_GEN_NC(short,swapw,c1);     break;
	case 'c' : MPUT_CHAR_NC(char) ;          break;
	case 'd' : MPUT_GEN_NC(double,swapd,c1);    break;
	case 'f' : MPUT_GEN_NC(float,swapf,c1);     break;
	case 'u' :
		switch ( c1 )
		{
		case 'i' :  MPUT_GEN_NC(unsigned int,swapi,c2); break;
		case 'l' :  MPUT_GEN_NC(unsigned long,swapl,c2); break;
		case 's' :  MPUT_GEN_NC(unsigned short,swapw,c2); break;
		case ' ' :  MPUT_GEN_NC(unsigned int,swapi,' '); break;
		case 'c' :  MPUT_CHAR_NC(unsigned char); break;
		default :  *ierr=1;return ;
		}
		break;
	default : *ierr=1; break;
	}
}
/*--------------------------------------------------------------------------*/
/*================================================
* function to write data stored in double
*================================================*/
/** used for char **/
#define MPUT_CHAR(Type) \
	for ( i=0; i< n; i++)  \
{ \
	Type  val = (char) *res++; \
	fwrite(&val,sizeof(Type),1,fa); \
}
/*--------------------------------------------------------------------------*/
/** write in a machine independant way : i.e data 
is swaped if necessary to output little-endian 
data **/

#define MPUT(Type,Fswap) for ( i=0; i< n; i++)  \
{ \
	Type val; \
	val =(Type) *res++; \
	if ( swap) val = Fswap(val); \
	fwrite(&val,sizeof(Type),1,fa); \
}
/*--------------------------------------------------------------------------*/
/** The output mode is controlled by type[1] **/
#define MPUT_GEN(Type,Fswap,cf) \
	switch ( cf )  \
{ \
	case ' ': MPUT(Type,Fswap); break; \
	case 'b': \
	swap = (islittleendian()==1) ? 1 : 0; \
	MPUT(Type,Fswap); break; \
		case 'l': \
		swap = (islittleendian()==1) ? 0 : 1; \
		MPUT(Type,Fswap); break; \
		default: \
		sciprint(_("%s: %s format not recognized.\n"),"mput",type); \
		*ierr=1;return; \
}
/*--------------------------------------------------------------------------*/
void mput2 (FILE *fa, integer swap2, double *res, integer n, char *type, integer *ierr)
{  
	char c1,c2;
	int i;
	ft_t ft = &ftf;
	*ierr=0;
	ft->fp = fa;
	c1 = ( strlen(type) > 1) ? type[1] : ' '; 
	c2 = ( strlen(type) > 2) ? type[2] : ' '; 
	switch ( type[0] )
	{
	case 'i' : MPUT_GEN(int,swapi,c1);       break;
	case 'l' : MPUT_GEN(long,swapl,c1);      break;
	case 's' : MPUT_GEN(short,swapw,c1);     break;
	case 'c' : MPUT_CHAR(char) ;          break;
	case 'd' : MPUT_GEN(double,swapd,c1);    break;
	case 'f' : MPUT_GEN(float,swapf,c1);     break;
	case 'u' :
		switch ( c1 )
		{
		case 'i' :  MPUT_GEN(unsigned int,swapi,c2); break;
		case 'l' :  MPUT_GEN(unsigned long,swapl,c2); break;
		case 's' :  MPUT_GEN(unsigned short,swapw,c2); break;
		case ' ' :  MPUT_GEN(unsigned int,swapi,' '); break;
		case 'c' :  MPUT_CHAR(unsigned char); break;
		default :  *ierr=1;return ;
		}
		break;
	default : *ierr=1; break;
	}
}
/*--------------------------------------------------------------------------*/
void C2F(mput) (integer *fd, double *res, integer *n, char *type, integer *ierr)
{
	int nc,swap2;
	FILE *fa;
	*ierr=0;
	if ((nc = (int)strlen(type)) == 0) 
	{
		sciprint(_("%s: Format is of length 0.\n"),"mput",type);
		*ierr=2;
		return;
	}
	if ((fa = GetFileOpenedInScilab(*fd)) !=NULL)
	{
		swap2 = GetSwapStatus(*fd);
		mput2(fa,swap2,res,*n,type,ierr);
		if (*ierr > 0) sciprint(_("%s: %s format not recognized.\n"),"mput",type);
	}
	else 
	{
		sciprint(_("%s: No input file associated to logical unit %d\n"),"mput",*fd);
		*ierr=3;
	}
}
/*--------------------------------------------------------------------------*/


