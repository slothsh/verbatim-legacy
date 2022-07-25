cmake_minimum_required(VERSION 3.20)
project(verbatim_proj VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(build_proj null)

# Project include directories
include_directories(
	include
)

# Catch2 Configuration
if(NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Linux") # TODO: Configure Linux with Catch2
    find_package(Catch2 3 REQUIRED)
    include(CTest)
    include(Catch)
endif(NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Linux")

# Platform message
message(STATUS "Building for platform: ${CMAKE_SYSTEM_NAME}")
	
	# Mac OS configuration
if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")

    include_directories(
		/usr/local/include/libxmlpp
        /usr/local/include/fmt
		/usr/local/include/magicenum
		/usr/local/include/catch2
		/usr/local/include/ptformat
	)
	
    find_library(LIBXMLPP NAMES libxml++-5.0.1.dylib PATHS /usr/local/lib)
    set(libxmlpp ${LIBXMLPP})

    find_library(LIBFMT NAMES libfmtd.a PATHS /usr/local/lib)
    set(libfmt ${LIBFMT})

    find_library(LIBPTFORMAT NAMES libptformat.dylib PATHS /usr/local/lib)
    set(libptformat ${LIBPTFORMAT})

	# Compiler warnings
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra")

# Windows configuration
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	# Fetch dependency paths and store in variables
	file(TO_CMAKE_PATH $ENV{LIBXMLPP_PATH} libxmlpp_path)
	file(TO_CMAKE_PATH $ENV{LIBFMT_PATH} libfmt_path)
	file(TO_CMAKE_PATH $ENV{LIBMAGICENUM_PATH} libmagicenum_path)
	file(TO_CMAKE_PATH $ENV{CATCH2_PATH} catch2_path)
	file(TO_CMAKE_PATH $ENV{LIBPTFORMAT_PATH} libptformat_path)
	message(STATUS ${libxmlpp_path})
	message(STATUS ${libfmt_path})
	message(STATUS ${libmagicenum_path})
	message(STATUS ${catch2_path})
	message(STATUS ${libptformat_path})

	include_directories(
		${libxmlpp_path}/include/libxml++-5.0
		${libfmt_path}/include
		${libmagicenum_path}/include
		${catch2_path}/include
        ${libptformat_path}
	)

	find_library(LIBFMT NAMES fmtd.lib PATHS ${libfmt_path}/lib)
	set(libfmt ${LIBFMT})

	find_library(LIBXMLPP NAMES xml++-vc142-5.0.lib PATHS ${libxmlpp_path}/lib)
	set(libxmlpp ${LIBXMLPP})
    
	find_library(LIBPTFORMAT NAMES ptformatshared.lib PATHS ${libptformat_path}/build/cmake/Debug)
	set(libptformat ${LIBPTFORMAT})

	# Compiler warnings
	# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra")

elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	# TODO

endif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")

# Executables for prototype builds
# ----------------------------------------------------------------------------|

# parsettml
add_executable(parsettml
	./src/application/parsettml.cpp
	./src/filesink.cpp
	./src/xmlfile.cpp
	./src/edlfile.cpp
	./src/ptxedlstructure.cpp
	./src/helpers.cpp
)
set_target_properties(parsettml PROPERTIES LINKER_LANGUAGE CXX)

# validatingnode
add_executable(validatingnode
	./src/application/validatingnode.cpp
)
set_target_properties(validatingnode PROPERTIES LINKER_LANGUAGE CXX)

# pttool
add_executable(pttool
	./src/application/pttool.cpp
    ./src/ptparser.cpp
)
set_target_properties(pttool PROPERTIES LINKER_LANGUAGE CXX)

# aapgetlines executable
add_executable(aapgetlines
	./src/application/aapgetlines.cpp
	./src/filesink.cpp
	./src/edlfile.cpp
	./src/ptxedlstructure.cpp
	./src/helpers.cpp
)
set_target_properties(aapgetlines PROPERTIES LINKER_LANGUAGE CXX)

# ----------------------------------------------------------------------------|

# Linking configuration for executables
target_link_libraries(parsettml ${libfmt} ${libxmlpp})
target_link_libraries(pttool ${libptformat} ${libfmt})

# Move DLLs for Windows
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	add_custom_command(
		TARGET parsettml POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  
		"${libxmlpp_path}/bin/xml++-vc142-5.0-1.dll"     
		$<TARGET_FILE_DIR:parsettml>
	)
	add_custom_command(
		TARGET parsettml POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  
		"${libfmt_path}/lib/fmtd.dll"
		$<TARGET_FILE_DIR:parsettml>
	)
	add_custom_command(
		TARGET parsettml POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  
		"${libfmt_path}/lib/fmtd.dll"
		$<TARGET_FILE_DIR:parsettml>
	)
    add_custom_command(
		TARGET pttool POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  
		"${libptformat_path}/build/cmake/Debug/ptformatshared.dll"
		$<TARGET_FILE_DIR:pttool>
	)
    add_custom_command(
		TARGET pttool POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  
		"${libfmt_path}/lib/fmtd.dll"
		$<TARGET_FILE_DIR:pttool>
	)
endif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")

# Catch2 Tests
# add_executable(test_catch2 tests/catch2.cpp)
# target_link_libraries(test_catch2 PRIVATE Catch2::Catch2WithMain)
# catch_discover_tests(test_catch2)

if(NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Linux") # TODO: Configure Linux with Catch2
    add_executable(test_validatingnode tests/validatingnode.cpp)
    target_link_libraries(test_validatingnode PRIVATE Catch2::Catch2WithMain)
    catch_discover_tests(test_validatingnode)
endif(NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Linux")