#!/usr/bin/python3
import re
import os
    
# PROBLEM 1
# Find all years from 1900-1999
# Known instances: 59
def problem_1(directory):
    # expected number of occurances of pattern
    expected = 59
    # resultant number of occurances of pattern
    real = 0
    # loop through directory
    for file in os.listdir(directory):
        # find filename
        filename = os.fsdecode(file)
        # test for valid filename(ending with .txt or .csv)
        if filename.endswith(".txt") or filename.endswith(".csv"):
            # open file for reading
            file = open(filename, "r")
            # list for occurances 
            occurances = []
            # loop through file
            for line in file:
                # update list of occurances
                occurances = re.findall(r"\b19[0-9]{2}\b", line)
                if len(occurances) > 0:
                    real += 1
    if (real == expected):
        print("PROBLEM 1: success")
    else:
        print("PROBLEM 1: fail")
        print("-> Expected: ", expected)
        print("-> Counted: ", real)
    print("")

# PROBLEM 2
# Find all years from 1900-2099
# Known instances: 103
def problem_2(directory):
    # expected number of occurances of pattern
    expected = 103
    # resultant number of occurances of pattern
    real = 0
    # loop through directory
    for file in os.listdir(directory):
        # find filename
        filename = os.fsdecode(file)
        # test for valid filename(ending with .txt or .csv)
        if filename.endswith(".txt") or filename.endswith(".csv"):
            # open file for reading
            file = open(filename, "r")
            # list for occurances 
            occurances = []
            # loop through file
            for line in file:
                # update list of occurances
                occurances = re.findall(r"\b(19|20)[0-9]{2}\b", line)
                if len(occurances) > 0:
                    real += 1
    if (real == expected):
        print("PROBLEM 2: success")
    else:
        print("PROBLEM 2: fail")
        print("-> Expected: ", expected)
        print("-> Counted: ", real)
    print("")

# PROBLEM 3
# Find all instances of the word 'old'
# Known instances: 70
def problem_3(directory):
    # expected number of occurances of pattern
    expected = 70
    # resultant number of occurances of pattern
    real = 0
    # loop through directory
    for file in os.listdir(directory):
        # find filename
        filename = os.fsdecode(file)
        # test for valid filename(ending with .txt or .csv)
        if filename.endswith(".txt") or filename.endswith(".csv"):
            # open file for reading
            file = open(filename, "r")
            # list for occurances 
            occurances = []
            # loop through file
            for line in file:
                # update list of occurances
                occurances = re.findall(r"\bold\b", line)
                if len(occurances) > 0:
                    real += 1
    if (real == expected):
        print("PROBLEM 3: success")
    else:
        print("PROBLEM 3: fail")
        print("-> Expected: ", expected)
        print("-> Counted: ", real)
    print("")

# PROBLEM 4
# Find all anything that looks like a letter grade inside of double quotes,
# uppercase letters only, and may or may not have '+' or '-' following it
# Known instances: 16
def problem_4(directory):
    # expected number of occurances of pattern
    expected = 16
    # resultant number of occurances of pattern
    real = 0
    # loop through directory
    for file in os.listdir(directory):
        # find filename
        filename = os.fsdecode(file)
        # test for valid filename(ending with .txt or .csv)
        if filename.endswith(".txt") or filename.endswith(".csv"):
            # open file for reading
            file = open(filename, "r")
            # list for occurances 
            occurances = []
            # loop through file
            for line in file:
                # update list of occurances
                occurances = re.findall("\"[ABCDF][+-]?\"", line)
                if len(occurances) > 0:
                    real += 1
    if (real == expected):
        print("PROBLEM 4: success")
    else:
        print("PROBLEM 4: fail")
        print("-> Expected: ", expected)
        print("-> Counted: ", real)
    print("")

# PROBLEM 5
# Find all words that being with a vowel and end with 'it' in wordlist.txt
# Known instances: 16
def problem_5(directory): 
    # expected number of occurances of pattern
    expected = 16
    # resultant number of occurances of pattern
    real = 0
    # loop through directory
    for file in os.listdir(directory):
        # find filename
        filename = os.fsdecode(file)
        # test for valid filename(ending with .txt or .csv)
        if filename.endswith(".txt") or filename.endswith(".csv"):
            # open file for reading
            file = open(filename, "r")
            # list for occurances 
            occurances = []
            # loop through file
            for line in file:
                # update list of occurances
                occurances = re.findall(r"\b[aeiou]\w+(it)$\b", line)
                if len(occurances) > 0:
                    real += 1
    if (real == expected):
        print("PROBLEM 5: success")
    else:
        print("PROBLEM 5: fail")
        print("-> Expected: ", expected)
        print("-> Counted: ", real)
    print("")

# PROBLEM 6
# Find all words that do not begin with a vowel but end with 'es' and are
# atleast 7 characters in length in wordlist.txt
# Known instances: 6
def problem_6(directory):
    # expected number of occurances of pattern
    expected = 6
    # resultant number of occurances of pattern
    real = 0
    # loop through directory
    for file in os.listdir(directory):
        # find filename
        filename = os.fsdecode(file)
        # test for valid filename(ending with .txt or .csv)
        if filename.endswith(".txt") or filename.endswith(".csv"):
            # open file for reading
            file = open(filename, "r")
            # list for occurances 
            occurances = []
            # loop through file
            for line in file:
                # update list of occurances
                occurances = re.findall(r"^[^aeiou]\w{4,}es$", line)
                if len(occurances) > 0:
                    real += 1
    if (real == expected):
        print("PROBLEM 6: success")
    else:
        print("PROBLEM 6: fail")
        print("-> Expected: ", expected)
        print("-> Counted: ", real)
    print("")

# PROBLEM 7
# Find all dollar amounts with optional cents
# Known instances: 30
def problem_7(directory):
    # expected number of occurances of pattern
    expected = 30
    # resultant number of occurances of pattern
    real = 0
    # loop through directory
    for file in os.listdir(directory):
        # find filename
        filename = os.fsdecode(file)
        # test for valid filename(ending with .txt or .csv)
        if filename.endswith(".txt") or filename.endswith(".csv"):
            # open file for reading
            file = open(filename, "r")
            # list for occurances 
            occurances = []
            # loop through file
            for line in file:
                # update list of occurances
                occurances = re.findall(r"\$\d+(\.\d+)?", line)
                if len(occurances) > 0:
                    real += 1
    if (real == expected):
        print("PROBLEM 7: success")
    else:
        print("PROBLEM 7: fail")    
        print("-> Expected: ", expected)
        print("-> Counted: ", real)
    print("")

def main():
    
    directory = os.fsencode(os.getcwd())
    problem_1(directory)
    problem_2(directory)
    problem_3(directory)
    problem_4(directory)
    problem_5(directory)
    problem_6(directory)
    problem_7(directory)

main()
