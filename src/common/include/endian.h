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

#ifndef _COPS_MAPEDITOR_ENDIAN_H_
#define _COPS_MAPEDITOR_ENDIAN_H_

#include "types.h"

#ifdef HAVE_ENDIAN_H
#include <endian.h>
#endif // HAVE_ENDIAN_H

/*
 *****************************************************
 * Determine endian at compilation
 ****************************************************
 */

// LITTLE_ENDIAN is defined with some header/compiler
#ifndef LITTLE_ENDIAN
#define LITTLE_ENDIAN 1
#endif

// BIG_ENDIAN is defined with some header/compiler
#ifndef BIG_ENDIAN
#define BIG_ENDIAN 2
#endif

// If BYTE_ORDER is defined, it should be equal to LITTLE_ENDIAN or BIG_ENDIAN.
// Else, it's an unsupported endianness.
// The value of LITTLE_ENDIAN and BIG_ENDIAN may be different to the one defined in this header.
#if defined(BYTE_ORDER) && (BYTE_ORDER != LITTLE_ENDIAN && BYTE_ORDER != BIG_ENDIAN)
#error Unsupported endianness!
#elif !defined(BYTE_ORDER)

// If __BYTE_ORDER__ is defined, it is possible to use it to define BYTE_ORDER with our custom values.
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define BYTE_ORDER LITTLE_ENDIAN
#elif defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define BYTE_ORDER BIG_ENDIAN
#elif defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__ // Middle-Endian BADC
#error Unsupported endianness!
#else

// If no byte order is defined, it is possible to use the target architecture macro to define
// BYTE_ORDER with our custom values.
// For the Bi-Endian architecture (e.g. ARM, IA64, etc), the default architecture is used.
// Although it SHOULD works in most cases, using runtime checks is more safer.
#if defined(__i386__) || defined(__i386) || defined(__X86__) || defined(_X86_) || defined(_M_IX86) || \
    defined(__x86_64__) || defined(__amd64__) || defined(__x86_64) || defined(__amd64) || \
    defined(_M_X64) || defined(_M_AMD64) ||                             \
    defined(__arm__) || defined(_ARM) ||                                \
    defined(__mips__) || defined(__MIPS__) || defined(__mips) ||        \
    defined(__alpha__) || defined(__alpha) || defined(_M_ALPHA)
#define BYTE_ORDER LITTLE_ENDIAN
#elif defined(__ppc__) || defined(__ppc64__) || defined(__powerpc__) || defined(_M_MPPC) || \
    defined(_M_PPC) ||                                                  \
    defined(__sparc__) || defined(__sparc) ||                           \
    defined(__ia64__) || defined(__IA64__) || defined(__ia64) || defined(__IA64)  || \
    defined(__itanium__) ||defined(_M_IA64) ||                          \
    defined(__hppa__) || defined (__hppa) || defined(__HPPA__) ||       \
    defined(__m68k__) || defined(__MC68K__) || defined(M68000)
#define BYTE_ORDER BIG_ENDIAN
#else
#error Unknow endianness!
#endif // Architecture

#endif // __BYTE_ORDER__

#endif // BYTE_ORDER

/*
 *****************************************************
 * Byte swapping methods
 ****************************************************
 */

/**
 * Swap all the bytes of the 16-bit integer to get the value
 * of the opposite endianness.
 *
 * @param[in]  x      the 16-bit integer
 *
 * @returns the integer with all bytes swapped for the opposite endian
 */
inline int16_t bswap16(int16_t x)
{
    #if defined(__GNUC__) && (((__GNUC__ * 100) + __GNUC_MINOR__) >= 480)
    return __builtin_bswap16(x); // GCC 4.8+
    #else
    return ((((uint16_t)(x) & 0xFF00) >> 8) | \
            (((uint16_t)(x) & 0x00FF) << 8));
    #endif
}

/**
 * Swap all the bytes of the 16-bit unsigned integer to get the value
 * of the opposite endianness.
 *
 * @param[in]  x      the 16-bit unsigned integer
 *
 * @returns the integer with all bytes swapped for the opposite endian
 */
inline uint16_t bswap16(uint16_t x)
{
    return (uint16_t)bswap16((int16_t)x);
}

/**
 * Swap all the bytes of the 32-bit integer to get the value
 * of the opposite endianness.
 *
 * @param[in]  x      the 32-bit integer
 *
 * @returns the integer with all bytes swapped for the opposite endian
 */
inline int32_t bswap32(int32_t x)
{
    #if defined(__GNUC__) && (((__GNUC__ * 100) + __GNUC_MINOR__) >= 430)
    return __builtin_bswap32(x); // GCC 4.3+
    #else
    return ((((uint32_t)(x) & 0xFF000000) >> 24) |                 \
            (((uint32_t)(x) & 0x00FF0000) >> 8) |                  \
            (((uint32_t)(x) & 0x0000FF00) << 8) |                  \
            (((uint32_t)(x) & 0x000000FF) << 24));
    #endif
}

/**
 * Swap all the bytes of the 32-bit unsigned integer to get the value
 * of the opposite endianness.
 *
 * @param[in]  x      the 32-bit unsigned integer
 *
 * @returns the integer with all bytes swapped for the opposite endian
 */
inline uint32_t bswap32(uint32_t x)
{
    return (uint32_t)bswap32((int32_t)x);
}

/**
 * Swap all the bytes of the 64-bit integer to get the value
 * of the opposite endianness.
 *
 * @param[in]  x      the 64-bit integer
 *
 * @returns the integer with all bytes swapped for the opposite endian
 */
inline int64_t bswap64(int64_t x)
{
    #if defined(__GNUC__) && (((__GNUC__ * 100) + __GNUC_MINOR__) >= 430)
    return __builtin_bswap64(x); // GCC 4.3+
    #else
    return (((uint64_t)(x) << 56) |                         \
            (((uint64_t)(x) << 40) & 0xFF000000000000ULL) | \
            (((uint64_t)(x) << 24) & 0xFF0000000000ULL) |   \
            (((uint64_t)(x) << 8)  & 0xFF00000000ULL) |     \
            (((uint64_t)(x) >> 8)  & 0xFF000000ULL) |       \
            (((uint64_t)(x) >> 24) & 0xFF0000ULL) |         \
            (((uint64_t)(x) >> 40) & 0xFF00ULL) |           \
            ((uint64_t)(x)  >> 56));
    #endif
}

/**
 * Swap all the bytes of the 64-bit unsigned integer to get the value
 * of the opposite endianness.
 *
 * @param[in]  x      the 64-bit unsigned integer
 *
 * @returns the integer with all bytes swapped for the opposite endian
 */
inline uint64_t bswap64(uint64_t x)
{
    return (uint64_t)bswap64((int64_t)x);
}

/*
 *****************************************************
 * Determine endian at runtime
 ****************************************************
 */

/**
 * Determine whether the current program is running under a big endian
 * architecture. It is determined at runtime.
 *
 * @retval TRUE if the processor is running under a big endian architecture.
 * @returns FALSE otherwise
 */
inline bool isBigEndian()
{
    int32_t dword = 0x11223344;
    int8_t* ptr = (int8_t*)&dword;

    return ptr[0] == 0x11 && ptr[1] == 0x22 &&
            ptr[2] == 0x33 && ptr[3] == 0x44;
}

/**
 * Determine whether or not, the current program is running under a
 * little endian architecture. It is determined at runtime.
 *
 * @retval TRUE if the processor is running under a little endian architecture.
 * @returns FALSE otherwise
 */
inline bool isLittleEndian()
{
    int32_t dword = 0x11223344;
    int8_t* ptr = (int8_t*)&dword;

    return ptr[0] == 0x44 && ptr[1] == 0x33 &&
            ptr[2] == 0x22 && ptr[3] == 0x11;
}

#endif // _COPS_MAPEDITOR_ENDIAN_H
