#!/bin/bash

first=$1
second=$2

if [[ ${first:?"No Argument passed"} < ${second:?"No Second Arg"} ]]
then
    echo "length of $first is smaller than $second"
fi