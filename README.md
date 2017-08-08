# Programming Contests
My Solutions to various Programming Contest Problems

## Running Against Test Data

I have written a program, `run_test.py`, which allows you to run your program against. All you need is to download the test data. This will test against all files in directory you specify. It assumes that the input file has the same name as its corresponding output file (with possible different extensions like `.in` and `.out` for example). To run:

```
python run_test.py /path/to/program.cpp /path/to/directory/containing/tests
```

Currently, only `C++` is supported.

Output format can be strings, integers or floats. If floats, it will test that difference between expected output and your own is at most `1e-6`. The time limit is set at `2 seconds`. These values can be changed with the variables defined at the top of the `run_test.py` file.

**Requirements:** python 3
