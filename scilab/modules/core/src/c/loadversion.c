/*-----------------------------------------------------------------------------------*/
/* INRIA 2006 */
/* Allan CORNET */
/*-----------------------------------------------------------------------------------*/ 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "loadversion.h"
#include "with_module.h"
#include "setgetSCIpath.h"
#include "MALLOC.h"
#include "GetXmlFileEncoding.h"
#include "../../../fileio/includes/FileExist.h"
/*-----------------------------------------------------------------------------------*/ 
#define FORMATFILENAMEVERSION  "%s/modules/%s/VERSION.xml" 
/*-----------------------------------------------------------------------------------*/ 
BOOL getversionmodule(char *modulename,
					  int *sci_version_major,
					  int *sci_version_minor,
					  int *sci_version_maintenance,
					  char *sci_version_string,
					  int *sci_version_revision)
{
	BOOL bOK=FALSE;

	if (with_module(modulename))
	{
		char *filename_VERSION_module=NULL;
		char *SciPath=NULL;
		int len=0;

		SciPath=getSCIpath();
		len=strlen(FORMATFILENAMEVERSION)+strlen(SciPath)+strlen(modulename)+1;
		filename_VERSION_module=(char*)MALLOC(sizeof(char)*len);
		sprintf(filename_VERSION_module,FORMATFILENAMEVERSION,SciPath,modulename);
		if (SciPath){FREE(SciPath);SciPath=NULL;}

		if (FileExist(filename_VERSION_module))
		{
			char *encoding=GetXmlFileEncoding(filename_VERSION_module);

			/* Don't care about line return / empty line */
			xmlKeepBlanksDefault(0);

			/* check if the XML file has been encoded with utf8 (unicode) or not */
			if ( (strcmp("utf-8", encoding)!=0) || (strcmp("UTF-8", encoding)==0) )
			{
				xmlDocPtr doc;
				xmlXPathContextPtr xpathCtxt = NULL;
				xmlXPathObjectPtr xpathObj = NULL;

				int version_major=0;
				int version_minor=0;
				int version_maintenance=0;
				int version_revision=0;
				char *version_string=0;

				doc = xmlParseFile (filename_VERSION_module);

				if (doc == NULL) 
				{
					printf("Error: could not parse file %s\n", filename_VERSION_module);
					return bOK;
				}

			xpathCtxt = xmlXPathNewContext(doc);
			xpathObj = xmlXPathEval((const xmlChar*)"//MODULE_VERSION/VERSION", xpathCtxt);
			if(xpathObj && xpathObj->nodesetval->nodeMax) 
				{
					
					xmlAttrPtr attrib=xpathObj->nodesetval->nodeTab[0]->properties;
					while (attrib != NULL)
						{	
							if (xmlStrEqual (attrib->name, (const xmlChar*) "major"))
								{ 
									/* we found <major> */
									const char *str=(const char*)attrib->children->content;
									version_major=atoi(str);
								}
							else if (xmlStrEqual (attrib->name, (const xmlChar*)"minor"))
								{ 
									/* we found <minor> */
									const char *str=(const char*)attrib->children->content;
									version_minor=atoi(str);
								}
							else if (xmlStrEqual (attrib->name, (const xmlChar*)"maintenance"))
								{ 
									/* we found <maintenance> */
									const char *str=(const char*)attrib->children->content;
									version_maintenance=atoi(str);
								}
							else if (xmlStrEqual (attrib->name, (const xmlChar*)"revision"))
								{ 
									/* we found <revision> */
									const char *str=(const char*)attrib->children->content;
									version_revision=atoi(str);
								}
							else if (xmlStrEqual (attrib->name, (const xmlChar*)"string"))
								{
									/* we found <string> */
									const char *str=(const char*)attrib->children->content;
									version_string=(char*)MALLOC(sizeof(char)*(strlen((const char*)str)+1));
									strcpy(version_string,str);
								}

							attrib = attrib->next;
						}

					*sci_version_major=version_major;
					*sci_version_minor=version_minor;
					*sci_version_maintenance=version_maintenance;
					*sci_version_revision=version_revision;
					strncpy(sci_version_string,version_string,1024);
					if (version_string) {FREE(version_string);version_string=NULL;}
				}
			else
				{
					printf("Error : Not a valid version file %s (should start with <MODULE_VERSION> and contains <VERSION major='' minor='' maintenance='' revision='' string=''>)\n", filename_VERSION_module);
					return bOK;
				}
			if(xpathObj) xmlXPathFreeObject(xpathObj);
			if(xpathCtxt) xmlXPathFreeContext(xpathCtxt);
				xmlFreeDoc (doc);

				/*
				* Cleanup function for the XML library.
				*/
				xmlCleanupParser();
			}
			else
			{
				printf("Error : Not a valid version file %s (encoding not 'utf-8') Encoding '%s' found\n", filename_VERSION_module, encoding);
			}

			if (encoding) {FREE(encoding);encoding=NULL;}

			bOK=TRUE;
		}
		
		if (filename_VERSION_module) {FREE(filename_VERSION_module);filename_VERSION_module=NULL;}
	}
	return bOK;
}
