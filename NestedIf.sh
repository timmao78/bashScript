#!/bin/bash
# Nested if statements

if [ $1 -gt 100 ]
then
	echo Hey that\' a large number.

	if (( $1 % 2 == 0 )) # This is a light variation on the if statement.
	then
		echo And is also an even number.
	fi
fi
