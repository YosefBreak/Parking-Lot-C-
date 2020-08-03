cmake_minimum_required(VERSION 3.12)
project(MTM)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-std=c++11  -Wall  -Werror  -pedantic-errors")
add_executable(MTM UniqueArray.h UniqueArrayImp.h ParkingLot.h ParkingLotPrinter.cpp ParkingLotPrinter.h ParkingLotTypes.h
        ParkingSpot.cpp ParkingSpot.h MtmParkingLot.cpp Time.cpp ParkingLotPrinter.cpp MtmParkingLot.cpp ParkingLotPrinter.cpp ParkingLot.cpp)