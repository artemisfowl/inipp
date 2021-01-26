# inipp
A simple INI file parser - header only

#### Usage
Copy the inipp header and source files and you are good to go.

The implementation for this one is very crude, nothing fancy that has been used.

#### Help
The main source code contains a sample implementation of the same headers, so please feel free to test it.

Basically there are two files which are present in the test\_input directory, the testpass.ini file should pass whereas the testfail.ini file will fail.

#### Improvements
Added the portion of code so that duplicate sections(sections with the same name) cannot be created.
Option names can be the same, however this library will limit the sections with the same name.
There are certain cases which still needs to be tested, so I will try to update the code based on the testing done. This is not the final version of the headers.

Please suggest ways of improvement and feel free to extend the same for any purpose.

