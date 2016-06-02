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

#ifndef _COPS_MAPEDITOR_ARCH_H_
#define _COPS_MAPEDITOR_ARCH_H_

#if defined(_AIX) || defined(__TOS_AIX__)
#define TARGET_SYSTEM "AIX"
#define TARGET_SYSTEM_AIX 1

#elif defined(__ANDROID__)
#define TARGET_SYSTEM "Android"
#define TARGET_SYSTEM_ANDROID 1

#elif defined(AMIGA) || defined(__amigaos__)
#define TARGET_SYSTEM "AMIGA"
#define TARGET_SYSTEM_AMIGA 1

#elif defined(__BEOS__)
#define TARGET_SYSTEM "BeOS"
#define TARGET_SYSTEM_BEOS 1

#elif defined(__FreeBSD_kernel__)
#define TARGET_SYSTEM "GNU/kFreeBSD"
#define TARGET_SYSTEM_GNU_FREEBSD 1

#elif defined(__gnu_linux__)
#define TARGET_SYSTEM "GNU/Linux"
#define TARGET_SYSTEM_GNU_LINUX 1

#elif defined(macintosh)
#define TARGET_SYSTEM "Mac OS 9"
#define TARGET_SYSTEM_MACOS 1

#elif defined(__APPLE__)
#define TARGET_SYSTEM "Mac OS X"
#define TARGET_SYSTEM_MACOS_X 1

#elif defined(MSDOS) || defined(__MSDOS__) || defined(DOS) || \
    defined(_MSDOS)
#define TARGET_SYSTEM "MS-DOS"
#define TARGET_SYSTEM_MSDOS 1

#elif defined(sun) || defined(__sun)
#define TARGET_SYSTEM "Solaris"
#define TARGET_SYSTEM_SOLARIS 1

#elif defined(_WIN16) || defined(_WIN32) || defined(_WIN64) || \
    defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
#define TARGET_SYSTEM "Windows"
#define TARGET_SYSTEM_WINDOWS 1

#else
#define TARGET_SYSTEM "unknown"
#define TARGET_SYSTEM_UNKNOWN 1

#endif // TARGET_SYSTEM



#if defined(__i386__) || defined(__i386) || defined(__X86__) || \
    defined(_X86_) || defined(_M_IX86)
#define TARGET_INSTR "x86"
#define TARGET_ARCH "Intel 32-bit"
#define TARGET_INSTR_X86 1

#elif defined(__x86_64__) || defined(__amd64__) || defined(__x86_64) || \
    defined(__amd64) || defined(_M_X64) || defined(_M_AMD64)
#define TARGET_INSTR "x86_64"
#define TARGET_ARCH "Intel 64-bit"
#define TARGET_INSTR_X86_64 1

#elif defined(__ppc__) || defined(__powerpc__) || \
    defined(_M_MPPC) || defined(_M_PPC)
#define TARGET_INSTR "ppc"
#define TARGET_ARCH "PowerPC 32-bit"
#define TARGET_INSTR_PPC 1

#elif defined(__ppc64__)
#define TARGET_INSTR "ppc64"
#define TARGET_ARCH "PowerPC 64-bit"
#define TARGET_INSTR_PPC64 1

#elif defined(__ia64__) || defined(__IA64__) || defined(__ia64) || \
    defined(__IA64) || defined(__itanium__) || defined(_M_IA64)
#define TARGET_INSTR "ia64"
#define TARGET_ARCH "Itanium 64-bit"
#define TARGET_INSTR_IA64 1

#elif defined(__arm__) || defined(_ARM) || defined(__TARGET_ARCH_ARM) || \
    defined(_M_ARM)
#define TARGET_INSTR "arm"
#define TARGET_ARCH "ARM"
#define TARGET_INSTR_ARM 1

#elif defined(__thumb__) || defined(__TARGET_ARCH_THUMB) || defined(_M_ARMT)
#define TARGET_INSTR "arm"
#define TARGET_ARCH "ARM (Thumb)"
#define TARGET_INSTR_ARM 1

#elif defined(__aarch64__)
#define TARGET_INSTR "arm64"
#define TARGET_ARCH "ARM 64-bit"
#define TARGET_INSTR_ARM64 1

#elif defined(__mips__) || defined(__MIPS__) || defined(__mips)
#define TARGET_INSTR "mips"
#define TARGET_ARCH "MIPS"
#define TARGET_INSTR_MIPS 1

#elif defined(__sparc__) || defined(__sparc)
#define TARGET_INSTR "sparc"
#define TARGET_ARCH "SPARC"
#define TARGET_INSTR_SPARC 1

#elif defined(__alpha__) || defined(__alpha) || defined(_M_ALPHA)
#define TARGET_INSTR "alpha"
#define TARGET_ARCH "Alpha"
#define TARGET_INSTR_ALPHA 1

#elif defined(__hppa__) || defined (__hppa) || defined(__HPPA__)
#define TARGET_INSTR "hppa"
#define TARGET_ARCH "HP/PA"
#define TARGET_INSTR_HPPA 1

#elif defined(__m68k__) || defined(__MC68K__) || defined(M68000)
#define TARGET_INSTR "m68k"
#define TARGET_ARCH "Motorola 68k"
#define TARGET_INSTR_M68K 1

#else
#define TARGET_INSTR "uknw"
#define TARGET_ARCH "unknown"
#define TARGET_INSTR_UNKNOWN

#endif // TARGET_ARCH

#endif // _COPS_MAPEDITOR_ARCH_H_
