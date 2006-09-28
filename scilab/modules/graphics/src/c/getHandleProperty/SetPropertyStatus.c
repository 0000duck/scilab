/*------------------------------------------------------------------------*/
/* file: SetPropertySatus.c                                               */
/* Copyright INRIA 2006                                                   */
/* Authors : Jean-Baptiste Silvy                                          */
/* desc : define the different type of return status for the sci_set      */
/*        routine                                                         */
/*------------------------------------------------------------------------*/

#include "SetPropertyStatus.h"

/*-----------------------------------------------------------------------------------*/
SetPropertyStatus sciSetFinalStatus( SetPropertyStatus status1, SetPropertyStatus status2 )
{
  if ( status1 == SET_PROPERTY_ERROR || status2 == SET_PROPERTY_ERROR )
  {
    /* problem */
    return -1 ;
  }
  else if ( status1 == SET_PROPERTY_UNCHANGED && status2 == SET_PROPERTY_UNCHANGED )
  {
    /* nothing changed */
    return 1 ;
  }
  else
  {
    /* everything should be ok */
    return 0 ;
  }
}

/*-----------------------------------------------------------------------------------*/
