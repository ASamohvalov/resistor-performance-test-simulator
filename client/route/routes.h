#ifndef ROUTES_H
#define ROUTES_H 

#include <QObject>

namespace route
{
    class Router : public QObject
    {
        Q_OBJECT
    public:
        Router(QObject* parent = nullptr);

        void setTemperature(const QString& data);
        void setAmperage(const QString& data);
    };
}

#endif
