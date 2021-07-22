cmake_minimum_required(VERSION 3.18)
project(edltools VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

# Project include directories
include_directories(
    include
)

# Platform dependencies for MacOS
message(STATUS "Building for platform: ${CMAKE_SYSTEM_NAME}")
if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    include_directories(
        /usr/local/include/libxmlpp
        /usr/local/include/fmt
		/usr/local/include/magicenum
		/usr/local/include/libtimecode/src/timecode
    )
	
    find_library(LIBXMLPP NAMES libxml++-5.0.1.dylib PATHS /usr/local/lib)
    set(libxmlpp ${LIBXMLPP})

    # find_library(LIBFMT NAMES libfmtd.dylib PATHS /usr/local/lib)
    find_library(LIBFMT NAMES libfmtd.a PATHS /usr/local/lib)
    set(libfmt ${LIBFMT})

	set(libtimecode_src /usr/local/include/libtimecode/src/timecode.c)

elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	# Fetch dependency paths and store in variables
	file(TO_CMAKE_PATH $ENV{LIBXMLPP_PATH} libxmlpp_path)
	file(TO_CMAKE_PATH $ENV{LIBFMT_PATH} libfmt_path)
	file(TO_CMAKE_PATH $ENV{LIBMAGICENUM_PATH} libmagicenum_path)
	file(TO_CMAKE_PATH $ENV{LIBTIMECODE_PATH} libtimecode_path)
	message(STATUS ${libxmlpp_path})
	message(STATUS ${libfmt_path})

	include_directories(
		${libxmlpp_path}/include/libxml++-5.0
		${libfmt_path}/include
		${libmagicenum_path}/include
		${libtimecode_path}/src/timecode
	)

	find_library(LIBFMT NAMES fmtd.lib PATHS ${libfmt_path}/lib)
	set(libfmt ${LIBFMT})

	find_library(LIBXMLPP NAMES xml++-vc142-5.0.lib PATHS ${libxmlpp_path}/lib)
	set(libxmlpp ${LIBXMLPP})
	
	set(libtimecode_src ${libtimecode_path}/src/timecode.c)
	
endif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")

# Executable for edltool
add_executable(edltool
    ./src/filesink.cpp
    ./src/xmlfile.cpp
    ./src/edlfile.cpp
    ./src/ptxedlstructure.cpp
    ./src/helpers.cpp
    ./src/edltool.cpp
	./src/versions.cpp
	./src/node.cpp
	${libtimecode_src}
)
set_target_properties(edltool PROPERTIES LINKER_LANGUAGE CXX)

# add_custom_command(
# 	TARGET edltool PRE_BUILD
# 	COMMAND "./scripts/hashdictionary.sh"
# )

if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
# set_target_properties(edltool PROPERTIES COMPILE_FLAGS "-fsanitize=address" LINK_FLAGS "-fsanitize=address") # Configure this more appropriately
# set_target_properties(edltool PROPERTIES COMPILE_FLAGS) # Configure this more appropriately
target_link_libraries(edltool ${libfmt} ${libxmlpp})

elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
target_link_libraries(edltool ${libfmt} ${libxmlpp})

endif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
add_custom_command(
	TARGET edltool POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different  
	"${libxmlpp_path}/bin/xml++-vc142-5.0-1.dll"      
	$<TARGET_FILE_DIR:edltool>
)
add_custom_command(
	TARGET edltool POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different  
	"${libfmt_path}/lib/fmtd.dll"      
	$<TARGET_FILE_DIR:edltool>
)
add_custom_command(
	TARGET edltool POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different  
	"${libfmt_path}/lib/fmtd.dll"      
	$<TARGET_FILE_DIR:edltool>
)
endif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")

# add_executable(xmltest
#     ./src/examples/xmlexample.cpp
# )
# target_link_libraries(xmltest PUBLIC ${libxml})