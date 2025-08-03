#include "routes.h"
#include "db/redis_wrapper.h"
#include <spdlog/spdlog.h>

namespace route
{
    void setTemperature(const std::string& data)
    {
        spdlog::info("set temperature - " + data);
        db::RedisWrapper wrapper;
        int temperature;
        try {
            temperature = std::stoi(data.c_str());
        } catch (...) { // out_of_range, invalid_argument
            spdlog::warn("invalid temperature format");
            return;
        }
        wrapper.set("temperature", temperature, "%i");
        // formula ...
    }
}