#!/bin/bash

file=$1
responsecodes=()

while read -r l; do
line_content=$(awk '{print $NF}' <<< "$l")
responsecode=$(awk '{print $(NF-1)}' <<< "$l")

if [ "$line_content" = '-' ]; then
line_content=0
fi

((total_content_size+=line_content))
((linenum++))

if [[ ! " ${responsecodes[@]} " =~ " ${responsecode} " ]]; then
responsecodes+=("$responsecode")
fi

done < "$file"

if [ "$linenum" -ne 0 ]; then
avgcontentsize=$(((total_content_size+(linenum/2))/linenum))
elif [ "$linenum" -e 0 ]; then
avgcontentsize=0
fi

num_unique_responses="${#responsecodes[@]}"
echo "$avgcontentsize
$num_unique_responses"
