find . -name '*.cpp' -print0 | 
    while IFS= read -r -d '' line; do 
        ./contest/hash_line.sh $line > $line.hash
    done
