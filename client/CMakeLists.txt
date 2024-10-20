project(Naming_Service_Client)

add_executable(client client.cpp)

target_link_libraries(client libidl -lTAO_CosNaming -lTAO_Svc_Utils -lTAO_CosEvent_Skel -lTAO_CosEvent -lTAO_PortableServer -lTAO_AnyTypeCode -lTAO -lACE)
