#include "env_handler.h"
#include <string>
#include "dotenv.h"

namespace config
{
    static const dotenv& getInstance()
    {
        static const dotenv env("../.env");
        return env;
    }

    std::string getEnv(const std::string& key)
    {
        return getInstance().get(key);
    }
} // namespace config
