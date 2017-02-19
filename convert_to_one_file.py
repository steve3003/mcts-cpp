import os
import re

include_dirs = ["Connect4/Inc", "mcts-cpp/Inc"]
source_dirs = ["Connect4/Src", "mcts-cpp/Src"]
output_file = "gcc/main.cpp"

include_re = re.compile(r'#include\s+"(\w+\.h)"')
cpp_include_re = re.compile(r'#include\s+<\w+\>')

source_output = ""
cpp_includes = set()
include_files = {}
source_files = [os.path.join(d,f) for d in source_dirs for f in os.listdir(d) if f.endswith(".cpp")]

def find_include_files(file):
    include_files[file] = []
    with open(file, "r") as f:
        for line in f.readlines():
            match = include_re.match(line)
            if match:
                include_file = match.group(1)
                include_file = next(os.path.join(d,include_file) for d in include_dirs if os.path.exists(os.path.join(d,include_file)))
                include_files[file].append(include_file)
                if include_file not in include_files:
                    find_include_files(include_file)
            elif cpp_include_re.match(line):
                cpp_includes.add(line)

for source_file in source_files:
    with open(source_file, "r") as f:
        for line in f.readlines():
            match = include_re.match(line)
            if match:
                include_file = match.group(1)
                include_file = next(os.path.join(d,include_file) for d in include_dirs if os.path.exists(os.path.join(d,include_file)))
                if include_file not in include_files:
                    find_include_files(include_file)
            elif cpp_include_re.match(line):
                cpp_includes.add(line)
            else:
                source_output += line
        source_output += '\n'

#print(include_files)

ordered_include_files = []
while include_files:
    dep_resolved = [f for f in include_files if not include_files[f]]
    ordered_include_files += dep_resolved
    for f in include_files:
        for d in dep_resolved:
            if d in include_files[f]:
                include_files[f].remove(d)
    for d in dep_resolved:
        del include_files[d]

with open(output_file, "w") as f:
    for cpp_include in cpp_includes:
        f.write(cpp_include)
    for include_file in ordered_include_files:
        with open(include_file, "r") as f2:
            for line in f2.readlines():
                match = include_re.match(line)
                if not match and not line.startswith("#pragma once") and not cpp_include_re.match(line):
                    f.write(line)
            f.write('\n')
    f.write(source_output)

os.system("pause")