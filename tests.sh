#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Initialize counters
total_tests=0
passed_tests=0
failed_tests=0

# Initialize flags
USE_VAL=0
USE_FUNCHECK=0
SHOW_OUTPUT=0

# Parse arguments
while getopts "tfo" opt; do
  case $opt in
    t)
      USE_VAL=1
      ;;
    f)
      USE_FUNCHECK=1
      ;;
    o)
      SHOW_OUTPUT=1
      ;;
    \?)
      echo "Invalid option: -$OPTARG" >&2
      exit 1
      ;;
  esac
done

# Check for mutual exclusivity
if [ "$USE_VAL" -eq 1 ] && [ "$USE_FUNCHECK" -eq 1 ]; then
    echo -e "${RED}Error: -t (valgrind) and -f (funcheck) cannot be used together. -f will be ignored${NC}"
    sleep 1
fi

# Set command prefix
CMD_PREFIX=""
if [ "$USE_VAL" -eq 1 ]; then
    CMD_PREFIX="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --track-fds=yes"
elif [ "$USE_FUNCHECK" -eq 1 ]; then
    CMD_PREFIX="funcheck -a"
fi

# Test function that takes map file path and expected return code
# Returns 0 if test passes, 1 if test fails
run_map_test() {
    local map_file="$1"
    local expected_code="$2"
    local test_name=$(basename "$map_file")
    
    echo -e "\n${YELLOW}TEST: $test_name${NC}"
	total_tests=$((total_tests + 1))
    
    # Run cub3d with the map file and capture exit code
    if [ "$SHOW_OUTPUT" -eq 1 ]; then
        $CMD_PREFIX ./cub3d "$map_file"
    else
        $CMD_PREFIX ./cub3d "$map_file" > /dev/null 2>&1
    fi
    local actual_code=$?
    
    # Compare actual and expected codes
    if [ "$actual_code" -eq "$expected_code" ]; then
        echo -e "${GREEN}✓ PASS: Expected $expected_code and got $actual_code${NC}"
		passed_tests=$((passed_tests + 1))
        return 0
    else
        echo -e "${RED}✗ FAIL: Expected $expected_code but got $actual_code${NC}"
		failed_tests=$((failed_tests + 1))
        return 1
    fi
}

echo -e "\n${YELLOW}=============== Running Map Tests ===============${NC}"

echo -e "\n${YELLOW}========= Valid Maps =========${NC}"
# Run all test cases with expected return codes
# Valid maps should return 0 (success)
for file in assets/maps/valid/*; do
    if [ -f "$file" ]; then
        run_map_test "$file" 0
    fi
done

echo -e "\n${YELLOW}========= Invalid Maps =========${NC}"
# Invalid maps should return non-zero (error)
for file in assets/maps/invalid/*; do
    if [ -f "$file" ]; then
        run_map_test "$file" 1
    fi
done

run_map_test "assets/maps/invalid/folder.cub" 1

echo -e "\nTotal tests: $total_tests"
echo -e "${GREEN}Passed tests: $passed_tests${NC}"
echo -e "${RED}Failed tests: $failed_tests${NC}"
