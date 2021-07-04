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

#ifndef _BMP_H_
#define _BMP_H_

#define BMPSIGNATURE 0x4d42	// MB
#define WINDOWS_V3_BMP 0x28	// 40

// PALETA KOLORÓW
#define _2COLORS 1			// jeden bajt okresla 8 punktow
#define _16COLORS 4			// jeden bajt okresla 2 punkty
#define _256COLORS 8		// jeden bajt okresla 1 punkt
#define _TRUECOLOR 24		// jeden punkt opisuja 3 bajty
#define _TRUECOLOR_ALPHA 32	// jeden punkt opisuja 4 bajty

// TRYBY KOMPRESJI
#define _BI_RGB 0			// KOMPRESJA RGB
#define _BI_RLE8 1			// KOMPRESJA RLE 8
#define _BI_RLE4 2			// KOMPRESJA RLE 4
#define _BI_BITFIELDS 3		// KOMPRESJA BITFIELDS
#define _BI_JPEG 4			// KOMPRESJA JPEG
#define _BI_PNG 5			// KOMPRESJA PNG

class CBITMAP
{
	private:
		// BITMAPFILEHEADER
		short bfReserved0;			// Zarezerwowane, zaleca sie nadanie wartosci 0
		short bfType;				// Identyfikator BMP, zazwyczaj litery "BM"
		int bfSize;					// Calkowita wielkosc pliku
		short bfReserved1;			// Zarezerwowane, zaleca sie nadanie wartosci 0
		short bfReserved2;			// Zarezerwowane, zaleca sie nadanie wartosci 0
		int bfOffBits;				// Pozycja (offset) danych pliku
									// ------------------------------------------------
		// BITMAPINFOHEADER			// ------------------------------------------------
		int biSize;					// Wielkoœæ nag³ówka informacyjnego. D³ugoœæ st¹d do koñca nag³ówka – 40, czasem mniej
		int biWidth;				// Szerokoœæ obrazu w pixelach
		int biHeight;				// Wysokoœæ obrazu w pixelach
		short biPlanes;				// Liczba warstw kolorów, zwykle 1
		short biHitCount;			// Liczba bitów na piksel
		int biCompression;			// Algorytm kompresji
		int biSizeImage;			// Rozmiar samego rysunku
		int biXPelsPerMeter;		// Rozdzielczoœæ pozioma
		int biYPelsPerMeter;		// Rozdzielczoœæ pionowa
		int biClrUsed;				// Liczba kolorów w palecie
		char biClrImportant;		// Liczba wa¿nych kolorów w palecie (gdy 0 to wszystkie s¹ wa¿ne)
		char biClrRotation;			// Flaga sygnalizuj¹ca czy ma nastêpowaæ rotacja palety (domyœlnie 0-brak rotacji)
		short biReserved;			// Zarezerwowane, zaleca sie nadanie wartosci 0
									// ------------------------------------------------
		// BITMAPDATA				// ------------------------------------------------
		short bdBytesPerPixel;		// Liczba bajtow na pixel
		unsigned int bdCanvasSize;	// Wielkosc plotna (ilosc pixeli)
		unsigned int bdDataSize;    // Liczba bajtow potrzebna do zaladowania bitmapy
		unsigned char *bdData;		// Wskaznik na tablice danych
		unsigned char bdComplement; // Liczba bajtow uzupelnien do 4
									// ------------------------------------------------		
		// ANOTHER					// ------------------------------------------------
		unsigned int* PixTab;		// Tabela Pixeli formatu HTML
		double* GreyTab;			// Tabela Szarosci

	public:
		CBITMAP() : bdBytesPerPixel(0), bdCanvasSize(0), bdDataSize(0), bdData(NULL), bdComplement(0), PixTab(NULL), GreyTab(NULL) {}
		~CBITMAP() { delete [] bdData; delete [] GreyTab; delete [] PixTab; }
										// ------------------------------------------------
		bool loadheader(char* path);	// Wczytanie naglowka bitmapy
		//bool load1(char* path);		// Wczytanie bitmapy 1-bitowej
		//bool load4(char* path);		// Wczytanie bitmapy 4-bitowej
		//bool load8(char* path);		// Wczytanie bitmapy 8-bitowej
		bool load16(char* path);		// Wczytanie bitmapy 16-bitowej
		bool load24(char* path);		// Wczytanie bitmapy 24-bitowej
 		bool load32(char* path);		// Wczytanie bitmapy 32-bitowej
										// ------------------------------------------------
		void printfileheader(void);		// Wydrukuje naglowek Fileheader
		void printinfoheader(void);		// Wydrukuje naglowek InfoHeader
		void printdata(void);			// Wydrukuje dane obrazu
										// ------------------------------------------------
		bool convert(void);				// Konwersja
										// ------------------------------------------------
		void conplain(void);			// Konwersja PLAIN TEXT
		void conhtml(void);				// Konwersja HTML
		void conascii(void);			// Konwersja HTML ASCII
		void conboth(void);				// Konwersja HTML BOTH
										// ------------------------------------------------
		short ret_HitCount(void) { return biHitCount; }
};										// ------------------------------------------------

#endif // _BMP_H_
