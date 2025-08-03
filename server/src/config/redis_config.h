#ifndef REDIS_CONFIG_H
#define REDIS_CONFIG_H

#include <hiredis.h>
#include <string>

namespace config 
{
    class RedisConfig
    {
    public:
        // @throw runtime_error
        RedisConfig();
        ~RedisConfig();
    
        redisContext* context() const noexcept;
    
    private:
        redisContext* ctx_;

        std::string hostname_;
        std::string port_;
        std::string password_;
    };
}

#endif // REDIS_CONFIG_H