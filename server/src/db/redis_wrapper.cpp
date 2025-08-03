#include "redis_wrapper.h"
#include "config/redis_config.h"

namespace db
{
    const config::RedisConfig RedisWrapper::config_;


    void RedisWrapper::set(const std::string& key, const std::string& value)
    {
        redisReply* reply = static_cast<redisReply*>(
                redisCommand(config_.context(), "SET %s %s", key.c_str(), value.c_str()));
        if (reply == nullptr) {
            throw std::runtime_error("execution command error");
        }
        freeReplyObject(reply);
    }

    std::string RedisWrapper::get(const std::string& key) const
    {
        redisReply* reply = static_cast<redisReply*>(
                redisCommand(config_.context(), "GET %s", key.c_str()));
        if (reply == nullptr) {
            throw std::runtime_error("execution command error");
        }
        std::string result = reply->str;
        freeReplyObject(reply);
        return result;
    }
}