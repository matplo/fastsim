project(AliGlauber CXX)
cmake_minimum_required(VERSION 2.8.11)

# indep. if root built with cmake assume the root-cint is in the path
execute_process ( COMMAND root-config --prefix WORKING_DIRECTORY /tmp OUTPUT_VARIABLE ROOT_DIR OUTPUT_STRIP_TRAILING_WHITESPACE )
#message ("[info] ROOT_DIR: ${ROOT_DIR}")
execute_process ( COMMAND root-config --etcdir WORKING_DIRECTORY /tmp OUTPUT_VARIABLE ROOT_ETCDIR OUTPUT_STRIP_TRAILING_WHITESPACE )
set( CMAKE_MODULE_PATH "${ROOT_ETCDIR}/cmake" )
#message ("[info] CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
find_package(ROOT REQUIRED Eg)

set(CMAKE_MACOSX_RPATH 1)

set(SRCS
	AliGlauberMC.cxx
	AliGlauberNucleus.cxx
	AliGlauberNucleon.cxx
)

# Headers from sources
string(REPLACE ".cxx" ".h" HDRS "${SRCS}")

# generate dictionaries
set(DICT ${PROJECT_NAME}_Dict )
set(LINKDEFS "${PROJECT_NAME}LinkDef.hh" )
#message("linkdef file is: ${LINKDEFS}")
# the dot below is needed for the ROOT_GENERATE_DICTIONARY
include_directories(${ROOT_INCLUDE_DIR} ${PROJECT_SOURCE_DIR})
# if root not build with cmake the following does not work
ROOT_GENERATE_DICTIONARY(${DICT} ${HDRS} LINKDEF ${LINKDEFS})
# workaround
#ADD_CUSTOM_COMMAND(
#    OUTPUT ${DICT}.cxx
#    COMMAND ${ROOTCINT_EXECUTABLE} -f ${DICT}.cxx -c ${HDRS} ${LINKDEFS}
#    DEPENDS ${HDRS} )
#message ("[info] ${DICT} ${ROOTCINT_EXECUTABLE}")

link_libraries(${ROOT_LIBRARIES})
add_library(${PROJECT_NAME} SHARED ${SRCS} ${HDRS} ${DICT}.cxx)

install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib)
install(FILES ${HDRS} DESTINATION include)
