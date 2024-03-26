#!/bin/bash

if [ "$#" -lt 2 ] || [ "$#" -gt 2 ]; then
echo "Invalid number of arguments"
exit 1
fi

if [ ! -r "$1" ]; then
echo "Cannot find/read $1"
exit 1
fi

data=$(<"$1")
data=$(awk -F ',' 'NR==1{print} NR>1{print} NR>1{a[$1]=$0} END{for(i in a) print
a[i]}' <<< "$data" | tail -n +2)
sorteddata=$(sort -t',' -k6,6nr -k1,4 <<< "$data")
highestvax=$(head -n "$2" <<< "$sorteddata")
awk -F ',' '{print $4 "," $5 "," $6}' <<< "$highestvax"
