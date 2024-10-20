cmake_minimum_required(VERSION 3.10)
project(Naming_Service_Server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED ENV{ACE_ROOT})
    message(FATAL_ERROR "ACE_ROOT environment variable is not set")
endif()

if(NOT DEFINED ENV{P_ROOT})
    message(FATAL_ERROR "P_ROOT environment variable is not set")
endif()

set(ACE_ROOT $ENV{ACE_ROOT})
set(TAO_ROOT ${ACE_ROOT}/TAO)
set(P_ROOT $ENV{P_ROOT})

include_directories(${ACE_ROOT}
                    ${ACE_ROOT}/ace
                    ${TAO_ROOT}
                    ${TAO_ROOT}/orbsvcs)

link_directories(${ACE_ROOT}/lib 
                 ${TAO_ROOT}/lib)

set(IDL_FILE_Quoter ${P_ROOT}/idl/Quoter.idl)
set(IDL_OUTPUT_DIR  ${P_ROOT}/server/idlgen )

set(GENERATED_SOURCES ${IDL_OUTPUT_DIR}/QuoterC.cpp 
                      ${IDL_OUTPUT_DIR}/QuoterS.cpp 
                      
                      ${IDL_OUTPUT_DIR}/QuoterC.h 
                      ${IDL_OUTPUT_DIR}/QuoterS.h
                      
                      ${IDL_OUTPUT_DIR}/QuoterC.inl
)

add_custom_command(
  OUTPUT ${GENERATED_SOURCES}
  COMMAND ${ACE_ROOT}/bin/tao_idl -o ${IDL_OUTPUT_DIR} -Cw ${IDL_FILE_Quoter}
  DEPENDS ${IDL_FILE_Quoter}
  COMMENT "Running tao_idl on ${IDL_FILE_Quoter} and generating files in ${IDL_OUTPUT_DIR}")
 
add_executable(server server.cpp 
                      ${IDL_OUTPUT_DIR}/QuoterC.cpp 
                      ${IDL_OUTPUT_DIR}/QuoterS.cpp 
                      Stock_Factory_i.cpp 
                      Stock_i.cpp)

target_link_libraries(server -lTAO_CosNaming -lTAO_Svc_Utils -lTAO_PortableServer -lTAO_AnyTypeCode -lTAO -lACE)
 