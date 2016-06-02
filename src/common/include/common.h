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

#ifndef _COPS_MAPEDITOR_COMMON_H_
#define _COPS_MAPEDITOR_COMMON_H_

#include "arch.h"
#include "types.h"
#include "endian.h"
#include "err.h"
#include "assert.h"
#include "log.h"

/*
 *****************************************************
 * Safe delete macros
 ****************************************************
 */

// Delete a pointer and set the pointer to NULL.
template<typename T>
inline void SAFE_DELETE(T*& ptr)
{
    delete ptr;
    ptr = nullptr;
}

// Delete an array and set the pointer to NULL.
template<typename T>
inline void SAFE_DELETE_ARRAY(T*& ptr)
{
    delete[] ptr;
    ptr = nullptr;
}

/*
 *****************************************************
 * Cross-compiling definitions
 ****************************************************
 */

// If using Visual Studio, and C++11 is not implemented
// POSIX-compliant platforms define those functions, so C++11 is not required
#if defined(_MSC_VER) && __cplusplus < 201103L
#define snprintf _snprintf
#endif

// If __TIMESTAMP__ is not defined, create it by merging __DATE__ and __TIME__
#ifndef __TIMESTAMP__
#define __TIMESTAMP__ (__DATE__ " " __TIME__)
#endif

#endif // _COPS_MAPEDITOR_COMMON_H_
