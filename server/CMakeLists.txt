
############# must before add_executable
include_directories("/home/OSPL/event/libevent/include")
#link_directories("/home/OSPL/event/libevent/.libs")
#link_libraries(event)
link_libraries("/home/OSPL/event/libevent/.libs/libevent.so")
#set(CMAKE_SKIP_RPATH true)
#set(CMAKE_SKIP_BUILD_RPATH true)
#set(CMAKE_SKIP_INSTALL_RPATH true)
#set(CMAKE_INSTALL_RPATH_USE_LINK_PATH true) or set(CMAKE_INSTALL_RPATH "/home/OSPL/event/libevent/.libs")


set(APP_SRC main.cpp TcpSocketServer.cpp EventServer.cpp)
add_executable(service ${APP_SRC})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})


#### after add_executable
#target_link_libraries(service event)
set_target_properties(service PROPERTIES INSTALL_RPATH "/home/OSPL/event/libevent/.libs")
#set_property(TARGET service PROPERTY INSTALL_RPATH_USE_LINK_PATH TRUE)

###make install
SET(CMAKE_INSTALL_PREFIX "/home/pro/echoServer/build")
install(TARGETS service DESTINATION ${CMAKE_INSTALL_PREFIX})


message(${PROJECT_BINARY_DIR})
message(${PROJECT_SOURCE_DIR})
message(${CMAKE_SKIP_RPATH})
#message(${CMAKE_SKIP_BUILD_RPATH})
message(${CMAKE_SKIP_INSTALL_RPATH})
#message(${CMAKE_BUILD_WITH_INSTALL_RPATH})
#message(${CMAKE_BUILD_RPATH})
#message(${BUILD_RPATH})
message("server cmakelist ", "------------ok")

