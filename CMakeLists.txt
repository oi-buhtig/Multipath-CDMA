cmake_minimum_required (VERSION 2.6)
project (Multipath-CDMA)
add_executable (task1
	src/task1.cpp
	src/wrappers.cpp
	)
ADD_DEFINITIONS("-std=c++11")
