/*------------------------------------------------------------------------*/
/* file: BasicAlgos.c                                                     */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Jean-Baptiste Silvy                           */
/* desc : Several basic algorithms which can be used in several places in */
/*        the code.                                                       */
/*------------------------------------------------------------------------*/

#include "BasicAlgos.h"
#include "MALLOC.h"
#include "core_math.h"

/*------------------------------------------------------------------------*/
double sciFindStPosMin( double x[], int n )
{
  double min ;
  int i ;

  if ( n <= 0 )
  {
    return -1.0 ;
  }

  min = x[0] ;

  for ( i = 1 ; i < n ; i++ )
  {
    if ( x[i] > 0.0 && x[i] < min )
    {
      min = x[i] ;
    }
  }

  /* if we have found at least one positive value in x, min strictly positive */
  return min ;
}
/*------------------------------------------------------------------------*/
int C2F(entier2d)( integer * n, double * dx,integer * s )
{
  integer ix;
  for (ix = *n -1 ; ix >= 0; --ix) { dx[ix] = (double) s[ix]; }
  return 0;
}  
/*------------------------------------------------------------------------*/
int checkMonotony( double vector[], int nbElement )
{
  int i ;
  if( vector[1] >= vector[0] )
  {
    /* might be incresing */
    for ( i = 1 ; i < nbElement - 1 ; i++ )
    {
      if ( vector[i+1] < vector[i] )
      {
        /* not increasing */
        return 0 ;
      }
    }
    return 1 ;
  }
  else
  {
    /* might be decreasing */
    for ( i = 1 ; i < nbElement - 1 ; i++ )
    {
      if ( vector[i+1] > vector[i] )
      {
        /* not decreasing */
        return 0 ;
      }
    }
    return -1 ;

  }
  return 0 ;

}
/*------------------------------------------------------------------------*/
void doubleArrayCopy( double dest[], const double src[], int nbElement )
{
  memcpy( dest, src, nbElement * sizeof(double) ) ;
}
/*------------------------------------------------------------------------*/
void intArrayCopy( int dest[], const int src[], int nbElement )
{
  memcpy( dest, src, nbElement * sizeof(int) ) ;
}
/*------------------------------------------------------------------------*/
void stringArrayCopy( char * dest[], char * src[], int nbElement )
{
  int i ;
  for ( i = 0 ; i < nbElement ; i++ )
  {
    int elemSize = strlen( src[i] ) + 1 ;
    FREE( dest[i] ) ;

    dest[i] = MALLOC( elemSize * sizeof(char) ) ;

    if ( dest[i] == NULL )
    {
      destroyStringArray( dest, nbElement ) ;
      return ;
    }

    strcpy( dest[i], src[i] ) ;
  }
}
/*------------------------------------------------------------------------*/
void setDoubleArraySingleValue( double dest[], double value, int nbElement )
{
  int i ;
  for ( i = 0 ; i < nbElement ; i++ )
  {
    dest[i] = value ;
  }
}
/*------------------------------------------------------------------------*/
double * createNewArrayFromSource( int destSize, const double src[], int srcSize )
{
  int i ;
  int endCopy = Min( destSize, srcSize ) ;
  /* create new array */
  double * dest = MALLOC( destSize * sizeof(double) ) ;

  if ( dest == NULL )
  {
    return NULL ;
  }

  /* copy the element which needs to be copied */
  memcpy( dest, src, endCopy * sizeof( double ) ) ;

  for ( i = endCopy ; i < destSize ; i++ )
  {
    dest[i] = 0.0 ;
  }

  return dest ;

}
/*------------------------------------------------------------------------*/
void destroyStringArray( char * src[], int nbStrings )
{
  int i ;
  for ( i = 0 ; i < nbStrings ; i++ )
  {
    FREE( src[i] ) ;
    src[i] = NULL ;
  }
  FREE( src ) ;
}
/*-----------------------------------------------------------------------------------*/
double * createDoubleArrayCopy( const double src[], int nbElement )
{
  double * res = MALLOC( nbElement * sizeof(double) ) ;

  if ( res == NULL )
  {
    return NULL ;
  }

  memcpy( res, src, nbElement * sizeof(double) ) ;

  return res ;
}
/*-----------------------------------------------------------------------------------*/
int * createIntArrayCopy( const int src[], int nbElement )
{
  int * res = MALLOC( nbElement * sizeof(int) ) ;
  
  if ( res == NULL )
  {
    return NULL ;
  }
  
  memcpy( res, src, nbElement * sizeof(int) ) ;

  return res ;
}
/*-----------------------------------------------------------------------------------*/
char ** createStringArrayCopy( char * src[], int nbElement )
{
  int i ;
  char ** res = MALLOC( nbElement * sizeof(char *) ) ;

  if ( res == NULL )
  {
    return NULL ;
  }

  for ( i = 0 ; i < nbElement; i++ )
  {
    res[i] = NULL ;
  }

  stringArrayCopy( res, src, nbElement ) ;

  return res ;

}
/*-----------------------------------------------------------------------------------*/
