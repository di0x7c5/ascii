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
#include <stdlib.h>
#include <string.h>

#include "bmp.h"
#include "ascii.h"

extern CASCII ASCII;

//------------------------------------------------------------------------------
// CASCII:    KONSTRUKTOR
//------------------------------------------------------------------------------
CASCII::CASCII()
: apSize(12), apConversionType(CVT_PLAIN), apBackgroundColor(BLACK), apFill('#'),
  apDoubleFill(false), apPrintFH(false), apPrintIH(false), apPrintD(false), apOutputStreamType(OUT_STD)
{
	strcpy(apFont,"Courier New");
	strcpy(apFileOut,"index.html");
}
//------------------------------------------------------------------------------
// CASCII:    DESTRUKTOR
//------------------------------------------------------------------------------
CASCII::~CASCII()
{
	apFill = apSize = 0;

	strcpy(apFont,"");
	strcpy(apFileIn,"");
	strcpy(apFileOut,"");
}
//------------------------------------------------------------------------------
// Funkcja:    color2hex
//------------------------------------------------------------------------------
unsigned int CASCII::color2hex(COLOR var)
{
	switch(var)
	{
		case BLACK:  return 0x000000; break;
        case BROWN:  return 0x000000; break;
		case RED:    return 0xff0000; break;
		case ORANGE: return 0xff7f00; break;
		case YELLOW: return 0xffff00; break;
		case GREEN:  return 0x00ff00; break;
	    case BLUE:   return 0x0000ff; break;
		case PURPLE: return 0xff00ff; break;
		case GREY:   return 0xc0c0c0; break;
		case WHITE:  return 0xffffff; break;
		default:     return 0x000000; break;
	}
}
//------------------------------------------------------------------------------
// Funkcja:	grey2char
//------------------------------------------------------------------------------
unsigned char CASCII::grey2fill(double var)
{
	if(var<16.0)   return '#'; else // #$o+*:.
	if(var<32.0)   return '#'; else // #Eji:,.
	if(var<48.0)   return 'E'; else // .,'"*:;!/=?$&@%#
	if(var<64.0)   return 'E'; else
	if(var<80.0)   return 'j'; else
	if(var<96.0)   return 'j'; else
	if(var<112.0)  return 'i'; else
	if(var<128.0)  return 'i'; else
	if(var<144.0)  return ':'; else
	if(var<160.0)  return ':'; else
	if(var<176.0)  return ','; else
	if(var<192.0)  return ','; else
	if(var<208.0)  return '.'; else
	if(var<224.0)  return '.'; else
	if(var<240.0)  return ' '; else
	if(var<=255.0) return ' '; else
		
	return ' ';
}
//------------------------------------------------------------------------------
// Funkcja:	str2uint
//------------------------------------------------------------------------------
unsigned int CASCII::str2uint(char *var)
{
	unsigned int result = 0;
	while(*var!=0)
	{
		result *= 10;
		result += ((unsigned int)*var++)-48;
	}
	return result;
}
//------------------------------------------------------------------------------
// Funkcja:	ParseCommandline
//------------------------------------------------------------------------------
bool CASCII::ParseCommandline(int argc, char *argv[])
{
 	if(argc<2) {
		printf("\nasci: Need to specify a name of BMP file!\nasci: Use --help or -h to see a list of options.\n");
		return true;
	}
	
	for(int i=1; i<argc; i++)
	{
		if( !strcmp(argv[i], "-h") || !strcmp(argv[i], "--help") ) {
			printf( "\nWywolanie: ascii <name.bmp> [OPTION]...\n"
					"Przetwarza bitmape <name.bmp> do postaci ASCII ART w pliku HTML.\n\n"
					"  -a  --size                 wielkosc pojedynczego znaku w px\n"
					"  -f  --fill                 znak ktorym rysowany jest obraz w HTML\n"
					"  -o  --out                  nazwa pliku wyjsciowego\n"
					"  -c  --convert              typ konwersji, mo¿liwe opcje:\n"
					"                             HTML, ASCII, BOTH\n"
					"  -bc --bgcolor              kolor tla, mozliwe opcje:\n"
					"                             BLACK, BROWN, RED, ORANGE, YELLOW,\n"
					"                             GREEN, BLUE, PURPLE, GREY, WHITE\n\n"
					"  -fh --fileheader           drukuje pola naglowka FILEHEADER pliku BMP\n"
					"  -ih --infoheader           drukuje pola naglowka INFOHEADER pliku BMP\n"
					"  -da --data                 drukuje dane pliku BMP\n\n"
					"  -df --doublefill           podwojne wypelnienie znakiem\n\n"
					"  -h  --help                 wyswietla ten tekst\n"
					"  -v  --version              wyswietla informacje o programie\n\n"
					"Domyslnie obraz generowany jest wypelnieniem '#'. Kolor tla w pliku\n"
					"jest domyslnie kolor czarny. Wielkosc wypelnienia 12 pixeli. Nazwa\n"
					"pliku wyjsciowego to \"index.html\". Domyslny typ konwersji to HTML.\n\n"
                    "Report bugs to di0x7c5@gmail.com\n");
			return true;
		} else
		if( !strcmp(argv[i], "-v") || !strcmp(argv[i], "--version") ) {
			printf("\n###############################################################################\n"
			"###############################################################################\n"
			"###############################################################################\n"
			"###############################################################################\n"
			"###############################################################################\n"
			"###############################################################################\n"
			"###############################################################################\n"
			"###############################################################################\n"
			"###############################################################################\n"
			"###############################################################################\n"
			"###############################################################################\n"
			"###############################################################################\n"
			"###############################################################################\n"
			"###############################################################################\n"
			"###############################################################################\n"
			"###############################################################################\n"
			"###############################################################################\n"
			"###############################################################################\n"
			"###############################################################################\n"
			"###############################################################################\n"
			"#######  #####    ####    ####    ####    ############    ###      ##  ###  ###\n"
			"######    ###  ##  ##  ##  ####  ######  ############  ##  ##  ######  ###  ###\n"
			"#####  ##  ##  ######  ##  ####  ######  ############  ##  ##  ######   ##  ###\n"
			"#####  ##  ###  #####  ########  ######  ############  ######  ######    #  ###\n"
			"#####  ##  ####  ####  ########  ######  ############  ######     ###  #    ###\n"
			"#####      #####  ###  ########  ######  ############  #   ##  ######  ##   ###\n"
			"#####  ##  ######  ##  ##  ####  ######  ############  ##  ##  ######  ###  ###\n"
			"#####  ##  ##  ##  ##  ##  ####  ######  ############  ##  ##  ######  ###  ###\n"
			"#####  ##  ###    ####    ####    ####    ############     ##      ##  ###  ###\n"
			"###############################################################################\n"
			"###############################################################################\n"
			"###############################################################################\n"
			"#####                                                                       ###\n"
			"##########################################################################  ###\n"
			"####### COPYRIGHT (C) 2oo8/~ By Dariusz Iwanoczko aka. di0x7c5 ###########  ###\n"
			"####### VERSION 0.2.3 ####################################################  ###\n"
			"##########################################################################  ###\n"
			"##########################################################################  ###\n"
			"###############################################################################\n"
			"###############################################################################\n"
			"###############################################################################\n"
			"###############################################################################\n"
			"###############################################################################\n"
			"###############################################################################\n"
			"###############################################################################\n"
			"### E-Mail: di0x7c5@gmail.com         #########################################\n"
			"### WWW: http://blackisthecolor.pl/   #########################################\n"
			"###############################################################################\n"
			"###############################################################################\n");
			return true;
		} else
		if( !strcmp(argv[i], "-df") || !strcmp(argv[i], "--doublefill") ) {
			apDoubleFill = true;
		} else
		
		if( !strcmp(argv[i], "-f") || !strcmp(argv[i], "--fill") ) {
			if ( (i+1)==argc ) {
				fprintf(stderr,"\n Need to specify a fill!\n");
				return true;
			} else {
				apFill = (unsigned char)*argv[++i];
			}
		} else
		if( !strcmp(argv[i], "-o") || !strcmp(argv[i], "--out") )
		{
			if( !((i+1)==argc) && !(*(argv[(i+1)])=='-') )
			{
				strcpy(apFileOut,argv[++i]);
				
				char* dotpos = strrchr(apFileOut,'.');
				if( !(dotpos && !strcmp(dotpos,".html")) )
					strcat(apFileOut,".html");
			} else
				strcpy(apFileOut, "index.html");

			apOutputStreamType = OUT_FILE;
			apConversionType = CVT_HTML;
		} else
		if( !strcmp(argv[i], "-s") || !strcmp(argv[i], "--size") ) {
			if ( (i+1)==argc ) {
				fprintf(stderr,"\n Need to specify a size!\n");
				return true;
			} else {
				apSize = str2uint(argv[++i]);
			}
		} else
		if( !strcmp(argv[i], "-c") || !strcmp(argv[i], "--convert") ) {
			if ( (++i)==argc ) {
				fprintf(stderr,"\n Need to specify a convertion type!\n");
				return true;
			} else { 
				if ( !strcmp(argv[i], "html")  || !strcmp(argv[i], "HTML") )
					apConversionType = CVT_HTML;
				else
				if ( !strcmp(argv[i], "ascii")  || !strcmp(argv[i], "ASCII") )
					apConversionType = CVT_ASCII;
				else
				if ( !strcmp(argv[i], "both")  || !strcmp(argv[i], "BOTH") )
					apConversionType = CVT_BOTH;
				else {
					fprintf(stderr,"\n Unknow convertion type: %s!\n", argv[i]);
					return true;
				}
				apOutputStreamType = OUT_FILE;
			}
		} else
		if( !strcmp(argv[i], "-bc") || !strcmp(argv[i], "--bgcolor") ) {
			if ( (++i)==argc ) {
				fprintf(stderr,"\n Need to specify a background color!\n");
				return true;
			} else {
				if ( !strcmp(argv[i], "black") || !strcmp(argv[i], "BLACK") )
				    apBackgroundColor = BLACK;
				else
				if ( !strcmp(argv[i], "brown") || !strcmp(argv[i], "BROWN") )
				    apBackgroundColor = BROWN;
				else
				if ( !strcmp(argv[i], "red") || !strcmp(argv[i], "RED") )
				    apBackgroundColor = RED;
				else
				if ( !strcmp(argv[i], "orange") || !strcmp(argv[i], "ORANGE") )
				    apBackgroundColor = ORANGE;
				else
				if ( !strcmp(argv[i], "yellow") || !strcmp(argv[i], "YELLOW") )
				    apBackgroundColor = YELLOW;
				else
				if ( !strcmp(argv[i], "green") || !strcmp(argv[i], "GREEN") )
				    apBackgroundColor = GREEN;
				else
				if ( !strcmp(argv[i], "blue") || !strcmp(argv[i], "BLUE") )
				    apBackgroundColor = BLUE;
				else
				if ( !strcmp(argv[i], "purple") || !strcmp(argv[i], "PURPLE") )
				    apBackgroundColor = PURPLE;
				else
				if ( !strcmp(argv[i], "grey") || !strcmp(argv[i], "GREY") )
				    apBackgroundColor = GREY;
				else
				if ( !strcmp(argv[i], "white") || !strcmp(argv[i], "WHITE") )
				    apBackgroundColor = WHITE;
				else {
					fprintf(stderr,"\n Unknow color: %s!\n", argv[i]);
					return true;
				}
			}
		} else
		if( !strcmp(argv[i], "-fh") || !strcmp(argv[i], "--fileheader") ) {
			apPrintFH = true;
		} else
		if( !strcmp(argv[i], "-ih") || !strcmp(argv[i], "--infoheader") ) {
			apPrintIH = true;
		} else
		if( !strcmp(argv[i], "-da") || !strcmp(argv[i], "--data") ) {
			apPrintD = true;
		} else
		if (i==1 && *argv[i]!='-') {
			strcpy(apFileIn,argv[1]);
		} else {
			fprintf(stderr,"\n Unknown option '%s'. Use --help or -h to see a list of options.\n", argv[i]);
			return true;
		}
	}
	
	// jesli zapisujemy dane do pliku i mamy konwersje ASCII to kolor tla bialu
	if(apOutputStreamType==OUT_FILE && apConversionType==CVT_ASCII)
		apBackgroundColor = WHITE;
	// jesli wyjsciem jest konsola to tylko w konwersji PLAIN
	if(apOutputStreamType==OUT_STD)
		apConversionType = CVT_PLAIN;
	
	return false;
} // END
