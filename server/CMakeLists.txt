set(APP_SRC main.cpp TcpSocketServer.cpp)
add_executable(service ${APP_SRC})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)

message(${PROJECT_BINARY_DIR})
message(${PROJECT_SOURCE_DIR})

