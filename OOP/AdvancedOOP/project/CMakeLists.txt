cmake_minimum_required( VERSION 3.14)

PROJECT(SystemMonitor)

set(CMAKE_BUILD_TYPE Debug)


MACRO(add_example name)
	ADD_EXECUTABLE(${name} ${name}.cpp)
ENDMACRO()


add_example(main)
