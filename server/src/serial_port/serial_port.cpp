#include "serial_port.h"
#include "config/env_handler.h"

#include <fcntl.h>
#include <spdlog/spdlog.h>
#include <stdexcept>
#include <unistd.h>

namespace serialPort
{
    SerialPort::SerialPort() : portfile_(config::getEnv("SERVER_COM_PORT")) 
    {}

    SerialPort::~SerialPort()
    {
        close(fd_);
    }

    void SerialPort::openPort()
    {
        fd_ = open(portfile_.c_str(), O_RDWR | O_NOCTTY);
        if (fd_ < 0) {
            throw std::runtime_error("error open portfile");
        }
        spdlog::info("port " + portfile_ + " is open");
    }

    std::string SerialPort::readLine() 
    {
        std::string line;
        char sy;
        while (read(fd_, &sy, 1) == 1) {
            if (sy == '\n') {
                break;
            }
            line += sy;
        }
        return line;
    }

    void SerialPort::writeLine(const std::string& data)
    {
        write(fd_, data.c_str(), data.length());
    }
}