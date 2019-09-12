#!/bin/bash
# Hashes a file, ignoring lines with #include, all whitespace and comments

sed -e "/#include/d" | cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-6
