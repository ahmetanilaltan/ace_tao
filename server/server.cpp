
#include "Stock_Factory_i.h"
#include "orbsvcs/CosNamingC.h"
#include "ace/streams.h"

int ACE_TMAIN (int argc, ACE_TCHAR* argv[])
{
  try {
    CORBA::ORB_var orb = CORBA::ORB_init (argc, argv);
    
    CORBA::Object_var poa_object = orb->resolve_initial_references ("RootPOA");
    
    PortableServer::POA_var poa = PortableServer::POA::_narrow (poa_object.in ());
    PortableServer::POAManager_var poa_manager = poa->the_POAManager ();
    
    poa_manager->activate ();

    Quoter_Stock_Factory_i stock_factory_i;
    Quoter::Stock_Factory_var stock_factory = stock_factory_i._this ();

    CORBA::Object_var naming_context_object = orb->resolve_initial_references ("NameService");
    CosNaming::NamingContext_var naming_context = CosNaming::NamingContext::_narrow (naming_context_object.in ());

    CosNaming::Name name (1);
    name.length (1);
    name[0].id = CORBA::string_dup ("Stock_Factory");

    naming_context->bind (name, stock_factory.in ());

    orb->run ();

    poa->destroy (true, true);
    orb->destroy ();
  }
  catch (const CORBA::Exception &) {
    cerr << "CORBA exception raised!" << endl;
  }
  return 0;
}
