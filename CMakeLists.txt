cmake_minimum_required(VERSION 3.17)
project(CPP_Yandex_week1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -std=c++98 -fsized-deallocation")

add_executable(main
        main.cpp)
