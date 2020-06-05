#!/usr/local/bin/bash
# else example

if [ $# -eq 1 ]
then
	nl $1
else
	echo No file to 'nl'
fi
