project(Naming_Service_Server)
 
add_executable(server server.cpp 
                      Stock_Factory_i.cpp 
                      Stock_i.cpp)

target_link_libraries(server libidl -lTAO_CosNaming -lTAO_Svc_Utils -lTAO_PortableServer -lTAO_AnyTypeCode -lTAO -lACE)
 