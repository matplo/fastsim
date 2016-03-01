set(SOURCES_LIB
	fjwrapper.cxx
)

set(NAME_LIB fjwrapper)

# Headers from sources
string(REPLACE ".cxx" ".h" HEADERS_LIB "${SOURCES_LIB}")

add_library(${NAME_LIB} SHARED ${SOURCES_LIB})
target_include_directories(${NAME_LIB} PUBLIC ${FASTJET_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/wrapper )  
target_link_libraries(${NAME_LIB} ${FASTJET_LIBS})

install(TARGETS ${NAME_LIB} LIBRARY DESTINATION lib)

install(FILES ${HEADERS_LIB} DESTINATION include)

