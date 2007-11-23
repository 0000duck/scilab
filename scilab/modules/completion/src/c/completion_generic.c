/*--------------------------------------------------------------------------*/
/* INRIA 2007 */
/* Allan CORNET */
/*--------------------------------------------------------------------------*/
#include <string.h>
#include "completion_generic.h"
#include "MALLOC.h"
/*--------------------------------------------------------------------------*/
char **completion_generic(char **dictionary,int sizedictionary,
						  char *somechars, int *sizeArrayReturned)
{
	char **results = NULL;
	int nbElements = 0;
	int i = 0;

	for (i = 0;i < sizedictionary;i++)
	{
		if (dictionary[i])
		{
			if ( strncmp(dictionary[i],somechars,strlen(somechars)) == 0)
			{
				char *copybuf = NULL;

				nbElements++;
                                /* +1 in MALLOC because a NULL element is inserted at the end of the array */
                                /* This NULL element is used in Java wrapper to know the size of the array */
				if (results) 
                                  results = (char**)REALLOC(results,sizeof(char*)*(nbElements+1)); 
				else 
                                  results = (char**)MALLOC(sizeof(char*)*(nbElements+1));
                                
                                results[nbElements]=NULL; /* Last element set to NULL */
				
                                copybuf = (char*)MALLOC(sizeof(char)*(strlen(dictionary[i])+1));
				if (copybuf) strcpy(copybuf,dictionary[i]);
				results[nbElements-1] = copybuf;
			}
			else
			{
				if (nbElements > 0)
				{
					break;
				}
			}
		}
	}
	*sizeArrayReturned = nbElements;
	return results;
}
/*--------------------------------------------------------------------------*/
