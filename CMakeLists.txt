<<<<<<< HEAD
# The following lines of boilerplate have to be in your project's CMakeLists
# in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

set(EXTRA_COMPONENT_DIRS ../components/)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(MPU6050_DMP6)
=======
idf_component_register(SRCS "main.cpp" "mpu6050.cpp" "wifi.c" "udp_trans.c" "web_server.c" "web_client.c"
    INCLUDE_DIRS "."
    EMBED_FILES "../html/error.html"
                "../html/favicon.ico"
                "../html/main.js"
                "../html/root.html"
                "../html/main.css")
>>>>>>> 940b62e5c053f36322bff0588e6949b0c1a4bb6b
