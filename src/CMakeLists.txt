FILE (GLOB_RECURSE project_SRCS *.cpp *.cxx *.cc *.C *.c *.h *.hpp)
set(headers
	${PROJECT_SOURCE_DIR}/include/lib.h
)
#SET (project_LIBS ${Boost_LIBRARIES} ${QT_LIBRARIES} ${Log4Cxx_LIBRARIES})
SET (project_BIN ${PROJECT_NAME})

add_library(${project_BIN} ${project_SRCS} ${project_MOC_SRCS_GENERATED} ${headers})
#TARGET_LINK_LIBRARIES(${project_BIN} ${project_LIBS})
SET_TARGET_PROPERTIES(${project_BIN} PROPERTIES VERSION "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}" OUTPUT_NAME ${project_BIN} CLEAN_DIRECT_OUTPUT 1)

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
