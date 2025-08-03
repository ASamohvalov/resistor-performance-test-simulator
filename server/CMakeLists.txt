cmake_minimum_required(VERSION 3.16)

project(server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
find_package(spdlog REQUIRED)

pkg_check_modules(HIREDIS REQUIRED hiredis)

add_executable(server
  src/main.cpp

  src/config/env_handler.cpp
  src/config/redis_config.cpp

  src/db/redis_wrapper.cpp
  src/serial_port/serial_port.cpp
  src/serial_port/receiver.cpp
  src/serial_port/sender.cpp

  src/route/routes.cpp
  src/route/route_provider.cpp
)

target_include_directories(server PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/src

  ${HIREDIS_INCLUDE_DIRS}
)

target_compile_options(server PRIVATE -Wall)

target_link_libraries(server PRIVATE
  ${HIREDIS_LIBRARIES}
  spdlog::spdlog
)
