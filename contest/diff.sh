#!/bin/bash

set -ex

for ((a=1; ; a++))
do
	./gen.out $a > in.txt
	./width.out < in.txt > out1
	./width_brute.out < in.txt > out2
	diff out1 out2
done
