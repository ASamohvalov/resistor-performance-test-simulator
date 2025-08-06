#include "env_handler.h"
#include "../include/dotenv.h"

#include <QString>

namespace config
{
    static const dotenv& getInstance()
    {
        static const dotenv env("../../.env");
        return env;
    }

    QString getEnv(const QString& key)
    {
        return QString::fromStdString(getInstance().get(key.toStdString()));
    }
} // namespace config
