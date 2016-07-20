set(SOURCES_LIB
    target.cxx
    py8partongun.cxx
    hfgun.cxx
)

set(NAME_LIB pgun)

# Headers from sources
string(REPLACE ".cxx" ".h" HEADERS_LIB "${SOURCES_LIB}")

# generate dictionaries
set(DICT ${NAME_LIB}_Dict )

set(LINKDEFS "${NAME_LIB}_LinkDef.h" )

# for cint to find the LinkDef 
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(${NAME_LIB} SHARED ${SOURCES_LIB} ${DICT}.cxx)
target_include_directories(${NAME_LIB} PUBLIC ${PYTHIA8_DIR}/include ${ROOT_INCLUDE_DIR} )
ROOT_GENERATE_DICTIONARY(${DICT} ${HEADERS_LIB} LINKDEF ${LINKDEFS})
target_link_libraries(${NAME_LIB} ${PYTHIA8_LDFLAGS} ${ROOT_LIBRARIES})

install(TARGETS ${NAME_LIB} LIBRARY DESTINATION lib COMPONENT library)
install(FILES ${HEADERS_LIB} DESTINATION include)
