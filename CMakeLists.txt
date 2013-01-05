cmake_minimum_required (VERSION 2.6)
project (Multipath-CDMA)
add_executable (task1
	src/task1.cpp
	src/wrappers.cpp
	)

add_executable (task2
	src/task2.cpp
	src/wrappers.cpp
)

add_executable (task3
	src/task3.cpp
	src/wrappers.cpp
)

add_executable (task4
	src/task4.cpp
	src/wrappers.cpp
)

add_executable (bmpHeaderDataSplit
	src/bmpHeaderDataSplit.cpp
)

add_executable (bmpHeaderDataMerge
	src/bmpHeaderDataMerge.cpp
)
