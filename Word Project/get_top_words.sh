#!/bin/bash

read -p "File Name: " file
read -p "k: " numofwords

new lines
cat $file | tr '[:upper:]' '[:lower:]' | tr -sc '[:alnum:]' '\n' |

grep -vwf stopwords | sort | uniq -c | sort -k1,1nr -k2 |

head -n $numofwords | awk '{print $2}'
