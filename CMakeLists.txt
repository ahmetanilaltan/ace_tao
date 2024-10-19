cmake_minimum_required(VERSION 3.10)
project(Naming_Service)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ortam değişkeni ACE_ROOT'u CMake'e aktar
if(NOT DEFINED ENV{ACE_ROOT})
    message(FATAL_ERROR "ACE_ROOT environment variable is not set")
endif()

set(ACE_ROOT $ENV{ACE_ROOT})
set(TAO_ROOT ${ACE_ROOT}/TAO)

include_directories(${ACE_ROOT}
                    ${ACE_ROOT}/ace
                    ${TAO_ROOT}
                    ${TAO_ROOT}/orbsvcs)

link_directories(${ACE_ROOT}/lib 
                 ${TAO_ROOT}/lib)

# IDL dosyasını tao_idl ile derle
set(IDL_FILE ${CMAKE_SOURCE_DIR}/idl/Quoter.idl)
set(IDL_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/idl)

set(GENERATED_SOURCES ${IDL_OUTPUT_DIR}/QuoterC.cpp 
                      ${IDL_OUTPUT_DIR}/QuoterS.cpp 

                      ${IDL_OUTPUT_DIR}/QuoterC.h 
                      ${IDL_OUTPUT_DIR}/QuoterS.h
                      
                      ${IDL_OUTPUT_DIR}/QuoterC.inl
                      
                      ${IDL_OUTPUT_DIR}/QuoterS_T.cpp
                      ${IDL_OUTPUT_DIR}/QuoterS_T.h)

add_custom_command(
  OUTPUT ${GENERATED_SOURCES}
  COMMAND ${ACE_ROOT}/bin/tao_idl -o ${IDL_OUTPUT_DIR} -Cw ${IDL_FILE}
  DEPENDS ${IDL_FILE}
  COMMENT "Running tao_idl on ${IDL_FILE} and generating files in ${IDL_OUTPUT_DIR}")

# Sunucu için derleme
add_executable(server server.cpp 
                      ${IDL_OUTPUT_DIR}/QuoterC.cpp 
                      ${IDL_OUTPUT_DIR}/QuoterS.cpp 
                      Stock_Factory_i.cpp 
                      Stock_i.cpp)

target_link_libraries(server -lTAO_CosNaming -lTAO_Svc_Utils -lTAO_PortableServer -lTAO_AnyTypeCode -lTAO -lACE)

# İstemci için derleme
add_executable(client client.cpp ${IDL_OUTPUT_DIR}/QuoterC.cpp)
target_link_libraries(client -lTAO_CosNaming -lTAO_Svc_Utils -lTAO_CosEvent_Skel -lTAO_CosEvent -lTAO_PortableServer -lTAO_AnyTypeCode -lTAO -lACE)
