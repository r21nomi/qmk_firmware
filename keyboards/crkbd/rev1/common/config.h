/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define PRODUCT         Corne Keyboard Rev.1 (Split Common)

#define USE_SERIAL
#define SOFT_SERIAL_PIN D2

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_SPLIT { 27, 27 }
#endif

#define DIODE_DIRECTION COL2ROW
