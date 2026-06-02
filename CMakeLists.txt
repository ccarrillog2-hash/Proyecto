cmake_minimum_required(VERSION 4.1)
project(programacion_l_proyecto_final)

set(CMAKE_CXX_STANDARD 20)

add_executable(programacion_l_proyecto_final main.cpp
        validaciones.cpp
        validaciones.h
        estructuras.h
        gestionproductos.cpp
        gestionproductos.h
        ventas.cpp
        ventas.h
        reportes.cpp
        reportes.h
        utilidades.cpp
        utilidades.h
        archivos.cpp
        archivos.h)
