project(wrapper CXX)
cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_MACOSX_RPATH 1)

set(SOURCES_LIB
	wrapper.cxx
)

set(SOURCES_EXE main.cxx)

# Headers from sources
string(REPLACE ".cxx" ".h" HEADERS_LIB "${SOURCES_LIB}")
string(REPLACE ".cxx" ".h" HEADERS_EXE "${SOURCES_EXE}")

set(FASTSIMLIBS "-L$ENV{FASTSIM}/lib")
set(FASTSIMINCLUDES $ENV{FASTSIM}/include)

set(PROJECT_LIB "${PROJECT_NAME}")
add_library(${PROJECT_LIB} SHARED ${SOURCES_LIB})
target_include_directories(${PROJECT_LIB} PUBLIC ${FASTSIMINCLUDES})  
target_link_libraries(${PROJECT_LIB})

set(PROJECT_EXE "${PROJECT_NAME}-test")
add_executable(${PROJECT_EXE} ${SOURCES_EXE})
#target_include_directories(${PROJECT_NAME} PUBLIC ${FASTSIMINCLUDES})  
target_link_libraries( ${PROJECT_EXE} ${PROJECT_LIB} )

install(TARGETS ${PROJECT_EXE} RUNTIME DESTINATION bin)
install(TARGETS ${PROJECT_LIB} LIBRARY DESTINATION lib COMPONENT library)

install(FILES ${HEADERS_LIB} DESTINATION include)
