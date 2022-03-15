#ifndef parse_h
#define parse_h

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


using namespace std;

class Parse{

public:

    // checks if inout string has matching amt of parens
    static bool checkParenthesis(string str)
    {

        bool match = true; //return bool
        int opencount = 0;
        int closecount = 0;

        for(int i = 0; i < str.length(); i++)
        {
            if(str[i] == '(')
            {
                opencount++;
            }
            if(str[i] == ')')
            {
                closecount++;
            }
        }

        if(opencount != closecount)
        {
            match = false;
        }

        return match;
    }

    //removes brackets and replaces them with "test "
    static string ReplaceBracket(string s)
    {
        s.erase(0,1);       // erase [
        s.insert(0,"test "); // add test in place of it
        for(int i = 0; i < s.size();i++)
        {
            // if has closing bracket
            if(s[i] == ']')
            {
                size_t found = s.find_first_of("]");
                s.erase(found,1);
            }
        }

        return s;
    }

    // this method will parse by space and return a vector of all parsed input
    static vector<string> parseBySpace(string input)
    {

        vector<string> vec;

        std::string old("(");
        std::string rep(" ( ");
        // make so we can parse ( as a connector
        for (int pos=0;(pos = input.find(old, pos)) != std::string::npos; pos+=rep.length())
        {
            input.replace(pos, old.length(), rep);
        }

        std::string old2(")");
        std::string rep2(" ) ");
        // make so we can parse ( as a connector
        for (int pos1=0;(pos1 = input.find(old2, pos1)) != std::string::npos; pos1 += rep2.length())
        {
            input.replace(pos1, old2.length(), rep2);
        }


        char *parseCmdLine = new char[input.length() + 1];      // creates new char* size of input
        strcpy(parseCmdLine, input.c_str());                  // copies typecasted input string to new char*

        char* ptr;

            ptr = strtok_r(parseCmdLine, " ", &parseCmdLine);  // parse by connector - grab text between
            while(ptr != NULL)
            {
                vec.push_back(ptr);
                ptr = strtok_r(NULL, " ", &parseCmdLine);              // iterates to next parse
            }

        return vec;
    }


    // this method is used to combine all non connector elements
    // *** returns new vector with combined elements
    static vector<string> combineVector(vector<string> vec)
    {
        vector<string> v;       // return vector
        queue<int> q;           // holds indices

        string s;
        int index;

        for(int i = 0; i < vec.size(); i++)
        {
            s = "";        //init string vriable

            //check if vec element is connector
            if(vec[i] == "||" || vec[i] == "&&" ||vec[i] == ";" ||vec[i] == "(" || vec[i] == ")"
             || vec[i] == "|" || vec[i] == "<" || vec[i] == ">" || vec[i] == ">>")
            {
                while(!q.empty())
                {
                    index = q.front();          // get index
                    s += vec[index] + " ";      // concat string
                    q.pop();                    // pop index
                }

                v.push_back(s);                 //push combined string
                v.push_back(vec[i]+ " ");              //push connector
            }
            else    // not connector
            {
                q.push(i);          // save index of non-connector
            }
        }

        // end for loop
        string s1 = "";
        while(!q.empty())
        {
            s1 += vec[q.front()] + " ";
            q.pop();
        }

        v.push_back(s1);

        return v;
    }

    // assigns precedence for certain operators
    // returns int value of precedence
    static int getPrecedence(string str)
    {

        int p;

        if(str == "( ")
        {
            p = 2;
        }
        else if(str == ") ")
        {
            p = 2;
        }
        else if(str == "&& ")
        {
            p = 1;
        }
        else if(str == "|| ")
        {
            p = 1;
        }
        else if(str == "; ")
        {
            p = 1;
        }

        return p;
    }

    // converts passed vector into reverse polish notation
    // returns formatted queue
    static queue<string> rpn(vector<string> vec)
    {
        stack<string> s;        // connector stack
        queue<string> q;        // output queue

        //iterate vector
        for(int i = 0; i < vec.size(); i++)
        {
            //if element is a connector
            if(vec[i] == "|| " || vec[i] == "( " || vec[i] == "&& " || vec[i] == "; ")
            {
                while((!s.empty()) &&
                      ((getPrecedence(s.top()) > getPrecedence(vec[i])) ||
                       (getPrecedence(s.top()) == getPrecedence(vec[i])))  &&
                      (s.top() != "( "))
                {
                    // push to output queue
                    q.push(s.top());
                    s.pop();
                }
                s.push(vec[i]); //push element to stack
            }
            else if(vec[i] == ") ")     //right paren
            {
                while(s.top() != "( ")
                {
                    q.push(s.top());
                    s.pop();
                }
                s.pop();                // pop last connector after loop
            }
            else
            {
                //build queue of commands
                if(vec[i] != " " && vec[i].size()!=0)
                {
                    q.push(vec[i]);
                }
            }
        }
        // final loop after iteration to clear remaning stack items
        while(!s.empty())
        {
            q.push(s.top());
            s.pop();
        }

        return q;       //return RPN queue
    }

};


#endif /* And_h */
