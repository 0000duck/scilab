/*-----------------------------------------------------------------------------------*/
/* INRIA 2007 */
/* Allan CORNET */
/*-----------------------------------------------------------------------------------*/
#include <windows.h>
#include <strsafe.h>
#include <string.h>
#include <stdio.h>
#include "../../../../../libs/DetectFramework2/DetectFramework.h"
#include "../../../../../libs/GetWindowsVersion/GetWindowsVersion.h"
/*-----------------------------------------------------------------------------------*/
#define MSG_DETECT_2K_OR_MORE "Scilab requires Windows 2000 or more."
#define MSG_DETECT_FRAMEWORK "The .NET Framework 2.0 is not installed"
#define MSG_WARNING "Warning"
#define MSG_LOAD_LIBRARIES "Wscilex.exe failed with error %d: %s"
#define MAIN_FUNCTION "Windows_Main"
#define LIBRARY_TO_LOAD "scilab_windows"
#define ARG_NW "-nw"
#define ARG_NWNI "-nwni"
#define ARG_NOGUI "-nogui"
#define LENGTH_BUFFER_SECURITY 64
/*-----------------------------------------------------------------------------------*/
typedef int (*MYPROC) (HINSTANCE, HINSTANCE ,LPSTR szCmdLine, int iCmdShow);
/*-----------------------------------------------------------------------------------*/
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR szCmdLine, int iCmdShow)
{
	HINSTANCE hinstLib = NULL; 
	MYPROC Windows_Main = NULL; 
	BOOL fFreeResult = FALSE, fRunTimeLinkSuccess = FALSE; 

	if (!DetectFrameWorkNET2())
	{
		MessageBox(NULL,TEXT(MSG_DETECT_FRAMEWORK),TEXT(MSG_WARNING),MB_ICONWARNING);
		return -1;
	}

	if (GetWindowsVersion() < OS_WIN32_WINDOWS_2000)
	{
		MessageBox(NULL,TEXT(MSG_DETECT_2K_OR_MORE),TEXT(MSG_WARNING),MB_ICONWARNING);
		return -1;
	}

	hinstLib = LoadLibrary(TEXT(LIBRARY_TO_LOAD)); 	
	if (hinstLib != NULL) 
	{ 
		Windows_Main = (MYPROC) GetProcAddress(hinstLib,MAIN_FUNCTION); 

		if (NULL != Windows_Main) 
		{
			fRunTimeLinkSuccess = TRUE;
			(Windows_Main)(hInstance,hPrevInstance,szCmdLine, iCmdShow);
		}
		fFreeResult = FreeLibrary(hinstLib); 
	} 

	if (! fRunTimeLinkSuccess) 
	{
		LPVOID lpMsgBuf;
		LPVOID lpDisplayBuf;

		DWORD dw = GetLastError(); 

		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dw,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR) &lpMsgBuf,
			0, NULL );

		lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,(lstrlen((LPCTSTR)lpMsgBuf)+LENGTH_BUFFER_SECURITY)*sizeof(TCHAR)); 
		StringCchPrintf((LPTSTR)lpDisplayBuf,LocalSize(lpDisplayBuf) / sizeof(TCHAR),TEXT(MSG_LOAD_LIBRARIES), dw, lpMsgBuf); 

		MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT(MSG_WARNING), MB_ICONERROR); 

		LocalFree(lpMsgBuf);
		LocalFree(lpDisplayBuf);
		exit(1);
	}
	else exit(0);

    return 0;
}
/*-----------------------------------------------------------------------------------*/
