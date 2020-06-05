#!/usr/bin/bash

#1 print the larger command line argument

if [ $1 -ge $2 ] 
then
	echo $1
else
	echo $2
fi

# describe a file

if [ -d $3 ]
then 
	echo $3 is a directory.
elif [ -e $3 ]
then
	if [ -s $3 ]
	then
		if [ -r $3 ]
		then
			echo $3 is readable.
		fi
		if [ -w $3 ]
		then
			echo $3 is writable.
		fi
		if [ -x $3 ]
		then
			echo $3 is executable.
		fi
	else
		echo $3 is a empty file.
	fi
else
	echo $3 doesn\'t exist.
fi

day=$( date | cut -d ' ' -f 1 )

case $day in
	Mon)
		echo Sad Sad
		;;
	Tue)
		echo Little Better
		;;
	Wed)
		echo There is Hope
		;;
	Thu)
		echo Winning
		;;
	Fri)
		echo Happy Happy
		;;
	Sat)
		echo Let Go Fishing
		;;
	Sun)
		echo Don\'t Think
		;;
	*)
		echo something not quite right.
		;;
esac
