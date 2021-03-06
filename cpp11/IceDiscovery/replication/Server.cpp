// **********************************************************************
//
// Copyright (c) 2003-2018 ZeroC, Inc. All rights reserved.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <HelloI.h>

using namespace std;

class Server : public Ice::Application
{
public:

    virtual int run(int argc, char* argv[]) override;
};

int
main(int argc, char* argv[])
{
#ifdef ICE_STATIC_LIBS
    Ice::registerIceSSL();
    Ice::registerIceDiscovery(false);
#endif
    Server app;
    int status = app.main(argc, argv);
    return status;
}

int
Server::run(int argc, char*[])
{
    if(argc > 1)
    {
        cerr << appName() << ": too many arguments" << endl;
        return EXIT_FAILURE;
    }

    auto properties = communicator()->getProperties();
    auto adapter = communicator()->createObjectAdapter("Hello");
    auto id = Ice::stringToIdentity("hello");
auto hello = make_shared<HelloI>(properties->getProperty("Ice.ProgramName"));
    adapter->add(hello, id);
    adapter->activate();
    communicator()->waitForShutdown();
    return EXIT_SUCCESS;
}
