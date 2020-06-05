#!/usr/local/bin/bash

# only print filename size and owner

ls -lh |tr -s ' ' | cut -d ' ' -f 3,5,9
