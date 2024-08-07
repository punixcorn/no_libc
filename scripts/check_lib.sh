#!/bin/bash
files=$(/bin/ls lib/)

if [ -z "$files" ];then 
    ./scripts/shared.sh
fi
