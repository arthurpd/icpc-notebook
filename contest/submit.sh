#!/bin/bash

if [ "$1" != "$2.cpp" ];
then
	echo "mismatch"
	exit 1
fi