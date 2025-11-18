
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
    
    echo "\n${YELLOW}TEST: $test_name${NC}"
	total_tests=$((total_tests + 1))
    
    # Run cub3d with the map file and capture exit code
    ./cub3d "$map_file" > /dev/null 2>&1
    local actual_code=$?
    
    # Compare actual and expected codes
    if [ "$actual_code" -eq "$expected_code" ]; then
        echo "${GREEN}✓ PASS: Expected $expected_code and got $actual_code${NC}"
		passed_tests=$((passed_tests + 1))
        return 0
    else
        echo "${RED}✗ FAIL: Expected $expected_code but got $actual_code${NC}"
		failed_tests=$((failed_tests + 1))
        return 1
    fi
}

echo "\n${YELLOW}=== Running Map Tests ===${NC}"

# Run all test cases with expected return codes
# Valid map should return 0 (success)
run_map_test "./assets/maps/basic.cub" 0
# Invalid maps should return non-zero (error)
run_map_test "./assets/maps/empty.cub" 1
run_map_test "./assets/maps/extra_color.cub" 1
run_map_test "./assets/maps/extra_map_layout.cub" 1
run_map_test "./assets/maps/extra_texture.cub" 1
run_map_test "./assets/maps/missing_color.cub" 1
run_map_test "./assets/maps/missing_extension" 1
run_map_test "./assets/maps/missing_map_layout.cub" 1
run_map_test "./assets/maps/missing_texture.cub" 1
run_map_test "./assets/maps/wrong_color_format.cub" 1
run_map_test "./assets/maps/wrong_extension.txt" 1
run_map_test "./assets/maps/wrong_extension2.cub.all" 1
run_map_test "./assets/maps/wrong_texture.cub" 1
run_map_test "./assets/maps/wrong_texture2.cub" 1

echo "\nTotal tests: $total_tests"
echo "${GREEN}Passed tests: $passed_tests${NC}"
echo "${RED}Failed tests: $failed_tests${NC}"
