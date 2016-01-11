FILE (GLOB_RECURSE samples_SRCS *.cpp *.cxx *.cc *.C *.c *.h *.hpp)

#SET (project_LIBS ${Boost_LIBRARIES} ${QT_LIBRARIES} ${Log4Cxx_LIBRARIES})
SET (samples_BIN "SAMPLES_${PROJECT_NAME}")

add_executable(${samples_BIN} ${samples_SRCS} ${samples_MOC_SRCS_GENERATED})
TARGET_LINK_LIBRARIES(${samples_BIN} ${PROJECT_NAME})

#INSTALL(TARGETS ${project_BIN} DESTINATION bin)

#
# Add third lib FIRST
#
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)

# if(MSVC)
	# TARGET_LINK_LIBRARIES( ${project_BIN} 
		# ${THIRD_FIRST_SRC}/lib/${CMAKE_CFG_INTDIR}/${THIRD_FIRST_NAME}.lib)
# else()
	# TARGET_LINK_LIBRARIES(${project_BIN} ${THIRD_FIRST_NAME})
# endif()
