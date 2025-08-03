#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <string>

namespace route
{
    enum class RouteType : int
    {
        SetTemperature = 1
    };

    void setTemperature(const std::string& data);
}

#endif