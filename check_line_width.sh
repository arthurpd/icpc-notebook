#!/bin/bash

WIDTH_LIMIT="70"
WIDTH="$(awk '{print length}' $1 | sort -nr | head -n1)"

if (( WIDTH > WIDTH_LIMIT )); then
	echo -e "\e[1;33mWarning: File $1 has width $WIDTH, above $WIDTH_LIMIT limit.\e[0m"
fi
