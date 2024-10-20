project(Naming_Service_Server)
 
add_executable(server server.cpp 
                      ${IDL_OUTPUT_DIR}/QuoterC.cpp 
                      ${IDL_OUTPUT_DIR}/QuoterS.cpp 
                      Stock_Factory_i.cpp 
                      Stock_i.cpp)

target_link_libraries(server -lTAO_CosNaming -lTAO_Svc_Utils -lTAO_PortableServer -lTAO_AnyTypeCode -lTAO -lACE)
 