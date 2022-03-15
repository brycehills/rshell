#ifndef Pipe_h
#define Pipe_h

#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include <fcntl.h>


#include "../src/Command.h"
#include "../src/Base.h"

using namespace std;

//    # General purpose process and command chaining tool.
//    # Similar to ">", but more general in effect.
class Pipe : public Base{

protected:
  Base* l;  // left command - command class parses string for us
  Base* r;  // right command

public:

  Pipe(Base* left, Base* right)
  {
    l = left;
    r = right;
  }

  void changeStdOut(int fd)
  {
    dup2(fd,1);
  }

  void changeStdIn(int fd)
  {
    dup2(fd, 0);
  }

  int backupStdOut()
  {
    return dup(1);
  }

  int backupStdIn()
  {
    return dup(0);
  }

  int getOutputFile(std::string fileName)
  {
      //open output file
      // >> includes append
      return open(fileName.c_str(), O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
  }

  // will execute and return true or false for a pipe object
  // recieved assistance for this function from the following source:
  // http://www.cs.loyola.edu/~jglenn/702/S2005/Examples/dup2.html
  bool execute()
  {
    bool pass = 1;    // return bool value
    int pipefd[2];    // pipefd
    int pid;          // process ID for fork()

    int outb = backupStdOut();    // backup stdout
    int inb = backupStdIn();      // backup stdin

    // make a pipe (fds go in pipefd[0] and pipefd[1])
    pipe(pipefd);

    pid = fork();   // call fork

    if (pid == 0)   // in child proc
      {
        // replace standard input with input part of pipe
        dup2(pipefd[0], 0);

        // close unused half of pipe - stdout
        close(pipefd[1]);

        // execute right command
        if(!r->execute())   // check if execute passes
        {
          pass = 0;
          changeStdIn(inb);
        }
      }
    else
      {
        // replace standard output with output part of pipe
        dup2(pipefd[1], 1);

        // close unused unput half of pipe
        close(pipefd[0]);

        // execute left command
        if(!l->execute())   // check if execute works
        {
          pass = 0;
          changeStdOut(outb);
        }
      }

      // restore the original file
      changeStdIn(inb);
      changeStdOut(outb);

    return pass;
  }

};

#endif
