// **********************************************************************
//
// Copyright (c) 2003-2017 ZeroC, Inc. All rights reserved.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <FilesystemI.h>

using namespace std;
using namespace Filesystem;
using namespace FilesystemI;

class FilesystemApp : public Ice::Application
{
public:

    virtual int run(int, char*[])
    {
        //
        // Terminate cleanly on receipt of a signal
        //
        shutdownOnInterrupt();

        //
        // Create an object adapter.
        //
        Ice::ObjectAdapterPtr adapter =
            communicator()->createObjectAdapterWithEndpoints("SimpleFilesystem", "default -h 127.0.0.1 -p 10000");

        //
        // Create the root directory.
        //
        DirectoryIPtr root = new DirectoryI;
        Ice::Identity id;
        id.name = "RootDir";
        adapter->add(root, id);

        //
        // All objects are created, allow client requests now.
        //
        adapter->activate();

        //
        // Wait until we are done.
        //
        communicator()->waitForShutdown();
        if(interrupted())
        {
            cerr << appName() << ": received signal, shutting down" << endl;
        }

        return 0;
    };
};

int
#ifdef _WIN32
wmain(int argc, wchar_t* argv[])
#else
main(int argc, char* argv[])
#endif
{
    FilesystemApp app;
    return app.main(argc, argv);
}