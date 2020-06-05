#!/usr/local/bin/bash

# 1
let a=$1*$2
echo $a

expr $1 \* $2

a=$(( $1 * $2))
echo $a

# 2 print tomorrow date

# 3 print a random number between 0~100
echo $(( $RANDOM % 100 ))

# 4 print a random number between $1 ~ $2
interval=$(( $2 - $1 ))
random=$(( $RANDOM % $interval ))
echo $(( $random + $1 ))
