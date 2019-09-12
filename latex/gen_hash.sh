#!/bin/bash

find ../ -name '*.cpp' -print0 | 
    while IFS= read -r -d '' line; do 
        echo "$line"
        ../contest/hash_line.sh < "$line" > "$line".hash
        echo -n "Full file hash: " >> "$line".hash
        ../contest/hash_file.sh < "$line" >> "$line".hash
    done
