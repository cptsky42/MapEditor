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

#ifndef _COPS_MAPEDITOR_LOG_H_
#define _COPS_MAPEDITOR_LOG_H_

#include <stdio.h>

#define LOG(fmt, ...) \
    fprintf(stderr, fmt "\n", __VA_ARGS__)

#endif // _COPS_MAPEDITOR_LOG_H_
