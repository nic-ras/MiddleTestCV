cmake_minimum_required(VERSION 3.10)

set( MiddleTestCV_src
    main.cpp
    dataset.cpp
    detector.cpp
    performance.cpp
)
add_executable(MiddleTestCV ${MiddleTestCV_src})

target_link_libraries(MiddleTestCV PRIVATE ${OpenCV_LIBS})
target_include_directories(MiddleTestCV PRIVATE ${OpenCV_INCLUDE_DIRS})
