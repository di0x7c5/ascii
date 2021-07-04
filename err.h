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

#ifndef _ERR_H_
#define _ERR_H_

#define ERR_NOERR 0
#define ERR_PARSECOMMANDLINE 1
#define ERR_BITMAPLOAD1 2
#define ERR_BITMAPLOAD4 3
#define ERR_BITMAPLOAD8 4
#define ERR_BITMAPLOAD16 5
#define ERR_BITMAPLOAD24 6
#define ERR_BITMAPLOAD32 7
#define ERR_MEMLOCATION 8
#define ERR_LOADHEADER 9
#define ERR_CONVERT 10
#define ERR_UNKNOWHITCOUNT 13
#define ERR_UNKNOWEXENSION 14

#endif // _ERR_H_
