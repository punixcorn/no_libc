#!/bin/bash
files=$(ls lib/)

if [ -z "$files" ];then 
    ./scripts/shared.sh
fi
