#ifndef ROUTE_PROVIDER_H
#define ROUTE_PROVIDER_H

#include <string>

namespace route
{
    // a function that calls a route multithreaded
    void call(const std::string& data);
}

#endif // ROUTE_PROVIDER_H