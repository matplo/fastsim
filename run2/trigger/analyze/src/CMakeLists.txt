# Fast simulation tool for the DETECTOR response based on ALICE data
# Detector system
# Copyright (C) 2015 Xiaoming Zhang ALICE Collaboration
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
project(Analyze CXX)
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
	readtree.cxx
	analysis.cxx
	rstructures.cxx
)

# Headers from sources
string(REPLACE ".cxx" ".h" HDRS "${SRCS}")

# generate dictionaries
set(DICT ${PROJECT_NAME}_Dict )
set(LINKDEFS "${PROJECT_NAME}LinkDef.h" )
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

set(R2LIBS "-L$ENV{RUN2EMCTRIGGER}/lib" -lR2Util )
link_libraries(${ROOT_LIBRARIES} ${R2LIBS})
add_library(${PROJECT_NAME} SHARED ${SRCS} ${HDRS} ${DICT}.cxx)

set(EXEC1 filter_single_entries)
set(SOURCES_EXE "${EXEC1}.cxx")
add_executable(${EXEC1} ${SOURCES_EXE})
target_include_directories(${EXEC1} PUBLIC "${ROOT_INCLUDE_DIR}")  
target_link_libraries(${EXEC1} ${ROOT_LIBRARIES})

#install(TARGETS ${PROJECT_NAME}
#        RUNTIME DESTINATION bin)

install(TARGETS ${PROJECT_NAME} ${EXEC1}
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)
install(FILES ${HDRS} DESTINATION include)
