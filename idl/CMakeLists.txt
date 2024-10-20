project(Naming_Service_Idl)

set(IDL_FILE_Quoter ${P_ROOT}/idl/Quoter.idl)

set(IDL_OUTPUT_DIR  ${P_ROOT}/idlgen)

set(GENERATED_SOURCES ${IDL_OUTPUT_DIR}/QuoterC.cpp 
                      ${IDL_OUTPUT_DIR}/QuoterS.cpp 
                      ${IDL_OUTPUT_DIR}/QuoterC.h 
                      ${IDL_OUTPUT_DIR}/QuoterS.h
                      ${IDL_OUTPUT_DIR}/QuoterC.inl
)

execute_process(COMMAND ${ACE_ROOT}/bin/tao_idl -o ${IDL_OUTPUT_DIR} -Cw ${IDL_FILE_Quoter})


add_library(libidl SHARED ${GENERATED_SOURCES})
target_link_libraries(libidl TAO_PortableServer)