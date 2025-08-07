#ifndef ROUTE_PROVIDER_H
#define ROUTE_PROVIDER_H

#include <QString>
#include <QThread>

#include "routes.h"

namespace route
{
    class RouteProvider : public QThread
    {
        Q_OBJECT
    public:
        RouteProvider(const QString& data, QObject* parent = nullptr);
        void router();

    private:
        QString data_;
        Router router_;
    };
}

#endif // ROUTE_PROVIDER_H
