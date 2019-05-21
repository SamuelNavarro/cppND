cmake_minimum_required( VERSION 3.10.2)

PROJECT(SystemMonitor)

set(CMAKE_BUILD_TYPE Debug)

find_package( Curses REQUIRED )

include_directories( ${CURSES_INCLUDE_DIRS} )


MACRO(add_example name)
	ADD_EXECUTABLE(${name} ${name}.cpp)
	TARGET_LINK_LIBRARIES(${name} ${CURSES_LIBRARIES} )
ENDMACRO()


add_example(main)
