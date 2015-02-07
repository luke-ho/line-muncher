# line-muncher
============

###Author: Luke Ho
###Assumptions: You have GCC, Python, Perl, Bash, make, egrep installed and that you're running this in a linux environment 

Quick Start
============
    Run the "./run.sh" in home directory.

Manual steps
============
    1.) Run "make" in home directory
    2.) cd to scripts/, run "make"
    3.) ./gen_tests
    4.) cd ../verif
    5.) run_tests.sh

The muncher will fork off a child process and print out, line-by-line, the contents of the file passed in.

In the scripts/ directory, there are two files: generate_tests.c and generate_tests.py. When "make" is ran, it will generate a gen_tests binary that will output numbers within a given range to a file

The python script (scripts/generate_tests.py) will put each new number on a separate line for more testing if required

gen_tests binary will put each new number back to back and spit it all out as a single line.

Update the generate_tests.c file to generate numbers from various ranges.

In the verif/ directory, run "run_tests.sh" to verify that the muncher is reading the input properly.  


License
============

The MIT License (MIT)

Copyright (c) 2015 Luke Ho

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
