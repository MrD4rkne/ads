#!/bin/bash

# Define colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

date=$(date +"%Y-%m-%d")

tasks=("zad1" "zad2")

path="./${date}"

template_path="${HOME}/code/sem3/asd/lab/template/zad/"

while [[ $# -gt 0 ]]; do
    case $1 in
        -a|--all)
            shift
            tasks=("$@")
            break
            ;;
        -p|--path)
            path=$2
            shift 2
            ;;
        -h|--help)
            echo -e "${YELLOW}Usage: ./generate.sh [options]${NC}"
            echo -e "${YELLOW}Options:${NC}"
            echo -e "${YELLOW}  -h, --help    Show this help message${NC}"
            echo -e "${YELLOW}  -a, --all <task1> <task2> ...    Generate all specified tasks${NC}"
            echo -e "${YELLOW}  -p, --path <path> Set directory where tasks will be generated${NC}"
            exit 0
            ;;
        *)
            echo -e "${RED}Unknown option: $1${NC}"
            exit 1
            ;;
    esac
done

echo -e "${GREEN}Generating tasks: ${tasks[@]}${NC}"
echo -e "${GREEN}Path: $path${NC}"
echo

if [ ! -d "$path" ]; then
    echo -e "${YELLOW}Creating directory $path${NC}"
    mkdir -p "$path"
    if [ $? -ne 0 ]; then
        echo -e "${RED}Failed to create directory $path${NC}"
        exit 1
    fi
fi

if ! cd $path; then
    echo -e "${RED}Failed to change directory to $path${NC}"
    exit 1
fi

for task in ${tasks[@]}; do
    echo -e "${GREEN}Generating task $task${NC}"
    if ! cp -r $template_path $task; then
        echo -e "${RED}Failed to copy template to $task${NC}"
        exit 1
    fi

    scripts=$(find $task -type f -name "*.sh")
    for script in $scripts; do
        if ! chmod +x $script; then
            echo -e "${RED}Failed to make $script executable${NC}"
            exit 1
        fi

        echo -e "${BLUE}Made $script executable${NC}"
    done

    echo -e "${GREEN}Successfully generated task $task${NC}"
    echo
done