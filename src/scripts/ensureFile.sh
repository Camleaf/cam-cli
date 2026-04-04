#!/bin/bash
# Script which ensures that the password document exists 
# needs the root file location in .local/lib passed to it

cd "$1" || exit 1
if [ ! -f "./stored/passwords.txt" ]; then
    if [ ! -d "./stored" ]; then
        mkdir "./stored/"
    fi
    touch "./stored/passwords.txt"
    echo "{}" > "./stored/passwords.txt"
fi
