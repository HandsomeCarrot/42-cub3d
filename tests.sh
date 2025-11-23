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

# Test function that takes map file path and expected return code
# Returns 0 if test passes, 1 if test fails
run_map_test() {
    local map_file="$1"
    local expected_code="$2"
    local test_name=$(basename "$map_file")
    
    echo -e "\n${YELLOW}TEST: $test_name${NC}"
	total_tests=$((total_tests + 1))
    
    # Run cub3d with the map file and capture exit code
    ./cub3d "$map_file" #> /dev/null 2>&1
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

echo -e "\n${YELLOW}=== Running Map Tests ===${NC}"

# Run all test cases with expected return codes
# Valid maps should return 0 (success)
run_map_test "./assets/maps/valid/basic.cub" 0
run_map_test "./assets/maps/valid/complex.cub" 0
run_map_test "./assets/maps/valid/order.cub" 0
run_map_test "./assets/maps/valid/spacing.cub" 0
run_map_test "./assets/maps/valid/more_spacing.cub" 0
run_map_test "./assets/maps/.valid/hidden_file.cub" 0

# Invalid maps should return non-zero (error)
run_map_test "./assets/maps/invalid/empty.cub" 1
run_map_test "./assets/maps/invalid/extra_color.cub" 1
run_map_test "./assets/maps/invalid/extra_map_layout.cub" 1
run_map_test "./assets/maps/invalid/extra_texture.cub" 1
run_map_test "./assets/maps/invalid/missing_color.cub" 1
run_map_test "./assets/maps/invalid/missing_extension" 1
run_map_test "./assets/maps/invalid/missing_map_layout.cub" 1
run_map_test "./assets/maps/invalid/missing_texture.cub" 1
run_map_test "./assets/maps/invalid/color_format.cub" 1
run_map_test "./assets/maps/invalid/extension.txt" 1
run_map_test "./assets/maps/invalid/extension_double.cub.all" 1
run_map_test "./assets/maps/invalid/texture_extension.cub" 1
run_map_test "./assets/maps/invalid/duplicate_player.cub" 1
run_map_test "./assets/maps/invalid/no_player.cub" 1
run_map_test "./assets/maps/invalid/open_map.cub" 1
run_map_test "./assets/maps/invalid/char.cub" 1
run_map_test "./assets/maps/invalid/map_first.cub" 1
# this is a hidden file (name = '', extension = '.cub') / (name = 'cub', extension = '')
run_map_test "./assets/maps/invalid/.cub" 1
run_map_test "./assets/maps/invalid/texture_path.cub" 1

echo -e "\nTotal tests: $total_tests"
echo -e "${GREEN}Passed tests: $passed_tests${NC}"
echo -e "${RED}Failed tests: $failed_tests${NC}"
