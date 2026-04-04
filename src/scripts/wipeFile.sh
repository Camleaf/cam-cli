#!/bin/bash
# Script which wipes the the password document exists 
# needs the root file location in .local/lib passed to it

cd "$1" || exit 1
if [  -f "./stored/passwords.txt" ]; then
    rm "./stored/passwords.txt"
fi
