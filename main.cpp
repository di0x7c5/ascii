/*
    BMP to ASCII Generator - Version 0.2.3
    Copyright (C) 2008/09  Dariusz Iwanoczko aka spark <spark89@wp.pl>

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
#include <stdlib.h>
#include <string.h>

#include "err.h"
#include "bmp.h"
#include "ascii.h"

CBITMAP BITMAP;
CASCII ASCII;

//------------------------------------------------------------------------------
// function:	main
//------------------------------------------------------------------------------
int main(int argc, char** argv)
{
 	//system("@echo OFF");
	fprintf(stderr,"\nascii: %s v. %s Welcome!\n", APPNAME, VERSION);
	
	// Rozgryzamy linie polecen
	if(ASCII.ParseCommandline(argc, argv)) return ERR_PARSECOMMANDLINE;
	// Wczytujemy naglowek pliku BMP
	if(BITMAP.loadheader(ASCII.apFileIn)) return ERR_LOADHEADER;
	// Wczytujemy dane obrazu z pliku BMP
	switch(BITMAP.ret_HitCount())
	{
		case 16: if(BITMAP.load16(ASCII.apFileIn)) return ERR_BITMAPLOAD16;
			break;
		case 24: if(BITMAP.load24(ASCII.apFileIn)) return ERR_BITMAPLOAD24;
			break;
		case 32: if(BITMAP.load32(ASCII.apFileIn)) return ERR_BITMAPLOAD32;
			break;
		default: return ERR_UNKNOWHITCOUNT;
			break;
	};
	// Informacje pomocnicze... jesli chcemy...
	if(ASCII.apPrintFH) BITMAP.printfileheader();
	if(ASCII.apPrintIH) BITMAP.printinfoheader();
	if(ASCII.apPrintD) BITMAP.printdata();
	// Konwerterujemy do ASCII
	if(BITMAP.convert()) return ERR_CONVERT;
	
	// Wszystko poszlo zgodnie z planem... Dziekujemy...
	fprintf(stderr,"\nascii: File '%s' converted successful", ASCII.apFileIn);
	
	if(ASCII.apOutputStreamType==OUT_STD)
		fprintf(stderr,".\n"); else fprintf(stderr," to '%s'\n", ASCII.apFileOut);
	
	fprintf(stderr,"ascii: ASCII Generator Done! Thank You!\n");
	
	return 0;
} // END
