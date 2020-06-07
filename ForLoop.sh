#!/usr/local/bin/bash
names='Stan Kyle Cartman'

# loop through a list
for name in $names
do
	echo $name
done
echo

# loop through a range
for value in {1..5}
do
	echo $value
done
echo

# loop through a range stepping
echo $BASH_VERSION
for value in {10..0..2}
do
	echo $value
done

echo All done.
