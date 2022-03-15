### Compiling rshell on hammer:
```
1. git clone https://github.com/brycehills/rshell.git
2. git submodule init
3. git submodule update
4. cmake3 .
5. make
6. run executables ./test or ./rshell from main directory
```

#Rshell
Basic implementation of a unix shell with connector functionality. 

### Commands are of the following format:
```
cmd 	= executable [ argumentList ] [ connector cmd ]
connector = || or && or ;
```
###example
 > username§host: ls -a && pwd || ps

![alt text](https://github.com/brycehills/rshell/blob/main/uml.JPG?raw=true)

# Classes
## Main
 dynamically grabs user input from command line. 
 Then, sends to Command.h to determine validity (execute)
 Parses user input by connector in main, then by space once inside the command constructor
 Once parsed by space it is prepped for execvp() syscall
 Our data member for parse is a string since will be performing operations on an input string
 ## Parse:
 This class handles manipulation/parsing of input data
 It will format the input string as needed
 It will also format the input string into reverse polish notation using the Schunting-yard algorithm.
 Once input is parsed and in RPN, it will build a queue to adhere to the proper precedence.
  Composite Pattern Class Group (Base, Connector, AND, OR, COLON)
 This class group all inherit from base class “Base”
 This class defines/implements the composite pattern
 The base class will have a definition for virtual method evaluate
 Evaluate will be defined differently in each of the composites (OR/AND/COLON)
 These will return true if valid commands
 They will then be executed based on the left to right precedence depending on the connectors.
 Since evaluate is a virtual method, we chose for all the data types for these classes to be of Base class
type pointers.
 This allows us to have a uniform interface throughout the program.
 ## I/O redirect & piping classes:
 These classes all also inherit from base
 They will handle piping and I/O redirection
 The classes include: Pipe, Output, OutputAppend, and Input
 Pipe: allows a user to input a command using piping
 Output/OutputAppend: allows a user to enter and execute commands with output redirection
 Input: allows a user to input commands that redirect input
 ## Test – GoogleTests:
 Our program also contains a test_rshell.cpp file which utilizes the googletest functionalty.
 We have written about 30 unit tests the allow us to continually test and confirm the inner workings of
the code are running properly.
 These unit tests are accesable via our “test” executable, which is separate from the main code, “rshell”
 New tests are added each time new functionality is added

# Coding Requirements
Extend your rshell program so that it properly handles input redirection <, output redirection > and >>, and piping |. This will require using the Unix functions dup and pipe. You can find help on how to use these functions in the man pages.
As an example, after this assignment, your program should be able to successfully handle the following command:
$ cat < existingInputFile | tr A-Z a-z | tee newOutputFile1 | tr a-z A-Z > newOutputFile2
IMPORTANT: This is a necessary but not sufficient test case. You must come up with others on your own.
Bash has an extensive syntax for redirection, and you are not required to implement all of it but only <, >, >>, and | as listed above. But if you're curious, see the linux documentation project's bash io-redirection tutorial for details.
# Submission
Make sure all branches are merged into the master branch, create a tag called hw4. Make sure the master branch is committed and pushed to your remote repository. You should also update your the design document that you created for Assignment 1 with the additional classes that you added to your system, as well as updating any previous classes that you modified.

NOTE: git push will not automatically push tags to your repository. Use git push origin hw4 to update your repository to include the hw4 tag. Additional information about git tags can be found here.










