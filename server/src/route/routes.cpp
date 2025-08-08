#include "routes.h"
#include "db/redis_wrapper.h"
#include "device/resistor.h"
#include "serial_port/serial_port.h"

#include <spdlog/spdlog.h>
#include <string>
#include <utility>

namespace route
{
    void setTemperature(const std::string& data)
    {
        double temperature;
        try {
            temperature = std::stod(data.c_str());
        } catch (...) { // out_of_range, invalid_argument
            spdlog::warn("invalid temperature format");
            return;
        }
        spdlog::info("set temperature - " + data);
        db::RedisWrapper wrapper;
        wrapper.set("temperature", temperature, "%f");
        double resistance = 
                device::calculateResistanceByTemp(device::baseResistor, temperature);
        wrapper.set("resistance", resistance, "%f");
        serialPort::SerialPort::getInstance().writeLine("1/" + std::to_string(resistance));
    }

    void setAmperage(const std::string& data)
    {
        double inputAmperage;
        try {
            inputAmperage = std::stod(data.c_str());
        } catch (...) {
            spdlog::warn("invalid amperage format");
            return;
        }
        spdlog::info("set amperage - " + data);
        std::pair<double, double> res = 
                device::calculateVoltageAndPowerByAmperage(device::getCurrentResistor(), inputAmperage);
        spdlog::info("res - " + std::to_string(res.first) + " " + std::to_string(res.second));
        serialPort::SerialPort::getInstance()
                .writeLine("2/" + std::to_string(res.first) + "&" + std::to_string(res.second));
    }
}