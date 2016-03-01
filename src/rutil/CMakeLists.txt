find_package(Boost REQUIRED math_c99)
if (BOOST-NOTFOUND)
	message(SEND_ERROR "Boost or one of the components not found. Will not compile ${EXE_NAME}")
endif (BOOST-NOTFOUND)

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
	rutil.cxx
)

set(NAME_LIB rutil)

# Headers from sources
string(REPLACE ".cxx" ".h" HEADERS_LIB "${SOURCES_LIB}")

# generate dictionaries
set(DICT ${NAME_LIB}_Dict )

set(LINKDEFS "${NAME_LIB}_LinkDef.h" )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../${NAME_LIB} ${Boost_INCLUDE_DIR} ${ROOT_INCLUDE_DIR})

ROOT_GENERATE_DICTIONARY(${DICT} ${HEADERS_LIB} LINKDEF ${LINKDEFS})

add_library(${NAME_LIB} SHARED ${SOURCES_LIB} ${DICT}.cxx)
target_link_libraries(${NAME_LIB} ${ROOT_LIBRARIES} ${Boost_LIBRARIES})

install(TARGETS ${NAME_LIB} LIBRARY DESTINATION lib COMPONENT library)
install(FILES ${HEADERS_LIB} DESTINATION include)
