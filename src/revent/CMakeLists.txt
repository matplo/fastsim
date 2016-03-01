set(SOURCES_LIB
	header.cxx 
	revent.cxx
)

set(NAME_LIB revent)

# Headers from sources
string(REPLACE ".cxx" ".h" HEADERS_LIB "${SOURCES_LIB}")

# generate dictionaries
set(DICT ${NAME_LIB}_Dict )

set(LINKDEFS "${NAME_LIB}_LinkDef.h" )

add_library(${NAME_LIB} SHARED ${SOURCES_LIB})
target_include_directories(${NAME_LIB} PUBLIC ${ROOT_INCLUDE_DIR} ${FASTJET_DIR}/include ${PYTHIA8_DIR}/include)
target_link_libraries(${NAME_LIB} ${PYTHIA8_LDFLAGS} ${FASTJET_LIBS} ${ROOT_LIBRARIES})

install(TARGETS ${NAME_LIB} LIBRARY DESTINATION lib COMPONENT library)
install(FILES ${HEADERS_LIB} DESTINATION include)
