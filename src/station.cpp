#include "station.h"

const Station* find_station(const Station* stations, int count, const std::string& name)
{
    for (int i = 0; i < count; ++i)
    {
        if (stations[i].name == name)
        {
            return &stations[i];}
    }
return nullptr;
}
