#!/bin/bash
# demonstrate variable scope 1

var1=foo
var2=bar

# Let's verify their current value

echo $0:: var1 : $var1, var2 : $var2

export var1
./ExportScript2.sh

# Let's see what they are now

echo $0:: var1 : $var1, var2 : $var2
