#ifndef ENV_HANDLER_H
#define ENV_HANDLER_H

#include <string>

namespace config
{
    std::string getEnv(const std::string& key);
}

#endif // ENV_HANDLER_H
