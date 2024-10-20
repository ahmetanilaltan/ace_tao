
#include "idlgen/QuoterC.h"
#include <orbsvcs/CosNamingC.h>
#include "ace/streams.h"

int ACE_TMAIN (int argc, ACE_TCHAR* argv[])
{
  try {
    CORBA::ORB_var orb = CORBA::ORB_init (argc, argv);

    if (argc < 2) {
      cerr << "Usage: " << argv[0] << "symbol symbol..." << endl;
      return 1;
    }

    CORBA::Object_var naming_context_object = orb->resolve_initial_references ("NameService");
    CosNaming::NamingContext_var naming_context = CosNaming::NamingContext::_narrow (naming_context_object.in ());

    CosNaming::Name name (1);
    name.length (1);
    name[0].id = CORBA::string_dup ("Stock_Factory");

    CORBA::Object_var factory_object = naming_context->resolve (name);

    Quoter::Stock_Factory_var factory = Quoter::Stock_Factory::_narrow (factory_object.in ());

    for (int i = 1; i != argc; ++i) {
      try {
        Quoter::Stock_var stock = factory->get_stock (ACE_TEXT_ALWAYS_CHAR (argv[i]));

        CORBA::String_var full_name = stock->full_name ();

        CORBA::Double price = stock->price ();

        cout << "The price of a stock in \""
             << full_name.in () << "\" is $"
             << price << endl;
      }
      catch (Quoter::Invalid_Stock_Symbol &) {
        cerr << "Invalid stock symbol <"
             << argv[i] << ">" << endl;
      }
    }

    orb->destroy ();
  }
  catch (const CORBA::Exception &) {
    cerr << "CORBA exception raised!" << endl;
  }
  return 0;
}
