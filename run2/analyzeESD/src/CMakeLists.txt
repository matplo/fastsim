project(AnalyzeESD CXX)
cmake_minimum_required(VERSION 2.8.11)

# indep. if root built with cmake assume the root-cint is in the path
execute_process ( COMMAND root-config --prefix WORKING_DIRECTORY /tmp OUTPUT_VARIABLE ROOT_DIR OUTPUT_STRIP_TRAILING_WHITESPACE )
#message ("[info] ROOT_DIR: ${ROOT_DIR}")
execute_process ( COMMAND root-config --etcdir WORKING_DIRECTORY /tmp OUTPUT_VARIABLE ROOT_ETCDIR OUTPUT_STRIP_TRAILING_WHITESPACE )
set( CMAKE_MODULE_PATH "${ROOT_ETCDIR}/cmake" )
#message ("[info] CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
find_package(ROOT REQUIRED Eg)

execute_process ( COMMAND fastjet-config --prefix WORKING_DIRECTORY /tmp OUTPUT_VARIABLE FASTJET_DIR OUTPUT_STRIP_TRAILING_WHITESPACE )
execute_process ( COMMAND fastjet-config --cxxflags WORKING_DIRECTORY /tmp OUTPUT_VARIABLE FASTJET_CXXFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE )
execute_process ( COMMAND fastjet-config --libs --plugins WORKING_DIRECTORY /tmp OUTPUT_VARIABLE FASTJET_LIBS OUTPUT_STRIP_TRAILING_WHITESPACE )
message( "FASTJET_DIR: ${FASTJET_DIR}")
message( "FASTJET_CXXFLAGS: ${FASTJET_CXXFLAGS}")
message( "FASTJET_LIBS: ${FASTJET_LIBS}")

set(CMAKE_MACOSX_RPATH 1)

set(ASRCS
	AliAnalysisM.cxx
)

# Headers from sources
string(REPLACE ".cxx" ".h" AHDRS "${ASRCS}")

set(RSRCS
	CaloVector.cxx
)
# Headers from sources
string(REPLACE ".cxx" ".h" RHDRS "${RSRCS}")

set(SRCS
	${RSRCS}
	${ASRCS}
	REvent.cxx
)
# Headers from sources
string(REPLACE ".cxx" ".h" HDRS "${SRCS}")

include_directories(${ROOT_INCLUDE_DIR} 
	${FASTJET_DIR}/include 
	$ENV{ALICE_PHYSICS}/include 
	$ENV{ALICE_ROOT}/include 
	$ENV{RUN2AESDDIR}/include
	${PROJECT_SOURCE_DIR})

set(ALILIBS -L$ENV{ALICE_ROOT}/lib -L$ENV{ALICE_PHYSICS}/lib )
link_libraries(${ROOT_LIBRARIES} 
	${ALILIBS} 
	${FASTJET_LIBS} 
	-L$ENV{RUN2AESDDIR}/lib -lEMCALTriggerFast)

# generate dictionaries
set(RDICT "R${PROJECT_NAME}_Dict" )
set(RLINKDEFS "R${PROJECT_NAME}LinkDef.hh" )
ROOT_GENERATE_DICTIONARY(${RDICT} ${RHDRS} LINKDEF ${RLINKDEFS} OPTIONS )
add_library("R${PROJECT_NAME}" SHARED ${RSRCS} ${RHDRS} ${RDICT}.cxx)

# generate dictionaries
set(DICT ${PROJECT_NAME}_Dict )
set(LINKDEFS "${PROJECT_NAME}LinkDef.hh" )
ROOT_GENERATE_DICTIONARY(${DICT} ${AHDRS} LINKDEF ${LINKDEFS} OPTIONS )
add_library(${PROJECT_NAME} SHARED ${SRCS} ${HDRS} ${DICT}.cxx)

#set(EXEC1 filter_single_entries)
#set(SOURCES_EXE "${EXEC1}.cxx")
#add_executable(${EXEC1} ${SOURCES_EXE})
#target_include_directories(${EXEC1} PUBLIC "${ROOT_INCLUDE_DIR}")  
#target_link_libraries(${EXEC1} ${ROOT_LIBRARIES})

#install(TARGETS ${PROJECT_NAME}
#        RUNTIME DESTINATION bin)

install(TARGETS ${PROJECT_NAME} R${PROJECT_NAME} #${EXEC1}
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)
install(FILES ${HDRS} DESTINATION include)
