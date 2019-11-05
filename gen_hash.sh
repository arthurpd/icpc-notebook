#!/bin/bash

echo "$1"
./contest/hash_line.sh < "$1" > "$1".hash
echo -n "Full file hash: " >> "$1".hash
./contest/hash_file.sh < "$1" >> "$1".hash
