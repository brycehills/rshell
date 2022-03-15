#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sstream>
#include <sys/wait.h>
#include <stack>
#include <deque>
#include <queue>
#include <sys/stat.h>
#include "../src/Base.h"
#include "../src/Command.h"
#include "../src/And.h"
#include "../src/Or.h"
#include "../src/Colon.h"
#include "../src/parse.h"
#include "../src/TestCommand.h"
#include "../src/Pipe.h"
#include "../src/Output.h"
#include "../src/OutputAppend.h"


using namespace std;

// takes in string and deletes everything after '#'
// as per required.
string deleteComment(string str)
{
    str = str.substr(0,str.find('#'));
    return str;
}

int main(int argc, char ** argv){

    cout << endl;       // endl for clean first display
    deque<Base*> commandDeque;

    // ~~~ getting user and host info for display
    char* userName = getlogin();
    char host[50];
    gethostname(host, sizeof host);
    // ~~~ end user/host info

    bool running = true;        // loop control variable
    string cmdLine;             // input command string to be parsed
    string newCmdLine;
    int searchIndex = 0;         // used to find comment
    bool parenBool;

    while(running)
    {

        //prompt display/get input
        cout << userName << " @ " << host << " $ ";
        getline(cin,cmdLine);

        // checking for no inputs
        // will loop until input is given
        while(cmdLine.empty())
        {
            //cout << "please enter a command...\n";
            cout << userName << " @ " << host << " $ ";
            getline(cin,cmdLine);
        }
        // delete comment from every input
        cmdLine = deleteComment(cmdLine);
        parenBool = Parse::checkParenthesis(cmdLine);
        while(parenBool == 0)
        {
            cout << userName << " @ " << host << " $ ";
            getline(cin,cmdLine);
            parenBool = Parse::checkParenthesis(cmdLine);
            cmdLine = deleteComment(cmdLine);
        }


        if(cmdLine[0] == '[')
        {
            cmdLine = Parse::ReplaceBracket(cmdLine);
        }


        // check for user entering exit
        if(cmdLine == "exit" || cmdLine == "exit ")
        {
            running = false;    // change LCV to be safe
            exit(1);            // exit program
        }

        vector<string> vec;
        vector<string> vec1;
        queue<string> q;

        vec = Parse::parseBySpace(cmdLine);
        vec1 = Parse::combineVector(vec);
        q = Parse::rpn(vec1);


        stack<Base*> cmdStack;
        string cmpstr;

        while(!q.empty())
        {
            cmpstr = q.front();
            q.pop();

            if(cmpstr == "&& ")
            {
                // add and
                Base* b1 = cmdStack.top();
                cmdStack.pop();

                Base* b2 = cmdStack.top();
                cmdStack.pop();

                And * a1 = new And(b2, b1);
                cmdStack.push(a1);
            }
            else if(cmpstr == "|| ")
            {
                //add or
                Base* b1 = cmdStack.top();
                cmdStack.pop();

                Base* b2 = cmdStack.top();
                cmdStack.pop();

                Or* or1 = new Or(b2, b1);
                cmdStack.push(or1);
            }
            else if(cmpstr == "; ")
            {
                //add semi
                Base* bp1 = cmdStack.top();
                cmdStack.pop();

                if(cmdStack.size() == 0)
                {
                    Colon* c1 = new Colon(bp1,NULL);
                    cmdStack.push(c1);
                }
                else
                {
                    Base* bp2 = cmdStack.top();
                    cmdStack.pop();

                    // adding semi colon object to tree
                    Colon* c1 = new Colon(bp2, bp1);
                    cmdStack.push(c1); // add to stack
                }

            }
            else
            {
                //add command
                Command *c = new Command(cmpstr);
                //add to the stack
                cmdStack.push(c);

            }
        }

            Base* exPtr = cmdStack.top();     // current object to execute
            exPtr->execute();                       // execute object
            cmdStack.pop();

    }
	return 0;
}
