project(GlauberMC CXX)
cmake_minimum_required(VERSION 2.8.11)

# indep. if root built with cmake assume the root-cint is in the path
execute_process ( COMMAND root-config --prefix WORKING_DIRECTORY /tmp OUTPUT_VARIABLE ROOT_DIR OUTPUT_STRIP_TRAILING_WHITESPACE )
#message ("[info] ROOT_DIR: ${ROOT_DIR}")
execute_process ( COMMAND root-config --etcdir WORKING_DIRECTORY /tmp OUTPUT_VARIABLE ROOT_ETCDIR OUTPUT_STRIP_TRAILING_WHITESPACE )
set( CMAKE_MODULE_PATH "${ROOT_ETCDIR}/cmake" )
#message ("[info] CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
find_package(ROOT REQUIRED Eg)

execute_process ( COMMAND pythia8-config --prefix WORKING_DIRECTORY /tmp OUTPUT_VARIABLE PYTHIA8_DIR OUTPUT_STRIP_TRAILING_WHITESPACE )
execute_process ( COMMAND pythia8-config --cxxflags WORKING_DIRECTORY /tmp OUTPUT_VARIABLE PYTHIA8_CXXFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE )
execute_process ( COMMAND pythia8-config --ldflags WORKING_DIRECTORY /tmp OUTPUT_VARIABLE PYTHIA8_LDFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE )
#execute_process ( COMMAND pythia8-config --includedir WORKING_DIRECTORY /tmp OUTPUT_VARIABLE PYTHIA8_INCDIR OUTPUT_STRIP_TRAILING_WHITESPACE )
#message( "PYTHIA8_INCDIR: ${PYTHIA8_INCDIR}")
message( "PYTHIA8_DIR: ${PYTHIA8_DIR}")
message( "PYTHIA8_CXXFLAGS: ${PYTHIA8_CXXFLAGS}")
message( "PYTHIA8_LDFLAGS: ${PYTHIA8_LDFLAGS}")

set(CMAKE_MACOSX_RPATH 1)

set(SRCS
	RndSource.cxx
	RndSource2D.cxx
)

set(SOURCES_EXE 
	deltaE.cxx
	util.cxx
	main.cxx
)

# Headers from sources
string(REPLACE ".cxx" ".h" HDRS "${SRCS}")

# generate dictionaries
include_directories( ${PROJECT_LIB} ${ROOT_INCLUDE_DIR} ${PROJECT_SOURCE_DIR} ${PYTHIA8_DIR}/include ${ROOT_INCLUDE_DIR} )

set(DICT ${PROJECT_NAME}_Dict )
set(LINKDEFS ${PROJECT_NAME}LinkDef.hh )
ROOT_GENERATE_DICTIONARY( ${DICT} ${HDRS} LINKDEF ${LINKDEFS} )

set ( PROJECT_LIB ${PROJECT_NAME} )
add_library( ${PROJECT_LIB} SHARED ${SRCS} ${HDRS} ${DICT}.cxx )
target_link_libraries( ${PROJECT_LIB} ${ROOT_LIBRARIES} ${PYTHIA8_LDFLAGS} )

set ( PROJECT_EXE ${PROJECT_NAME}.exe )
add_executable( ${PROJECT_EXE} ${SOURCES_EXE} )
target_link_libraries( ${PROJECT_EXE} ${PROJECT_LIB} ${ROOT_LIBRARIES} ${PYTHIA8_LDFLAGS} )


install(TARGETS ${PROJECT_EXE} ${PROJECT_LIB}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)
install(FILES ${HDRS} DESTINATION include)

install(FILES ${HEADERS_LIB} DESTINATION include)
