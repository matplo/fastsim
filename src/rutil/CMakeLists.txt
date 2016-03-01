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
