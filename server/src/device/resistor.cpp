#include "resistor.h"
#include "db/redis_wrapper.h"
#include <spdlog/spdlog.h>

namespace device
{
    static constexpr double ROOM_TEMP = 20;
    static constexpr double START_RESISTANCE = 100;
    static constexpr double MIN_POSSIBLE_TEMP = -65;
    static constexpr double MAX_POSSIBLE_TEMP = 155;
    static constexpr double MAX_POWER = 1;

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
        if (temp < MIN_POSSIBLE_TEMP || temp > MAX_POSSIBLE_TEMP) {
            spdlog::warn("inaccessible temperature");
            return 0;
        }
        return resistor.resistance * 
                (1 + resistor.resistance_coefficient * (temp - ROOM_TEMP));
    }

    std::pair<double, double> calculateVoltageAndPowerByAmperage(
                const Resistor& resistor, double amperage)
    {
        // I = V / R
        double voltage = amperage * resistor.resistance;
        // P = I * I * R
        double power = amperage * amperage * resistor.resistance;
        if (power > MAX_POWER) {
            spdlog::warn("max power exceeded");
            return std::make_pair(0, 0);
        }
        return std::make_pair(voltage, power);
    }
}