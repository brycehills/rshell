### Compiling rshell on hammer:
```
1. git clone https://github.com/cs100/assignment-1-abc1234.git
2. git submodule init
3. git submodule update
4. cmake3 .
5. make
6. run executables ./test or ./rshell from main directory
```

# Coding Requirements
Extend your rshell program so that it properly handles input redirection <, output redirection > and >>, and piping |. This will require using the Unix functions dup and pipe. You can find help on how to use these functions in the man pages.
As an example, after this assignment, your program should be able to successfully handle the following command:
$ cat < existingInputFile | tr A-Z a-z | tee newOutputFile1 | tr a-z A-Z > newOutputFile2
IMPORTANT: This is a necessary but not sufficient test case. You must come up with others on your own.
Bash has an extensive syntax for redirection, and you are not required to implement all of it but only <, >, >>, and | as listed above. But if you're curious, see the linux documentation project's bash io-redirection tutorial for details.
# Submission
Make sure all branches are merged into the master branch, create a tag called hw4. Make sure the master branch is committed and pushed to your remote repository. You should also update your the design document that you created for Assignment 1 with the additional classes that you added to your system, as well as updating any previous classes that you modified.

NOTE: git push will not automatically push tags to your repository. Use git push origin hw4 to update your repository to include the hw4 tag. Additional information about git tags can be found here.










