#!/usr/local/bin/bash

# Basic arithmetic using double parentheses

a=$(( 4 + 5 ))
echo $a

a=$((3+5))
echo $a

b=$(( a + 3 )) # We may include variables without the preceding $ sign.
echo $b

b=$(( $a + 4 )) # Variables can be included with the $ sign if you prefer.
echo $b

(( b++ ))
echo $b

(( b+= 3))
echo $b

a=$(( 4 * 5 ))
echo $a

