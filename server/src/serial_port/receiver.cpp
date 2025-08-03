#include "receiver.h"
#include "route/route_provider.h"

#include <spdlog/spdlog.h>

namespace serialPort
{
#if 0
    void Receiver::start() 
    {
        std::thread thread (&Receiver::run, this);        
        thread.detach();
    }

    void Receiver::run()
#endif

    void Receiver::start() 
    {
	    openPort();
        while (true) {
            std::string data = readLine();
            if (data.empty() || data == "\n") continue;
            route::call(data);
        }
    }
}