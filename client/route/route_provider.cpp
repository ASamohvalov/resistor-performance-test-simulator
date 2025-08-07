#include "route_provider.h"
#include "routes.h"
#include <QDebug>
#include <qthread.h>

namespace route
{
    RouteProvider::RouteProvider(const QString& data, QObject* parent)
        : QThread(parent)
        , data_(data) {}

    void RouteProvider::router()
    {
        int slashPosition = data_.indexOf('/');
        if (slashPosition == -1) {
            qInfo() << "ошибка формата полученных данных";
            return;
        }

        bool ok;
        QString routeStr = data_.left(slashPosition);
        int route = routeStr.toInt(&ok);
        if (!ok) {
            qInfo() << "передан некорректный формат сообщения";
            return;
        }
        QString routeData = data_.mid(slashPosition + 1); // remove after /

        switch (route) {
        case 1:
            router_.setTemperature(routeData);
            break;
        case 2:
            router_.setAmperage(routeData);
            break;
        default:
            qInfo() << "путь не найден";
        }
    }
}
