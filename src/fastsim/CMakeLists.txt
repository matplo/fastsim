# indep. if root built with cmake assume the root-cint is in the path
execute_process ( COMMAND root-config --prefix WORKING_DIRECTORY /tmp OUTPUT_VARIABLE ROOT_DIR OUTPUT_STRIP_TRAILING_WHITESPACE )
#message ("[info] ROOT_DIR: ${ROOT_DIR}")
execute_process ( COMMAND root-config --etcdir WORKING_DIRECTORY /tmp OUTPUT_VARIABLE ROOT_ETCDIR OUTPUT_STRIP_TRAILING_WHITESPACE )
set( CMAKE_MODULE_PATH "${ROOT_ETCDIR}/cmake" )
#message ("[info] CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
find_package(ROOT REQUIRED EG)

execute_process ( COMMAND root-config --libs WORKING_DIRECTORY /tmp OUTPUT_VARIABLE ROOT_LIBS OUTPUT_STRIP_TRAILING_WHITESPACE )

if(DEFINED ROOT_USE_FILE) 
  include(${ROOT_USE_FILE}) 
else() 
  include_directories(${ROOT_INCLUDE_DIRS}) 
endif() 

set(SOURCES_LIB
	util.cxx
	#toymcpy8.cxx
	header.cxx
	revent.cxx
	pythia_run.cxx
)

set(SOURCES_EXE main.cxx)

# Headers from sources
string(REPLACE ".cxx" ".h" HEADERS_LIB "${SOURCES_LIB}")
string(REPLACE ".cxx" ".h" HEADERS_EXE "${SOURCES_EXE}")

set(PROJECT_UTIL_LIB "${PROJECT_NAME}util")
add_library(${PROJECT_UTIL_LIB} SHARED ${SOURCES_LIB})
target_include_directories(${PROJECT_UTIL_LIB} PUBLIC ${ROOT_INCLUDE_DIR} ${FASTJET_DIR}/include ${PYTHIA8_DIR}/include)  
target_link_libraries(${PROJECT_UTIL_LIB} ${PYTHIA8_LDFLAGS} ${FASTJET_LIBS} ${ROOT_LIBRARIES} fjwrapper rutil wrapper)

add_executable(${PROJECT_NAME} ${SOURCES_EXE})
target_include_directories(${PROJECT_NAME} PUBLIC ${ROOT_INCLUDE_DIR} ${FASTJET_DIR}/include ${PYTHIA8_DIR}/include)  
target_link_libraries( ${PROJECT_NAME} ${PROJECT_UTIL_LIB})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

install(TARGETS ${PROJECT_UTIL_LIB} LIBRARY DESTINATION lib)

install(FILES ${HEADERS_LIB} DESTINATION include)
