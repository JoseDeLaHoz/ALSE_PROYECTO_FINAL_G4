cmake_minimum_required(VERSION 3.5)

project(Proyecto LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}_consola 
	Control_DB.h 
	Control_DB.cpp 
	sensor.h 
	sensor.cpp 
	main.cpp)
	
add_executable(${PROJECT_NAME}_interfaz 
        main_I.cpp
        dialoglogin.cpp
        dialoglogin.h
        dialoglogin.ui
        dia_createuser.cpp
        dia_createuser.h
        dia_createuser.ui
        mainw_datos.cpp
        mainw_datos.h
        mainw_datos.ui
	Control_DB.h
        Control_DB.cpp
        recursos.qrc)

target_link_libraries (${PROJECT_NAME}_consola sqlite3 )
target_link_libraries(${PROJECT_NAME}_interfaz Qt5::Widgets sqlite3)

set_target_properties(${PROJECT_NAME}_consola ${PROJECT_NAME}_interfaz
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../bin")

find_package(Qt5 COMPONENTS Widgets REQUIRED)

