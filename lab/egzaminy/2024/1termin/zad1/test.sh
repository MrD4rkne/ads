#!/bin/bash
make clean

BRUT=brut.a
PROG=zad.a
GEN=gen.a

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

i=0

while true ;
do
    i=$((i+1))
    echo -e "${YELLOW}Generating input: test$i.in.gen${NC}"

    if ! "./${GEN}" $i > test.in.gen ; then
        echo -e "${RED}Failed to generate input${NC}"
        exit 1
    fi

    echo -e "${YELLOW}Running ${BRUT}...${NC}"

    if ! "./${BRUT}" < test.in.gen > test.out.correct ; then
        echo -e "${RED}Failed to run ${BRUT}${NC}"
        exit 1
    fi

    echo

    echo -e "${YELLOW}Running ${PROG}...${NC}"

    if ! "./${PROG}" < test.in.gen > test.out ; then
        echo -e "${RED}Failed to run ${PROG}${NC}"
        exit 1
    fi

    echo
    
    if ! diff test.out.correct test.out ; then
        echo -e "${RED}Test $i failed${NC}"
        exit 1
    else
        echo -e "${GREEN}Test $i passed${NC}"
    fi
done
