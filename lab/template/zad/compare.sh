#!/bin/bash
make clean

PROG=zad.a

# Define colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${YELLOW}Compiling...${NC}"
if ! make ; then
    echo -e "${RED}Compilation failed${NC}"
    exit 1
fi

testsDir="./tests"
inputFiles=$(find "${testsDir}" -name "*.in")

failedTests=0

for file in $inputFiles
do
    testName=$(basename $file .in)
    echo -e "${YELLOW}Running ${PROG} on ${testName}...${NC}"

    prg_output="${testsDir}/${testName}.out"
    expected_output="${testsDir}/${testName}.out.exp"

    if ! "./${PROG}" < ${file} > ${prg_output} ; then
        echo -e "${RED}Failed to run ${PROG}${NC}"
        exit 1
    fi

    echo -e "${BLUE}Finished running ${PROG}${NC}"

    echo
    
    if ! diff $prg_output $expected_output  ; then
        echo -e "${RED}Test $i failed${NC}"
        failedTests=$((failedTests+1))
    else
        echo -e "${GREEN}Test $i passed${NC}"
    fi
done

if [ $failedTests -eq 0 ]; then
    echo -e "${GREEN}All tests passed${NC}"
else
    echo -e "${RED}Some tests failed${NC}"
fi
