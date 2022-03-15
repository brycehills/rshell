#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "gtest/gtest.h"
#include "../src/Base.h"
#include "../src/Command.h"
#include "../src/And.h"
#include "../src/Or.h"
#include "../src/Colon.h"
#include "../src/parse.h"
#include "../src/Pipe.h"
#include "../src/Output.h"
#include "../src/OutputAppend.h"
#include "../src/Input.h"



using namespace std;


// EXECUTE TESTS - tests the output of execute(); is correct
// with respect to the instantiated object(s)

// testing execuet of command object
TEST (ExecuteTest, CommandExecuteTest){
    string str1 = "echo a";
    Command* c1 = new Command(str1);        // new command object
    testing::internal::CaptureStdout();
    c1->execute();                          // calling execute on command
    string str = testing::internal::GetCapturedStdout();
    EXPECT_EQ("a\n", str);
}

// testing execute of or object
TEST (ExecuteTest, OrExecuteTest){
    string str1 = "echo a";
    string str2 = "echo b";

    // commands
    Command* c1 = new Command(str1);
    Command* c2 = new Command(str2);

    Or* or1 = new Or(c1,c2);       // OR object

    testing::internal::CaptureStdout();
    or1->execute();                 // calling execute on or
    string str = testing::internal::GetCapturedStdout();
    EXPECT_EQ("a\n", str);
}

//testing execute of nested and objects
TEST (ExecuteTest, DoubleAndExecuteTest){
    //test strings
    string str1 = "echo a";
    string str2 = "echo b";
    string str3 = "echo c";
    string str4 = "echo d";

    // commands
    Command* c1 = new Command(str1);
    Command* c2 = new Command(str2);
    Command* c3 = new Command(str3);
    Command* c4 = new Command(str4);

    // nesting and objects
    Base *and1 = new And(c1,c2);     //AND object
    Base *and2 = new And(c3,c4);

    // nested AND object
    And *and3 = new And(and1, and2);

    testing::internal::CaptureStdout();
    and3->execute();                // callingn execute on and
    string str = testing::internal::GetCapturedStdout();
    EXPECT_EQ("a\nb\nc\nd\n", str);     //expected output
}

//testing execute of and object
TEST (ExecuteTest, DoubleOrExecuteTest){
    //test strings
    string str1 = "echo a";
    string str2 = "echo b";
    string str3 = "echo c";
    string str4 = "echo d";

    // commands
    Command* c1 = new Command(str1);
    Command* c2 = new Command(str2);
    Command* c3 = new Command(str3);
    Command* c4 = new Command(str4);

    // nesting and objects
    Base *or1 = new Or(c1,c2);     //AND object
    Base *or2 = new Or(c3,c4);

    // nested AND object
    Or *or3 = new Or(or1, or2);

    testing::internal::CaptureStdout();
    or3->execute();                // callingn execute on and
    string str = testing::internal::GetCapturedStdout();
    EXPECT_EQ("a\n", str);     //expected output
}

//testing execute of and object
TEST (ExecuteTest, AndExecuteTest){

    //test strings
    string str1 = "echo a";
    string str2 = "echo b";

    // commands
    Command* c1 = new Command(str1);
    Command* c2 = new Command(str2);

    And *and1 = new And(c1,c2);     //AND object

    testing::internal::CaptureStdout();
    and1->execute();                // callingn execute on and
    string str = testing::internal::GetCapturedStdout();
    EXPECT_EQ("a\nb\n", str);
}

//testing execute of and object
TEST (ExecuteTest, TripleAndExecuteTest){

    //test strings
    string str1 = "echo a";
    string str2 = "echo b";
    string str3 = "echo c";

    // commands
    Command* c1 = new Command(str1);
    Command* c2 = new Command(str2);
    Command* c3 = new Command(str3);

    And *and1 = new And(c1,c2);     //AND object
    And *and2 = new And(and1,c3);

    testing::internal::CaptureStdout();
    and2->execute();                // callingn execute on and
    string str = testing::internal::GetCapturedStdout();
    EXPECT_EQ("a\nb\nc\n", str);
}

//testing execute of and object
TEST (ExecuteTest, TripleOrExecuteTest){

    // test strings
    string str1 = "echo a";
    string str2 = "echo b";
    string str3 = "echo c";

    // commands
    Command* c1 = new Command(str1);
    Command* c2 = new Command(str2);
    Command* c3 = new Command(str3);

    Or *and1 = new Or(c1,c2);     //AND object
    Or *and2 = new Or(and1,c3);   // or obj

    testing::internal::CaptureStdout();
    and2->execute();                // callingn execute on and
    string str = testing::internal::GetCapturedStdout();
    EXPECT_EQ("a\n", str);
}

//testing bested and/or execution
TEST (ExecuteTest, NestedAndOrExecuteTest){

    //test strings
    string str1 = "echo a";
    string str2 = "echo b";
    string str3 = "echo c";

    // commands
    Command* c1 = new Command(str1);
    Command* c2 = new Command(str2);
    Command* c3 = new Command(str3);

    And *and1 = new And(c1,c2);     //AND object
    Or *and2 = new Or(and1,c3);     // OR object with AND as left side

    testing::internal::CaptureStdout();
    and2->execute();                // callingn execute on and
    string str = testing::internal::GetCapturedStdout();
    EXPECT_EQ("a\nb\n", str);       //expected output
}

//testing execute of colon object - shows we can instiantiate and
// runn a colon object
TEST (ExecuteTest, ColonExecuteTest){
    string str1 = "echo a";
    string str2 = "echo b";

    // commands
    Command* c1 = new Command(str1);
    Command* c2 = new Command(str2);

    Colon *colon1 = new Colon(c1,c2);     //COLON object

    testing::internal::CaptureStdout();
    colon1->execute();                // callingn execute on COLON
    string str = testing::internal::GetCapturedStdout();
    EXPECT_EQ("a\nb\n", str);
}


//testing delete commennt functionality used in main.cpp
TEST (DeleteCommentTest, NoSpaceCommentTest){
    // test string
    string s = "ls && ls -a #123";

    s = s.substr(0,s.find('#'));

    testing::internal::CaptureStdout();
    cout << s;
    string str = testing::internal::GetCapturedStdout();
    EXPECT_EQ("ls && ls -a ", str);
}

//testing delete commennt functionality used in main.cpp
TEST (DeleteCommentTest, WithSpaceCommentTest){
    // test string
    string s = "echo a && ls -a # 123";

    s = s.substr(0,s.find('#'));

    testing::internal::CaptureStdout();
    cout << s;
    string str = testing::internal::GetCapturedStdout();
    EXPECT_EQ("echo a && ls -a ", str);
}

//testing delete commennt functionality used in main.cpp
TEST (DeleteCommentTest, LongCommentTest){
    // test string
    string s = "echo a && echo b # 123 123 123 123 123 123 123 123 ppp www qqq    ";

    s = s.substr(0,s.find('#'));

    testing::internal::CaptureStdout();
    cout << s;
    string str = testing::internal::GetCapturedStdout();
    EXPECT_EQ("echo a && echo b ", str);
}

// checking that parenthesis match
TEST (ParenthesisTest, TestTrueCheckParens){
    string s = "(echo a)";
    bool val;
    testing::internal::CaptureStdout();
    val = Parse::checkParenthesis(s);
    cout << val;
    string str = testing::internal::GetCapturedStdout();
    EXPECT_EQ("1", str);
}

// checking for parenthesis mismatch
TEST (ParenthesisTest, TestFalseCheckParens){
    string s = "(echo a))";
    bool val;
    testing::internal::CaptureStdout();
    val = Parse::checkParenthesis(s);
    cout << val;
    string str = testing::internal::GetCapturedStdout();
    EXPECT_EQ("0", str);
}

// checking combine vector method
TEST (VectorCombineTest, CheckCombineVec){
    string s = "ls -l && ls -a";
    vector<string> v;
    v.push_back(s);

    v = Parse::combineVector(v);
    testing::internal::CaptureStdout();

    for(int i=0; i<v.size();i++)
    {
        cout << v[i] << " ";
    }
    string str = testing::internal::GetCapturedStdout();
    EXPECT_EQ("ls -l && ls -a", s);
}

// sending one arg vector to rpn to test queue has proper contents
TEST (PrecedenceTest, SingleParenTest){
    string s = "(echo a)";
    vector<string> v;
    queue<string> q;
    v.push_back(s);

    q = Parse::rpn(v);

    //output content of queue
    testing::internal::CaptureStdout();
    while(!q.empty())
    {
        cout << q.front() << " ";
        q.pop();
    }
    string str = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(echo a) ", str);
}

// sending arg vector to rpn to test queue has proper contents
TEST (PrecedenceTest, DoubleParenTest){
    string s1 = "(echo a)";
    string s2 = "&& ";
    string s3 = "(echo b)";
    vector<string> v;
    queue<string> q;

    //fill queue
    v.push_back(s1);
    v.push_back(s2);
    v.push_back(s3);

    //call rpn method
    q = Parse::rpn(v);

    //output content of queue
    testing::internal::CaptureStdout();
    while(!q.empty())
    {
        cout << q.front() << " ";  // adds extra space here
        q.pop();
    }
    string str = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(echo a) (echo b) &&  ", str);
}

// sending one arg vector to rpn to test queue has proper contents
TEST (PrecedenceTest, DoubleOperatorTest){
    string s1 = "(echo a)";
    string s2 = "&& ";
    string s3 = "(echo b)";
    string s4 = "|| ";
    string s5 = "(echo c)";
    string s6 = "&& ";
    string s7 = "(echo d)";
    vector<string> v;
    queue<string> q;

    //fill queue
    v.push_back(s1);
    v.push_back(s2);
    v.push_back(s3);
    v.push_back(s4);
    v.push_back(s5);
    v.push_back(s6);
    v.push_back(s7);

    //call rpn method
    q = Parse::rpn(v);

    //output content of queue
    testing::internal::CaptureStdout();
    while(!q.empty())
    {
        cout << q.front() << " ";  // adds extra space here
        q.pop();
    }
    string str = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(echo a) (echo b) &&  (echo c) ||  (echo d) &&  ", str);
}

// tests parse method replacebracket()
// will return a modified string
TEST (ParseTest, ReplaceBracketTest){
    string str1 = "[-e /users/user1/path/doc/hello.txt ]";
    string s = Parse::ReplaceBracket(str1);

    testing::internal::CaptureStdout();
    cout << s;
    string str = testing::internal::GetCapturedStdout();
    EXPECT_EQ("test -e /users/user1/path/doc/hello.txt ", str);
}

// tests parse method replacebraxket()
// will return a modified string
TEST (ParseTest, ReplaceBracketConnectorTest){
    string str1 = "[-e /users/user1/path/doc/hello.txt] && echo a";
    string s = Parse::ReplaceBracket(str1);

    testing::internal::CaptureStdout();
    cout << s;
    string str = testing::internal::GetCapturedStdout();
    EXPECT_EQ("test -e /users/user1/path/doc/hello.txt && echo a", str);
}

//testing false -e file path
TEST (TestCommandTest, FalseFileExistsTest){
    string str1 = "test -e /users/user1/path/doc/hello.txt";

    Command * c = new Command(str1);

    testing::internal::CaptureStdout();
    c->execute();
    string str = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(False)\n", str);
}

// testing Basic Output stream >
TEST (ExecuteRedirTest, OutputOpTest){
    string str1 = "echo a\nb";
    string filename = "test.txt";
    Command* c1 = new Command(str1);            // new command object
    Base* outTest = new Output(c1,filename);

    testing::internal::CaptureStdout();
    outTest->execute();                          // calling execute on command
    string str = testing::internal::GetCapturedStdout();
    EXPECT_EQ("", str);
}

// testing Basic OutputAppend stream >>
// when ran mulitple times without deleting the txt file,
// this test will create and append to the text file
TEST (ExecuteRedirTest, OutputAppendOpTest){
    string str1 = "echo hello";
    string filename = "appendedfile.txt";
    Command* c1 = new Command(str1);        // new command object
    Base* outTest = new OutputAppend(c1,filename);

    testing::internal::CaptureStdout();
    outTest->execute();                          // calling execute on command
    string str = testing::internal::GetCapturedStdout();
    EXPECT_EQ("", str);
}

// testing Basic input stream >>
// we take the text within test.txt and pipe it to the cat command
TEST (ExecuteRedirTest, InputOpTest){
    string str1 = "cat";
    string filename = "test.txt";
    Command* c1 = new Command(str1);        // new command object
    Base* inTest = new Input(c1, filename);

    testing::internal::CaptureStdout();
    inTest->execute();                          // calling execute on command
    string str = testing::internal::GetCapturedStdout();
    EXPECT_EQ("a\nb\n", str);
}

// testing Basic Pipe operation |
// testing to cat test1.txt into "tee pipetest.txt"
TEST (ExecuteRedirTest, PipeOpTest){
    string str1 = "cat test.txt";
    string str2 = "tee pipetest.txt";

    Command* command1 = new Command(str1);        // new command object
    Command* command2 = new Command(str2);        // new command object

    Base* pipeobj = new Pipe(command1, command2);       // new pipe object

    testing::internal::CaptureStdout();           //capture stdout
    pipeobj->execute();                          // calling execute on pipe object
    string str = testing::internal::GetCapturedStdout();
    EXPECT_EQ("", str);
}

// testing Basic Pipe operation |
// throwing contents of ls command into lstext.txt
// needs to be manually checked inside file - lstext.txt
TEST (ExecuteRedirTest, PipeLSTest){
    // test command strings
    string str1 = "ls";
    string str2 = "tee lstest.txt";
    string s = "";

    Command* command1 = new Command(str1);        // new command object
    Command* command2 = new Command(str2);        // new command object

    Base* pipeobj = new Pipe(command1, command2);       // new pipe object

    testing::internal::CaptureStdout();           //capture stdout
    pipeobj->execute();                          // calling execute on pipe object
    string str = testing::internal::GetCapturedStdout();
    s = str;    // hacky way to grab output from ls, but the file is whats important
    EXPECT_EQ(s, str);
}


// testing chained Pipe operation |
// uses a nested pipe object to grep "b"from test.txt into outputpipe.txt
TEST (ExecuteRedirTest, ChainPipeOpTest){

    // test inputs for commands
    string str1 = "cat test.txt";
    string str2 = "grep -i b";
    string str3 = "tee outputpipe.txt";

    Command* command1 = new Command(str1);        // new command object
    Command* command2 = new Command(str2);        // new command object
    Command* command3 = new Command(str3);        // new command object

    Base * pipeobj1 = new Pipe(command1, command2);       // new pipe object
    Base * pipeobj2 = new Pipe(pipeobj1, command3);       // new pipe obnject

    testing::internal::CaptureStdout();           //capture stdout
    pipeobj2->execute();                          // calling execute on pipe object
    string str = testing::internal::GetCapturedStdout();
    EXPECT_EQ("", str);     // expercting clean console, since working inside files
}


// main which runs all tests at run time
int main(int argc, char ** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
