# Programming Contests
My Solutions to various Programming Contest Problems

## Code Book

I am also including my code book along with problems from various sites like Codeforces that utilize particular data structures, algorithms etc. I will also try to write up tutorials explaining the theory behind how everything works, as well as editorials for some of the more interesting problems.

EDIT: At the moment, there is plenty of geometry routines in my codebook and number theory/combinatorics.

Currently starting to include some data structures. Segment Trees are comprehensively included, with a short tutorial. 

## Automatically Compile and Run

###### I have included an `initc++.txt` file  with starting configuration (macros defined, etc. etc. check it out), as well as a `makefile` included in the `template` folder.

When competing, I use a single file called `p.cpp` to write my code in. To run and compile it, using input from a file called `input.txt`, I have included a `makefile`. Simply run

`make`

in the command line in the same directory as the makefile. Additionally, you can output the answer to a text file called `ans.txt` by running:

`make out_file`

#### Runtime

To determine the runtime of a program, include the `-D TIMP` compiler flag. This defines the macro `TIMP`. Using `ifdef` in `p.cpp` file included, this will print the running time of the program.

Run `make CFLAGS=-DTIMP`

#### Automatically populate file with template

Running `make init` will copy the file `initc++.txt` into the file `p.cpp`. This is simply a shortcut for the bash command:

`cat initc++.txt > p.cpp`

## Running Against Test Data

I have written a program, `run_test.py`, which allows you to run your program against. All you need is to download the test data. This will test against all files in directory you specify. It assumes that the input file has the same name as its corresponding output file (with possible different extensions like `.in` and `.out` for example). To run:

```
python3 run_test.py /path/to/program.cpp /path/to/directory/containing/tests
```

Currently, only `C++` is supported.

Output format can be strings, integers or floats. If floats, it will test that difference between expected output and your own is at most `1e-6`. The time limit is set at `2 seconds`. These values can be changed with the variables defined at the top of the `run_test.py` file.

**Requirements:** python 3

## Generator

If you have a code book, then plenty of functions and classes are already written and ready to be used. All you need is to copy and paste them into your own file. Moreover, your solution file for some problems may get very long if you need to include multiple implementations of different data structures, many functions etc. Also for geometry problems, there are plenty of utility functions that you never change that clutter up the top of your file.

Instead, you can write your lazy-segment tree in a separate file, your geometry in another, etc, etc. and have a clean file with only your main function and some `#include`'s at the top. But when submitting, you need everything in one file. To remedy this, run

`bash generator.sh {name of your main file}`

in the command line, and everything in your include files will be copied into a file `sol.cpp` with everything you need to submit.

For an example, see `Codebook\Generator-Ex\`

Still a work in progress. Currently only one include can be used per file. And it must be the very first line of the file.
