#!/bin/bash

year=$1
day=$(printf "%02d" $2)
extra_flags="${@:3}"
year_day_path="${year}/day${day}"
binpath="bin/${year_day_path}"

mkdir -p "bin/$year"

g++ -std=c++2a -Wall "src/${year_day_path}.cpp" -o $binpath $extra_flags
eval "./${binpath}"
