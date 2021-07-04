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

#ifndef _ASCII_H_
#define _ASCII_H_

#define APPNAME "ASCII Generator"
#define VERSION "0.2.3"
#define DEMOMAXPX 100

enum COLOR { BLACK, BROWN, RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, GREY, WHITE };
enum OUTPUT { OUT_STD, OUT_FILE };
enum CONVERSIONTYPE { CVT_PLAIN , CVT_HTML, CVT_ASCII, CVT_BOTH };

class CASCII
{
	private:
		// (...)
	public:													// ----------------------------------------
		char apFileIn[64];									// Nazwa pliku BMP
    	char apFileOut[64];									// Nazwa pliku HTML
    	char apFont[32];									// Typ Czcionki
    	unsigned char apFill;								// Znak ktorym wypelniamy bitmape
    	unsigned int apSize;								// Wielkosc wydruku w pixelach
    	bool apDoubleFill;         							// Podwojne wypelnienie
		bool apPrintFH;										// Wydruk File Header
		bool apPrintIH;										// Wydruk Info Header
		bool apPrintD;										// Wydruk Data
		COLOR apBackgroundColor;							// Kolor Tla
		FILE* apOutputStream;								// Wskaznik na Docelowy Strumien
		OUTPUT apOutputStreamType;							// Typ Docelowego Strumienia Wyjscia
		CONVERSIONTYPE apConversionType;					// Tryb Konwersji
															// ----------------------------------------
		CASCII();											// Konstruktor
		~CASCII();											// Destruktor
															// ----------------------------------------
		bool ParseCommandline(int argc, char** argv); 	 	// Analiza Wiersza Polecen
		double ConvertSize(double const var, char* cur);    // Zamiana jednostek rozmiaru
		unsigned int color2hex(COLOR var);					// Zwraca wartosc HEX na podstawie COLOR
		unsigned char grey2fill(double var);				// Zwraca znak wypelnienia na podstawie VAR
		unsigned int str2uint(char *var);  	 				// Zamiana lancucha znakow na liczbe
};															// ----------------------------------------

#endif // _ASCII_H_
