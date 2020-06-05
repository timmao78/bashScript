#!/bin/bash

echo here is the random word:
head -$((RANDOM*7)) /usr/share/dict/words | tail -1
echo

echo here are the words containing no less than $1 characters:
grep -E "\w{$1}" /usr/share/dict/words
