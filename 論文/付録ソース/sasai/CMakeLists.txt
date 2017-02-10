cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(HELLO_WORLD)
find_package(PCL 1.3 REQUIRED COMPONENTS common io)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
add_executable(3Dworld 3Dworld.cpp)
target_link_libraries(3Dworld ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES})

cmake_minimum_required(VERSION 2.8)
project( 3dworld )
find_package( OpenCV 3.0 REQUIRED )




cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(match)
find_package(PCL 1.7 REQUIRED COMPONENTS common io)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
add_executable(match match.cpp tsukuba_tkk.cpp navigation.cpp)
target_link_libraries(match ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES})

cmake_minimum_required(VERSION 2.8)
project( match )
find_package( OpenCV 3.0 REQUIRED )



cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(HELLO_WORLD)
find_package(PCL 1.3 REQUIRED COMPONENTS common io)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
add_executable(drone_Rt drone_Rt.cpp)
target_link_libraries(drone_Rt ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES})

cmake_minimum_required(VERSION 2.8)
project( drone_Rt )
find_package( OpenCV 3.0 REQUIRED )


cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(HELLO_WORLD)
find_package(PCL 1.3 REQUIRED COMPONENTS common io)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
add_executable(imwrite imwrite.cpp)
target_link_libraries(imwrite ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES})

cmake_minimum_required(VERSION 2.8)
project( imwrite )
find_package( OpenCV 3.0 REQUIRED )


include_directories( ${OpenCV_INCLUDE_DIRS} )

#file(GLOB viso
  #  "src/*.h"
    #"src/*.cpp"
#)
#add_executable( 3Dworld ${viso} )
target_link_libraries( 3Dworld ${OpenCV_LIBS} )




include_directories( ${OpenCV_INCLUDE_DIRS} )

#file(GLOB viso
  #  "src/*.h"
    #"src/*.cpp"
#)

target_link_libraries( match ${OpenCV_LIBS} )



include_directories( ${OpenCV_INCLUDE_DIRS} )

#file(GLOB viso
  #  "src/*.h"
    #"src/*.cpp"
#)

target_link_libraries( drone_Rt ${OpenCV_LIBS} )


include_directories( ${OpenCV_INCLUDE_DIRS} )

#file(GLOB viso
  #  "src/*.h"
    #"src/*.cpp"
#)

target_link_libraries( imwrite ${OpenCV_LIBS} )



cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(viewer)

find_package(PCL 1.7 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (viewer viewer.cpp)
target_link_libraries (viewer ${PCL_LIBRARIES})


cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(gpstest)
add_executable(gps gpstest.cpp tsukuba_tkk.cpp navigation.cpp tsukuba_time.cpp joystick.cpp)





