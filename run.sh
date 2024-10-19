#!/bin/bash

# İsim servisini başlat
$TAO_ROOT/orbsvcs/Naming_Service/tao_cosnaming -m 1 -ORBListenEndpoints iiop://localhost:12345 -o $P_ROOT/ns.ior

# Olay kanalını başlat
$TAO_ROOT/orbsvcs/Event_Service/tao_rtevent -ORBInitRef NameService=file://$P_ROOT/ns.ior

tao_nslist
$TAO_ROOT/utils/nslist/tao_nslist -ORBInitRef NameService=file://$P_ROOT/ns.ior