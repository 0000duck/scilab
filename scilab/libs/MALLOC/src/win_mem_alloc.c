/*-----------------------------------------------------------------------------------*/
/* Allan CORNET */
/* INRIA 2005 */
/*-----------------------------------------------------------------------------------*/
#include "../includes/win_mem_alloc.h"
#include <stdio.h>
#include <string.h>
#include <memory.h>
/*-----------------------------------------------------------------------------------*/
IMPORT_EXPORT_MALLOC_DLL LPVOID MyHeapRealloc(LPVOID lpAddress,SIZE_T dwSize,char *fichier,int ligne)
{
 LPVOID NewPointer=NULL;
 SIZE_T precSize=0;

 if (lpAddress)
 {
	 NewPointer=HeapReAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,lpAddress,dwSize);
 }
 else
 {
	#ifdef _DEBUG
		char MsgError[1024];
		wsprintf(MsgError,"REALLOC (1) Error File %s Line %d ",fichier,ligne);
		MessageBox(NULL,MsgError,"Error",MB_ICONSTOP | MB_OK);
	#endif
		NewPointer=HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,dwSize);

	if (NewPointer==NULL)
	{
		#ifdef _DEBUG
			char MsgError[1024];
			wsprintf(MsgError,"REALLOC (2) Error File %s Line %d ",fichier,ligne);
			MessageBox(NULL,MsgError,"Error",MB_ICONSTOP | MB_OK);
		#endif
	}
 }
 return NewPointer;
}
/*-----------------------------------------------------------------------------------*/
IMPORT_EXPORT_MALLOC_DLL LPVOID MyHeapAlloc(SIZE_T dwSize,char *fichier,int ligne)
{
	LPVOID NewPointer=NULL;

	if (dwSize>0)
	{
		NewPointer=HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,dwSize);

		if (NewPointer==NULL)
		{
			#ifdef _DEBUG
			char MsgError[1024];
			wsprintf(MsgError,"MALLOC (1) Error File %s Line %d ",fichier,ligne);
			MessageBox(NULL,MsgError,"Error",MB_ICONSTOP | MB_OK);
			#endif
		}
	}
	else
	{
		#ifdef _DEBUG
			char MsgError[1024];
			wsprintf(MsgError,"MALLOC (2) Error File %s Line %d ",fichier,ligne);
			MessageBox(NULL,MsgError,"Error",MB_ICONSTOP | MB_OK);
		#endif
			NewPointer=HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,dwSize);
	}
	return NewPointer;
}
/*-----------------------------------------------------------------------------------*/
IMPORT_EXPORT_MALLOC_DLL void MyHeapFree(LPVOID lpAddress,char *fichier,int ligne)
{
	_try
	{
		HeapFree(GetProcessHeap(),HEAP_NO_SERIALIZE,lpAddress);
	}
	_except (EXCEPTION_EXECUTE_HANDLER)
	{
		#ifdef _DEBUG
		char MsgError[1024];
		wsprintf(MsgError,"FREE Error File %s Line %d ",fichier,ligne);
		MessageBox(NULL,MsgError,"Error",MB_ICONSTOP | MB_OK);
		#endif
	}
}
/*-----------------------------------------------------------------------------------*/
IMPORT_EXPORT_MALLOC_DLL LPVOID MyVirtualAlloc(SIZE_T dwSize,char *fichier,int ligne)
{
	LPVOID NewPointer=NULL;

	if (dwSize>0)
	{
		NewPointer=VirtualAlloc(NULL,((unsigned) dwSize),MEM_RESERVE, PAGE_NOCACHE | PAGE_READWRITE);

		if (NewPointer==NULL)
		{
			#ifdef _DEBUG
			char MsgError[1024];
			wsprintf(MsgError,"MALLOC (VirtualAlloc 1) Error File %s Line %d ",fichier,ligne);
			MessageBox(NULL,MsgError,"Error",MB_ICONSTOP | MB_OK);
			#endif
			VirtualFree(NewPointer,0, MEM_RELEASE);
		}
		else
		{
			NewPointer=VirtualAlloc(NewPointer,((unsigned) dwSize),MEM_COMMIT, PAGE_NOCACHE | PAGE_READWRITE);
		}
	}
	else
	{
		#ifdef _DEBUG
		char MsgError[1024];
		wsprintf(MsgError,"MALLOC (VirtualAlloc 2) Error File %s Line %d ",fichier,ligne);
		MessageBox(NULL,MsgError,"Error",MB_ICONSTOP | MB_OK);
		#endif

		NewPointer=VirtualAlloc(NULL,((unsigned) dwSize),MEM_RESERVE, PAGE_NOCACHE | PAGE_READWRITE);
		NewPointer=VirtualAlloc(NewPointer,((unsigned) dwSize),MEM_COMMIT, PAGE_NOCACHE | PAGE_READWRITE);
	}
	return NewPointer;

}
/*-----------------------------------------------------------------------------------*/
IMPORT_EXPORT_MALLOC_DLL void MyVirtualFree(LPVOID lpAddress,SIZE_T dwSize,char *fichier,int ligne)
{
	if (lpAddress)
	{
		VirtualFree(lpAddress, dwSize, MEM_DECOMMIT);
		VirtualFree(lpAddress,0, MEM_RELEASE);
	}
}
/*-----------------------------------------------------------------------------------*/
