/*------------------------------------------------------------------------*/
/* file: sci_champ.h                                                      */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Jean-Baptiste Silvy                           */
/* desc : interface for champ (and champ1) routine                        */
/*------------------------------------------------------------------------*/

#ifndef _INT_CHAMP_H_
#define _INT_CHAMP_H_

/**
* interface function for the champ routine :
* champ(x,y,fx,fy,[arfact=1.0,rect=[xMin,yMin,xMax,yMax],flag])
*
* @param[in] fname     name of the routine (ie champ)
* @param[in] fname_len length of fname
* @return 0 if success, -1 otherwise
*/
int sci_champ( char * fname, unsigned long fname_len ) ;

/**
* interface function for the champ routine :
* champ1(x,y,fx,fy,[arfact=1.0,rect=[xMin,yMin,xMax,yMax],flag])
*
* @param[in] fname     name of the routine (ie champ)
* @param[in] fname_len length of fname
* @return 0 if success, -1 otherwise
*/
int sci_champ1( char * fname, unsigned long fname_len ) ;

/**
 * Generic function for both champ and champ1.
 */
int sci_champ_G( char *fname, int (*func) (),unsigned long fname_len ) ;

#endif /* _INT_CHAMP_H_ */
