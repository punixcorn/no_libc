#!/bin/bash

normal="\e[0m"
green="\e[32m"
red="\e[35m"
bold="\e[1m"

for file in $(/bin/ls include/src/) ;do
    printf "${bold}compiling${normal} ${green}$i${normal} => "
    name=$( sed 's/\.c//g' <<< $file )
    printf "${bold}${red}${name}lib.so${normal}\n"
    gcc -shared include/src/$file -o lib/lib${name}.so
done
