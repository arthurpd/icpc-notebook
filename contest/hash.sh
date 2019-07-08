for i in $(seq 1 `wc -l < $1`); do 
	echo -en "$i\t";
	head -n $i $1 | cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-6 | tr -d '\n'; 
	echo -en '\t';
	sed -n $i'p' $1;
done
