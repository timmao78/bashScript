#!/bin/bash

cp $1 "$( basename $1 .sh )_$( date "+%Y-%m-%d").sh"

#echo $@ | xargs -I file cp file "$( basename file .sh )_$( date "+%Y-%m-%d").sh"
echo $@ | xargs -I file echo $( basename $( basename file ) .sh )

