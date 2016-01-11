#
# (G)Test project
#
# nedjapejasinovic@gmail.com
# 
# Downloading or just include GTest and GMosck
# lib targets to 'test' target
#
# downloading if GTEST_DOWNLOAD_GTEST_AND_GMOCK option is true
# or use GTEST_GMOCK_DIR and GTEST_DIR cache path options
#
# (Troubleshoot):
# Problem with linking testing lib posible:
#	Change that library Code Generation > Runtime library to
# 	/MT for release and /MTd for debug
#	or in cmake file after library target added put next lines
#	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
#	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
#	just like is 'test' created
#

#
# Project include
# include headers of library that write tests
set(PROJECT_INCLUDE ${CMAKE_SOURCE_DIR}/include)

#
# Target sources
set(test_INC )
set(test_SRC 
	gtest_main.cc 
)

#
# Add 'test' executable
#
add_executable(test ${test_SRC} ${test_INC})
#configure them
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")



if(GTEST_DOWNLOAD_GTEST_AND_GMOCK)
	# Download gtest and gmock packages
	#
	find_package(Threads REQUIRED)
	# Enable ExternalProject CMake module
	include(ExternalProject)
	# Download and install GoogleTest
	ExternalProject_Add(
		gtest
		URL https://googletest.googlecode.com/files/gtest-1.7.0.zip
		PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
		# Disable install step
		INSTALL_COMMAND ""
	)
	# Set gtest properties
	ExternalProject_Get_Property(gtest source_dir binary_dir)
	set_target_properties(test PROPERTIES
		"IMPORTED_LOCATION" "${binary_dir}/libgtest.a"
		"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
	#    "INTERFACE_INCLUDE_DIRECTORIES" "${source_dir}/include"
	)
	# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
	include_directories("${source_dir}/include")
	# Download and install GoogleMock
	ExternalProject_Add(
		gmock
		URL https://googlemock.googlecode.com/files/gmock-1.7.0.zip
		PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gmock
		# Disable install step
		INSTALL_COMMAND ""
	)
	# Create a libgmock target to be used as a dependency by test programs
	add_library(libgmock IMPORTED STATIC GLOBAL)
	add_dependencies(libgmock gmock)
	# Set gmock properties
	ExternalProject_Get_Property(gmock source_dir binary_dir)
	set_target_properties(libgmock PROPERTIES
		"IMPORTED_LOCATION" "${binary_dir}/libgmock.a"
		"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
	#    "INTERFACE_INCLUDE_DIRECTORIES" "${source_dir}/include"
	)
else()
	# For manual paths
	#
	# Add GTest project target
	add_subdirectory(${GTEST_GMOCK_DIR})
	# Include GTest headers
	include_directories(test ${GTEST_DIR}/include)
endif()

#######################################################################################
#
# Configure target
#

# i couldn't make it work with interface_include_directories
include_directories("${source_dir}/include")


# Include library that you testing headers
include_directories(test ${PROJECT_INCLUDE})

# todo: delete if not necessary
# include gmock headers to project 'test'
include_directories(test ${CMAKE_CURRENT_BINARY_DIR}/gmock/src/gmock/include)

# 
# Link GTest libs
#
if(GTEST_DOWNLOAD_GTEST_AND_GMOCK)
	# If downloading link gtest libs to 'test' target
	#
	if(MSVC)
		# win
		TARGET_LINK_LIBRARIES(test ${CMAKE_CURRENT_BINARY_DIR}/gmock/src/gmock-build/${CMAKE_CFG_INTDIR}/gmock.lib)
		TARGET_LINK_LIBRARIES(test ${CMAKE_CURRENT_BINARY_DIR}/gmock/src/gmock-build/${CMAKE_CFG_INTDIR}/gmock_main.lib)
	else()
		# linux
		TARGET_LINK_LIBRARIES(test libgmock)
		#TARGET_LINK_LIBRARIES(tests ${CMAKE_CURRENT_BINARY_DIR}/gmock/src/gmock-build/libmock_main.a)
	endif()
else()
	# If manual find gtest project paths
	#
	if(MSVC)
		# win
		target_link_libraries(test ${LIBRARY_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}/gmock.lib)
	else()
		# linux
		target_link_libraries(test gmock)
	endif()
endif()

# 
# Link testing library
#
if(MSVC)
	# win
	target_link_libraries(test "${LIBRARY_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}/${PROJECT_NAME}.lib")
else()
	# linux
	TARGET_LINK_LIBRARIES(test ${PROJECT_NAME})
	#TARGET_LINK_LIBRARIES(tests ${CMAKE_CURRENT_BINARY_DIR}/gmock/src/gmock-build/libmock_main.a)
endif()