#ifndef ENV_HANDLER_H
#define ENV_HANDLER_H

#include <QString>

namespace config
{
    QString getEnv(const QString& key);
}

#endif // ENV_HANDLER_H
