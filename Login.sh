#!/bin/bash
# Ask the user for login details

read -p 'Username: ' uservar
read -sp 'Password: ' passvar
echo
echo Thank you, $uservar. We now have your login details. \($passvar\)


