#!/bin/bash

make

if [ $? -ne 0 ]; then
    exit 1
fi

run_test() {
    for i in `ls inputs/$1/test*`; do
        echo "Running $1 on $i"
        ./$1 < $i
        echo "-------------------"
        echo
    done
}

if [ "$1" == "1" ]; then
    if [ "$2" == "y" ]; then
        run_test one
    else
        ./one < inputs/one.txt
    fi
elif [ "$1" == "2" ]; then
    if [ "$2" == "y" ]; then
        run_test two
    else
        ./two < inputs/two.txt
        
        # if two.txt is not present, run on one.txt
        if [ $? -ne 0 ]; then
            ./two < inputs/one.txt
        fi
    fi
else
    echo "Usage: $0 [1|2]"
fi

# usage: ./test.sh 1 y # run one and test
