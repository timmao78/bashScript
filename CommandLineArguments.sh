#!/usr/local/bin/bash

echo "This script's name is $0."
echo "$# argument(s) is(are) passed in."
echo The first argument is $1.
echo The second argument is $2.
#echo $@
echo The exit status of the most recently run process is $?.
echo The process ID of the current script is $$.
echo The user running this script is $USER.
echo The host this script is running on is $HOSTNAME.
