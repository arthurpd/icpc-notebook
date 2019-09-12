#!/bin/bash

while IFS= read -r line; do # Loops lines of stdin.
	echo "$line" | cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-6 | tr -d '[:space:]';
	echo "	$line";	# Before $line is a tab.
done
