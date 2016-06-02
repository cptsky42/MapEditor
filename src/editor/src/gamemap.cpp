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

#include "gamemap.h"
#include <stdio.h>
#include <algorithm>

using namespace std;

#if BYTE_ORDER == BIG_ENDIAN
#warning "Will need to swap when reading and writing !"
#endif

GameMap :: GameMap()
{

}

GameMap :: ~GameMap()
{
    clear();
}

err_t
GameMap :: load(const string& aPath)
{
    assert(!aPath.empty());

    clear();

    err_t err = ERROR_SUCCESS;
    FILE* stream = nullptr;

    stream = fopen(aPath.c_str(), "rb");
    if (stream != nullptr)
    {
        int32_t amount = 0;
        fread(&amount, sizeof(amount), 1, stream);
        #if BYTE_ORDER == BIG_ENDIAN
        amount = bswap32(amount);
        #endif

        LOG("Found %d elements...", amount);
        for (int32_t i = 0; i < amount; ++i)
        {
            MapInfo* info = new MapInfo();

            fread(&info->UniqID, sizeof(info->UniqID), 1, stream);
            #if BYTE_ORDER == BIG_ENDIAN
            info->UniqID = bswap32(info->UniqID);
            #endif

            int32_t len = 0;
            fread(&len, sizeof(len), 1, stream);
            #if BYTE_ORDER == BIG_ENDIAN
            len = bswap32(len);
            #endif


            char* path = new char[len + 1];
            path[len] = '\0';

            fread(path, sizeof(char), len, stream);
            info->Path = path;

            SAFE_DELETE_ARRAY(path);

            fread(&info->PuzzleSize, sizeof(info->PuzzleSize), 1, stream);
            #if BYTE_ORDER == BIG_ENDIAN
            info->PuzzleSize = bswap32(info->PuzzleSize);
            #endif

            map<int32_t, MapInfo*>::iterator it = mMaps.find(info->UniqID);
            if (it == mMaps.end())
            {
                mMaps[info->UniqID] = info;
                LOG("Added UID=%d, Path=%s, PuzzleSize=%d",
                    info->UniqID, info->Path.c_str(), info->PuzzleSize);

                info = nullptr;
            }
            else
            {
                LOG("Collision for UID=%d", info->UniqID);
                err = ERROR_UNKNOWN;
            }

            SAFE_DELETE(info);
        }

        fclose(stream);
    }
    else
    {
        err = ERROR_OPEN_FAILED;
    }

    return err;
}

err_t
GameMap :: save(const string& aPath)
{
    assert(!aPath.empty());
    assert(mMaps.size() <= INT32_MAX);

    err_t err = ERROR_SUCCESS;
    FILE* stream = nullptr;

    stream = fopen(aPath.c_str(), "wb");
    if (stream != nullptr)
    {
        int32_t amount = (int32_t)mMaps.size();
        #if BYTE_ORDER == BIG_ENDIAN
        amount = bswap32(amount);
        #endif

        fwrite(&amount, sizeof(amount), 1, stream);

        for (map<int32_t, MapInfo*>::iterator
             it = mMaps.begin(), end = mMaps.end();
             it != end; ++it)
        {
            MapInfo* info = it->second;

            int32_t uniqID = info->UniqID;
            #if BYTE_ORDER == BIG_ENDIAN
            uniqID = bswap32(uniqID);
            #endif
            fwrite(&uniqID, sizeof(uniqID), 1, stream);

            assert(info->Path.size() <= INT32_MAX);
            int32_t len = (int32_t)info->Path.size();
            #if BYTE_ORDER == BIG_ENDIAN
            len = bswap32(len);
            #endif

            fwrite(&len, sizeof(len), 1, stream);
            fwrite((char*)info->Path.data(), sizeof(char), (int32_t)info->Path.size(), stream);

            int32_t puzzleSize = info->PuzzleSize;
            #if BYTE_ORDER == BIG_ENDIAN
            puzzleSize = bswap32(puzzleSize);
            #endif

            fwrite(&puzzleSize, sizeof(puzzleSize), 1, stream);
        }

        fclose(stream);
    }
    else
    {
        err = ERROR_OPEN_FAILED;
    }

    return err;
}

GameMap::MapInfo*
GameMap :: getMapInfo(int32_t aUniqID)
{
    MapInfo* info = nullptr;

    map<int32_t, MapInfo*>::iterator it = mMaps.find(aUniqID);
    if (it != mMaps.end())
    {
        info = it->second;
    }

    return info;
}

vector<int32_t>
GameMap :: getMapUIDs()
{
    vector<int32_t> mList;
    mList.reserve(mMaps.size());

    for (map<int32_t, MapInfo*>::iterator
         it = mMaps.begin(), end = mMaps.end();
         it != end; ++it)
    {
        MapInfo* info = it->second;

        mList.push_back(info->UniqID);
    }

    sort(mList.begin(), mList.end());
    return mList;
}


err_t
GameMap :: add(MapInfo** aInfo)
{
    assert(aInfo != nullptr && *aInfo != nullptr);

    err_t err = ERROR_SUCCESS;

    map<int32_t, MapInfo*>::iterator it = mMaps.find((*aInfo)->UniqID);
    if (it == mMaps.end())
    {
        mMaps[(*aInfo)->UniqID] = *aInfo;
    }
    else
    {
        err = ERROR_UNKNOWN;
    }

    if (IS_SUCCESS(err))
    {
        *aInfo = nullptr;
    }
    SAFE_DELETE(*aInfo);

    return err;
}

err_t
GameMap :: remove(int32_t aUniqID)
{
    err_t err = ERROR_SUCCESS;

    map<int32_t, MapInfo*>::iterator it = mMaps.find(aUniqID);
    if (it != mMaps.end())
    {
        mMaps.erase(it);
    }
    else
    {
        err = ERROR_NOT_FOUND;
    }

    return err;
}

void
GameMap :: clear()
{
    for (map<int32_t, MapInfo*>::iterator
         it = mMaps.begin(), end = mMaps.end();
         it != end; ++it)
    {
        MapInfo* info = it->second;
        SAFE_DELETE(info);
    }
    mMaps.clear();
}
