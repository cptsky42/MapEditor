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

#ifndef _COPS_MAPEDITOR_GAMEMAP_H_
#define _COPS_MAPEDITOR_GAMEMAP_H_

#include "common.h"
#include <string>
#include <map>
#include <vector>

class GameMap
{
public:
    struct MapInfo
    {
    public:
        int32_t UniqID;
        std::string Path;
        int32_t PuzzleSize;

    public:
        MapInfo() { UniqID = 0; PuzzleSize = 0; }
    };

public:
    GameMap();
    ~GameMap();

public:
    err_t load(const std::string& aPath);
    err_t save(const std::string& aPath);

    GameMap::MapInfo* getMapInfo(int32_t aUniqID);
    std::vector<int32_t> getMapUIDs();

    err_t add(MapInfo** aInfo);
    err_t remove(int32_t aUniqID);

    void clear();

private:
    std::map<int32_t, MapInfo*> mMaps;
};

#endif // _COPS_MAPEDITOR_GAMEMAP_H_
