/*-----------------------------------------------------------------------------------*/
/* --- Windows only ---- */
#include <windows.h>
#include "win_mem_alloc.h"
/*-----------------------------------------------------------------------------------*/
#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383
/*-----------------------------------------------------------------------------------*/
BOOL WindowsQueryRegistry(char *ParamIn1,char *ParamIn2,char *ParamIn3,char *ParamOut1,int *ParamOut2,BOOL *OuputIsREG_SZ);
BOOL WindowsQueryRegistryList(char *ParamIn1,char *ParamIn2,int dimMax,char **ListKeys);
BOOL WindowsQueryRegistryNumberOfElementsInList(char *ParamIn1,char *ParamIn2,int *Number);
HKEY GetHkeyrootFromString(char *string);
/*-----------------------------------------------------------------------------------*/
BOOL WindowsQueryRegistry(char *ParamIn1,char *ParamIn2,char *ParamIn3,char *ParamOut1,int *ParamOut2,BOOL *OuputIsREG_SZ)
{
	BOOL bOK=TRUE;
	HKEY key;
	HKEY hKeyToOpen=NULL;

	hKeyToOpen =GetHkeyrootFromString(ParamIn1);

	if ( RegOpenKeyEx(hKeyToOpen, ParamIn2, 0, KEY_QUERY_VALUE , &key) == ERROR_SUCCESS )
	{
		DWORD type=0;

		if ( RegQueryValueEx(key, ParamIn3, NULL, &type, NULL, NULL) == ERROR_SUCCESS )
		{
			if ( (type == REG_EXPAND_SZ) || (type == REG_SZ) )
			{
				DWORD Length=MAX_PATH;
				char Line[MAX_PATH];
				if (RegQueryValueEx(key, ParamIn3, NULL, &type, (LPBYTE)&Line, &Length) == ERROR_SUCCESS )
				{
					wsprintf(ParamOut1,"%s",Line);
					*OuputIsREG_SZ=TRUE;
				}
			}
			else
			{
				DWORD size=4;
				int Num=0;
				if (RegQueryValueEx(key, ParamIn3, NULL, &type, (LPBYTE)&Num, &size) == ERROR_SUCCESS )
				{
					*ParamOut2=Num;
					*OuputIsREG_SZ=FALSE;
				}
			}
		}
		RegCloseKey(key);
	}
	else bOK=FALSE;

	return bOK;
}
/*-----------------------------------------------------------------------------------*/
BOOL WindowsQueryRegistryList(char *ParamIn1,char *ParamIn2,int dimMax,char **ListKeys)
{
	BOOL bOK=TRUE;
	HKEY key;
	HKEY hKeyToOpen=NULL;

	hKeyToOpen =GetHkeyrootFromString(ParamIn1);

	if ( RegOpenKeyEx(hKeyToOpen, ParamIn2, 0, KEY_READ , &key) == ERROR_SUCCESS )
	{
		int i=0;
		for (i=0; i<dimMax; i++) 
		{ 
			TCHAR    achKey[MAX_KEY_LENGTH];
			DWORD    cbName = MAX_KEY_LENGTH;
			DWORD	Type;
			DWORD retCode;

			retCode=RegEnumValue(key,i,
				achKey,
				&cbName,
				NULL,
				&Type,
				NULL,
				NULL);

			if (retCode != ERROR_SUCCESS) 
			{
				bOK=FALSE;			
				RegCloseKey(key);
				return bOK;
			}
			else
			{
				char *chaine=NULL;
				chaine=(char*) MALLOC(sizeof(char)*255);
				strcpy(chaine,achKey);
				*ListKeys=chaine;
				*ListKeys++;
			}
		}

		RegCloseKey(key);

	}
	else bOK=FALSE;

	return bOK;
}
/*-----------------------------------------------------------------------------------*/
HKEY GetHkeyrootFromString(char *string)
{
	HKEY hkey=NULL;

	if ( strcmp(string,"HKEY_CLASSES_ROOT") == 0 )	hkey = HKEY_CLASSES_ROOT;
	if ( strcmp(string,"HKEY_CURRENT_USER") == 0 )	hkey = HKEY_CURRENT_USER;
	if ( strcmp(string,"HKEY_LOCAL_MACHINE") == 0 )	hkey = HKEY_LOCAL_MACHINE;
	if ( strcmp(string,"HKEY_USERS") == 0 )			hkey = HKEY_USERS;
	if ( strcmp(string,"HKEY_DYN_DATA") == 0 )		hkey = HKEY_DYN_DATA;

	return hkey;
}
/*-----------------------------------------------------------------------------------*/
BOOL WindowsQueryRegistryNumberOfElementsInList(char *ParamIn1,char *ParamIn2,int *Number)
{
	BOOL bOK=TRUE;

	HKEY hKeyToOpen;
	HKEY hTestKey;

	hKeyToOpen =GetHkeyrootFromString(ParamIn1);
	if( RegOpenKeyEx(hKeyToOpen,ParamIn2, 0, KEY_READ, &hTestKey) == ERROR_SUCCESS )
	{
		DWORD retCode; 

		TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
		DWORD    cchClassName = MAX_PATH;  // size of class string 
		DWORD    cSubKeys=0;               // number of subkeys 
		DWORD    cbMaxSubKey;              // longest subkey size 
		DWORD    cchMaxClass;              // longest class string 
		DWORD    cValues;              // number of values for key 
		DWORD    cchMaxValue;          // longest value name 
		DWORD    cbMaxValueData;       // longest value data 
		DWORD    cbSecurityDescriptor; // size of security descriptor 
		FILETIME ftLastWriteTime;      // last write time 

		retCode = RegQueryInfoKey(
			hTestKey,                    // key handle 
			achClass,                // buffer for class name 
			&cchClassName,           // size of class string 
			NULL,                    // reserved 
			&cSubKeys,               // number of subkeys 
			&cbMaxSubKey,            // longest subkey size 
			&cchMaxClass,            // longest class string 
			&cValues,                // number of values for this key 
			&cchMaxValue,            // longest value name 
			&cbMaxValueData,         // longest value data 
			&cbSecurityDescriptor,   // security descriptor 
			&ftLastWriteTime);       // last write time 

		if (retCode != ERROR_SUCCESS) bOK=FALSE;
		else *Number=cValues;

		RegCloseKey(hKeyToOpen);
	}
	else bOK=FALSE;

	return bOK;
}
/*-----------------------------------------------------------------------------------*/
