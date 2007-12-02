/*--------------------------------------------------------------------------*/
/* Allan CORNET */
/* INRIA 2007 */
/*--------------------------------------------------------------------------*/
#include <string.h>
#include <ctype.h>
#include "isletter.h"
#include "MALLOC.h"
/*--------------------------------------------------------------------------*/
BOOL *IsDigit(char *input_string)
{
	BOOL *returnedValues = NULL;
	if (input_string)
	{
		int i = 0;
		int length_input_string = (int)strlen(input_string);

		if (length_input_string > 0)
		{
			returnedValues = (BOOL*)MALLOC(sizeof(BOOL)*length_input_string);
			if (returnedValues)
			{
				for (i = 0;i < length_input_string; i++)
				{
					if ( isdigit(input_string[i]) ) returnedValues[i] = TRUE;
					else returnedValues[i] = FALSE;
				}
			}
		}
	}
	return returnedValues;
}
/*--------------------------------------------------------------------------*/
