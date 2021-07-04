/*
    BMP to ASCII Generator - Version 0.2.3
    Copyright (C) 2008/09  Dariusz Iwanoczko aka di0x7c5 <di0x7c5@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>

#include "err.h"
#include "bmp.h"
#include "ascii.h"

extern CASCII ASCII;
extern CBITMAP BITMAP;

//------------------------------------------------------------------------------
// CBITMAP:	loadheader
//------------------------------------------------------------------------------
bool CBITMAP::loadheader(char* path)
{
 	// otworzenie binarnego strumienia danych do bitmapy
	FILE* BMPFILE = fopen(path, "rb");
	if(!BMPFILE) {
		fprintf(stderr, "\nascii: Can't find file - '%s'!\n", path);
		return true;
	} else
		fprintf(stderr,"\nascii: File '%s' opened successful.\n", path);

	// wczytanie naglowka
	fread(&bfType, 54, 1, BMPFILE);

	// uwagi, uwagi, uwagi ...
	if( bfType != BMPSIGNATURE ) {
		fprintf(stderr, "\nascii: File '%s' is not a BMP format!\n", ASCII.apFileIn);
		fclose(BMPFILE);
		return true;
	} else
	if( biSize != WINDOWS_V3_BMP) {
		fprintf(stderr, "\nascii: BMP File is not in Windows V3 Format!\n");
		fclose(BMPFILE);
		return true;
	} else
	if( biHitCount != _TRUECOLOR_ALPHA && biHitCount != _TRUECOLOR) {
		fprintf(stderr, "\nascii: BMP File is not in 24 (True Color) or 32 bits (True Color Alpha) mode!\n");
		fclose(BMPFILE);
		return true;
	} else
	if( biPlanes != 1) {
		fprintf(stderr, "\nascii: BMP File have more than 1 places!\n");
		fclose(BMPFILE);
		return true;
	}
	if( biCompression != _BI_RGB) {
		fprintf(stderr, "\nascii: BMP Format Compression invalid!\n");
		fclose(BMPFILE);
		return true;
	} else
		fprintf(stderr,"ascii: BMP Format is Correct.\n");

	bdBytesPerPixel = biHitCount/8;				// Liczba bajtow na pixel
	bdCanvasSize = biWidth*biHeight;			// Wielkosc plotna (ilosc pixeli)

	// obliczenie liczby bitow wypelnienia do iloczynu czworki
	while( ((biWidth*bdBytesPerPixel) + bdComplement)%4 != 0 ) bdComplement++;

	return false;	
}
//------------------------------------------------------------------------------
// CBITMAP:	load16
//------------------------------------------------------------------------------
bool CBITMAP::load16(char* path)
{
	fprintf(stderr,"ascii: Starting load BMP to memmory using 'load16'.\n");
//?
	bdDataSize = bdCanvasSize*3;	// Liczba bajtow potrzebna do zaladowania bitmapy
//?
 	// otworzenie binarnego strumienia danych do bitmapy
	FILE* BMPFILE = fopen(path, "rb");
	if(!BMPFILE) {
		fprintf(stderr, "\nascii: Something bad is happend the BMP File, sorry...\n\n");
		return true;
	}

	bdData = new unsigned char [bdDataSize];
	if (!bdData) return true;

	// ustawienie pozycji w pliku na offset danych
	fseek(BMPFILE, bfOffBits, SEEK_SET);
	// odczyt pixeli i zapis do tablicy
/*
	for(unsigned int i=0; i<biHeight; i++)
	{
		fread(bdData+(3*i*biWidth), (3*biWidth), 1, BMPFILE);
		fseek(BMPFILE, ftell(BMPFILE) + bdComplement, SEEK_SET);
	}
*/

	// zamkniecie pliku BMP, nadanie wskaznikowi wartosc NULL
	fclose(BMPFILE);
	BMPFILE = NULL;

	fprintf(stderr,"ascii: BMP Load Successful!\n");

	// Tabela Pixeli formatu HTML
/*
	PixTab = new unsigned int [bdCanvasSize]; if (!PixTab) return ERR_MEMLOCATION;
	for(unsigned int i=0; i<bdCanvasSize; i++) // BGR
		PixTab[bdCanvasSize-i-1] = bdData[i*3] + bdData[(i*3)+1]*0x100 + bdData[(i*3)+2]*0x10000;

	// Tabela Szarosci
	GreyTab = new double [bdCanvasSize]; if (!GreyTab) return ERR_MEMLOCATION;
	for(unsigned int i=0; i<bdCanvasSize; i++) // Y = 0.299*R + 0.587*G + 0.114*B
		GreyTab[bdCanvasSize-i-1] = (0.114*bdData[(i*3)])+(0.587*bdData[(i*3)+1])+(0.299*bdData[(i*3)+2]);
*/
	return false;
}
//------------------------------------------------------------------------------
// CBITMAP:	load24
//------------------------------------------------------------------------------
bool CBITMAP::load24(char* path)
{
	fprintf(stderr,"ascii: Starting load BMP to memmory using 'load24'.\n");

	bdDataSize = bdCanvasSize*3;	// Liczba bajtow potrzebna do zaladowania bitmapy

 	// otworzenie binarnego strumienia danych do bitmapy
	FILE* BMPFILE = fopen(path, "rb");
	if(!BMPFILE) {
		fprintf(stderr, "\nascii: Something bad is happend the BMP File, sorry...\n\n");
		return true;	
	}

	bdData = new unsigned char [bdDataSize];
	if (!bdData) return true;

	// ustawienie pozycji w pliku na offset danych
	fseek(BMPFILE, bfOffBits, SEEK_SET);
	// odczyt pixeli i zapis do tablicy
	for(unsigned int i=0; i<biHeight; i++)
	{
		fread(bdData+(3*i*biWidth), (3*biWidth), 1, BMPFILE);
		fseek(BMPFILE, ftell(BMPFILE) + bdComplement, SEEK_SET);
	}

	// zamkniecie pliku BMP, nadanie wskaznikowi wartosc NULL
	fclose(BMPFILE);
	BMPFILE = NULL;

	fprintf(stderr,"ascii: BMP Load Successful!\n");

	// Tabela Pixeli formatu HTML
	PixTab = new unsigned int [bdCanvasSize]; if (!PixTab) return ERR_MEMLOCATION;
	for(unsigned int i=0; i<bdCanvasSize; i++) // BGR
		PixTab[bdCanvasSize-i-1] = bdData[i*3] + bdData[(i*3)+1]*0x100 + bdData[(i*3)+2]*0x10000;

	// Tabela Szarosci
	GreyTab = new double [bdCanvasSize]; if (!GreyTab) return ERR_MEMLOCATION;
	for(unsigned int i=0; i<bdCanvasSize; i++) // Y = 0.299*R + 0.587*G + 0.114*B
		GreyTab[bdCanvasSize-i-1] = (0.114*bdData[(i*3)])+(0.587*bdData[(i*3)+1])+(0.299*bdData[(i*3)+2]);

	return false;
}
//------------------------------------------------------------------------------
// CBITMAP:	load32
//------------------------------------------------------------------------------
bool CBITMAP::load32(char* path)
{
	fprintf(stderr,"ascii: Starting Load BMP to Memmory Using 'load32'.\n");

	bdDataSize = bdCanvasSize*3;	// Liczba bajtow potrzebna do zaladowania bitmapy

 	// otworzenie binarnego strumienia danych do bitmapy
	FILE* BMPFILE = fopen(path, "rb");
	if(!BMPFILE) {
		fprintf(stderr, "\nascii: Something bad is happend the BMP File, sorry...\n\n");
		return true;
	}

	bdData = new unsigned char [bdDataSize];
	if (!bdData) return true;

	// ustawienie pozycji w pliku na offset danych
	fseek(BMPFILE, bfOffBits, SEEK_SET);
	// odczyt pixeli i zapis do tablicy
	for(unsigned int i=0; i<biHeight; i++)
	{
		for(unsigned int j=0; j<biWidth; j++)
		{
			fread(bdData+(3*biWidth*i)+(3*j), 3, 1, BMPFILE);
			fseek(BMPFILE, 1, SEEK_CUR);
		}
		fseek(BMPFILE, ftell(BMPFILE) + bdComplement, SEEK_SET);
	}

	// zamkniecie pliku BMP, nadanie wskaznikowi wartosc NULL
	fclose(BMPFILE);
	BMPFILE = NULL;

	fprintf(stderr,"ascii: BMP Load Successful!\n");

	// Tabela Pixeli formatu HTML
	PixTab = new unsigned int [bdCanvasSize]; if (!PixTab) return ERR_MEMLOCATION;
	for(unsigned int i=0; i<bdCanvasSize; i++) // BGR
		PixTab[bdCanvasSize-i-1] = bdData[i*3] + bdData[(i*3)+1]*0x100 + bdData[(i*3)+2]*0x10000;

	// Tabela Szarosci
	GreyTab = new double [bdCanvasSize]; if (!GreyTab) return ERR_MEMLOCATION;
	for(unsigned int i=0; i<bdCanvasSize; i++) // Y = 0.299*R + 0.587*G + 0.114*B
		GreyTab[bdCanvasSize-i-1] = (0.114*bdData[(i*3)])+(0.587*bdData[(i*3)+1])+(0.299*bdData[(i*3)+2]);

	return false;
}
//------------------------------------------------------------------------------
// CBITMAP:	printfileheader
//------------------------------------------------------------------------------
void CBITMAP::printfileheader(void)
{
	fprintf(stderr,"\nascii: FILEHEADER:\n"
          "ascii: --------------------------------\n"
          "ascii:  bfReserved0: %hd \n"
          "ascii:  bfType: %hd \n"
          "ascii:  bfSize: %d \n"
          "ascii:  bfReserved1: %hd \n"
          "ascii:  bfReserved2: %hd \n"
          "ascii:  bfOffBits: 0x%x \n"
          "ascii: --------------------------------\n\n", bfReserved0, bfType, bfSize, bfReserved1, bfReserved2, bfOffBits);
}
//------------------------------------------------------------------------------
// CBITMAP:	printfileheader
//------------------------------------------------------------------------------
void CBITMAP::printinfoheader(void)
{
	fprintf(stderr,"\nascii: INFOHEADER:\n"
		   "ascii: --------------------------------\n"
		   "ascii:  biSize: %d\n"
		   "ascii:  biWidth: %d\n"
		   "ascii:  biHeight: %d\n"
		   "ascii:  biPlanes: %hd\n"
		   "ascii:  biHitCount: %hd\n"
		   "ascii:  biCompression: %d\n"
		   "ascii:  biSizeImage: %d\n"
		   "ascii:  biXPelsPerMeter: %d\n"
		   "ascii:  biYPelsPerMeter: %d\n"
		   "ascii:  biClrUsed: %d\n"
		   "ascii:  biClrImportant %d\n"
		   "ascii:  biReserved: %hd\n"
		   "ascii: --------------------------------\n\n", biSize, biWidth, biHeight, biPlanes, biHitCount, biCompression, biSizeImage, biXPelsPerMeter, biYPelsPerMeter, biClrUsed, (int)biClrImportant, (int)biClrRotation, biReserved);
}
//------------------------------------------------------------------------------
// CBITMAP:	printdata
//------------------------------------------------------------------------------
void CBITMAP::printdata(void)
{
	fprintf(stderr,"\nascii: DATA:\n"
	       "ascii: --------------------------------\n"
	       "ascii:  bdBytesPerPixel: %hd\n"
	       "ascii:  bdCanvasSize: %u\n"
	       "ascii:  bdDataSize: %u\n"
	       "ascii:  bdComplement: %u\n"
		   "ascii: --------------------------------\n", bdBytesPerPixel, bdCanvasSize, bdDataSize, bdComplement);

	for(unsigned int i=0; i<bdDataSize; i++)
	{
		fprintf(stderr," %02x", bdData[i]);
		if((i+1)%(biWidth*3)==0)
		    printf("\n");
	}

	fprintf(stderr,"\nascii: --------------------------------\n\n");
}
//------------------------------------------------------------------------------
// CBITMAP:	conplain()
//------------------------------------------------------------------------------
void CBITMAP::conplain(void)
{
	fprintf(stderr,"ascii: Starting Convert using PLAIN TEXT Convert Type.\n\n");
	
	for(unsigned int i=0; i<bdCanvasSize; i++)
	{
		fprintf(ASCII.apOutputStream, "%c", ASCII.grey2fill(GreyTab[i]));
		if(ASCII.apDoubleFill) fprintf(ASCII.apOutputStream, "%c", ASCII.grey2fill(GreyTab[i]));
		if(i!=0 && (i+1)%BITMAP.biWidth==0) fprintf(ASCII.apOutputStream, "\n");
	}
}
//------------------------------------------------------------------------------
// CBITMAP:	conhtml()
//------------------------------------------------------------------------------
void CBITMAP::conhtml(void)
{
	fprintf(stderr,"ascii: Starting Convert using HTML Convert Type.\n");
	
	for(unsigned int i=0; i<bdCanvasSize; i++)
	{
		fprintf(ASCII.apOutputStream, "<font color=#%06x>%c", PixTab[i], ASCII.apFill);
		if(ASCII.apDoubleFill) fprintf(ASCII.apOutputStream, "%c", ASCII.apFill);
		fprintf(ASCII.apOutputStream, "</font>");
		if(i!=0 && (i+1)%BITMAP.biWidth==0) fprintf(ASCII.apOutputStream, "<br>");
	}
}
//------------------------------------------------------------------------------
// CBITMAP:	conascii()
//------------------------------------------------------------------------------
void CBITMAP::conascii(void)
{
	fprintf(stderr,"ascii: Starting Convert using HTML ASCII Convert Type.\n");
	
	for(unsigned int i=0; i<bdCanvasSize; i++)
	{
		if(ASCII.grey2fill(GreyTab[i])==' ')
			fprintf(ASCII.apOutputStream, "&nbsp;");
		else
			fprintf(ASCII.apOutputStream, "%c", ASCII.grey2fill(GreyTab[i]));
		if(ASCII.apDoubleFill==true)
		    if(ASCII.grey2fill(GreyTab[i])==' ')
				fprintf(ASCII.apOutputStream, "&nbsp;");
			else
				fprintf(ASCII.apOutputStream, "%c", ASCII.grey2fill(GreyTab[i]) );
		if(i!=0 && (i+1)%BITMAP.biWidth==0) fprintf(ASCII.apOutputStream, "<br>");
	}
}
//------------------------------------------------------------------------------
// CBITMAP:	conboth()
//------------------------------------------------------------------------------
void CBITMAP::conboth(void)
{
	fprintf(stderr,"ascii: Starting Convert using HTML BOTH Convert Type.\n");
	
	for(unsigned int i=0; i<bdCanvasSize; i++)
	{
		if(ASCII.grey2fill(GreyTab[i])==' ')
			fprintf(ASCII.apOutputStream, "<font>&nbsp;");
		else
			fprintf(ASCII.apOutputStream, "<font color=\"#%06x\">%c", PixTab[i], ASCII.grey2fill(GreyTab[i]));
		if(ASCII.apDoubleFill==true)
		    if(ASCII.grey2fill(GreyTab[i])==' ')
				fprintf(ASCII.apOutputStream, "&nbsp;");
			else
				fprintf(ASCII.apOutputStream, "%c", ASCII.grey2fill(GreyTab[i]) );
		fprintf(ASCII.apOutputStream, "</font>");
		if(i!=0 && (i+1)%BITMAP.biWidth==0)
			fprintf(ASCII.apOutputStream, "<br>");
	}
}
//------------------------------------------------------------------------------
/*						PRZYKLADOWY PLIK HTML:
	<html>
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
		<link rel="Stylesheet" href="XYZ.css">
		<title> [NAGLOWEK] </title>

		<style type="text/css">
			body { font-size: %dpx }
		</style>
	</head>
	<body bgcolor="#000000">
	<center>
	<font face="XYZ">

	!!! OBRAZ !!!

	</font>
	</center>
	</body>
	</html>
*/
//------------------------------------------------------------------------------
// CBITMAP:	convert()
//------------------------------------------------------------------------------
bool CBITMAP::convert()
{
	{	// usuwamy efekt lustra
		unsigned int ClrPixBuf;

		for(unsigned int i=0; i<BITMAP.biHeight; i++)
		{
			for(unsigned int j=0; j<BITMAP.biWidth/2; j++)
			{
				ClrPixBuf = PixTab[(BITMAP.biWidth*i)+j];
				PixTab[(BITMAP.biWidth*i)+j] = PixTab[(BITMAP.biWidth*i)+BITMAP.biWidth-j-1];
				PixTab[(BITMAP.biWidth*i)+BITMAP.biWidth-j-1] = ClrPixBuf;
				
				ClrPixBuf = (int)GreyTab[(BITMAP.biWidth*i)+j];
				GreyTab[(BITMAP.biWidth*i)+j] = GreyTab[(BITMAP.biWidth*i)+BITMAP.biWidth-j-1];
				GreyTab[(BITMAP.biWidth*i)+BITMAP.biWidth-j-1] = ClrPixBuf;
			}
		}
	}

	// ustawiamy strumien wyjsiowy na podstawie zmiennej apOutputStreamType
	if( ASCII.apOutputStreamType == OUT_STD ) {
		ASCII.apOutputStream = stdout;	
	} else {
		ASCII.apOutputStream = fopen(ASCII.apFileOut, "wt");
		if(!ASCII.apOutputStream) return true;
	}

	// NAGLOWEK HTML sekcja HEAD
	if( ASCII.apOutputStreamType == OUT_FILE )
		fprintf(ASCII.apOutputStream, "<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"><title>%s - %s</title><style type=\"text/css\">body { font-size: %dpx }</style></head><body bgcolor=\"#%06x\"><center><font face=\"%s\">", APPNAME, VERSION, ASCII.apSize, ASCII.color2hex(ASCII.apBackgroundColor), ASCII.apFont);

	// Jesli korzystamy z podwojnego wypelnienia, informujemy o tym uzytkownika...
	if(ASCII.apDoubleFill) fprintf(stderr,"ascii: Double fill convert is set.\n");

	// Typy konwersji na podstawie zmiennej apConversionType
	switch(ASCII.apConversionType)
	{
		case CVT_PLAIN:	conplain();
			break;
		case CVT_HTML:	conhtml();
			break;
		case CVT_ASCII:	conascii();
			break;
		case CVT_BOTH:	conboth();
			break;
		default: fprintf(stderr,"\nascii: Unknow conversion type in \"convertbmp()\" function!\n\n");
			return true;
			break;
	};
		
	// Tagi Zamykajace
	if(ASCII.apOutputStreamType==OUT_FILE) {
		fprintf(ASCII.apOutputStream, "</font></center></body></html>");
		fclose(ASCII.apOutputStream);
		ASCII.apOutputStream = NULL;
	}

	return false;
} // END
