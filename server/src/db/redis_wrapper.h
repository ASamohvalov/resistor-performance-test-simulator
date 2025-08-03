#ifndef REDIS_WRAPPER_H
#define REDIS_WRAPPER_H

#include "config/redis_config.h"

#include <hiredis/hiredis.h>
#include <spdlog/spdlog.h>
#include <stdexcept>
#include <string>

namespace db
{
    class RedisWrapper
    {
    public:
        template <typename T> 
        void set(const std::string& key, const T& value, const std::string& valueFormat) const
        {
            std::string command = "SET %s " + valueFormat;
            redisReply* reply = static_cast<redisReply*>(
                    redisCommand(config_.context(), command.c_str(), key.c_str(), value));
            if (reply == nullptr) {
                throw std::runtime_error("execution command error");
            }
            freeReplyObject(reply);
        }

        void set(const std::string& key, const std::string& value);
        std::string get(const std::string& key) const;

    private:
        static const config::RedisConfig config_;
    }; 
} // namespace db

#endif // REDIS_WAPPER_H
