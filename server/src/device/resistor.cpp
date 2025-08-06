#include "resistor.h"
#include "db/redis_wrapper.h"
#include <spdlog/spdlog.h>

namespace device
{
    static constexpr double ROOM_TEMP = 20;
    static constexpr double START_RESISTANCE = 200;

    const Resistor baseResistor { START_RESISTANCE };

    Resistor getCurrentResistor()
    {
        db::RedisWrapper wrapper;
        try {
            return Resistor { std::stod(wrapper.get("resistance").c_str()) };
        } catch(...) { // if resistance is empty in redis
            return baseResistor;
        }
    }

    double calculateResistanceByTemp(const Resistor& resistor, double temp)
    {
        return resistor.resistance * 
                (1 + resistor.resistance_coefficient * (temp - ROOM_TEMP));
    }

    double calculateVoltageByAmperage(const Resistor& resistor, double amperage)
    {
        // I = V / R
        return amperage * resistor.resistance;
    }
}