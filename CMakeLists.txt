cmake_minimum_required(VERSION 3.9)
project(EDA2TrabalhoPratico)

set(CMAKE_CXX_STANDARD 11)

add_executable(EDA2TrabalhoPratico main.cpp CityList.cpp CityList.h StreetList.cpp StreetList.h HouseList.cpp
        HouseList.h BridgeList.cpp BridgeList.h RouteList.cpp RouteList.h StopoverQueue.cpp StopoverQueue.h
        MatchQueue.cpp MatchQueue.h RoundList.cpp RoundList.h)