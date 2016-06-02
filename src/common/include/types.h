/*
 * ******* MapEditor - Open Source *******
 * Copyright (C) 2013 Jean-Philippe Boivin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _COPS_MAPEDITOR_TYPES_H_
#define _COPS_MAPEDITOR_TYPES_H_

#include <stddef.h> // Define nullptr, size_t
#include <limits.h> // Define UCHAR_MAX, etc

#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS
#include <stdint.h> // Will define intN_t

/*
 *****************************************************
 * nullptr definition
 ****************************************************
 */

#if !defined(nullptr) // C++11 defines nullptr
#define nullptr NULL
#endif // !defined(nullptr)

#endif // _COPS_MAPEDITOR_TYPES_H
