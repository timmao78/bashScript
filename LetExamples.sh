#!/bin/bash

# Basic arithmetic using let

let a=5+4 # without quotes, no spaces are allowed
echo $a

let "a = 5 + 4" # in quotes, spaces are allowed
echo $a

let a++
echo $a

let "a = 4 * 5"
echo $a

let "a = $1 + 30"
echo $a

let a=$1+30
echo $a
