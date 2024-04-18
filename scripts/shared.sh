#!/bin/bash

normal="\e[0m"
green="\e[32m"
red="\e[35m"
bold="\e[1m"

for i in $(/bin/ls include/src/) ;do

    printf "${bold}compiling${normal} ${green}$i${normal} => "
    name=$( sed 's/\.c//g' <<< $i )
    printf "${bold}${red}${name}lib.so${normal}\n"
    gcc -shared include/src/$i -o lib/lib${name}.so
done
