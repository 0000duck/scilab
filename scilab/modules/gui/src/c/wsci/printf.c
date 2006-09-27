/* Allan CORNET */
/* INRIA 2005 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <windows.h>
#include <windowsx.h>
#include <Winuser.h>
#include "wgnuplib.h"
#include "printf.h"
#include "winmain.h"
#include "wcommon.h"

#include "Messages.h"
#include "Warnings.h"
#include "Errors.h"


/*-----------------------------------------------------------------------------------*/
extern int PutString(char *Str);
extern void Xputchar ();
extern int getdiary();
extern void diary_nnl(char *str,int *n);
extern BOOL IsWindowInterface(void);
extern LPTW GetTextWinScilab(void);
/*-----------------------------------------------------------------------------------*/
int MyPutCh (int ch)
{
	char Str[1];
	Str[0]=ch;
	//PutString(Str);
	return TextPutCh (&textwin, (BYTE) ch);
}
/*-----------------------------------------------------------------------------------*/
int MyGetCh (void)
{
	return TextGetCh (&textwin);
}
/*-----------------------------------------------------------------------------------*/
char * MyFGetS (char *str, unsigned int size, FILE * file)
{
	char FAR *p;
	if (isterm (file))
	{
		p = TextGetS (&textwin, str, size);
		if (p != (char FAR *) NULL)
		return str;
		return (char *) NULL;
	}
	return fgets (str, size, file);
}
/*-----------------------------------------------------------------------------------*/
int MyFPutC (int ch, FILE * file)
{
	if (isterm (file))
	{
		MyPutCh ((BYTE) ch);
		TextMessage ();
		return ch;
	}
	return fputc (ch, file);
}
/*-----------------------------------------------------------------------------------*/
int MyFPutS (char *str, FILE * file)
{
	if (isterm (file))
	{
		TextPutS (&textwin, str);
		PutString(str);
		
		TextMessage ();
		return (*str);		/* different from Borland library */
	}
	return fputs (str, file);
}
/*-----------------------------------------------------------------------------------*/
/** synonym for scilab but without the \n **/
void Scistring (char *str)
{
	int i;
	C2F (xscion) (&i);
	if (i == 0)
	fprintf (stdout, "%s", str);
	else
	{
		TextPutS (&textwin, str);
		PutString(str);
		PutString("\n");
		MyPutCh ('\n');
	}
}
/*-----------------------------------------------------------------------------------*/
/*---------------------------------------------------
* the same but no diary record
*---------------------------------------------------*/
void sciprint_nd (char *fmt,...)
{
	int i, count, lstr;
	char buf[MAXPRINTF];
	va_list args;
	va_start (args, fmt);

	/* next three lines added for diary SS */
	count = _vsnprintf (buf,MAXPRINTF-1, fmt, args);
	if (count == -1)
	{
		buf[MAXPRINTF-1]='\0';
	}
	lstr = strlen (buf);

	C2F (xscion) (&i);
	if (i == 0)
	{
		/*count = vfprintf(stdout, fmt, args ); */
		printf ("%s", buf);
	}
	else
	{
		/*count = vsprintf(buf,fmt,args); SS */
		TextPutS (&textwin, buf);
		PutString(buf);
	}
	va_end (args);
	/** return count; **/
}
/*-----------------------------------------------------------------------------------*/
size_t MyFWrite (const void *ptr, size_t size, size_t n, FILE * file)
{
	if (isterm (file))
	{
		int i;
		for (i = 0; i < (int) n; i++)
		TextPutCh (&textwin, ((BYTE *) ptr)[i]);
		TextMessage ();
		return n;
	}
	return fwrite (ptr, size, n, file);
}
/*-----------------------------------------------------------------------------------*/
size_t MyFRead (void *ptr, size_t size, size_t n, FILE * file)
{
	if (isterm (file))
	{
		int i;
		for (i = 0; i < (int) n; i++)
		((BYTE *) ptr)[i] = TextGetChE (&textwin);
		TextMessage ();
		return n;
	}
	return fread (ptr, size, n, file);
}
/*-----------------------------------------------------------------------------------*/
/* I/O Function for scilab : this function are used when Xscilab is on */
/*-----------------------------------------------------------------------------------*/
void Xputchar (char c)
{
	MyPutCh ((int) c);

}
/*-----------------------------------------------------------------------------------*/
void Xputstring (char *str,int n)
{
	int i;
	
	PutString(str);
	for (i = 0; i < n; i++)	Xputchar (str[i]);
}
/*-----------------------------------------------------------------------------------*/
void C2F (xscisncr) (char *str,integer *n,integer dummy)
{
	Xputstring (str, *n);
}
/*-----------------------------------------------------------------------------------*/
void C2F (xscistring) (char *str,int *n,long int dummy)
{
	Xputstring (str, *n);
	Xputstring ("\r\n", 2);
}
/*-----------------------------------------------------------------------------------*/
void C2F (xscimore) (int *n)
{
	int n1, ln;
	*n = 0;
	ln = strlen (MORESTR);
	Xputstring (MORESTR, ln);
	n1 = TextGetCh (&textwin);
	if (n1 == 'n')
	{
		*n = 1;
		Xputstring ("\r\n", 2);
	}
	else
	{
		if (IsWindowInterface())
		{
			#define NOTEXT 0xF0
			int X=0,Y=0;
			int i = 0;
			LPTW lptw=GetTextWinScilab();

			X=lptw->CursorPos.x-strlen(MORESTR);
			Y=lptw->CursorPos.y;
			if (Y>0)
			{
				i=(Y)*lptw->ScreenSize.x;

				_fmemset(lptw->ScreenBuffer + i, ' ', lptw->ScreenSize.x);
				_fmemset(lptw->AttrBuffer + i, NOTEXT,lptw->ScreenSize.x);

				TextGotoXY (lptw, X,Y);
				InvalidateRect (lptw->hWndText, NULL, TRUE);
			}
		}
		
	}
	
	TextMessage ();
}
/*-----------------------------------------------------------------------------------*/
/* I/O Function for C routines : test for xscion */
void Scisncr (char *str)
{
	int i;
	integer lstr;
	C2F (xscion) (&i);
	if (i == 0)
	fprintf (stdout, "%s", str);
	else
	{
		lstr = strlen (str);
		C2F (xscisncr) (str, &lstr, 0L);
	}
}
/*-----------------------------------------------------------------------------------*/
