cmake_minimum_required(VERSION 3.10)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED ENV{ACE_ROOT})
    message(FATAL_ERROR "ACE_ROOT environment variable is not set")
endif()

if(NOT DEFINED ENV{P_ROOT})
    message(FATAL_ERROR "P_ROOT environment variable is not set")
endif()

set(ACE_ROOT $ENV{ACE_ROOT} )
set(TAO_ROOT ${ACE_ROOT}/TAO)
set(P_ROOT   $ENV{P_ROOT}   )


include_directories(${ACE_ROOT}
                    ${ACE_ROOT}/ace
                    ${TAO_ROOT}
                    ${TAO_ROOT}/orbsvcs
                    ${P_ROOT}/idlgen
)

link_directories(${ACE_ROOT}/lib 
                 ${TAO_ROOT}/lib
                 ${P_ROOT}/lib
)

file(MAKE_DIRECTORY ${P_ROOT}/bin)
file(MAKE_DIRECTORY ${P_ROOT}/lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${P_ROOT}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${P_ROOT}/lib)

project(MainProject)

add_subdirectory(idl/)
add_subdirectory(client/)
#add_subdirectory(server/)
