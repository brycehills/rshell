#ifndef TestCommand_h
#define TestCommand_h

#include "../src/Base.h"

using namespace std;

class TestCommand : public Base{
    
public:
    
    // testcmd constructor - takes in string
    // builds path to send to execute
    TestCommand(string s)
    {
        
    }
    // COMMAND execute will run stat() depending on which flag is given (-e by default)
    // RETURNS: bool - passed or not passed (T or F)
    bool execute()
    {
        return 0;
    }
    

};

#endif


