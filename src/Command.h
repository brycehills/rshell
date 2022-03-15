#ifndef Command_h
#define Command_h

#include "../src/Base.h"
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

class Command : public Base{
public:

    // COMMAND constructor - takes in string
    // builds vector of space terminated commands
    Command(string s)
    {
        bool isTest;
        testString = "";
        // in main we will need to add switch for [ to test and remove ]
        isTest = checkTest(s);

        if(isTest)
        {
            //take out "test" and following space
            s.erase(0,5);

            //check for no flag
            s = addFlag(s);

            testString = s;
        }
        else
        {

            //convert string to char* to use with parser
            char* ar = new char[s.length() + 1];
            strcpy(ar, s.c_str());

            //parse char * by spaces
            char* parsingSpace = strtok(ar," ");

            // loops until last token
            while(parsingSpace != NULL)
            {
                charVec.push_back(parsingSpace);     // adds parsed string to vector
                parsingSpace = strtok(NULL," ");     // iterate to next space
            }

        }
    }

    //checks is passed string is a test command or not
    bool checkTest(string str)
    {
        bool isTest = false;
        //cout << str.substr(0,4) << endl;
        if(str.substr(0,4) == "test")
        {
            isTest = true;
        }

        return isTest;
    }

    // if no flag set, defaults to -e flag
    string addFlag(string str)
    {
        for(int i = 0; i < str.length(); i++)
        {
            if(str[0] != '-')
            {
                str.insert(0, "-e ");
            }
        }

        return str;
    }

    // COMMAND execute will use fork and execvp to call passed arguments
    // RETURNS: bool - passed or not passed (T or F)
    bool execute()
    {

        // test path test -e /Users/brycehills/Documents/assignment-1-abc1234/src/And.h

        bool pass = 1;      // initialize return bool

        if(testString[0] == '-')
        {
            struct stat file;

            string str = testString;
            str.erase(0,3);             //remove flag
            str.erase(str.size() - 1);  //remove ending space

            int num = stat(str.c_str(), &file);     // save result of stat()
            mode_t modeVar = file.st_mode;          // store mode variable

            if(testString[0] == '-' && testString[1] == 'e')
            {
                // handle file exists functionality
                if(num < 0)
                {
                    cout << "(False)" << endl;
                }
                else
                {
                    cout << "(True)" << endl;
                }
            }
            else if(testString[0] == '-' && testString[1] == 'd')
            {
                // 2. handle file dir functionality
                if(S_ISDIR(modeVar))
                {
                    cout << "(True)" << endl;
                }
                else
                {
                    cout << "(False)" << endl;
                }
            }
            else if(testString[0] == '-' && testString[1] == 'f')
            {
                // 2. handle -f functionality
                if(S_ISREG(modeVar))
                {
                    cout << "(True)" << endl;
                }
                else
                {
                    cout << "(False)" << endl;
                }
            }
            else
            {
                    // invalid path so do nothing
            }
        }
        else
        {
            // set big enough size for csvec
            csVec.reserve(charVec.size());

            // create csvec initializing the space-parsed cmd/arg values
            for(int i = 0; i < charVec.size();i++)
            {
                csVec.push_back(charVec.at(i));
            }

            // add null terminator dynamically
            csVec.push_back(NULL);

            // type cast csvec for our args arr
            char** args = const_cast<char**>(&csVec[0]);

            // create new charcter array - duplicated from charvec
            // we need a char array to send to execvp
            // iterate through vector & create array
            for(int i = 0; i < charVec.size();i++)
            {
                 //assign command vec value to array
                args[i] = charVec.at(i);
            }


            // help from: http://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/fork/exec.html
            // takes argument array with ending null terminantor
            // creates a child process and runs execvp
            pid_t  pid;
            int    status;

            if ((pid = fork()) < 0) {               // forks into new child PID
                //printf("*** ERROR: forking child process failed\n");
                pass = false;
                exit(1);
            }
            else if (pid == 0) {                    // checking child PID
                if (execvp(*args, args) < 0) {     // calls execvp on passed args
                    //printf("*** ERROR: exec failed\n");
                    exit(1);
                }
            }
            else {
                while (wait(&status) != pid)       // waiting for parent to finish
                    ;
            }

        }

        return pass;        //returns passed or not passed boolean
    }

protected:

    vector<char*> charVec;      // vector or character pointers
    vector<const char*> csVec;  // cs vector
    string testString;          // if string is a test
};

#endif
