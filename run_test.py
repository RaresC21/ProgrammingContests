import subprocess
import time
import sys
from platform import system
from os import listdir, remove
from os.path import isfile, join, isdir


PRECISION = 1e-6
TLE = 2.0
executable = "./a.out"
if system() == "Windows" :
    executable = "a.exe"

def isFloat(x, y) :
    try:
        float(x)
        float(y)
        return True
    except ValueError:
        return False

def cmp(a, b) :
    if isFloat(a, b) :
        a = float(a)
        b = float(b)
        return abs(a - b) <= PRECISION
    else :
        return a == b

def compare_output(output, data_path) :
    official = [line.rstrip('\n') for line in open(data_path + output)]
    mine = [line.rstrip('\n') for line in open("my_answer.txt")]

    if (len(official) != len(mine)) :
        return False

    for a, b in zip(official, mine) :
        if not cmp(a, b):
            return False

    return True


def execute(data_path, input):
    input_data = open(data_path + input)
    my_answer = open("my_answer.txt", "w")

    try:
        subprocess.call([executable], stdin=input_data, stdout=my_answer, timeout=TLE)
    except subprocess.TimeoutExpired:
        return False

    return True


def run() :
    data_path = sys.argv[-1]
    program = sys.argv[-2]

    files = [f for f in listdir(data_path) if isfile(join(data_path, f))]
    files.sort()

    subprocess.call(["g++", "-std=c++14", "-o", executable, program])
    for i in range(0, len(files), 2):
        output = files[i]
        input = files[i + 1]

        in_time_limit = execute(data_path, input)
        if not in_time_limit :
            print ("Test %s: TLE" % input)
            return

        if (compare_output(output, data_path)) :
            print ("Test %s: AC" % input)
        else :
            print ("Test %s: WA" % input)
            return

def clean() :
    remove("my_answer.txt")
    remove(executable)

def check_args() :
    if (len(sys.argv) != 3) :
        raise Exception("You need to pass in to arguments. The first argument must be the path to your c++ program. The second must bethe path to the test folder.")

    if (sys.argv[1][-3:] != "cpp") :
        raise Exception("First argument not a c++ file. (Must have .cpp ending)")

    program = sys.argv[-2]
    data = sys.argv[-1]
    try:
        open(program)
        assert isdir(data)
    except IOError:
        raise IOError("Specified C++ file does not exist")
    except AssertionError:
        raise AssertionError("Specified directory for test data does not exist")

check_args()
run()
clean()