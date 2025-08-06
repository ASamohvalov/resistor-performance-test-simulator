#include "route_provider.h"
#include "route/routes.h"
#include <spdlog/spdlog.h>
#include <thread>

namespace route
{
    namespace
    {
        void router(const std::string& data)
        {
            size_t slashPosition = data.find('/');
            if (slashPosition == data.npos) {
                spdlog::warn("slash not found in data");
                return;
            }

            int route = std::atoi(data.substr(0, slashPosition).c_str());
            std::string routeData = data.substr(slashPosition + 1); // remove after /
            
            switch (route) {
            case 1:
                setTemperature(routeData);
                break;
            case 2:
                setAmperage(routeData);
                break;
            default:
                spdlog::warn("route not defined");
            }
        }
    }

    void call(const std::string& data)
    {
        std::thread thread(&router, data);
        thread.detach();
    }
}