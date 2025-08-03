#include "redis_config.h"
#include "config/env_handler.h"

#include <bits/types/struct_timeval.h>
#include <stdexcept>
#include <string>

namespace config 
{
    RedisConfig::RedisConfig() : hostname_(getEnv("REDIS_HOSTNAME"))
            , port_(getEnv("REDIS_PORT"))
            , password_(getEnv("REDIS_PASSWORD"))
    {
        ctx_ = redisConnect(hostname_.c_str(), std::stoi(port_));
        if (ctx_ == nullptr || ctx_->err) {
            throw std::runtime_error("Redis connection error");
        }
    }

    redisContext* RedisConfig::context() const noexcept
    {
        return ctx_;
    }

    RedisConfig::~RedisConfig()
    {
        redisFree(ctx_);
    }
}