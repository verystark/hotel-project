#include "cli.hh"
#include "hotel.hh"
#include <string>
#include <memory>

using namespace std;

const string PROMPT = "Hotel> ";

int main()
{
    shared_ptr<Hotel> hotel = make_shared<Hotel>();
    if ( !hotel->init() )
    {
        return EXIT_FAILURE;
    }

    Cli cli(hotel, PROMPT);
    while ( cli.exec() );

    return EXIT_SUCCESS;
}
