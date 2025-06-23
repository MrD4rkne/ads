#!/bin/bash
make clean

echo "Compiling..."
if ! make ; then
    echo "Compilation failed"
    exit 1
fi

i=0

while true ;
do
    i=$((i+1))
    echo "Generating input: test$i.in"

    if ! ./gen $i > test.in ; then
        echo "Failed to generate input"
        exit 1
    fi

    echo "Running brut..."

    if ! time ./brut < test.in > test.out.correct ; then
        echo "Failed to run brut"
        exit 1
    fi

    echo

    echo "Running dom..."

    if ! time ./dom < test.in > test.out ; then
        echo "Failed to run dom"
        exit 1
    fi

    echo
    
    if ! diff test.out.correct test.out ; then
        echo "Test $i failed"
        exit 1
    fi
done



